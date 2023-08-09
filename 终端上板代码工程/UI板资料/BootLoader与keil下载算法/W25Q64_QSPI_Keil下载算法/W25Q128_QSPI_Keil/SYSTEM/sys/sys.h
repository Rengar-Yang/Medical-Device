#ifndef __SYS_H
#define __SYS_H	 
#include "stm32l431xx.h" 

//0,��֧��OS
//1,֧��OS
#define SYSTEM_SUPPORT_OS		0		//����ϵͳ�ļ����Ƿ�֧��OS
///////////////////////////////////////////////////////////////////////////////////
//����һЩ���õ��������Ͷ̹ؼ��� 
typedef uint32_t  u32;
typedef uint16_t u16;
typedef uint8_t  u8;
 
typedef volatile uint32_t  vu32;
typedef volatile uint16_t vu16;
typedef volatile uint8_t  vu8; 



//GPIO����ר�ú궨��
#define GPIO_MODE_IN    	0		//��ͨ����ģʽ
#define GPIO_MODE_OUT		1		//��ͨ���ģʽ
#define GPIO_MODE_AF		2		//AF����ģʽ
#define GPIO_MODE_AIN		3		//ģ������ģʽ

#define GPIO_SPEED_LOW		0		//GPIO�ٶ�(����,12M)
#define GPIO_SPEED_MID		1		//GPIO�ٶ�(����,60M)
#define GPIO_SPEED_FAST		2		//GPIO�ٶ�(����,85M)
#define GPIO_SPEED_HIGH		3		//GPIO�ٶ�(����,100M)  

#define GPIO_PUPD_NONE		0		//����������
#define GPIO_PUPD_PU		1		//����
#define GPIO_PUPD_PD		2		//����
#define GPIO_PUPD_RES		3		//���� 

#define GPIO_OTYPE_PP		0		//�������
#define GPIO_OTYPE_OD		1		//��©��� 


////////////////////////////////////////////////////////////////////////////////// 
void QSPI_Enable_Memmapmode(void);							//QSPI�ڴ�ӳ��ģʽʹ�ܺ���
u8 Sys_Clock_Set(u32 plln,u32 pllm,u32 pllp,u32 pllq);		//ϵͳʱ������
void Stm32_Clock_Init(u32 plln,u32 pllm,u32 pllp,u32 pllq); //ʱ�ӳ�ʼ��  
void MY_NVIC_SetVectorTable(u32 NVIC_VectTab, u32 Offset);	//����ƫ�Ƶ�ַ
void MY_NVIC_PriorityGroupConfig(u8 NVIC_Group);			//����NVIC����
void MY_NVIC_Init(u8 NVIC_PreemptionPriority,u8 NVIC_SubPriority,u8 NVIC_Channel,u8 NVIC_Group);//�����ж�

void GPIO_AF_Set(GPIO_TypeDef* GPIOx,u8 BITx,u8 AFx);		//GPIO���ù�������
void GPIO_Set(GPIO_TypeDef* GPIOx,u32 BITx,u32 MODE,u32 OTYPE,u32 OSPEED,u32 PUPD);//GPIO���ú��� 
void GPIO_Pin_Set(GPIO_TypeDef* GPIOx,u16 pinx,u8 status);	//����ĳ��IO�ڵ����״̬
u8 GPIO_Pin_Get(GPIO_TypeDef* GPIOx,u16 pinx);				//��ȡĳ��IO�ڵ�����״̬
#endif











