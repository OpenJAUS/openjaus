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
// File Name: reportCameraCapabilitiesMessage.c
//
// Written By: Danny Kent (jaus AT dannykent DOT com), Tom Galluzzo (galluzzo AT gmail DOT com)
//
// Version: 3.3.0
//
// Date: 07/09/08
//
// Description: This file defines the functionality of a ReportCameraCapabilitiesMessage

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jaus.h"

static const int commandCode = JAUS_REPORT_CAMERA_CAPABILITIES;
static const int maxDataSizeBytes = 81;

static JausBoolean headerFromBuffer(ReportCameraCapabilitiesMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);
static JausBoolean headerToBuffer(ReportCameraCapabilitiesMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);
static int headerToString(ReportCameraCapabilitiesMessage message, char **buf);

static JausBoolean dataFromBuffer(ReportCameraCapabilitiesMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);
static int dataToBuffer(ReportCameraCapabilitiesMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);
static void dataInitialize(ReportCameraCapabilitiesMessage message);
static void dataDestroy(ReportCameraCapabilitiesMessage message);
static unsigned int dataSize(ReportCameraCapabilitiesMessage message);

// ************************************************************************************************************** //
//                                    USER CONFIGURED FUNCTIONS
// ************************************************************************************************************** //

// Initializes the message-specific fields
static void dataInitialize(ReportCameraCapabilitiesMessage message)
{
	// Set initial values of message fields
	message->presenceVector = newJausUnsignedShort(JAUS_SHORT_PRESENCE_VECTOR_ALL_ON);
	message->cameraID = newJausByte(0);
	message->cameraDescription[0] = 0;
	message->maxHorizontalFovRadians = newJausDouble(0);			// Scaled UShort (0, JAUS_PI) 
	message->minHorizontalFovRadians = newJausDouble(0);			// Scaled UShort (0, JAUS_PI) 
	message->maxVerticalFovRadians = newJausDouble(0);			// Scaled UShort (0, JAUS_PI) 
	message->minVerticalFovRadians = newJausDouble(0);			// Scaled UShort (0, JAUS_PI) 
	message->maxHorizontalResolution = newJausUnsignedShort(0);
	message->minHorizontalResolution = newJausUnsignedShort(0);
	message->maxVerticalResolution = newJausUnsignedShort(0);
	message->minVerticalResolution = newJausUnsignedShort(0);
	message->maxFrameRate = newJausUnsignedShort(0);
	message->minFrameRate = newJausUnsignedShort(0);
	message->maxShutterSpeed = newJausUnsignedShort(0);
	message->minShutterSpeed = newJausUnsignedShort(0);
	
	// Image Control
	message->autoFocusAvailable = JAUS_FALSE;
	message->autoIrisAvailable = JAUS_FALSE;
	message->imageStabilizationAvailable = JAUS_FALSE;
	message->whiteBalanceAvailable = JAUS_FALSE;
	message->syncFlashAvailable = JAUS_FALSE;
	message->redEyeAvailable = JAUS_FALSE;
	message->autoShutterAvailable = JAUS_FALSE;
	message->videoAutoGainAvailable = JAUS_FALSE;
	message->interlacedVideoAvailable = JAUS_FALSE;

	// Audio Control
	message->audioEnabledAvailable = newJausUnsignedShort(0);
	message->audioAutoGainAvailable = newJausUnsignedShort(0);
	message->stereoAudioAvailable = newJausUnsignedShort(0);
	message->directionalAudioAvailable = newJausUnsignedShort(0);
	message->frontMicrophoneAvailable = newJausUnsignedShort(0);
	message->rearMicrophoneAvailable = newJausUnsignedShort(0);
	message->leftMicrophoneAvailable = newJausUnsignedShort(0);
	message->rightMicrophoneAvailable = newJausUnsignedShort(0);
}

// Destructs the message-specific fields
static void dataDestroy(ReportCameraCapabilitiesMessage message)
{
	// Free message fields
}

