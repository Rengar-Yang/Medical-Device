#ifndef __NS2009_H
#define __NS2009_H

#include "main.h"

#ifdef __cplusplus
extern "C"{
#endif // __cplusplus

#define NS2009_ADDR_READ  0x91
#define NS2009_ADDR_WRITE 0x90

#define NS2009_LOW_POWER_READ_X 	0xc0
#define NS2009_LOW_POWER_READ_Y 	0xd0
#define NS2009_LOW_POWER_READ_Z1 	0xe0
#define NS2009_LOW_POWER_READ_Z2 	0xf0

#define SCREEN_X_PIXEL 240
#define SCREEN_Y_PIXEL 320

void bsp_ns2009_init(void);
unsigned int ns2009_read(const unsigned char _cmd);
unsigned int bsp_ns2009_getPress(void);
unsigned int bsp_ns2009_getPos(unsigned int *_pos);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif
