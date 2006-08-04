// File Name: reportPlatformSpecificationsMessage.c
//
// Written By: Danny Kent (jaus AT dannykent DOT com), Tom Galluzzo (galluzzo AT gmail DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines the functionality of a ReportPlatformSpecificationsMessage



#include <stdlib.h>
#include <string.h>
#include "cimar/jaus.h"

static const int commandCode = JAUS_REPORT_PLATFORM_SPECIFICATIONS;
static const int maxDataSizeBytes = 59;

static JausBoolean headerFromBuffer(ReportPlatformSpecificationsMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);
static JausBoolean headerToBuffer(ReportPlatformSpecificationsMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);

static JausBoolean dataFromBuffer(ReportPlatformSpecificationsMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);
static int dataToBuffer(ReportPlatformSpecificationsMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);
static void dataInitialize(ReportPlatformSpecificationsMessage message);

// ************************************************************************************************************** //
//                                    USER CONFIGURED FUNCTIONS
// ************************************************************************************************************** //

// Initializes the message-specific fields
static void dataInitialize(ReportPlatformSpecificationsMessage message)
{
	// Set initial values of message fields
	message->presenceVector = newJausIntegerPresenceVector();
	message->platformName[0] = 0;
	message-> frontMeters= newJausDouble(0);			// Scaled Unsigned Short (0, 32.767)
	message-> backMeters= newJausDouble(0);				// Scaled Unsigned Short (0, 32.767)
	message-> rightMeters= newJausDouble(0);			// Scaled Unsigned Short (0, 32.767)
	message-> leftMeters= newJausDouble(0);				// Scaled Unsigned Short (0, 32.767)
	message-> bottomMeters= newJausDouble(0);			// Scaled Unsigned Short (0, 32.767)
	message-> topMeters= newJausDouble(0);				// Scaled Unsigned Short (0, 32.767)
	message-> xCgMeters= newJausDouble(0);				// Scaled Unsigned Short (0, 32.767)
	message-> yCgMeters= newJausDouble(0);				// Scaled Unsigned Short (0, 32.767)
	message-> zCgMeters= newJausDouble(0);				// Scaled Unsigned Short (0, 32.767)
	message-> turningRadiusMeters= newJausDouble(0); 	// Scaled Unsigned Short (0, 65.535)
	message-> wheelBaseMeters= newJausDouble(0); 		// Scaled Unsigned Short (0, 65.535)
	message-> trackWidthMeters= newJausDouble(0); 		// Scaled Unsigned Short (0, 65.535)
	message-> pitchOverRadians= newJausDouble(0);		// Scaled Unsigned Short (0, 2.56)
	message-> rollOverRadians= newJausDouble(0);		// Scaled Unsigned Short (0, 2.56)
	message-> maximumVelocityXMps= newJausDouble(0);	// Scaled Unsigned Short (0, 65.535) Mps = Meters per Second
	message-> maximumVelocityYMps= newJausDouble(0);	// Scaled Unsigned Short (0, 65.535) Mps = Meters per Second
	message-> maximumVelocityZMps= newJausDouble(0);	// Scaled Unsigned Short (0, 65.535) Mps = Meters per Second		
	message-> maximumRollRateRps= newJausDouble(0);		// Scaled Unsigned Short (0, 32.767) Rps = Radians per Second
	message-> maximumPitchRateRps= newJausDouble(0);	// Scaled Unsigned Short (0, 32.767) Rps = Radians per Second
	message-> maximumYawRateRps= newJausDouble(0);		// Scaled Unsigned Short (0, 32.767) Rps = Radians per Second	
}

