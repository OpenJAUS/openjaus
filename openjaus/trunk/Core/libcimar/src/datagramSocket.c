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

DatagramSocket datagramSocketCreate(short port, InetAddress ipAddress)
{
	DatagramSocket datagramSocket;
	struct sockaddr_in address;
	socklen_t addressLength = sizeof(address);

	datagramSocket = (DatagramSocket) malloc( sizeof(DatagramSocketStruct) );
	if( datagramSocket == NULL )
	{
		return NULL;
	}
	
	// Open a socket with: Protocol Family (PF) IPv4, of Datagram Socket Type, and using UDP IP protocol explicitly
	datagramSocket->descriptor = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP); 
	if(datagramSocket->descriptor == -1)
	{
		return NULL;
	}
	
	memset(&address, 0, sizeof(address));					// Clear the data structure to zero
	address.sin_family = AF_INET;							// Set Internet Socket (sin), Family to: Address Family (AF) IPv4 (INET)
	address.sin_addr.s_addr = ipAddress->value;	// Set Internet Socket (sin), Address to: The ipAddressString argument
	address.sin_port = htons(port);							// Set Internet Socket (sin), Port to: the port argument

	// Bind our open socket to a free port on the localhost, with our defined ipAddress
	if(bind(datagramSocket->descriptor, (struct sockaddr *)&address, sizeof(address)))
	{
		close(datagramSocket->descriptor);
		return NULL;
	}

	if(getsockname(datagramSocket->descriptor, (struct sockaddr *)&address, &addressLength))
	{
		close(datagramSocket->descriptor);
		return NULL;
	}

	datagramSocket->address = ipAddress;
	datagramSocket->port = ntohs(address.sin_port);
	datagramSocket->timeout.tv_sec = 0;
	datagramSocket->timeout.tv_usec = 0;
	datagramSocket->blocking = 1;
	
	return datagramSocket;
}

void datagramSocketDestroy(DatagramSocket datagramSocket)
{
	close(datagramSocket->descriptor);
	free(datagramSocket);
}

int datagramSocketSend(DatagramSocket datagramSocket, DatagramPacket packet)
{
	struct sockaddr_in toAddress;
	int bytesSent = 0;
	struct timeval timeout;
	
	memset(&toAddress, 0, sizeof(toAddress));
	toAddress.sin_family = AF_INET;									// Set Internet Socket (sin), Family to: Address Family (AF) IPv4 (INET)
	toAddress.sin_addr.s_addr = packet->address->value;				// Set Internet Socket (sin), Address to: The packet ipAddressString
	toAddress.sin_port = htons(packet->port);						// Set Internet Socket (sin), Port to: the packet port
	
	timeout.tv_sec = 0;
	timeout.tv_usec = 1000; // Sleep at least one millisecond
							// TODO: This select is a temporary solution to give the hardware a small amount
							//		of time to process the data
	if(select(datagramSocket->descriptor + 1, NULL, NULL, NULL, &timeout) > -1)
	{
		bytesSent = sendto(datagramSocket->descriptor, (void *)packet->buffer, (size_t)packet->bufferSizeBytes, 0, (struct sockaddr *)&toAddress, sizeof(toAddress));
	}
	else
	{
		return -1;
	}
	
	return bytesSent;
}

int datagramSocketReceive(DatagramSocket datagramSocket, DatagramPacket packet)
{
	struct timeval timeout;
	struct timeval *timeoutPtr = NULL;
	fd_set readSet;
	struct sockaddr_in fromAddress;
	socklen_t fromAddressLength;
	int bytesReceived = 0;
	
	memset(&fromAddress, 0, sizeof(fromAddress));
	
	if(!datagramSocket->blocking)
	{
		timeout = datagramSocket->timeout;
		timeoutPtr = &timeout;
	}
	
	FD_ZERO(&readSet);
	FD_SET(datagramSocket->descriptor, &readSet);

	if(select(datagramSocket->descriptor + 1, &readSet, NULL, NULL, timeoutPtr) > 0)
	{
		if(FD_ISSET(datagramSocket->descriptor, &readSet))
		{
			fromAddressLength = sizeof(fromAddress);
			bytesReceived = recvfrom(datagramSocket->descriptor, packet->buffer, packet->bufferSizeBytes, 0, (struct sockaddr*)&fromAddress, &fromAddressLength);
		}
		else
		{
			return -1;
		}
		
	}
	else
	{
		return -1;
	}
	
	if(bytesReceived != -1)
	{
		packet->port = ntohs(fromAddress.sin_port);
		packet->address->value = fromAddress.sin_addr.s_addr;
	}
	
	return bytesReceived;
}

void datagramSocketSetTimeout(DatagramSocket datagramSocket, double timeoutSec)
{
	long sec, usec;
	
	sec = (long)timeoutSec;
	usec = (long)((timeoutSec - (double)sec) * 1.0e6);
			
	datagramSocket->timeout.tv_sec = sec;
	datagramSocket->timeout.tv_usec = usec;
	datagramSocket->blocking = 0;
}



