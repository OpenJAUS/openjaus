// File Name: setGlobalWaypointMessage.c
//
// Written By: Danny Kent (jaus AT dannykent DOT com), Tom Galluzzo (galluzzo AT gmail DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines the functionality of a SetGlobalWaypointMessage



#include <stdlib.h>
#include <string.h>
#include "cimar/jaus.h"

static const int commandCode = JAUS_SET_GLOBAL_WAYPOINT;
static const int maxDataSizeBytes = 21;

static JausBoolean headerFromBuffer(SetGlobalWaypointMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);
static JausBoolean headerToBuffer(SetGlobalWaypointMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);

static JausBoolean dataFromBuffer(SetGlobalWaypointMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);
static int dataToBuffer(SetGlobalWaypointMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);
static void dataInitialize(SetGlobalWaypointMessage message);

// ************************************************************************************************************** //
//                                    USER CONFIGURED FUNCTIONS
// ************************************************************************************************************** //

// Initializes the message-specific fields
static void dataInitialize(SetGlobalWaypointMessage message)
{
	// Set initial values of message fields
	message->presenceVector = newJausBytePresenceVector ();
	message->waypointNumber = newJausUnsignedShort(0);
	message->latitudeDegrees = newJausDouble(0);	// Scaled Integer (-90, 90)
	message->longitudeDegrees = newJausDouble(0); 	// Scaled Integer (-180, 180)
	message->elevationMeters = newJausDouble(0); 	// Scaled Integer (-10000, 35000)
	message->rollRadians = newJausDouble(0);		// Scaled Short (-JAUS_PI, JAUS_PI)
	message->pitchRadians = newJausDouble(0);		// Scaled Short (-JAUS_PI, JAUS_PI)
	message->yawRadians = newJausDouble(0);			// Scaled Short (-JAUS_PI, JAUS_PI)
}

