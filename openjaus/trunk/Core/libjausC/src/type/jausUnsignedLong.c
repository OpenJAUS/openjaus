// File Name: jausUnsignedLong.c
//
// Written By: Danny Kent (jaus AT dannykent DOT com), Tom Galluzzo (galluzzo AT gmail DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines all the basic JausUnsignedLong funtionality, this should be primarily used through the JausType file and its methods

#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "cimar/jaus.h"

JausUnsignedLong newJausUnsignedLong(unsigned long long val)
{
	return val;
}

JausBoolean jausUnsignedLongFromBuffer(JausUnsignedLong *jULong, unsigned char *buf, unsigned int bufferSizeBytes)
{
	int i = 0;
	unsigned long tempULong = 0;
	
	if(bufferSizeBytes < JAUS_UNSIGNED_LONG_SIZE_BYTES)
		return JAUS_FALSE;
	else
	{
		if(isHostBigEndian())
		{
			// swap bytes
			for(i = 0; i < JAUS_UNSIGNED_LONG_SIZE_BYTES; i++)
				tempULong += (buf[i] << (JAUS_UNSIGNED_LONG_SIZE_BYTES-i-1)*8);
		}
		else
			memcpy(&(tempULong), buf, JAUS_UNSIGNED_LONG_SIZE_BYTES);
	
		*jULong = newJausUnsignedLong(tempULong);
		return JAUS_TRUE;
	}
}

JausBoolean jausUnsignedLongToBuffer(JausUnsignedLong input, unsigned char *buf, unsigned int bufferSizeBytes)
{
	int i = 0;
	if(bufferSizeBytes < JAUS_UNSIGNED_LONG_SIZE_BYTES)
		return JAUS_FALSE;
	else
	{
		if(isHostBigEndian())
		{
			// swap bytes
			for (i = 0; i < JAUS_UNSIGNED_LONG_SIZE_BYTES; i++)
				buf[i] = ((input >> (JAUS_UNSIGNED_LONG_SIZE_BYTES-i-1)*8) & 0xFF); // 8 bits per byte
		}
		else
			memcpy(buf, &input, JAUS_UNSIGNED_LONG_SIZE_BYTES);
		
		return JAUS_TRUE;
	}
}

double jausUnsignedLongToDouble(JausUnsignedLong input, double min, double max)
{
	// BUG: What to do when max < min
	double scaleFactor = (max-min)/JAUS_UNSIGNED_LONG_RANGE;
	double bias = min; 

	return input*scaleFactor + bias;
}

JausUnsignedLong jausUnsignedLongFromDouble(double value, double min, double max)
{
	//limit value between min and max UnsignedLong values
	double scaleFactor = (max-min)/JAUS_UNSIGNED_LONG_RANGE;
	double bias = min;
	
	// limit real number between min and max
	if(value < min) value = min;
	if(value > max) value = max;
		
	// calculate rounded integer value
	return newJausUnsignedLong((unsigned long) rint((value - bias)/scaleFactor));
}
