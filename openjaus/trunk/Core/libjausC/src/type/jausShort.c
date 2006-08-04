// File Name: jausShort.c
//
// Written By: Danny Kent (jaus AT dannykent DOT com), Tom Galluzzo (galluzzo AT gmail DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines all the basic JausShort funtionality, this should be primarily used through the JausType file and its methods

#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "cimar/jaus.h"

JausShort newJausShort(short val)
{
	return val;	
}

JausBoolean jausShortFromBuffer(JausShort *jShort, unsigned char *buf, unsigned int bufferSizeBytes)
{
	int i = 0;
	short tempShort = 0;
	
	if(bufferSizeBytes < JAUS_SHORT_SIZE_BYTES)
		return JAUS_FALSE;
	else
	{
		if(isHostBigEndian())
		{
			// swap bytes
			for(i = 0; i < JAUS_SHORT_SIZE_BYTES; i++)
				tempShort += (buf[i] << (JAUS_SHORT_SIZE_BYTES-i-1)*8);
		}
		else
			memcpy(&(tempShort), buf, JAUS_SHORT_SIZE_BYTES);
		
		*jShort = newJausShort(tempShort);
		return JAUS_TRUE;
	}
}

JausBoolean jausShortToBuffer(JausShort input, unsigned char *buf, unsigned int bufferSizeBytes)
{
	int i = 0;

	if(bufferSizeBytes < JAUS_SHORT_SIZE_BYTES)
		return JAUS_FALSE;
	else
	{
		if(isHostBigEndian())
		{
			// swap bytes
			for (i = 0; i < JAUS_SHORT_SIZE_BYTES; i++)
				buf[i] = ((input >> (JAUS_SHORT_SIZE_BYTES-i-1)*8) & 0xFF); // 8 bits per byte
		}
		else
			memcpy(buf, &input, JAUS_SHORT_SIZE_BYTES);
		
		return JAUS_TRUE;
	}
}

double jausShortToDouble(JausShort input, double min, double max)
{
	// BUG: What to do when max < min
	double scaleFactor = (max-min)/JAUS_SHORT_RANGE;;
	double bias = (max+min)/2.0; 
    
	return input*scaleFactor + bias;
}

JausShort jausShortFromDouble(double value, double min, double max)
{
	//limit value between min and max Short values
	double scaleFactor = (max-min)/JAUS_SHORT_RANGE;
	double bias = (max+min)/2.0;
	
	// limit real number between min and max
	if(value < min) value = min;
	if(value > max) value = max;
		
	// calculate rounded integer value
	return newJausShort((short) rint((value - bias)/scaleFactor));
}
