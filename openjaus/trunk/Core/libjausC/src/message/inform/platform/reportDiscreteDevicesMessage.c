// File Name: reportDiscreteDevicesMessage.c
//
// Written By: Danny Kent (jaus AT dannykent DOT com), Tom Galluzzo (galluzzo AT gmail DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines the functionality of a ReportDiscreteDevicesMessage



#include <stdlib.h>
#include <string.h>
#include "cimar/jaus.h"

static const int commandCode = JAUS_REPORT_DISCRETE_DEVICES;
static const int maxDataSizeBytes = 5;

static JausBoolean headerFromBuffer(ReportDiscreteDevicesMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);
static JausBoolean headerToBuffer(ReportDiscreteDevicesMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);

static JausBoolean dataFromBuffer(ReportDiscreteDevicesMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);
static int dataToBuffer(ReportDiscreteDevicesMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);
static void dataInitialize(ReportDiscreteDevicesMessage message);

// ************************************************************************************************************** //
//                                    USER CONFIGURED FUNCTIONS
// ************************************************************************************************************** //

// Initializes the message-specific fields
static void dataInitialize(ReportDiscreteDevicesMessage message)
{
	// Set initial values of message fields
	message->presenceVector = newJausBytePresenceVector();
	message->mainPropulsion = newJausByte(0);
	message->parkingBrakeHorn = newJausByte(0);
	message->gear = newJausByte(0);
	message->transferCase = newJausByte(0);
}

