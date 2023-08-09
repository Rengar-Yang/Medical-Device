#include "norflash.h"
#include "qspi.h"
#include "delay.h"
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

u16 NORFLASH_TYPE=W25Q128;	//Ĭ����W25Q128
u8 NORFLASH_QPI_MODE=0;		//QSPIģʽ��־:0,SPIģʽ;1,QPIģʽ.

//4KbytesΪһ��Sector
//16������Ϊ1��Block
//W25Q64
//����Ϊ8M�ֽ�,����128��Block,2048��Sector 
													 
//��ʼ��SPI FLASH��IO��
void NORFLASH_Init(void)
{ 
	u8 temp;
	QSPI_Init();					//��ʼ��QSPI
 	NORFLASH_Qspi_Enable();			//ʹ��QSPIģʽ
	NORFLASH_TYPE=NORFLASH_ReadID();//��ȡFLASH ID.
	if(NORFLASH_TYPE == W25Q64)      //SPI W25Q128
    {
		NORFLASH_Write_Enable();	//дʹ��
		QSPI_Send_CMD(W25X_SetReadParam,0,(3<<6)|(0<<4)|(0<<2)|(3<<0),0);	//QPI,���ö�����ָ��,��ַΪ0,4�ߴ�����_8λ��ַ_�޵�ַ_4�ߴ���ָ��,�޿�����,1���ֽ�����
		temp=3<<4;					//����P4&P5=11,8��dummy clocks,104M
		QSPI_Transmit(&temp,1);		//����1���ֽ�	
    }

}  
//W25QXX����QSPIģʽ 
void NORFLASH_Qspi_Enable(void)
{
	u8 stareg2=0;
	stareg2=NORFLASH_ReadSR(2);		//�ȶ���״̬�Ĵ���2��ԭʼֵ 
	//printf("stareg2:%x\r\n",stareg2);
	if((stareg2&0X02)==0)			//QEλδʹ��
	{ 
		NORFLASH_Write_Enable();		//дʹ�� 
		stareg2|=1<<1;				//ʹ��QEλ		
		NORFLASH_Write_SR(2,stareg2);	//д״̬�Ĵ���2
	}
	QSPI_Send_CMD(W25X_EnterQPIMode,0,(0<<6)|(0<<4)|(0<<2)|(1<<0),0);	//дcommandָ��,��ַΪ0,������_8λ��ַ_�޵�ַ_���ߴ���ָ��,�޿�����,0���ֽ�����
	NORFLASH_QPI_MODE=1;				//���QSPIģʽ
}

//W25QXX�˳�QSPIģʽ 
void NORFLASH_Qspi_Disable(void)
{ 
	QSPI_Send_CMD(W25X_ExitQPIMode,0,(0<<6)|(0<<4)|(0<<2)|(3<<0),0);	//дcommandָ��,��ַΪ0,������_8λ��ַ_�޵�ַ_4�ߴ���ָ��,�޿�����,0���ֽ�����
	NORFLASH_QPI_MODE=0;				//���SPIģʽ
}

//��ȡW25QXX��״̬�Ĵ�����W25QXXһ����3��״̬�Ĵ���
//״̬�Ĵ���1��
//BIT7  6   5   4   3   2   1   0
//SPR   RV  TB BP2 BP1 BP0 WEL BUSY
//SPR:Ĭ��0,״̬�Ĵ�������λ,���WPʹ��
//TB,BP2,BP1,BP0:FLASH����д��������
//WEL:дʹ������
//BUSY:æ���λ(1,æ;0,����)
//Ĭ��:0x00
//״̬�Ĵ���2��
//BIT7  6   5   4   3   2   1   0
//SUS   CMP LB3 LB2 LB1 (R) QE  SRP1
//״̬�Ĵ���3��
//BIT7      6    5    4   3   2   1   0
//HOLD/RST  DRV1 DRV0 (R) (R) WPS ADP ADS
//regno:״̬�Ĵ����ţ���:1~3
//����ֵ:״̬�Ĵ���ֵ
u8 NORFLASH_ReadSR(u8 regno)   
{  
	u8 byte=0,command=0; 
    switch(regno)
    {
        case 1:
            command=W25X_ReadStatusReg1;    //��״̬�Ĵ���1ָ��
            break;
        case 2:
            command=W25X_ReadStatusReg2;    //��״̬�Ĵ���2ָ��
            break;
        case 3:
            command=W25X_ReadStatusReg3;    //��״̬�Ĵ���3ָ��
            break;
        default:
            command=W25X_ReadStatusReg1;    
            break;
    }   
	if(NORFLASH_QPI_MODE)QSPI_Send_CMD(command,0,(3<<6)|(0<<4)|(0<<2)|(3<<0),0);//QPI,дcommandָ��,��ַΪ0,4�ߴ�����_8λ��ַ_�޵�ַ_4�ߴ���ָ��,�޿�����,1���ֽ�����
	else QSPI_Send_CMD(command,0,(1<<6)|(0<<4)|(0<<2)|(1<<0),0);				//SPI,дcommandָ��,��ַΪ0,���ߴ�����_8λ��ַ_�޵�ַ_���ߴ���ָ��,�޿�����,1���ֽ�����
	QSPI_Receive(&byte,1);	        
	return byte;   
}   

