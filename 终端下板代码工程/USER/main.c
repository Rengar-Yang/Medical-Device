#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h" 
#include "draw_api.h"
#include "test.h"
#include "led.h"
#include "lcd.h"
#include "common.h"
#include "yaogan.h"
#include "DHT11.h"
#include "usart3.h"

int a;
char ii=0;
extern unsigned char wifi_time_cnt;
u8 temperiture,humi; 
u8 NetTimeTask=0,PostData=0,PostOK=0;

RCC_ClocksTypeDef get_rcc_clock;
//max30102参数
uint32_t aun_ir_buffer[500]; //IR LED sensor data   红外数据，用于计算血氧
int32_t n_ir_buffer_length=500;    //data length  
uint32_t aun_red_buffer[500];    //Red LED sensor data  红光数据，用于计算心率曲线以及计算心率
int32_t n_sp02; //SPO2 value
int8_t ch_spo2_valid;   //indicator to show if the SP02 calculation is valid
int32_t n_heart_rate;   //heart rate value
int8_t  ch_hr_valid;    //indicator to show if the heart rate calculation is valid
#define MAX_BRIGHTNESS 255
int32_t n_brightness;
int8_t measure_mod=0,change_mod=0;

enum
{
	LA =262,
	LB =294,
	LC =330,
	LD =349,
	LE =392,
	LF =440,
	LG =494,
	
	MA =523,
	MB =578,
	MC =659,
	MD =698,
	ME =784,
	MF =880,
	MG =988,
	
	HA =1064,
	HB =1175,
	HC =1318,
	HD =1397,
	HE =1568,
	HF =1760,
	HG =1976
};


const uint32_t STAY[]={

	//5353
	ME<<16 | 250,
	MC<<16 | 250,
	ME<<16 | 250,
	MC<<16 | 250,
	//222321
	MB<<16 | 125,
	MB<<16 | 125,
	MB<<16 | 125,
	MC<<16 | 125,
	MB<<16 | 125,
	MA<<16 | 250,
	//7115
	LG<<16 | 125,
	MA<<16 | 125,
	MA<<16 | 125,
	ME<<16 | 500,
	//177777111
	MA<<16 | 125,
	LG<<16 | 125,
	LG<<16 | 125,
	LG<<16 | 125,
	LG<<16 | 125,
	LG<<16 | 125,
	MA<<16 | 125,
	MA<<16 | 125,
	MA<<16 | 250,
	//1715
	MA<<16 | 125,
	LG<<16 | 125,
	MA<<16 | 125,
	ME<<16 | 500,
	//177777111
	MA<<16 | 125,
	LG<<16 | 125,
	LG<<16 | 125,
	LG<<16 | 125,
	LG<<16 | 125,
	LG<<16 | 125,
	MA<<16 | 125,
	MA<<16 | 125,
	MA<<16 | 250,
	//1715
	MA<<16 | 125,
	LG<<16 | 125,
	MA<<16 | 125,
	ME<<16 | 500,
	//177777111
	MA<<16 | 125,
	LG<<16 | 125,
	LG<<16 | 125,
	LG<<16 | 125,
	LG<<16 | 125,
	LG<<16 | 125,
	MA<<16 | 125,
	MA<<16 | 125,
	MA<<16 | 250,
	//1715
	MA<<16 | 125,
	LG<<16 | 125,
	MA<<16 | 125,
	ME<<16 | 500,
	//71275
	LG<<16 | 125,
	MA<<16 | 125,
	MB<<16 | 125,
	MG<<16 | 125,
	ME<<16 | 500,
	
	
	
	TONE_REPEAT

};  //旋律


