#include "qspi.h"


//等待状态标志
//flag:需要等待的标志位
//sta:需要等待的状态
//wtime:等待时间
//返回值:0,等待成功.
//	     1,等待失败.
u8 QSPI_Wait_Flag(u32 flag,u8 sta,u32 wtime)
{
	u8 flagsta=0;
	while(wtime)
	{
		flagsta=(QUADSPI->SR&flag)?1:0; 
		if(flagsta==sta)break;
		wtime--;
	}
	if(wtime)return 0;
	else return 1;
}

//初始化QSPI接口
//返回值:0,成功;
//       1,失败;
void QSPI_Init(void)
{

}

//QSPI发送命令
//cmd:要发送的指令
//addr:发送到的目的地址
//mode:模式,详细位定义如下:
//	mode[1:0]:指令模式;00,无指令;01,单线传输指令;10,双线传输指令;11,四线传输指令.
//	mode[3:2]:地址模式;00,无地址;01,单线传输地址;10,双线传输地址;11,四线传输地址.
//	mode[5:4]:地址长度;00,8位地址;01,16位地址;10,24位地址;11,32位地址.
//	mode[7:6]:数据模式;00,无数据;01,单线传输数据;10,双线传输数据;11,四线传输数据.
//dmcycle:空指令周期数
void QSPI_Send_CMD(u8 cmd,u32 addr,u8 mode,u8 dmcycle)
{
	u32 tempreg=0;	
	u8 status;
	if(QSPI_Wait_Flag(1<<5,0,0XFFFF)==0)	//等待BUSY空闲
	{
		tempreg=0<<31;						//禁止DDR模式
		tempreg|=0<<28;						//每次都发送指令
		tempreg|=0<<26;						//间接写模式
		tempreg|=((u32)mode>>6)<<24;		//设置数据模式
		tempreg|=(u32)dmcycle<<18;			//设置空指令周期数
		tempreg|=((u32)(mode>>4)&0X03)<<12;	//设置地址长度
		tempreg|=((u32)(mode>>2)&0X03)<<10;	//设置地址模式
		tempreg|=((u32)(mode>>0)&0X03)<<8;	//设置指令模式
		tempreg|=cmd;						//设置指令
		QUADSPI->CCR=tempreg;				//设置CCR寄存器
		if(mode&0X0C)						//有指令+地址要发送
		{
			QUADSPI->AR=addr;				//设置地址寄存器
		} 
		if((mode&0XC0)==0)					//无数据传输,等待指令发送完成
		{
			status=QSPI_Wait_Flag(1<<1,1,0XFFFF);//等待TCF,即传输完成
			if(status==0)
			{
				QUADSPI->FCR|=1<<1;			//清除TCF标志位 
			}
		}
	}	
}

//QSPI接收指定长度的数据
//buf:接收数据缓冲区首地址
//datalen:要传输的数据长度
//返回值:0,正常
//    其他,错误代码
u8 QSPI_Receive(u8* buf,u32 datalen)
{
	u32 tempreg=QUADSPI->CCR;
	u32 addrreg=QUADSPI->AR; 	
	u8 status;
	vu32 *data_reg=&QUADSPI->DR;
	QUADSPI->DLR=datalen-1;					//设置数据传输长度
	tempreg&=~(3<<26);						//清除FMODE原来的设置
	tempreg|=1<<26;							//设置FMODE为间接读取模式
	QUADSPI->FCR|=1<<1;						//清除TCF标志位
	QUADSPI->CCR=tempreg;					//回写CCR寄存器
	QUADSPI->AR=addrreg;					//回写AR寄存器,触发传输
	while(datalen)
	{
		status=QSPI_Wait_Flag(3<<1,1,0XFFFF);//等到FTF和TCF,即接收到了数据
		if(status==0)						//等待成功
		{
			*buf++=*(vu8 *)data_reg;
			datalen--;
		}else break;
	}
	if(status==0)
	{
		QUADSPI->CR|=1<<2;							//终止传输 
		status=QSPI_Wait_Flag(1<<1,1,0XFFFF);		//等待TCF,即数据传输完成
		if(status==0)
		{
			QUADSPI->FCR|=1<<1;						//清除TCF标志位 
			status=QSPI_Wait_Flag(1<<5,0,0XFFFF);	//等待BUSY位清零
		}
	}
	return status;
} 

//QSPI发送指定长度的数据
//buf:发送数据缓冲区首地址
//datalen:要传输的数据长度
//返回值:0,正常
//    其他,错误代码
u8 QSPI_Transmit(u8* buf,u32 datalen)
{
	u32 tempreg=QUADSPI->CCR;
	u32 addrreg=QUADSPI->AR; 
	u8 status;
	vu32 *data_reg=&QUADSPI->DR;
	QUADSPI->DLR=datalen-1;					//设置数据传输长度
	tempreg&=~(3<<26);						//清除FMODE原来的设置
	tempreg|=0<<26;							//设置FMODE为间接写入模式
	QUADSPI->FCR|=1<<1;						//清除TCF标志位
	QUADSPI->CCR=tempreg;					//回写CCR寄存器 
	while(datalen)
	{
		status=QSPI_Wait_Flag(1<<2,1,0XFFFF);//等到FTF
		if(status!=0)						//等待成功
		{
			break;
		}
		*(vu8 *)data_reg=*buf++;
		datalen--;
	}
	if(status==0)
	{
		QUADSPI->CR|=1<<2;							//终止传输 
		status=QSPI_Wait_Flag(1<<1,1,0XFFFF);		//等待TCF,即数据传输完成
		if(status==0)
		{
			QUADSPI->FCR|=1<<1;						//清除TCF标志位 
			status=QSPI_Wait_Flag(1<<5,0,0XFFFF);	//等待BUSY位清零
		}
	}
	return status;
}




















