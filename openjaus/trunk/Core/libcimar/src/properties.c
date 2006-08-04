// File Name: properties.c
//
// Written By: Tom Galluzzo (galluzzo AT gmail DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description:	This file describes the functionality associated with a Properties object.
// Inspired by the class of the same name in the JAVA language.

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cimar.h"

Properties propertiesCreate(void)
{
	return NULL;
}

void propertiesDestroy(Properties properties)
{
	Properties deadProperty;
	
	while(properties)
	{
		free(properties->property);
		free(properties->value);
		deadProperty = properties;
		properties = properties->nextProperty;
		free(deadProperty);
	}
}

#ifdef __APPLE__
ssize_t getline(char **buf, size_t *n, FILE *file)
{
	ssize_t size = 0;
	int c;
	while (1)
	{
		c = fgetc(file);
		// check if EOF
		if (c == EOF || c == '\n')
			break;

		size++;
	}
 
	if (size > 0)
	{
		if (c == '\n')
		{
			size += 1; // +1 for the \n
		}
		
		if (fseek(file, -size, SEEK_CUR))
		{
			return -1;getline
		}
		
		if (buf == NULL)
		{
		 *buf = (char*)malloc(size+1 * sizeof(char)); // +1 for xtra \0
		}
		else if (size != *n)
		{
			*buf = (char*)realloc(*buf, size+1 * sizeof(char));
			*n = size;
		}
	
		fgets(*buf, size+1, file);
	
		return size; // success
 	}
 	
 	return -1;
}
#endif

Properties propertiesLoad(Properties properties, FILE *file)
{
	const char delimeters[] = "\t\n\r=";
	char *buf = NULL;
	char *tempProperty, *tempValue;
	size_t bufSizeChars = 0;
	Properties property = properties;
	Properties firstProperty = properties;
	
	while( getline(&buf, &bufSizeChars, file ) > -1)
	{
		tempProperty = strtok(buf, delimeters);
		tempValue = strtok(NULL, delimeters);
		if(tempProperty && tempProperty[0] != '#')
		{
			if(property)
			{
				property->nextProperty = (Properties)malloc( sizeof(PropertyStruct) );
				property = property->nextProperty;

				property->property = (char *)malloc( strlen(tempProperty) + 1 ); 
				sprintf(property->property, "%s", tempProperty);

				property->value = (char *)malloc( strlen(tempValue) + 1 ); 
				sprintf(property->value, "%s", tempValue);

				property->nextProperty = NULL;
			}
			else
			{
				property = (Properties)malloc( sizeof(PropertyStruct) );

				property->property = (char *)malloc( strlen(tempProperty) + 1 );
				sprintf(property->property, "%s", tempProperty);

				property->value = (char *)malloc( strlen(tempValue) + 1 ); 
				sprintf(property->value, "%s", tempValue);

				property->nextProperty = NULL;
				firstProperty = property;
			}
			// printf("%s = %s\n", tempProperty, tempValue);	
		}
	}
	
	if(buf)
	{
		free(buf);
	}
	
	return firstProperty; 
}

char *propertiesGetProperty(Properties properties, char * testProperty)
{
	while(properties)
	{
		if(strcmp(properties->property, testProperty))
		{
			properties = properties->nextProperty;
		}
		else
		{
			return properties->value;
		}
	}
	
	return NULL;
}