const uint32_t TUNE[]={
	
	
	LF<<16 | 250,
	LC<<16 | 250,
	HF<<16 | 250,
	MC<<16 | 250,
	
	LD<<16 | 250,
	MA<<16 | 250,
	MD<<16 | 250,
	MA<<16 | 250,
	
	LE<<16 | 250,
	MB<<16 | 250,
	ME<<16 | 250,
	MB<<16 | 250,
	
	MA<<16 | 250,
	ME<<16 | 250,
	HA<<16 | 250,
	ME<<16 | 250,
	
	LF<<16 | 250,
	LC<<16 | 250,
	HF<<16 | 250,
	MC<<16 | 250,
	
	LD<<16 | 250,
	MA<<16 | 250,
	MD<<16 | 250,
	MA<<16 | 250,
	
	LE<<16 | 250,
	MB<<16 | 250,
	ME<<16 | 250,
	MB<<16 | 250,
	//1 5123
	MA<<16 | 500,
	LE<<16 | 125,
	MA<<16 | 125,
	MB<<16 | 125,
	MC<<16 | 125,
	//2111
	MB<<16 | 250,
	MA<<16 | 125,
	MA<<16 | 125,
	MA<<16 | 500,
	
	TONE_PAUSE<<16 | 125,
	LE<<16 | 125,
	MA<<16 | 125,
	MB<<16 | 125,
	MC<<16 | 125,
	
	//212233
	MB<<16 | 250,
	MA<<16 | 125,
	MB<<16 | 125,
	MB<<16 | 125,
	MC<<16 | 250,
	MC<<16 | 125,
	
	//35123
	MC<<16 | 500,
	LE<<16 | 125,
	MA<<16 | 125,
	MB<<16 | 125,
	MC<<16 | 125,
	
	//2111
	MB<<16 | 250,
	MA<<16 | 125,
	MA<<16 | 125,
	MA<<16 | 500,
	
	
	//05123
	TONE_PAUSE<<16 | 125,
	LE<<16 | 125,
	MA<<16 | 125,
	MB<<16 | 125,
	MC<<16 | 125,
	//212253
	MB<<16 | 250,
	MA<<16 | 125,
	MB<<16 | 125,
	MB<<16 | 125,
	ME<<16 | 250,
	MC<<16 | 125,
	
	//334
	MC<<16 | 500,
	MC<<16 | 250,
	MD<<16 | 250,
	
	//55555
	ME<<16 | 250,
	ME<<16 | 125,
	ME<<16 | 125,
	ME<<16 | 250,
	ME<<16 | 250,
	
	//531134
	ME<<16 | 250,
	MC<<16 | 125,
	MA<<16 | 125,
	MA<<16 | 125,
	MC<<16 | 250,
	MD<<16 | 125,
	
	//55555
	ME<<16 | 250,
	ME<<16 | 125,
	ME<<16 | 125,
	ME<<16 | 250,
	ME<<16 | 250,
	//531 112
	ME<<16 | 250,
	MC<<16 | 125,
	MA<<16 | 125,
	MA<<16 | 250,
	MA<<16 | 125,
	MB<<16 | 125,
	
	//33333
	MC<<16 | 250,
	MC<<16 | 125,
	MC<<16 | 125,
	MC<<16 | 250,
	MC<<16 | 250,
	//366321
	MC<<16 | 250,
	LF<<16 | 250,
	MF<<16 | 125,
	MC<<16 | 125,
	MB<<16 | 125,
	LA<<16 | 250,
	
	//20
	MB<<16 | 500,
	TONE_PAUSE<<16 | 125,
	
	//05123
	TONE_PAUSE<<16 | 125,
	LE<<16 | 125,
	MA<<16 | 125,
	MB<<16 | 125,
	MC<<16 | 125,
	//2111
	MB<<16 | 250,
	MA<<16 | 125,
	MA<<16 | 125,
	MA<<16 | 500,
	//05123
	TONE_PAUSE<<16 | 125,
	LE<<16 | 125,
	MA<<16 | 125,
	MB<<16 | 125,
	MC<<16 | 125,
	
	//212233
	MB<<16 | 250,
	MA<<16 | 125,
	MB<<16 | 125,
	MB<<16 | 125,
	MC<<16 | 250,
	MC<<16 | 125,
	
	//35123
	MC<<16 | 500,
	LE<<16 | 125,
	MA<<16 | 125,
	MB<<16 | 125,
	MC<<16 | 125,
	//2111
	MB<<16 | 250,
	MA<<16 | 125,
	MA<<16 | 125,
	MA<<16 | 500,
	//05123
	TONE_PAUSE<<16 | 125,
	LE<<16 | 125,
	MA<<16 | 125,
	MB<<16 | 125,
	MC<<16 | 125,
	//212253
	MB<<16 | 250,
	MA<<16 | 125,
	MB<<16 | 125,
	MB<<16 | 125,
	ME<<16 | 250,
	MC<<16 | 125,
	
	
	
	//334
	MC<<16 | 500,
	MC<<16 | 250,
	MD<<16 | 250,
	
	//55555
	ME<<16 | 250,
	ME<<16 | 125,
	ME<<16 | 125,
	ME<<16 | 250,
	ME<<16 | 250,
	
	//531134
	ME<<16 | 250,
	MC<<16 | 125,
	MA<<16 | 125,
	MA<<16 | 125,
	MC<<16 | 250,
	MD<<16 | 125,
	
	//55555
	ME<<16 | 250,
	ME<<16 | 125,
	ME<<16 | 125,
	ME<<16 | 250,
	ME<<16 | 250,
	//531 112
	ME<<16 | 250,
	MC<<16 | 125,
	MA<<16 | 125,
	MA<<16 | 250,
	MA<<16 | 125,
	MB<<16 | 125,
	
	//33333
	MC<<16 | 250,
	MC<<16 | 125,
	MC<<16 | 125,
	MC<<16 | 250,
	MC<<16 | 250,
	//363216
	MC<<16 | 500,
	MF<<16 | 125,
	MC<<16 | 125,
	MB<<16 | 125,
	MA<<16 | 125,
	LF<<16 | 125,
	
	//10
	MA<<16 | 500,
	TONE_PAUSE<<16 | 250,
	//0
	//TONE_PAUSE<<16 | 3000,
	
	//55555
	ME<<16 | 250,
	ME<<16 | 125,
	ME<<16 | 125,
	ME<<16 | 250,
	ME<<16 | 250,
	
	//531134
	ME<<16 | 250,
	MC<<16 | 125,
	MA<<16 | 125,
	MA<<16 | 125,
	MC<<16 | 250,
	MD<<16 | 125,
	
	//55555
	ME<<16 | 250,
	ME<<16 | 125,
	ME<<16 | 125,
	ME<<16 | 250,
	ME<<16 | 250,
	//531 112
	ME<<16 | 250,
	MC<<16 | 125,
	MA<<16 | 125,
	MA<<16 | 250,
	MA<<16 | 125,
	MB<<16 | 125,
	
	
	
	//33333
	MC<<16 | 250,
	MC<<16 | 125,
	MC<<16 | 125,
	MC<<16 | 250,
	MC<<16 | 250,
	//366321
	MC<<16 | 250,
	LF<<16 | 250,
	MF<<16 | 125,
	MC<<16 | 125,
	MB<<16 | 125,
	LA<<16 | 250,
	
	//20
	MB<<16 | 500,
	TONE_PAUSE<<16 | 125,
	
	//05123
	TONE_PAUSE<<16 | 125,
	LE<<16 | 125,
	MA<<16 | 125,
	MB<<16 | 125,
	MC<<16 | 125,
	//2111
	MB<<16 | 250,
	MA<<16 | 125,
	MA<<16 | 125,
	MA<<16 | 500,
	//05123
	TONE_PAUSE<<16 | 125,
	LE<<16 | 125,
	MA<<16 | 125,
	MB<<16 | 125,
	MC<<16 | 125,
	
	//212233
	MB<<16 | 250,
	MA<<16 | 125,
	MB<<16 | 125,
	MB<<16 | 125,
	MC<<16 | 250,
	MC<<16 | 125,
	
	//35123
	MC<<16 | 500,
	LE<<16 | 125,
	MA<<16 | 125,
	MB<<16 | 125,
	MC<<16 | 125,
	
	//2111
	MB<<16 | 250,
	MA<<16 | 125,
	MA<<16 | 125,
	MA<<16 | 500,
	
	TONE_PAUSE<<16 | 2000,
	
	TONE_REPEAT

};  //旋律