//дW25QXX״̬�Ĵ���
void NORFLASH_Write_SR(u8 regno,u8 sr)   
{   
    u8 command=0;
    switch(regno)
    {
        case 1:
            command=W25X_WriteStatusReg1;    //д״̬�Ĵ���1ָ��
            break;
        case 2:
            command=W25X_WriteStatusReg2;    //д״̬�Ĵ���2ָ��
            break;
        case 3:
            command=W25X_WriteStatusReg3;    //д״̬�Ĵ���3ָ��
            break;
        default:
            command=W25X_WriteStatusReg1;    
            break;
    }   
	if(NORFLASH_QPI_MODE)QSPI_Send_CMD(command,0,(3<<6)|(0<<4)|(0<<2)|(3<<0),0);//QPI,дcommandָ��,��ַΪ0,4�ߴ�����_8λ��ַ_�޵�ַ_4�ߴ���ָ��,�޿�����,1���ֽ�����
	else QSPI_Send_CMD(command,0,(1<<6)|(0<<4)|(0<<2)|(1<<0),0);				//SPI,дcommandָ��,��ַΪ0,���ߴ�����_8λ��ַ_�޵�ַ_���ߴ���ָ��,�޿�����,1���ֽ�����
	QSPI_Transmit(&sr,1);	         	      
}  

//W25QXXдʹ��	
//��S1�Ĵ�����WEL��λ   
void NORFLASH_Write_Enable(void)   
{
	if(NORFLASH_QPI_MODE)QSPI_Send_CMD(W25X_WriteEnable,0,(0<<6)|(0<<4)|(0<<2)|(3<<0),0);	//QPI,дʹ��ָ��,��ַΪ0,������_8λ��ַ_�޵�ַ_4�ߴ���ָ��,�޿�����,0���ֽ�����
	else QSPI_Send_CMD(W25X_WriteEnable,0,(0<<6)|(0<<4)|(0<<2)|(1<<0),0);					//SPI,дʹ��ָ��,��ַΪ0,������_8λ��ַ_�޵�ַ_���ߴ���ָ��,�޿�����,0���ֽ�����
} 

//W25QXXд��ֹ	
//��WEL����  
void NORFLASH_Write_Disable(void)   
{  
	if(NORFLASH_QPI_MODE)QSPI_Send_CMD(W25X_WriteDisable,0,(0<<6)|(0<<4)|(0<<2)|(3<<0),0);	//QPI,д��ָֹ��,��ַΪ0,������_8λ��ַ_�޵�ַ_4�ߴ���ָ��,�޿�����,0���ֽ�����
	else QSPI_Send_CMD(W25X_WriteDisable,0,(0<<6)|(0<<4)|(0<<2)|(1<<0),0);					//SPI,д��ָֹ��,��ַΪ0,������_8λ��ַ_�޵�ַ_���ߴ���ָ��,�޿�����,0���ֽ����� 
} 

