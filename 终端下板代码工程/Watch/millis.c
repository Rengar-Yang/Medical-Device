/*
 * Project: Lightweight millisecond tracking library
 * Author: Zak Kemble, contact@zakkemble.co.uk
 * Copyright: (C) 2013 by Zak Kemble
 * License: GNU GPL v3 (see License.txt)
 * Web: http://blog.zakkemble.co.uk/millisecond-tracking-library-for-avr/
 */

#ifndef ARDUINO


#include "common.h"
#include "sys.h"
#include "led.h"
//#include "misc.h"

 millis_t milliseconds;


//static inline bool millis_interrupt_off(void)
//{
//	TIM_Cmd(TIM2,DISABLE);//����ʱ��
//	return true;
//}

//static inline bool millis_interrupt_on(void)
//{
//	TIM_Cmd(TIM2,ENABLE);//����ʱ��
//	return false;
//}

////// NEED TO DO A RESTORE THING! if paused then millis() is called it will unpause
//#define MILLIS_ATOMIC() for(bool cs = millis_interrupt_off(); cs; cs = millis_interrupt_on())


// Initialise library
void millis_init()
{
	// Timer settings
	  //1������Ƕ���жϿ�����NVIC
     NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);//���ȼ�����
     NVIC_InitTypeDef nvic;
     nvic.NVIC_IRQChannel=TIM2_IRQn;
     nvic.NVIC_IRQChannelCmd=ENABLE;
     nvic.NVIC_IRQChannelPreemptionPriority=0;
     nvic.NVIC_IRQChannelSubPriority=0;
     NVIC_Init(&nvic);

	 //2����ʱ����ʼ������
     TIM_TimeBaseInitTypeDef tim;//�ṹ��
     //���ȼ���������
     RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);//����ʱ��
     TIM_DeInit(TIM2);//����������
     tim.TIM_ClockDivision=TIM_CKD_DIV1;//������Ƶ
     tim.TIM_CounterMode=TIM_CounterMode_Up;//���ϼ���
     tim.TIM_Period=50;//�Զ���װ�ؼĴ�����ֵ
     tim.TIM_Prescaler=1439;//ʱ��Ԥ��Ƶ
     tim.TIM_RepetitionCounter=0;
     TIM_TimeBaseInit(TIM2,&tim);//��ʼ���ṹ��
     TIM_ClearFlag(TIM2,TIM_FLAG_Update);//�������жϱ�־
     TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
     TIM_Cmd(TIM2,ENABLE);//����ʱ��
     	
}

void Task_operater()
{
	//1������Ƕ���жϿ�����NVIC
     NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);//���ȼ�����
     NVIC_InitTypeDef nvic;
     nvic.NVIC_IRQChannel=TIM4_IRQn;
     nvic.NVIC_IRQChannelCmd=ENABLE;
     nvic.NVIC_IRQChannelPreemptionPriority=1;
     nvic.NVIC_IRQChannelSubPriority=1;
     NVIC_Init(&nvic);

	 //2����ʱ����ʼ������
     TIM_TimeBaseInitTypeDef tim;//�ṹ��
     //���ȼ���������
     RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);//����ʱ��
     TIM_DeInit(TIM4);//
     tim.TIM_ClockDivision=TIM_CKD_DIV1;//������Ƶ
     tim.TIM_CounterMode=TIM_CounterMode_Up;//���ϼ���
     tim.TIM_Period=32;//�Զ���װ�ؼĴ�����ֵ
     tim.TIM_Prescaler=1459;//ʱ��Ԥ��Ƶ
     tim.TIM_RepetitionCounter=0;
     TIM_TimeBaseInit(TIM4,&tim);//��ʼ���ṹ��
     TIM_ClearFlag(TIM4,TIM_FLAG_Update);//�������жϱ�־
     TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);
     TIM_Cmd(TIM4,ENABLE);//����ʱ��
}

void ADC_operater_timer()
{
	//1������Ƕ���жϿ�����NVIC
     NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);//���ȼ�����
     NVIC_InitTypeDef nvic;
     nvic.NVIC_IRQChannel=TIM3_IRQn;
     nvic.NVIC_IRQChannelCmd=ENABLE;
     nvic.NVIC_IRQChannelPreemptionPriority=1;
     nvic.NVIC_IRQChannelSubPriority=1;
     NVIC_Init(&nvic);

	 //2����ʱ����ʼ������
     TIM_TimeBaseInitTypeDef tim;//�ṹ��
     //���ȼ���������
     RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);//����ʱ��
     TIM_DeInit(TIM3);//
     tim.TIM_ClockDivision=TIM_CKD_DIV1;//������Ƶ
     tim.TIM_CounterMode=TIM_CounterMode_Up;//���ϼ���
     tim.TIM_Period=71;//�Զ���װ�ؼĴ�����ֵ
     tim.TIM_Prescaler=999;//ʱ��Ԥ��Ƶ
     tim.TIM_RepetitionCounter=0;
     TIM_TimeBaseInit(TIM3,&tim);//��ʼ���ṹ��
     TIM_ClearFlag(TIM3,TIM_FLAG_Update);//�������жϱ�־
     TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
     TIM_Cmd(TIM3,ENABLE);//����ʱ��
}