// Return boolean of success
static JausBoolean dataFromBuffer(ReportCameraCapabilitiesMessage message, unsigned char *buffer, unsigned int bufferSizeBytes)
{
	int index = 0;
	JausUnsignedShort tempUShort;

	if(bufferSizeBytes == message->dataSize)
	{
		// Unpack Message Fields from Buffer
		
		// Presence Vector
		if(!jausUnsignedShortFromBuffer(&message->presenceVector, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
		index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
		
		// CameraID
		if(!jausByteFromBuffer(&message->cameraID, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
		index += JAUS_BYTE_SIZE_BYTES;

		// Camera Description
		if(jausUnsignedShortIsBitSet(message->presenceVector, JAUS_REPORT_CAMERA_CAPABILITIES_PV_DESCRIPTION_BIT))
		{
			// unpack string of length JAUS_CAMERA_DESCRIPTION_LENGTH_BYTES
			if(bufferSizeBytes-index < JAUS_CAMERA_DESCRIPTION_LENGTH_BYTES) return JAUS_FALSE;
			
			memcpy(&message->cameraDescription, buffer+index, JAUS_CAMERA_DESCRIPTION_LENGTH_BYTES);
			index += JAUS_CAMERA_DESCRIPTION_LENGTH_BYTES;
		}
	
		if(jausUnsignedShortIsBitSet(message->presenceVector, JAUS_REPORT_CAMERA_CAPABILITIES_PV_MAX_HORIZONTAL_FOV_BIT))
		{
			if(!jausUnsignedShortFromBuffer(&tempUShort, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;

			// Scaled UShort (0, JAUS_PI)
			message->maxHorizontalFovRadians = jausUnsignedShortToDouble(tempUShort, 0, JAUS_PI);
		}

		if(jausUnsignedShortIsBitSet(message->presenceVector, JAUS_REPORT_CAMERA_CAPABILITIES_PV_MIN_HORIZONTAL_FOV_BIT))
		{
			if(!jausUnsignedShortFromBuffer(&tempUShort, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;

			// Scaled UShort (0, JAUS_PI)
			message->minHorizontalFovRadians = jausUnsignedShortToDouble(tempUShort, 0, JAUS_PI);
		}

		if(jausUnsignedShortIsBitSet(message->presenceVector, JAUS_REPORT_CAMERA_CAPABILITIES_PV_MAX_VERTICAL_FOV_BIT))
		{
			if(!jausUnsignedShortFromBuffer(&tempUShort, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;

			// Scaled UShort (0, JAUS_PI)
			message->maxVerticalFovRadians = jausUnsignedShortToDouble(tempUShort, 0, JAUS_PI);
		}

		if(jausUnsignedShortIsBitSet(message->presenceVector, JAUS_REPORT_CAMERA_CAPABILITIES_PV_MIN_VERTICAL_FOV_BIT))
		{
			if(!jausUnsignedShortFromBuffer(&tempUShort, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;

			// Scaled UShort (0, JAUS_PI)
			message->minVerticalFovRadians = jausUnsignedShortToDouble(tempUShort, 0, JAUS_PI);
		}

		if(jausUnsignedShortIsBitSet(message->presenceVector, JAUS_REPORT_CAMERA_CAPABILITIES_PV_MAX_HORIZONTAL_RESOLUTION_BIT))
		{
			if(!jausUnsignedShortFromBuffer(&message->maxHorizontalResolution, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
		}

		if(jausUnsignedShortIsBitSet(message->presenceVector, JAUS_REPORT_CAMERA_CAPABILITIES_PV_MIN_HORIZONTAL_RESOLUTION_BIT))
		{
			if(!jausUnsignedShortFromBuffer(&message->minHorizontalResolution, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
		}

		if(jausUnsignedShortIsBitSet(message->presenceVector, JAUS_REPORT_CAMERA_CAPABILITIES_PV_MAX_VERTICAL_RESOLUTION_BIT))
		{
			if(!jausUnsignedShortFromBuffer(&message->maxVerticalResolution, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
		}

		if(jausUnsignedShortIsBitSet(message->presenceVector, JAUS_REPORT_CAMERA_CAPABILITIES_PV_MIN_VERTICAL_RESOLUTION_BIT))
		{
			if(!jausUnsignedShortFromBuffer(&message->minVerticalResolution, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
		}

		if(jausUnsignedShortIsBitSet(message->presenceVector, JAUS_REPORT_CAMERA_CAPABILITIES_PV_MAX_FRAME_RATE_BIT))
		{
			if(!jausUnsignedShortFromBuffer(&message->maxFrameRate, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
		}

		if(jausUnsignedShortIsBitSet(message->presenceVector, JAUS_REPORT_CAMERA_CAPABILITIES_PV_MIN_FRAME_RATE_BIT))
		{
			if(!jausUnsignedShortFromBuffer(&message->minFrameRate, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
		}
		
		if(jausUnsignedShortIsBitSet(message->presenceVector, JAUS_REPORT_CAMERA_CAPABILITIES_PV_MAX_SHUTTER_SPEED_BIT))
		{
			if(!jausUnsignedShortFromBuffer(&message->maxShutterSpeed, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
		}

		if(jausUnsignedShortIsBitSet(message->presenceVector, JAUS_REPORT_CAMERA_CAPABILITIES_PV_MIN_SHUTTER_SPEED_BIT))
		{
			if(!jausUnsignedShortFromBuffer(&message->minShutterSpeed, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
		}

		// Image Control
		if(jausUnsignedShortIsBitSet(message->presenceVector, JAUS_REPORT_CAMERA_CAPABILITIES_PV_IMAGE_CONTROL_BIT))
		{
			//unpack
			if(!jausUnsignedShortFromBuffer(&tempUShort, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;

			// Setup the datastructure's boolean values
			message->autoFocusAvailable = jausUnsignedShortIsBitSet(tempUShort, JAUS_CAMERA_IMAGE_CONTROL_BF_AUTO_FOCUS_BIT)? JAUS_TRUE : JAUS_FALSE;
			message->autoIrisAvailable = jausUnsignedShortIsBitSet(tempUShort, JAUS_CAMERA_IMAGE_CONTROL_BF_AUTO_IRIS_BIT)? JAUS_TRUE : JAUS_FALSE;
			message->imageStabilizationAvailable = jausUnsignedShortIsBitSet(tempUShort, JAUS_CAMERA_IMAGE_CONTROL_BF_IMAGE_STABILIZATION_BIT)? JAUS_TRUE : JAUS_FALSE;
			message->whiteBalanceAvailable = jausUnsignedShortIsBitSet(tempUShort, JAUS_CAMERA_IMAGE_CONTROL_BF_WHITE_BALANCE_BIT)? JAUS_TRUE : JAUS_FALSE;
			message->syncFlashAvailable = jausUnsignedShortIsBitSet(tempUShort, JAUS_CAMERA_IMAGE_CONTROL_BF_SYNC_FLASH_BIT)? JAUS_TRUE : JAUS_FALSE;
			message->redEyeAvailable = jausUnsignedShortIsBitSet(tempUShort, JAUS_CAMERA_IMAGE_CONTROL_BF_RED_EYE_BIT)? JAUS_TRUE : JAUS_FALSE;
			message->autoShutterAvailable = jausUnsignedShortIsBitSet(tempUShort, JAUS_CAMERA_IMAGE_CONTROL_BF_AUTO_SHUTTER_BIT)? JAUS_TRUE : JAUS_FALSE;
			message->videoAutoGainAvailable = jausUnsignedShortIsBitSet(tempUShort, JAUS_CAMERA_IMAGE_CONTROL_BF_AUTO_GAIN_BIT)? JAUS_TRUE : JAUS_FALSE;
			message->interlacedVideoAvailable = jausUnsignedShortIsBitSet(tempUShort, JAUS_CAMERA_IMAGE_CONTROL_BF_INTERLACED_BIT)? JAUS_TRUE : JAUS_FALSE;
		}

		// Audio Control
		if(jausUnsignedShortIsBitSet(message->presenceVector, JAUS_REPORT_CAMERA_CAPABILITIES_PV_AUDIO_CONTROL_BIT))
		{
			//unpack
			if(!jausUnsignedShortFromBuffer(&tempUShort, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;

			message->audioEnabledAvailable = jausUnsignedShortIsBitSet(tempUShort, JAUS_CAMERA_AUDIO_CONTROL_BF_AUDIO_BIT)? JAUS_TRUE : JAUS_FALSE;
			message->audioAutoGainAvailable = jausUnsignedShortIsBitSet(tempUShort, JAUS_CAMERA_AUDIO_CONTROL_BF_AUTO_GAIN_BIT)? JAUS_TRUE : JAUS_FALSE;
			message->stereoAudioAvailable = jausUnsignedShortIsBitSet(tempUShort, JAUS_CAMERA_AUDIO_CONTROL_BF_STEREO_BIT)? JAUS_TRUE : JAUS_FALSE;
			message->directionalAudioAvailable = jausUnsignedShortIsBitSet(tempUShort, JAUS_CAMERA_AUDIO_CONTROL_BF_DIRECTIONAL_BIT)? JAUS_TRUE : JAUS_FALSE;
			message->frontMicrophoneAvailable = jausUnsignedShortIsBitSet(tempUShort, JAUS_CAMERA_AUDIO_CONTROL_BF_FRONT_MICROPHONE_BIT)? JAUS_TRUE : JAUS_FALSE;
			message->rearMicrophoneAvailable = jausUnsignedShortIsBitSet(tempUShort, JAUS_CAMERA_AUDIO_CONTROL_BF_REAR_MICROPHONE_BIT)? JAUS_TRUE : JAUS_FALSE;
			message->leftMicrophoneAvailable = jausUnsignedShortIsBitSet(tempUShort, JAUS_CAMERA_AUDIO_CONTROL_BF_LEFT_MICROPHONE_BIT)? JAUS_TRUE : JAUS_FALSE;
			message->rightMicrophoneAvailable = jausUnsignedShortIsBitSet(tempUShort, JAUS_CAMERA_AUDIO_CONTROL_BF_RIGHT_MICROPHONE_BIT)? JAUS_TRUE : JAUS_FALSE;
		}

		return JAUS_TRUE;
	}
	else
	{
		return JAUS_FALSE;
	}
}

// Returns number of bytes put into the buffer
static int dataToBuffer(ReportCameraCapabilitiesMessage message, unsigned char *buffer, unsigned int bufferSizeBytes)
{
	int index = 0;
	JausUnsignedShort tempUShort;

	if(bufferSizeBytes >= dataSize(message))
	{
		// Pack Message Fields to Buffer
		
		// Presence Vector
		if(!jausUnsignedShortToBuffer(message->presenceVector, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
		index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
		
		// CameraID
		if(!jausByteToBuffer(message->cameraID, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
		index += JAUS_BYTE_SIZE_BYTES;

		// Camera Description
		if(jausUnsignedShortIsBitSet(message->presenceVector, JAUS_REPORT_CAMERA_CAPABILITIES_PV_DESCRIPTION_BIT))
		{
			// unpack string of length JAUS_CAMERA_DESCRIPTION_LENGTH_BYTES
			if(bufferSizeBytes-index < JAUS_CAMERA_DESCRIPTION_LENGTH_BYTES) return JAUS_FALSE;
			
			memcpy(buffer+index, message->cameraDescription, JAUS_CAMERA_DESCRIPTION_LENGTH_BYTES);
			index += JAUS_CAMERA_DESCRIPTION_LENGTH_BYTES;
		}
	
		if(jausUnsignedShortIsBitSet(message->presenceVector, JAUS_REPORT_CAMERA_CAPABILITIES_PV_MAX_HORIZONTAL_FOV_BIT))
		{
			// Scaled UShort (0, JAUS_PI)
			tempUShort = jausUnsignedShortFromDouble(message->maxHorizontalFovRadians, 0, JAUS_PI);

			if(!jausUnsignedShortToBuffer(tempUShort, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
		}

		if(jausUnsignedShortIsBitSet(message->presenceVector, JAUS_REPORT_CAMERA_CAPABILITIES_PV_MIN_HORIZONTAL_FOV_BIT))
		{
			// Scaled UShort (0, JAUS_PI)
			tempUShort = jausUnsignedShortFromDouble(message->minHorizontalFovRadians, 0, JAUS_PI);

			if(!jausUnsignedShortToBuffer(tempUShort, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
		}

		if(jausUnsignedShortIsBitSet(message->presenceVector, JAUS_REPORT_CAMERA_CAPABILITIES_PV_MAX_VERTICAL_FOV_BIT))
		{
			// Scaled UShort (0, JAUS_PI)
			tempUShort = jausUnsignedShortFromDouble(message->maxVerticalFovRadians, 0, JAUS_PI);

			if(!jausUnsignedShortToBuffer(tempUShort, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
		}

		if(jausUnsignedShortIsBitSet(message->presenceVector, JAUS_REPORT_CAMERA_CAPABILITIES_PV_MIN_VERTICAL_FOV_BIT))
		{
			// Scaled UShort (0, JAUS_PI)
			tempUShort = jausUnsignedShortFromDouble(message->minVerticalFovRadians, 0, JAUS_PI);

			if(!jausUnsignedShortToBuffer(tempUShort, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
		}

		if(jausUnsignedShortIsBitSet(message->presenceVector, JAUS_REPORT_CAMERA_CAPABILITIES_PV_MAX_HORIZONTAL_RESOLUTION_BIT))
		{
			if(!jausUnsignedShortToBuffer(message->maxHorizontalResolution, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
		}

		if(jausUnsignedShortIsBitSet(message->presenceVector, JAUS_REPORT_CAMERA_CAPABILITIES_PV_MIN_HORIZONTAL_RESOLUTION_BIT))
		{
			if(!jausUnsignedShortToBuffer(message->minHorizontalResolution, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
		}

		if(jausUnsignedShortIsBitSet(message->presenceVector, JAUS_REPORT_CAMERA_CAPABILITIES_PV_MAX_VERTICAL_RESOLUTION_BIT))
		{
			if(!jausUnsignedShortToBuffer(message->maxVerticalResolution, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
		}

		if(jausUnsignedShortIsBitSet(message->presenceVector, JAUS_REPORT_CAMERA_CAPABILITIES_PV_MIN_VERTICAL_RESOLUTION_BIT))
		{
			if(!jausUnsignedShortToBuffer(message->minVerticalResolution, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
		}

		if(jausUnsignedShortIsBitSet(message->presenceVector, JAUS_REPORT_CAMERA_CAPABILITIES_PV_MAX_FRAME_RATE_BIT))
		{
			if(!jausUnsignedShortToBuffer(message->maxFrameRate, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
		}

		if(jausUnsignedShortIsBitSet(message->presenceVector, JAUS_REPORT_CAMERA_CAPABILITIES_PV_MIN_FRAME_RATE_BIT))
		{
			if(!jausUnsignedShortToBuffer(message->minFrameRate, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
		}
		
		if(jausUnsignedShortIsBitSet(message->presenceVector, JAUS_REPORT_CAMERA_CAPABILITIES_PV_MAX_SHUTTER_SPEED_BIT))
		{
			if(!jausUnsignedShortToBuffer(message->maxShutterSpeed, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
		}

		if(jausUnsignedShortIsBitSet(message->presenceVector, JAUS_REPORT_CAMERA_CAPABILITIES_PV_MIN_SHUTTER_SPEED_BIT))
		{
			if(!jausUnsignedShortToBuffer(message->minShutterSpeed, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
		}

		// Image Control
		if(jausUnsignedShortIsBitSet(message->presenceVector, JAUS_REPORT_CAMERA_CAPABILITIES_PV_IMAGE_CONTROL_BIT))
		{
			// Setup the datastructure's boolean values
			tempUShort = 0;
			if(message->autoFocusAvailable) jausUnsignedShortSetBit(&tempUShort, JAUS_CAMERA_IMAGE_CONTROL_BF_AUTO_FOCUS_BIT);
			if(message->autoIrisAvailable) jausUnsignedShortSetBit(&tempUShort, JAUS_CAMERA_IMAGE_CONTROL_BF_AUTO_IRIS_BIT);
			if(message->imageStabilizationAvailable) jausUnsignedShortSetBit(&tempUShort, JAUS_CAMERA_IMAGE_CONTROL_BF_IMAGE_STABILIZATION_BIT);
			if(message->whiteBalanceAvailable) jausUnsignedShortSetBit(&tempUShort, JAUS_CAMERA_IMAGE_CONTROL_BF_WHITE_BALANCE_BIT);
			if(message->syncFlashAvailable) jausUnsignedShortSetBit(&tempUShort, JAUS_CAMERA_IMAGE_CONTROL_BF_SYNC_FLASH_BIT);
			if(message->redEyeAvailable) jausUnsignedShortSetBit(&tempUShort, JAUS_CAMERA_IMAGE_CONTROL_BF_RED_EYE_BIT);
			if(message->autoShutterAvailable) jausUnsignedShortSetBit(&tempUShort, JAUS_CAMERA_IMAGE_CONTROL_BF_AUTO_SHUTTER_BIT);
			if(message->videoAutoGainAvailable) jausUnsignedShortSetBit(&tempUShort, JAUS_CAMERA_IMAGE_CONTROL_BF_AUTO_GAIN_BIT);
			if(message->interlacedVideoAvailable) jausUnsignedShortSetBit(&tempUShort, JAUS_CAMERA_IMAGE_CONTROL_BF_INTERLACED_BIT);

			if(!jausUnsignedShortToBuffer(tempUShort, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
		}

		// Audio Control
		if(jausUnsignedShortIsBitSet(message->presenceVector, JAUS_REPORT_CAMERA_CAPABILITIES_PV_AUDIO_CONTROL_BIT))
		{
			// Setup the datastructure's boolean values
			tempUShort = 0;
			if(message->audioEnabledAvailable) jausUnsignedShortSetBit(&tempUShort, JAUS_CAMERA_AUDIO_CONTROL_BF_AUDIO_BIT);
			if(message->audioAutoGainAvailable) jausUnsignedShortSetBit(&tempUShort, JAUS_CAMERA_AUDIO_CONTROL_BF_AUTO_GAIN_BIT);
			if(message->stereoAudioAvailable) jausUnsignedShortSetBit(&tempUShort, JAUS_CAMERA_AUDIO_CONTROL_BF_STEREO_BIT);
			if(message->directionalAudioAvailable) jausUnsignedShortSetBit(&tempUShort, JAUS_CAMERA_AUDIO_CONTROL_BF_DIRECTIONAL_BIT);
			if(message->frontMicrophoneAvailable) jausUnsignedShortSetBit(&tempUShort, JAUS_CAMERA_AUDIO_CONTROL_BF_FRONT_MICROPHONE_BIT);
			if(message->rearMicrophoneAvailable) jausUnsignedShortSetBit(&tempUShort, JAUS_CAMERA_AUDIO_CONTROL_BF_REAR_MICROPHONE_BIT);
			if(message->leftMicrophoneAvailable) jausUnsignedShortSetBit(&tempUShort, JAUS_CAMERA_AUDIO_CONTROL_BF_LEFT_MICROPHONE_BIT);
			if(message->rightMicrophoneAvailable) jausUnsignedShortSetBit(&tempUShort, JAUS_CAMERA_AUDIO_CONTROL_BF_RIGHT_MICROPHONE_BIT);

			if(!jausUnsignedShortToBuffer(tempUShort, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
		}
	}

	return index;
}

static int dataToString(ReportCameraCapabilitiesMessage message, char **buf)
{
  //message already verified 

  //Setup temporary string buffer
  
  unsigned int bufSize = 28 * 50 + sizeof(message->cameraDescription);
  (*buf) = (char*)malloc(sizeof(char)*bufSize);

  strcpy((*buf), "\nPresence Vector: ");
  jausUnsignedShortToHexString(message->presenceVector, (*buf)+strlen(*buf));
  
  strcat((*buf), "\nCamera Id: " );
  jausByteToString(message->cameraID, (*buf)+strlen(*buf));
  // Camera Description
  if(jausUnsignedShortIsBitSet(message->presenceVector, JAUS_REPORT_CAMERA_CAPABILITIES_PV_DESCRIPTION_BIT))
  {
    strcat((*buf), "\nDescription: ");
    strcat((*buf), message->cameraDescription);
  }

  if(jausUnsignedShortIsBitSet(message->presenceVector, JAUS_REPORT_CAMERA_CAPABILITIES_PV_MAX_HORIZONTAL_FOV_BIT))
  {
    strcat((*buf), "\nMax Horizontal FOV(radians): ");
    jausDoubleToString(message->maxHorizontalFovRadians, (*buf)+strlen(*buf));
  }

  if(jausUnsignedShortIsBitSet(message->presenceVector, JAUS_REPORT_CAMERA_CAPABILITIES_PV_MIN_HORIZONTAL_FOV_BIT))
  {
    strcat((*buf), "\nMin Horizontal FOV(radians): ");
    jausDoubleToString(message->minHorizontalFovRadians, (*buf)+strlen(*buf));
  }

  if(jausUnsignedShortIsBitSet(message->presenceVector, JAUS_REPORT_CAMERA_CAPABILITIES_PV_MAX_VERTICAL_FOV_BIT))
  {
    strcat((*buf), "\nMax Vertical FOV(radians): ");
    jausDoubleToString(message->maxVerticalFovRadians, (*buf)+strlen(*buf));
  }

  if(jausUnsignedShortIsBitSet(message->presenceVector, JAUS_REPORT_CAMERA_CAPABILITIES_PV_MIN_VERTICAL_FOV_BIT))
  {
    strcat((*buf), "\nMin Vertical FOV(radians): ");
    jausDoubleToString(message->minVerticalFovRadians, (*buf)+strlen(*buf));
  }

  if(jausUnsignedShortIsBitSet(message->presenceVector, JAUS_REPORT_CAMERA_CAPABILITIES_PV_MAX_HORIZONTAL_RESOLUTION_BIT))
  {
    strcat((*buf), "\nMax Horizontal Resolution: ");
    jausUnsignedShortToString(message->maxHorizontalResolution, (*buf)+strlen(*buf));
  }

  if(jausUnsignedShortIsBitSet(message->presenceVector, JAUS_REPORT_CAMERA_CAPABILITIES_PV_MIN_HORIZONTAL_RESOLUTION_BIT))
  {
    strcat((*buf), "\nMin Horizontal Resolution: ");
    jausUnsignedShortToString(message->minHorizontalResolution, (*buf)+strlen(*buf));
  }

  if(jausUnsignedShortIsBitSet(message->presenceVector, JAUS_REPORT_CAMERA_CAPABILITIES_PV_MAX_VERTICAL_RESOLUTION_BIT))
  {
    strcat((*buf), "\nMax Vertical Resolution: ");
    jausUnsignedShortToString(message->maxVerticalResolution, (*buf)+strlen(*buf));
  }

  if(jausUnsignedShortIsBitSet(message->presenceVector, JAUS_REPORT_CAMERA_CAPABILITIES_PV_MIN_VERTICAL_RESOLUTION_BIT))
  {
    strcat((*buf), "\nMin Vertical Resolution: ");
    jausUnsignedShortToString(message->minVerticalResolution, (*buf)+strlen(*buf));
  }

  if(jausUnsignedShortIsBitSet(message->presenceVector, JAUS_REPORT_CAMERA_CAPABILITIES_PV_MAX_FRAME_RATE_BIT))
  {
    strcat((*buf), "\nMax Frame Rate(frames per second): ");
    jausUnsignedShortToString(message->maxFrameRate, (*buf)+strlen(*buf));
  }

  if(jausUnsignedShortIsBitSet(message->presenceVector, JAUS_REPORT_CAMERA_CAPABILITIES_PV_MIN_FRAME_RATE_BIT))
  {
    strcat((*buf), "\nMin Frame Rate(frames per second): ");
    jausUnsignedShortToString(message->minFrameRate, (*buf)+strlen(*buf));
  }
  
  if(jausUnsignedShortIsBitSet(message->presenceVector, JAUS_REPORT_CAMERA_CAPABILITIES_PV_MAX_SHUTTER_SPEED_BIT))
  {
    strcat((*buf), "\nMax Shutter Speed(seconds): ");
    jausUnsignedShortToString(message->maxShutterSpeed, (*buf)+strlen(*buf));
  }

  if(jausUnsignedShortIsBitSet(message->presenceVector, JAUS_REPORT_CAMERA_CAPABILITIES_PV_MIN_SHUTTER_SPEED_BIT))
  {
    strcat((*buf), "\nMin Shutter Speed(seconds): ");
    jausUnsignedShortToString(message->minShutterSpeed, (*buf)+strlen(*buf));
  }

  // Image Control
  if(jausUnsignedShortIsBitSet(message->presenceVector, JAUS_REPORT_CAMERA_CAPABILITIES_PV_IMAGE_CONTROL_BIT))
  {
    strcat((*buf), "\nAuto Focus Available: ");
    jausBooleanToString(message->autoFocusAvailable, (*buf)+strlen(*buf));
    
    strcat((*buf), "\nAuto Exposure/Iris Available: ");
    jausBooleanToString(message->autoIrisAvailable, (*buf)+strlen(*buf));

    strcat((*buf), "\nImage Stabilization Available: ");
    jausBooleanToString(message->imageStabilizationAvailable, (*buf)+strlen(*buf));

    strcat((*buf), "\nWhite Balance Available: ");
    jausBooleanToString(message->whiteBalanceAvailable, (*buf)+strlen(*buf));

    strcat((*buf), "\nSync Flash/Strobe Available: ");
    jausBooleanToString(message->syncFlashAvailable, (*buf)+strlen(*buf));

    strcat((*buf), "\nRed Eye Available: ");
    jausBooleanToString(message->redEyeAvailable, (*buf)+strlen(*buf));

    strcat((*buf), "\nAuto Shutter Available: ");
    jausBooleanToString(message->autoShutterAvailable, (*buf)+strlen(*buf));

    strcat((*buf), "\nVideo Auto Gain Available: ");
    jausBooleanToString(message->videoAutoGainAvailable, (*buf)+strlen(*buf));

    strcat((*buf), "\nInterlaced Video Available: ");
    jausBooleanToString(message->interlacedVideoAvailable, (*buf)+strlen(*buf));
  }

  // Audio Control
  if(jausUnsignedShortIsBitSet(message->presenceVector, JAUS_REPORT_CAMERA_CAPABILITIES_PV_AUDIO_CONTROL_BIT))
  {
    strcat((*buf), "\nAudio Enabled Available: ");
    jausBooleanToString(message->audioEnabledAvailable, (*buf)+strlen(*buf));

    strcat((*buf), "\nAudio Auto Gain Available: ");
    jausBooleanToString(message->audioAutoGainAvailable, (*buf)+strlen(*buf));

    strcat((*buf), "\nStereo Audio Available: ");
    jausBooleanToString(message->stereoAudioAvailable, (*buf)+strlen(*buf));

    strcat((*buf), "\nDirectional Audio Available: ");
    jausBooleanToString(message->directionalAudioAvailable, (*buf)+strlen(*buf));

    strcat((*buf), "\nFront Microphone Available: ");
    jausBooleanToString(message->frontMicrophoneAvailable, (*buf)+strlen(*buf));

    strcat((*buf), "\nRear Microphone Available: ");
    jausBooleanToString(message->rearMicrophoneAvailable, (*buf)+strlen(*buf));

    strcat((*buf), "\nLeft Microphone Available: ");
    jausBooleanToString(message->leftMicrophoneAvailable, (*buf)+strlen(*buf));

    strcat((*buf), "\nRight Microphone Available: ");
    jausBooleanToString(message->rightMicrophoneAvailable, (*buf)+strlen(*buf));
  }
  
  return (int)strlen(*buf);
}

// Returns number of bytes put into the buffer
static unsigned int dataSize(ReportCameraCapabilitiesMessage message)
{
	int index = 0;

	// Presence Vector
	index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
	
	// CameraID
	index += JAUS_BYTE_SIZE_BYTES;

	// Camera Description
	if(jausUnsignedShortIsBitSet(message->presenceVector, JAUS_REPORT_CAMERA_CAPABILITIES_PV_DESCRIPTION_BIT))
	{
		index += JAUS_CAMERA_DESCRIPTION_LENGTH_BYTES;
	}

	if(jausUnsignedShortIsBitSet(message->presenceVector, JAUS_REPORT_CAMERA_CAPABILITIES_PV_MAX_HORIZONTAL_FOV_BIT))
	{
		index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
	}

	if(jausUnsignedShortIsBitSet(message->presenceVector, JAUS_REPORT_CAMERA_CAPABILITIES_PV_MIN_HORIZONTAL_FOV_BIT))
	{
		index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
	}

	if(jausUnsignedShortIsBitSet(message->presenceVector, JAUS_REPORT_CAMERA_CAPABILITIES_PV_MAX_VERTICAL_FOV_BIT))
	{
		index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
	}

	if(jausUnsignedShortIsBitSet(message->presenceVector, JAUS_REPORT_CAMERA_CAPABILITIES_PV_MIN_VERTICAL_FOV_BIT))
	{
		index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
	}

	if(jausUnsignedShortIsBitSet(message->presenceVector, JAUS_REPORT_CAMERA_CAPABILITIES_PV_MAX_HORIZONTAL_RESOLUTION_BIT))
	{
		index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
	}

	if(jausUnsignedShortIsBitSet(message->presenceVector, JAUS_REPORT_CAMERA_CAPABILITIES_PV_MIN_HORIZONTAL_RESOLUTION_BIT))
	{
		index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
	}

	if(jausUnsignedShortIsBitSet(message->presenceVector, JAUS_REPORT_CAMERA_CAPABILITIES_PV_MAX_VERTICAL_RESOLUTION_BIT))
	{
		index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
	}

	if(jausUnsignedShortIsBitSet(message->presenceVector, JAUS_REPORT_CAMERA_CAPABILITIES_PV_MIN_VERTICAL_RESOLUTION_BIT))
	{
		index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
	}

	if(jausUnsignedShortIsBitSet(message->presenceVector, JAUS_REPORT_CAMERA_CAPABILITIES_PV_MAX_FRAME_RATE_BIT))
	{
		index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
	}

	if(jausUnsignedShortIsBitSet(message->presenceVector, JAUS_REPORT_CAMERA_CAPABILITIES_PV_MIN_FRAME_RATE_BIT))
	{
		index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
	}
	
	if(jausUnsignedShortIsBitSet(message->presenceVector, JAUS_REPORT_CAMERA_CAPABILITIES_PV_MAX_SHUTTER_SPEED_BIT))
	{
		index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
	}

	if(jausUnsignedShortIsBitSet(message->presenceVector, JAUS_REPORT_CAMERA_CAPABILITIES_PV_MIN_SHUTTER_SPEED_BIT))
	{
		index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
	}

	// Image Control
	if(jausUnsignedShortIsBitSet(message->presenceVector, JAUS_REPORT_CAMERA_CAPABILITIES_PV_IMAGE_CONTROL_BIT))
	{
		index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
	}

	// Audio Control
	if(jausUnsignedShortIsBitSet(message->presenceVector, JAUS_REPORT_CAMERA_CAPABILITIES_PV_AUDIO_CONTROL_BIT))
	{
		index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
	}
		
	return index;
}

// ************************************************************************************************************** //
//                                    NON-USER CONFIGURED FUNCTIONS
// ************************************************************************************************************** //

ReportCameraCapabilitiesMessage reportCameraCapabilitiesMessageCreate(void)
{
	ReportCameraCapabilitiesMessage message;

	message = (ReportCameraCapabilitiesMessage)malloc( sizeof(ReportCameraCapabilitiesMessageStruct) );
	if(message == NULL)
	{
		return NULL;
	}
	
	// Initialize Values
	message->properties.priority = JAUS_DEFAULT_PRIORITY;
	message->properties.ackNak = JAUS_ACK_NAK_NOT_REQUIRED;
	message->properties.scFlag = JAUS_NOT_SERVICE_CONNECTION_MESSAGE;
	message->properties.expFlag = JAUS_NOT_EXPERIMENTAL_MESSAGE;
	message->properties.version = JAUS_VERSION_3_3;
	message->properties.reserved = 0;
	message->commandCode = commandCode;
	message->destination = jausAddressCreate();
	message->source = jausAddressCreate();
	message->dataFlag = JAUS_SINGLE_DATA_PACKET;
	message->dataSize = maxDataSizeBytes;
	message->sequenceNumber = 0;
	
	dataInitialize(message);
	message->dataSize = dataSize(message);
	
	return message;	
}

void reportCameraCapabilitiesMessageDestroy(ReportCameraCapabilitiesMessage message)
{
	dataDestroy(message);
	jausAddressDestroy(message->source);
	jausAddressDestroy(message->destination);
	free(message);
}

JausBoolean reportCameraCapabilitiesMessageFromBuffer(ReportCameraCapabilitiesMessage message, unsigned char* buffer, unsigned int bufferSizeBytes)
{
	int index = 0;
	
	if(headerFromBuffer(message, buffer+index, bufferSizeBytes-index))
	{
		index += JAUS_HEADER_SIZE_BYTES;
		if(dataFromBuffer(message, buffer+index, bufferSizeBytes-index))
		{
			return JAUS_TRUE;
		}
		else
		{
			return JAUS_FALSE;
		}
	}
	else
	{
		return JAUS_FALSE;
	}
}

JausBoolean reportCameraCapabilitiesMessageToBuffer(ReportCameraCapabilitiesMessage message, unsigned char *buffer, unsigned int bufferSizeBytes)
{
	if(bufferSizeBytes < reportCameraCapabilitiesMessageSize(message))
	{
		return JAUS_FALSE; //improper size	
	}
	else
	{	
		message->dataSize = dataToBuffer(message, buffer+JAUS_HEADER_SIZE_BYTES, bufferSizeBytes - JAUS_HEADER_SIZE_BYTES);
		if(headerToBuffer(message, buffer, bufferSizeBytes))
		{
			return JAUS_TRUE;
		}
		else
		{
			return JAUS_FALSE; // headerToReportCameraCapabilitiesBuffer failed
		}
	}
}

ReportCameraCapabilitiesMessage reportCameraCapabilitiesMessageFromJausMessage(JausMessage jausMessage)
{
	ReportCameraCapabilitiesMessage message;
	
	if(jausMessage->commandCode != commandCode)
	{
		return NULL; // Wrong message type
	}
	else
	{
		message = (ReportCameraCapabilitiesMessage)malloc( sizeof(ReportCameraCapabilitiesMessageStruct) );
		if(message == NULL)
		{
			return NULL;
		}
		
		message->properties.priority = jausMessage->properties.priority;
		message->properties.ackNak = jausMessage->properties.ackNak;
		message->properties.scFlag = jausMessage->properties.scFlag;
		message->properties.expFlag = jausMessage->properties.expFlag;
		message->properties.version = jausMessage->properties.version;
		message->properties.reserved = jausMessage->properties.reserved;
		message->commandCode = jausMessage->commandCode;
		message->destination = jausAddressCreate();
		*message->destination = *jausMessage->destination;
		message->source = jausAddressCreate();
		*message->source = *jausMessage->source;
		message->dataSize = jausMessage->dataSize;
		message->dataFlag = jausMessage->dataFlag;
		message->sequenceNumber = jausMessage->sequenceNumber;
		
		// Unpack jausMessage->data
		if(dataFromBuffer(message, jausMessage->data, jausMessage->dataSize))
		{
			return message;
		}
		else
		{
			return NULL;
		}
	}
}

JausMessage reportCameraCapabilitiesMessageToJausMessage(ReportCameraCapabilitiesMessage message)
{
	JausMessage jausMessage;
	
	jausMessage = (JausMessage)malloc( sizeof(struct JausMessageStruct) );
	if(jausMessage == NULL)
	{
		return NULL;
	}	
	
	jausMessage->properties.priority = message->properties.priority;
	jausMessage->properties.ackNak = message->properties.ackNak;
	jausMessage->properties.scFlag = message->properties.scFlag;
	jausMessage->properties.expFlag = message->properties.expFlag;
	jausMessage->properties.version = message->properties.version;
	jausMessage->properties.reserved = message->properties.reserved;
	jausMessage->commandCode = message->commandCode;
	jausMessage->destination = jausAddressCreate();
	*jausMessage->destination = *message->destination;
	jausMessage->source = jausAddressCreate();
	*jausMessage->source = *message->source;
	jausMessage->dataSize = dataSize(message);
	jausMessage->dataFlag = message->dataFlag;
	jausMessage->sequenceNumber = message->sequenceNumber;
	
	jausMessage->data = (unsigned char *)malloc(jausMessage->dataSize);
	jausMessage->dataSize = dataToBuffer(message, jausMessage->data, jausMessage->dataSize);
	
	return jausMessage;
}

unsigned int reportCameraCapabilitiesMessageSize(ReportCameraCapabilitiesMessage message)
{
	return (unsigned int)(dataSize(message) + JAUS_HEADER_SIZE_BYTES);
}

char* reportCameraCapabilitiesMessageToString(ReportCameraCapabilitiesMessage message)
{
  if(message)
  {
    char* buf1 = NULL;
    char* buf2 = NULL;
    char* buf = NULL;
    
    int returnVal;
    
    //Print the message header to the string buffer
    returnVal = headerToString(message, &buf1);
    
    //Print the message data fields to the string buffer
    returnVal += dataToString(message, &buf2);
    
buf = (char*)malloc(strlen(buf1)+strlen(buf2)+1);
    strcpy(buf, buf1);
    strcat(buf, buf2);

    free(buf1);
    free(buf2);
    
    return buf;
  }
  else
  {
    char* buf = "Invalid ReportCameraCapabilities Message";
    char* msg = (char*)malloc(strlen(buf)+1);
    strcpy(msg, buf);
    return msg;
  }
}
//********************* PRIVATE HEADER FUNCTIONS **********************//

static JausBoolean headerFromBuffer(ReportCameraCapabilitiesMessage message, unsigned char *buffer, unsigned int bufferSizeBytes)
{
	if(bufferSizeBytes < JAUS_HEADER_SIZE_BYTES)
	{
		return JAUS_FALSE;
	}
	else
	{
		// unpack header
		message->properties.priority = (buffer[0] & 0x0F);
		message->properties.ackNak	 = ((buffer[0] >> 4) & 0x03);
		message->properties.scFlag	 = ((buffer[0] >> 6) & 0x01);
		message->properties.expFlag	 = ((buffer[0] >> 7) & 0x01);
		message->properties.version	 = (buffer[1] & 0x3F);
		message->properties.reserved = ((buffer[1] >> 6) & 0x03);
		
		message->commandCode = buffer[2] + (buffer[3] << 8);
	
		message->destination->instance = buffer[4];
		message->destination->component = buffer[5];
		message->destination->node = buffer[6];
		message->destination->subsystem = buffer[7];
	
		message->source->instance = buffer[8];
		message->source->component = buffer[9];
		message->source->node = buffer[10];
		message->source->subsystem = buffer[11];
		
		message->dataSize = buffer[12] + ((buffer[13] & 0x0F) << 8);

		message->dataFlag = ((buffer[13] >> 4) & 0x0F);

		message->sequenceNumber = buffer[14] + (buffer[15] << 8);
		
		return JAUS_TRUE;
	}
}

static JausBoolean headerToBuffer(ReportCameraCapabilitiesMessage message, unsigned char *buffer, unsigned int bufferSizeBytes)
{
	JausUnsignedShort *propertiesPtr = (JausUnsignedShort*)&message->properties;
	
	if(bufferSizeBytes < JAUS_HEADER_SIZE_BYTES)
	{
		return JAUS_FALSE;
	}
	else
	{	
		buffer[0] = (unsigned char)(*propertiesPtr & 0xFF);
		buffer[1] = (unsigned char)((*propertiesPtr & 0xFF00) >> 8);

		buffer[2] = (unsigned char)(message->commandCode & 0xFF);
		buffer[3] = (unsigned char)((message->commandCode & 0xFF00) >> 8);

		buffer[4] = (unsigned char)(message->destination->instance & 0xFF);
		buffer[5] = (unsigned char)(message->destination->component & 0xFF);
		buffer[6] = (unsigned char)(message->destination->node & 0xFF);
		buffer[7] = (unsigned char)(message->destination->subsystem & 0xFF);

		buffer[8] = (unsigned char)(message->source->instance & 0xFF);
		buffer[9] = (unsigned char)(message->source->component & 0xFF);
		buffer[10] = (unsigned char)(message->source->node & 0xFF);
		buffer[11] = (unsigned char)(message->source->subsystem & 0xFF);
		
		buffer[12] = (unsigned char)(message->dataSize & 0xFF);
		buffer[13] = (unsigned char)((message->dataFlag & 0xFF) << 4) | (unsigned char)((message->dataSize & 0x0F00) >> 8);

		buffer[14] = (unsigned char)(message->sequenceNumber & 0xFF);
		buffer[15] = (unsigned char)((message->sequenceNumber & 0xFF00) >> 8);
		
		return JAUS_TRUE;
	}
}

static int headerToString(ReportCameraCapabilitiesMessage message, char **buf)
{
  //message existance already verified 

  //Setup temporary string buffer
  
  unsigned int bufSize = 500;
  (*buf) = (char*)malloc(sizeof(char)*bufSize);
  
  strcpy((*buf), jausCommandCodeString(message->commandCode) );
  strcat((*buf), " (0x");
  sprintf((*buf)+strlen(*buf), "%04X", message->commandCode);

  strcat((*buf), ")\nReserved: ");
  jausUnsignedShortToString(message->properties.reserved, (*buf)+strlen(*buf));

  strcat((*buf), "\nVersion: ");
  switch(message->properties.version)
  {
    case 0:
      strcat((*buf), "2.0 and 2.1 compatible");
      break;
    case 1:
      strcat((*buf), "3.0 through 3.1 compatible");
      break;
    case 2:
      strcat((*buf), "3.2 and 3.3 compatible");
      break;
    default:
      strcat((*buf), "Reserved for Future: ");
      jausUnsignedShortToString(message->properties.version, (*buf)+strlen(*buf));
      break;
  }

  strcat((*buf), "\nExp. Flag: ");
  if(message->properties.expFlag == 0)
    strcat((*buf), "JAUS");
  else 
    strcat((*buf), "Experimental");
  
  strcat((*buf), "\nSC Flag: ");
  if(message->properties.scFlag == 0)
    strcat((*buf), "Service Connection");
  else
    strcat((*buf), "Not Service Connection");
  
  strcat((*buf), "\nACK/NAK: ");
  switch(message->properties.ackNak)
  {
  case 0:
    strcat((*buf), "None");
    break;
  case 1:
    strcat((*buf), "Request ack/nak");
    break;
  case 2:
    strcat((*buf), "nak response");
    break;
  case 3:
    strcat((*buf), "ack response");
    break;
  default:
    break;
  }
  
  strcat((*buf), "\nPriority: ");
  if(message->properties.priority < 12)
  {
    strcat((*buf), "Normal Priority ");
    jausUnsignedShortToString(message->properties.priority, (*buf)+strlen(*buf));
  }
  else
  {
    strcat((*buf), "Safety Critical Priority ");
    jausUnsignedShortToString(message->properties.priority, (*buf)+strlen(*buf));
  }
  
  strcat((*buf), "\nSource: ");
  jausAddressToString(message->source, (*buf)+strlen(*buf));
  
  strcat((*buf), "\nDestination: ");
  jausAddressToString(message->destination, (*buf)+strlen(*buf));
  
  strcat((*buf), "\nData Size: ");
  jausUnsignedIntegerToString(message->dataSize, (*buf)+strlen(*buf));
  
  strcat((*buf), "\nData Flag: ");
  jausUnsignedIntegerToString(message->dataFlag, (*buf)+strlen(*buf));
  switch(message->dataFlag)
  {
    case 0:
      strcat((*buf), " Only data packet in single-packet stream");
      break;
    case 1:
      strcat((*buf), " First data packet in muti-packet stream");
      break;
    case 2:
      strcat((*buf), " Normal data packet");
      break;
    case 4:
      strcat((*buf), " Retransmitted data packet");
      break;
    case 8:
      strcat((*buf), " Last data packet in stream");
      break;
    default:
      strcat((*buf), " Unrecognized data flag code");
      break;
  }
  
  strcat((*buf), "\nSequence Number: ");
  jausUnsignedShortToString(message->sequenceNumber, (*buf)+strlen(*buf));
  
  return (int)strlen(*buf);
  
}
