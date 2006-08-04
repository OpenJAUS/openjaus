// File Name: reportGlobalPoseMessage.c
//
// Written By: Danny Kent (jaus AT dannykent DOT com), Tom Galluzzo (galluzzo AT gmail DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines the functionality of a ReportGlobalPoseMessage



#include <stdlib.h>
#include <string.h>
#include "cimar/jaus.h"

static const int commandCode = JAUS_REPORT_GLOBAL_POSE;
static const int maxDataSizeBytes = 30;

static JausBoolean headerFromBuffer(ReportGlobalPoseMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);
static JausBoolean headerToBuffer(ReportGlobalPoseMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);

static JausBoolean dataFromBuffer(ReportGlobalPoseMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);
static int dataToBuffer(ReportGlobalPoseMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);
static void dataInitialize(ReportGlobalPoseMessage message);

// ************************************************************************************************************** //
//                                    USER CONFIGURED FUNCTIONS
// ************************************************************************************************************** //

// Initializes the message-specific fields
static void dataInitialize(ReportGlobalPoseMessage message)
{
	// Set initial values of message fields
	message->presenceVector = newJausShortPresenceVector();
	message->latitudeDegrees = newJausDouble(0);			// Scaled Int (-90, 90)
	message->longitudeDegrees = newJausDouble(0);			// Scaled Int (-180, 180)
	message->elevationMeters = newJausDouble(0);			// Scaled Int (-10000, 35000)
	message->positionRmsMeters = newJausDouble(0);			// Scaled UInt (0, 100)
	message->rollRadians = newJausDouble(0);				// Scaled Short (-JAUS_PI, JAUS_PI)
	message->pitchRadians = newJausDouble(0);				// Scaled Short (-JAUS_PI, JAUS_PI)
	message->yawRadians = newJausDouble(0);					// Scaled Short (-JAUS_PI, JAUS_PI)
	message->attitudeRmsRadians = newJausDouble(0);			// Scaled Short (0, JAUS_PI)
	message->timeStamp = newJausUnsignedInteger(0);
}

