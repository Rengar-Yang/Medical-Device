#include "sys.h"  

//设置向量表偏移地址
//NVIC_VectTab:基址
//Offset:偏移量		 
void MY_NVIC_SetVectorTable(u32 NVIC_VectTab,u32 Offset)	 
{ 	   	  
	SCB->VTOR=NVIC_VectTab|(Offset&(u32)0xFFFFFE00);//设置NVIC的向量表偏移寄存器,VTOR低9位保留,即[8:0]保留。
}
//设置NVIC分组
//NVIC_Group:NVIC分组 0~4 总共5组 		   
void MY_NVIC_PriorityGroupConfig(u8 NVIC_Group)	 
{ 
	u32 temp,temp1;	  
	temp1=(~NVIC_Group)&0x07;//取后三位
	temp1<<=8;
	temp=SCB->AIRCR;  //读取先前的设置
	temp&=0X0000F8FF; //清空先前分组
	temp|=0X05FA0000; //写入钥匙
	temp|=temp1;	   
	SCB->AIRCR=temp;  //设置分组	    	  				   
}
//设置NVIC 
//NVIC_PreemptionPriority:抢占优先级
//NVIC_SubPriority       :响应优先级
//NVIC_Channel           :中断编号
//NVIC_Group             :中断分组 0~4
//注意优先级不能超过设定的组的范围!否则会有意想不到的错误
//组划分:
//组0:0位抢占优先级,4位响应优先级
//组1:1位抢占优先级,3位响应优先级
//组2:2位抢占优先级,2位响应优先级
//组3:3位抢占优先级,1位响应优先级
//组4:4位抢占优先级,0位响应优先级
//NVIC_SubPriority和NVIC_PreemptionPriority的原则是,数值越小,越优先	   
void MY_NVIC_Init(u8 NVIC_PreemptionPriority,u8 NVIC_SubPriority,u8 NVIC_Channel,u8 NVIC_Group)	 
{ 
	u32 temp;	  
	MY_NVIC_PriorityGroupConfig(NVIC_Group);//设置分组
	temp=NVIC_PreemptionPriority<<(4-NVIC_Group);	  
	temp|=NVIC_SubPriority&(0x0f>>NVIC_Group);
	temp&=0xf;								//取低四位
	NVIC->ISER[NVIC_Channel/32]|=1<<NVIC_Channel%32;//使能中断位(要清除的话,设置ICER对应位为1即可)
	NVIC->IP[NVIC_Channel]|=temp<<4;				//设置响应优先级和抢断优先级   	    	  				   
} 
    

