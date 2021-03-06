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
 *   A PARTICULAR PURVELOCITY_STATE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
 *   OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, 
 *   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY 
 *   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 ****************************************************************************/
// File Name: setEndEffectorVelocityStateMessage.c
//
// Written By: Danny Kent (jaus AT dannykent DOT com), Tom Galluzzo (galluzzo AT gmail DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines the functionality of a SetEndEffectorVelocityStateMessage

#include <stdlib.h>
#include <string.h>
#include "jaus.h"

static const int commandCode = JAUS_SET_END_EFFECTOR_VELOCITY_STATE;
static const int maxDataSizeBytes = 25;

static JausBoolean headerFromBuffer(SetEndEffectorVelocityStateMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);
static JausBoolean headerToBuffer(SetEndEffectorVelocityStateMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);

static JausBoolean dataFromBuffer(SetEndEffectorVelocityStateMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);
static int dataToBuffer(SetEndEffectorVelocityStateMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);
static void dataInitialize(SetEndEffectorVelocityStateMessage message);
static void dataDestroy(SetEndEffectorVelocityStateMessage message);

// ************************************************************************************************************** //
//                                    USER CONFIGURED FUNCTIONS
// ************************************************************************************************************** //

// Initializes the message-specific fields
static void dataInitialize(SetEndEffectorVelocityStateMessage message)
{
	// Set initial values of message fields
	message->coordinateSystem = newJausByte(0);
	message->xAngular = newJausDouble(0);
	message->yAngular = newJausDouble(0);
	message->zAngular = newJausDouble(0);
	message->xLinear = newJausDouble(0);
	message->yLinear = newJausDouble(0);
	message->zLinear = newJausDouble(0);
}

// Destructs the message-specific fields
static void dataDestroy(SetEndEffectorVelocityStateMessage message)
{
	// Free message fields
}

