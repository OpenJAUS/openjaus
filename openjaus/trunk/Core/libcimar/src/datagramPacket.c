// File Name: datagramPacket.c
//
// Written By: Tom Galluzzo (galluzzo AT gmail DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file describes the functionality associated with a DatagramPacket object. 
// Inspired by the class of the same name in the JAVA language.

#include <unistd.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "cimar.h"

DatagramPacket datagramPacketCreate(void)
{
	DatagramPacket packet;
	
	packet = (DatagramPacket)malloc( sizeof(DatagramPacketStruct) );
	if(packet == NULL)
	{
		return NULL;
	}

	packet->address = inetAddressCreate();
	if(packet->address == NULL)
	{
		free(packet);
		return NULL;
	}
	
	return packet;
}

void datagramPacketDestroy(DatagramPacket packet)
{
	inetAddressDestroy(packet->address);
	
	free(packet);
}