// Get current milliseconds
millis_t millis_get()
{
	millis_t ms;
		ms = milliseconds;
	return ms;
}


extern char imu_run;
extern char sensor_run;
static s8 id=0;//�豸ID��
int Post_time=0;
 //��ʱ���жϺ������� //TIM2ͨ�ö�ʱ��
 void TIM2_IRQHandler(void)
{
		if(TIM_GetITStatus(TIM2,TIM_IT_Update)!=RESET)//�ж��жϱ�־�Ƿ���
		{
			wifi_wait_data_hander();
//				milliseconds++;		
			u1_disconnect++;//�������ӱ�־λ
			Post_time++;
				update = true;
			
			#ifdef RTC_SRC
			  update = true;
			#else
			TDS_value=100;
					if(Post_time%600==0)
					{				
							TDS_value=200;	
					}		
					else if(Post_time%600==50)
					{				
							TDS_value=70;						
					}		
			/*˫��ͨѶ����*/
			/*             1    2   3    4        5            6           7        8          9         10       11          12        13    14  15    16      17         18*/
			/*����֡��ʽ��0XA5 0X5A ʪ�� �¶� �������߸�8λ �������ߵ�8λ ���ʸ�8λ ���ʵ�8λ ���ʼ��״̬ Ѫ����8λ Ѫ����8λ Ѫ�����״̬ �������� Сʱ ���� ����  �ĵ��8λ   �ĵ��8λ*/
			if (Post_time%50==0&&PostData==0)//˫��ͨѶ
			{					
				DHT11_Read_Data(&temperiture,&humi);
				USART3_TX_BUF[0]=0xA5;
				USART3_TX_BUF[1]=0x5A;
				USART3_TX_BUF[2]=humi;
				USART3_TX_BUF[3]=temperiture;
				USART3_TX_BUF[4]=n_brightness>>8;//�������߸�8λ
				USART3_TX_BUF[5]=n_brightness&0xff;//��������8λ
			  USART3_TX_BUF[6]=(n_heart_rate*7/10)>>8;//���ʸ�8λ
				USART3_TX_BUF[7]=(n_heart_rate*7/10)&0xff;//����8λ							
				USART3_TX_BUF[8]=ch_hr_valid;//���ʼ��״̬
				USART3_TX_BUF[9]=n_sp02>>8;//Ѫ����8λ
				USART3_TX_BUF[10]=n_sp02&0xff;//Ѫ����8λ
				USART3_TX_BUF[11]=ch_spo2_valid;//Ѫ�����״̬		
				
				if(isPressed[0]==0)							//��������λ
					USART3_TX_BUF[12]=1;
				else if(isPressed[1]==0)
					USART3_TX_BUF[12]=2;
				else if(isPressed[2]==0)
					USART3_TX_BUF[12]=3;
				else
					USART3_TX_BUF[12]=0;
				
				USART3_TX_BUF[13]=timeDate.time.hour;	//ʱ������λ
				USART3_TX_BUF[14]=timeDate.time.mins;
				USART3_TX_BUF[15]=timeDate.time.secs;
				
				USART3_TX_BUF[16]=TDS_value>>8;//�ĵ��8λ
				USART3_TX_BUF[17]=TDS_value&0xff;//�ĵ��8λ
			  if(DebugOK==1)
					{
						USART3_TX_BUF[18]=1;
						DebugOK=0;
					}
			  else
						USART3_TX_BUF[18]=0;
				USART3_TX_BUF[19]=0;
				USART3_TX_BUF[20]=0;
				USART3_TX_BUF[21]=0;
			  			
				for(int t=0;t<USART3_TXD_LEN;t++)//��������
					{
						USART_SendData(USART3, USART3_TX_BUF[t]);//�򴮿�3��������
						while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
					}	
			}
			
			if(imu_run||sensor_run||PostData)//���������ݲɼ�������ͨ�Ŵ���
				{
					if(Post_time%50==0)
					{						
							DHT11_Read_Data(&temperiture,&humi);
						
			        /*�����������ݰ�*/
							USART1_TX_BUF[0]=0xa5;
					  	USART1_TX_BUF[USART1_TXD_LEN-1]=0x5a;
							USART1_TX_BUF[1]=temperiture;//��������					
							USART1_TX_BUF[2]=humi;
							USART1_TX_BUF[3]=ch_hr_valid;//���ʼ��״̬
						  USART1_TX_BUF[4]=ch_spo2_valid;//Ѫ�����״̬	
							USART1_TX_BUF[5]=timeDate.time.hour;	//ʱ������λ
							USART1_TX_BUF[6]=timeDate.time.mins;
							USART1_TX_BUF[7]=timeDate.time.secs;
						
							USART1_TX_BUF[8]=n_brightness>>8;//�������߸�8λ
							USART1_TX_BUF[9]=n_brightness&0xff;//��������8λ
							USART1_TX_BUF[10]=(n_heart_rate*5/10)>>8;//���ʸ�8λ
							USART1_TX_BUF[11]=(n_heart_rate*5/10)&0xff;//����8λ										
							USART1_TX_BUF[12]=n_sp02>>8;//Ѫ����8λ
							USART1_TX_BUF[13]=n_sp02&0xff;//Ѫ����8λ			
							USART1_TX_BUF[14]=TDS_value>>8;//�ĵ��8λ
							USART1_TX_BUF[15]=TDS_value&0xff;//�ĵ��8λ

							USART1_TX_BUF[16]=(s16)yaw>>8;//yaw��8λ
							USART1_TX_BUF[17]=(s16)yaw&0xff;//yaw��8λ		
							USART1_TX_BUF[18]=(s16)roll>>8;//roll��8λ
							USART1_TX_BUF[19]=(s16)roll&0xff;//roll��8λ
							USART1_TX_BUF[USART1_TXD_LEN-2]=0;
						
							for(int i=1;i<=USART1_TXD_LEN-3;i++)
							USART1_TX_BUF[USART1_TXD_LEN-2]+=USART1_TX_BUF[i];	
						
							for(int t=0;t<USART1_TXD_LEN;t++)
							{
								USART_SendData(USART1, USART1_TX_BUF[t]);//�򴮿�1��������
								while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
							}		
							
							
							/*˫��ͨ�����ݰ�*/
							USART3_TX_BUF[0]=0xA5;
							USART3_TX_BUF[1]=0x5A;
							USART3_TX_BUF[2]=humi;
							USART3_TX_BUF[3]=temperiture;
							USART3_TX_BUF[4]=n_brightness>>8;//�������߸�8λ
							USART3_TX_BUF[5]=n_brightness&0xff;//��������8λ
							USART3_TX_BUF[6]=(n_heart_rate*5/10)>>8;//���ʸ�8λ
							USART3_TX_BUF[7]=(n_heart_rate*5/10)&0xff;//���ʵ�8λ							
							USART3_TX_BUF[8]=ch_hr_valid;//���ʼ��״̬
							USART3_TX_BUF[9]=n_sp02>>8;//Ѫ����8λ
							USART3_TX_BUF[10]=n_sp02&0xff;//Ѫ����8λ
							USART3_TX_BUF[11]=ch_spo2_valid;//Ѫ�����״̬		
							
							if(isPressed[0]==0)							//��������λ
								USART3_TX_BUF[12]=1;
							else if(isPressed[1]==0)
								USART3_TX_BUF[12]=2;
							else if(isPressed[2]==0)
								USART3_TX_BUF[12]=3;
							else
								USART3_TX_BUF[12]=0;
							
							USART3_TX_BUF[13]=timeDate.time.hour;	//ʱ������λ
							USART3_TX_BUF[14]=timeDate.time.mins;
							USART3_TX_BUF[15]=timeDate.time.secs;
							
							USART3_TX_BUF[16]=TDS_value>>8;//�ĵ��8λ
							USART3_TX_BUF[17]=TDS_value&0xff;//�ĵ��8λ
							if(DebugOK==1)
							{
								USART3_TX_BUF[18]=1;
								DebugOK=0;
							}
							else
								USART3_TX_BUF[18]=0;
							USART3_TX_BUF[19]=0;
							USART3_TX_BUF[20]=0;
							USART3_TX_BUF[21]=0;
							
							
							for(int t=0;t<USART3_TXD_LEN;t++)//��������
								{
									USART_SendData(USART3, USART3_TX_BUF[t]);//�򴮿�3��������
									while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
								}	
					}
								
					if(Post_time%1000==0)//�����ϴ�����
					{					
							if(PostOK==1)
								WiFi_send("id:%d,temp:%d,humi:%d,heart:%d,sp02:%d\r\n",id,temperiture,humi,n_heart_rate*5/10,n_sp02);
							}
	      }
			#endif
			
	 }
	 TIM_ClearITPendingBit(TIM2,TIM_FLAG_Update);     //�ֶ�����жϱ�־λ
}

void TIM4_IRQHandler(void)
{
	milliseconds++;		
	if(milliseconds%1000==0)
			{
				update = true;
				++timeDate.time.secs;   //ÿ���ӱ�־λ+1;
				
			}
	c_loop(); //ѭ��
	TIM_ClearITPendingBit(TIM4,TIM_FLAG_Update);     //�ֶ�����жϱ�־λ
}

#endif
