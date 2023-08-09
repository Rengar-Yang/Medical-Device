#include "postdata.h"
#include "common.h"
static prev_menu_s prevMenuData;

//bool keep_on=0;
char HWsensor_run=0;

static void mSelect(void);
static void itemLoader(byte);

void mHWPostOpen(void)
{
	
	setMenuInfo(6, MENU_TYPE_STR, PSTR(STR_POSTMENU));
	setMenuFuncs(MENUFUNC_NEXT, mSelect, MENUFUNC_PREV, itemLoader);

	setPrevMenuOpen(&prevMenuData, mPostOpen);

	beginAnimation2(NULL); //打开动画动画过度
}


static void mTempOpen()
{
	char buf[24];
	sprintf(buf,"TEMP:%d",temperiture);
//	draw_string((char*)buf, false, 0, 16);
	setMenuOption(0, buf, NULL, NULL);
	sprintf(buf,"HUMI:%d",humi);
//	draw_string((char*)buf, false, 0, 24);
	setMenuOption(1, buf, NULL, NULL);
	sprintf(buf,"pit:%.2f",pitch);
//	draw_string((char*)buf, false, 0, 32);
	setMenuOption(2, buf, NULL, NULL);
	sprintf(buf,"rol:%.2f",roll);
//	draw_string((char*)buf, false, 0, 40);
	setMenuOption(3, buf, NULL, NULL);
	sprintf(buf,"yaw:%.2f",yaw);
//	draw_string((char*)buf, false, 0, 48);
	setMenuOption(4, buf, NULL, NULL);
	sprintf(buf,"TDS:%.2f",TDS_value);
//	draw_string((char*)buf, false, 0, 48);
	setMenuOption(5, buf, NULL, NULL);
}

static bool btnExit()
{
//	animation_start(display_load, ANIM_MOVE_OFF);
//	keep_on=false;  //如果在draw里一直刷新变量，变量在这里关闭不了，因为会draw线程会再次覆盖
	setMenuOption_P(menuData.optionCount - 1, menuBack, menu_exit, back);
	sensor_run=0;
	return true;
}

static void quit()
{
	menuData.prevMenu != NULL ? menuData.prevMenu() : mMainOpen();
	sensor_run=0;
	WiFi_send("+++");
}

static void itemLoader(byte num)
{
	sensor_run=1;
	mTempOpen();
//	buttons_setFuncs(btnExit, btnExit, btnExit);
//	beginAnimation2(NULL);	
	setMenuOption_P(menuData.optionCount - 1, menuBack, menu_exit, quit);
//	keep_on = true;
}

static void mSelect()
{
	setPrevMenuExit(&prevMenuData);
	doAction(exitSelected());
}