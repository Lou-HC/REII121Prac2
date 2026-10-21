/*
Loulan
15 October 2026
Prac2 Reii121
*/
#include "Ports.h"
#include <mcs51/8051.h>

void InitPort0(void);

void InitPort0(void)
{
    P0M0 = OUTPUT_M0;
    P0M1 = OUTPUT_M1;

    P0M0 |= (INPUT_M0 & 0x80);
    P0M1 &= ~(INPUT_M1 & 0x80);

    //green LED
    P4M0 = (OUTPUT_M0 & 0x10);
    P4M1 = (OUTPUT_M1 & 0x10);

    /*
    This makes all but the DP Output,
    where the DP is input.
    */

}