//����ֵ����:				   
//0XEF13,��ʾоƬ�ͺ�ΪW25Q80  
//0XEF14,��ʾоƬ�ͺ�ΪW25Q16    
//0XEF15,��ʾоƬ�ͺ�ΪW25Q32  
//0XEF16,��ʾоƬ�ͺ�ΪW25Q64 
//0XEF17,��ʾоƬ�ͺ�ΪW25Q128 	  
//0XEF18,��ʾоƬ�ͺ�ΪW25Q256
u16 NORFLASH_ReadID(void)
{
	u8 temp[2];
	u16 deviceid;
	if(NORFLASH_QPI_MODE)QSPI_Send_CMD(W25X_ManufactDeviceID,0,(3<<6)|(2<<4)|(3<<2)|(3<<0),0);	//QPI,��id,��ַΪ0,4�ߴ�������_24λ��ַ_4�ߴ����ַ_4�ߴ���ָ��,�޿�����,2���ֽ�����
	else QSPI_Send_CMD(W25X_ManufactDeviceID,0,(1<<6)|(2<<4)|(1<<2)|(1<<0),0);					//SPI,��id,��ַΪ0,���ߴ�������_24λ��ַ_���ߴ����ַ_���ߴ���ָ��,�޿�����,2���ֽ�����
	QSPI_Receive(temp,2);
	deviceid=(temp[0]<<8)|temp[1];
	return deviceid;
}    

//��ȡSPI FLASH,��֧��QPIģʽ  
//��ָ����ַ��ʼ��ȡָ�����ȵ�����
//pBuffer:���ݴ洢��
//ReadAddr:��ʼ��ȡ�ĵ�ַ(���32bit)
//NumByteToRead:Ҫ��ȡ���ֽ���(���65535)
void NORFLASH_Read(u8* pBuffer,u32 ReadAddr,u16 NumByteToRead)   
{ 
	QSPI_Send_CMD(W25X_FastReadData,ReadAddr,(3<<6)|(2<<4)|(3<<2)|(3<<0),8);	//QPI,���ٶ�����,��ַΪReadAddr,4�ߴ�������_24λ��ַ_4�ߴ����ַ_4�ߴ���ָ��,8������,NumByteToRead������
	QSPI_Receive(pBuffer,NumByteToRead); 
}  


//SPI��һҳ(0~65535)��д������256���ֽڵ�����
//��ָ����ַ��ʼд�����256�ֽڵ�����
//pBuffer:���ݴ洢��
//WriteAddr:��ʼд��ĵ�ַ(���32bit)
//NumByteToWrite:Ҫд����ֽ���(���256),������Ӧ�ó�����ҳ��ʣ���ֽ���!!!	 
void NORFLASH_Write_Page(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite)
{
	NORFLASH_Write_Enable();					//дʹ��
	QSPI_Send_CMD(W25X_PageProgram,WriteAddr,(3<<6)|(2<<4)|(3<<2)|(3<<0),0);	//QPI,ҳдָ��,��ַΪWriteAddr,4�ߴ�������_24λ��ַ_4�ߴ����ַ_4�ߴ���ָ��,�޿�����,NumByteToWrite������
	QSPI_Transmit(pBuffer,NumByteToWrite);	         	      
	NORFLASH_Wait_Busy();					   //�ȴ�д�����
} 

//�޼���дSPI FLASH 
//����ȷ����д�ĵ�ַ��Χ�ڵ�����ȫ��Ϊ0XFF,�����ڷ�0XFF��д������ݽ�ʧ��!
//�����Զ���ҳ���� 
//��ָ����ַ��ʼд��ָ�����ȵ�����,����Ҫȷ����ַ��Խ��!
//pBuffer:���ݴ洢��
//WriteAddr:��ʼд��ĵ�ַ(���32bit)
//NumByteToWrite:Ҫд����ֽ���(���65535)
//CHECK OK
void NORFLASH_Write_NoCheck(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite)   
{ 			 		 
	u16 pageremain;	   
	pageremain=256-WriteAddr%256; //��ҳʣ����ֽ���		 	    
	if(NumByteToWrite<=pageremain)pageremain=NumByteToWrite;//������256���ֽ�
	while(1)
	{	   
		NORFLASH_Write_Page(pBuffer,WriteAddr,pageremain);
		if(NumByteToWrite==pageremain)break;//д�������
	 	else //NumByteToWrite>pageremain
		{
			pBuffer+=pageremain;
			WriteAddr+=pageremain;	

			NumByteToWrite-=pageremain;			  //��ȥ�Ѿ�д���˵��ֽ���
			if(NumByteToWrite>256)pageremain=256; //һ�ο���д��256���ֽ�
			else pageremain=NumByteToWrite; 	  //����256���ֽ���
		}
	}   
} 

