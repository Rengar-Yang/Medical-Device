#ifndef __DHT11_H
#define __DHT11_H   
#include "sys.h"
 
//IO方向设置
#define DHT11_IO_IN()  {GPIOB->CRH&=0XFF0FFFFF;GPIOB->CRH|=8<<20;}
#define DHT11_IO_OUT() {GPIOB->CRH&=0XFF0FFFFF;GPIOB->CRH|=3<<20;}
 
//IO操作函数											   
#define	DHT11_DQ_OUT PBout(13) 
#define	DHT11_DQ_IN  PBin(13)  
 
 
u8 DHT11_Init(void);
u8 DHT11_Read_Data(u8 *temp,u8 *humi);
u8 DHT11_Read_Byte(void);
u8 DHT11_Read_Bit(void);
void DHT11_Rst(void);
u8 DHT11_Check(void);
 
#endif