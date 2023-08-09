#include "sys.h"  

//����������ƫ�Ƶ�ַ
//NVIC_VectTab:��ַ
//Offset:ƫ����		 
void MY_NVIC_SetVectorTable(u32 NVIC_VectTab,u32 Offset)	 
{ 	   	  
	SCB->VTOR=NVIC_VectTab|(Offset&(u32)0xFFFFFE00);//����NVIC��������ƫ�ƼĴ���,VTOR��9λ����,��[8:0]������
}
//����NVIC����
//NVIC_Group:NVIC���� 0~4 �ܹ�5�� 		   
void MY_NVIC_PriorityGroupConfig(u8 NVIC_Group)	 
{ 
	u32 temp,temp1;	  
	temp1=(~NVIC_Group)&0x07;//ȡ����λ
	temp1<<=8;
	temp=SCB->AIRCR;  //��ȡ��ǰ������
	temp&=0X0000F8FF; //�����ǰ����
	temp|=0X05FA0000; //д��Կ��
	temp|=temp1;	   
	SCB->AIRCR=temp;  //���÷���	    	  				   
}
//����NVIC 
//NVIC_PreemptionPriority:��ռ���ȼ�
//NVIC_SubPriority       :��Ӧ���ȼ�
//NVIC_Channel           :�жϱ��
//NVIC_Group             :�жϷ��� 0~4
//ע�����ȼ����ܳ����趨����ķ�Χ!����������벻���Ĵ���
//�黮��:
//��0:0λ��ռ���ȼ�,4λ��Ӧ���ȼ�
//��1:1λ��ռ���ȼ�,3λ��Ӧ���ȼ�
//��2:2λ��ռ���ȼ�,2λ��Ӧ���ȼ�
//��3:3λ��ռ���ȼ�,1λ��Ӧ���ȼ�
//��4:4λ��ռ���ȼ�,0λ��Ӧ���ȼ�
//NVIC_SubPriority��NVIC_PreemptionPriority��ԭ����,��ֵԽС,Խ����	   
void MY_NVIC_Init(u8 NVIC_PreemptionPriority,u8 NVIC_SubPriority,u8 NVIC_Channel,u8 NVIC_Group)	 
{ 
	u32 temp;	  
	MY_NVIC_PriorityGroupConfig(NVIC_Group);//���÷���
	temp=NVIC_PreemptionPriority<<(4-NVIC_Group);	  
	temp|=NVIC_SubPriority&(0x0f>>NVIC_Group);
	temp&=0xf;								//ȡ����λ
	NVIC->ISER[NVIC_Channel/32]|=1<<NVIC_Channel%32;//ʹ���ж�λ(Ҫ����Ļ�,����ICER��ӦλΪ1����)
	NVIC->IP[NVIC_Channel]|=temp<<4;				//������Ӧ���ȼ����������ȼ�   	    	  				   
} 
    

