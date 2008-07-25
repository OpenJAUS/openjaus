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
// File Name: reportLocalPoseMessage.h
//
// Written By: Danny Kent (jaus AT dannykent DOT com), Tom Galluzzo 
//
// Version: 3.3.0
//
// Date: 07/09/08
//
// Description: This file defines the attributes of a ReportLocalPoseMessage

#ifndef REPORT_LOCAL_POSE_MESSAGE_H
#define REPORT_LOCAL_POSE_MESSAGE_H

#include "jaus.h"

#ifndef JAUS_LOCAL_POSE_PV
#define JAUS_LOCAL_POSE_PV
#define JAUS_LOCAL_POSE_PV_X_BIT		0
#define JAUS_LOCAL_POSE_PV_Y_BIT		1
#define JAUS_LOCAL_POSE_PV_Z_BIT		2
#define JAUS_LOCAL_POSE_PV_POSITION_RMS_BIT	3
#define JAUS_LOCAL_POSE_PV_ROLL_BIT			4
#define JAUS_LOCAL_POSE_PV_PITCH_BIT			5
#define JAUS_LOCAL_POSE_PV_YAW_BIT			6
#define JAUS_LOCAL_POSE_PV_ATTITUDE_RMS_BIT	7
#define JAUS_LOCAL_POSE_PV_TIME_STAMP_BIT		8
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

	JausUnsignedShort presenceVector;
	JausDouble xM;				// Scaled Int (-100000, 100000)
	JausDouble yM;			// Scaled Int (-100000, 100000)
	JausDouble zM;				// Scaled Int (-10000, 35000)
	JausDouble positionRmsMeters;			// Scaled UInt (0, 100)
	JausDouble rollRadians;					// Scaled Short (-JAUS_PI, JAUS_PI)
	JausDouble pitchRadians;				// Scaled Short (-JAUS_PI, JAUS_PI)
	JausDouble yawRadians;					// Scaled Short (-JAUS_PI, JAUS_PI)
	JausDouble attitudeRmsRadians;			// Scaled Short (0, JAUS_PI)
	JausTime time;
	
}ReportLocalPoseMessageStruct;

typedef ReportLocalPoseMessageStruct* ReportLocalPoseMessage;

JAUS_EXPORT ReportLocalPoseMessage reportLocalPoseMessageCreate(void);
JAUS_EXPORT void reportLocalPoseMessageDestroy(ReportLocalPoseMessage);

JAUS_EXPORT JausBoolean reportLocalPoseMessageFromBuffer(ReportLocalPoseMessage message, unsigned char* buffer, unsigned int bufferSizeBytes);
JAUS_EXPORT JausBoolean reportLocalPoseMessageToBuffer(ReportLocalPoseMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);

JAUS_EXPORT ReportLocalPoseMessage reportLocalPoseMessageFromJausMessage(JausMessage jausMessage);
JAUS_EXPORT JausMessage reportLocalPoseMessageToJausMessage(ReportLocalPoseMessage message);

JAUS_EXPORT unsigned int reportLocalPoseMessageSize(ReportLocalPoseMessage message);

#endif // REPORT_LOCAL_POSE_MESSAGE_H
