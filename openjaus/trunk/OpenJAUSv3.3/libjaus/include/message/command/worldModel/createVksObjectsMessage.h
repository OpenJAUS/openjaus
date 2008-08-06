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
// File Name: createVksObjectsMessage.h
//
// Written By: Danny Kent (jaus AT dannykent DOT com)
//
// Version: 3.3.0a
//
// Date: 08/07/08
//
// Description: This file defines the attributes of a CreateVksObjectsMessage

#ifndef CREATE_VKS_OBJECTS_MESSAGE_H
#define CREATE_VKS_OBJECTS_MESSAGE_H

#include "jaus.h"

#ifndef VKS_PV_CREATE
#define VKS_PV_CREATE_BUFFERED_BIT	0
#endif

#ifndef VKS_CREATE_PROPERTIES
#define VKS_CREATE_PROPERTIES_CONFIRMATION_BIT	0
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
	JausByte presenceVector;		// presenceVector
	JausByte messageProperties; 	// Bit Field, use Presence Vector for ease
	JausByte requestId;							// Local Request ID
	JausArray vectorObjects;						// Dynamic Array of Vector Objects
}CreateVksObjectsMessageStruct;

typedef CreateVksObjectsMessageStruct* CreateVksObjectsMessage;

JAUS_EXPORT CreateVksObjectsMessage createVksObjectsMessageCreate(void);
JAUS_EXPORT void createVksObjectsMessageDestroy(CreateVksObjectsMessage);

JAUS_EXPORT JausBoolean createVksObjectsMessageFromBuffer(CreateVksObjectsMessage message, unsigned char* buffer, unsigned int bufferSizeBytes);
JAUS_EXPORT JausBoolean createVksObjectsMessageToBuffer(CreateVksObjectsMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);

JAUS_EXPORT CreateVksObjectsMessage createVksObjectsMessageFromJausMessage(JausMessage jausMessage);
JAUS_EXPORT JausMessage createVksObjectsMessageToJausMessage(CreateVksObjectsMessage message);

JAUS_EXPORT unsigned int createVksObjectsMessageSize(CreateVksObjectsMessage message);

#endif // CREATE_VKS_OBJECTS_MESSAGE_H