//дSPI FLASH  
//��ָ����ַ��ʼд��ָ�����ȵ�����
//�ú�������������!
//pBuffer:���ݴ洢��
//WriteAddr:��ʼд��ĵ�ַ(���32bit)						
//NumByteToWrite:Ҫд����ֽ���(���65535)   
u8 NORFLASH_BUFFER[4096];		 
void NORFLASH_Write(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite)   
{ 
	u32 secpos;
	u16 secoff;
	u16 secremain;	   
 	u16 i;    
	u8 * NORFLASH_BUF;	  
   	NORFLASH_BUF=NORFLASH_BUFFER;	     
 	secpos=WriteAddr/4096;//������ַ  
	secoff=WriteAddr%4096;//�������ڵ�ƫ��
	secremain=4096-secoff;//����ʣ��ռ��С   
 	//printf("ad:%X,nb:%X\r\n",WriteAddr,NumByteToWrite);//������
 	if(NumByteToWrite<=secremain)secremain=NumByteToWrite;//������4096���ֽ�
	while(1) 
	{	
		NORFLASH_Read(NORFLASH_BUF,secpos*4096,4096);//������������������
		for(i=0;i<secremain;i++)//У������
		{
			if(NORFLASH_BUF[secoff+i]!=0XFF)break;//��Ҫ����  	  
		}
		if(i<secremain)//��Ҫ����
		{
			NORFLASH_Erase_Sector(secpos);//�����������
			for(i=0;i<secremain;i++)	   //����
			{
				NORFLASH_BUF[i+secoff]=pBuffer[i];	  
			}
			NORFLASH_Write_NoCheck(NORFLASH_BUF,secpos*4096,4096);	//д����������   
		}else NORFLASH_Write_NoCheck(pBuffer,WriteAddr,secremain);//д�Ѿ������˵�,ֱ��д������ʣ������. 				   
		if(NumByteToWrite==secremain)break;//д�������
		else//д��δ����
		{
			secpos++;//������ַ��1
			secoff=0;//ƫ��λ��Ϊ0 	 

		   	pBuffer+=secremain;  //ָ��ƫ��
			WriteAddr+=secremain;//д��ַƫ��	   
		   	NumByteToWrite-=secremain;				//�ֽ����ݼ�
			if(NumByteToWrite>4096)secremain=4096;	//��һ����������д����
			else secremain=NumByteToWrite;			//��һ����������д����
		}	 
	};	 
}

//��������оƬ		  
//�ȴ�ʱ�䳬��...
void NORFLASH_Erase_Chip(void)   
{                                   
    NORFLASH_Write_Enable();					//SET WEL 
    NORFLASH_Wait_Busy();   
	QSPI_Send_CMD(W25X_ChipErase,0,(0<<6)|(0<<4)|(0<<2)|(3<<0),0);//QPI,дȫƬ����ָ��,��ַΪ0,������_8λ��ַ_�޵�ַ_4�ߴ���ָ��,�޿�����,0���ֽ�����
	NORFLASH_Wait_Busy();						//�ȴ�оƬ��������
} 

//����һ������
//Dst_Addr:������ַ ����ʵ����������
//����һ������������ʱ��:150ms
void NORFLASH_Erase_Sector(u32 Dst_Addr)   
{  
	 
 	//printf("fe:%x\r\n",Dst_Addr);		//����falsh�������,������  	  
 	Dst_Addr*=4096;
    NORFLASH_Write_Enable();			//SET WEL 	 
    NORFLASH_Wait_Busy();  
	QSPI_Send_CMD(W25X_SectorErase,Dst_Addr,(0<<6)|(2<<4)|(3<<2)|(3<<0),0);//QPI,д��������ָ��,��ַΪ0,������_24λ��ַ_4�ߴ����ַ_4�ߴ���ָ��,�޿�����,0���ֽ�����
    NORFLASH_Wait_Busy();				//�ȴ��������
}

//�ȴ�����
void NORFLASH_Wait_Busy(void)   
{   
	while((NORFLASH_ReadSR(1)&0x01)==0x01);	// �ȴ�BUSYλ���
}   
























