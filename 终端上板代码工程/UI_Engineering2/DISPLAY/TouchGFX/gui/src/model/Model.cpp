#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>
#include "main.h"

Model::Model() : modelListener(0)
{
}

void Model::tick()
{
}

int Model::GetHumidity()//湿度获取
{
	return UART2_temp[2];
}

int Model::GetTemperature()//温度获取
{
  return UART2_temp[3];
}

int Model::GetHeartSignal()//心率信号获取
{
	int a=0;
	a=(UART2_temp[4]<<8) | UART2_temp[5];
	return a;
}

int Model::GetHeartRate()//心率获取
{
	int a=0;
	a=(UART2_temp[6]<<8) | UART2_temp[7];
	return a;
}

int Model::GetHeartRateValid()//心率有效性
{
	return UART2_temp[8];
}

int Model::GetSPO2()//血氧获取
{
	int a=0;
	a=(UART2_temp[9]<<8) | UART2_temp[10];
	return a;
}


int Model::GetSPO2Valid()//血氧有效性
{
	return UART2_temp[11];
}

int Model::GetButton()//按键检测
{
	return UART2_temp[12];
}

int Model::IfStarted()//是否已经开机
{
	return started;
}

int Model::GetHour()//获取小时
{
	return UART2_temp[13];
}

int Model::GetMinute()//获取分钟
{
	return UART2_temp[14];
}

int Model::GetSecond()//获取秒数
{
	return UART2_temp[15];
}

int Model::GetECG()//血氧获取
{
	int a=0;
	a=(UART2_temp[16]<<8) | UART2_temp[17];
	return a;
}

int Model::GetDebugResult()//Debug结果获取
{
	return UART2_temp[18];
}

void Model::HealthDiagnose()//健康检测标志位置1
{
	UART2_Data[2]=1;
}

void Model::CancelHealthDiagnose()//健康检测标志位置0
{
	UART2_Data[2]=0;
}

void Model::NetTime()//时间更新标志位置1
{
	UART2_Data[3]=1;
}

void Model::CancelNetTime()//时间更新标志位置0
{
	UART2_Data[3]=0;
}

void Model::StateDetect()//姿态监测标志位置1
{
	UART2_Data[4]=1;
}

void Model::CancelStateDetect()//姿态监测标志位置0
{
	UART2_Data[4]=0;
}

void Model::NetDebug()//网络Debug标志位置1
{
	UART2_Data[5]=1;
}

void Model::CancelNetDebug()//网络Debug标志位置0
{
	UART2_Data[5]=0;
}

void Model::ConnectWIFI()//连接WIFI
{
	UART2_Data[6]=1;
}

void Model::CancelConnectWIFI()//取消连接WIFI
{
	UART2_Data[6]=0;
}

void Model::PostData()//上传数据
{
	UART2_Data[7]=1;
}

void Model::CancelPostData()//上传数据
{
	UART2_Data[7]=0;
}