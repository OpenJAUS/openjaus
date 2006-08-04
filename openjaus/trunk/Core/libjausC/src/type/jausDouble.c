// File Name: jausDouble.c
//
// Written By: Danny Kent (jaus AT dannykent DOT com), Tom Galluzzo (galluzzo AT gmail DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines all the basic JausDouble funtionality, this should be primarily used through the JausType file and its methods

#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "cimar/jaus.h"

JausDouble newJausDouble(double val)
{
	return val;
}

JausBoolean jausDoubleFromBuffer(JausDouble *jDouble, unsigned char *buf, unsigned int bufferSizeBytes)
{
	int i = 0;
	unsigned long tempLong = 0;
	double tempDouble = 0.0;
	
	if(bufferSizeBytes < JAUS_DOUBLE_SIZE_BYTES)
	{
		return JAUS_FALSE; // insufficient data in buffer
	}
	else
	{
		if(isHostBigEndian())
		{
			// swap bytes
			for(i = 0; i < JAUS_DOUBLE_SIZE_BYTES; i++)
			{
				tempLong += (buf[i] << (JAUS_DOUBLE_SIZE_BYTES-i-1)*8);
			}
			memcpy(&(tempDouble), &(tempLong), JAUS_DOUBLE_SIZE_BYTES);
		}
		else
		{
			memcpy(&tempDouble, buf, JAUS_DOUBLE_SIZE_BYTES);
		}
		
		*jDouble = newJausDouble(tempDouble);
		return JAUS_TRUE;
	}
}

JausBoolean jausDoubleToBuffer(JausDouble input, unsigned char *buf, unsigned int bufferSizeBytes)
{
	int i = 0;
	unsigned long tempLong;

	if(bufferSizeBytes < JAUS_DOUBLE_SIZE_BYTES)
	{
		return JAUS_FALSE; // insufficient room in buffer
	}
	else
	{
		
		if(isHostBigEndian())
		{
			memcpy(&(tempLong), &(input), JAUS_DOUBLE_SIZE_BYTES);
			// swap bytes
			for (i = 0; i < JAUS_DOUBLE_SIZE_BYTES; i++)
			{
				buf[i] = ((tempLong >> (JAUS_DOUBLE_SIZE_BYTES-i-1)*8) & 0xFF); // 8 bits per byte
			}
		}
		else
		{
			memcpy(buf, &(input), JAUS_DOUBLE_SIZE_BYTES);
		}
			
		return JAUS_TRUE;
	}
}