// Return boolean of success
static JausBoolean dataFromBuffer(ReportGlobalPoseMessage message, unsigned char *buffer, unsigned int bufferSizeBytes)
{
	int index = 0;
	JausInteger tempInt;
	JausUnsignedInteger tempUInt;
	JausShort	tempShort;
	JausUnsignedShort tempUShort;
	
	if(bufferSizeBytes == message->dataSize)
	{
		// Unpack Message Fields from Buffer
		// Use Presence Vector
		if(!jausShortPresenceVectorFromBuffer(&message->presenceVector, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
		index += JAUS_SHORT_PRESENCE_VECTOR_SIZE_BYTES;

		if(jausShortPresenceVectorIsBitSet(message->presenceVector, JAUS_POSE_PV_LATITUDE_BIT))
		{
			//unpack
			if(!jausIntegerFromBuffer(&tempInt, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_INTEGER_SIZE_BYTES;

			// Scaled Int (-90, 90)			
			message->latitudeDegrees = jausIntegerToDouble(tempInt, -90, 90);
		}
		
		if(jausShortPresenceVectorIsBitSet(message->presenceVector, JAUS_POSE_PV_LONGITUDE_BIT))
		{
			//unpack
			if(!jausIntegerFromBuffer(&tempInt, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_INTEGER_SIZE_BYTES;

			// Scaled Int (-180, 180)			
			message->longitudeDegrees = jausIntegerToDouble(tempInt, -180, 180);
		}
		
		if(jausShortPresenceVectorIsBitSet(message->presenceVector, JAUS_POSE_PV_ELEVATION_BIT))
		{
			//unpack
			if(!jausIntegerFromBuffer(&tempInt, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_INTEGER_SIZE_BYTES;

			// Scaled Int (-10000, 35000)			
			message->elevationMeters = jausIntegerToDouble(tempInt, -10000, 35000);
		}
		
		if(jausShortPresenceVectorIsBitSet(message->presenceVector, JAUS_POSE_PV_POSITION_RMS_BIT))
		{
			//unpack
			if(!jausUnsignedIntegerFromBuffer(&tempUInt, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_UNSIGNED_INTEGER_SIZE_BYTES;

			// Scaled Int (0, 100)			
			message->positionRmsMeters = jausUnsignedIntegerToDouble(tempUInt, 0, 100);
		}
	
		if(jausShortPresenceVectorIsBitSet(message->presenceVector, JAUS_POSE_PV_ROLL_BIT))
		{
			// unpack
			if(!jausShortFromBuffer(&tempShort, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_SHORT_SIZE_BYTES;
			
			// Scaled Short (-JAUS_PI, JAUS_PI)
			message->rollRadians = jausShortToDouble(tempShort, -JAUS_PI, JAUS_PI);
		}
		
		if(jausShortPresenceVectorIsBitSet(message->presenceVector, JAUS_POSE_PV_PITCH_BIT))
		{
			// unpack
			if(!jausShortFromBuffer(&tempShort, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_SHORT_SIZE_BYTES;
			
			// Scaled Short (-JAUS_PI, JAUS_PI)
			message->pitchRadians = jausShortToDouble(tempShort, -JAUS_PI, JAUS_PI);
		}
		
		if(jausShortPresenceVectorIsBitSet(message->presenceVector, JAUS_POSE_PV_YAW_BIT))
		{
			// unpack
			if(!jausShortFromBuffer(&tempShort, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_SHORT_SIZE_BYTES;
			
			// Scaled Short (-JAUS_PI, JAUS_PI)
			message->yawRadians = jausShortToDouble(tempShort, -JAUS_PI, JAUS_PI);
		}
		
		if(jausShortPresenceVectorIsBitSet(message->presenceVector, JAUS_POSE_PV_ATTITUDE_RMS_BIT))
		{
			// unpack
			if(!jausUnsignedShortFromBuffer(&tempUShort, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
			
			// Scaled Unsigned Short (0, JAUS_PI)
			message->attitudeRmsRadians = jausUnsignedShortToDouble(tempUShort, 0, JAUS_PI);
		}
		
		if(jausShortPresenceVectorIsBitSet(message->presenceVector, JAUS_POSE_PV_TIME_STAMP_BIT))
		{
			//unpack
			if(!jausUnsignedIntegerFromBuffer(&message->timeStamp, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_UNSIGNED_INTEGER_SIZE_BYTES;
		}
		return JAUS_TRUE;
	}
	else
	{
		return JAUS_FALSE;
	}
}

// Returns number of bytes put into the buffer
static int dataToBuffer(ReportGlobalPoseMessage message, unsigned char *buffer, unsigned int bufferSizeBytes)
{
	int index = 0;
	JausInteger tempInt;
	JausUnsignedInteger tempUInt;
	JausShort	tempShort;
	JausUnsignedShort tempUShort;

	if(bufferSizeBytes >= message->dataSize)
	{
		// Pack Message Fields to Buffer
		// Use Presence Vector
		if(!jausShortPresenceVectorToBuffer(message->presenceVector, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
		index += JAUS_SHORT_PRESENCE_VECTOR_SIZE_BYTES;
		
		if(jausShortPresenceVectorIsBitSet(message->presenceVector, JAUS_POSE_PV_LATITUDE_BIT))
		{
			// Scaled Int (-90, 90)			
			tempInt = jausIntegerFromDouble(message->latitudeDegrees, -90, 90);

			//pack
			if(!jausIntegerToBuffer(tempInt, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_INTEGER_SIZE_BYTES;

		}
		
		if(jausShortPresenceVectorIsBitSet(message->presenceVector, JAUS_POSE_PV_LONGITUDE_BIT))
		{
			// Scaled Int (-180, 180)			
			tempInt = jausIntegerFromDouble(message->longitudeDegrees, -180, 180);

			//pack
			if(!jausIntegerToBuffer(tempInt, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_INTEGER_SIZE_BYTES;

		}

		if(jausShortPresenceVectorIsBitSet(message->presenceVector, JAUS_POSE_PV_ELEVATION_BIT))
		{
			// Scaled Int (-10000, 35000)			
			tempInt = jausIntegerFromDouble(message->elevationMeters, -10000, 35000);

			//unpack
			if(!jausIntegerToBuffer(tempInt, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_INTEGER_SIZE_BYTES;
		}
		
		if(jausShortPresenceVectorIsBitSet(message->presenceVector, JAUS_POSE_PV_POSITION_RMS_BIT))
		{
			// Scaled Int (0, 100)			
			tempUInt = jausUnsignedIntegerFromDouble(message->positionRmsMeters, 0, 100);

			//unpack
			if(!jausUnsignedIntegerToBuffer(tempUInt, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_UNSIGNED_INTEGER_SIZE_BYTES;
		}
	
		if(jausShortPresenceVectorIsBitSet(message->presenceVector, JAUS_POSE_PV_ROLL_BIT))
		{
			// Scaled Short (-JAUS_PI, JAUS_PI)
			tempShort = jausShortFromDouble(message->rollRadians, -JAUS_PI, JAUS_PI);

			// unpack
			if(!jausShortToBuffer(tempShort, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_SHORT_SIZE_BYTES;
		}
		
		if(jausShortPresenceVectorIsBitSet(message->presenceVector, JAUS_POSE_PV_PITCH_BIT))
		{
			// Scaled Short (-JAUS_PI, JAUS_PI)
			tempShort = jausShortFromDouble(message->pitchRadians, -JAUS_PI, JAUS_PI);

			// unpack
			if(!jausShortToBuffer(tempShort, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_SHORT_SIZE_BYTES;
		}
		
		if(jausShortPresenceVectorIsBitSet(message->presenceVector, JAUS_POSE_PV_YAW_BIT))
		{
			// Scaled Short (-JAUS_PI, JAUS_PI)
			tempShort = jausShortFromDouble(message->yawRadians, -JAUS_PI, JAUS_PI);

			// unpack
			if(!jausShortToBuffer(tempShort, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_SHORT_SIZE_BYTES;
		}
		
		if(jausShortPresenceVectorIsBitSet(message->presenceVector, JAUS_POSE_PV_ATTITUDE_RMS_BIT))
		{
			// Scaled Unsigned Short (0, JAUS_PI)
			tempUShort = jausUnsignedShortFromDouble(message->attitudeRmsRadians, 0, JAUS_PI);

			// unpack
			if(!jausUnsignedShortToBuffer(tempUShort, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
		}
		
		if(jausShortPresenceVectorIsBitSet(message->presenceVector, JAUS_POSE_PV_TIME_STAMP_BIT))
		{
			//unpack
			if(!jausUnsignedIntegerToBuffer(message->timeStamp, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_UNSIGNED_INTEGER_SIZE_BYTES;
		}
	}

	return index;
}

// ************************************************************************************************************** //
//                                    NON-USER CONFIGURED FUNCTIONS
// ************************************************************************************************************** //

ReportGlobalPoseMessage reportGlobalPoseMessageCreate(void)
{
	ReportGlobalPoseMessage message;

	message = (ReportGlobalPoseMessage)malloc( sizeof(ReportGlobalPoseMessageStruct) );
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

void reportGlobalPoseMessageDestroy(ReportGlobalPoseMessage message)
{
	jausAddressDestroy(message->source);
	jausAddressDestroy(message->destination);
	free(message);
}

JausBoolean reportGlobalPoseMessageFromBuffer(ReportGlobalPoseMessage message, unsigned char* buffer, unsigned int bufferSizeBytes)
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

JausBoolean reportGlobalPoseMessageToBuffer(ReportGlobalPoseMessage message, unsigned char *buffer, unsigned int bufferSizeBytes)
{
	if(bufferSizeBytes < reportGlobalPoseMessageSize(message))
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
			return JAUS_FALSE; // headerToReportGlobalPoseBuffer failed
		}
	}
}

JausBoolean reportGlobalPoseMessageToUdpBuffer(ReportGlobalPoseMessage message, unsigned char *buffer, unsigned int bufferSizeBytes)
{
	if(bufferSizeBytes < reportGlobalPoseMessageUdpSize(message))
	{
		return JAUS_FALSE; // improper size
	}
	else
	{
		strncpy((char *)buffer, JAUS_UDP_HEADER, JAUS_UDP_HEADER_SIZE_BYTES); //copies the UDP header into the buffer
		return reportGlobalPoseMessageToBuffer(message, buffer+JAUS_UDP_HEADER_SIZE_BYTES, bufferSizeBytes - JAUS_UDP_HEADER_SIZE_BYTES);
	}
}

ReportGlobalPoseMessage reportGlobalPoseMessageFromJausMessage(JausMessage jausMessage)
{
	ReportGlobalPoseMessage message;
	
	if(jausMessage->commandCode != commandCode)
	{
		return NULL; // Wrong message type
	}
	else
	{
		message = (ReportGlobalPoseMessage)malloc( sizeof(ReportGlobalPoseMessageStruct) );
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

JausMessage reportGlobalPoseMessageToJausMessage(ReportGlobalPoseMessage message)
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

unsigned int reportGlobalPoseMessageUdpSize(ReportGlobalPoseMessage message)
{
	return (unsigned int)(message->dataSize + JAUS_HEADER_SIZE_BYTES + JAUS_UDP_HEADER_SIZE_BYTES);
}

unsigned int reportGlobalPoseMessageSize(ReportGlobalPoseMessage message)
{
	return (unsigned int)(message->dataSize + JAUS_HEADER_SIZE_BYTES);
}

//********************* PRIVATE HEADER FUNCTIONS **********************//

static JausBoolean headerFromBuffer(ReportGlobalPoseMessage message, unsigned char *buffer, unsigned int bufferSizeBytes)
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

static JausBoolean headerToBuffer(ReportGlobalPoseMessage message, unsigned char *buffer, unsigned int bufferSizeBytes)
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

