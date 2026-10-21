#include "Driver_SPI.h"

unsigned char DataWriteSPI = 0;

void SetupDriverPortPinsPolling (void)
{
    P1M0 &= ~0xF0;  // Reset the high nibble to zeros
    P1M1 &= ~0xF0;  // Reset the high nibble to zeros

    P1M0 |= 0x20;   // P1.5 MISO set to input // 0010 = 0x2
    P1M1 |= 0xD0;   // P1.7 = MOSI, P1.6 = CS, P1.4 = CLCK set to Ouputs // 1101 = 0xD

    P1 &= ~0xF0;    // Make the high nibble all zeros
    // This action is set in the Driver_SPI.h file
    SPI_CS_HIGH;
    SPI_CLK_HIGH;
}

// This routine will use a methode called bit - bang
// This is a methode used to emulate a periperale hardware, e.g. SPI
// GPIO (General-purpose Input and Output) pins will be used to emulate the SPI
// P1.7 = MOSI, P1.6 = CS, P1.5 MISO, P1.4 = CLCK
// I use the following datasheet of the SPI expansion I/O: MCP23008-MCP23S08-Data-Sheet-20001919F.pdf
// Look at the following pg 27
// FIGURE 2-6: SPI OUTPUT TIMING
void SendSetupAddressData (unsigned char SetupAddress, unsigned char SetupData)
{
    volatile unsigned char SendData = SPI_WRITE_ADDRESS;
    volatile unsigned char LoopTimes;

    // Note the follwong from the diagram:
    // 1. The data is clocked on the falling edge
    // 2. The data on SO will be set when the clck is LOW
    // 3. The MSB - Most Significant Bit will be send first and the LSB - Least Significant Bit last

    // In the Setup of the port GPIO the CS and CLK was set high
    // The clock will start LOW and then the CS will be made LOW,
    // else if the CS go first LOW the CLK will load data into the IC when going LOW
    // We will have some wat time, a for loop.

    // The following bytes must be send
    // 1. IC address - see the header file and it must be a write
    // 2. The address in the MCP23S08 pg 8: TABLE 1-3: CONFIGURATION AND CONTROL REGISTERS
    // 3. The SetupData that needs to be setup

    SPI_CLK_LOW;
    SPI_CS_LOW; //we are active.
     // 8-bits must be send
    LoopTimes = 8;
    // 1. IC address - see the header file and it must be a write
    do
    {
        // write the first bit (MSB) onto MOSI PIN, HIGH or LOW by testing the bit
        if (SendData & 0x80)
            SPI_MOSI_HIGH;
        else
            SPI_MOSI_LOW;
        // Shift to the next bit
        SendData <<= 1;
        SPI_CLK_HIGH;
        SPI_CLK_LOW;
   }
    while (--LoopTimes > 0);

    // 8-bits must be send
    LoopTimes = 8;
    // 2. The address in the MCP23S08 pg 8: TABLE 1-3: CONFIGURATION AND CONTROL REGISTERS
    SendData = SetupAddress;
    do
    {
        // write the first bit (MSB) onto MOSI PIN, HIGH or LOW by testing the bit
        if (SendData & 0x80)
            SPI_MOSI_HIGH;
        else
            SPI_MOSI_LOW;
        // Shift to the next bit
        SendData <<= 1;
        SPI_CLK_HIGH;
        SPI_CLK_LOW;
  }
    while (--LoopTimes > 0);

    // 8-bits must be send
    LoopTimes = 8;
    // 3. The SetupData that needs to be setup
    SendData = SetupData;
    do
    {
        // write the first bit (MSB) onto MOSI PIN, HIGH or LOW by testing the bit
        if (SendData & 0x80)
            SPI_MOSI_HIGH;
        else
            SPI_MOSI_LOW;
        // Shift to the next bit
        SendData <<= 1;
        SPI_CLK_HIGH;
        SPI_CLK_LOW;
   }
    while (--LoopTimes > 0);
    // Data Send Done, make CS high
    SPI_CS_HIGH;
}

// This routine will use a methode called bit - bang
// This is a methode used to emulate a periperale hardware, e.g. SPI
// GPIO (General-purpose Input and Output) pins will be used to emulate the SPI
// P1.7 = MOSI, P1.6 = CS, P1.5 MISO, P1.4 = CLCK
// I use the following datasheet of the SPI expansion I/O: MCP23008-MCP23S08-Data-Sheet-20001919F.pdf
// Look at the following pg 27
// FIGURE 2-6: SPI OUTPUT TIMING
unsigned char ReadDataSPI (unsigned char SetupAddress)
{
    volatile unsigned char SendData = SPI_READ_ADDRESS;
    volatile unsigned char LoopTimes;
    unsigned char ReadByte = 0;

    // Note the follwong from the diagram:
    // 1. The data is clocked on the falling edge
    // 2. The data on SO will be set when the clck is LOW
    // 3. The MSB - Most Significant Bit will be send first and the LSB - Least Significant Bit last

    // In the Setup of the port GPIO the CS and CLK was set high
    // The clock will start LOW and then the CS will be made LOW,
    // else if the CS go first LOW the CLK will load data into the IC when going LOW
    // We will have some wat time, a for loop.

    // The following bytes must be send
    // 1. IC address - see the header file and it must be a write
    // 2. The address in the MCP23S08 pg 8: TABLE 1-3: CONFIGURATION AND CONTROL REGISTERS
    // 3. The SetupData that needs to be setup

    SPI_CLK_LOW;
    SPI_CS_LOW;
    // 8-bits must be send
    LoopTimes = 8;
    // 1. IC address - see the header file and it must be a write
    do
    {
        // write the first bit (MSB) onto MOSI PIN, HIGH or LOW by testing the bit
        if (SendData & 0x80)
            SPI_MOSI_HIGH;
        else
            SPI_MOSI_LOW;
        // Shift to the next bit
        SendData <<= 1;
        // wait a moment
        SPI_CLK_HIGH;
        SPI_CLK_LOW;
   }
    while (--LoopTimes > 0);

    // 8-bits must be send
    LoopTimes = 8;
    // 2. The address in the MCP23S08 pg 8: TABLE 1-3: CONFIGURATION AND CONTROL REGISTERS
    SendData = SetupAddress;
    do
    {
        // write the first bit (MSB) onto MOSI PIN, HIGH or LOW by testing the bit
        if (SendData & 0x80)
            SPI_MOSI_HIGH;
        else
            SPI_MOSI_LOW;
        // Shift to the next bit
        SendData <<= 1;
        SPI_CLK_HIGH;
        SPI_CLK_LOW;
  }
    while (--LoopTimes > 0);

    // 8-bits must be read
    LoopTimes = 8;
    // 3. The SetupData that needs to be setup
    SendData = 0x00;
    do
    {
        // write the first bit (MSB) onto MOSI PIN, HIGH or LOW by testing the bit
        if (SendData & 0x80)
            SPI_MOSI_HIGH;
        else
            SPI_MOSI_LOW;
        // Shift to the next bit
        SendData <<= 1;
        // wait a moment
    //    for (Wait = 0; Wait < WAIT_TIME; Wait++);
        SPI_CLK_HIGH;
   //     for (Wait = 0; Wait < WAIT_TIME; Wait++);
        ReadByte <<= 0x01;
        if (SPI_MISO_INPUT)
            ReadByte |= 0x01;
        SPI_CLK_LOW;
  //      for (Wait = 0; Wait < WAIT_TIME; Wait++);
   }
    while (--LoopTimes > 0);
    // Data Send Done, make CS high
    SPI_CS_HIGH;

    return ReadByte;
}
