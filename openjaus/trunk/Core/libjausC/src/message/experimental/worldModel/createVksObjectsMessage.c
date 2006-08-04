// File Name: createVksObjectsMessage.c
//
// Written By: Danny Kent (jaus AT dannykent DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines the functionality of a CreateVksObjectsMessage

#include <stdlib.h>
#include <string.h>
#include <cimar.h>
#include "cimar/jaus.h"

static const int commandCode = JAUS_CREATE_VKS_OBJECTS;
static const int maxDataSizeBytes = 512000; // Max Message size: 500K

static JausBoolean headerFromBuffer(CreateVksObjectsMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);
static JausBoolean headerToBuffer(CreateVksObjectsMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);

static JausBoolean dataFromBuffer(CreateVksObjectsMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);
static int dataToBuffer(CreateVksObjectsMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);
static void dataInitialize(CreateVksObjectsMessage message);
static void dataDestroy(CreateVksObjectsMessage message);

// ************************************************************************************************************** //
//                                    USER CONFIGURED FUNCTIONS
// ************************************************************************************************************** //

// Initializes the message-specific fields
static void dataInitialize(CreateVksObjectsMessage message)
{
	message->expFlag = JAUS_EXPERIMENTAL_MESSAGE;
	// Set initial values of message fields
	message->presenceVector = newJausBytePresenceVector();		// presenceVector
	message->messageProperties = newJausBytePresenceVector(); 	// Bit Field, use Presence Vector for ease
	message->requestId = newJausByte(0);						// Local Request ID
	message->vectorObjects = vectorCreate();					// Dynamic Array of Vector Objects
}

// Destructs the message-specific fields
static void dataDestroy(CreateVksObjectsMessage message)
{
	// Free message fields
	if(message->vectorObjects) vectorDestroy(message->vectorObjects, (void *)vectorObjectDestroy);
}

