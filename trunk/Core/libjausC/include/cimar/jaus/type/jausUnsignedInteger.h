// File Name: jausUnsignedInteger.h
//
// Written By: Danny Kent (jaus AT dannykent DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines all the basic JausUnsignedInteger funtionality, this should be primarily used 
// through the JausType file and its methods

#ifndef JAUS_UNSIGNED_INTEGER_H
#define JAUS_UNSIGNED_INTEGER_H

#include "cimar/jaus.h"

#define JAUS_UNSIGNED_INTEGER_SIZE_BYTES	4

#define JAUS_UNSIGNED_INTEGER_RANGE 		4294967294.0 // NOTE: This range is incorrect, but is as defined by Jaus
#define JAUS_UNSIGNED_INTEGER_MAX_VALUE 	4294967295L
#define JAUS_UNSIGNED_INTEGER_MIN_VALUE 	0

typedef unsigned int JausUnsignedInteger;

JausUnsignedInteger newJausUnsignedInteger(unsigned int val);

JausBoolean jausUnsignedIntegerFromBuffer(JausUnsignedInteger *jUint, unsigned char *buf, unsigned int bufferSizeBytes);
JausBoolean jausUnsignedIntegerToBuffer(JausUnsignedInteger input, unsigned char *buf, unsigned int bufferSizeBytes);

double jausUnsignedIntegerToDouble(JausUnsignedInteger input, double min, double max);
JausUnsignedInteger jausUnsignedIntegerFromDouble(double value, double min, double max);

#endif // JAUS_UNSIGNED_INTEGER_H
