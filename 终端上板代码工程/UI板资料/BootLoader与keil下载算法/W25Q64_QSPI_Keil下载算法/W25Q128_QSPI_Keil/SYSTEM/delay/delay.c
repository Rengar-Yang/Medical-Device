#include "delay.h"
#include "sys.h"
////////////////////////////////////////////////////////////////////////////////// 	 
//如果使用ucos,则包括下面的头文件即可.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos 使用	  
#endif
//////////////////////////////////////////////////////////////////////////////////  
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32H7开发板
//使用SysTick的普通计数模式对延迟进行管理(支持ucosii)
//包括delay_us,delay_ms
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2019/4/21
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved
//********************************************************************************
//修改说明
//无
//////////////////////////////////////////////////////////////////////////////////

static u16  fac_us=0;							//us延时倍乘数			   

//如果使用OS,则包括下面的头文件（以ucos为例）即可.
#if SYSTEM_SUPPORT_OS
#include "includes.h"							//支持OS时，使用	 
static u16 fac_ms=0;							//ms延时倍乘数,在os下,代表每个节拍的ms数 
#endif

	
#if SYSTEM_SUPPORT_OS							//如果SYSTEM_SUPPORT_OS定义了,说明要支持OS了(不限于UCOS).
//当delay_us/delay_ms需要支持OS的时候需要三个与OS相关的宏定义和函数来支持
//首先是3个宏定义:
//    delay_osrunning:用于表示OS当前是否正在运行,以决定是否可以使用相关函数
//delay_ostickspersec:用于表示OS设定的时钟节拍,delay_init将根据这个参数来初始哈systick
// delay_osintnesting:用于表示OS中断嵌套级别,因为中断里面不可以调度,delay_ms使用该参数来决定如何运行
//然后是3个函数:
//  delay_osschedlock:用于锁定OS任务调度,禁止调度
//delay_osschedunlock:用于解锁OS任务调度,重新开启调度
//    delay_ostimedly:用于OS延时,可以引起任务调度.

//本例程仅作UCOSII和UCOSIII的支持,其他OS,请自行参考着移植
//支持UCOSII
#ifdef 	OS_CRITICAL_METHOD						//OS_CRITICAL_METHOD定义了,说明要支持UCOSII				
#define delay_osrunning		OSRunning			//OS是否运行标记,0,不运行;1,在运行
#define delay_ostickspersec	OS_TICKS_PER_SEC	//OS时钟节拍,即每秒调度次数
#define delay_osintnesting 	OSIntNesting		//中断嵌套级别,即中断嵌套次数
#endif

//支持UCOSIII
#ifdef 	CPU_CFG_CRITICAL_METHOD					//CPU_CFG_CRITICAL_METHOD定义了,说明要支持UCOSIII	
#define delay_osrunning		OSRunning			//OS是否运行标记,0,不运行;1,在运行
#define delay_ostickspersec	OSCfg_TickRate_Hz	//OS时钟节拍,即每秒调度次数
#define delay_osintnesting 	OSIntNestingCtr		//中断嵌套级别,即中断嵌套次数
#endif


//us级延时时,关闭任务调度(防止打断us级延迟)
void delay_osschedlock(void)
{
#ifdef CPU_CFG_CRITICAL_METHOD   			//使用UCOSIII
	OS_ERR err; 
	OSSchedLock(&err);						//UCOSIII的方式,禁止调度，防止打断us延时
#else										//否则UCOSII
	OSSchedLock();							//UCOSII的方式,禁止调度，防止打断us延时
#endif
}

//us级延时时,恢复任务调度
void delay_osschedunlock(void)
{	
#ifdef CPU_CFG_CRITICAL_METHOD   			//使用UCOSIII
	OS_ERR err; 
	OSSchedUnlock(&err);					//UCOSIII的方式,恢复调度
#else										//否则UCOSII
	OSSchedUnlock();						//UCOSII的方式,恢复调度
#endif
}

//调用OS自带的延时函数延时
//ticks:延时的节拍数
void delay_ostimedly(u32 ticks)
{
#ifdef CPU_CFG_CRITICAL_METHOD
	OS_ERR err; 
	OSTimeDly(ticks,OS_OPT_TIME_PERIODIC,&err);//UCOSIII延时采用周期模式
#else
	OSTimeDly(ticks);						//UCOSII延时
#endif 
}
 
//systick中断服务函数,使用OS时用到
void SysTick_Handler(void)
{	
	if(delay_osrunning==1)					//OS开始跑了,才执行正常的调度处理
	{
		OSIntEnter();						//进入中断
		OSTimeTick();       				//调用ucos的时钟服务程序               
		OSIntExit();       	 				//触发任务切换软中断
	}
}
#endif
			   
