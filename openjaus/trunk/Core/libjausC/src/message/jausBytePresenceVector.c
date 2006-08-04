// File Name: jausBytePrescenceVector.c
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

JausBytePresenceVector newJausBytePresenceVector(void)
{
	JausBytePresenceVector vector;
	
	vector = newJausByte(0);
	
	return vector;
}

JausBoolean jausBytePresenceVectorFromBuffer(JausBytePresenceVector *input, unsigned char *buf, unsigned int bufferSizeBytes)
{
	return jausByteFromBuffer(input, buf, bufferSizeBytes);
}

JausBoolean jausBytePresenceVectorToBuffer(JausBytePresenceVector input, unsigned char *buf, unsigned int bufferSizeBytes)
{
	return jausByteToBuffer(input, buf, bufferSizeBytes);
}

JausBoolean jausBytePresenceVectorIsBitSet(JausBytePresenceVector input, int bit)
{
	return (input & (0x01 << bit)) > 0 ? JAUS_TRUE : JAUS_FALSE;
}

JausBoolean jausBytePresenceVectorSetBit(JausBytePresenceVector *input, int bit)
{
	if(JAUS_BYTE_SIZE_BYTES*8 < bit) // 8 bits per byte
	{
		return JAUS_FALSE;
	}
	else
	{
		*input |= 0x01 << bit;
		return JAUS_TRUE;
	}
}

JausBoolean jausBytePresenceVectorClearBit(JausBytePresenceVector *input, int bit)
{
	if(JAUS_BYTE_SIZE_BYTES*8 < bit) // 8 bits per byte
	{
		return JAUS_FALSE;
	}
	else
	{
		*input &= ~(0x01 << bit);
		return JAUS_TRUE;
	}
}
