#include "sys.h"
#include "usart.h"	
#include "usart2.h"     //������Ҫ��ͷ�ļ�
#include "wait_data_clock.h"     //������Ҫ��ͷ�ļ�
#include "wifi.h"
#include "Net_debug.h"
////////////////////////////////////////////////////////////////////////////////// 	 
//���ʹ��ucos,����������ͷ�ļ�����.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos ʹ��	  
#endif

//////////////////////////////////////////////////////////////////
//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    

//�ض���fputc���� 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//ѭ������,ֱ���������   
    USART1->DR = (u8) ch;      
	return ch;
}
#endif 

/*ʹ��microLib�ķ���*/
 /* 
int fputc(int ch, FILE *f)
{
	USART_SendData(USART1, (uint8_t) ch);

	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) {}	
   
    return ch;
}
int GetKey (void)  { 

    while (!(USART1->SR & USART_FLAG_RXNE));

    return ((int)(USART1->DR & 0x1FF));
}
*/
 
#if EN_USART1_RX   //���ʹ���˽���
//����1�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	
char usart1_debug_buffer[USART1_RXBUFF_SIZE];
s8 USART1_RX_BUF[USART1_REC_LEN];     //���ջ���,���USART1_REC_LEN���ֽ�.
s16 USART1_TX_BUF[USART1_TXD_LEN];     //���ͻ���,���USART1_REC_LEN���ֽ�.
u32 u1_sys_time;
u8 u1_recive,u1_finish=0;
u32 u1_disconnect;
//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
u16 USART1_RX_STA=0;       //����״̬���	  
  
void Usart1_init(u32 bound){
  //GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��USART1��GPIOAʱ��
  
	//USART1_TX   GPIOA.9
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.9
   
  //USART1_RX	  GPIOA.10��ʼ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.10  

  //Usart1 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
  
   //USART ��ʼ������

	USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

  USART_Init(USART1, &USART_InitStructure); //��ʼ������1
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
  USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ���1 

}

__align(8) char USART1_TxBuff[USART1_TXBUFF_SIZE]; 

void u1_printf(char* fmt,...) 
{  
	unsigned int i,length;
	
	va_list ap;
	va_start(ap,fmt);
	vsprintf(USART1_TxBuff,fmt,ap);
	va_end(ap);	
	
	length=strlen((const char*)USART1_TxBuff);		
	while((USART1->SR&0X40)==0);
	for(i = 0;i < length;i ++)
	{
		USART1->DR = USART1_TxBuff[i];
		while((USART1->SR&0X40)==0);	
	}	
}

void USART1_IRQHandler(void)                	//����1�жϷ������
	{
		s8 Res,start=1;	
		u8 len;
		u1_sys_time=u1_disconnect=0;	
		u1_recive=1;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�����ж�
	{
		if(Net_debug==0)	
	{
			Res =USART_ReceiveData(USART1);//(USART1->DR);	//��ȡ���յ�������
			USART1_RX_BUF[USART1_RX_STA]=Res ;
			//if(USART1_RX_BUF[0]==0xA5)
			if(USART1_RX_BUF[0]!=-91)
			{
				start=0;
				USART1_RX_STA=0;
			}
			else
				start=1;
			if(start==1)
			{		
			USART1_RX_STA++;
			if(USART1_RX_STA>(USART1_REC_LEN-1))USART1_RX_STA=0;//�������ݴ���,���¿�ʼ����	
		  }  
		
//				if(Res==0x5a)USART1_RX_STA=0;
//				else
//					{
//					USART1_RX_BUF[USART1_RX_STA&0X3FFF]=Res ;
//					USART1_RX_STA++;
//					if(USART1_RX_STA>(USART1_REC_LEN-1))USART1_RX_STA=0;//�������ݴ���,���¿�ʼ����	  
//					}		 
				
  	}  	
	else
		{
//			usart1_debug_buffer[USART1_RX_STA] = USART1->DR;   //�ѽ��յ������ݱ��浽Usart1_RxBuff��		
//      USART1_RX_STA++;	
		Res =USART_ReceiveData(USART1);//(USART1->DR);	//��ȡ���յ�������
		
			if(u1_finish==1)//���յ���0x0d
			{
				if(Res!=0x0a)USART1_RX_STA=0;//���մ���,���¿�ʼ
				else 
				{
					u1_finish=0;
					USART1_RX_STA=0;	//��������� 
//					WiFi_RxCounter=0;                           //WiFi������������������    
//					Usart2_RxCompleted=0;		
//					memset(WiFi_RX_BUF,0,WiFi_RXBUFF_SIZE);     //���WiFi���ջ����� 	
          //u1_printf("%s\r\n",usart1_debug_buffer);					
					WiFi_send("%s\r\n",usart1_debug_buffer);
//					console_log(1,"%s",usart1_debug_buffer);
					memset(usart1_debug_buffer,0,USART1_RXBUFF_SIZE);    
//					while(!Usart2_RxCompleted);
//					delay_ms(1000);
//					console_log(1,"%s",&Data_buff[2]);
//			    u1_printf("%s",&Data_buff[2]);
//					u1_printf("%s",Usart2_RxBuff);
//					console_log(1,"%s",Usart2_RxBuff);
//  	      console_log(1,"%s",&Data_buff[2]);
				}
			}
			else //��û�յ�0X0D
			{	
				if(Res==0x0d)
				{
					u1_finish=1;
				}
				else
				{
					usart1_debug_buffer[USART1_RX_STA]=Res ;
					USART1_RX_STA++;
					if(USART1_RX_STA>(USART1_RXBUFF_SIZE-1))USART1_RX_STA=0;//�������ݴ���,���¿�ʼ����	  
				}		 
			}  					
		}	
} 
	
#if SYSTEM_SUPPORT_OS 	//���SYSTEM_SUPPORT_OSΪ�棬����Ҫ֧��OS.
	OSIntExit();  											 
#endif
} 
#endif	

