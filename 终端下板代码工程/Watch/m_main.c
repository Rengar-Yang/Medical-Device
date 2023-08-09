/*
 * Project: N|Watch
 * Author: Zak Kemble, contact@zakkemble.co.uk
 * Copyright: (C) 2013 by Zak Kemble
 * License: GNU GPL v3 (see License.txt)
 * Web: http://blog.zakkemble.co.uk/diy-digital-wristwatch/
 */

#include "common.h"

#define OPTION_COUNT getItemCount()

static prev_menu_s prevMenuData;

static void mOpen(void);
static void mSelect(void);
static void itemLoader(byte);

static uint8_t getItemCount()
{
  uint8_t cnt = 1;
#if COMPILE_ALARM
	++cnt;
#endif
#if COMPILE_GAME1 || COMPILE_GAME2 || COMPILE_GAME3
  ++cnt;
#endif
#if COMPILE_STOPWATCH
  ++cnt;
#endif
#if COMPILE_TORCH
  ++cnt;
#endif
#if COMPILE_BTRCCAR
  ++cnt;
#endif
#if COMPILE_TUNEMAKER
  ++cnt;
#endif	
#if COMPILE_SENSOR
	++cnt;
#endif
#if COMPILE_DEBUG
	++cnt;
#endif
#if COMPILE_SERVER
	++cnt;
#endif
  return cnt;
}

void mMainOpen()
{
	buttons_setFuncs(NULL, menu_select, NULL);
	beginAnimation(mOpen);  //关闭动画开始，并执行打开主菜单
}

//打开主菜单
static void mOpen()
{
	display_setDrawFunc(menu_draw);  //绑定绘制函数为menu_draw

	buttons_setFuncs(menu_up, menu_select, menu_down);  //绑定按键功能函数

	setMenuInfo(OPTION_COUNT, MENU_TYPE_ICON, PSTR(STR_MAINMENU));   //获取当前菜单信息（选项个数，菜单类型是文字还是图标）
	setMenuFuncs(MENUFUNC_NEXT, mSelect, MENUFUNC_PREV, itemLoader);  //绑定菜单的函数,如前进后退选择确认

	setPrevMenuOpen(&prevMenuData, mOpen);  //储存上级菜单

	beginAnimation2(NULL);      //开启过度动画
	
}

static void mSelect()
{
	setPrevMenuExit(&prevMenuData);  //储存上一次菜单的选项
	doAction(true);
}

static void itemLoader(byte num)
{
	num = 0;
#if COMPILE_ALARM
	setMenuOption_P(num++, PSTR(STR_ALARMS), menu_alarm, mAlarmsOpen);
#endif
#if COMPILE_TORCH
	setMenuOption_P(num++, PSTR(STR_FLASHLIGHT), menu_torch, torch_open);
#endif
#if COMPILE_STOPWATCH
	setMenuOption_P(num++, PSTR(STR_STOPWATCH), menu_stopwatch, stopwatch_open);
#endif
#if COMPILE_BTRCCAR
	setMenuOption_P(num++, PSTR(STR_BTRCCAR), menu_stopwatch, btrccar_open);
#endif
	#if COMPILE_TUNEMAKER
	setMenuOption_P(num++, PSTR(STR_TUNEMAKER), menu_tunemaker, tunemakerOpen);
#endif	
#if COMPILE_GAME1 || COMPILE_GAME2 || COMPILE_GAME3
	setMenuOption_P(num++, PSTR(STR_GAMES), menu_games, mGamesOpen);
#endif
	//setMenuOption_P(num++, PSTR(STR_CALCULATORS), menu_calc, calcOpen);
#if COMPILE_SENSOR
	setMenuOption_P(num++, PSTR(STR_SENSOR), menu_sensor, mSensorOpen);
#endif
#if COMPILE_DEBUG
	setMenuOption_P(num++, PSTR(STR_DEBUG), menu_debug, mNetDebugOpen);
#endif
#if COMPILE_SERVER
  setMenuOption_P(num++, PSTR(STR_SERVER2), menu_cloud, mServerOpen);
#endif
	setMenuOption_P(num++, PSTR(STR_SETTINGS), menu_settings, mSettingsOpen);
	setMenuOption_P(OPTION_COUNT, PSTR(STR_EXIT), menu_exit, menu_close);
	
}