void c_setup()
{
	
	SystemInit();	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2	  
	delay_init();	    	 //延时函数初始
	
	millis_init();				//软件任务定时器初始化
	Task_operater();			//硬件任务定时器初始化
	buttons_init();				//按钮初始化
	Usart1_init(9600);	 //串口初始化9600
	Usart2_Init(115200);
	Usart3_init(115200);	 //串口初始化115200
	WiFi_ResetIO_Init();
	DHT11_Init();
	ADCx_Init();
  max30102_init();
	
	u1_printf("AT+ROLE=S");
	RESET_IO(0);                                    //复位IO拉低电平
	delay_ms(500);                                  //延时500ms
	RESET_IO(1);   
	delay_ms(1000);
	WiFi_send("AT\r\n"); 
	delay_ms(500);
	WiFi_send("AT+CWMODE=1\r\n"); 
	delay_ms(500);
	WiFi_send("AT+CWJAP=\"%s\",\"%s\"\r\n",SSID,PASS); 
	delay_ms(500);

	ii=MPU_Init();
	printf("MPU_ERROR1:%d",ii);

	ii=mpu_dmp_init();																			//MPU自检
	printf("MPU_ERROR2:%d",ii);

	delay_ms(500);

	led_init();               //初始化LED
	buzzer_init();	
	time_init();
	pwrmgr_init();

}

