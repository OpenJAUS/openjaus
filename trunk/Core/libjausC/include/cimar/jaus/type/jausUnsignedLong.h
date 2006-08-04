// File Name: jausUnsignedLong.h
//
// Written By: Danny Kent (jaus AT dannykent DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines all the basic JausUnsignedLong funtionality, this should be primarily used 
// through the JausType file and its methods

#ifndef JAUS_UNSIGNED_LONG_H
#define JAUS_UNSIGNED_LONG_H

#include "cimar/jaus.h"

#define JAUS_UNSIGNED_LONG_SIZE_BYTES	8

#define JAUS_UNSIGNED_LONG_RANGE 		(double) 1.8446744073709552e19
#define JAUS_UNSIGNED_LONG_MAX_VALUE 	1.8446744073709553e+19L
#define JAUS_UNSIGNED_LONG_MIN_VALUE 	0

typedef unsigned long long JausUnsignedLong;

JausUnsignedLong newJausUnsignedLong(unsigned long long val);

JausBoolean jausUnsignedLongFromBuffer(JausUnsignedLong *jULong, unsigned char *buf, unsigned int bufferSizeBytes);
JausBoolean jausUnsignedLongToBuffer(JausUnsignedLong input, unsigned char *buf, unsigned int bufferSizeBytes);

double jausUnsignedLongToDouble(JausUnsignedLong input, double min, double max);
JausUnsignedLong jausUnsignedLongFromDouble(double value, double min, double max);

#endif // JAUS_UNSIGNED_LONG_H
