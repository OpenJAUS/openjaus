/*****************************************************************************
 *  Copyright (c) 2006, University of Florida.
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
// File Name: jausUnsignedLong.c
//
// Written By: Danny Kent (jaus AT dannykent DOT com), Tom Galluzzo (galluzzo AT gmail DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines all the basic JausUnsignedLong funtionality, this should be primarily used through the JausType file and its methods

#include <string.h>
#include <stdlib.h>
#include "jaus.h"

JausUnsignedLong newJausUnsignedLong(unsigned long long val)
{
	return val;
}

JausBoolean jausUnsignedLongFromBuffer(JausUnsignedLong *jULong, unsigned char *buf, unsigned int bufferSizeBytes)
{
#ifdef JAUS_BIG_ENDIAN
	int i = 0;
#endif
	unsigned long tempULong = 0;
	
	if(bufferSizeBytes < JAUS_UNSIGNED_LONG_SIZE_BYTES)
		return JAUS_FALSE;
	else
	{
#ifdef JAUS_BIG_ENDIAN
		// swap bytes
		for(i = 0; i < JAUS_UNSIGNED_LONG_SIZE_BYTES; i++)
			tempULong += (buf[i] << (JAUS_UNSIGNED_LONG_SIZE_BYTES-i-1)*8);
#else
		memcpy(&(tempULong), buf, JAUS_UNSIGNED_LONG_SIZE_BYTES);
#endif	
		*jULong = newJausUnsignedLong(tempULong);
		return JAUS_TRUE;
	}
}

JausBoolean jausUnsignedLongToBuffer(JausUnsignedLong input, unsigned char *buf, unsigned int bufferSizeBytes)
{
#ifdef JAUS_BIG_ENDIAN
	int i = 0;
#endif
	if(bufferSizeBytes < JAUS_UNSIGNED_LONG_SIZE_BYTES)
		return JAUS_FALSE;
	else
	{
#ifdef JAUS_BIG_ENDIAN
		// swap bytes
		for (i = 0; i < JAUS_UNSIGNED_LONG_SIZE_BYTES; i++)
			buf[i] = (unsigned int)((input >> (JAUS_UNSIGNED_LONG_SIZE_BYTES-i-1)*8) & 0xFF); // 8 bits per byte
#else
		memcpy(buf, &input, JAUS_UNSIGNED_LONG_SIZE_BYTES);
#endif		
		return JAUS_TRUE;
	}
}

double jausUnsignedLongToDouble(JausUnsignedLong input, double min, double max)
{
	// BUG: What to do when max < min
	double scaleFactor = (max-min)/JAUS_UNSIGNED_LONG_RANGE;
	double bias = min; 

	return input*scaleFactor + bias;
}

JausUnsignedLong jausUnsignedLongFromDouble(double value, double min, double max)
{
	//limit value between min and max UnsignedLong values
	double scaleFactor = (max-min)/JAUS_UNSIGNED_LONG_RANGE;
	double bias = min;
	
	// limit real number between min and max
	if(value < min) value = min;
	if(value > max) value = max;
		
	// calculate rounded integer value
	return newJausUnsignedLong((unsigned long)((value - bias)/scaleFactor + 0.5));
}

