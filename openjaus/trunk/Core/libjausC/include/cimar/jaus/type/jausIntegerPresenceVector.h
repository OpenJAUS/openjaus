// File Name: jausIntegerPrescenceVector.h
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

#ifndef JAUS_INTEGER_PRESENCE_VECTOR_H
#define JAUS_INTEGER_PRESENCE_VECTOR_H

#include "cimar/jaus.h"

#define JAUS_INTEGER_PRESENCE_VECTOR_SIZE_BYTES JAUS_UNSIGNED_INTEGER_SIZE_BYTES

typedef	JausUnsignedInteger JausIntegerPresenceVector;

JausIntegerPresenceVector newJausIntegerPresenceVector(void);

JausBoolean jausIntegerPresenceVectorFromBuffer(JausIntegerPresenceVector *vector, unsigned char *buf, unsigned int bufferSizeBytes);
JausBoolean jausIntegerPresenceVectorToBuffer(JausIntegerPresenceVector vector, unsigned char *buf, unsigned int bufferSizeBytes);

JausBoolean jausIntegerPresenceVectorIsBitSet(JausIntegerPresenceVector vector, int bit);
JausBoolean jausIntegerPresenceVectorSetBit(JausIntegerPresenceVector *vector, int bit);
JausBoolean jausIntegerPresenceVectorClearBit(JausIntegerPresenceVector *vector, int bit);

#endif // JAUS_INTEGER_PRESENCE_VECTOR_H
