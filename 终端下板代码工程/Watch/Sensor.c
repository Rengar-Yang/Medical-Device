#include "Sensor.h"
#include "common.h"
static prev_menu_s prevMenuData;

//bool keep_on=0;
static void mSelect(void);
static void itemLoader(byte);
static void setSensorUI(void);
void mSensorOpen()
{
	setMenuInfo(3, MENU_TYPE_ICON, PSTR(STR_SENSORMENU));
	setMenuFuncs(MENUFUNC_NEXT, mSelect, MENUFUNC_PREV, itemLoader);

	setPrevMenuOpen(&prevMenuData, mSensorOpen);

	beginAnimation2(NULL); //打开动画动画过度
}

//void mCloudOpen(void)
//{

//}

void show_cloud_data()
{
	console_log(1,"%s",Usart2_RxBuff);
	console_log(1,"%s",&Data_buff[2]);
	console_log(100,"Connected！");
}

void connect_cloud_cmd(void)
{
		console_log(500,"Connecting Cloud");
	  WiFi_send("AT+ATKCLDSTA=\"%s\",\"%s\"\r\n",DataID,DataPASS);
	  delay_ms(500);
		console_log(500,"press down");
		show_wather_data();
}

void connect_HWcloud_cmd(void)
{
		console_log(500,"Connecting Server");
////	  WiFi_send("AT+ATKCLDSTA=\"%s\",\"%s\"\r\n",DataID,DataPASS);
////	  delay_ms(500);
//	  WiFi_send("AT+MQTTUSERCFG=0,1,\"NULL\",\"%s\",\"%s\",0,0,""\r\n",MQTT_UserName,MQTT_PassWord);
//	  delay_ms(500);
//	  WiFi_send("AT+MQTTCLIENTID=0,\"%s\"\r\n",MQTT_ClientID);
//	  delay_ms(500);
//	  WiFi_send("AT+MQTTCONN=0,\"a160d6ba32.iot-mqtts.cn-north-4.myhuaweicloud.com\",1883,1\r\n");
//		console_log(1,"%s",Usart2_RxBuff);
//  	console_log(1,"%s",&Data_buff[2]);
	
	  WiFi_send("AT+CIPMUX=0\r\n");
	  delay_ms(500);
	  WiFi_send("AT+CIPMODE=1\r\n");
	  delay_ms(500);
	  WiFi_send("AT+CIPSTART=\"TCP\",\"%s\",%d\r\n",Local_Server_IP,Local_Server_Port);
	  delay_ms(1000);
	  WiFi_send("AT+CIPSEND\r\n");
	  delay_ms(500);
		console_log(1,"%s",Usart2_RxBuff);
  	console_log(1,"%s",&Data_buff[2]);
		
}



static void itemLoader(byte num)
{
	//mPostOpen();
	  setMenuOption_P(0, PSTR(STR_POSTTEMP), menu_thermometer, mPostOpen);
	  setMenuOption_P(1, PSTR(STR_CLOUD), menu_cloud, connect_cloud_cmd);
//		setMenuOption_P(2, PSTR(STR_SLEEP), menu_sleep, mHWPostOpen);    //这里有bug！！！  可以再增加一个图标就可以解决
	  setMenuOption_P(2, PSTR(STR_SERVER), menu_post, connect_HWcloud_cmd);
//	  setMenuOption_P(3, PSTR(STR_SERVER2), menu_display, mServerOpen);
//		setMenuOption_P(4, PSTR(STR_DIAGNOSTICS), menu_diagnostic, mDiagOpen);
	addBackOption();
}
static void mSelect()
{
	setPrevMenuExit(&prevMenuData);
	doAction(exitSelected());
}