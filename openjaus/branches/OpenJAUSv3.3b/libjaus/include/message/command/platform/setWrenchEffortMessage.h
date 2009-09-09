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
// File Name: setWrenchEffortMessage.h
//
// Written By: Danny Kent (jaus AT dannykent DOT com), Tom Galluzzo 
//
// Version: 3.3.0b
//
// Date: 09/08/09
//
// Description: This file defines the attributes of a SetWrenchEffortMessage

#ifndef SET_WRENCH_EFFORT_MESSAGE_H
#define SET_WRENCH_EFFORT_MESSAGE_H

#include "jaus.h"

#ifndef JAUS_WRENCH_PV
#define JAUS_WRENCH_PV
#define JAUS_WRENCH_PV_PROPULSIVE_LINEAR_X_BIT		0
#define JAUS_WRENCH_PV_PROPULSIVE_LINEAR_Y_BIT		1
#define JAUS_WRENCH_PV_PROPULSIVE_LINEAR_Z_BIT		2
#define JAUS_WRENCH_PV_PROPULSIVE_ROTATIONAL_X_BIT	3
#define JAUS_WRENCH_PV_PROPULSIVE_ROTATIONAL_Y_BIT	4
#define JAUS_WRENCH_PV_PROPULSIVE_ROTATIONAL_Z_BIT	5
#define JAUS_WRENCH_PV_RESISTIVE_LINEAR_X_BIT		6
#define JAUS_WRENCH_PV_RESISTIVE_LINEAR_Y_BIT		7
#define JAUS_WRENCH_PV_RESISTIVE_LINEAR_Z_BIT		8
#define JAUS_WRENCH_PV_RESISTIVE_ROTATIONAL_X_BIT	9
#define JAUS_WRENCH_PV_RESISTIVE_ROTATIONAL_Y_BIT	10
#define JAUS_WRENCH_PV_RESISTIVE_ROTATIONAL_Z_BIT	11
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

	// Message Fields:
	JausUnsignedShort presenceVector;
	JausDouble propulsiveLinearEffortXPercent;		// Scaled Short (-100, 100)
	JausDouble propulsiveLinearEffortYPercent;		// Scaled Short (-100, 100)
	JausDouble propulsiveLinearEffortZPercent;		// Scaled Short (-100, 100)
	JausDouble propulsiveRotationalEffortXPercent;	// Scaled Short (-100, 100)
	JausDouble propulsiveRotationalEffortYPercent;	// Scaled Short (-100, 100)
	JausDouble propulsiveRotationalEffortZPercent;	// Scaled Short (-100, 100)
	JausDouble resistiveLinearEffortXPercent;		// Scaled Byte (0, 100)
	JausDouble resistiveLinearEffortYPercent;		// Scaled Byte (0, 100)
	JausDouble resistiveLinearEffortZPercent;		// Scaled Byte (0, 100)
	JausDouble resistiveRotationalEffortXPercent;	// Scaled Byte (0, 100)
	JausDouble resistiveRotationalEffortZPercent;	// Scaled Byte (0, 100)
	JausDouble resistiveRotationalEffortYPercent;	// Scaled Byte (0, 100)
	
}SetWrenchEffortMessageStruct;

typedef SetWrenchEffortMessageStruct* SetWrenchEffortMessage;

JAUS_EXPORT SetWrenchEffortMessage setWrenchEffortMessageCreate(void);
JAUS_EXPORT void setWrenchEffortMessageDestroy(SetWrenchEffortMessage);

JAUS_EXPORT JausBoolean setWrenchEffortMessageFromBuffer(SetWrenchEffortMessage message, unsigned char* buffer, unsigned int bufferSizeBytes);
JAUS_EXPORT JausBoolean setWrenchEffortMessageToBuffer(SetWrenchEffortMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);

JAUS_EXPORT SetWrenchEffortMessage setWrenchEffortMessageFromJausMessage(JausMessage jausMessage);
JAUS_EXPORT JausMessage setWrenchEffortMessageToJausMessage(SetWrenchEffortMessage message);

JAUS_EXPORT unsigned int setWrenchEffortMessageSize(SetWrenchEffortMessage message);

JAUS_EXPORT char* setWrenchEffortMessageToString(SetWrenchEffortMessage message);
#endif // SET_WRENCH_EFFORT_MESSAGE_H
