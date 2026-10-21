/*
 */

#include <mcs51/8051.h>
#include "Driver_SPI.h"
#include "Timers.h"
#include "Ports.h"
#include "Serial_Port.h"
#include "main.h"

void IncLeftSide(void);

void IncRightSide(void);

void SetupRightSevenSegNums(void);

unsigned char GetRightSevenSeg(void);

unsigned char rightNum = 8, leftNum = 5;

unsigned char RIGHT_SEVEN_SEG_NUMS[10];


void main(void)
{

    // Insert code




    unsigned int left_inc = DEF_INC_VAL, right_inc = DEF_INC_VAL;

    //All Init

    SetupDriverPortPinsPolling();

    InitPort0();

    InitSerialPort();

    InitTimer0Polling();

    SendSetupAddressData(MCP23S08_IODIR, 0x80);

    SetupRightSevenSegNums();

    //Initial values

    SendSetupAddressData(MCP23S08_GPIO, RIGHT_SEVEN_SEG_NUMS[rightNum]);

    P0 = SEVEN_SEG_NUMS[leftNum];

    Wait2s();


    unsigned char leftCount = 0, rightCount = 0;
    unsigned char numPassLeft = 0, numPassRight = 0;


    while(1)
    {
        RunTimer();
        if (TimerFlags & 0x02) //meaning that 100ms have passed
        {
            TimerFlags &= ~0x02;
            leftCount++;
            rightCount++;
            //*** LEFT SIDE ***//
            if ((leftCount * DEF_INC_VAL) == left_inc)
            {
                leftCount = 0;
                IncLeftSide();
                numPassLeft++;
            }
            if (SW8)
            {
                while (SW8)
                {
                    //wait until it's released
                };
                left_inc += DEF_INC_VAL;
                numPassLeft = 0;
                SendTime('l', left_inc);
                //now the leftside is  counting slower.
            }

            //*** RIGHT SIDE ***//

            if ((rightCount * DEF_INC_VAL) == right_inc)
            {
                rightCount = 0;
                IncRightSide();
                numPassRight++;
            }
            if (SW16)
            {
                while (SW16)
                {
                    //wait until it's released
                };
                right_inc += DEF_INC_VAL;
                numPassRight = 0;
                SendTime('r', right_inc);
                //now the rightside is  counting slower.
            }

            //now we want to reset each after a second each

            //left
            if (numPassLeft >= 1000 / left_inc)
            {
                numPassLeft = 0;
                if (left_inc != DEF_INC_VAL)
                {
                    SendTime('l', DEF_INC_VAL);
                }

                left_inc = DEF_INC_VAL;

            }
            //right
            if (numPassRight >= 1000 / right_inc)
            {
                numPassRight = 0;
                if (right_inc != DEF_INC_VAL)
                {
                    SendTime('r', DEF_INC_VAL);
                }
                right_inc = DEF_INC_VAL;


            }

            /*
            MATH
            (number of passes) times (time per pass) = time passed
            and 100ms is 1/10 of 1s
            thus we times DEFVAL with 10.
            WHEEEEEE :0         :)

            */



        }//100ms passed
    }//while 1
    ;

} //main end

void IncLeftSide(void)
{

    if (leftNum == 9)
    {
        leftNum = 0;
    }
    else
    {
        leftNum++;
    }
    P0 = SEVEN_SEG_NUMS[leftNum];

}

void IncRightSide(void)
{
    if (rightNum == 9)
    {
        rightNum = 0;
    }
    else
    {
        rightNum++;
    }
    SendSetupAddressData(MCP23S08_GPIO, RIGHT_SEVEN_SEG_NUMS[rightNum]);
}

void SetupRightSevenSegNums(void)
{
    /*
    Testing Right LED:
    0x01    a
    0x02    b
    0x04    c
    0x08    d
    0x10    e
    0x20    no work; supposed to be g
    0x40    f
    */
    for (int i = 0; i < 10; i++)
    { //we are swapping the F and G pins on the displays.
        //F => 0010 0000 => 0x20; G => 0100 0000 => 0x40;
        RIGHT_SEVEN_SEG_NUMS[i] = SEVEN_SEG_NUMS[i];
        // First, the F:
        if (RIGHT_SEVEN_SEG_NUMS[i] & 0x20) //if F on, turn G on
        {
            RIGHT_SEVEN_SEG_NUMS[i] |= 0x40;
        }
        else
        {
            RIGHT_SEVEN_SEG_NUMS[i] &= ~0x40; //else, turn G off
        }
        //Next, the G:
        if (RIGHT_SEVEN_SEG_NUMS[i] & 0x40) //if G on, turn F on
        {
            RIGHT_SEVEN_SEG_NUMS[i] |= 0x20;
        }
        else
        {
            RIGHT_SEVEN_SEG_NUMS[i] &= ~0x20; //else, turn F off
        }

    }
}

unsigned char GetRightSevenSeg(void)
{
    /*
    #steps for Louis :)
    1. Set IO Dir
    2. Ask for data

    However, consider that the IO Dir for SW16 has already been set above.
    Thus, we need only ask for the data
    Which can be found in the GPIO
    */
    return ReadDataSPI(MCP23S08_GPIO);

}
