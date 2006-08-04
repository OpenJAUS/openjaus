// File Name: datagramPacket.h
//
// Written By: Tom Galluzzo (galluzzo AT gmail DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file describes the functionality associated with a DatagramPacket object. 
// Inspired by the class of the same name in the JAVA language.

#ifndef DATAGRAM_PACKET_H
#define DATAGRAM_PACKET_H

typedef struct
{
	unsigned char *buffer;
	int bufferSizeBytes;
	unsigned short port;
	InetAddress address;
}DatagramPacketStruct;

typedef DatagramPacketStruct *DatagramPacket;

DatagramPacket datagramPacketCreate(void);
void datagramPacketDestroy(DatagramPacket);

#endif // DATAGRAM_PACKET_H
