#include "sys.h"
#include "usart.h"	
#include "usart2.h"     //������Ҫ��ͷ�ļ�
#include "usart3.h"     //������Ҫ��ͷ�ļ�
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

    


#endif 

/*ʹ��microLib�ķ���*/
 /* 
int fputc(int ch, FILE *f)
{
	USART_SendData(USART3, (uint8_t) ch);

	while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET) {}	
   
    return ch;
}
int GetKey (void)  { 

    while (!(USART3->SR & USART_FLAG_RXNE));

    return ((int)(USART3->DR & 0x1FF));
}
*/
 
#if EN_USART3_RX   //���ʹ���˽���
//����1�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	
char USART3_debug_buffer[USART3_RXBUFF_SIZE];
s8 USART3_RX_BUF[USART3_REC_LEN];     //���ջ���,���USART3_REC_LEN���ֽ�.
s8 USART3_TX_BUF[USART3_TXD_LEN];     //���ͻ���,���USART3_REC_LEN���ֽ�.
u32 u3_sys_time;
u8 u3_recive,u3_finish=0;
u32 u3_disconnect;
//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
u16 USART3_RX_STA=0;       //����״̬���	  
  
void Usart3_init(u32 bound){
  //����ʹ�õ�GPIO������
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure; //����һ���ṹ�������������ʼ��GPIO
	//ʹ�ܴ��ڵ�RCCʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE); //ʹ��UART3����GPIOB��ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	// Configure USART3 Rx (PB.11) as input floating
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	// Configure USART3 Tx (PB.10) as alternate function push-pull
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	//���ô���
	USART_InitStructure.USART_BaudRate = bound;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;


	// Configure USART3
	USART_Init(USART3, &USART_InitStructure);//���ô���3
	// Enable USART3 Receive interrupts ʹ�ܴ��ڽ����ж�
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
	// Enable the USART3
	USART_Cmd(USART3, ENABLE);//ʹ�ܴ���3

	//�����ж�����
	//Configure the NVIC Preemption Priority Bits
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

	// Enable the USART3 Interrupt
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;        //�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);


}

__align(8) char USART3_TxBuff[USART3_TXBUFF_SIZE]; 

void u3_printf(char* fmt,...) 
{  
	unsigned int i,length;
	
	va_list ap;
	va_start(ap,fmt);
	vsprintf(USART3_TxBuff,fmt,ap);
	va_end(ap);	
	
	length=strlen((const char*)USART3_TxBuff);		
	while((USART3->SR&0X40)==0);
	for(i = 0;i < length;i ++)
	{
		USART3->DR = USART3_TxBuff[i];
		while((USART3->SR&0X40)==0);	
	}	
}

void USART3_IRQHandler(void)                	//����3�жϷ������
	{
		s8 Res,start=1;	
		u8 len;
		u3_sys_time=u3_disconnect=0;	
		u3_recive=1;
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
	{
		if(Net_debug==0)	
	{
		Res =USART_ReceiveData(USART3);//(USART3->DR);	//��ȡ���յ�������
		USART3_RX_BUF[USART3_RX_STA]=Res ;
		//if(USART3_RX_BUF[0]==0xA5)
		if(USART3_RX_BUF[0]!=-91)
		{
			start=0;
			USART3_RX_STA=0;
		}
		else
			start=1;
		if(start==1)
		{		
		USART3_RX_STA++;
		if(USART3_RX_STA>(USART3_REC_LEN-1))USART3_RX_STA=0;//�������ݴ���,���¿�ʼ����	
		}  
		
//				if(Res==0x5a)USART3_RX_STA=0;
//				else
//					{
//					USART3_RX_BUF[USART3_RX_STA&0X3FFF]=Res ;
//					USART3_RX_STA++;
//					if(USART3_RX_STA>(USART3_REC_LEN-1))USART3_RX_STA=0;//�������ݴ���,���¿�ʼ����	  
//					}		 
				
	}  	
	else
		{
//			USART3_debug_buffer[USART3_RX_STA] = USART3->DR;   //�ѽ��յ������ݱ��浽USART3_RxBuff��		
//      USART3_RX_STA++;	
		Res =USART_ReceiveData(USART3);//(USART3->DR);	//��ȡ���յ�������
		
			if(u3_finish==1)//���յ���0x0d
			{
				if(Res!=0x0a)USART3_RX_STA=0;//���մ���,���¿�ʼ
				else 
				{
					u3_finish=0;
					USART3_RX_STA=0;	//��������� 
//					WiFi_RxCounter=0;                           //WiFi������������������    
//					Usart2_RxCompleted=0;		
//					memset(WiFi_RX_BUF,0,WiFi_RXBUFF_SIZE);     //���WiFi���ջ����� 	
          //u1_printf("%s\r\n",USART3_debug_buffer);					
					WiFi_send("%s\r\n",USART3_debug_buffer);
//					console_log(1,"%s",USART3_debug_buffer);
					memset(USART3_debug_buffer,0,USART3_RXBUFF_SIZE);    
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
					u3_finish=1;
				}
				else
				{
					USART3_debug_buffer[USART3_RX_STA]=Res ;
					USART3_RX_STA++;
					if(USART3_RX_STA>(USART3_RXBUFF_SIZE-1))USART3_RX_STA=0;//�������ݴ���,���¿�ʼ����	  
				}		 
			}  					
		}	
} 
	
#if SYSTEM_SUPPORT_OS 	//���SYSTEM_SUPPORT_OSΪ�棬����Ҫ֧��OS.
	OSIntExit();  											 
#endif
} 
#endif	