//初始化延迟函数
//当使用ucos的时候,此函数会初始化ucos的时钟节拍
//SYSTICK的时钟设置为内核时钟
//SYSCLK:系统时钟频率,即CPU频率(rcc_c_ck),400Mhz
void delay_init(u16 SYSCLK)
{
#if SYSTEM_SUPPORT_OS 						//如果需要支持OS.
	u32 reload;
#endif
 	SysTick->CTRL|=1<<2;					//SYSTICK使用内核时钟源,同CPU同频率	 
	fac_us=SYSCLK;							//不论是否使用OS,fac_us都需要使用
#if SYSTEM_SUPPORT_OS 						//如果需要支持OS.
	reload=SYSCLK;							//每秒钟的计数次数 单位为M	   
	reload*=1000000/delay_ostickspersec;	//根据delay_ostickspersec设定溢出时间
											//reload为24位寄存器,最大值:16777216,在400M下,约合0.042s左右	
	fac_ms=1000/delay_ostickspersec;		//代表OS可以延时的最少单位	   
	SysTick->CTRL|=1<<1;   					//开启SYSTICK中断
	SysTick->LOAD=reload; 					//每1/delay_ostickspersec秒中断一次	
	SysTick->CTRL|=1<<0;   					//开启SYSTICK    
#endif
}

#if SYSTEM_SUPPORT_OS 						//如果需要支持OS.
//延时nus
//nus:要延时的us数.	
//nus:0~10737418(最大值即2^32/fac_us@fac_us=400)							   
void delay_us(u32 nus)
{		
	u32 ticks;
	u32 told,tnow,tcnt=0;
	u32 reload=SysTick->LOAD;				//LOAD的值	    	 
	ticks=nus*fac_us; 						//需要的节拍数 
	delay_osschedlock();					//阻止OS调度，防止打断us延时
	told=SysTick->VAL;        				//刚进入时的计数器值
	while(1)
	{
		tnow=SysTick->VAL;	
		if(tnow!=told)
		{	    
			if(tnow<told)tcnt+=told-tnow;	//这里注意一下SYSTICK是一个递减的计数器就可以了.
			else tcnt+=reload-tnow+told;	    
			told=tnow;
			if(tcnt>=ticks)break;			//时间超过/等于要延迟的时间,则退出.
		}  
	};
	delay_osschedunlock();					//恢复OS调度											    
}  
//延时nms
//nms:要延时的ms数
//nms:0~65535
void delay_ms(u16 nms)
{	
	if(delay_osrunning&&delay_osintnesting==0)//如果OS已经在跑了,并且不是在中断里面(中断里面不能任务调度)	    
	{		 
		if(nms>=fac_ms)						//延时的时间大于OS的最少时间周期 
		{ 
   			delay_ostimedly(nms/fac_ms);	//OS延时
		}
		nms%=fac_ms;						//OS已经无法提供这么小的延时了,采用普通方式延时    
	}
	delay_us((u32)(nms*1000));				//普通方式延时
}
#else  //不用ucos时
//延时nus
//nus为要延时的us数.	
//注意:nus的值,不要大于41943us(最大值即2^24/fac_us@fac_us=400)
void delay_us(u32 nus)
{		
	u32 temp;	    	 
	SysTick->LOAD=nus*fac_us; 				//时间加载	  		 
	SysTick->VAL=0x00;        				//清空计数器
	SysTick->CTRL|=1<<0 ;          			//开始倒数  
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));	//等待时间到达   
	SysTick->CTRL&=~(1<<0) ;       			//关闭SYSTICK
	SysTick->VAL =0X00;       				//清空计数器 
}
//延时nms
//注意nms的范围
//SysTick->LOAD为24位寄存器,所以,最大延时为:
//nms<=2^24 *1000/SYSCLK
//SYSCLK单位为Hz,nms单位为ms
//对400M条件下,nms<=41.94ms 
void delay_xms(u16 nms)
{	 		  	  
	u32 temp=0;		   
	SysTick->LOAD=(u32)nms*fac_us*1000;		//时间加载(SysTick->LOAD为24bit)
	SysTick->VAL =0x00;           			//清空计数器
	SysTick->CTRL|=1<<0 ;          			//开始倒数  
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));	//等待时间到达   
	SysTick->CTRL&=~(1<<0) ;       			//关闭SYSTICK
	SysTick->VAL =0X00;     		  		//清空计数器	  	    
} 
//延时nms 
//nms:0~65535
void delay_ms(u16 nms)
{	 	 
	u16 repeat=nms/30;						//这里用30,是考虑到可能有超频应用,
											//比如500Mhz的时候,delay_xms最大只能延时33.5ms左右了
	u16 remain=nms%30;
	while(repeat)
	{
		delay_xms(30);
		repeat--;
	}
	if(remain)delay_xms(remain);
} 
#endif
			 



