//GPIO复用设置
//GPIOx:GPIOA~GPIOK.
//BITx:0~15,代表IO引脚编号.
//AFx:0~15,代表AF0~AF15.
//AF0~15设置情况(这里仅是列出常用的,详细的请见STM32H743xx数据手册,Table 9~19):
//AF0:MCO/SWD/SWCLK/RTC;   		AF1:TIM1/2/TIM16/17/LPTIM1;		AF2:TIM3~5/TIM12/HRTIM1/SAI1;	AF3:TIM8/LPTIM2~5/HRTIM1/LPUART1;
//AF4:I2C1~I2C4/TIM15/USART1;	AF5:SPI1~SPI6/CEC;         		AF6:SPI3/SAI1~3/UART4/I2C4; 	AF7:SPI2/3/6/USART1~3/6/UART7/SDIO1;
//AF8:USART4/5/8/SPDIF/SAI2/4;	AF9;FDCAN1~2/TIM13/14/LCD/QSPI; AF10:USB_OTG1/2/SAI2/4/QSPI;  	AF11:ETH/UART7/SDIO2/I2C4/COMP1/2;
//AF12:FMC/SDIO1/OTG2/LCD;		AF13:DCIM/DSI/LCD/COMP1/2; 		AF14:LCD/UART5;					AF15:EVENTOUT;
void GPIO_AF_Set(GPIO_TypeDef* GPIOx,u8 BITx,u8 AFx)
{  
	GPIOx->AFR[BITx>>3]&=~(0X0F<<((BITx&0X07)*4));
	GPIOx->AFR[BITx>>3]|=(u32)AFx<<((BITx&0X07)*4);
}   
//GPIO通用设置 
//GPIOx:GPIOA~GPIOK.
//BITx:0X0000~0XFFFF,位设置,每个位代表一个IO,第0位代表Px0,第1位代表Px1,依次类推.比如0X0101,代表同时设置Px0和Px8.
//MODE:0~3;模式选择,0,输入(系统复位默认状态);1,普通输出;2,复用功能;3,模拟输入.
//OTYPE:0/1;输出类型选择,0,推挽输出;1,开漏输出.
//OSPEED:0~3;输出速度设置,0,低速;1,中速;2,快速;3,高速. 
//PUPD:0~3:上下拉设置,0,不带上下拉;1,上拉;2,下拉;3,保留.
//注意:在输入模式(普通输入/模拟输入)下,OTYPE和OSPEED参数无效!!
void GPIO_Set(GPIO_TypeDef* GPIOx,u32 BITx,u32 MODE,u32 OTYPE,u32 OSPEED,u32 PUPD)
{  
	u32 pinpos=0,pos=0,curpin=0;
	for(pinpos=0;pinpos<16;pinpos++)
	{
		pos=1<<pinpos;	//一个个位检查 
		curpin=BITx&pos;//检查引脚是否要设置
		if(curpin==pos)	//需要设置
		{
			GPIOx->MODER&=~(3<<(pinpos*2));	//先清除原来的设置
			GPIOx->MODER|=MODE<<(pinpos*2);	//设置新的模式 
			if((MODE==0X01)||(MODE==0X02))	//如果是输出模式/复用功能模式
			{  
				GPIOx->OSPEEDR&=~(3<<(pinpos*2));	//清除原来的设置
				GPIOx->OSPEEDR|=(OSPEED<<(pinpos*2));//设置新的速度值  
				GPIOx->OTYPER&=~(1<<pinpos) ;		//清除原来的设置
				GPIOx->OTYPER|=OTYPE<<pinpos;		//设置新的输出模式
			}  
			GPIOx->PUPDR&=~(3<<(pinpos*2));	//先清除原来的设置
			GPIOx->PUPDR|=PUPD<<(pinpos*2);	//设置新的上下拉
		}
	}
} 

//时钟设置函数
//Fvco=Fs*(plln/pllm);
//Fsys=Fvco/pllp=Fs*(plln/(pllm*pllp));
//Fq=Fvco/pllq=Fs*(plln/(pllm*pllq));

//Fvco:VCO频率
//Fsys:系统时钟频率,也是PLL1的p分频输出时钟频率
//Fq:PLL1的q分频输出时钟频率
//Fs:PLL输入时钟频率,可以是HSI,CSI,HSE等. 

//plln:PLL1倍频系数(PLL倍频),取值范围:4~512.
//pllm:PLL1预分频系数(进PLL之前的分频),取值范围:2~63.
//pllp:PLL1的p分频系数(PLL之后的分频),分频后作为系统时钟,取值范围:2~128.(且必须是2的倍数)
//pllq:PLL1的q分频系数(PLL之后的分频),取值范围:1~128.

//CPU频率(rcc_c_ck)=sys_d1cpre_ck=400Mhz 
//rcc_aclk=rcc_hclk3=200Mhz
//AHB1/2/3/4(rcc_hclk1/2/3/4)=200Mhz  
//APB1/2/3/4(rcc_pclk1/2/3/4)=100Mhz  
//pll2_p_ck=(25/25)*440/2)=220Mhz
//pll2_r_ck=FMC时钟频率=((25/25)*440/2)=110Mhz

