// File Name: jausLong.h
//
// Written By: Danny Kent (jaus AT dannykent DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines all the basic JausLong funtionality, this should be primarily used 
// through the JausType file and its methods

#ifndef JAUS_LONG_H
#define JAUS_LONG_H

#include "cimar/jaus.h"

#define JAUS_LONG_SIZE_BYTES	8 // size

#define JAUS_LONG_RANGE 		(double) 18446744073709551614.0
#define JAUS_LONG_MAX_VALUE 	9223372036854775807L
#define JAUS_LONG_MIN_VALUE 	-9223372036854775807L

typedef	long long JausLong;

JausLong newJausLong(long long val);

JausBoolean jausLongFromBuffer(JausLong *jLong, unsigned char *buf, unsigned int bufferSizeBytes);
JausBoolean jausLongToBuffer(JausLong input, unsigned char *buf, unsigned int bufferSizeBytes);

double jausLongToDouble(JausLong input, double min, double max);
JausLong jausLongFromDouble(double value, double min, double max);

#endif // JAUS_LONG_H
