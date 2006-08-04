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
