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
// File Name: reportCameraPoseMessage.h
//
// Written By: Danny Kent (jaus AT dannykent DOT com), Tom Galluzzo 
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines the attributes of a ReportCameraPoseMessage

#ifndef REPORT_CAMERA_POSE_MESSAGE_H
#define REPORT_CAMERA_POSE_MESSAGE_H

#include "jaus.h"

#define JAUS_CAMERA_NAME_LENGTH_BYTES	15

#ifndef JAUS_REPORT_CAMERA_POSE_PV
#define JAUS_REPORT_CAMERA_POSE_PV
#define JAUS_REPORT_CAMERA_POSE_PV_CAMERA_NAME_BIT			0
#define JAUS_REPORT_CAMERA_POSE_PV_X_ORIGIN_BIT				1
#define JAUS_REPORT_CAMERA_POSE_PV_Y_ORIGIN_BIT				2
#define JAUS_REPORT_CAMERA_POSE_PV_Z_ORIGIN_BIT				3
#define JAUS_REPORT_CAMERA_POSE_PV_X_DIRECTION_COSINE_X		4
#define JAUS_REPORT_CAMERA_POSE_PV_X_DIRECTION_COSINE_Y		5
#define JAUS_REPORT_CAMERA_POSE_PV_X_DIRECTION_COSINE_Z		6
#define JAUS_REPORT_CAMERA_POSE_PV_Z_DIRECTION_COSINE_X		7
#define JAUS_REPORT_CAMERA_POSE_PV_Z_DIRECTION_COSINE_Y		8
#define JAUS_REPORT_CAMERA_POSE_PV_Z_DIRECTION_COSINE_Z		9
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
	JausShortPresenceVector presenceVector;
	JausByte cameraID;
	char cameraName[JAUS_CAMERA_NAME_LENGTH_BYTES];
	JausDouble xCameraOriginMeters;	// Scaled Short (-32.767, 32.767)
	JausDouble yCameraOriginMeters;	// Scaled Short (-32.767, 32.767)
	JausDouble zCameraOriginMeters;	// Scaled Short (-32.767, 32.767)
	JausDouble xCameraAxisDirectionCosineX; // Scaled Short (-1.0, 1.0)
	JausDouble xCameraAxisDirectionCosineY; // Scaled Short (-1.0, 1.0)
	JausDouble xCameraAxisDirectionCosineZ; // Scaled Short (-1.0, 1.0)
	JausDouble zCameraAxisDirectionCosineX; // Scaled Short (-1.0, 1.0)
	JausDouble zCameraAxisDirectionCosineY; // Scaled Short (-1.0, 1.0)
	JausDouble zCameraAxisDirectionCosineZ; // Scaled Short (-1.0, 1.0)

}ReportCameraPoseMessageStruct;

typedef ReportCameraPoseMessageStruct* ReportCameraPoseMessage;

JAUS_EXPORT ReportCameraPoseMessage reportCameraPoseMessageCreate(void);
JAUS_EXPORT void reportCameraPoseMessageDestroy(ReportCameraPoseMessage);

JAUS_EXPORT JausBoolean reportCameraPoseMessageFromBuffer(ReportCameraPoseMessage message, unsigned char* buffer, unsigned int bufferSizeBytes);
JAUS_EXPORT JausBoolean reportCameraPoseMessageToBuffer(ReportCameraPoseMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);

JAUS_EXPORT ReportCameraPoseMessage reportCameraPoseMessageFromJausMessage(JausMessage jausMessage);
JAUS_EXPORT JausMessage reportCameraPoseMessageToJausMessage(ReportCameraPoseMessage message);

JAUS_EXPORT unsigned int reportCameraPoseMessageSize(ReportCameraPoseMessage message);

#endif // REPORT_CAMERA_POSE_MESSAGE_H
