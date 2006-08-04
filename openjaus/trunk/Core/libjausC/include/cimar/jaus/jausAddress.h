// File Name: jausAddress.h
//
// Written By: Danny Kent (jaus AT dannykent DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines the basic JausAddress of each component

#ifndef JAUS_ADDRESS_H
#define JAUS_ADDRESS_H

#include "cimar/jaus.h"

#define JAUS_INVALID_INSTANCE 		0
#define JAUS_INVALID_COMPONENT 		0
#define JAUS_INVALID_NODE 			0
#define JAUS_INVALID_SUBSYSTEM 		0

#define JAUS_BROADCAST 				255
#define JAUS_BROADCAST_INSTANCE 	255
#define JAUS_BROADCAST_COMPONENT 	255
#define JAUS_BROADCAST_NODE 		255
#define JAUS_BROADCAST_SUBSYSTEM 	255

#define JAUS_NODE_MANAGER_COMPONENT 	1
#define JAUS_PRIMARY_NODE_MANAGER_NODE 	1

typedef union
{
	struct
	{
		JausByte instance;
		JausByte component;
		JausByte node;
		JausByte subsystem;
	};
	JausUnsignedInteger id;
}JausAddressStruct;

typedef JausAddressStruct *JausAddress;

JausAddress jausAddressCreate(void);
void jausAddressDestroy(JausAddress);

int jausAddressToString(JausAddress, char *);

#endif // JAUS_ADDRESS_H
