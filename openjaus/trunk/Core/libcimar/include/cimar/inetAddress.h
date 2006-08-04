// File Name: inetAddress.h
//
// Written By: Tom Galluzzo (galluzzo AT gmail DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file describes the functionality associated with a InetAddress object. 
// Inspired by the class of the same name in the JAVA language.

#ifndef INET_ADDRESS_H
#define INET_ADDRESS_H

typedef struct
{
	unsigned int value;
}InetAddressStruct;

typedef InetAddressStruct * InetAddress;

InetAddress inetAddressCreate(void);
void inetAddressDestroy(InetAddress);
InetAddress inetAddressGetLocalHost(void);
InetAddress inetAddressGetByName(char *);
InetAddress inetAddressGetByString(char *);
int inetAddressToString(InetAddress, char *);

#endif // INET_ADDRESS_H
