#include "beep.h" 


#include "common.h"



static uint buzzLen;
static millis8_t startTime;
static buzzFinish_f onFinish;
static tonePrio_t prio;

static void stop(void);



//TIM13 PWM部分初始化 
//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数
void TIM_PWM_Init_Init(u32 arr,u32 psc)
{                                                
//       //此部分需手动修改IO口设置
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);// 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);  //使能GPIO外设时钟使能
	                                                                     	

   //设置该引脚为复用输出功能,输出TIM3 CH1的PWM脉冲波形
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; //TIM_CH1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOA,GPIO_Pin_6);  //蜂鸣器对应引脚GPIO拉低，
	
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 80K
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  不分频
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_Pulse = 25; //设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx

	TIM_CtrlPWMOutputs(TIM3,ENABLE);	//MOE 主输出使能	

	//TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);  //CH1预装载使能	 
	
	//TIM_ARRPreloadConfig(TIM1, ENABLE); //使能TIMx在ARR上的预装载寄存器，禁用预装载寄存器，修改ARR的值（TIM_Period）会直接操作影子寄存器，新的ARR值将立即生效：
	
	TIM_Cmd(TIM3, DISABLE);  //使能TIM3
                                                       
}  



//蜂鸣器初始化
//初始化PF8为输出口		    
//BEEP IO初始化
void buzzer_init()
{
	TIM_PWM_Init_Init(50,1439);
}
 
// Non-blocking buzz
void buzzer_buzz(uint16_t len, uint16_t tone, vol_t volType, tonePrio_t _prio, buzzFinish_f _onFinish)
{
	if(_prio < prio)
		return;
	else if(tone == TONE_STOP)
	{
		stop();
		return;
	}


	
	// Tell power manager that we are busy buzzing
//	pwrmgr_setState(PWR_ACTIVE_BUZZER, PWR_STATE_IDLE);

	prio = _prio;
	onFinish = _onFinish;
	buzzLen = len;
	startTime = millis();

	// Silent pause tone   //无声暂停音
	if(tone == TONE_PAUSE)
	{
//		CLEAR_BITS(TCCR1A, COM1A1, COM1A0);
//		power_timer1_disable();
		TIM_SetCompare2(TIM3,5000);
		
		TIM_Cmd(TIM3, DISABLE);  //停止TIM3

		BEEP=0; 
		return;
	}

	// Workout volume
	uint ocr;
	byte vol;
	
	

	switch(volType)
	{
		case VOL_UI:
			vol = appConfig.volUI;
			break;
		case VOL_ALARM:
			vol = appConfig.volAlarm;
			break;
		case VOL_HOUR:
			vol = appConfig.volHour;
			break;
		default:
			vol = 2;
			break;
	}

	// Pulse width goes down as freq goes up
	// This keeps power consumption the same for all frequencies, but volume goes down as freq goes up

	//vol--;
//	if(vol > 2)
//		return;

//  uint icr = tone * (8 << 1);

//	ocr = icr - (icr / (32>>vol));
	
	ocr = 50000/tone;


	//BEEP=1; //PB.5 输出低 
	
	switch(vol)
	{
		case 0:
			TIM_SetCompare2(TIM3,5000);//给一个超级大值关闭音量
			break;
		case 1:
			TIM_SetCompare2(TIM3,ocr/8);//1/4音量
			break;
		case 2:
			TIM_SetCompare2(TIM3,ocr/4);//1/2音量
			break;
		case 3:
			TIM_SetCompare2(TIM3,ocr/2);//1/1音量
			break;
	}
	//TIM_SetCompare1(TIM1,(ocr>>(2-vol))/2);
	
	TIM_SetAutoreload(TIM3,ocr);  //改变频率
	TIM_SetCounter(TIM3,0);
	TIM_Cmd(TIM3, ENABLE);

}
/*
#include "led.h"

void buzzer_buzzb(byte len, tone_t tone, vol_t volType)
{
	(void)(volType);

	led_flash(LED_GREEN, 50, 255);
	led_flash(LED_RED, 50, 255);

	power_timer1_enable();
	TCCR1A |= _BV(COM1A1)|_BV(COM1A0);

//	static uint vol = 0;
//	vol++;
//	if(vol > 790)
//		vol = 1;
//	OCR1A = vol;

//	if(vol > 3)
//		vol = 0;
//	if(vol == 0)
//		OCR1A = tone; // normal
//	else if(vol == 1)
//		OCR1A = (tone * 2) - 50; // quiet
//	else if(vol == 2)
//		OCR1A = (tone / 2); // loud
//	else if(vol == 3)
//		OCR1A = (tone / 4); // loader (acually quiter)

	OCR1A = (tone * 2) - 100;
	ICR1 = tone * 2;
	while(len--)
	{
		delay(1);
		led_update();
	}		
//	delay(20);
	TCCR1A &= ~(_BV(COM1A1)|_BV(COM1A0));
	power_timer1_disable();
}
*/
// Are we buzzing?
bool buzzer_buzzing()
{
	return buzzLen;
}
#include "led.h"
// See if its time to stop buzzing
void buzzer_update()
{

	if(buzzLen && (millis() - startTime) >= buzzLen)
	{
		stop();
		led_flash(LED_GREEN, 50, 255);

		if(onFinish != NULL)
			onFinish();  //播放下一个音节
	}
}

static void stop()
{
//	CLEAR_BITS(TCCR1A, COM1A1, COM1A0);
//	power_timer1_disable();
    TIM_SetCompare2(TIM3,5000);
    TIM_Cmd(TIM3, DISABLE);  //停止TIM3
	BEEP=0; //PB.5 输出低 
	buzzLen = 0;
	prio = PRIO_MIN;

//	pwrmgr_setState(PWR_ACTIVE_BUZZER, PWR_STATE_NONE);
}

// Sometimes the buzzer kind of 'pops' from a bad waveform output (the first HIGH pulse is too long)
// Here we wait until a timer overflow and then turn on the timer output
// It still sometimes pops, but much less so than turning on the timer output in buzzer_buzz()
//ISR(TIMER1_OVF_vect)
//{
//	SET_BITS(TCCR1A, COM1A1, COM1A0);
//	TIMSK1 = 0;
//}






