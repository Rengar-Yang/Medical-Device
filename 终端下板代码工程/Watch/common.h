/*
 * Project: N|Watch
 * Author: Zak Kemble, contact@zakkemble.co.uk
 * Copyright: (C) 2013 by Zak Kemble
 * License: GNU GPL v3 (see License.txt)
 * Web: http://blog.zakkemble.co.uk/diy-digital-wristwatch/
 */

#ifndef COMMON_H_
#define COMMON_H_




#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

#include "config.h"
#include "util.h"
#include "typedefs.h"
#include "debug.h"
#include "sys.h"
//#include "wdt.h"
//#include "spi.h"
//#include "i2c.h"
//#include "m_rtc.h"
//#include "adc.h"
//#include "oled.h"
#include "buttons.h"
//#include "battery.h"
//#include "buzzer.h"
//#include "led.h"
//#include "ds3231.h"
#include "millis.h"
#include "functions.h"
#include "alarms.h"
#include "diag.h"
#include "m_display.h"
#include "games.h"
#include "timedate.h"
#include "settings.h"
#include "sleep.h"
#include "sound.h"
#include "m_main.h"
#include "game1.h"
#include "game2.h"
#include "game3.h"
#include "game4.h"
#include "stopwatch.h"
#include "torch.h"
#include "Sensor.h"
#include "postdata.h"
#include "Net_debug.h"
#include "Build_Server.h"

//#include "screenshot.h"    //输出oledbuff里面的数据
#include "normal.h"
//#include "lowbatt.h"
#include "ui.h"
#include "tunemaker.h"

//#include "system.h"
#include "global.h"
#include "display.h"
#include "time.h"
#include "alarm.h"
#include "pwrmgr.h"
#include "appconfig.h"
//#include "disco.h"
#include "tune.h"
#include "animation.h"
#include "draw.h"
#include "menu.h"

#include "english.h"
#include "lang.h"
#include "tunes.h"
//#include "discos.h"
#include "resources.h"

#include "DHT11.h"
#include "bsp_adc.h"
#include "Net_debug.h"
#include "mpu6050.h"
#include "mpuiic.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "mpu_task.h"
#include "myiic.h"
#include "max30102.h"
#include "algorithm.h"

#include "wait_data_clock.h"
#include  "wifi_task.h"
#include "wifi.h"
#include "usart.h"
#include "usart2.h"
#include "usart3.h"
#include "gui_log_console.h"
#include "wifi_cmd_task.h"

#endif /* COMMON_H_ */
//extern s8 KEY1,KEY2,KEY0;
extern u8 NetTimeTask,PostData,PostOK,DebugOK;
extern 	u8 temperiture,humi; 
extern uint32_t aun_ir_buffer[500]; //IR LED sensor data   红外数据，用于计算血氧
extern int32_t n_ir_buffer_length;    //data length  
extern uint32_t aun_red_buffer[500];    //Red LED sensor data  红光数据，用于计算心率曲线以及计算心率
extern int32_t n_sp02; //SPO2 value
extern int8_t ch_spo2_valid;   //indicator to show if the SP02 calculation is valid
extern int32_t n_heart_rate;   //heart rate value
extern int8_t  ch_hr_valid;    //indicator to show if the heart rate calculation is valid
extern int32_t n_brightness;