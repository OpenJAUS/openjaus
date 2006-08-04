// File Name: jausShortPrescenceVector.h
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

#ifndef JAUS_SHORT_PRESENCE_VECTOR_H
#define JAUS_SHORT_PRESENCE_VECTOR_H

#include "cimar/jaus.h"

#define JAUS_SHORT_PRESENCE_VECTOR_SIZE_BYTES JAUS_UNSIGNED_SHORT_SIZE_BYTES

typedef JausUnsignedShort JausShortPresenceVector;

JausShortPresenceVector newJausShortPresenceVector(void);

JausBoolean jausShortPresenceVectorFromBuffer(JausShortPresenceVector *vector, unsigned char *buf, unsigned int bufferSizeBytes);
JausBoolean jausShortPresenceVectorToBuffer(JausShortPresenceVector vector, unsigned char *buf, unsigned int bufferSizeBytes);

JausBoolean jausShortPresenceVectorIsBitSet(JausShortPresenceVector vector, int bit);
JausBoolean jausShortPresenceVectorSetBit(JausShortPresenceVector *vector, int bit);
JausBoolean jausShortPresenceVectorClearBit(JausShortPresenceVector *vector, int bit);

#endif // JAUS_SHORT_PRESENCE_VECTOR_H
