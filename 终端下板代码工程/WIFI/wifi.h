
/*-------------------------------------------------*/
/*                                                 */
/*              ����Wifi���ܵ�ͷ�ļ�               */
/*                                                 */
/*-------------------------------------------------*/

#ifndef __WIFI_H
#define __WIFI_H

#include "usart2.h"	       //������Ҫ��ͷ�ļ�
#include "sys.h"
#include "gui_log_console.h"
#include "wait_data_clock.h"

extern char TCP_flag;      //0����ʼ��UDPʧ��  1����ʼ��UDP�ɹ�
extern char  Data_buff[1024];
extern char RX_DAT_OK;

#define RESET_IO(x)    GPIO_WriteBit(GPIOA, GPIO_Pin_11, (BitAction)x)  //PA4����WiFi�ĸ�λ

#define WiFi_log        printf
#define WiFi_send       u2_printf           //����2���� WiFi
#define WiFi_RxCounter    Usart2_RxCounter    //����2���� WiFi
#define WiFi_RX_BUF       Usart2_RxBuff       //����2���� WiFi
#define WiFi_RXBUFF_SIZE  USART2_RXBUFF_SIZE  //����2���� WiFi

#define SSID   "CUMT_Apex"                     //·����SSID����
#define PASS   "88888888"                 //·��������

//��Ϊ�Ʒ��������豸��Ϣ
#define MQTT_ClientID "62da3fe06b9813541d529727_0614_0_0_2022072206"
#define MQTT_UserName "62da3fe06b9813541d529727_0614"
#define MQTT_PassWord "60643747b9b556d9a1fbbe165aefab30095f2f20591c0d760431b8373cecedc9"

//��Ϊ�ƶ����뷢��������
#define SET_TOPIC  "$oc/devices/62da3fe06b9813541d529727_0614/sys/messages/down"  //����
#define POST_TOPIC "$oc/devices/62da3fe06b9813541d529727_0614/sys/properties/report"  //����

//ԭ�������ݿ�
#define DataID   "17448873064437649896"    //���ݿ���
#define DataPASS  "12345678"               //���ݿ�����

//���ط�����
#define Local_Server_IP  "5920r89m89.zicp.fun"
#define Local_Server_Port 21365

//����WiFi��������
#define Wifi_name "Iot_Server"
#define Wifi_password "88888888"

/*-----------------------------------------------------------------------------*/
/*                              �����Լ������绷���޸�                         */
/*-----------------------------------------------------------------------------*/
extern char *ServerIP;           //��ŷ�����IP��������
extern char *ServerIP2;           //��ŷ�����IP��������
extern char *ServerIP3;
extern int  ServerPort;                      //��ŷ������Ķ˿ں���
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