// Return boolean of success
static JausBoolean dataFromBuffer(CreateVksObjectsMessage message, unsigned char *buffer, unsigned int bufferSizeBytes)
{
	int index = 0;
	int i = 0;
	JausUnsignedShort objectCount;
	JausBoolean objectBuffered = JAUS_FALSE;
	JausWorldModelVectorObject object = NULL;
	
	if(bufferSizeBytes == message->dataSize)
	{
		// Unpack Message Fields from Buffer
		// Presence Vector
		if(!jausBytePresenceVectorFromBuffer(&message->presenceVector, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
		index += JAUS_BYTE_PRESENCE_VECTOR_SIZE_BYTES;
	
		objectBuffered = jausBytePresenceVectorIsBitSet(message->presenceVector, VKS_PV_CREATE_BUFFERED_BIT);
		
		// Message Properties
		if(!jausBytePresenceVectorFromBuffer(&message->messageProperties, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
		index += JAUS_BYTE_PRESENCE_VECTOR_SIZE_BYTES;

		// Local Request Id
		if(!jausByteFromBuffer(&message->requestId, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
		index += JAUS_BYTE_SIZE_BYTES;

		// Number of Objects
		if(!jausUnsignedShortFromBuffer(&objectCount, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
		index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
		
		message->vectorObjects = vectorCreate();
		if(!message->vectorObjects) return JAUS_FALSE;
		
		for(i = 0; i < objectCount; i++)
		{
			object = vectorObjectFromBuffer(buffer+index, bufferSizeBytes-index, objectBuffered);
			if(!object) return JAUS_FALSE;
			index += vectorObjectSizeBytes(object, objectBuffered);
			vectorAdd(message->vectorObjects, object);
		}
		return JAUS_TRUE;
	}
	else
	{
		return JAUS_FALSE;
	}
}

// Returns number of bytes put into the buffer
static int dataToBuffer(CreateVksObjectsMessage message, unsigned char *buffer, unsigned int bufferSizeBytes)
{
	int index = 0;
	int i = 0;
	JausBoolean objectBuffered;
	JausWorldModelVectorObject object;

	if(bufferSizeBytes >= message->dataSize)
	{
		// Pack Message Fields to Buffer
		// Presence Vector
		if(!jausBytePresenceVectorToBuffer(message->presenceVector, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
		index += JAUS_BYTE_PRESENCE_VECTOR_SIZE_BYTES;
	
		objectBuffered = jausBytePresenceVectorIsBitSet(message->presenceVector, VKS_PV_CREATE_BUFFERED_BIT);
		
		// Message Properties
		if(!jausBytePresenceVectorToBuffer(message->messageProperties, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
		index += JAUS_BYTE_PRESENCE_VECTOR_SIZE_BYTES;
		
		// Local Request Id
		if(!jausByteToBuffer(message->requestId, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
		index += JAUS_BYTE_SIZE_BYTES;

		// Number of Objects
		if(!jausUnsignedShortToBuffer((JausUnsignedShort)message->vectorObjects->elementCount, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
		index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
		
		for(i = 0; i < message->vectorObjects->elementCount; i++)
		{
			object = (JausWorldModelVectorObject) message->vectorObjects->elementData[i];
			if(!vectorObjectToBuffer(object, buffer+index, bufferSizeBytes-index, objectBuffered)) return JAUS_FALSE;
			index += vectorObjectSizeBytes(object, objectBuffered);
		}
	}
	return index;
}

// ************************************************************************************************************** //
//                                    NON-USER CONFIGURED FUNCTIONS
// ************************************************************************************************************** //

CreateVksObjectsMessage createVksObjectsMessageCreate(void)
{
	CreateVksObjectsMessage message;

	message = (CreateVksObjectsMessage)malloc( sizeof(CreateVksObjectsMessageStruct) );
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

void createVksObjectsMessageDestroy(CreateVksObjectsMessage message)
{
	dataDestroy(message);
	jausAddressDestroy(message->source);
	jausAddressDestroy(message->destination);
	free(message);
}

JausBoolean createVksObjectsMessageFromBuffer(CreateVksObjectsMessage message, unsigned char* buffer, unsigned int bufferSizeBytes)
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

JausBoolean createVksObjectsMessageToBuffer(CreateVksObjectsMessage message, unsigned char *buffer, unsigned int bufferSizeBytes)
{
	if(bufferSizeBytes < createVksObjectsMessageSize(message))
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
			return JAUS_FALSE; // headerToCreateVksObjectsBuffer failed
		}
	}
}

JausBoolean createVksObjectsMessageToUdpBuffer(CreateVksObjectsMessage message, unsigned char *buffer, unsigned int bufferSizeBytes)
{
	if(bufferSizeBytes < createVksObjectsMessageUdpSize(message))
	{
		return JAUS_FALSE; // improper size
	}
	else
	{
		strncpy( (char *) buffer, JAUS_UDP_HEADER, JAUS_UDP_HEADER_SIZE_BYTES); //copies the UDP header into the buffer
		return createVksObjectsMessageToBuffer(message, buffer+JAUS_UDP_HEADER_SIZE_BYTES, bufferSizeBytes - JAUS_UDP_HEADER_SIZE_BYTES);
	}
}

CreateVksObjectsMessage createVksObjectsMessageFromJausMessage(JausMessage jausMessage)
{
	CreateVksObjectsMessage message;

	if(jausMessage->commandCode != commandCode)
	{
		return NULL; // Wrong message type
	}
	else
	{
		message = (CreateVksObjectsMessage)malloc( sizeof(CreateVksObjectsMessageStruct) );
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

JausMessage createVksObjectsMessageToJausMessage(CreateVksObjectsMessage message)
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

unsigned int createVksObjectsMessageUdpSize(CreateVksObjectsMessage message)
{
	return (unsigned int)(message->dataSize + JAUS_HEADER_SIZE_BYTES + JAUS_UDP_HEADER_SIZE_BYTES);
}

unsigned int createVksObjectsMessageSize(CreateVksObjectsMessage message)
{
	return (unsigned int)(message->dataSize + JAUS_HEADER_SIZE_BYTES);
}

//********************* PRIVATE HEADER FUNCTIONS **********************//

static JausBoolean headerFromBuffer(CreateVksObjectsMessage message, unsigned char *buffer, unsigned int bufferSizeBytes)
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

static JausBoolean headerToBuffer(CreateVksObjectsMessage message, unsigned char *buffer, unsigned int bufferSizeBytes)
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

