// File Name: datagramSocket.h
//
// Written By: Tom Galluzzo (galluzzo AT gmail DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file describes the functionality associated with a DatagramSocket object. 
// Inspired by the class of the same name in the JAVA language.

#ifndef DATAGRAM_SOCKET_H
#define DATAGRAM_SOCKET_H

#include <sys/time.h>

typedef struct
{
	int descriptor;
	unsigned short port;
	InetAddress address;
	struct timeval timeout;
	int blocking;
}DatagramSocketStruct;

typedef DatagramSocketStruct *DatagramSocket;

DatagramSocket datagramSocketCreate(short, InetAddress);
void datagramSocketDestroy(DatagramSocket);

void datagramSocketSetSendBufferSize(DatagramSocket, int);
int datagramSocketGetSendBufferSize(DatagramSocket);
void datagramSocketSetRecvBufferSize(DatagramSocket, int);
int datagramSocketGetRecvBufferSize(DatagramSocket);
int datagramSocketSend(DatagramSocket, DatagramPacket);
int datagramSocketReceive(DatagramSocket, DatagramPacket);
void datagramSocketSetTimeout(DatagramSocket, double);

#endif // DATAGRAM_SOCKET_H
