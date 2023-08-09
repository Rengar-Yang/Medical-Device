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
//	TIM_Cmd(TIM2,DISABLE);//开启时钟
//	return true;
//}

//static inline bool millis_interrupt_on(void)
//{
//	TIM_Cmd(TIM2,ENABLE);//开启时钟
//	return false;
//}

////// NEED TO DO A RESTORE THING! if paused then millis() is called it will unpause
//#define MILLIS_ATOMIC() for(bool cs = millis_interrupt_off(); cs; cs = millis_interrupt_on())


// Initialise library
void millis_init()
{
	// Timer settings
	  //1、配置嵌套中断控制器NVIC
     NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);//优先级分组
     NVIC_InitTypeDef nvic;
     nvic.NVIC_IRQChannel=TIM2_IRQn;
     nvic.NVIC_IRQChannelCmd=ENABLE;
     nvic.NVIC_IRQChannelPreemptionPriority=0;
     nvic.NVIC_IRQChannelSubPriority=0;
     NVIC_Init(&nvic);

	 //2、定时器初始化配置
     TIM_TimeBaseInitTypeDef tim;//结构体
     //优先级函数调用
     RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);//开启时钟
     TIM_DeInit(TIM2);//？？？？？
     tim.TIM_ClockDivision=TIM_CKD_DIV1;//采样分频
     tim.TIM_CounterMode=TIM_CounterMode_Up;//向上计数
     tim.TIM_Period=50;//自动重装载寄存器的值
     tim.TIM_Prescaler=1439;//时钟预分频
     tim.TIM_RepetitionCounter=0;
     TIM_TimeBaseInit(TIM2,&tim);//初始化结构体
     TIM_ClearFlag(TIM2,TIM_FLAG_Update);//清除溢出中断标志
     TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
     TIM_Cmd(TIM2,ENABLE);//开启时钟
     	
}

void Task_operater()
{
	//1、配置嵌套中断控制器NVIC
     NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);//优先级分组
     NVIC_InitTypeDef nvic;
     nvic.NVIC_IRQChannel=TIM4_IRQn;
     nvic.NVIC_IRQChannelCmd=ENABLE;
     nvic.NVIC_IRQChannelPreemptionPriority=1;
     nvic.NVIC_IRQChannelSubPriority=1;
     NVIC_Init(&nvic);

	 //2、定时器初始化配置
     TIM_TimeBaseInitTypeDef tim;//结构体
     //优先级函数调用
     RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);//开启时钟
     TIM_DeInit(TIM4);//
     tim.TIM_ClockDivision=TIM_CKD_DIV1;//采样分频
     tim.TIM_CounterMode=TIM_CounterMode_Up;//向上计数
     tim.TIM_Period=32;//自动重装载寄存器的值
     tim.TIM_Prescaler=1459;//时钟预分频
     tim.TIM_RepetitionCounter=0;
     TIM_TimeBaseInit(TIM4,&tim);//初始化结构体
     TIM_ClearFlag(TIM4,TIM_FLAG_Update);//清除溢出中断标志
     TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);
     TIM_Cmd(TIM4,ENABLE);//开启时钟
}