// Return boolean of success
static JausBoolean dataFromBuffer(SetEndEffectorVelocityStateMessage message, unsigned char *buffer, unsigned int bufferSizeBytes)
{
	int index = 0;
	JausUnsignedInteger tempUInt;
	
	if(bufferSizeBytes == message->dataSize)
	{
		// Unpack Message Fields from Buffer
		if(!jausByteFromBuffer(&message->coordinateSystem, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
		index += JAUS_BYTE_SIZE_BYTES;

		if(!jausUnsignedIntegerFromBuffer(&tempUInt, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
		index += JAUS_UNSIGNED_INTEGER_SIZE_BYTES;
		// Scaled Short (-20*JAUS_PI, 20*JAUS_PI)			
		message->xAngular = jausUnsignedIntegerToDouble(tempUInt, -20*JAUS_PI, 20*JAUS_PI);

		if(!jausUnsignedIntegerFromBuffer(&tempUInt, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
		index += JAUS_UNSIGNED_INTEGER_SIZE_BYTES;
		// Scaled Short (-20*JAUS_PI, 20*JAUS_PI)			
		message->yAngular = jausUnsignedIntegerToDouble(tempUInt, -20*JAUS_PI, 20*JAUS_PI);

		if(!jausUnsignedIntegerFromBuffer(&tempUInt, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
		index += JAUS_UNSIGNED_INTEGER_SIZE_BYTES;
		// Scaled Short (-20*JAUS_PI, 20*JAUS_PI)			
		message->zAngular = jausUnsignedIntegerToDouble(tempUInt, -20*JAUS_PI, 20*JAUS_PI);

		if(!jausUnsignedIntegerFromBuffer(&tempUInt, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
		index += JAUS_UNSIGNED_INTEGER_SIZE_BYTES;
		// Scaled Short (-10, 10)			
		message->xLinear = jausUnsignedIntegerToDouble(tempUInt, -10, 10);

		if(!jausUnsignedIntegerFromBuffer(&tempUInt, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
		index += JAUS_UNSIGNED_INTEGER_SIZE_BYTES;
		// Scaled Short (-10, 10)			
		message->yLinear = jausUnsignedIntegerToDouble(tempUInt, -10, 10);

		if(!jausUnsignedIntegerFromBuffer(&tempUInt, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
		index += JAUS_UNSIGNED_INTEGER_SIZE_BYTES;
		// Scaled Short (-10, 10)			
		message->zLinear = jausUnsignedIntegerToDouble(tempUInt, -10, 10);

		return JAUS_TRUE;
	}
	else
	{
		return JAUS_FALSE;
	}
}

// Returns number of bytes put into the buffer
static int dataToBuffer(SetEndEffectorVelocityStateMessage message, unsigned char *buffer, unsigned int bufferSizeBytes)
{
	int index = 0;
	JausUnsignedInteger tempUInt;

	if(bufferSizeBytes >= message->dataSize)
	{
		// Pack Message Fields to Buffer
		if(!jausByteToBuffer(message->coordinateSystem, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
		index += JAUS_BYTE_SIZE_BYTES;

		// Scaled Short (-20*JAUS_PI, 20*JAUS_PI)			
		tempUInt = jausUnsignedIntegerFromDouble(message->xAngular, -20*JAUS_PI, 20*JAUS_PI);
		if(!jausUnsignedIntegerToBuffer(tempUInt, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
		index += JAUS_UNSIGNED_INTEGER_SIZE_BYTES;

		tempUInt = jausUnsignedIntegerFromDouble(message->yAngular, -20*JAUS_PI, 20*JAUS_PI);
		if(!jausUnsignedIntegerToBuffer(tempUInt, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
		index += JAUS_UNSIGNED_INTEGER_SIZE_BYTES;

		tempUInt = jausUnsignedIntegerFromDouble(message->zAngular, -20*JAUS_PI, 20*JAUS_PI);
		if(!jausUnsignedIntegerToBuffer(tempUInt, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
		index += JAUS_UNSIGNED_INTEGER_SIZE_BYTES;

		// Scaled Short (-10, 10)			
		tempUInt = jausUnsignedIntegerFromDouble(message->xLinear, -10, 10);
		if(!jausUnsignedIntegerToBuffer(tempUInt, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
		index += JAUS_UNSIGNED_INTEGER_SIZE_BYTES;

		tempUInt = jausUnsignedIntegerFromDouble(message->yLinear, -10, 10);
		if(!jausUnsignedIntegerToBuffer(tempUInt, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
		index += JAUS_UNSIGNED_INTEGER_SIZE_BYTES;

		tempUInt = jausUnsignedIntegerFromDouble(message->zLinear, -10, 10);
		if(!jausUnsignedIntegerToBuffer(tempUInt, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
		index += JAUS_UNSIGNED_INTEGER_SIZE_BYTES;

	}

	return index;
}

// Returns number of bytes put into the buffer
static int dataSize(SetEndEffectorVelocityStateMessage message)
{
	return maxDataSizeBytes;
}

// ************************************************************************************************************** //
//                                    NON-USER CONFIGURED FUNCTIONS
// ************************************************************************************************************** //

SetEndEffectorVelocityStateMessage setEndEffectorVelocityStateMessageCreate(void)
{
	SetEndEffectorVelocityStateMessage message;

	message = (SetEndEffectorVelocityStateMessage)malloc( sizeof(SetEndEffectorVelocityStateMessageStruct) );
	if(message == NULL)
	{
		return NULL;
	}
	
	// Initialize Values
	message->properties.priority = JAUS_DEFAULT_PRIORITY;
	message->properties.ackNak = JAUS_ACK_NAK_NOT_REQUIRED;
	message->properties.scFlag = JAUS_NOT_SERVICE_CONNECTION_MESSAGE;
	message->properties.expFlag = JAUS_NOT_EXPERIMENTAL_MESSAGE;
	message->properties.version = JAUS_VERSION_3_2;
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

void setEndEffectorVelocityStateMessageDestroy(SetEndEffectorVelocityStateMessage message)
{
	dataDestroy(message);
	jausAddressDestroy(message->source);
	jausAddressDestroy(message->destination);
	free(message);
}

JausBoolean setEndEffectorVelocityStateMessageFromBuffer(SetEndEffectorVelocityStateMessage message, unsigned char* buffer, unsigned int bufferSizeBytes)
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

JausBoolean setEndEffectorVelocityStateMessageToBuffer(SetEndEffectorVelocityStateMessage message, unsigned char *buffer, unsigned int bufferSizeBytes)
{
	if(bufferSizeBytes < setEndEffectorVelocityStateMessageSize(message))
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
			return JAUS_FALSE; // headerToXxXxBuffer failed
		}
	}
}

SetEndEffectorVelocityStateMessage setEndEffectorVelocityStateMessageFromJausMessage(JausMessage jausMessage)
{
	SetEndEffectorVelocityStateMessage message;
	
	if(jausMessage->commandCode != commandCode)
	{
		return NULL; // Wrong message type
	}
	else
	{
		message = (SetEndEffectorVelocityStateMessage)malloc( sizeof(SetEndEffectorVelocityStateMessageStruct) );
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

JausMessage setEndEffectorVelocityStateMessageToJausMessage(SetEndEffectorVelocityStateMessage message)
{
	JausMessage jausMessage;
	int size;
	
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
	jausMessage->dataFlag = message->dataFlag;
	jausMessage->sequenceNumber = message->sequenceNumber;
	
	size = dataSize(message);
	jausMessage->data = (unsigned char *)malloc(size);
	jausMessage->dataSize = dataToBuffer(message, jausMessage->data, size);
	
	return jausMessage;
}

unsigned int setEndEffectorVelocityStateMessageSize(SetEndEffectorVelocityStateMessage message)
{
	return (unsigned int)(dataSize(message) + JAUS_HEADER_SIZE_BYTES);
}

//********************* PRIVATE HEADER FUNCTIONS **********************//

static JausBoolean headerFromBuffer(SetEndEffectorVelocityStateMessage message, unsigned char *buffer, unsigned int bufferSizeBytes)
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

static JausBoolean headerToBuffer(SetEndEffectorVelocityStateMessage message, unsigned char *buffer, unsigned int bufferSizeBytes)
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

