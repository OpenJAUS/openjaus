/*****************************************************************************
 *  Copyright (c) 2006, University of Florida.
 *  All rights reserved.
 *  
 *  This file is part of OpenJAUS.  OpenJAUS is distributed under the BSD 
 *  license.  See the LICENSE file for details.
 * 
 *  Redistribution and use in source and binary forms, with or without 
 *  modification, are permitted provided that the following conditions 
 *  are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer in the documentation and/or other materials provided
 *       with the distribution.
 *     * Neither the name of the University of Florida nor the names of its 
 *       contributors may be used to endorse or promote products derived from 
 *       this software without specific prior written permission.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
 *   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
 *   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR 
 *   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
 *   OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, 
 *   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY 
 *   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 ****************************************************************************/
// File Name: multicastSocket.c
//
// Written By: Tom Galluzzo (galluzzo AT gmail DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description:	This file describes the functionality associated with a MulicastSocket object.
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

MulticastSocket multicastSocketCreate(short port)
{
	MulticastSocket multicastSocket;
//	struct sockaddr_in address;
//	socklen_t addressLength = sizeof(address);

	multicastSocket = (MulticastSocket)malloc( sizeof(MulticastSocketStruct) );
	if(multicastSocket == NULL)
	{
		return NULL;
	}
	
	// Open a socket with: Protocol Family (PF) IPv4, of Datagram Socket Type, and using UDP IP protocol explicitly
	multicastSocket->descriptor = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP); 
	if(multicastSocket->descriptor == -1)
	{
		return NULL;
	}

	multicastSocket->netIf = NULL;
	multicastSocket->port = port;
	multicastSocket->timeout.tv_sec = 0;
	multicastSocket->timeout.tv_usec = 0;
	multicastSocket->blocking = 1;
	
	return multicastSocket;
	
/*	memset(&address, 0, sizeof(address));					// Clear the data structure to zero
	address.sin_family = AF_INET;							// Set Internet Socket (sin), Family to: Address Family (AF) IPv4 (INET)
	address.sin_addr.s_addr = inet_addr(ipAddressString);	// Set Internet Socket (sin), Address to: The ipAddressString argument
	address.sin_port = htons(port);							// Set Internet Socket (sin), Port to: the port argument

	// Bind our open socket to a free port on the localhost, with our defined ipAddress
	if(bind(multicastSocket->descriptor, (struct sockaddr *)&address, sizeof(address)))
	{
		close(multicastSocket->descriptor);
		return -2;
	}

	if(getsockname(multicastSocket->descriptor, (struct sockaddr *)&address, &addressLength))
	{
		close(multicastSocket->descriptor);
		return -3;
	}

	memset(multicastSocket->ipAddressString, 0, IP_ADDRESS_STRING_SIZE_BYTES);
	sprintf(multicastSocket->ipAddressString, "%s", inet_ntoa(address.sin_addr));
	multicastSocket->port = ntohs(address.sin_port);
	*/
}

void multicastSocketDestroy(MulticastSocket multicastSocket)
{
	close(multicastSocket->descriptor);
	free(multicastSocket);
}

int multicastSocketSetNetIf(MulticastSocket multicastSocket, NetworkInterface netIf)
{
	if(multicastSocket == NULL)
	{
		return -1;
	}

	multicastSocket->netIf = netIf;

#ifdef SO_BINDTODEVICE
	return setsockopt(multicastSocket->descriptor, SOL_SOCKET, SO_BINDTODEVICE, netIf->name, sizeof(netIf->name) + 1);
#else
	fprintf(stderr, "multicastSocket.c: SO_BINDTODEVICE not defined, pretending everything worked!\n");
	return -1;
#endif
}

int multicastSocketJoinGroup(MulticastSocket multicastSocket, InetAddress groupIpAddress)
{
	struct ip_mreq multicastRequest;

	if(multicastSocket == NULL)
	{
		return -1;
	}

	if(multicastSocket->netIf == NULL)
	{
		return -1;
	}

	multicastRequest.imr_multiaddr.s_addr = groupIpAddress->value;
	
	//multicastRequest.imr_address.s_addr = multicastSocket->netIf->address->value;
	multicastRequest.imr_interface.s_addr = multicastSocket->netIf->address->value;

	//multicastRequest.imr_ifindex = multicastSocket->netIf->index;

	return setsockopt(multicastSocket->descriptor, IPPROTO_IP, IP_ADD_MEMBERSHIP, &multicastRequest, sizeof(multicastRequest)); 
}

int multicastSocketSend(MulticastSocket multicastSocket, DatagramPacket packet)
{
	struct sockaddr_in toAddress;
	int bytesSent = 0;
	struct timeval timeout;
	
	memset(&toAddress, 0, sizeof(toAddress));
	toAddress.sin_family = AF_INET;									// Set Internet Socket (sin), Family to: Address Family (AF) IPv4 (INET)
	toAddress.sin_addr.s_addr = packet->address->value;	// Set Internet Socket (sin), Address to: The packet ipAddressString
	toAddress.sin_port = htons(packet->port);						// Set Internet Socket (sin), Port to: the packet port
	
	timeout.tv_sec = 0;
	timeout.tv_usec = 1000; // Sleep at least one millisecond
							// TODO: This select is a temporary solution to give the hardware a small amount
							//		of time to process the data
	if(select(multicastSocket->descriptor + 1, NULL, NULL, NULL, &timeout) > -1)
	{
		bytesSent = sendto(multicastSocket->descriptor, (void *)packet->buffer, (size_t)packet->bufferSizeBytes, 0, (struct sockaddr *)&toAddress, sizeof(toAddress));
	}
	else
	{
		return -1;
	}
	
	return bytesSent;
}


int multicastSocketReceive(MulticastSocket multicastSocket, DatagramPacket packet)
{
	struct timeval *timeoutPtr = NULL;
	fd_set readSet;
	struct sockaddr_in fromAddress;
	socklen_t fromAddressLength;
	int bytesReceived = 0;
	
	memset(&fromAddress, 0, sizeof(fromAddress));
	
	if(!multicastSocket->blocking)
	{
		timeoutPtr = &multicastSocket->timeout;
	}
	
	FD_ZERO(&readSet);
	FD_SET(multicastSocket->descriptor, &readSet);

	if(select(multicastSocket->descriptor + 1, &readSet, NULL, NULL, timeoutPtr) > 0)
	{
		if(FD_ISSET(multicastSocket->descriptor, &readSet))
		{
			fromAddressLength = sizeof(fromAddress);
			bytesReceived = recvfrom(multicastSocket->descriptor, packet->buffer, packet->bufferSizeBytes, 0, (struct sockaddr*)&fromAddress, &fromAddressLength);
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

void multicastSocketSetTimeout(MulticastSocket multicastSocket, double timeoutSec)
{
	long sec, usec;
	
	sec = (long)timeoutSec;
	usec = (long)((timeoutSec - (double)sec) * 1.0e6);
			
	multicastSocket->timeout.tv_sec = sec;
	multicastSocket->timeout.tv_usec = usec;
	multicastSocket->blocking = 0;
}


