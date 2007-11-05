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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "multicastSocket.h"

MulticastSocket multicastSocketCreate(short port, InetAddress ipAddress)
{
	MulticastSocket multicastSocket;
	struct sockaddr_in address;
	socklen_t addressLength = sizeof(address);
	
#ifdef WIN32	
	// Initialize the socket subsystem
	WSADATA wsaData;
	int err;
	err = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if(err != 0)
	{
		printf("WSA Startup Error\n");
		return NULL;
	}
#endif

	multicastSocket = (MulticastSocket)malloc( sizeof(MulticastSocketStruct) );
	if(multicastSocket == NULL)
	{
		printf("Malloc Error\n");
		return NULL;
	}
	
	// Open a socket with: Protocol Family (PF) IPv4, of Datagram Socket Type, and using UDP IP protocol explicitly
	multicastSocket->descriptor = (int) socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP); 
	if(multicastSocket->descriptor == INVALID_SOCKET)
	{
		int ev = WSAGetLastError();
		printf("INVALID_SOCKET %d\n", ev);
		return NULL;
	}

	memset(&address, 0, sizeof(address));			// Clear the data structure to zero
	address.sin_family = AF_INET;					// Set Internet Socket (sin), Family to: Address Family (AF) IPv4 (INET)
	address.sin_addr.s_addr = ipAddress->value;	// Set Internet Socket (sin), Address to: The ipAddressString argument
	address.sin_port = htons(port);					// Set Internet Socket (sin), Port to: the port argument

	// Bind our open socket to a free port on the localhost, with our defined ipAddress
	if(bind(multicastSocket->descriptor, (struct sockaddr *)&address, sizeof(address)))
	{
		printf("Error: Cannot bind to %s:%d\n", inet_ntoa(address.sin_addr), ntohs(address.sin_port));
		CLOSE_SOCKET(multicastSocket->descriptor);
		return NULL;
	}

	if(getsockname(multicastSocket->descriptor, (struct sockaddr *)&address, &addressLength))
	{
		CLOSE_SOCKET(multicastSocket->descriptor);
		return NULL;
	}

	// Let the operating system decide which interface to send multicast on... DK
#ifdef WIN32
	if(setsockopt(multicastSocket->descriptor, IPPROTO_IP, IP_MULTICAST_IF, (char *)&ipAddress->value, sizeof(ipAddress->value)))
	{
		CLOSE_SOCKET(multicastSocket->descriptor);
		return NULL;
	}
#else
	if(setsockopt(multicastSocket->descriptor, IPPROTO_IP, IP_MULTICAST_IF, &ipAddress->value, sizeof(ipAddress->value)))
	{
		CLOSE_SOCKET(multicastSocket->descriptor);
		return NULL;
	}
#endif

	multicastSocket->address = ipAddress;
	multicastSocket->port = ntohs(address.sin_port);
	multicastSocket->timeout.tv_sec = 0;
	multicastSocket->timeout.tv_usec = 0;
	multicastSocket->blocking = 1;
	
	return multicastSocket;
}

void multicastSocketDestroy(MulticastSocket multicastSocket)
{
	CLOSE_SOCKET(multicastSocket->descriptor);
	free(multicastSocket);

#ifdef WIN32	
	// Initialize the socket subsystem
	WSACleanup();
#endif

}
//
//int multicastSocketSetNetIf(MulticastSocket multicastSocket, NetworkInterface netIf)
//{
//	if(multicastSocket == NULL)
//	{
//		return -1;
//	}
//
//	multicastSocket->netIf = netIf;
//
//#ifdef SO_BINDTODEVICE
//	return setsockopt(multicastSocket->descriptor, SOL_SOCKET, SO_BINDTODEVICE, netIf->name, sizeof(netIf->name) + 1);
//#else
//	fprintf(stderr, "multicastSocket.c: SO_BINDTODEVICE not defined, pretending everything worked!\n");
//	return -1;
//#endif
//}
//

int multicastSocketJoinGroup(MulticastSocket multicastSocket, InetAddress groupIpAddress)
{
	struct ip_mreq multicastRequest;

	if(multicastSocket == NULL)
	{
		return -1;
	}

	//if(multicastSocket->netIf == NULL)
	//{
	//	return -1;
	//}

	multicastRequest.imr_multiaddr.s_addr = groupIpAddress->value;
	
	//multicastRequest.imr_address.s_addr = multicastSocket->netIf->address->value;
	multicastRequest.imr_interface.s_addr = multicastSocket->address->value;

	//multicastRequest.imr_ifindex = multicastSocket->netIf->index;

#ifdef WIN32
	return setsockopt(multicastSocket->descriptor, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char *)&multicastRequest, sizeof(multicastRequest)); 
#else
	return setsockopt(multicastSocket->descriptor, IPPROTO_IP, IP_ADD_MEMBERSHIP, &multicastRequest, sizeof(multicastRequest)); 
#endif

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
		bytesSent = sendto(multicastSocket->descriptor, (void *)packet->buffer, packet->bufferSizeBytes, 0, (struct sockaddr *)&toAddress, sizeof(toAddress));
	}
	else
	{
		return -1;
	}
	
	return bytesSent;
}


int multicastSocketReceive(MulticastSocket multicastSocket, DatagramPacket packet)
{
	struct timeval timeout;
	struct timeval *timeoutPtr = NULL;
	fd_set readSet;
	struct sockaddr_in fromAddress;
	socklen_t fromAddressLength;
	int bytesReceived = 0;
	
	memset(&fromAddress, 0, sizeof(fromAddress));
	
	if(!multicastSocket->blocking)
	{
		timeout = multicastSocket->timeout;
		timeoutPtr = &timeout;
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

int multicastSocketSetTTL(MulticastSocket multicastSocket, unsigned int ttl)
{
	if(ttl > 255)
	{
		ttl = 255;
	}

	if(ttl < 1)
	{
		ttl = 1;
	}

#ifdef WIN32
	return setsockopt(multicastSocket->descriptor, IPPROTO_IP, IP_MULTICAST_TTL, (char *)&ttl, sizeof(unsigned int)); 
#else
	return setsockopt(multicastSocket->descriptor, IPPROTO_IP, IP_MULTICAST_TTL, &ttl, sizeof(unsigned int)); 
#endif
	
}

int multicastSocketSetLoopback(MulticastSocket multicastSocket, unsigned int loop)
{
#ifdef WIN32
	return setsockopt(multicastSocket->descriptor, IPPROTO_IP, IP_MULTICAST_LOOP, (char *)&loop, sizeof(unsigned int)); 
#else
	return setsockopt(multicastSocket->descriptor, IPPROTO_IP, IP_MULTICAST_LOOP, &loop, sizeof(unsigned int)); 
#endif
}

	