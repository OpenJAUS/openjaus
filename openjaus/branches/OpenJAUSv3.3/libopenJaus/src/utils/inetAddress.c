/*****************************************************************************
 *  Copyright (c) 2008, OpenJAUS.com
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
// File Name: inetAddress.c
//
// Written By: Tom Galluzzo (galluzzo AT gmail DOT com)
//
// Version: 3.3 BETA
//
// Date: 04/15/08
//
// Description: This file describes the functionality associated with a InetAddress object. 
// Inspired by the class of the same name in the JAVA language.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils/inetAddress.h"

#ifdef WIN32
	const char *inet_ntop(int af, const void *src, char *dst, socklen_t cnt);
	int inet_pton(int af, const char *src, void *dst);
#endif 

InetAddress inetAddressCreate(void)
{
	return (InetAddress) malloc( sizeof(InetAddressStruct) );
}

void inetAddressDestroy(InetAddress address)
{
	free(address);
}

InetAddress inetAddressGetLocalHost(void)
{
	struct hostent *localhost;
	InetAddress address;

#ifdef WIN32	
	// Initialize the socket subsystem
	WSADATA wsaData;
	int err;
	err = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if(err != 0)
	{
		return NULL;
	}
#endif
	
	address = (InetAddress) malloc( sizeof(InetAddressStruct) );
	if( address == NULL )
	{
		return NULL;
	}
	
	// Get the localhost entry, which allows us to connect to the loopback ip interface
	localhost = gethostbyname("127.0.0.1");
	if(localhost == NULL)
	{
		return NULL;
	}
	else
	{
		memcpy(address, localhost->h_addr_list[0], sizeof(InetAddressStruct));
		return address;
	}
}

InetAddress inetAddressGetByName(char *nameString)
{
	struct hostent *host;
	InetAddress address;
	
#ifdef WIN32	
	// Initialize the socket subsystem
	WSADATA wsaData;
	int err;
	err = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if(err != 0)
	{
		return NULL;
	}
#endif

	address = (InetAddress) malloc( sizeof(InetAddressStruct) );
	if( address == NULL )
	{
		return NULL;
	}
	
	host = gethostbyname(nameString);
	if(host == NULL)
	{
		return NULL;
	}
	else
	{
		memcpy(address, host->h_addr_list[0], sizeof(InetAddressStruct));
		return address;
	}
}

InetAddress inetAddressGetByString(char *addressString)
{
	struct hostent *host;
	InetAddress address;
	
#ifdef WIN32	
	// Initialize the socket subsystem
	WSADATA wsaData;
	int err;
	err = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if(err != 0)
	{
		return NULL;
	}
#endif

	address = (InetAddress) malloc( sizeof(InetAddressStruct) );
	if( address == NULL )
	{
		return NULL;
	}
	
	host = gethostbyname(addressString);
	if(host == NULL)
	{
		return NULL;
	}
	else
	{
		memcpy(address, host->h_addr_list[0], sizeof(InetAddressStruct));
		return address;
	}
}

int inetAddressToString(InetAddress address, char *string)
{
	struct in_addr inAddress;
	
	memset(&inAddress, 0, sizeof(inAddress));
	inAddress.s_addr = address->value;
	
	return sprintf(string, "%s", inet_ntoa(inAddress));
}

void inetAddressToBuffer(InetAddress address, char *string, int length)
{
	struct in_addr inAddress;
	
	memset(&inAddress, 0, sizeof(inAddress));
	inAddress.s_addr = address->value;
	
	inet_ntop(AF_INET, &inAddress, string, length);
}

// Winsock does not have support for inet_ntop or inet_pton
// These functions were found online at the following URL: http://osdir.com/ml/network.ipv6.general/2005-09/msg00030.html
// These provide an implementation of inet_ntop and inet_pton for Windows cross-platform compatibility

#ifdef WIN32
const char *inet_ntop(int af, const void *src, char *dst, socklen_t cnt)
{
    if (af == AF_INET)
    {
        struct sockaddr_in in;
        memset(&in, 0, sizeof(in));
        in.sin_family = AF_INET;
        memcpy(&in.sin_addr, src, sizeof(struct in_addr));
        getnameinfo((struct sockaddr *)&in, sizeof(struct sockaddr_in), dst, cnt, NULL, 0, NI_NUMERICHOST);
        return dst;
    }
    else if (af == AF_INET6)
    {
        struct sockaddr_in6 in;
        memset(&in, 0, sizeof(in));
        in.sin6_family = AF_INET6;
        memcpy(&in.sin6_addr, src, sizeof(struct in_addr6));
        getnameinfo((struct sockaddr *)&in, sizeof(struct sockaddr_in6), dst, cnt, NULL, 0, NI_NUMERICHOST);
        return dst;
    }
    return NULL;
}

int inet_pton(int af, const char *src, void *dst)
{
    struct addrinfo hints, *res, *ressave;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = af;

    if (getaddrinfo(src, NULL, &hints, &res) != 0)
    {
        // TODO: Log Error
		//dolog(LOG_ERR, "Couldn't resolve host %s\n", src);
        return -1;
    }

    ressave = res;

    while (res)
    {
        memcpy(dst, res->ai_addr, res->ai_addrlen);
        res = res->ai_next;
    }

    freeaddrinfo(ressave);
    return 0;
}

#endif
