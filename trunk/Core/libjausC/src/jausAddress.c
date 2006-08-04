// File Name: jausAddress.c
//
// Written By: Danny Kent (jaus AT dannykent DOT com), Tom Galluzzo (galluzzo AT gmail DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines the basic functions for use with the JausAddress of each component

#include <stdio.h>
#include <stdlib.h>
#include "cimar/jaus.h"

JausAddress jausAddressCreate(void)
{
	JausAddress address;
	
	address = (JausAddress)malloc( sizeof(JausAddressStruct) );
	if(address == NULL)
	{
		return NULL;
	}
	
	// Init Values
	address->id = 0;
	
	return address;
}

void jausAddressDestroy(JausAddress address)
{
	free(address);
}


int jausAddressToString(JausAddress address, char *buf)
{
	return sprintf(buf, "%d.%d.%d.%d", address->subsystem, address->node, address->component, address->instance);
}

