// File Name: jausUnsignedInteger.c
//
// Written By: Danny Kent (jaus AT dannykent DOT com), Tom Galluzzo (galluzzo AT gmail DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines all the basic JausUnsignedInteger funtionality, this should be primarily used through the JausType file and its methods

#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "cimar/jaus.h"

JausUnsignedInteger newJausUnsignedInteger(unsigned int val)
{
	return val;
}

JausBoolean jausUnsignedIntegerFromBuffer(JausUnsignedInteger *jUint, unsigned char *buf, unsigned int bufferSizeBytes)
{
	int i = 0;
	unsigned int tempUInt;
	
	if(bufferSizeBytes < JAUS_UNSIGNED_INTEGER_SIZE_BYTES)
		return JAUS_FALSE;
	else
	{
		if(isHostBigEndian())
		{
			// swap bytes
			for(i = 0; i < JAUS_UNSIGNED_INTEGER_SIZE_BYTES; i++)
				tempUInt += (buf[i] << (JAUS_UNSIGNED_INTEGER_SIZE_BYTES-i-1)*8);
		}
		else
			memcpy(&(tempUInt), buf, JAUS_UNSIGNED_INTEGER_SIZE_BYTES);
	
		*jUint = newJausUnsignedInteger(tempUInt);
		return JAUS_TRUE;
	}
}

JausBoolean jausUnsignedIntegerToBuffer(JausUnsignedInteger input, unsigned char *buf, unsigned int bufferSizeBytes)
{
	int i = 0;

	if(bufferSizeBytes < JAUS_UNSIGNED_INTEGER_SIZE_BYTES)
		return JAUS_FALSE;
	else
	{
		if(isHostBigEndian())
		{
			// swap bytes
			for (i = 0; i < JAUS_UNSIGNED_INTEGER_SIZE_BYTES; i++)
				buf[i] = ((input >> (JAUS_UNSIGNED_INTEGER_SIZE_BYTES-i-1)*8) & 0xFF); // 8 bits per byte
		}
		else
			memcpy(buf, &input, JAUS_UNSIGNED_INTEGER_SIZE_BYTES);
		
		return JAUS_TRUE;
	}
}

double jausUnsignedIntegerToDouble(JausUnsignedInteger input, double min, double max)
{
	// BUG: What to do when max < min
	double scaleFactor = (max-min)/JAUS_UNSIGNED_INTEGER_RANGE;
	double bias = min;

	return input*scaleFactor + bias;
}

JausUnsignedInteger jausUnsignedIntegerFromDouble(double value, double min, double max)
{
	//limit value between min and max UnsignedInteger values
	double scaleFactor = (max-min)/JAUS_UNSIGNED_INTEGER_RANGE;
	double bias = min;
	
	// limit real number between min and max
	if(value < min) value = min;
	if(value > max) value = max;
		
	// calculate rounded integer value
	return newJausUnsignedInteger((unsigned int) rint((value - bias)/scaleFactor));
}
