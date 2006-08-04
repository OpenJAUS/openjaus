// File Name: jausInteger.c
//
// Written By: Danny Kent (jaus AT dannykent DOT com), Tom Galluzzo (galluzzo AT gmail DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines all the basic JausFloat funtionality, this should be primarily used through the JausType file and its methods

#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "cimar/jaus.h"

JausInteger newJausInteger(int val)
{
	return val;
}

JausBoolean jausIntegerFromBuffer(JausInteger *jInteger, unsigned char *buf, unsigned int bufferSizeBytes)
{
	int i = 0;
	int tempInt = 0;
	
	if(bufferSizeBytes < JAUS_INTEGER_SIZE_BYTES)
	{
		return JAUS_FALSE;
	}
	else
	{
		if(isHostBigEndian())
		{
			// swap bytes
			for(i = 0; i < JAUS_INTEGER_SIZE_BYTES; i++)
			{
				tempInt += (buf[i] << (JAUS_INTEGER_SIZE_BYTES-i-1)*8);
			}
		}
		else
		{
			memcpy(&(tempInt), buf, JAUS_INTEGER_SIZE_BYTES);
		}
		
		*jInteger = newJausInteger(tempInt);
		return JAUS_TRUE;
	}
}

JausBoolean jausIntegerToBuffer(JausInteger input, unsigned char *buf, unsigned int bufferSizeBytes)
{
	int i = 0;

	if(bufferSizeBytes < JAUS_INTEGER_SIZE_BYTES)
	{
		return JAUS_FALSE;
	}
	else
	{
		if(isHostBigEndian())
		{
			// swap bytes
			for (i = 0; i < JAUS_INTEGER_SIZE_BYTES; i++)
			{
				buf[i] = ((input >> (JAUS_INTEGER_SIZE_BYTES-i-1)*8) & 0xFF); // 8 bits per byte
			}
		}
		else
		{
			memcpy(buf, &(input), JAUS_INTEGER_SIZE_BYTES);
		}
		return JAUS_TRUE;
	}
}

double jausIntegerToDouble(JausInteger input, double min, double max)
{
	// BUG: What to do when max < min
	double scaleFactor = (max-min)/JAUS_INTEGER_RANGE;
	double bias = (max+min)/2.0; 
		
	return input*scaleFactor + bias;
}

JausInteger jausIntegerFromDouble(double value, double min, double max)
{
	//limit value between min and max Int values
	double scaleFactor = (max-min)/JAUS_INTEGER_RANGE;
	double bias = (max+min)/2.0;
	
	// limit real number between min and max
	if(value < min) value = min;
	if(value > max) value = max;
		
	// return rounded integer value
	return newJausInteger((int) rint((value - bias)/scaleFactor));
}
