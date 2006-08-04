// File Name: multicastSocket.h
//
// Written By: Tom Galluzzo (galluzzo AT gmail DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description:	This file describes the functionality associated with a MulicastSocket object.
// Inspired by the class of the same name in the JAVA language.

#ifndef MULTICAST_SOCKET_H
#define MULTICAST_SOCKET_H

typedef struct
{
	int descriptor;
	unsigned short port;
	InetAddress address;
	struct timeval timeout;
	int blocking;
	NetworkInterface netIf;
}MulticastSocketStruct;

typedef MulticastSocketStruct *MulticastSocket;

MulticastSocket multicastSocketCreate(short);
void multicastSocketDestroy(MulticastSocket);
int multicastSocketSetNetIf(MulticastSocket, NetworkInterface);
int multicastSocketJoinGroup(MulticastSocket, InetAddress);
int multicastSocketSend(MulticastSocket, DatagramPacket);

#endif // MULTICAST_SOCKET_H
