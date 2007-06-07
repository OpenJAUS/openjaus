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
// File Name: JausEventLimit.h
//
// Written By: Danny Kent (jaus AT dannykent DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file describes the stucture and functionality associated with an 
// EventLimit for use with the Jaus Events Message Set
#ifndef EVENT_LIMITS_H
#define EVENT_LIMITS_H

// Attribute Data Types as defined in Events Document v1.8
#ifndef EVENT_LIMIT_DATA_TYPE
#define EVENT_LIMIT_DATA_TYPE
#define EVENT_LIMIT_DEFAULT_DATA			255
#define EVENT_LIMIT_BYTE_DATA				0
#define EVENT_LIMIT_SHORT_DATA				1
#define EVENT_LIMIT_INTEGER_DATA			2
#define EVENT_LIMIT_LONG_DATA				3
#define EVENT_LIMIT_UNSIGNED_SHORT_DATA		4
#define EVENT_LIMIT_UNSIGNED_INTEGER_DATA	5
#define EVENT_LIMIT_UNSIGNED_LONG_DATA		6
#define EVENT_LIMIT_FLOAT_DATA				7
#define EVENT_LIMIT_DOUBLE_DATA				8
#define EVENT_LIMIT_RGB_DATA				9
#endif

typedef union
{
	JausByte byteValue;
	JausShort shortValue;
	JausInteger integerValue;
	JausLong longValue;
	JausUnsignedShort unsignedShortValue;
	JausUnsignedInteger unsignedIntegerValue;
	JausUnsignedLong unsignedLongValue;
	JausFloat floatValue;
	JausDouble doubleValue;
	struct
	{
		JausByte redValue;
		JausByte greenValue;
		JausByte blueValue;
	}rgb;
}JausEventLimitStruct;

typedef JausEventLimitStruct *JausEventLimit;

typedef struct JausEventListStruct
{
	void *eventMessage;
	JausByte eventId;
	JausEventLimit previousLimitValue;
}JausEventStruct;

typedef JausEventStruct *JausEvent;

// JausEventLimit Constructor
JausEventLimit jausEventLimitCreate();

// JausEventLimit Destructor
void jausEventLimitDestroy(JausEventLimit limit);

// JausEventLimit Constructor (from Buffer)
JausEventLimit jausEventLimitFromBuffer(unsigned char *buffer, unsigned int bufferSizeBytes, JausByte dataType);

// JausEventLimit To Buffer
JausBoolean jausEventLimitToBuffer(JausEventLimit limit, unsigned char *buffer, unsigned int bufferSizeBytes, JausByte dataType);

unsigned int jausEventLimitByteSize(JausByte dataType);

JausEvent jausEventCreate();
void jausEventDestroy(JausEvent event);

#endif
