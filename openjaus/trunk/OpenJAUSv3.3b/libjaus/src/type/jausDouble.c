/*****************************************************************************
 *  Copyright (c) 2009, OpenJAUS.com
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
// File Name: jausDouble.c
//
// Written By: Danny Kent (jaus AT dannykent DOT com), Tom Galluzzo (galluzzo AT gmail DOT com)
//
// Version: 3.3.0b
//
// Date: 09/08/09
//
// Description: This file defines all the basic JausDouble funtionality, this should be primarily used through the JausType file and its methods

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "jaus.h"

JausDouble newJausDouble(double val)
{
	return val;
}

JausBoolean jausDoubleFromBuffer(JausDouble *jDouble, unsigned char *buf, unsigned int bufferSizeBytes)
{
#ifdef JAUS_BIG_ENDIAN
	int i = 0;
	unsigned long tempLong = 0;
#endif	
	double tempDouble = 0.0;
	
	if(bufferSizeBytes < JAUS_DOUBLE_SIZE_BYTES)
	{
		return JAUS_FALSE; // insufficient data in buffer
	}
	else
	{
#ifdef JAUS_BIG_ENDIAN
		// swap bytes
		for(i = 0; i < JAUS_DOUBLE_SIZE_BYTES; i++)
		{
			tempLong += (buf[i] << (JAUS_DOUBLE_SIZE_BYTES-i-1)*8);
		}
		memcpy(&(tempDouble), &(tempLong), JAUS_DOUBLE_SIZE_BYTES);
#else
		memcpy(&tempDouble, buf, JAUS_DOUBLE_SIZE_BYTES);
#endif
		*jDouble = newJausDouble(tempDouble);
		return JAUS_TRUE;
	}
}

JausBoolean jausDoubleToBuffer(JausDouble input, unsigned char *buf, unsigned int bufferSizeBytes)
{
#ifdef JAUS_BIG_ENDIAN
	int i = 0;
	unsigned long tempLong = 0;
#endif	

	if(bufferSizeBytes < JAUS_DOUBLE_SIZE_BYTES)
	{
		return JAUS_FALSE; // insufficient room in buffer
	}
	else
	{
#ifdef JAUS_BIG_ENDIAN
		memcpy(&(tempLong), &(input), JAUS_DOUBLE_SIZE_BYTES);
		// swap bytes
		for (i = 0; i < JAUS_DOUBLE_SIZE_BYTES; i++)
		{
			buf[i] = (unsigned char)((tempLong >> (JAUS_DOUBLE_SIZE_BYTES-i-1)*8) & 0xFF); // 8 bits per byte
		}
#else
		memcpy(buf, &(input), JAUS_DOUBLE_SIZE_BYTES);
#endif
	
		return JAUS_TRUE;
	}
}

int jausDoubleToString(JausDouble number, char *buf)
{
  return sprintf(buf, "%f", number);
}