// Return boolean of success
static JausBoolean dataFromBuffer(SetGlobalWaypointMessage message, unsigned char *buffer, unsigned int bufferSizeBytes)
{
	int index = 0;
	JausInteger tempInteger;
	JausShort tempShort;

	if(bufferSizeBytes == message->dataSize)
	{
		// Unpack Message Fields from Buffer
		// Use Presence Vector
		if(!jausBytePresenceVectorFromBuffer(&message->presenceVector, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
		index += JAUS_BYTE_PRESENCE_VECTOR_SIZE_BYTES;
		
		if(!jausUnsignedShortFromBuffer(&message->waypointNumber, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
		index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
		
		//unpack
		//JausDouble latitudeDegrees		// Scaled Integer (-90, 90)
		if(!jausIntegerFromBuffer(&tempInteger, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
		index += JAUS_INTEGER_SIZE_BYTES;
		message->latitudeDegrees = jausIntegerToDouble(tempInteger, -90, 90);
		
		//unpack
		//JausDouble longitudeDegrees		// Scaled Integer (-180, 180)
		if(!jausIntegerFromBuffer(&tempInteger, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
		index += JAUS_INTEGER_SIZE_BYTES;
		message->longitudeDegrees = jausIntegerToDouble(tempInteger, -180, 180);

		if(jausBytePresenceVectorIsBitSet(message->presenceVector, JAUS_WAYPOINT_PV_ELEVATION_BIT))
		{
			//unpack
			//JausDouble elevationMeters	// Scaled Integer (-10000, 35000)
			if(!jausIntegerFromBuffer(&tempInteger, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_INTEGER_SIZE_BYTES;
			
			message->elevationMeters = jausIntegerToDouble(tempInteger, -10000, 35000);
		}

		if(jausBytePresenceVectorIsBitSet(message->presenceVector, JAUS_WAYPOINT_PV_ROLL_BIT))
		{
			//unpack
			//JausDouble rollRadians // Scaled Short (-JAUS_PI, JAUS_PI)
			if(!jausShortFromBuffer(&tempShort, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_SHORT_SIZE_BYTES;

			message->rollRadians = jausShortToDouble(tempShort, -JAUS_PI, JAUS_PI);
		}
		
		if(jausBytePresenceVectorIsBitSet(message->presenceVector, JAUS_WAYPOINT_PV_PITCH_BIT))
		{
			//unpack
			//JausDouble pitchRadians;		// Scaled Short (-JAUS_PI, JAUS_PI)
			if(!jausShortFromBuffer(&tempShort, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_SHORT_SIZE_BYTES;

			message->pitchRadians = jausShortToDouble(tempShort, -JAUS_PI, JAUS_PI);
		}
			
		if(jausBytePresenceVectorIsBitSet(message->presenceVector, JAUS_WAYPOINT_PV_YAW_BIT))
		{
			//unpack
			//JausDouble yawRadians;			// Scaled Short (-JAUS_PI, JAUS_PI)
			if(!jausShortFromBuffer(&tempShort, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_SHORT_SIZE_BYTES;

			message->yawRadians = jausShortToDouble(tempShort, -JAUS_PI, JAUS_PI);
		}
		return JAUS_TRUE;
	}
	else
	{
		return JAUS_FALSE;
	}
}

// Returns number of bytes put into the buffer
static int dataToBuffer(SetGlobalWaypointMessage message, unsigned char *buffer, unsigned int bufferSizeBytes)
{
	int index = 0;
	JausInteger tempInteger;
	JausShort tempShort;

	if(bufferSizeBytes >= message->dataSize)
	{
		// Pack Message Fields to Buffer
		// Use Presence Vector
		if(!jausBytePresenceVectorToBuffer(message->presenceVector, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
		index += JAUS_BYTE_PRESENCE_VECTOR_SIZE_BYTES;
		
		if(!jausUnsignedShortToBuffer(message->waypointNumber, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
		index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
		
		//pack
		//JausDouble latitudeDegrees		// Scaled Integer (-90, 90)
		tempInteger = jausIntegerFromDouble(message->latitudeDegrees, -90, 90);
		if(!jausIntegerToBuffer(tempInteger, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
		index += JAUS_INTEGER_SIZE_BYTES;
		
		//pack
		//JausDouble longitudeDegrees		// Scaled Integer (-180, 180)
		tempInteger = jausIntegerFromDouble(message->longitudeDegrees, -180, 180);
		if(!jausIntegerToBuffer(tempInteger, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
		index += JAUS_INTEGER_SIZE_BYTES;
		
		if(jausBytePresenceVectorIsBitSet(message->presenceVector, JAUS_WAYPOINT_PV_ELEVATION_BIT))
		{
			//pack
			//JausDouble elevationMeters	// Scaled Integer (-10000, 35000)
			tempInteger = jausIntegerFromDouble(message->elevationMeters, -10000, 35000);
			if(!jausIntegerToBuffer(tempInteger, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_INTEGER_SIZE_BYTES;
		}

		if(jausBytePresenceVectorIsBitSet(message->presenceVector, JAUS_WAYPOINT_PV_ROLL_BIT))
		{
			//pack
			//JausDouble rollRadians // Scaled Short (-JAUS_PI, JAUS_PI)
			tempShort = jausShortFromDouble(message->rollRadians, -JAUS_PI, JAUS_PI);
			if(!jausShortToBuffer(tempShort, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_SHORT_SIZE_BYTES;
		}
		
		if(jausBytePresenceVectorIsBitSet(message->presenceVector, JAUS_WAYPOINT_PV_PITCH_BIT))
		{
			//pack
			//JausDouble pitchRadians;		// Scaled Short (-JAUS_PI, JAUS_PI)
			tempShort = jausShortToDouble(message->pitchRadians, -JAUS_PI, JAUS_PI);
			if(!jausShortToBuffer(tempShort, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_SHORT_SIZE_BYTES;
		}
			
		if(jausBytePresenceVectorIsBitSet(message->presenceVector, JAUS_WAYPOINT_PV_YAW_BIT))
		{
			//pack
			//JausDouble yawRadians;			// Scaled Short (-JAUS_PI, JAUS_PI)
			tempShort = jausShortToDouble(message->yawRadians, -JAUS_PI, JAUS_PI);
			if(!jausShortToBuffer(tempShort, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_SHORT_SIZE_BYTES;
		}
	}
	return index;
}

// ************************************************************************************************************** //
//                                    NON-USER CONFIGURED FUNCTIONS
// ************************************************************************************************************** //

SetGlobalWaypointMessage setGlobalWaypointMessageCreate(void)
{
	SetGlobalWaypointMessage message;

	message = (SetGlobalWaypointMessage)malloc( sizeof(SetGlobalWaypointMessageStruct) );
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

void setGlobalWaypointMessageDestroy(SetGlobalWaypointMessage message)
{
	jausAddressDestroy(message->source);
	jausAddressDestroy(message->destination);
	free(message);
}

JausBoolean setGlobalWaypointMessageFromBuffer(SetGlobalWaypointMessage message, unsigned char* buffer, unsigned int bufferSizeBytes)
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

JausBoolean setGlobalWaypointMessageToBuffer(SetGlobalWaypointMessage message, unsigned char *buffer, unsigned int bufferSizeBytes)
{
	if(bufferSizeBytes < setGlobalWaypointMessageSize(message))
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
			return JAUS_FALSE; // headerToSetGlobalWaypointBuffer failed
		}
	}
}

JausBoolean setGlobalWaypointMessageToUdpBuffer(SetGlobalWaypointMessage message, unsigned char *buffer, unsigned int bufferSizeBytes)
{
	if(bufferSizeBytes < setGlobalWaypointMessageUdpSize(message))
	{
		return JAUS_FALSE; // improper size
	}
	else
	{
		strncpy((char *)buffer, JAUS_UDP_HEADER, JAUS_UDP_HEADER_SIZE_BYTES); //copies the UDP header into the buffer
		return setGlobalWaypointMessageToBuffer(message, buffer+JAUS_UDP_HEADER_SIZE_BYTES, bufferSizeBytes - JAUS_UDP_HEADER_SIZE_BYTES);
	}
}

SetGlobalWaypointMessage setGlobalWaypointMessageFromJausMessage(JausMessage jausMessage)
{
	SetGlobalWaypointMessage message;
	
	if(jausMessage->commandCode != commandCode)
	{
		return NULL; // Wrong message type
	}
	else
	{
		message = (SetGlobalWaypointMessage)malloc( sizeof(SetGlobalWaypointMessageStruct) );
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

JausMessage setGlobalWaypointMessageToJausMessage(SetGlobalWaypointMessage message)
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

unsigned int setGlobalWaypointMessageUdpSize(SetGlobalWaypointMessage message)
{
	return (unsigned int)(message->dataSize + JAUS_HEADER_SIZE_BYTES + JAUS_UDP_HEADER_SIZE_BYTES);
}

unsigned int setGlobalWaypointMessageSize(SetGlobalWaypointMessage message)
{
	return (unsigned int)(message->dataSize + JAUS_HEADER_SIZE_BYTES);
}

//********************* PRIVATE HEADER FUNCTIONS **********************//

static JausBoolean headerFromBuffer(SetGlobalWaypointMessage message, unsigned char *buffer, unsigned int bufferSizeBytes)
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

static JausBoolean headerToBuffer(SetGlobalWaypointMessage message, unsigned char *buffer, unsigned int bufferSizeBytes)
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

