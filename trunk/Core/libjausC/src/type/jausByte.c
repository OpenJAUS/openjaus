// File Name: jausByte.c
//
// Written By: Danny Kent (jaus AT dannykent DOT com), Tom Galluzzo (galluzzo AT gmail DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines all the basic JausByte funtionality, this should be primarily used through the 
// JausType file and its methods

#include <math.h>
#include <stdlib.h>
#include "cimar/jaus.h"

JausByte newJausByte(unsigned char value)
{
	return value;
}

JausBoolean jausByteFromBuffer(JausByte *jByte, unsigned char *buf, unsigned int bufferSizeBytes)
{
	if(bufferSizeBytes < JAUS_BYTE_SIZE_BYTES)
	{
		return JAUS_FALSE; // not enough data in buffer
	}
	else
	{
		*jByte = newJausByte((unsigned char)buf[0]);
		return JAUS_TRUE;
	}	
}

JausBoolean jausByteToBuffer(JausByte input, unsigned char *buf, unsigned int bufferSizeBytes)
{
	if(bufferSizeBytes < JAUS_BYTE_SIZE_BYTES) 
	{
		return JAUS_FALSE; // not enough room
	}
	else
	{
		buf[0] = input;
		return JAUS_TRUE;
	}
}

double jausByteToDouble(JausByte input, double min, double max)
{
	// BUG: What to do when max < min
	double scaleFactor = (max-min)/JAUS_BYTE_RANGE;
	double bias = min;
  
	return input*scaleFactor + bias;
}

JausByte jausByteFromDouble(double value, double min, double max)
{
	// BUG: What to do when max < min
	double scaleFactor = (max-min)/JAUS_BYTE_RANGE;
	double bias = min;
	
	// limit real number between min and max
	if(value < min) value = min;
	if(value > max) value = max;
		
	// return rounded integer value
	return newJausByte((unsigned char) rint((value - bias)/scaleFactor));
}