void DownloadTime()//下载网络时间
{
	WiFi_send("AT+CIPMODE=1\r\n");
	delay_ms(500);
	delay_ms(500);
	WiFi_send("AT+CIPMUX=0\r\n");
	WiFi_send("AT+CIPSTART=\"TCP\",\"%s\",%d\r\n",ServerIP3,ServerPort);//发送连接服务器指令
	delay_ms(500);
	delay_ms(500);
	delay_ms(500);
	delay_ms(500);
	WiFi_send("AT+CIPSEND\r\n");                  //发送进入透传指令
	delay_ms(500);
	delay_ms(500);
	WiFi_send("GET http://cgi.im.qq.com\r\n");
	delay_ms(500);
	delay_ms(500);
	updata_time_data();
	WiFi_send("+++\r\n");
}

void ConnectWIFI()//连接WIFI
{
	WiFi_send("AT+CWMODE=1\r\n"); 
	delay_ms(500);
	WiFi_send("AT+CWJAP=\"%s\",\"%s\"\r\n",SSID,PASS); 
	delay_ms(500);
}

void PostData_cmd()//上传数据
{
		WiFi_send("AT+CIPMODE=1\r\n");
		delay_ms(200);
		WiFi_send("AT+CIPMUX=0\r\n");
	  delay_ms(200);
	  WiFi_send("AT+CIPSTART=\"TCP\",\"%s\",%d\r\n",Local_Server_IP,Local_Server_Port);
	  delay_ms(200);
	  WiFi_send("AT+CIPSEND\r\n");
	  delay_ms(200);		
		PostOK=1;
}

void c_loop()
{
	RCC_GetClocksFreq(&get_rcc_clock);//记录时钟频率
  time_update();
	
	if(pwrmgr_userActive())
	{
		buttons_update();
	}
  
	
  	buzzer_update();
	
    led_update();
	
	
#if COMPILE_STOPWATCH
	stopwatch_update();
#endif

	pwrmgr_update();
	

}


