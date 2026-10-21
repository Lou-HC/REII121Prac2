/*
Loulan
15 October 2026
Prac2 Reii121
*/


#include "Serial_Port.h"
#include <mcs51/8051.h>

void InitSerialPort(void);

void SendByteSerialPort(unsigned char data);

void sendStringSerialPort(unsigned char *data);

void InitTimer1(void);

void SendTime(unsigned char LeftOrRight, unsigned char num);


void InitSerialPort(void)
{
    SCON |= 0x40; //SM0 = 1, SM1 = 0 Only send, no receive

    InitTimer1();
}

void SendByteSerialPort(unsigned char data)
{
    TI = 0;
    SBUF = data;
    while (TI == 0);
}

void sendStringSerialPort(unsigned char *data)
{
    unsigned char i = 0;

    do
    {
        SendByteSerialPort(data[i]);
    } while (data[++i] != '\0');
}

void InitTimer1(void)
{
    TMOD |= 0x20;

    TH1 = 244;

    TR1 = 1;
}

void SendTime(unsigned char LeftOrRight, unsigned char num)
{
    sendStringSerialPort("\nTiming value");
    if (LeftOrRight == 'l' || LeftOrRight == 'L')
    {
        sendStringSerialPort("\nLeft = ");
    }
    else if (LeftOrRight == 'r' || LeftOrRight == 'R')
    {
        sendStringSerialPort("\nRight = ");
    }
    //since num is only in intervals of 100...
    num /= 100;
    SendByteSerialPort(num + '0');
    sendStringSerialPort("00ms\n");

}