//GPIO��������
//GPIOx:GPIOA~GPIOK.
//BITx:0~15,����IO���ű��.
//AFx:0~15,����AF0~AF15.
//AF0~15�������(��������г����õ�,��ϸ�����STM32H743xx�����ֲ�,Table 9~19):
//AF0:MCO/SWD/SWCLK/RTC;   		AF1:TIM1/2/TIM16/17/LPTIM1;		AF2:TIM3~5/TIM12/HRTIM1/SAI1;	AF3:TIM8/LPTIM2~5/HRTIM1/LPUART1;
//AF4:I2C1~I2C4/TIM15/USART1;	AF5:SPI1~SPI6/CEC;         		AF6:SPI3/SAI1~3/UART4/I2C4; 	AF7:SPI2/3/6/USART1~3/6/UART7/SDIO1;
//AF8:USART4/5/8/SPDIF/SAI2/4;	AF9;FDCAN1~2/TIM13/14/LCD/QSPI; AF10:USB_OTG1/2/SAI2/4/QSPI;  	AF11:ETH/UART7/SDIO2/I2C4/COMP1/2;
//AF12:FMC/SDIO1/OTG2/LCD;		AF13:DCIM/DSI/LCD/COMP1/2; 		AF14:LCD/UART5;					AF15:EVENTOUT;
void GPIO_AF_Set(GPIO_TypeDef* GPIOx,u8 BITx,u8 AFx)
{  
	GPIOx->AFR[BITx>>3]&=~(0X0F<<((BITx&0X07)*4));
	GPIOx->AFR[BITx>>3]|=(u32)AFx<<((BITx&0X07)*4);
}   
//GPIOͨ������ 
//GPIOx:GPIOA~GPIOK.
//BITx:0X0000~0XFFFF,λ����,ÿ��λ����һ��IO,��0λ����Px0,��1λ����Px1,��������.����0X0101,����ͬʱ����Px0��Px8.
//MODE:0~3;ģʽѡ��,0,����(ϵͳ��λĬ��״̬);1,��ͨ���;2,���ù���;3,ģ������.
//OTYPE:0/1;�������ѡ��,0,�������;1,��©���.
//OSPEED:0~3;����ٶ�����,0,����;1,����;2,����;3,����. 
//PUPD:0~3:����������,0,����������;1,����;2,����;3,����.
//ע��:������ģʽ(��ͨ����/ģ������)��,OTYPE��OSPEED������Ч!!
void GPIO_Set(GPIO_TypeDef* GPIOx,u32 BITx,u32 MODE,u32 OTYPE,u32 OSPEED,u32 PUPD)
{  
	u32 pinpos=0,pos=0,curpin=0;
	for(pinpos=0;pinpos<16;pinpos++)
	{
		pos=1<<pinpos;	//һ����λ��� 
		curpin=BITx&pos;//��������Ƿ�Ҫ����
		if(curpin==pos)	//��Ҫ����
		{
			GPIOx->MODER&=~(3<<(pinpos*2));	//�����ԭ��������
			GPIOx->MODER|=MODE<<(pinpos*2);	//�����µ�ģʽ 
			if((MODE==0X01)||(MODE==0X02))	//��������ģʽ/���ù���ģʽ
			{  
				GPIOx->OSPEEDR&=~(3<<(pinpos*2));	//���ԭ��������
				GPIOx->OSPEEDR|=(OSPEED<<(pinpos*2));//�����µ��ٶ�ֵ  
				GPIOx->OTYPER&=~(1<<pinpos) ;		//���ԭ��������
				GPIOx->OTYPER|=OTYPE<<pinpos;		//�����µ����ģʽ
			}  
			GPIOx->PUPDR&=~(3<<(pinpos*2));	//�����ԭ��������
			GPIOx->PUPDR|=PUPD<<(pinpos*2);	//�����µ�������
		}
	}
} 

//ʱ�����ú���
//Fvco=Fs*(plln/pllm);
//Fsys=Fvco/pllp=Fs*(plln/(pllm*pllp));
//Fq=Fvco/pllq=Fs*(plln/(pllm*pllq));

//Fvco:VCOƵ��
//Fsys:ϵͳʱ��Ƶ��,Ҳ��PLL1��p��Ƶ���ʱ��Ƶ��
//Fq:PLL1��q��Ƶ���ʱ��Ƶ��
//Fs:PLL����ʱ��Ƶ��,������HSI,CSI,HSE��. 

//plln:PLL1��Ƶϵ��(PLL��Ƶ),ȡֵ��Χ:4~512.
//pllm:PLL1Ԥ��Ƶϵ��(��PLL֮ǰ�ķ�Ƶ),ȡֵ��Χ:2~63.
//pllp:PLL1��p��Ƶϵ��(PLL֮��ķ�Ƶ),��Ƶ����Ϊϵͳʱ��,ȡֵ��Χ:2~128.(�ұ�����2�ı���)
//pllq:PLL1��q��Ƶϵ��(PLL֮��ķ�Ƶ),ȡֵ��Χ:1~128.

//CPUƵ��(rcc_c_ck)=sys_d1cpre_ck=400Mhz 
//rcc_aclk=rcc_hclk3=200Mhz
//AHB1/2/3/4(rcc_hclk1/2/3/4)=200Mhz  
//APB1/2/3/4(rcc_pclk1/2/3/4)=100Mhz  
//pll2_p_ck=(25/25)*440/2)=220Mhz
//pll2_r_ck=FMCʱ��Ƶ��=((25/25)*440/2)=110Mhz

