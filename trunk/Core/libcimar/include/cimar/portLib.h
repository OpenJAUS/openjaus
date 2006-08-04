// File Name: portLib.h
//
// Written By: David Novick, Jeff Wit, Tom Galluzzo (galluzzo AT gmail DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: Serial port hardware abstraction header file

#ifndef PORT_LIB_H
#define PORT_LIB_H

#define FLUSH_IN_BUF	0
#define FLUSH_OUT_BUF	1
#define FLUSH_BOTH_BUF	2

typedef int SerialPort;

#ifdef __cplusplus
extern "C" 
{
#endif

// Public Function Prototypes
int portClose(SerialPort );
int portCtl(SerialPort , int , char *);
SerialPort portOpen(int , int , char *);
int portSetVMin(SerialPort, int);
int portSetVtime(SerialPort, int);
int portRecv(SerialPort , char *, int);
int portSend(SerialPort , char *, int);

#ifdef __cplusplus
}
#endif

#endif // PORT_LIB_H
