#include "Net_debug.h"
#include "common.h"
static prev_menu_s prevMenuData;
char Net_debug=0;
int debug_begin=0;
//bool keep_on=0;
static void itemLoader(byte);

static bool btnExit()
{
//	animation_start(display_load, ANIM_MOVE_OFF);
//	keep_on=false;  //�����draw��һֱˢ�±���������������رղ��ˣ���Ϊ��draw�̻߳��ٴθ���
//	setMenuOption_P(menuData.optionCount - 1, menuBack, menu_exit, back);
	back();
	Net_debug=0;
	debug_begin=0;
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
	
//ִ�к���
			
	return DISPLAY_BUSY;
}

void mNetDebugOpen()
{
	Net_debug=1;
	display_setDrawFunc(draw);
	buttons_setFuncs(btndown, btnExit, btnup );
//	setMenuFuncs(btndown, btnExit, btnup,run_debug);
	beginAnimation2(NULL);

	//loop showģʽ
	LOOP_SHOW_MD=true;
	Usart2_RxCompleted=0;
	
	//�����ʾƫ��
	pix_show_idx=64;
	
	//��һ�ν���ʱ��ӡ�˾仰
	if(debug_begin==0)
	{
		console_log(1," ");
		console_log(1,"/***************/");
		console_log(1,"Use PC to Debug");
		debug_begin=1;
	}
}



