// File Name: properties.h
//
// Written By: Tom Galluzzo (galluzzo AT gmail DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description:	This file describes the functionality associated with a Properties object.
// Inspired by the class of the same name in the JAVA language.

#ifndef PROPERTIES_H
#define PROPERTIES_H

#include <stdio.h>

typedef struct propertyStruct
{
	char *property;
	char *value;
	struct propertyStruct *nextProperty;
}PropertyStruct;

typedef PropertyStruct *Properties;

Properties propertiesCreate(void);
void propertiesDestroy(Properties);
Properties propertiesLoad(Properties, FILE *);
char *propertiesGetProperty(Properties, char *);

#endif // PROPERTIES_H
