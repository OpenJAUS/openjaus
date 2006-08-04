// File Name: JausDouble.h
//
// Written By: Danny Kent (jaus AT dannykent DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines all the basic JausDouble funtionality, this should be primarily used 
// through the JausType file and its methods

#ifndef JAUS_DOUBLE_H
#define JAUS_DOUBLE_H

#include "cimar/jaus.h"

#define JAUS_DOUBLE_SIZE_BYTES	8

typedef	double JausDouble;

JausDouble newJausDouble(double val);

JausBoolean jausDoubleFromBuffer(JausDouble *jDouble, unsigned char *buf, unsigned int bufferSizeBytes);
JausBoolean jausDoubleToBuffer(JausDouble input, unsigned char *buf, unsigned int bufferSizeBytes);

#endif // JAUS_DOUBLE_H
