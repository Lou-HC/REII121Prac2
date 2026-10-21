/*
Loulan
15 October 2026
Prac2 Reii121
*/

#include <mcs51/8051.h>
#include "Timers.h"
#include "Serial_Port.h"

unsigned char TimerFlags = 0;
/*
all in ms
0000 0001 => 50
0000 0010 => 100

*/

unsigned char SEVEN_SEG_NUMS[10] = {SEVEN_SEG_0, SEVEN_SEG_1, SEVEN_SEG_2, SEVEN_SEG_3, SEVEN_SEG_4, SEVEN_SEG_5, SEVEN_SEG_6, SEVEN_SEG_7, SEVEN_SEG_8, SEVEN_SEG_9};


void InitTimer0Polling(void);

void RunTimer(void);

void Wait2s(void);



void InitTimer0Polling(void)
{
    TMOD |= 0x01;
    TH0 = TIMER_RELOAD_HIGH;
    TL0 = TIMER_RELOAD_LOW;

    RH0 = TIMER_RELOAD_HIGH;
    RL0 = TIMER_RELOAD_LOW;

    TR0 = 1;
}

void RunTimer(void)
{
    /*
all in ms
0000 0001 => 50     0x01
0000 0010 => 100    0x02

*/
    static unsigned char count = 0;

    if (TIMER0_OVERFLOW)
        { //1ms has passed
            TCON &= ~TIMER0_OVERFLOW_FLAG; //overflow flag off
            count++;
        }
        /*
        Meaning that the timer has overflowed.
        50ms have passed.
        */
        if ((count > 50) && (TimerFlags & 0x01))
        {
            /*
            If timerflags & 0x01 and overflow, that means that 50ms has passed
            after 50 ms have passed, i.e. 100ms have passed.
            */
            TimerFlags |= 0x02;
            TimerFlags &= ~0x01;
            count = 0;
        }
        if (count > 50)
        {

            TimerFlags |= 0x01;
            count = 0;
        }




}

void Wait2s(void)
{
    unsigned char count = 0;

    while (count < 20)
    {
        RunTimer();
        if (TimerFlags & 0x02)
            {
                //100ms
                TimerFlags &= ~0x02;
                count++;
            }
    }

}



