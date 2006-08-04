// File Name: jausShort.h
//
// Written By: Danny Kent (jaus AT dannykent DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines all the basic JausShort funtionality, this should be primarily used 
// through the JausType file and its methods

#ifndef JAUS_SHORT_H
#define JAUS_SHORT_H

#include "cimar/jaus.h"

#define JAUS_SHORT_SIZE_BYTES	2 //size bytes

#define JAUS_SHORT_RANGE 		65534.0 // NOTE: This range is incorrect, but is as defined by Jaus
#define JAUS_SHORT_MAX_VALUE 	32767
#define JAUS_SHORT_MIN_VALUE 	-32768

typedef	short JausShort;

JausShort newJausShort(short val);

JausBoolean jausShortFromBuffer(JausShort *jShort, unsigned char *buf, unsigned int bufferSizeBytes);
JausBoolean jausShortToBuffer(JausShort input, unsigned char *buf, unsigned int bufferSizeBytes);

double jausShortToDouble(JausShort input, double min, double max);
JausShort jausShortFromDouble(double value, double min, double max);

#endif // JAUS_SHORT_H
