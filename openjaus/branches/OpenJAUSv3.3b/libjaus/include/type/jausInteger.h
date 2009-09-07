/*****************************************************************************
 *  Copyright (c) 2008, University of Florida
 *  All rights reserved.
 *
 *  This file is part of OpenJAUS.  OpenJAUS is distributed under the BSD
 *  license.  See the LICENSE file for details.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer in the documentation and/or other materials provided
 *       with the distribution.
 *     * Neither the name of the University of Florida nor the names of its
 *       contributors may be used to endorse or promote products derived from
 *       this software without specific prior written permission.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *   OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 ****************************************************************************/
// File Name: jausInteger.h
//
// Written By: Danny Kent (jaus AT dannykent DOT com)
//
// Version: 3.3.0b
//
// Date: 08/07/08
//
// Description: This file defines all the basic JausInteger funtionality, this should be primarily used
// through the JausType file and its methods

#ifndef JAUS_INTEGER_H
#define JAUS_INTEGER_H

#include "jaus.h"

#define JAUS_INTEGER_SIZE_BYTES	4 //size

#define JAUS_INTEGER_RANGE 		4294967294.0 	// NOTE: This range is incorrect, but is as defined by Jaus
#define JAUS_INTEGER_MAX_VALUE 	2147483647
#define JAUS_INTEGER_MIN_VALUE 	-2147483648

typedef int JausInteger;

JAUS_EXPORT JausInteger newJausInteger(int val);

JAUS_EXPORT JausBoolean jausIntegerFromBuffer(JausInteger *jInteger, unsigned char *buf, unsigned int bufferSizeBytes);
JAUS_EXPORT JausBoolean jausIntegerToBuffer(JausInteger input, unsigned char *buf, unsigned int bufferSizeBytes);

JAUS_EXPORT int jausIntegerToString(JausInteger value, char * buf);

JAUS_EXPORT double jausIntegerToDouble(JausInteger input, double min, double max);
JAUS_EXPORT JausInteger jausIntegerFromDouble(double value, double min, double max);

#endif // JAUS_INTEGER_H
