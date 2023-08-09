#include "sys.h"
#include "usart.h"	
#include "usart2.h"     //包含需要的头文件
#include "usart3.h"     //包含需要的头文件
#include "wait_data_clock.h"     //包含需要的头文件
#include "wifi.h"
#include "Net_debug.h"
////////////////////////////////////////////////////////////////////////////////// 	 
//如果使用ucos,则包括下面的头文件即可.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos 使用	  
#endif

//////////////////////////////////////////////////////////////////
//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 

}; 

    


#endif 

/*使用microLib的方法*/
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
 
#if EN_USART3_RX   //如果使能了接收
//串口1中断服务程序
//注意,读取USARTx->SR能避免莫名其妙的错误   	
char USART3_debug_buffer[USART3_RXBUFF_SIZE];
s8 USART3_RX_BUF[USART3_REC_LEN];     //接收缓冲,最大USART3_REC_LEN个字节.
s8 USART3_TX_BUF[USART3_TXD_LEN];     //发送缓冲,最大USART3_REC_LEN个字节.
u32 u3_sys_time;
u8 u3_recive,u3_finish=0;
u32 u3_disconnect;
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
u16 USART3_RX_STA=0;       //接收状态标记	  
  
void Usart3_init(u32 bound){
  //串口使用的GPIO口配置
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure; //声明一个结构体变量，用来初始化GPIO
	//使能串口的RCC时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE); //使能UART3所在GPIOB的时钟
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

	//配置串口
	USART_InitStructure.USART_BaudRate = bound;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;


	// Configure USART3
	USART_Init(USART3, &USART_InitStructure);//配置串口3
	// Enable USART3 Receive interrupts 使能串口接收中断
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
	// Enable the USART3
	USART_Cmd(USART3, ENABLE);//使能串口3

	//串口中断配置
	//Configure the NVIC Preemption Priority Bits
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

	// Enable the USART3 Interrupt
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;        //子优先级3
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

void USART3_IRQHandler(void)                	//串口3中断服务程序
	{
		s8 Res,start=1;	
		u8 len;
		u3_sys_time=u3_disconnect=0;	
		u3_recive=1;
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
	{
		if(Net_debug==0)	
	{
		Res =USART_ReceiveData(USART3);//(USART3->DR);	//读取接收到的数据
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
		if(USART3_RX_STA>(USART3_REC_LEN-1))USART3_RX_STA=0;//接收数据错误,重新开始接收	
		}  
		
//				if(Res==0x5a)USART3_RX_STA=0;
//				else
//					{
//					USART3_RX_BUF[USART3_RX_STA&0X3FFF]=Res ;
//					USART3_RX_STA++;
//					if(USART3_RX_STA>(USART3_REC_LEN-1))USART3_RX_STA=0;//接收数据错误,重新开始接收	  
//					}		 
				
	}  	
	else
		{
//			USART3_debug_buffer[USART3_RX_STA] = USART3->DR;   //把接收到的数据保存到USART3_RxBuff中		
//      USART3_RX_STA++;	
		Res =USART_ReceiveData(USART3);//(USART3->DR);	//读取接收到的数据
		
			if(u3_finish==1)//接收到了0x0d
			{
				if(Res!=0x0a)USART3_RX_STA=0;//接收错误,重新开始
				else 
				{
					u3_finish=0;
					USART3_RX_STA=0;	//接收完成了 
//					WiFi_RxCounter=0;                           //WiFi接收数据量变量清零    
//					Usart2_RxCompleted=0;		
//					memset(WiFi_RX_BUF,0,WiFi_RXBUFF_SIZE);     //清空WiFi接收缓冲区 	
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
			else //还没收到0X0D
			{	
				if(Res==0x0d)
				{
					u3_finish=1;
				}
				else
				{
					USART3_debug_buffer[USART3_RX_STA]=Res ;
					USART3_RX_STA++;
					if(USART3_RX_STA>(USART3_RXBUFF_SIZE-1))USART3_RX_STA=0;//接收数据错误,重新开始接收	  
				}		 
			}  					
		}	
} 
	
#if SYSTEM_SUPPORT_OS 	//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
	OSIntExit();  											 
#endif
} 
#endif	
