/*
Loulan
15 October 2026
Prac2 Reii121
*/
#include <mcs51/8051.h>


#ifndef TIMERS_H
#define TIMERS_H

#define TIMER_RELOAD_HIGH   0xFC
#define TIMER_RELOAD_LOW    0x65
/*
done by:
x instructions * 1,085us/ins = 50ms

65535 - ans = THTL
*/

#define TIMER0_OVERFLOW_FLAG    0x20

#define TIMER0_OVERFLOW         TCON & TIMER0_OVERFLOW_FLAG

#define SEVEN_SEG_0     0x3F
#define SEVEN_SEG_1     0x06
#define SEVEN_SEG_2     0x5B
#define SEVEN_SEG_3     0x4F
#define SEVEN_SEG_4     0x66
#define SEVEN_SEG_5     0x6D
#define SEVEN_SEG_6     0x7D
#define SEVEN_SEG_7     0x07
#define SEVEN_SEG_8     0x7F
#define SEVEN_SEG_9     0x6F
#define SEVEN_SEG_DP    0x80

extern unsigned char SEVEN_SEG_NUMS[10];
extern unsigned char TimerFlags;

void InitTimer0Polling(void);
void RunTimer(void);
void Wait2s(void);
#endif // TIMER_CONTROL_H


