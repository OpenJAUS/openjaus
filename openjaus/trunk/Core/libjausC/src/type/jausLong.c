// File Name: jausLong.c
//
// Written By: Danny Kent (jaus AT dannykent DOT com), Tom Galluzzo (galluzzo AT gmail DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines all the basic JausLong funtionality, this should be primarily used through the JausType file and its methods

#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "cimar/jaus.h"

JausLong newJausLong(long long val)
{
	return val;
}

JausBoolean jausLongFromBuffer(JausLong *jLong, unsigned char *buf, unsigned int bufferSizeBytes)
{
	int i = 0;
	long tempLong = 0;
	
	if(bufferSizeBytes < JAUS_LONG_SIZE_BYTES)
	{
		return JAUS_FALSE;
	}
	else
	{	
		if(isHostBigEndian())
		{
			// swap bytes
			for(i = 0; i < JAUS_LONG_SIZE_BYTES; i++)
			{
				tempLong += (buf[i] << (JAUS_LONG_SIZE_BYTES-i-1)*8);
			}
		}
		else
		{
			memcpy(&(tempLong), buf, JAUS_LONG_SIZE_BYTES);
		}
		
		*jLong = newJausLong(tempLong);
		return JAUS_TRUE;
	}
}

JausBoolean jausLongToBuffer(JausLong input, unsigned char *buf, unsigned int bufferSizeBytes)
{
	int i = 0;

	if(bufferSizeBytes < JAUS_LONG_SIZE_BYTES)
	{
		return JAUS_FALSE;
	}
	else
	{	
		if(isHostBigEndian())
		{
			// swap bytes
			for (i = 0; i < JAUS_LONG_SIZE_BYTES; i++)
			{
				buf[i] = ((input >> (JAUS_LONG_SIZE_BYTES-i-1)*8) & 0xFF); // 8 bits per byte
			}
		}
		else
		{
			memcpy(buf, &input, JAUS_LONG_SIZE_BYTES);
		}
		
		return JAUS_TRUE;
	}
}

double jausLongToDouble(JausLong input, double min, double max)
{
	// BUG: What to do when max < min
	double scaleFactor = (max-min)/JAUS_LONG_RANGE;
	double bias = (max+min)/2.0; 
		
	return input*scaleFactor + bias;
}

JausLong jausLongFromDouble(double value, double min, double max)
{
	// BUG: What to do when max < min
	//limit value between min and max Long values
	double scaleFactor = (max-min)/JAUS_LONG_RANGE;
	double bias = (max+min)/2.0;
	
	// limit real number between min and max
	if(value < min) value = min;
	if(value > max) value = max;
		
	// return rounded integer value
	return newJausLong((long) rint((value - bias)/scaleFactor));
}