//�ⲿ����Ϊ25M��ʱ��,�Ƽ�ֵ:plln=160,pllm=5,pllp=2,pllq=4.
//�õ�:Fvco=25*(160/5)=800Mhz
//     Fsys=pll1_p_ck=800/2=400Mhz
//     Fq=pll1_q_ck=800/4=200Mhz
//����ֵ:0,�ɹ�;1,ʧ�ܡ�
u8 Sys_Clock_Set(u32 plln,u32 pllm,u32 pllp,u32 pllq)
{ 
	u16 retry=0;
	u8 status=0;
	
	PWR->CR3&=~(1<<2);				//SCUEN=0,����LDOEN��BYPASSλ������
	PWR->CR1|=0x01<<9;				//VOS range1,FLASH���ʿ��Եõ��������

	RCC->CR|=1<<16;					//HSEON=1,����HSE
	while(((RCC->CR&(1<<17))==0)&&(retry<0X7FFF))retry++;//�ȴ�HSE RDY
	if(retry==0X7FFF)status=1;		//HSE�޷�����
	else   
	{
		RCC->PLLCFGR|=3<<0;			//HSE as PLL source
		RCC->PLLCFGR|=0<<4;			//PLLM=1
		RCC->PLLCFGR|=20<<8;		//PLLN=20
		RCC->PLLCFGR|=1<<16;		//PLLP_EN
		RCC->PLLCFGR|=1<<20;		//PLLQ_EN
		RCC->PLLCFGR|=1<<24;		//PLLR_EN
		
		RCC->CR|=1<<24;				//PLL1ON=1,ʹ��PLL1
		
		while((RCC->CR&(1<<25))==0);//PLL1RDY=1?,�ȴ�PLL1׼����  
		RCC->CR|=1<<26;				//PLL2ON=1,ʹ��PLL2
		while((RCC->CR&(1<<27))==0);//PLL2RDY=1?,�ȴ�PLL2׼����  
	

		RCC->CFGR|=3<<0;			//SW[2:0]=3,ϵͳʱ��(sys_clk)ѡ������pll1_p_ck,��400Mhz
		while(1)
		{
			retry=(RCC->CFGR&(3<<2))>>2;	//��ȡSWS[2:0]��״̬,�ж��Ƿ��л��ɹ�
			if(retry==3)break;		//�ɹ���ϵͳʱ��Դ�л�Ϊpll1_p_ck
		}
			
		
		
		FLASH->ACR|=4<<0;			//LATENCY[2:0]=2,2��CPU�ȴ�����(@VOS1 Level,maxclock=210Mhz)
		

 
		RCC->CR|=1<<7;				//CSION=1,ʹ��CSI,ΪIO������Ԫ�ṩʱ��
		RCC->APB2ENR|=1<<0;			//SYSCFGEN=1,ʹ��SYSCFGʱ��

	} 
	return status;
}  
 
//ϵͳʱ�ӳ�ʼ������
//plln:PLL1��Ƶϵ��(PLL��Ƶ),ȡֵ��Χ:4~512.
//pllm:PLL1Ԥ��Ƶϵ��(��PLL֮ǰ�ķ�Ƶ),ȡֵ��Χ:2~63.
//pllp:PLL1��p��Ƶϵ��(PLL֮��ķ�Ƶ),��Ƶ����Ϊϵͳʱ��,ȡֵ��Χ:2~128.(�ұ�����2�ı���)
//pllq:PLL1��q��Ƶϵ��(PLL֮��ķ�Ƶ),ȡֵ��Χ:2~128.
void Stm32_Clock_Init(u32 plln,u32 pllm,u32 pllp,u32 pllq)
{  
	
	RCC->CR=0x00000001;				//����HISON,�����ڲ�����RC�񵴣�����λȫ����
	RCC->CFGR=0x00000000;			//CFGR���� 
	RCC->CR &= 0xEAF6FFFFU;   // ?? HSEON,CSSON,HSION ,PLLON ?     
	RCC->PLLCFGR = 0x00001000U;		//PLLCFGR���� 
	RCC->CR &= 0xFFFBFFFFU;       // ?? HSEBYP ?
	RCC->CIER=0x00000000;			//CIER����,��ֹ����RCC����ж�  
	Sys_Clock_Set(plln,pllm,pllp,pllq);//����ʱ��  

	//����������				  
#ifdef  VECT_TAB_RAM
	MY_NVIC_SetVectorTable(D1_AXISRAM_BASE,0x0);
#else   
	MY_NVIC_SetVectorTable(0x08000000,0x0);
#endif 
}		  

