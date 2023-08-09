#ifndef __USART3_H
#define __USART3_H
#include "stdio.h"	
#include "sys.h" 
#include "string.h"     //������Ҫ��ͷ�ļ�
#include "stdarg.h"		//������Ҫ��ͷ�ļ�

#define USART3_REC_LEN  			24 	//�����������ֽ��� 24
#define USART3_TXD_LEN  			24
#define EN_USART3_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����
#define USART3_TXBUFF_SIZE 1
#define USART3_RXBUFF_SIZE 1
extern u32 u3_sys_time,u3_disconnect;;
extern u8 u3_recive;
extern s8  USART3_RX_BUF[USART3_REC_LEN]; //���ջ���,���USART3_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern s8  USART3_TX_BUF[USART3_TXD_LEN]; 
extern char USART3_debug_buffer[USART3_RXBUFF_SIZE];
extern u16 USART3_RX_STA;         		//����״̬���	
//����봮���жϽ��գ��벻Ҫע�����º궨��
extern void Usart3_init(u32 bound);
extern void u3_printf(char*,...) ;

#endif