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
// File Name: confirmEventMessage.h
//
// Written By: Danny Kent (jaus AT dannykent DOT com), Tom Galluzzo 
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines the attributes of a ConfirmEventMessage

#ifndef CONFIRM_EVENT_MESSAGE_H
#define CONFIRM_EVENT_MESSAGE_H

#include "jaus.h"

#define JAUS_CONFIRM_EVENT	0xF009

// PV as defined in Events Document v1.8
#ifndef CONFIRM_EVENT_PV
#define CONFIRM_EVENT_PV
#define CONFIRM_EVENT_PV_PERIODIC_RATE_BIT	0
#endif

// Response Codes as defined in Events Document v1.8
#ifndef CONFIRM_EVENT_RESPONSE_CODES
#define CONFIRM_EVENT_RESPONSE_CODES
#define SUCCESSFUL_RESPONSE					0
#define PERIODIC_UNSUPPORTED_RESPONSE		1
#define CHANGE_BASED_UNSUPPORTED_RESPONSE	2
#define CONNECTION_REFUSED_RESPONSE			3
#define INVALID_EVENT_RESPONSE				4
#define MESSAGE_UNSUPPORTED_RESPONSE		5
#endif

typedef struct
{
	// Include all parameters from a JausMessage structure:
	// Header Properties
	struct
	{
		// Properties by bit fields
		#ifdef JAUS_BIG_ENDIAN
			JausUnsignedShort reserved:2;
			JausUnsignedShort version:6;
			JausUnsignedShort expFlag:1;
			JausUnsignedShort scFlag:1;
			JausUnsignedShort ackNak:2;
			JausUnsignedShort priority:4; 
		#elif JAUS_LITTLE_ENDIAN
			JausUnsignedShort priority:4; 
			JausUnsignedShort ackNak:2;
			JausUnsignedShort scFlag:1; 
			JausUnsignedShort expFlag:1;
			JausUnsignedShort version:6; 
			JausUnsignedShort reserved:2;
		#else
			#error "Please define system endianess (see jaus.h)"
		#endif
	}properties;

	JausUnsignedShort commandCode; 

	JausAddress destination;

	JausAddress source;

	JausUnsignedInteger dataSize;

	JausUnsignedInteger dataFlag;
	
	JausUnsignedShort sequenceNumber;

	// MESSAGE DATA MEMBERS GO HERE
	JausByte presenceVector;	// 1: Presence Vector
	JausUnsignedShort messageCode;			// 2: Command Code of message sent in case of event occurance
	JausByte eventId;						// 3: Event Id
	JausDouble confirmedUpdateRate;			// 4: For Periodic Events, Scaled UnsignedShort (0, 1092)
	JausByte responseCode;					// 5: Enumeration of Response Types (see above)
	
}ConfirmEventMessageStruct;

typedef ConfirmEventMessageStruct* ConfirmEventMessage;

JAUS_EXPORT ConfirmEventMessage confirmEventMessageCreate(void);
JAUS_EXPORT void confirmEventMessageDestroy(ConfirmEventMessage);

JAUS_EXPORT JausBoolean confirmEventMessageFromBuffer(ConfirmEventMessage message, unsigned char* buffer, unsigned int bufferSizeBytes);
JAUS_EXPORT JausBoolean confirmEventMessageToBuffer(ConfirmEventMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);

JAUS_EXPORT ConfirmEventMessage confirmEventMessageFromJausMessage(JausMessage jausMessage);
JAUS_EXPORT JausMessage confirmEventMessageToJausMessage(ConfirmEventMessage message);

JAUS_EXPORT unsigned int confirmEventMessageSize(ConfirmEventMessage message);

#endif // CONFIRM_EVENT_MESSAGE_H
