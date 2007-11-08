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
// File Name: setVelocityStateMessage.h
//
// Written By: Danny Kent (jaus AT dannykent DOT com), Tom Galluzzo 
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines the attributes of a SetVelocityStateMessage

#ifndef SET_VELOCITY_STATE_MESSAGE_H
#define SET_VELOCITY_STATE_MESSAGE_H

#include "jaus.h"

#ifndef JAUS_VELOCITY_PV
#define JAUS_VELOCITY_PV
#define JAUS_VELOCITY_PV_VELOCITY_X_BIT		0
#define JAUS_VELOCITY_PV_VELOCITY_Y_BIT		1
#define JAUS_VELOCITY_PV_VELOCITY_Z_BIT		2
#define JAUS_VELOCITY_PV_VELOCITY_RMS_BIT	3
#define JAUS_VELOCITY_PV_ROLL_RATE_BIT		4
#define JAUS_VELOCITY_PV_PITCH_RATE_BIT		5
#define JAUS_VELOCITY_PV_YAW_RATE_BIT		6
#define JAUS_VELOCITY_PV_RATE_RMS_BIT		7
#define JAUS_VELOCITY_PV_TIME_STAMP_BIT		8
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

	JausShortPresenceVector presenceVector;
	JausDouble velocityXMps;	// Scaled Int (-65.534, 65.534) 	Mps = Meters per Second
	JausDouble velocityYMps;	// Scaled Int (-65.534, 65.534) 	Mps = Meters per Second
	JausDouble velocityZMps;	// Scaled Int (-65.534, 65.534) 	Mps = Meters per Secon
	JausDouble velocityRmsMps;	// Scaled UInt (0, 100) 			Mps = Meters per Second
	JausDouble rollRateRps;		// Scaled Short (-32.767, 32.767) 	Rps = Radians per Second
	JausDouble pitchRateRps;	// Scaled Short (-32.767, 32.767) 	Rps = Radians per Second
	JausDouble yawRateRps;		// Scaled Short (-32.767, 32.767) 	Rps = Radians per Second
	JausDouble rateRmsRps;		// Scaled UShort (0, JAUS_PI) 		Rps = Radians per Second
	JausUnsignedInteger timeStamp;

}SetVelocityStateMessageStruct;

typedef SetVelocityStateMessageStruct* SetVelocityStateMessage;

SetVelocityStateMessage setVelocityStateMessageCreate(void);
void setVelocityStateMessageDestroy(SetVelocityStateMessage);

JausBoolean setVelocityStateMessageFromBuffer(SetVelocityStateMessage message, unsigned char* buffer, unsigned int bufferSizeBytes);
JausBoolean setVelocityStateMessageToBuffer(SetVelocityStateMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);


SetVelocityStateMessage setVelocityStateMessageFromJausMessage(JausMessage jausMessage);
JausMessage setVelocityStateMessageToJausMessage(SetVelocityStateMessage message);


unsigned int setVelocityStateMessageSize(SetVelocityStateMessage message);


#endif // SET_VELOCITY_STATE_MESSAGE_H
