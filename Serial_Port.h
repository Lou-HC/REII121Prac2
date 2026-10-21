/*
Loulan
15 October 2026
Prac2 Reii121
*/

#ifndef SERIAL_PORT_H
#define SERIAL_PORT_H

void InitSerialPort(void);
void SendByteSerialPort(unsigned char data);
void sendStringSerialPort(unsigned char *data);
void SendTime(unsigned char LeftOrRight, unsigned char num);

#endif // SERIAL_PORT_H
