#include "cloud.h"
#include "common.h"
static prev_menu_s prevMenuData;

static void mSelect(void);
static void itemLoader(byte);

void mCloudOpen(void)
{
	
	setMenuInfo(5, MENU_TYPE_STR, PSTR(STR_POSTMENU));
	setMenuFuncs(MENUFUNC_NEXT, mSelect, MENUFUNC_PREV, itemLoader);

	setPrevMenuOpen(&prevMenuData, mCloudOpen);

	beginAnimation2(NULL); //打开动画动画过度
}

void show_cloud_data()
{
	console_log(1,"%s",Usart2_RxBuff);
	console_log(1,"%s",&Data_buff[2]);
}

void connect_cloud_cmd(void)
{
		console_log(500,"Connecting To Cloud");
	  WiFi_send("AT+ATKCLDSTA=\"%s\",\"%s\"\r\n",DataID,DataPASS);
	  delay_ms(500);
		console_log(500,"press down");
		show_wather_data();
		cmd_finish=6;	
}