// Return boolean of success
static JausBoolean dataFromBuffer(ReportPlatformSpecificationsMessage message, unsigned char *buffer, unsigned int bufferSizeBytes)
{
	int index = 0;
	JausUnsignedShort tempUShort;
	
	if(bufferSizeBytes == message->dataSize)
	{
		// Unpack Message Fields from Buffer
		// Unpack Using Presence Vector
		if(!jausIntegerPresenceVectorFromBuffer(&message->presenceVector, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
		index += JAUS_INTEGER_PRESENCE_VECTOR_SIZE_BYTES;

		if(jausIntegerPresenceVectorIsBitSet(message->presenceVector, JAUS_DISCRETE_PV_PLATFORM_NAME_BIT))
		{
			// unpack string of length JAUS_PLATFORM_NAME_LENGTH_BYTES
			if(bufferSizeBytes-index < JAUS_PLATFORM_NAME_LENGTH_BYTES) return JAUS_FALSE;
			
			memcpy(&message->platformName, buffer+index, JAUS_PLATFORM_NAME_LENGTH_BYTES);
			index += JAUS_PLATFORM_NAME_LENGTH_BYTES;
		}
		
		if(jausIntegerPresenceVectorIsBitSet(message->presenceVector, JAUS_DISCRETE_PV_FRONT_BIT))
		{
			// unpack
			if(!jausUnsignedShortFromBuffer(&tempUShort, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
			
			// Scaled Unsigned Short (0, 32.767)
			message->frontMeters = jausUnsignedShortToDouble(tempUShort, 0, 32.767);
		}

		if(jausIntegerPresenceVectorIsBitSet(message->presenceVector, JAUS_DISCRETE_PV_BACK_BIT))
		{
			// unpack
			if(!jausUnsignedShortFromBuffer(&tempUShort, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
			
			// Scaled Unsigned Short (0, 32.767)
			message->backMeters = jausUnsignedShortToDouble(tempUShort, 0, 32.767);
		}

		if(jausIntegerPresenceVectorIsBitSet(message->presenceVector, JAUS_DISCRETE_PV_RIGHT_BIT))
		{
			// unpack
			if(!jausUnsignedShortFromBuffer(&tempUShort, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
			
			// Scaled Unsigned Short (0, 32.767)
			message->rightMeters = jausUnsignedShortToDouble(tempUShort, 0, 32.767);
		}

		if(jausIntegerPresenceVectorIsBitSet(message->presenceVector, JAUS_DISCRETE_PV_LEFT_BIT))
		{
			// unpack
			if(!jausUnsignedShortFromBuffer(&tempUShort, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
			
			// Scaled Unsigned Short (0, 32.767)
			message->leftMeters = jausUnsignedShortToDouble(tempUShort, 0, 32.767);
		}

		if(jausIntegerPresenceVectorIsBitSet(message->presenceVector, JAUS_DISCRETE_PV_BOTTOM_BIT))
		{
			// unpack
			if(!jausUnsignedShortFromBuffer(&tempUShort, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
			
			// Scaled Unsigned Short (0, 32.767)
			message->bottomMeters = jausUnsignedShortToDouble(tempUShort, 0, 32.767);
		}

		if(jausIntegerPresenceVectorIsBitSet(message->presenceVector, JAUS_DISCRETE_PV_TOP_BIT))
		{
			// unpack
			if(!jausUnsignedShortFromBuffer(&tempUShort, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
			
			// Scaled Unsigned Short (0, 32.767)
			message->topMeters = jausUnsignedShortToDouble(tempUShort, 0, 32.767);
		}

		if(jausIntegerPresenceVectorIsBitSet(message->presenceVector, JAUS_DISCRETE_PV_X_CG_BIT))
		{
			// unpack
			if(!jausUnsignedShortFromBuffer(&tempUShort, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
			
			// Scaled Unsigned Short (0, 32.767)
			message->xCgMeters = jausUnsignedShortToDouble(tempUShort, 0, 32.767);
		}

		if(jausIntegerPresenceVectorIsBitSet(message->presenceVector, JAUS_DISCRETE_PV_Y_CG_BIT))
		{
			// unpack
			if(!jausUnsignedShortFromBuffer(&tempUShort, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
			
			// Scaled Unsigned Short (0, 32.767)
			message->yCgMeters = jausUnsignedShortToDouble(tempUShort, 0, 32.767);
		}

		if(jausIntegerPresenceVectorIsBitSet(message->presenceVector, JAUS_DISCRETE_PV_Z_CG_BIT))
		{
			// unpack
			if(!jausUnsignedShortFromBuffer(&tempUShort, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
			
			// Scaled Unsigned Short (0, 32.767)
			message->zCgMeters = jausUnsignedShortToDouble(tempUShort, 0, 32.767);
		}

		if(jausIntegerPresenceVectorIsBitSet(message->presenceVector, JAUS_DISCRETE_PV_TURNING_RADIUS_BIT))
		{
			// unpack
			if(!jausUnsignedShortFromBuffer(&tempUShort, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
			
			// Scaled Unsigned Short (0, 65.535)
			message->turningRadiusMeters = jausUnsignedShortToDouble(tempUShort, 0, 65.535);
		}

		if(jausIntegerPresenceVectorIsBitSet(message->presenceVector, JAUS_DISCRETE_PV_WHEEL_BASE_BIT))
		{
			// unpack
			if(!jausUnsignedShortFromBuffer(&tempUShort, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
			
			// Scaled Unsigned Short (0, 65.535)
			message->wheelBaseMeters = jausUnsignedShortToDouble(tempUShort, 0, 65.535);
		}
		
		if(jausIntegerPresenceVectorIsBitSet(message->presenceVector, JAUS_DISCRETE_PV_TRACK_WIDTH_BIT))
		{
			// unpack
			if(!jausUnsignedShortFromBuffer(&tempUShort, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
			
			// Scaled Unsigned Short (0, 65.535)
			message->trackWidthMeters = jausUnsignedShortToDouble(tempUShort, 0, 65.535);
		}

		if(jausIntegerPresenceVectorIsBitSet(message->presenceVector, JAUS_DISCRETE_PV_PITCH_OVER_BIT))
		{
			// unpack
			if(!jausUnsignedShortFromBuffer(&tempUShort, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
			
			// Scaled Unsigned Short (0, 2.56)
			message->pitchOverRadians = jausUnsignedShortToDouble(tempUShort, 0, 2.56);
		}
		
		if(jausIntegerPresenceVectorIsBitSet(message->presenceVector, JAUS_DISCRETE_PV_ROLL_OVER_BIT))
		{
			// unpack
			if(!jausUnsignedShortFromBuffer(&tempUShort, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
			
			// Scaled Unsigned Short (0, 2.56)
			message->rollOverRadians = jausUnsignedShortToDouble(tempUShort, 0, 2.56);
		}
		
		if(jausIntegerPresenceVectorIsBitSet(message->presenceVector, JAUS_DISCRETE_PV_MAX_VELOCITY_X_BIT))
		{
			// unpack
			if(!jausUnsignedShortFromBuffer(&tempUShort, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
			
			// Scaled Unsigned Short (0, 65.535)
			message->maximumVelocityXMps = jausUnsignedShortToDouble(tempUShort, 0, 65.535);
		}
		
		if(jausIntegerPresenceVectorIsBitSet(message->presenceVector, JAUS_DISCRETE_PV_MAX_VELOCITY_Y_BIT))
		{
			// unpack
			if(!jausUnsignedShortFromBuffer(&tempUShort, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
			
			// Scaled Unsigned Short (0, 65.535)
			message->maximumVelocityYMps = jausUnsignedShortToDouble(tempUShort, 0, 65.535);
		}

		if(jausIntegerPresenceVectorIsBitSet(message->presenceVector, JAUS_DISCRETE_PV_MAX_VELOCITY_Z_BIT))
		{
			// unpack
			if(!jausUnsignedShortFromBuffer(&tempUShort, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
			
			// Scaled Unsigned Short (0, 65.535)
			message->maximumVelocityZMps = jausUnsignedShortToDouble(tempUShort, 0, 65.535);
		}

		if(jausIntegerPresenceVectorIsBitSet(message->presenceVector, JAUS_DISCRETE_PV_MAX_ROLL_RATE_BIT))
		{
			// unpack
			if(!jausUnsignedShortFromBuffer(&tempUShort, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
			
			// Scaled Unsigned Short (0, 32.767)
			message->maximumRollRateRps = jausUnsignedShortToDouble(tempUShort, 0, 32.767);
		}
		
		if(jausIntegerPresenceVectorIsBitSet(message->presenceVector, JAUS_DISCRETE_PV_MAX_PITCH_RATE_BIT))
		{
			// unpack
			if(!jausUnsignedShortFromBuffer(&tempUShort, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
			
			// Scaled Unsigned Short (0, 32.767)
			message->maximumPitchRateRps = jausUnsignedShortToDouble(tempUShort, 0, 32.767);
		}

		if(jausIntegerPresenceVectorIsBitSet(message->presenceVector, JAUS_DISCRETE_PV_MAX_YAW_RATE_BIT))
		{
			// unpack
			if(!jausUnsignedShortFromBuffer(&tempUShort, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
			
			// Scaled Unsigned Short (0, 32.767)
			message->maximumYawRateRps = jausUnsignedShortToDouble(tempUShort, 0, 32.767);
		}

		
		return JAUS_TRUE;
	}
	else
	{
		return JAUS_FALSE;
	}
}

// Returns number of bytes put into the buffer
static int dataToBuffer(ReportPlatformSpecificationsMessage message, unsigned char *buffer, unsigned int bufferSizeBytes)
{
	int index = 0;
	JausUnsignedShort tempUShort;

	if(bufferSizeBytes >= message->dataSize)
	{
		// Pack Message Fields to Buffer
		// Pack using Presence Vector
		if(!jausIntegerPresenceVectorToBuffer(message->presenceVector, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
		index += JAUS_INTEGER_PRESENCE_VECTOR_SIZE_BYTES;

		if(jausIntegerPresenceVectorIsBitSet(message->presenceVector, JAUS_DISCRETE_PV_PLATFORM_NAME_BIT))
		{
			// pack string of length JAUS_PLATFORM_NAME_LENGTH_BYTES
			if(bufferSizeBytes-index < JAUS_PLATFORM_NAME_LENGTH_BYTES) return JAUS_FALSE;
			
			memcpy(buffer+index, &message->platformName, JAUS_PLATFORM_NAME_LENGTH_BYTES);
			index += JAUS_PLATFORM_NAME_LENGTH_BYTES;
		}

		if(jausIntegerPresenceVectorIsBitSet(message->presenceVector, JAUS_DISCRETE_PV_FRONT_BIT))
		{
			// Scaled Unsigned Short (0, 32.767)
			tempUShort = jausUnsignedShortFromDouble(message->frontMeters, 0, 32.767);

			// pack
			if(!jausUnsignedShortToBuffer(tempUShort, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
		}

		if(jausIntegerPresenceVectorIsBitSet(message->presenceVector, JAUS_DISCRETE_PV_BACK_BIT))
		{
			// Scaled Unsigned Short (0, 32.767)
			tempUShort = jausUnsignedShortFromDouble(message->backMeters, 0, 32.767);

			// pack
			if(!jausUnsignedShortToBuffer(tempUShort, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
		}

		if(jausIntegerPresenceVectorIsBitSet(message->presenceVector, JAUS_DISCRETE_PV_RIGHT_BIT))
		{
			// Scaled Unsigned Short (0, 32.767)
			tempUShort = jausUnsignedShortFromDouble(message->rightMeters, 0, 32.767);

			// pack
			if(!jausUnsignedShortToBuffer(tempUShort, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
		}

		if(jausIntegerPresenceVectorIsBitSet(message->presenceVector, JAUS_DISCRETE_PV_LEFT_BIT))
		{
			// Scaled Unsigned Short (0, 32.767)
			tempUShort = jausUnsignedShortFromDouble(message->leftMeters, 0, 32.767);

			// pack
			if(!jausUnsignedShortToBuffer(tempUShort, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
		}

		if(jausIntegerPresenceVectorIsBitSet(message->presenceVector, JAUS_DISCRETE_PV_BOTTOM_BIT))
		{
			// Scaled Unsigned Short (0, 32.767)
			tempUShort = jausUnsignedShortFromDouble(message->bottomMeters, 0, 32.767);

			// pack
			if(!jausUnsignedShortToBuffer(tempUShort, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
		}

		if(jausIntegerPresenceVectorIsBitSet(message->presenceVector, JAUS_DISCRETE_PV_TOP_BIT))
		{
			// Scaled Unsigned Short (0, 32.767)
			tempUShort = jausUnsignedShortFromDouble(message->topMeters, 0, 32.767);

			// pack
			if(!jausUnsignedShortToBuffer(tempUShort, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
		}

		if(jausIntegerPresenceVectorIsBitSet(message->presenceVector, JAUS_DISCRETE_PV_X_CG_BIT))
		{
			// Scaled Unsigned Short (0, 32.767)
			tempUShort = jausUnsignedShortFromDouble(message->xCgMeters, 0, 32.767);

			// pack
			if(!jausUnsignedShortToBuffer(tempUShort, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
		}

		if(jausIntegerPresenceVectorIsBitSet(message->presenceVector, JAUS_DISCRETE_PV_Y_CG_BIT))
		{
			// Scaled Unsigned Short (0, 32.767)
			tempUShort = jausUnsignedShortFromDouble(message->yCgMeters, 0, 32.767);

			// pack
			if(!jausUnsignedShortToBuffer(tempUShort, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
		}

		if(jausIntegerPresenceVectorIsBitSet(message->presenceVector, JAUS_DISCRETE_PV_Z_CG_BIT))
		{
			// Scaled Unsigned Short (0, 32.767)
			tempUShort = jausUnsignedShortFromDouble(message->zCgMeters, 0, 32.767);

			// pack
			if(!jausUnsignedShortToBuffer(tempUShort, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
		}

		if(jausIntegerPresenceVectorIsBitSet(message->presenceVector, JAUS_DISCRETE_PV_TURNING_RADIUS_BIT))
		{
			// Scaled Unsigned Short (0, 65.535)
			tempUShort = jausUnsignedShortFromDouble(message->turningRadiusMeters, 0, 65.535);

			// pack
			if(!jausUnsignedShortToBuffer(tempUShort, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
		}

		if(jausIntegerPresenceVectorIsBitSet(message->presenceVector, JAUS_DISCRETE_PV_WHEEL_BASE_BIT))
		{
			// Scaled Unsigned Short (0, 65.535)
			tempUShort = jausUnsignedShortFromDouble(message->wheelBaseMeters, 0, 65.535);

			// pack
			if(!jausUnsignedShortToBuffer(tempUShort, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
		}

		if(jausIntegerPresenceVectorIsBitSet(message->presenceVector, JAUS_DISCRETE_PV_TRACK_WIDTH_BIT))
		{
			// Scaled Unsigned Short (0, 65.535)
			tempUShort = jausUnsignedShortFromDouble(message->trackWidthMeters, 0, 65.535);

			// pack
			if(!jausUnsignedShortToBuffer(tempUShort, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
		}

		if(jausIntegerPresenceVectorIsBitSet(message->presenceVector, JAUS_DISCRETE_PV_PITCH_OVER_BIT))
		{
			// Scaled Unsigned Short (0, 2.56)
			tempUShort = jausUnsignedShortFromDouble(message->pitchOverRadians, 0, 2.56);

			// pack
			if(!jausUnsignedShortToBuffer(tempUShort, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
		}

		if(jausIntegerPresenceVectorIsBitSet(message->presenceVector, JAUS_DISCRETE_PV_ROLL_OVER_BIT))
		{
			// Scaled Unsigned Short (0, 2.56)
			tempUShort = jausUnsignedShortFromDouble(message->rollOverRadians, 0, 2.56);

			// pack
			if(!jausUnsignedShortToBuffer(tempUShort, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
		}

		if(jausIntegerPresenceVectorIsBitSet(message->presenceVector, JAUS_DISCRETE_PV_MAX_VELOCITY_X_BIT))
		{
			// Scaled Unsigned Short (0, 65.535)
			tempUShort = jausUnsignedShortFromDouble(message->maximumVelocityXMps, 0, 65.535);

			// pack
			if(!jausUnsignedShortToBuffer(tempUShort, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
		}

		if(jausIntegerPresenceVectorIsBitSet(message->presenceVector, JAUS_DISCRETE_PV_MAX_VELOCITY_Y_BIT))
		{
			// Scaled Unsigned Short (0, 65.535)
			tempUShort = jausUnsignedShortFromDouble(message->maximumVelocityYMps, 0, 65.535);

			// pack
			if(!jausUnsignedShortToBuffer(tempUShort, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
		}

		if(jausIntegerPresenceVectorIsBitSet(message->presenceVector, JAUS_DISCRETE_PV_MAX_VELOCITY_Z_BIT))
		{
			// Scaled Unsigned Short (0, 65.535)
			tempUShort = jausUnsignedShortFromDouble(message->maximumVelocityZMps, 0, 65.535);

			// pack
			if(!jausUnsignedShortToBuffer(tempUShort, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
		}

		if(jausIntegerPresenceVectorIsBitSet(message->presenceVector, JAUS_DISCRETE_PV_MAX_ROLL_RATE_BIT))
		{
			// Scaled Unsigned Short (0, 32.767)
			tempUShort = jausUnsignedShortFromDouble(message->maximumRollRateRps, 0, 32.767);

			// pack
			if(!jausUnsignedShortToBuffer(tempUShort, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
		}

		if(jausIntegerPresenceVectorIsBitSet(message->presenceVector, JAUS_DISCRETE_PV_MAX_PITCH_RATE_BIT))
		{
			// Scaled Unsigned Short (0, 32.767)
			tempUShort = jausUnsignedShortFromDouble(message->maximumPitchRateRps, 0, 32.767);

			// pack
			if(!jausUnsignedShortToBuffer(tempUShort, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
		}

		if(jausIntegerPresenceVectorIsBitSet(message->presenceVector, JAUS_DISCRETE_PV_MAX_YAW_RATE_BIT))
		{
			// Scaled Unsigned Short (0, 32.767)
			tempUShort = jausUnsignedShortFromDouble(message->maximumYawRateRps, 0, 32.767);

			// pack
			if(!jausUnsignedShortToBuffer(tempUShort, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
		}

	}

	return index;
}

// ************************************************************************************************************** //
//                                    NON-USER CONFIGURED FUNCTIONS
// ************************************************************************************************************** //

ReportPlatformSpecificationsMessage reportPlatformSpecificationsMessageCreate(void)
{
	ReportPlatformSpecificationsMessage message;

	message = (ReportPlatformSpecificationsMessage)malloc( sizeof(ReportPlatformSpecificationsMessageStruct) );
	if(message == NULL)
	{
		return NULL;
	}
	
	// Initialize Values
	message->priority = JAUS_DEFAULT_PRIORITY;
	message->ackNak = JAUS_ACK_NAK_NOT_REQUIRED;
	message->scFlag = JAUS_NOT_SERVICE_CONNECTION_MESSAGE;
	message->expFlag = JAUS_NOT_EXPERIMENTAL_MESSAGE;
	message->version = JAUS_VERSION_3_2;
	message->reserved = 0;
	message->commandCode = commandCode;
	message->destination = jausAddressCreate();
	message->source = jausAddressCreate();
	message->dataFlag = JAUS_SINGLE_DATA_PACKET;
	message->dataSize = maxDataSizeBytes;
	message->sequenceNumber = 0;
	
	dataInitialize(message);
	
	return message;	
}

void reportPlatformSpecificationsMessageDestroy(ReportPlatformSpecificationsMessage message)
{
	jausAddressDestroy(message->source);
	jausAddressDestroy(message->destination);
	free(message);
}

JausBoolean reportPlatformSpecificationsMessageFromBuffer(ReportPlatformSpecificationsMessage message, unsigned char* buffer, unsigned int bufferSizeBytes)
{
	int index = 0;
	
	if(!strncmp((char *)buffer, JAUS_UDP_HEADER, JAUS_UDP_HEADER_SIZE_BYTES)) // equals 1 if same
	{
		index += JAUS_UDP_HEADER_SIZE_BYTES;
	}

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

JausBoolean reportPlatformSpecificationsMessageToBuffer(ReportPlatformSpecificationsMessage message, unsigned char *buffer, unsigned int bufferSizeBytes)
{
	if(bufferSizeBytes < reportPlatformSpecificationsMessageSize(message))
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
			return JAUS_FALSE; // headerToReportPlatformSpecificationsBuffer failed
		}
	}
}

JausBoolean reportPlatformSpecificationsMessageToUdpBuffer(ReportPlatformSpecificationsMessage message, unsigned char *buffer, unsigned int bufferSizeBytes)
{
	if(bufferSizeBytes < reportPlatformSpecificationsMessageUdpSize(message))
	{
		return JAUS_FALSE; // improper size
	}
	else
	{
		strncpy((char *)buffer, JAUS_UDP_HEADER, JAUS_UDP_HEADER_SIZE_BYTES); //copies the UDP header into the buffer
		return reportPlatformSpecificationsMessageToBuffer(message, buffer+JAUS_UDP_HEADER_SIZE_BYTES, bufferSizeBytes - JAUS_UDP_HEADER_SIZE_BYTES);
	}
}

ReportPlatformSpecificationsMessage reportPlatformSpecificationsMessageFromJausMessage(JausMessage jausMessage)
{
	ReportPlatformSpecificationsMessage message;
	
	if(jausMessage->commandCode != commandCode)
	{
		return NULL; // Wrong message type
	}
	else
	{
		message = (ReportPlatformSpecificationsMessage)malloc( sizeof(ReportPlatformSpecificationsMessageStruct) );
		if(message == NULL)
		{
			return NULL;
		}
		
		message->properties = jausMessage->properties;
		message->commandCode = jausMessage->commandCode;
		message->destination = jausAddressCreate();
		message->destination->id = jausMessage->destination->id;
		message->source = jausAddressCreate();
		message->source->id = jausMessage->source->id;
		message->dataControl = jausMessage->dataControl;
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

JausMessage reportPlatformSpecificationsMessageToJausMessage(ReportPlatformSpecificationsMessage message)
{
	JausMessage jausMessage;
	
	jausMessage = (JausMessage)malloc( sizeof(JausMessageStruct) );
	if(jausMessage == NULL)
	{
		return NULL;
	}	
	
	jausMessage->properties = message->properties;
	jausMessage->commandCode = message->commandCode;
	jausMessage->destination = jausAddressCreate();
	jausMessage->destination->id = message->destination->id;
	jausMessage->source = jausAddressCreate();
	jausMessage->source->id = message->source->id;
	jausMessage->dataControl = message->dataControl;
	jausMessage->sequenceNumber = message->sequenceNumber;
	
	jausMessage->data = (unsigned char *)malloc(message->dataSize);
	jausMessage->dataSize = dataToBuffer(message, jausMessage->data, message->dataSize);
	
	return jausMessage;
}

unsigned int reportPlatformSpecificationsMessageUdpSize(ReportPlatformSpecificationsMessage message)
{
	return (unsigned int)(message->dataSize + JAUS_HEADER_SIZE_BYTES + JAUS_UDP_HEADER_SIZE_BYTES);
}

unsigned int reportPlatformSpecificationsMessageSize(ReportPlatformSpecificationsMessage message)
{
	return (unsigned int)(message->dataSize + JAUS_HEADER_SIZE_BYTES);
}

//********************* PRIVATE HEADER FUNCTIONS **********************//

static JausBoolean headerFromBuffer(ReportPlatformSpecificationsMessage message, unsigned char *buffer, unsigned int bufferSizeBytes)
{
	if(bufferSizeBytes < JAUS_HEADER_SIZE_BYTES)
	{
		return JAUS_FALSE;
	}
	else
	{
		// unpack header
		message->properties = buffer[0] + (buffer[1] << 8);
		message->commandCode = buffer[2] + (buffer[3] << 8);
	
		message->destination->instance = buffer[4];
		message->destination->component = buffer[5];
		message->destination->node = buffer[6];
		message->destination->subsystem = buffer[7];
	
		message->source->instance = buffer[8];
		message->source->component = buffer[9];
		message->source->node = buffer[10];
		message->source->subsystem = buffer[11];
		
		message->dataControl = buffer[12] + (buffer[13] << 8);
		message->sequenceNumber = buffer[14] + (buffer[15] << 8);
		
		return JAUS_TRUE;
	}
}

static JausBoolean headerToBuffer(ReportPlatformSpecificationsMessage message, unsigned char *buffer, unsigned int bufferSizeBytes)
{
	if(bufferSizeBytes < JAUS_HEADER_SIZE_BYTES)
	{
		return JAUS_FALSE;
	}
	else
	{	
		buffer[0] = (unsigned char)(message->properties & 0xFF);
		buffer[1] = (unsigned char)((message->properties & 0xFF00) >> 8);

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
		
		buffer[12] = (unsigned char)(message->dataControl & 0xFF);
		buffer[13] = (unsigned char)((message->dataControl & 0xFF00) >> 8);

		buffer[14] = (unsigned char)(message->sequenceNumber & 0xFF);
		buffer[15] = (unsigned char)((message->sequenceNumber & 0xFF00) >> 8);
		
		return JAUS_TRUE;
	}
}

