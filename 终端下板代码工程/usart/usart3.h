#ifndef __USART3_H
#define __USART3_H
#include "stdio.h"	
#include "sys.h" 
#include "string.h"     //包含需要的头文件
#include "stdarg.h"		//包含需要的头文件

#define USART3_REC_LEN  			24 	//定义最大接收字节数 24
#define USART3_TXD_LEN  			24
#define EN_USART3_RX 			1		//使能（1）/禁止（0）串口1接收
#define USART3_TXBUFF_SIZE 1
#define USART3_RXBUFF_SIZE 1
extern u32 u3_sys_time,u3_disconnect;;
extern u8 u3_recive;
extern s8  USART3_RX_BUF[USART3_REC_LEN]; //接收缓冲,最大USART3_REC_LEN个字节.末字节为换行符 
extern s8  USART3_TX_BUF[USART3_TXD_LEN]; 
extern char USART3_debug_buffer[USART3_RXBUFF_SIZE];
extern u16 USART3_RX_STA;         		//接收状态标记	
//如果想串口中断接收，请不要注释以下宏定义
extern void Usart3_init(u32 bound);
extern void u3_printf(char*,...) ;

#endif