#include "common.h"
#include "usart.h"
#if COMPILE_GAME4

#define PLATFORM_WIDTH	12    //ƽ̨���
#define PLATFORM_HEIGHT	4     //ƽ̨�߶�
#define UPT_MOVE_NONE	0     //���ƶ�
#define UPT_MOVE_RIGHT	1     //�����ƶ�
#define UPT_MOVE_LEFT	2     //�����ƶ�
#define BLOCK_COLS		32    //ש������
#define BLOCK_ROWS		5     //ש������
#define BLOCK_COUNT		(BLOCK_COLS * BLOCK_ROWS)  //ש������

typedef struct{
	float x;
	float y;
	float velX;
	float velY;
}s_ball;

static const byte block[] PROGMEM ={
	0x07,0x07,0x07,
};

static const byte platform[] PROGMEM ={
	0x60,0x70,0x50,0x10,0x30,0xF0,0xF0,0x30,0x10,0x50,0x70,0x60,
};
static const byte platform2[] PROGMEM ={
	0x06,0x0E,0x0A,0x08,0x0C,0x0F,0x0F,0x0C,0x08,0x0A,0x0E,0x06,
};

static const byte ballImg[] PROGMEM ={
	0x03,0x03,
};

static bool btnExit(void);
static bool btnRight(void);
static bool btnLeft(void);
display_t game4_draw(void);

static byte uptMove;    //�ƶ�״̬
static s_ball ball;
static bool* blocks;
static byte lives;      //����ֵ
static uint score;      //�÷�
static byte platformX;  
static byte platformX2; //���������

