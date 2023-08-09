/*******************************************************.h函数********/
#define TRIG_Send PAout(6) //输出端口为PA6
#define ECHO_Reci PAin(7) //输入端口为PA7

float Senor_Using(void);
void TIM3_Int_Init();
