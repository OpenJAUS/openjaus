// File Name: jausFloat.h
//
// Written By: Danny Kent (jaus AT dannykent DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines all the basic JausFloat funtionality, this should be primarily used 
// through the JausType file and its methods

#ifndef JAUS_FLOAT_H
#define JAUS_FLOAT_H

#include "cimar/jaus.h"

#define JAUS_FLOAT_SIZE_BYTES	4

typedef float JausFloat;

JausFloat newJausFloat(float val);

JausBoolean jausFloatFromBuffer(JausFloat *jFloat, unsigned char *buf, unsigned int bufferSizeBytes);
JausBoolean jausFloatToBuffer(JausFloat input, unsigned char *buf, unsigned int bufferSizeBytes);

#endif // JAUS_FLOAT_H