void ADC_operater_timer()
{
	//1、配置嵌套中断控制器NVIC
     NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);//优先级分组
     NVIC_InitTypeDef nvic;
     nvic.NVIC_IRQChannel=TIM3_IRQn;
     nvic.NVIC_IRQChannelCmd=ENABLE;
     nvic.NVIC_IRQChannelPreemptionPriority=1;
     nvic.NVIC_IRQChannelSubPriority=1;
     NVIC_Init(&nvic);

	 //2、定时器初始化配置
     TIM_TimeBaseInitTypeDef tim;//结构体
     //优先级函数调用
     RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);//开启时钟
     TIM_DeInit(TIM3);//
     tim.TIM_ClockDivision=TIM_CKD_DIV1;//采样分频
     tim.TIM_CounterMode=TIM_CounterMode_Up;//向上计数
     tim.TIM_Period=71;//自动重装载寄存器的值
     tim.TIM_Prescaler=999;//时钟预分频
     tim.TIM_RepetitionCounter=0;
     TIM_TimeBaseInit(TIM3,&tim);//初始化结构体
     TIM_ClearFlag(TIM3,TIM_FLAG_Update);//清除溢出中断标志
     TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
     TIM_Cmd(TIM3,ENABLE);//开启时钟
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
static s8 id=0;//设备ID号
int Post_time=0;
 //定时器中断函数处理。 //TIM2通用定时器
 void TIM2_IRQHandler(void)
{
		if(TIM_GetITStatus(TIM2,TIM_IT_Update)!=RESET)//判断中断标志是否发生
		{
			wifi_wait_data_hander();
//				milliseconds++;		
			u1_disconnect++;//串口连接标志位
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
			/*双板通讯代码*/
			/*             1    2   3    4        5            6           7        8          9         10       11          12        13    14  15    16      17         18*/
			/*数据帧格式：0XA5 0X5A 湿度 温度 心率曲线高8位 心率曲线低8位 心率高8位 心率低8位 心率检测状态 血氧高8位 血氧低8位 血氧检测状态 按键反馈 小时 分钟 秒数  心电高8位   心电低8位*/
			if (Post_time%50==0&&PostData==0)//双板通讯
			{					
				DHT11_Read_Data(&temperiture,&humi);
				USART3_TX_BUF[0]=0xA5;
				USART3_TX_BUF[1]=0x5A;
				USART3_TX_BUF[2]=humi;
				USART3_TX_BUF[3]=temperiture;
				USART3_TX_BUF[4]=n_brightness>>8;//心率曲线高8位
				USART3_TX_BUF[5]=n_brightness&0xff;//心率曲线8位
			  USART3_TX_BUF[6]=(n_heart_rate*7/10)>>8;//心率高8位
				USART3_TX_BUF[7]=(n_heart_rate*7/10)&0xff;//心率8位							
				USART3_TX_BUF[8]=ch_hr_valid;//心率监测状态
				USART3_TX_BUF[9]=n_sp02>>8;//血氧高8位
				USART3_TX_BUF[10]=n_sp02&0xff;//血氧低8位
				USART3_TX_BUF[11]=ch_spo2_valid;//血氧监测状态		
				
				if(isPressed[0]==0)							//按键数据位
					USART3_TX_BUF[12]=1;
				else if(isPressed[1]==0)
					USART3_TX_BUF[12]=2;
				else if(isPressed[2]==0)
					USART3_TX_BUF[12]=3;
				else
					USART3_TX_BUF[12]=0;
				
				USART3_TX_BUF[13]=timeDate.time.hour;	//时间数据位
				USART3_TX_BUF[14]=timeDate.time.mins;
				USART3_TX_BUF[15]=timeDate.time.secs;
				
				USART3_TX_BUF[16]=TDS_value>>8;//心电高8位
				USART3_TX_BUF[17]=TDS_value&0xff;//心电低8位
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
			  			
				for(int t=0;t<USART3_TXD_LEN;t++)//发送数据
					{
						USART_SendData(USART3, USART3_TX_BUF[t]);//向串口3发送数据
						while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);//等待发送结束
					}	
			}
			
			if(imu_run||sensor_run||PostData)//传感器数据采集和网络通信代码
				{
					if(Post_time%50==0)
					{						
							DHT11_Read_Data(&temperiture,&humi);
						
			        /*蓝牙发送数据包*/
							USART1_TX_BUF[0]=0xa5;
					  	USART1_TX_BUF[USART1_TXD_LEN-1]=0x5a;
							USART1_TX_BUF[1]=temperiture;//蓝牙发送					
							USART1_TX_BUF[2]=humi;
							USART1_TX_BUF[3]=ch_hr_valid;//心率监测状态
						  USART1_TX_BUF[4]=ch_spo2_valid;//血氧监测状态	
							USART1_TX_BUF[5]=timeDate.time.hour;	//时间数据位
							USART1_TX_BUF[6]=timeDate.time.mins;
							USART1_TX_BUF[7]=timeDate.time.secs;
						
							USART1_TX_BUF[8]=n_brightness>>8;//心率曲线高8位
							USART1_TX_BUF[9]=n_brightness&0xff;//心率曲线8位
							USART1_TX_BUF[10]=(n_heart_rate*5/10)>>8;//心率高8位
							USART1_TX_BUF[11]=(n_heart_rate*5/10)&0xff;//心率8位										
							USART1_TX_BUF[12]=n_sp02>>8;//血氧高8位
							USART1_TX_BUF[13]=n_sp02&0xff;//血氧低8位			
							USART1_TX_BUF[14]=TDS_value>>8;//心电高8位
							USART1_TX_BUF[15]=TDS_value&0xff;//心电低8位

							USART1_TX_BUF[16]=(s16)yaw>>8;//yaw高8位
							USART1_TX_BUF[17]=(s16)yaw&0xff;//yaw低8位		
							USART1_TX_BUF[18]=(s16)roll>>8;//roll高8位
							USART1_TX_BUF[19]=(s16)roll&0xff;//roll低8位
							USART1_TX_BUF[USART1_TXD_LEN-2]=0;
						
							for(int i=1;i<=USART1_TXD_LEN-3;i++)
							USART1_TX_BUF[USART1_TXD_LEN-2]+=USART1_TX_BUF[i];	
						
							for(int t=0;t<USART1_TXD_LEN;t++)
							{
								USART_SendData(USART1, USART1_TX_BUF[t]);//向串口1发送数据
								while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//等待发送结束
							}		
							
							
							/*双板通信数据包*/
							USART3_TX_BUF[0]=0xA5;
							USART3_TX_BUF[1]=0x5A;
							USART3_TX_BUF[2]=humi;
							USART3_TX_BUF[3]=temperiture;
							USART3_TX_BUF[4]=n_brightness>>8;//心率曲线高8位
							USART3_TX_BUF[5]=n_brightness&0xff;//心率曲线8位
							USART3_TX_BUF[6]=(n_heart_rate*5/10)>>8;//心率高8位
							USART3_TX_BUF[7]=(n_heart_rate*5/10)&0xff;//心率低8位							
							USART3_TX_BUF[8]=ch_hr_valid;//心率监测状态
							USART3_TX_BUF[9]=n_sp02>>8;//血氧高8位
							USART3_TX_BUF[10]=n_sp02&0xff;//血氧低8位
							USART3_TX_BUF[11]=ch_spo2_valid;//血氧监测状态		
							
							if(isPressed[0]==0)							//按键数据位
								USART3_TX_BUF[12]=1;
							else if(isPressed[1]==0)
								USART3_TX_BUF[12]=2;
							else if(isPressed[2]==0)
								USART3_TX_BUF[12]=3;
							else
								USART3_TX_BUF[12]=0;
							
							USART3_TX_BUF[13]=timeDate.time.hour;	//时间数据位
							USART3_TX_BUF[14]=timeDate.time.mins;
							USART3_TX_BUF[15]=timeDate.time.secs;
							
							USART3_TX_BUF[16]=TDS_value>>8;//心电高8位
							USART3_TX_BUF[17]=TDS_value&0xff;//心电低8位
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
							
							
							for(int t=0;t<USART3_TXD_LEN;t++)//发送数据
								{
									USART_SendData(USART3, USART3_TX_BUF[t]);//向串口3发送数据
									while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);//等待发送结束
								}	
					}
								
					if(Post_time%1000==0)//数据上传函数
					{					
							if(PostOK==1)
								WiFi_send("id:%d,temp:%d,humi:%d,heart:%d,sp02:%d\r\n",id,temperiture,humi,n_heart_rate*5/10,n_sp02);
							}
	      }
			#endif
			
	 }
	 TIM_ClearITPendingBit(TIM2,TIM_FLAG_Update);     //手动清除中断标志位
}

void TIM4_IRQHandler(void)
{
	milliseconds++;		
	if(milliseconds%1000==0)
			{
				update = true;
				++timeDate.time.secs;   //每秒钟标志位+1;
				
			}
	c_loop(); //循环
	TIM_ClearITPendingBit(TIM4,TIM_FLAG_Update);     //手动清除中断标志位
}

#endif
