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
// File Name: jausTime.h
//
// Written By: Danny Kent (jaus AT dannykent DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines the functionality of a JausTime object

#ifndef JAUS_TIME_H
#define JAUS_TIME_H

#include "cimar/jaus.h"

#define JAUS_TIME_STAMP_SIZE_BYTES		JAUS_UNSIGNED_INTEGER_SIZE_BYTES // size
#define JAUS_DATE_STAMP_SIZE_BYTES		JAUS_UNSIGNED_SHORT_SIZE_BYTES // size

// Bit Shift Defines
#define JAUS_TIME_STAMP_MILLISEC_SHIFT 	0
#define JAUS_TIME_STAMP_SECOND_SHIFT 	10
#define JAUS_TIME_STAMP_MINUTE_SHIFT 	16
#define JAUS_TIME_STAMP_HOUR_SHIFT 		22
#define JAUS_TIME_STAMP_DAY_SHIFT 		27
#define JAUS_DATE_STAMP_DAY_SHIFT 		0
#define JAUS_DATE_STAMP_MONTH_SHIFT 	5
#define JAUS_DATE_STAMP_YEAR_SHIFT 		9

// Bit Mask Defines
#define JAUS_TIME_STAMP_MILLISEC_MASK 	0x1FF 	// 9 bits
#define JAUS_TIME_STAMP_SECOND_MASK 	0x3F	// 6 bits
#define JAUS_TIME_STAMP_MINUTE_MASK 	0x3F	// 6 bits
#define JAUS_TIME_STAMP_HOUR_MASK 		0x1F	// 5 bits
#define JAUS_TIME_STAMP_DAY_MASK 		0x1F	// 5 bits
#define JAUS_DATE_STAMP_DAY_MASK 		0x1F	// 5 bits
#define JAUS_DATE_STAMP_MONTH_MASK 		0x0F	// 4 bits
#define JAUS_DATE_STAMP_YEAR_MASK 		0x7F	// 7 bits

typedef struct
{
	JausUnsignedInteger timeStamp;
	JausUnsignedShort dateStamp;

	JausUnsignedShort millisec;
	JausUnsignedShort second;
	JausUnsignedShort minute;
	JausUnsignedShort hour;
	JausUnsignedShort day;
	JausUnsignedShort month;
	JausUnsignedShort year;
	
}JausTimeStruct;

typedef JausTimeStruct *JausTime;

JausTime jausTimeCreate(void);
void jausTimeDestroy(JausTime time);

JausBoolean jausTimeSetCurrentTime(JausTime time);
JausBoolean jausTimeToString(JausTime time, char *buffer);

JausBoolean jausTimeStampFromBuffer(JausTime input, unsigned char *buf, unsigned int bufferSizeBytes);
JausBoolean jausTimeStampToBuffer(JausTime input, unsigned char *buf, unsigned int bufferSizeBytes);

JausBoolean jausDataStampFromBuffer(JausTime input, unsigned char *buf, unsigned int bufferSizeBytes);
JausBoolean jausDataStampToBuffer(JausTime input, unsigned char *buf, unsigned int bufferSizeBytes);

JausUnsignedInteger jausTimeGetTimeStamp(JausTime time);
JausUnsignedShort jausTimeGetDateStamp(JausTime time);

#endif
