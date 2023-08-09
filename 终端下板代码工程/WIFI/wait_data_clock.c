/*-------------------------------------------------*/
/*            ��γ����STM32ϵ�п�����              */
/*-------------------------------------------------*/
/*                                                 */
/*            ʵ�ֶ�ʱ��4���ܵ�Դ�ļ�              */
/*                                                 */
/*-------------------------------------------------*/
#include "wait_data_clock.h"
#include "stm32f10x.h"  //������Ҫ��ͷ�ļ�
#include "wifi.h"	       //������Ҫ��ͷ�ļ�
//#include "usart.h"
#include "usart2.h"
#include "usart3.h"
#include "Net_debug.h"
#include "Build_Server.h"
#define  WiFi_DATA_TIME_OK  8


char is_wifi_data_start=0;  //�Ƿ�ʼ��������
char id_from,id_to,size;
unsigned char wifi_time_cnt=0;
//char new_info=0;
extern void u1_printf();
char  Transfer_buff[100];     //���ݻ�����
uint8_t DebugOK=0;
//���������ڶ�ʱ���ж���
void wifi_wait_data_hander(void)
{
	if(is_wifi_data_start)
	{
		wifi_time_cnt++;
		if(wifi_time_cnt > WiFi_DATA_TIME_OK)
		{
			Usart2_RxCompleted = 1;                                       //����2������ɱ�־λ��λ
			memcpy(&Data_buff[2],Usart2_RxBuff,Usart2_RxCounter);         //��������
			Data_buff[0] = WiFi_RxCounter/256;                            //��¼���յ�������		
			Data_buff[1] = WiFi_RxCounter%256;                            //��¼���յ�������
			Data_buff[WiFi_RxCounter+2] = '\0';                           //���������
			WiFi_RxCounter=0;                                             //�������ֵ
			memset(WiFi_RX_BUF,0,WiFi_RXBUFF_SIZE);     //���WiFi���ջ����� 				
 			wifi_time_cnt=0;
			if(Net_debug==1)
			{				  
					u1_printf("%s",&Data_buff[2]);
					DebugOK=1;
//				  console_log(1,"%s",&Data_buff[2]);
			}
			if(Build_server==1)//��������Ϣת��
			{			
					id_from=Data_buff[9];//���ͷ�ID
					id_to=Data_buff[13];//���շ�ID
					size=Data_buff[11];	//���ݴ�С
					Transfer_buff[0]=id_from;//��ʾ���ͷ�ID
			  	Transfer_buff[1]=':';
					memcpy(&Transfer_buff[2],Data_buff+13,size);         //��������
					Transfer_buff[size]='\0';				
					if(new_info==1)//���µ�ת��ָ��
					{				  			
						  id_from=Data_buff[9];
							id_to=Data_buff[13];
							size=Data_buff[11]-2;
							memcpy(&Transfer_buff[0],Data_buff+15,size);         //��������
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
	   is_wifi_data_start=0;                        				  //�رս�����		
		}
	}

}



