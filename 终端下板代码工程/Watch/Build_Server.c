#include "Build_Server.h"
#include "common.h"
static prev_menu_s prevMenuData;
char Build_server=0;
int server_begin=0;
//bool keep_on=0;
static void itemLoader(byte);

static bool btnExit()
{
//	animation_start(display_load, ANIM_MOVE_OFF);
//	keep_on=false;  //如果在draw里一直刷新变量，变量在这里关闭不了，因为会draw线程会再次覆盖
//	setMenuOption_P(menuData.optionCount - 1, menuBack, menu_exit, back);
	back();
	Build_server=0;
	server_begin=0;
	WiFi_send("AT+CIPSERVER=0,%d\r\n",Local_Server_Port);
	return true;
}


static bool btnup()
{
	
//
}

extern unsigned char cmd_finish;

extern char skip_aim_flag;

static bool btndown()
{
	
	buttons_setFunc(BTN_1,down_line);
	buttons_setFunc(BTN_3,up_line); 
	

	console_log(1,"->");

	
	skip_aim_flag=1;
	return true;
}
extern char LOOP_SHOW_MD;
extern short pix_show_idx;

static display_t draw()
{

	console_loop_show();
	
//执行函数
			
	return DISPLAY_BUSY;
}

void Build_Server(void)
{
	  //mNetDebugOpen();
	  WiFi_send("AT+CWMODE=2\r\n");
	  delay_ms(500);
	  WiFi_send("AT+CIPMUX=1\r\n");
	  delay_ms(500);
	  WiFi_send("AT+CWSAP=\"%s\",\"%s\",1,2\r\n",Wifi_name,Wifi_password);
	  delay_ms(1000);
	  WiFi_send("AT+CIPSERVER=1,%d\r\n",Local_Server_Port);
	  delay_ms(500);
		console_log(1,"%s",Usart2_RxBuff);
  	console_log(1,"%s",&Data_buff[2]);
}

void mServerOpen()
{
	Build_server=1;
	display_setDrawFunc(draw);
	buttons_setFuncs(btndown, btnExit, btnup );
//	setPrevMenuOpen(&prevMenuData, mSensorOpen);
//	setMenuFuncs(btndown, btnExit, btnup,run_debug);
	beginAnimation2(NULL);

	//loop show模式
	LOOP_SHOW_MD=true;
//	Usart2_RxCompleted=0;
	
	//清除显示偏移
	pix_show_idx=64;
	
	//第一次进入时执行此函数
	if(server_begin==0)
	{
		console_log(1," ");
		console_log(1,"/***************/");
		console_log(500,"Building Server");
	
		Build_Server();
		server_begin=1;
	}
}