int main(void)
{ 
	
	//max30102变量
	uint32_t un_min, un_max, un_prev_data;  
	int i,j;
	float f_temp;
	u8 temp[6];
	
	c_setup();	    //初始化
  a=1;
	
	while(1)
	{
		if(USART3_RX_BUF[2]==1||PostData==1)//上板发来了心率指令
		{
				if(measure_mod==0&&aun_red_buffer[400]>=10000)//待机状态转变为测量状态
			{
				max30102_standard();//标准模式
				measure_mod=1;
			}
			
			if(measure_mod==1&&aun_red_buffer[400]<10000)//进入待机状态
			{
				max30102_standby();//待机模式
				measure_mod=0;
				n_heart_rate=0;//无手指时保证数值为0
				n_sp02=0;
			}
			
			//读取和计算max30102数据，总体用缓存的500组数据分析，实际每读取100组新数据分析一次
						i=0;
						un_min=0x3FFFF;
						un_max=0;
						//将前100组样本转储到内存中（实际没有），并将后400组样本移到顶部，将100-500缓存数据移位到0-400
						for(i=100;i<500;i++){
								aun_red_buffer[i-100]=aun_red_buffer[i];//将100-500缓存数据移位到0-400
								aun_ir_buffer[i-100]=aun_ir_buffer[i];//将100-500缓存数据移位到0-400
								//更新信号的最小值和最大值
								if(un_min>aun_red_buffer[i])//寻找移位后0-400中的最小值
									un_min=aun_red_buffer[i];
								if(un_max<aun_red_buffer[i])//寻找移位后0-400中的最大值
									un_max=aun_red_buffer[i];
						}
						//在计算心率前取100组样本，取的数据放在400-500缓存数组中
						for(i=400;i<500;i++){
							un_prev_data=aun_red_buffer[i-1];//临时记录上一次读取数据
							while(MAX30102_INT==1);
							max30102_FIFO_ReadBytes(REG_FIFO_DATA,temp);//读取传感器数据，赋值到temp中
							aun_red_buffer[i] =  (long)((long)((long)temp[0]&0x03)<<16) | (long)temp[1]<<8 | (long)temp[2];  //将值合并得到实际数字，数组400-500为新读取数据
							aun_ir_buffer[i] = (long)((long)((long)temp[3] & 0x03)<<16) |(long)temp[4]<<8 | (long)temp[5];   //将值合并得到实际数字，数组400-500为新读取数据
							if(aun_red_buffer[i]>un_prev_data){//用新获取的一个数值与上一个数值对比
								f_temp=aun_red_buffer[i]-un_prev_data;
								f_temp/=(un_max-un_min);
								f_temp*=MAX_BRIGHTNESS;//公式（心率曲线）=（新数值-旧数值）/（最大值-最小值）*255
								n_brightness-=(int)f_temp;
								if(n_brightness<0)
									n_brightness=0;
							}
							else{
								f_temp=un_prev_data-aun_red_buffer[i];
								f_temp/=(un_max-un_min);
								f_temp*=MAX_BRIGHTNESS;//公式（心率曲线）=（旧数值-新数值）/（最大值-最小值）*255
								n_brightness+=(int)f_temp;
								if(n_brightness>MAX_BRIGHTNESS)
									n_brightness=MAX_BRIGHTNESS;
							}
							
					}
						maxim_heart_rate_and_oxygen_saturation(aun_ir_buffer, n_ir_buffer_length, aun_red_buffer, &n_sp02, &ch_spo2_valid, &n_heart_rate, &ch_hr_valid);//传入500个心率和血氧数据计算传感器检测结论，反馈心率和血氧测试结果
						if(n_heart_rate<0)n_heart_rate=0;//保证数值非负
						if(n_sp02<0)n_sp02=0;
						if(n_sp02<95&&n_sp02>0)n_sp02=95;
			}				
			else
			{
				max30102_standby();
				measure_mod=0;
			}
			
			/*获取时间*/
			if(USART3_RX_BUF[3]==1&&NetTimeTask==0)//上板发来了网络时间指令
			{
				delay_ms(500);//消抖
				if(USART3_RX_BUF[3]==1&&NetTimeTask==0)//上板发来了网络时间指令
				{
					DownloadTime();
					NetTimeTask=1;
				}
			}
			else if (USART3_RX_BUF[3]==0&&NetTimeTask==1)
			{
				delay_ms(500);//消抖
				if (USART3_RX_BUF[3]==0&&NetTimeTask==1)
					NetTimeTask=0;
			}
			
			/*网络Debug*/
			if(USART3_RX_BUF[5]==1&&Net_debug==0)//上板发来了网络debug指令
			{
				delay_ms(500);//消抖
				if(USART3_RX_BUF[5]==1&&Net_debug==0)//上板发来了网络debug指令
				{
					Net_debug=1;
				}
			}
			else if (USART3_RX_BUF[5]==0&&Net_debug==1)
			{
				delay_ms(500);//消抖
				if (USART3_RX_BUF[5]==0&&Net_debug==1)
					Net_debug=0;
			}
			
			/*上传数据*/
			if(USART3_RX_BUF[7]==1&&PostData==0)//上板发来了上传数据指令
			{
				delay_ms(500);//消抖
				if(USART3_RX_BUF[7]==1&&PostData==0&&PostOK==0)//上板发来了上传数据指令
				{
					PostData=1;
					PostData_cmd();
				}
			}
			
		}

}

