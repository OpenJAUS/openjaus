// File Name: networkInterface.c
//
// Written By: Tom Galluzzo (galluzzo AT gmail DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description:	This file describes the functionality associated with a NetworkInterface object.
// Inspired by the class of the same name in the JAVA language.

#include <unistd.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <net/if.h>
#include <stdio.h>

#include "cimar.h"

#define MAX_NUM_INTERFACES	16

NetworkInterface networkInterfaceGetByName(char * name)
{
	NetworkInterface netIf;
	int sock, netifCount, i;
	struct sockaddr_in *address;
	struct ifconf ifConfig;
	struct ifreq req[MAX_NUM_INTERFACES];
	
	if(name == NULL)
	{
		return NULL;
	}
	
	netIf = (NetworkInterface)malloc( sizeof( NetworkInterfaceStruct ) );
	if( netIf == NULL )
	{
		return NULL;
	}

	sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if( sock < 0 )
	{
		return NULL;
	}
	
	ifConfig.ifc_len = MAX_NUM_INTERFACES * sizeof(struct ifreq);
	ifConfig.ifc_req = req;
	if( ioctl(sock, SIOCGIFCONF, &ifConfig) < 0)
	{
		close(sock);
		return NULL;
	}
	
	netifCount = ifConfig.ifc_len / sizeof( struct ifreq );
	
	for(i=0; i<netifCount; i++)
	{
		if( !strcmp(req[i].ifr_name, name) )
		{
			netIf->name = (char *)malloc( strlen(req[i].ifr_name) + 1 );
			sprintf(netIf->name, "%s", req[i].ifr_name);
			
			address = (struct sockaddr_in *) &(req[i].ifr_addr);
			netIf->address = inetAddressGetByName( inet_ntoa(address->sin_addr) );

			netIf->index = i;
			
			close(sock);
			return netIf;
		}
	}
	
	free(netIf);
	close(sock);
	return NULL;
}

void networkInterfaceDestroy(NetworkInterface netIf)
{
	if( netIf == NULL )
	{
		return;
	}
	
	inetAddressDestroy(netIf->address);
	free(netIf->name);
	free(netIf);
}

void networkInterfaceEnermerate(void)
{
	int sock, netifCount, i;
	struct sockaddr_in *address;
	struct ifconf netif;
	struct ifreq req[10];
	
	netif.ifc_len = 10 * sizeof(struct ifreq);
	netif.ifc_req = req;
	
	sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
	
	ioctl(sock, SIOCGIFCONF, &netif);
	
	netifCount = netif.ifc_len / sizeof( struct ifreq );
	printf("Network IF count: %d\n", netifCount);
	
	for(i=0; i<netifCount; i++)
	{
		printf("Network Interface #%d\n", i+1);
		printf("\tName = %s\n", req[i].ifr_name);
		
		address = (struct sockaddr_in *) &(req[i].ifr_addr);
		printf("\tAddress = %s\n", inet_ntoa(address->sin_addr) );
	}
	
	close(sock);
}

