// File Name: jausByte.h
//
// Written By: Danny Kent (jaus AT dannykent DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines all the basic JausByte funtionality, this should be primarily used 
// through the JausType file and its methods

#ifndef JAUS_BYTE_H
#define JAUS_BYTE_H

#include "cimar/jaus.h"

#define JAUS_BYTE_SIZE_BYTES	1 // size

#define JAUS_BYTE_RANGE 	255.0
#define JAUS_BYTE_MAX_VALUE 255
#define JAUS_BYTE_MIN_VALUE 0

typedef unsigned char JausByte;

JausByte newJausByte(unsigned char val);

JausBoolean jausByteFromBuffer(JausByte *jByte, unsigned char *buf, unsigned int bufferSizeBytes);
JausBoolean jausByteToBuffer(JausByte input, unsigned char *buf, unsigned int bufferSizeBytes);

JausByte jausByteFromDouble(double val, double min, double max);
double jausByteToDouble(JausByte input, double min, double max);

#endif //JAUS_BYTE_H
