#ifndef __ADC_H
#define	__ADC_H


#include "stm32f10x.h"

// ע�⣺����ADC�ɼ���IO����û�и��ã�����ɼ���ѹ����Ӱ��
/********************ADC1����ͨ�������ţ�����**************************/
#define    ADCx                          ADC1
#define    ADC_APBxClock_FUN             RCC_APB2PeriphClockCmd
#define    ADC_CLK                       RCC_APB2Periph_ADC1

#define    ADC_GPIO_APBxClock_FUN        RCC_APB2PeriphClockCmd
#define    ADC_GPIO_CLK                  RCC_APB2Periph_GPIOA  
#define    ADC_PORT                      GPIOA

// PA4-ͨ��4 ����IO
#define    ADC_PIN                       GPIO_Pin_4
#define    ADC_CHANNEL                   ADC_Channel_4
#define    ADC_DMA_CHANNEL               DMA1_Channel1

void ADCx_Init(void);
extern void TDS_Value_Conversion();
extern u16 TDS_value;
extern float TDS_voltage;
extern __IO uint16_t ADC_ConvertedValue;
#endif /* __ADC_H */

