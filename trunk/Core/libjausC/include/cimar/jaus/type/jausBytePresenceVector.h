// File Name: jausBytePrescenceVector.h
//
// Written By: Danny Kent (jaus AT dannykent DOT com)
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

#ifndef JAUS_BYTE_PRESENCE_VECTOR_H
#define JAUS_BYTE_PRESENCE_VECTOR_H

#include "cimar/jaus.h"

#define JAUS_BYTE_PRESENCE_VECTOR_SIZE_BYTES JAUS_BYTE_SIZE_BYTES

typedef JausByte JausBytePresenceVector;

JausBytePresenceVector newJausBytePresenceVector(void);

JausBoolean jausBytePresenceVectorFromBuffer(JausBytePresenceVector *vector, unsigned char *buf, unsigned int bufferSizeBytes);
JausBoolean jausBytePresenceVectorToBuffer(JausBytePresenceVector vector, unsigned char *buf, unsigned int bufferSizeBytes);

JausBoolean jausBytePresenceVectorIsBitSet(JausBytePresenceVector vector, int bit);
JausBoolean jausBytePresenceVectorSetBit(JausBytePresenceVector *vector, int bit);
JausBoolean jausBytePresenceVectorClearBit(JausBytePresenceVector *vector, int bit);

#endif // JAUS_BYTE_PRESENCE_VECTOR_H
