#ifndef __QSPI_H
#define __QSPI_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32H7������
//QSPI ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2019/5/4
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	 


u8 QSPI_Wait_Flag(u32 flag,u8 sta,u32 wtime);					//QSPI�ȴ�ĳ��״̬
u8 QSPI_Init(void);												//��ʼ��QSPI
void QSPI_Send_CMD(u8 cmd,u32 addr,u8 mode,u8 dmcycle);			//QSPI��������
u8 QSPI_Receive(u8* buf,u32 datalen);							//QSPI��������
u8 QSPI_Transmit(u8* buf,u32 datalen);							//QSPI��������

#endif

