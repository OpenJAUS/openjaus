// File Name: jausUnsignedShort.h
//
// Written By: Danny Kent (jaus AT dannykent DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines all the basic JausUnsignedShort funtionality, this should be primarily used 
// through the JausType file and its methods

#ifndef JAUS_UNSIGNED_SHORT_H
#define JAUS_UNSIGNED_SHORT_H

#include "cimar/jaus.h"

#define JAUS_UNSIGNED_SHORT_SIZE_BYTES	2

#define JAUS_UNSIGNED_SHORT_RANGE 		65535.0 // NOTE: This range is incorrect, but is as defined by Jaus
#define JAUS_UNSIGNED_SHORT_MAX_VALUE 	65535
#define JAUS_UNSIGNED_SHORT_MIN_VALUE 	0

typedef unsigned short JausUnsignedShort;

JausUnsignedShort newJausUnsignedShort(unsigned short val);

JausBoolean jausUnsignedShortFromBuffer(JausUnsignedShort *jUShort, unsigned char *buf, unsigned int bufferSizeBytes);
JausBoolean jausUnsignedShortToBuffer(JausUnsignedShort input, unsigned char *buf, unsigned int bufferSizeBytes);

double jausUnsignedShortToDouble(JausUnsignedShort input, double min, double max);
JausUnsignedShort jausUnsignedShortFromDouble(double value, double min, double max);

#endif // JAUS_UNSIGNED_SHORT_H
