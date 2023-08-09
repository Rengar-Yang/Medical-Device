#ifndef __NORFLASH_H
#define __NORFLASH_H

#ifdef __cplusplus
extern "C"{
#endif // __cplusplus
	
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32H7������
//NOR FLASH(W25QXX) QPIģʽ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2019/5/4
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	


//W25Xϵ��/Qϵ��оƬ�б�	   
//W25Q80  ID  0XEF13
//W25Q16  ID  0XEF14
//W25Q32  ID  0XEF15
//W25Q64  ID  0XEF16	
//W25Q128 ID  0XEF17	
//W25Q256 ID  0XEF18
#define W25Q80 	0XEF13 	
#define W25Q16 	0XEF14
#define W25Q32 	0XEF15
#define W25Q64 	0XEF16
#define W25Q128	0XEF17
#define W25Q256 0XEF18

#define EX_FLASH_START_ADDR	0x90000000
#define EX_FLASH_SIZE				0x00800000
#define EX_FLASH_END_ADDR		(EX_FLASH_START_ADDR+EX_FLASH_SIZE)

extern u16 NORFLASH_TYPE;					//����W25QXXоƬ�ͺ�		   
 
////////////////////////////////////////////////////////////////////////////////// 
//ָ���
#define W25X_WriteEnable		0x06 
#define W25X_WriteDisable		0x04 
#define W25X_ReadStatusReg1		0x05 
#define W25X_ReadStatusReg2		0x35 
#define W25X_ReadStatusReg3		0x15 
#define W25X_WriteStatusReg1    0x01 
#define W25X_WriteStatusReg2    0x31 
#define W25X_WriteStatusReg3    0x11 
#define W25X_ReadData			0x03 
#define W25X_FastReadData		0x0B 
#define W25X_FastReadDual		0x3B 
#define W25X_PageProgram		0x02 
#define W25X_BlockErase			0xD8 
#define W25X_SectorErase		0x20 
#define W25X_ChipErase			0xC7 
#define W25X_PowerDown			0xB9 
#define W25X_ReleasePowerDown	0xAB 
#define W25X_DeviceID			0xAB 
#define W25X_ManufactDeviceID	0x90 
#define W25X_JedecDeviceID		0x9F 
#define W25X_Enable4ByteAddr    0xB7
#define W25X_Exit4ByteAddr      0xE9
#define W25X_SetReadParam		0xC0 
#define W25X_EnterQPIMode       0x38
#define W25X_ExitQPIMode        0xFF

void NORFLASH_Init(void);				//��ʼ��W25QXX
void NORFLASH_Qspi_Enable(void);		//ʹ��QSPIģʽ
void NORFLASH_Qspi_Disable(void);		//�ر�QSPIģʽ
u16  NORFLASH_ReadID(void);				//��ȡFLASH ID
u8 NORFLASH_ReadSR(u8 regno);			//��ȡ״̬�Ĵ��� 
void NORFLASH_Write_SR(u8 regno,u8 sr);	//д״̬�Ĵ���
void NORFLASH_Write_Enable(void);  		//дʹ�� 
void NORFLASH_Write_Disable(void);		//д����
void NORFLASH_Write_NoCheck(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite);	//дflash,��У��
void NORFLASH_Read(u8* pBuffer,u32 ReadAddr,u16 NumByteToRead);   			//��ȡflash
void NORFLASH_Write(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite);			//д��flash
void NORFLASH_Erase_Chip(void);    	  		//��Ƭ����
void NORFLASH_Erase_Sector(u32 Dst_Addr);	//��������
void NORFLASH_Wait_Busy(void);           	//�ȴ�����


//void DataReader_WaitForReceiveDone(void);
//void DataReader_ReadData(uint32_t address24, uint8_t* buffer, uint32_t length);
//void DataReader_StartDMAReadData(uint32_t address24, uint8_t* buffer, uint32_t length);

//void DataReader_StartDMAReadData(uint32_t address24, uint8_t* buffer, uint32_t length);
#ifdef __cplusplus
}
#endif // __cplusplus

#endif