//��Ϸ��ʼ
void game4_start()
{
	menu_close();
  u1_printf("AT+ROLE=M");
	srand(millis());

	display_setDrawFunc(game4_draw);
	buttons_setFuncs(btnRight, btnExit, btnLeft);
	
	uptMove = UPT_MOVE_NONE;

	ball.x = FRAME_WIDTH / 2;
	ball.y = FRAME_HEIGHT - 10;
	ball.velX = -0.5;
	ball.velY = -0.6;
//	ball.velX = -1;
//	ball.velY = -1.1;
	
	blocks = calloc(BLOCK_COUNT, 1);  //void* calloc��unsigned int num��unsigned int size���ڴ�Ķ�̬�洢���з���num������Ϊsize�������ռ�
									//��������һ��ָ�������ʼ��ַ��ָ��,calloc�������Զ����ڴ��ʼ��Ϊ0
	lives = 3;
	score = 0;
	platformX = (FRAME_WIDTH / 2) - (PLATFORM_WIDTH / 2);    //ƽ̨X���꣨����ƽ̨��ʼ���꣩ = ��Ļ���/2��ȥƽ̨���/2
	platformX2 = (FRAME_WIDTH / 2) - (PLATFORM_WIDTH / 2);
}
//��Ϸ�˳�
static bool btnExit()
{
	free(blocks);    //�ͷ��ڴ�ռ�ĺ���
	u1_printf("AT+ROLE=S");
	if(lives == 255)  //����ֵ�������������Ϊ��
		game4_start();
	else
		animation_start(display_load, ANIM_MOVE_OFF);
	return true;
}
//�����ƶ�
static bool btnRight()
{
	uptMove = UPT_MOVE_RIGHT;
	return false;
}
//�����ƶ�
static bool btnLeft()
{
	uptMove = UPT_MOVE_LEFT;
	return false;
}
//��Ϸ��ͼ
display_t game4_draw()
{
	bool gameEnded = ((score >= BLOCK_COUNT) || (lives == 255));  //��Ϸ������־�����÷ִ���ש������������ֵ���

	byte platformXtmp = platformX;        //�������ƽ̨X����
	
  platformX2 = FRAME_WIDTH - PLATFORM_WIDTH - USART1_RX_BUF[1];       //�Է�����
	
	// Move platform
	if(uptMove == UPT_MOVE_RIGHT)    //�����ƶ�
		platformXtmp += 3;
	else if(uptMove == UPT_MOVE_LEFT)   //�����ƶ�
		platformXtmp -= 3;
	uptMove = UPT_MOVE_NONE;     //Ĭ�ϲ��ƶ�

	// Make sure platform stays on screen
	if(platformXtmp > 250)
		platformXtmp = 0;
	else if(platformXtmp > FRAME_WIDTH - PLATFORM_WIDTH)
		platformXtmp = FRAME_WIDTH - PLATFORM_WIDTH;

	// Draw platform ����ƽ̨ͼ��
	draw_bitmap(platformXtmp, FRAME_HEIGHT - 8, platform, 12, 8, NOINVERT, 0);
	draw_bitmap(platformX2, 0, platform2, 12, 8, NOINVERT, 0);
	platformX = platformXtmp;

	// Move ball
	if(!gameEnded)   //�����Ϸû�н�����С������ƶ�
	{
		ball.x += ball.velX;
		ball.y += ball.velY;
	}

	bool blockCollide = false;   //��ײ��־
	const float ballX = ball.x;
	const byte ballY = ball.y;

	// Block collision    //����ײ
//	byte idx = 0;
//	LOOP(BLOCK_COLS, x)  //for(x=0;x<BLOCK_COLS;x++)
//	{
//		LOOP(BLOCK_ROWS, y)
//		{                         //С����ש���λ�ù�ϵ�������
//			if(!blocks[idx] && ballX >= x * 4 && ballX < (x * 4) + 4 && ballY >= (y * 4) + 8 && ballY < (y * 4) + 8 + 4)
//			{
//				buzzer_buzz(100, TONE_2KHZ, VOL_UI, PRIO_UI, NULL);    //������
//				blocks[idx] = true;   //ש����ʧ
//				blockCollide = true;  //��ײ��־λ��һ
//				score++;    //�÷ּ�һ
//			}
//			idx++;
//		}
//	}

	// Side wall collision
	if(ballX > FRAME_WIDTH - 2)
	{
		if(ballX > 240)
			ball.x = 0;		
		else
			ball.x = FRAME_WIDTH - 2;
		buzzer_buzz(200, TONE_2_5KHZ, VOL_UI, PRIO_UI, NULL);
		ball.velX = -ball.velX;		
	}
	if(ballX < 0)
	{
		ball.x = 0;		
		buzzer_buzz(200, TONE_2_5KHZ, VOL_UI, PRIO_UI, NULL);
		ball.velX = -ball.velX;	
	}
	
	// Top/bottom wall collision	
		if(ballY > FRAME_HEIGHT - 2)
	{
		if(ballY > 240)
			ball.y = 0;		
		else
			ball.y = FRAME_HEIGHT - 2;
		buzzer_buzz(200, TONE_2_5KHZ, VOL_UI, PRIO_UI, NULL);
		ball.velY = -ball.velY;		
	}
	 if(ballY < 0)
	{
		ball.y = 0;		
		buzzer_buzz(200, TONE_2_5KHZ, VOL_UI, PRIO_UI, NULL);
		ball.velY = -ball.velY;	
	}
	

	// Platform collision С����ƽ̨��ײ
	bool platformCollision = false;         //С���Y���������Ļ�߶ȼ�ȥƽ̨�߶�&&С��X������ƽ̨��ʼ�����ƽ̨��ʼ�������ƽ̨���֮��
	if(!gameEnded && ballY >= FRAME_HEIGHT - PLATFORM_HEIGHT && ballY < 240 && ballX >= platformX && ballX <= platformX + PLATFORM_WIDTH)
	{
		platformCollision = true;
		buzzer_buzz(200, TONE_5KHZ, VOL_UI, PRIO_UI, NULL);
		ball.y = FRAME_HEIGHT - PLATFORM_HEIGHT;
		if(ball.velY > 0)
			ball.velY = -ball.velY;
		ball.velX = ((float)rand() / (RAND_MAX / 2)) - 1; // -1.0 to 1.0   X�����ٶ��������
	}
	
	if(!gameEnded && ballY <= PLATFORM_HEIGHT+4 && ballY < 240 && ballX >= platformX2 && ballX <= platformX2 + PLATFORM_WIDTH)
	{
		platformCollision = true;
		buzzer_buzz(200, TONE_5KHZ, VOL_UI, PRIO_UI, NULL);
		ball.y = PLATFORM_HEIGHT+5;
		if(ball.velY < 0)
			ball.velY = -ball.velY;
		ball.velX = ((float)rand() / (RAND_MAX / 2)) - 1; // -1.0 to 1.0   X�����ٶ��������
	}

	// Top/bottom wall collision
//	if(!gameEnded && !platformCollision && (ballY > FRAME_HEIGHT - 2 || blockCollide))
//	{
//		if(ballY > 240)
//		{
//			buzzer_buzz(200, TONE_2_5KHZ, VOL_UI, PRIO_UI, NULL);
//			ball.y = 0;
//		}
//		else if(!blockCollide)
//		{
//			buzzer_buzz(200, TONE_2KHZ, VOL_UI, PRIO_UI, NULL);
//			ball.y = FRAME_HEIGHT - 1;
//			//lives--;
//		}
//		ball.velY *= -1;
//	}

	// Draw ball  ����С��
	draw_bitmap(ball.x, ball.y, ballImg, 2, 8, NOINVERT, 0);

	// Draw blocks  ����ש��
//	idx = 0;
//	LOOP(BLOCK_COLS, x)
//	{
//		LOOP(BLOCK_ROWS, y)
//		{
//			if(!blocks[idx])
//				draw_bitmap(x * 4, (y * 4) + 8, block, 3, 8, NOINVERT, 0);
//			idx++;
//		}
//	}

	// Draw score   ��ӡ����
//	char buff[6];
//	sprintf_P(buff, PSTR("%u"), score);
//	draw_string(buff, false, 0, 0);

	// Draw score   ��ӡ����״̬
	if(u1_disconnect>=200)
	{
		char buff[6];
		sprintf_P(buff, PSTR("Wait to connect"));
		draw_string(buff, false, 16, 28);
	}

	// Draw lives   ��ӡ����ֵ
//	if(lives != 255)
//	{
//		LOOP(lives, i)
//			draw_bitmap((FRAME_WIDTH - (3*8)) + (8*i), 1, livesImg, 7, 8, NOINVERT, 0);
//	}	

              USART1_TX_BUF[0]=0xa5;
					  	USART1_TX_BUF[USART1_TXD_LEN-1]=0x5a;
							USART1_TX_BUF[1]=platformXtmp;//��������
							USART1_TX_BUF[2]=ballX;
							USART1_TX_BUF[3]=ballY;
							USART1_TX_BUF[USART1_TXD_LEN-2]=0;
						
							for(int i=1;i<=USART1_TXD_LEN-3;i++)
							USART1_TX_BUF[USART1_TXD_LEN-2]+=USART1_TX_BUF[i];	
						
							for(int t=0;t<USART1_TXD_LEN;t++)
							{
								USART_SendData(USART1, USART1_TX_BUF[t]);//�򴮿�1��������
								while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
							}
							
	// Got all blocks   //��������ש��
	if(score >= BLOCK_COUNT)
		draw_string_P(PSTR(STR_WIN), false, 50, 32);  //������Ϸʤ��

	// No lives left (255 because overflow)
	if(lives == 255)
		draw_string_P(PSTR(STR_GAMEOVER), false, 34, 32);  //������Ϸ����

	return DISPLAY_BUSY;  //������Ļˢ��æ
}

#endif