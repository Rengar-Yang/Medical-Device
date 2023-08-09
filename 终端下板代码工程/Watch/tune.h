/*
 * Project: N|Watch
 * Author: Zak Kemble, contact@zakkemble.co.uk
 * Copyright: (C) 2014 by Zak Kemble
 * License: GNU GPL v3 (see License.txt)
 * Web: http://blog.zakkemble.co.uk/diy-digital-wristwatch/
 */

#ifndef TUNE_H_
#define TUNE_H_
#include "typedefs.h"
#include "beep.h"
#define TUNEMEM_RAM 0
#define TUNEMEM_EEPROM 1
#define TUNEMEM_PROGMEM 2

// Where to store tunes
#define TUNEMEM_TYPE	TUNEMEM_RAM

#if TUNEMEM_TYPE == TUNEMEM_PROGMEM
#define TUNEMEM PROGMEM
#elif TUNEMEM_TYPE == TUNEMEM_EEPROM
#define TUNEMEM EEMEM
#else
#define TUNEMEM 
#endif

typedef ulong tune_t;

void tune_play(const tune_t*, vol_t, tonePrio_t);
void tune_stop(tonePrio_t);

#endif /* TUNE_H_ */
