#include "sys.h"
#include "usart.h"	
#include "usart2.h"     //包含需要的头文件
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

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    

//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
    USART1->DR = (u8) ch;      
	return ch;
}
#endif 

/*使用microLib的方法*/
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
 
#if EN_USART1_RX   //如果使能了接收
//串口1中断服务程序
//注意,读取USARTx->SR能避免莫名其妙的错误   	
char usart1_debug_buffer[USART1_RXBUFF_SIZE];
s8 USART1_RX_BUF[USART1_REC_LEN];     //接收缓冲,最大USART1_REC_LEN个字节.
s16 USART1_TX_BUF[USART1_TXD_LEN];     //发送缓冲,最大USART1_REC_LEN个字节.
u32 u1_sys_time;
u8 u1_recive,u1_finish=0;
u32 u1_disconnect;
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
u16 USART1_RX_STA=0;       //接收状态标记	  
  
void Usart1_init(u32 bound){
  //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//使能USART1，GPIOA时钟
  
	//USART1_TX   GPIOA.9
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.9
   
  //USART1_RX	  GPIOA.10初始化
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.10  

  //Usart1 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  
   //USART 初始化设置

	USART_InitStructure.USART_BaudRate = bound;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

  USART_Init(USART1, &USART_InitStructure); //初始化串口1
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启串口接受中断
  USART_Cmd(USART1, ENABLE);                    //使能串口1 

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

void USART1_IRQHandler(void)                	//串口1中断服务程序
	{
		s8 Res,start=1;	
		u8 len;
		u1_sys_time=u1_disconnect=0;	
		u1_recive=1;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断
	{
		if(Net_debug==0)	
	{
			Res =USART_ReceiveData(USART1);//(USART1->DR);	//读取接收到的数据
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
			if(USART1_RX_STA>(USART1_REC_LEN-1))USART1_RX_STA=0;//接收数据错误,重新开始接收	
		  }  
		
//				if(Res==0x5a)USART1_RX_STA=0;
//				else
//					{
//					USART1_RX_BUF[USART1_RX_STA&0X3FFF]=Res ;
//					USART1_RX_STA++;
//					if(USART1_RX_STA>(USART1_REC_LEN-1))USART1_RX_STA=0;//接收数据错误,重新开始接收	  
//					}		 
				
  	}  	
	else
		{
//			usart1_debug_buffer[USART1_RX_STA] = USART1->DR;   //把接收到的数据保存到Usart1_RxBuff中		
//      USART1_RX_STA++;	
		Res =USART_ReceiveData(USART1);//(USART1->DR);	//读取接收到的数据
		
			if(u1_finish==1)//接收到了0x0d
			{
				if(Res!=0x0a)USART1_RX_STA=0;//接收错误,重新开始
				else 
				{
					u1_finish=0;
					USART1_RX_STA=0;	//接收完成了 
//					WiFi_RxCounter=0;                           //WiFi接收数据量变量清零    
//					Usart2_RxCompleted=0;		
//					memset(WiFi_RX_BUF,0,WiFi_RXBUFF_SIZE);     //清空WiFi接收缓冲区 	
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
			else //还没收到0X0D
			{	
				if(Res==0x0d)
				{
					u1_finish=1;
				}
				else
				{
					usart1_debug_buffer[USART1_RX_STA]=Res ;
					USART1_RX_STA++;
					if(USART1_RX_STA>(USART1_RXBUFF_SIZE-1))USART1_RX_STA=0;//接收数据错误,重新开始接收	  
				}		 
			}  					
		}	
} 
	
#if SYSTEM_SUPPORT_OS 	//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
	OSIntExit();  											 
#endif
} 
#endif	

