#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>
#include "main.h"

Model::Model() : modelListener(0)
{
}

void Model::tick()
{
}

int Model::GetHumidity()//ʪ�Ȼ�ȡ
{
	return UART2_temp[2];
}

int Model::GetTemperature()//�¶Ȼ�ȡ
{
  return UART2_temp[3];
}

int Model::GetHeartSignal()//�����źŻ�ȡ
{
	int a=0;
	a=(UART2_temp[4]<<8) | UART2_temp[5];
	return a;
}

int Model::GetHeartRate()//���ʻ�ȡ
{
	int a=0;
	a=(UART2_temp[6]<<8) | UART2_temp[7];
	return a;
}

int Model::GetHeartRateValid()//������Ч��
{
	return UART2_temp[8];
}

int Model::GetSPO2()//Ѫ����ȡ
{
	int a=0;
	a=(UART2_temp[9]<<8) | UART2_temp[10];
	return a;
}


int Model::GetSPO2Valid()//Ѫ����Ч��
{
	return UART2_temp[11];
}

int Model::GetButton()//�������
{
	return UART2_temp[12];
}

int Model::IfStarted()//�Ƿ��Ѿ�����
{
	return started;
}

int Model::GetHour()//��ȡСʱ
{
	return UART2_temp[13];
}

int Model::GetMinute()//��ȡ����
{
	return UART2_temp[14];
}

int Model::GetSecond()//��ȡ����
{
	return UART2_temp[15];
}

int Model::GetECG()//Ѫ����ȡ
{
	int a=0;
	a=(UART2_temp[16]<<8) | UART2_temp[17];
	return a;
}

int Model::GetDebugResult()//Debug�����ȡ
{
	return UART2_temp[18];
}

void Model::HealthDiagnose()//��������־λ��1
{
	UART2_Data[2]=1;
}

void Model::CancelHealthDiagnose()//��������־λ��0
{
	UART2_Data[2]=0;
}

void Model::NetTime()//ʱ����±�־λ��1
{
	UART2_Data[3]=1;
}

void Model::CancelNetTime()//ʱ����±�־λ��0
{
	UART2_Data[3]=0;
}

void Model::StateDetect()//��̬����־λ��1
{
	UART2_Data[4]=1;
}

void Model::CancelStateDetect()//��̬����־λ��0
{
	UART2_Data[4]=0;
}

void Model::NetDebug()//����Debug��־λ��1
{
	UART2_Data[5]=1;
}

void Model::CancelNetDebug()//����Debug��־λ��0
{
	UART2_Data[5]=0;
}

void Model::ConnectWIFI()//����WIFI
{
	UART2_Data[6]=1;
}

void Model::CancelConnectWIFI()//ȡ������WIFI
{
	UART2_Data[6]=0;
}

void Model::PostData()//�ϴ�����
{
	UART2_Data[7]=1;
}

void Model::CancelPostData()//�ϴ�����
{
	UART2_Data[7]=0;
}