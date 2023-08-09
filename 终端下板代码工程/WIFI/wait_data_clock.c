/*-------------------------------------------------*/
/*            超纬电子STM32系列开发板              */
/*-------------------------------------------------*/
/*                                                 */
/*            实现定时器4功能的源文件              */
/*                                                 */
/*-------------------------------------------------*/
#include "wait_data_clock.h"
#include "stm32f10x.h"  //包含需要的头文件
#include "wifi.h"	       //包含需要的头文件
//#include "usart.h"
#include "usart2.h"
#include "usart3.h"
#include "Net_debug.h"
#include "Build_Server.h"
#define  WiFi_DATA_TIME_OK  8


char is_wifi_data_start=0;  //是否开始接收数据
char id_from,id_to,size;
unsigned char wifi_time_cnt=0;
//char new_info=0;
extern void u1_printf();
char  Transfer_buff[100];     //数据缓冲区
uint8_t DebugOK=0;
//服务函数放在定时器中断中
void wifi_wait_data_hander(void)
{
	if(is_wifi_data_start)
	{
		wifi_time_cnt++;
		if(wifi_time_cnt > WiFi_DATA_TIME_OK)
		{
			Usart2_RxCompleted = 1;                                       //串口2接收完成标志位置位
			memcpy(&Data_buff[2],Usart2_RxBuff,Usart2_RxCounter);         //拷贝数据
			Data_buff[0] = WiFi_RxCounter/256;                            //记录接收的数据量		
			Data_buff[1] = WiFi_RxCounter%256;                            //记录接收的数据量
			Data_buff[WiFi_RxCounter+2] = '\0';                           //加入结束符
			WiFi_RxCounter=0;                                             //清零计数值
			memset(WiFi_RX_BUF,0,WiFi_RXBUFF_SIZE);     //清空WiFi接收缓冲区 				
 			wifi_time_cnt=0;
			if(Net_debug==1)
			{				  
					u1_printf("%s",&Data_buff[2]);
					DebugOK=1;
//				  console_log(1,"%s",&Data_buff[2]);
			}
			if(Build_server==1)//服务器消息转发
			{			
					id_from=Data_buff[9];//发送方ID
					id_to=Data_buff[13];//接收方ID
					size=Data_buff[11];	//数据大小
					Transfer_buff[0]=id_from;//显示发送方ID
			  	Transfer_buff[1]=':';
					memcpy(&Transfer_buff[2],Data_buff+13,size);         //拷贝数据
					Transfer_buff[size]='\0';				
					if(new_info==1)//有新的转发指令
					{				  			
						  id_from=Data_buff[9];
							id_to=Data_buff[13];
							size=Data_buff[11]-2;
							memcpy(&Transfer_buff[0],Data_buff+15,size);         //拷贝数据
							Transfer_buff[size]='\0';
							WiFi_send("AT+CIPSEND=%c,%c\r\n",id_to,size);
							delay_ms(500);
							WiFi_send("%s",&Transfer_buff[0]);		
              new_info=0;							
					}
					u1_printf("%s",&Data_buff[2]);
					if(Data_buff[4]!='+')
						console_log(1,"%s",&Data_buff[2]);
				  else
			      console_log(1,"%s",&Transfer_buff[0]);				
			}
	   is_wifi_data_start=0;                        				  //关闭接收器		
		}
	}

}



