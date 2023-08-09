#include "yaogan.h"
#include "usart.h"

volatile unsigned short ADCConvertedValue[4]={0};//�������ADCת�����
         
void ADC_DMA_Init(void)
{

    DMA_InitTypeDef DMA_InitStructure;

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);//ʹ��ʱ��

    DMA_DeInit(DMA1_Channel1);    //��ͨ��һ�Ĵ�����ΪĬ��ֵ
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&(ADC1->DR);//�ò������Զ���DMA�������ַ
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&ADCConvertedValue;//�ò������Զ���DMA�ڴ����ַ(ת���������ĵ�ַ)
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;//�ò����涨����������Ϊ���ݴ����Ŀ�ĵػ�����Դ���˴�����Ϊ��Դ
    DMA_InitStructure.DMA_BufferSize = 4;//����ָ��DMAͨ����DMA����Ĵ�С,��λΪ���ݵ�λ������Ҳ����ADCConvertedValue�Ĵ�С
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//�趨�����ַ�Ĵ����������,�˴���Ϊ���� Disable
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//�����趨�ڴ��ַ�Ĵ����������,�˴���Ϊ������Enable
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;//���ݿ��Ϊ16λ
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;//���ݿ��Ϊ16λ
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular; //������ѭ������ģʽ
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;//DMAͨ��ӵ�и����ȼ� �ֱ�4���ȼ� �͡��С��ߡ��ǳ���
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;//ʹ��DMAͨ�����ڴ浽�ڴ洫��
    DMA_Init(DMA1_Channel1, &DMA_InitStructure);//����DMA_InitStruct��ָ���Ĳ�����ʼ��DMA��ͨ��

    DMA_Cmd(DMA1_Channel1, ENABLE);//����DMAͨ��һ
}


void Yaogan_ADC_Init(void)
{	
	ADC_InitTypeDef ADC_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
	
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1|RCC_APB2Periph_GPIOA,ENABLE);
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);  //����ADC��Ƶ����6 72M/6=12,ADC���ʱ�䲻�ܳ���14M
	
	
    /*4��IO�ڵ����ã�PA1��PA2��PA3 ,PA6��*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOA, &GPIO_InitStructure);


    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_ScanConvMode = ENABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE; //����ת��
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfChannel = 4;
    ADC_Init(ADC1, &ADC_InitStructure);
    
    ADC_RegularChannelConfig(ADC1,ADC_Channel_1,1,ADC_SampleTime_239Cycles5);//PA1
	ADC_RegularChannelConfig(ADC1,ADC_Channel_2,2,ADC_SampleTime_239Cycles5);//PA2
	ADC_RegularChannelConfig(ADC1,ADC_Channel_3,3,ADC_SampleTime_239Cycles5);//PA3
	ADC_RegularChannelConfig(ADC1,ADC_Channel_6,4,ADC_SampleTime_239Cycles5);//PA6

	  
    ADC_DMACmd(ADC1, ENABLE);//����ADC��DMA֧��
    ADC_Cmd(ADC1, ENABLE);

    ADC_ResetCalibration(ADC1);
    while(ADC_GetResetCalibrationStatus(ADC1));
    ADC_StartCalibration(ADC1);
    while(ADC_GetCalibrationStatus(ADC1));

}				  

void Yaogan_Init(void)
{
	ADC_DMA_Init();
	Yaogan_ADC_Init();
	
}

volatile u16 AD_N_Value[4]={0};

//���ADCֵ
//ch:ͨ��ֵ 0~3
void Get_ADC_Data(void)   
{
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ʹ��ָ����ADC1�����ת����������	
	 
	//while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�ȴ�ת����
	AD_N_Value[0]=1000*((float)ADCConvertedValue[0]/4096.0);
	AD_N_Value[1]=1000*((float)ADCConvertedValue[1]/4096.0);
	AD_N_Value[2]=1000*((float)ADCConvertedValue[2]/4096.0);
	AD_N_Value[3]=1000*((float)ADCConvertedValue[3]/4096.0);
	
}


unsigned char Yaogan_Get_Left(void)
{
	Get_ADC_Data();
	printf("%d ,%d\r\n",AD_N_Value[1],AD_N_Value[2]);
	if(AD_N_Value[1]>700||AD_N_Value[2]>700)
		return 0;
	else
		return 1;
}

unsigned char Yaogan_Get_Right(void)
{
	Get_ADC_Data();
	if(AD_N_Value[1]<300||AD_N_Value[2]<300)
		return 0;
	else
		return 1;
}


unsigned char Yaogan_scan(void) 
{
	unsigned char out=0;
	Get_ADC_Data();
	
	//printf("%d,%d,%d,%d \r\n",AD_N_Value[0],AD_N_Value[1],AD_N_Value[2],AD_N_Value[3]);
	
	if(AD_N_Value[2]>700) out|=0x01;  //
	if(AD_N_Value[2]<300) out|=0x02;  //
	
	if(AD_N_Value[3]>700) out|=0x04;  //up
	if(AD_N_Value[3]<300) out|=0x08;  //down

	return out;
	
}


