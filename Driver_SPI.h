// PVH 12 Desember 2025
/*
    Header File for generic helper functions
*/

#include <mcs51/8051.h>
#ifndef DIVER_SPI_H
#define DIVER_SPI_H

#define SPI_WRITE_ADDRESS   0x42    // Page 7 in MCP23008-MCP23S08-Data-Sheet-20001919F.pdf
#define SPI_READ_ADDRESS    0x43    // Page 7 in MCP23008-MCP23S08-Data-Sheet-20001919F.pdf

#define SPI_CS_HIGH         P1 |= 0x10
#define SPI_CS_LOW          P1 &= ~0x10
#define SPI_CS_TOGGLE       P1 ^= 0x10

#define SPI_CLK_HIGH        P1 |= 0x40
#define SPI_CLK_LOW         P1 &= ~0x40
#define SPI_CLK_TOGGLE      P1 ^= 0x40

#define SPI_MOSI_HIGH       P1 |= 0x80
#define SPI_MOSI_LOW        P1 &= ~0x80
#define SPI_MOSI_TOGGLE     P1 ^= 0x80

#define SPI_MISO_INPUT      P1 & 0x20

#define WAIT_TIME           1

#define MCP23S08_IODIR      0x00
#define MCP23S08_IPOL       0x01
#define MCP23S08_GPINTEN    0x02
#define MCP23S08_DEFVAL     0x03
#define MCP23S08_INTCON     0x04
#define MCP23S08_IOCON      0x05
#define MCP23S08_GPPU       0x06
#define MCP23S08_INTF       0x07
#define MCP23S08_INTCAP     0x08
#define MCP23S08_GPIO       0x09
#define MCP23S08_OLAT       0x0A

extern unsigned char DataWriteSPI;

void SetupDriverPortPinsPolling (void);
void SendSetupAddressData (unsigned char SetupAddress, unsigned char SetupData);
unsigned char ReadDataSPI (unsigned char SetupAddress);

#endif // DIVER_SPI_H
