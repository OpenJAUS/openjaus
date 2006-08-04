// File Name: jausFloat.c
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

JausFloat newJausFloat(float val)
{
	return val;
}

// Returns success or failed
JausBoolean jausFloatFromBuffer(JausFloat *jFloat, unsigned char *buf, unsigned int bufferSizeBytes)
{
	int i = 0;
	unsigned int tempInt = 0;
	float tempFloat = 0.0;
	
	if(bufferSizeBytes < JAUS_FLOAT_SIZE_BYTES)
		return JAUS_FALSE;
	else
	{
		if(isHostBigEndian())
		{
			// swap bytes
			for(i = 0; i < JAUS_FLOAT_SIZE_BYTES; i++)
				tempInt += (buf[i] << (JAUS_FLOAT_SIZE_BYTES-i-1)*8);
			memcpy(&(tempFloat), &(tempInt), JAUS_FLOAT_SIZE_BYTES);
		}
		else
			memcpy(&(tempFloat), buf, JAUS_FLOAT_SIZE_BYTES);
		
		*jFloat = newJausFloat(tempFloat);
		return JAUS_TRUE;
	}
}

JausBoolean jausFloatToBuffer(JausFloat input, unsigned char *buf, unsigned int bufferSizeBytes)
{
	int i = 0;
	unsigned int tempInt;

	if(bufferSizeBytes < JAUS_FLOAT_SIZE_BYTES)
		return JAUS_FALSE;
	else
	{
		if(isHostBigEndian())
		{
			memcpy(&(tempInt), &(input), JAUS_FLOAT_SIZE_BYTES);
	
			// swap bytes
			for (i = 0; i < JAUS_FLOAT_SIZE_BYTES; i++)
				buf[i] = ((tempInt >> (JAUS_FLOAT_SIZE_BYTES-i-1)*8) & 0xFF); // 8 bits per byte
		}
		else
			memcpy(buf, &(input), JAUS_FLOAT_SIZE_BYTES);
	
		return JAUS_TRUE;
	}
}
