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
// File Name: inetAddress.c
//
// Written By: Tom Galluzzo (galluzzo AT gmail DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file describes the functionality associated with a InetAddress object. 
// Inspired by the class of the same name in the JAVA language.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>

#include "cimar.h"

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
	
	address = (InetAddress) malloc( sizeof(InetAddressStruct) );
	if( address == NULL )
	{
		return NULL;
	}
	
	// Get the localhost entry, which allows us to connect to the loopback ip interface
	localhost = gethostbyname("localhost");
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
	
	return sprintf(string, "%s", inet_ntoa(inAddress) );
}