//外部晶振为25M的时候,推荐值:plln=160,pllm=5,pllp=2,pllq=4.
//得到:Fvco=25*(160/5)=800Mhz
//     Fsys=pll1_p_ck=800/2=400Mhz
//     Fq=pll1_q_ck=800/4=200Mhz
//返回值:0,成功;1,失败。
u8 Sys_Clock_Set(u32 plln,u32 pllm,u32 pllp,u32 pllq)
{ 
	u16 retry=0;
	u8 status=0;
	
	PWR->CR3&=~(1<<2);				//SCUEN=0,锁定LDOEN和BYPASS位的设置
	PWR->CR1|=0x01<<9;				//VOS range1,FLASH访问可以得到最高性能

	RCC->CR|=1<<16;					//HSEON=1,开启HSE
	while(((RCC->CR&(1<<17))==0)&&(retry<0X7FFF))retry++;//等待HSE RDY
	if(retry==0X7FFF)status=1;		//HSE无法就绪
	else   
	{
		RCC->PLLCFGR|=3<<0;			//HSE as PLL source
		RCC->PLLCFGR|=0<<4;			//PLLM=1
		RCC->PLLCFGR|=20<<8;		//PLLN=20
		RCC->PLLCFGR|=1<<16;		//PLLP_EN
		RCC->PLLCFGR|=1<<20;		//PLLQ_EN
		RCC->PLLCFGR|=1<<24;		//PLLR_EN
		
		RCC->CR|=1<<24;				//PLL1ON=1,使能PLL1
		
		while((RCC->CR&(1<<25))==0);//PLL1RDY=1?,等待PLL1准备好  
		RCC->CR|=1<<26;				//PLL2ON=1,使能PLL2
		while((RCC->CR&(1<<27))==0);//PLL2RDY=1?,等待PLL2准备好  
	

		RCC->CFGR|=3<<0;			//SW[2:0]=3,系统时钟(sys_clk)选择来自pll1_p_ck,即400Mhz
		while(1)
		{
			retry=(RCC->CFGR&(3<<2))>>2;	//获取SWS[2:0]的状态,判断是否切换成功
			if(retry==3)break;		//成功将系统时钟源切换为pll1_p_ck
		}
			
		
		
		FLASH->ACR|=4<<0;			//LATENCY[2:0]=2,2个CPU等待周期(@VOS1 Level,maxclock=210Mhz)
		

 
		RCC->CR|=1<<7;				//CSION=1,使能CSI,为IO补偿单元提供时钟
		RCC->APB2ENR|=1<<0;			//SYSCFGEN=1,使能SYSCFG时钟

	} 
	return status;
}  
 
//系统时钟初始化函数
//plln:PLL1倍频系数(PLL倍频),取值范围:4~512.
//pllm:PLL1预分频系数(进PLL之前的分频),取值范围:2~63.
//pllp:PLL1的p分频系数(PLL之后的分频),分频后作为系统时钟,取值范围:2~128.(且必须是2的倍数)
//pllq:PLL1的q分频系数(PLL之后的分频),取值范围:2~128.
void Stm32_Clock_Init(u32 plln,u32 pllm,u32 pllp,u32 pllq)
{  
	
	RCC->CR=0x00000001;				//设置HISON,开启内部高速RC振荡，其他位全清零
	RCC->CFGR=0x00000000;			//CFGR清零 
	RCC->CR &= 0xEAF6FFFFU;   // ?? HSEON,CSSON,HSION ,PLLON ?     
	RCC->PLLCFGR = 0x00001000U;		//PLLCFGR清零 
	RCC->CR &= 0xFFFBFFFFU;       // ?? HSEBYP ?
	RCC->CIER=0x00000000;			//CIER清零,禁止所有RCC相关中断  
	Sys_Clock_Set(plln,pllm,pllp,pllq);//设置时钟  

	//配置向量表				  
#ifdef  VECT_TAB_RAM
	MY_NVIC_SetVectorTable(D1_AXISRAM_BASE,0x0);
#else   
	MY_NVIC_SetVectorTable(0x08000000,0x0);
#endif 
}		  