// Return boolean of success
static JausBoolean dataFromBuffer(ReportDiscreteDevicesMessage message, unsigned char *buffer, unsigned int bufferSizeBytes)
{
	int index = 0;
	
	if(bufferSizeBytes == message->dataSize)
	{
		// Unpack Message Fields from Buffer
		// Unpack according to presence vector
		if(!jausBytePresenceVectorFromBuffer(&message->presenceVector, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
		index += JAUS_BYTE_PRESENCE_VECTOR_SIZE_BYTES;
		
		if(jausBytePresenceVectorIsBitSet(message->presenceVector, JAUS_DEVICES_PV_PROPULSION_BIT))
		{
			//unpack
			if(!jausByteFromBuffer(&message->mainPropulsion, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_BYTE_SIZE_BYTES;
		}
		
		if(jausBytePresenceVectorIsBitSet(message->presenceVector, JAUS_DEVICES_PV_PARKING_BIT))
		{
			//unpack
			if(!jausByteFromBuffer(&message->parkingBrakeHorn, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_BYTE_SIZE_BYTES;
		}

		if(jausBytePresenceVectorIsBitSet(message->presenceVector, JAUS_DEVICES_PV_GEAR_BIT))
		{
			//unpack
			if(!jausByteFromBuffer(&message->gear, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_BYTE_SIZE_BYTES;
		}

		if(jausBytePresenceVectorIsBitSet(message->presenceVector, JAUS_DEVICES_PV_TRANSFER_BIT))
		{
			//unpack
			if(!jausByteFromBuffer(&message->transferCase, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_BYTE_SIZE_BYTES;
		}

		return JAUS_TRUE;
	}
	else
	{
		return JAUS_FALSE;
	}
}

// Returns number of bytes put into the buffer
static int dataToBuffer(ReportDiscreteDevicesMessage message, unsigned char *buffer, unsigned int bufferSizeBytes)
{
	int index = 0;

	if(bufferSizeBytes >= message->dataSize)
	{
		// Pack Message Fields to Buffer
		// Pack according to presence vector
		if(!jausBytePresenceVectorToBuffer(message->presenceVector, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
		index += JAUS_BYTE_PRESENCE_VECTOR_SIZE_BYTES;
		
		if(jausBytePresenceVectorIsBitSet(message->presenceVector, JAUS_DEVICES_PV_PROPULSION_BIT))
		{
			if(!jausByteToBuffer(message->mainPropulsion, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_BYTE_SIZE_BYTES;
		}
		
		if(jausBytePresenceVectorIsBitSet(message->presenceVector, JAUS_DEVICES_PV_PARKING_BIT))
		{
			if(!jausByteToBuffer(message->parkingBrakeHorn, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_BYTE_SIZE_BYTES;
		}

		if(jausBytePresenceVectorIsBitSet(message->presenceVector, JAUS_DEVICES_PV_GEAR_BIT))
		{
			if(!jausByteToBuffer(message->gear, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_BYTE_SIZE_BYTES;
		}

		if(jausBytePresenceVectorIsBitSet(message->presenceVector, JAUS_DEVICES_PV_TRANSFER_BIT))
		{
			if(!jausByteToBuffer(message->transferCase, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_BYTE_SIZE_BYTES;
		}
	}

	return index;
}

// ************************************************************************************************************** //
//                                    NON-USER CONFIGURED FUNCTIONS
// ************************************************************************************************************** //

ReportDiscreteDevicesMessage reportDiscreteDevicesMessageCreate(void)
{
	ReportDiscreteDevicesMessage message;

	message = (ReportDiscreteDevicesMessage)malloc( sizeof(ReportDiscreteDevicesMessageStruct) );
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

void reportDiscreteDevicesMessageDestroy(ReportDiscreteDevicesMessage message)
{
	jausAddressDestroy(message->source);
	jausAddressDestroy(message->destination);
	free(message);
}

JausBoolean reportDiscreteDevicesMessageFromBuffer(ReportDiscreteDevicesMessage message, unsigned char* buffer, unsigned int bufferSizeBytes)
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

JausBoolean reportDiscreteDevicesMessageToBuffer(ReportDiscreteDevicesMessage message, unsigned char *buffer, unsigned int bufferSizeBytes)
{
	if(bufferSizeBytes < reportDiscreteDevicesMessageSize(message))
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
			return JAUS_FALSE; // headerToReportDescreteDevicesBuffer failed
		}
	}
}

JausBoolean reportDiscreteDevicesMessageToUdpBuffer(ReportDiscreteDevicesMessage message, unsigned char *buffer, unsigned int bufferSizeBytes)
{
	if(bufferSizeBytes < reportDiscreteDevicesMessageUdpSize(message))
	{
		return JAUS_FALSE; // improper size
	}
	else
	{
		strncpy((char *)buffer, JAUS_UDP_HEADER, JAUS_UDP_HEADER_SIZE_BYTES); //copies the UDP header into the buffer
		return reportDiscreteDevicesMessageToBuffer(message, buffer+JAUS_UDP_HEADER_SIZE_BYTES, bufferSizeBytes - JAUS_UDP_HEADER_SIZE_BYTES);
	}
}

ReportDiscreteDevicesMessage reportDiscreteDevicesMessageFromJausMessage(JausMessage jausMessage)
{
	ReportDiscreteDevicesMessage message;
	
	if(jausMessage->commandCode != commandCode)
	{
		return NULL; // Wrong message type
	}
	else
	{
		message = (ReportDiscreteDevicesMessage)malloc( sizeof(ReportDiscreteDevicesMessageStruct) );
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

JausMessage reportDiscreteDevicesMessageToJausMessage(ReportDiscreteDevicesMessage message)
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

unsigned int reportDiscreteDevicesMessageUdpSize(ReportDiscreteDevicesMessage message)
{
	return (unsigned int)(message->dataSize + JAUS_HEADER_SIZE_BYTES + JAUS_UDP_HEADER_SIZE_BYTES);
}

unsigned int reportDiscreteDevicesMessageSize(ReportDiscreteDevicesMessage message)
{
	return (unsigned int)(message->dataSize + JAUS_HEADER_SIZE_BYTES);
}

//********************* PRIVATE HEADER FUNCTIONS **********************//

static JausBoolean headerFromBuffer(ReportDiscreteDevicesMessage message, unsigned char *buffer, unsigned int bufferSizeBytes)
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

static JausBoolean headerToBuffer(ReportDiscreteDevicesMessage message, unsigned char *buffer, unsigned int bufferSizeBytes)
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

