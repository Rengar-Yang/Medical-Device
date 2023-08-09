
/*-------------------------------------------------*/
/*                                                 */
/*              操作Wifi功能的头文件               */
/*                                                 */
/*-------------------------------------------------*/

#ifndef __WIFI_H
#define __WIFI_H

#include "usart2.h"	       //包含需要的头文件
#include "sys.h"
#include "gui_log_console.h"
#include "wait_data_clock.h"

extern char TCP_flag;      //0：初始化UDP失败  1：初始化UDP成功
extern char  Data_buff[1024];
extern char RX_DAT_OK;

#define RESET_IO(x)    GPIO_WriteBit(GPIOA, GPIO_Pin_11, (BitAction)x)  //PA4控制WiFi的复位

#define WiFi_log        printf
#define WiFi_send       u2_printf           //串口2控制 WiFi
#define WiFi_RxCounter    Usart2_RxCounter    //串口2控制 WiFi
#define WiFi_RX_BUF       Usart2_RxBuff       //串口2控制 WiFi
#define WiFi_RXBUFF_SIZE  USART2_RXBUFF_SIZE  //串口2控制 WiFi

#define SSID   "CUMT_Apex"                     //路由器SSID名称
#define PASS   "88888888"                 //路由器密码

//华为云服务器的设备信息
#define MQTT_ClientID "62da3fe06b9813541d529727_0614_0_0_2022072206"
#define MQTT_UserName "62da3fe06b9813541d529727_0614"
#define MQTT_PassWord "60643747b9b556d9a1fbbe165aefab30095f2f20591c0d760431b8373cecedc9"

//华为云订阅与发布的主题
#define SET_TOPIC  "$oc/devices/62da3fe06b9813541d529727_0614/sys/messages/down"  //订阅
#define POST_TOPIC "$oc/devices/62da3fe06b9813541d529727_0614/sys/properties/report"  //发布

//原子云数据库
#define DataID   "17448873064437649896"    //数据库编号
#define DataPASS  "12345678"               //数据库密码

//本地服务器
#define Local_Server_IP  "5920r89m89.zicp.fun"
#define Local_Server_Port 21365

//自身WiFi名和密码
#define Wifi_name "Iot_Server"
#define Wifi_password "88888888"

/*-----------------------------------------------------------------------------*/
/*                              根据自己的网络环境修改                         */
/*-----------------------------------------------------------------------------*/
extern char *ServerIP;           //存放服务器IP或是域名
extern char *ServerIP2;           //存放服务器IP或是域名
extern char *ServerIP3;
extern int  ServerPort;                      //存放服务器的端口号区
/*-----------------------------------------------------------------------------*/

char WiFi_Init(void);
void WiFi_ResetIO_Init(void);
char WiFi_SendCmd(char *cmd, int timeout);
char WiFi_Reset(int timeout);
char WiFi_JoinAP(int timeout);
char WiFi_Connect_Server(int timeout);
char WiFi_Smartconfig(int timeout);
char WiFi_WaitAP(int timeout);
char WiFi_GetIP(u16 timeout);
char WiFi_Get_LinkSta(void);
char WiFi_Get_Data(char *data, char *len, char *id);
char WiFi_SendData(char id, char *databuff, int data_len, int timeout);
char WiFi_Connect_TCP(int timeout);
char WiFi_Connect_XIN_ZHI_TCP_Server(void);
//////////////////
void deep_sleep(void);
void light_sleep(void);
void connect_my_phone(void);
void connect_my_phone2(void);
void reset_wifi_cmd(void);
void get_weather_cmd(void);

void show_wather_data(void);

void show_time_data(void);
void updata_time_data(void);

extern char CMD_S[10];
#endif


