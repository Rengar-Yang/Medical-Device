#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "sys.h" 
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32������
//����1��ʼ��		   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/8/18
//�汾��V1.5
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved
//********************************************************************************
//V1.3�޸�˵�� 
//֧����Ӧ��ͬƵ���µĴ��ڲ���������.
//�����˶�printf��֧��
//�����˴��ڽ��������.
//������printf��һ���ַ���ʧ��bug
//V1.4�޸�˵��
//1,�޸Ĵ��ڳ�ʼ��IO��bug
//2,�޸���USART1_RX_STA,ʹ�ô����������ֽ���Ϊ2��14�η�
//3,������USART1_REC_LEN,���ڶ��崮�����������յ��ֽ���(������2��14�η�)
//4,�޸���EN_USART1_RX��ʹ�ܷ�ʽ
//V1.5�޸�˵��
//1,�����˶�UCOSII��֧��
#define USART1_REC_LEN  			22  	//�����������ֽ��� 22
#define USART1_TXD_LEN  			22
#define EN_USART1_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����
#define USART1_TXBUFF_SIZE 200
#define USART1_RXBUFF_SIZE 200
extern u32 u1_sys_time,u1_disconnect;;
extern u8 u1_recive;
extern s8  USART1_RX_BUF[USART1_REC_LEN]; //���ջ���,���USART1_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern s16  USART1_TX_BUF[USART1_TXD_LEN]; 
extern char usart1_debug_buffer[USART1_RXBUFF_SIZE];
extern u16 USART1_RX_STA;         		//����״̬���	
//����봮���жϽ��գ��벻Ҫע�����º궨��
void Usart1_init(u32 bound);
#endif


