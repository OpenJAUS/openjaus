// File Name: jausInteger.h
//
// Written By: Danny Kent (jaus AT dannykent DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines all the basic JausInteger funtionality, this should be primarily used 
// through the JausType file and its methods

#ifndef JAUS_INTEGER_H
#define JAUS_INTEGER_H

#include "cimar/jaus.h"

#define JAUS_INTEGER_SIZE_BYTES	4 //size

#define JAUS_INTEGER_RANGE 		4294967294.0 	// NOTE: This range is incorrect, but is as defined by Jaus
#define JAUS_INTEGER_MAX_VALUE 	2147483647
#define JAUS_INTEGER_MIN_VALUE 	-2147483648

typedef int JausInteger;

JausInteger newJausInteger(int val);

JausBoolean jausIntegerFromBuffer(JausInteger *jInteger, unsigned char *buf, unsigned int bufferSizeBytes);
JausBoolean jausIntegerToBuffer(JausInteger input, unsigned char *buf, unsigned int bufferSizeBytes);

double jausIntegerToDouble(JausInteger input, double min, double max);
JausInteger jausIntegerFromDouble(double value, double min, double max);

#endif // JAUS_INTEGER_H
