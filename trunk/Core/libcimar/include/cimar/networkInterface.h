// File Name: networkInterface.h
//
// Written By: Tom Galluzzo (galluzzo AT gmail DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description:	This file describes the functionality associated with a NetworkInterface object.
// Inspired by the class of the same name in the JAVA language.

#ifndef NETWORK_INTERFACE_H
#define NETWORK_INTERFACE_H

typedef struct
{
	int index;
	char *name;
	InetAddress address;
}NetworkInterfaceStruct;

typedef NetworkInterfaceStruct *NetworkInterface;

NetworkInterface networkInterfaceGetByName(char * name);
void networkInterfaceDestroy(NetworkInterface);
void networkInterfaceEnermerate(void);

#endif // NETWORK_INTERFACE_H
