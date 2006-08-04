// File Name: jausIntegerPrescenceVector.c
//
// Written By: 	Danny Kent (jaus AT dannykent DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines the JAUS Presence Vector class and its associated methods.  
// JausPresenceVector is to be nested with JAUS message classes that contain a Presence
// Vector field and is used to test for the presence of absence of a field of interest
//
// A JAUS Presence Vector can be a byte, an unsigned short or an unsigned integer.
//

#include "cimar/jaus.h"

JausIntegerPresenceVector newJausIntegerPresenceVector(void)
{
	JausIntegerPresenceVector vector;
	
	vector = newJausUnsignedInteger(0);
	
	return vector;
}

JausBoolean jausIntegerPresenceVectorFromBuffer(JausIntegerPresenceVector *input, unsigned char *buf, unsigned int bufferSizeBytes)
{
	return jausUnsignedIntegerFromBuffer(input, buf, bufferSizeBytes);
}

JausBoolean jausIntegerPresenceVectorToBuffer(JausIntegerPresenceVector input, unsigned char *buf, unsigned int bufferSizeBytes)
{
	return jausUnsignedIntegerToBuffer(input, buf, bufferSizeBytes);
}

JausBoolean jausIntegerPresenceVectorIsBitSet(JausIntegerPresenceVector input, int bit)
{
	return (input & (0x01 << bit)) > 0 ? JAUS_TRUE : JAUS_FALSE;
}

JausBoolean jausIntegerPresenceVectorSetBit(JausIntegerPresenceVector *input, int bit)
{
	if(JAUS_INTEGER_SIZE_BYTES*8 < bit) // 8 bits per byte
	{
		return JAUS_FALSE;
	}
	else
	{
		*input |= 0x01 << bit;
		return JAUS_TRUE;
	}
}

JausBoolean jausIntegerPresenceVectorClearBit(JausIntegerPresenceVector *input, int bit)
{
	if(JAUS_INTEGER_SIZE_BYTES*8 < bit)
	{
		return JAUS_FALSE;
	}
	else
	{
		*input &= ~(0x01 << bit);
		return JAUS_TRUE;
	}
}
