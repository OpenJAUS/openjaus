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
// File Name: reportWrenchEffortMessage.c
//
// Written By: Danny Kent (jaus AT dannykent DOT com), Tom Galluzzo (galluzzo AT gmail DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines the functionality of a ReportWrenchEffortMessage



#include <stdlib.h>
#include <string.h>
#include "cimar/jaus.h"

static const int commandCode = JAUS_REPORT_WRENCH_EFFORT;
static const int maxDataSizeBytes = 20;

static JausBoolean headerFromBuffer(ReportWrenchEffortMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);
static JausBoolean headerToBuffer(ReportWrenchEffortMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);

static JausBoolean dataFromBuffer(ReportWrenchEffortMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);
static int dataToBuffer(ReportWrenchEffortMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);
static void dataInitialize(ReportWrenchEffortMessage message);

// ************************************************************************************************************** //
//                                    USER CONFIGURED FUNCTIONS
// ************************************************************************************************************** //

// Initializes the message-specific fields
static void dataInitialize(ReportWrenchEffortMessage message)
{
	// Set initial values of message fields
	message->presenceVector = newJausShortPresenceVector();

	message->propulsiveLinearEffortXPercent = newJausDouble(0);		// Scaled Short (-100, 100)
	message->propulsiveLinearEffortYPercent = newJausDouble(0);		// Scaled Short (-100, 100)
	message->propulsiveLinearEffortZPercent = newJausDouble(0);		// Scaled Short (-100, 100)
	message->propulsiveRotationalEffortXPercent = newJausDouble(0);	// Scaled Short (-100, 100)
	message->propulsiveRotationalEffortZPercent = newJausDouble(0);	// Scaled Short (-100, 100)
	message->propulsiveRotationalEffortYPercent = newJausDouble(0);	// Scaled Short (-100, 100)

	message->resistiveLinearEffortXPercent = newJausDouble(0);		// Scaled Byte (0, 100)
	message->resistiveLinearEffortYPercent = newJausDouble(0);		// Scaled Byte (0, 100)
	message->resistiveLinearEffortZPercent = newJausDouble(0);		// Scaled Byte (0, 100)
	message->resistiveRotationalEffortXPercent = newJausDouble(0);	// Scaled Byte (0, 100)
	message->resistiveRotationalEffortZPercent = newJausDouble(0);	// Scaled Byte (0, 100)
	message->resistiveRotationalEffortYPercent = newJausDouble(0);	// Scaled Byte (0, 100)
}

// Return boolean of success
static JausBoolean dataFromBuffer(ReportWrenchEffortMessage message, unsigned char *buffer, unsigned int bufferSizeBytes)
{
	int index = 0;
	JausShort tempShort;
	JausByte tempByte;

	if(bufferSizeBytes == message->dataSize)
	{
		// Unpack Message Fields from Buffer
		// Unpack according to presence vector
		if(!jausShortPresenceVectorFromBuffer(&message->presenceVector, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
		index += JAUS_SHORT_PRESENCE_VECTOR_SIZE_BYTES;

		if(jausShortPresenceVectorIsBitSet(message->presenceVector, JAUS_WRENCH_PV_PROPULSIVE_LINEAR_X_BIT))
		{
			// unpack propulsive linear effort X
			if(!jausShortFromBuffer(&tempShort, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_SHORT_SIZE_BYTES;
			
			// Scaled Short (-100, 100)
			message->propulsiveLinearEffortXPercent = jausShortToDouble(tempShort, -100, 100);
		}
		
		if(jausShortPresenceVectorIsBitSet(message->presenceVector, JAUS_WRENCH_PV_PROPULSIVE_LINEAR_Y_BIT))
		{
			// unpack propulsive linear effort Y
			if(!jausShortFromBuffer(&tempShort, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_SHORT_SIZE_BYTES;
			
			// Scaled Short (-100, 100)
			message->propulsiveLinearEffortYPercent = jausShortToDouble(tempShort, -100, 100);
		}
		
		if(jausShortPresenceVectorIsBitSet(message->presenceVector, JAUS_WRENCH_PV_PROPULSIVE_LINEAR_Z_BIT))
		{
			// unpack propulsive linear effort Z
			if(!jausShortFromBuffer(&tempShort, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_SHORT_SIZE_BYTES;
			
			// Scaled Short (-100, 100)
			message->propulsiveLinearEffortZPercent = jausShortToDouble(tempShort, -100, 100);
		}

		if(jausShortPresenceVectorIsBitSet(message->presenceVector, JAUS_WRENCH_PV_PROPULSIVE_ROTATIONAL_X_BIT))
		{
			// unpack propulsive rotational effort X
			if(!jausShortFromBuffer(&tempShort, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_SHORT_SIZE_BYTES;
			
			// Scaled Short (-100, 100)
			message->propulsiveRotationalEffortXPercent = jausShortToDouble(tempShort, -100, 100);
		}
		
		if(jausShortPresenceVectorIsBitSet(message->presenceVector, JAUS_WRENCH_PV_PROPULSIVE_ROTATIONAL_Y_BIT))
		{
			// unpack propulsive rotational effort Y
			if(!jausShortFromBuffer(&tempShort, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_SHORT_SIZE_BYTES;
			
			// Scaled Short (-100, 100)
			message->propulsiveRotationalEffortYPercent = jausShortToDouble(tempShort, -100, 100);
		}
		
		if(jausShortPresenceVectorIsBitSet(message->presenceVector, JAUS_WRENCH_PV_PROPULSIVE_ROTATIONAL_Z_BIT))
		{
			// unpack propulsive rotational effort Z
			if(!jausShortFromBuffer(&tempShort, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_SHORT_SIZE_BYTES;
			
			// Scaled Short (-100, 100)
			message->propulsiveRotationalEffortZPercent = jausShortToDouble(tempShort, -100, 100);
		}

		// Resistive
		if(jausShortPresenceVectorIsBitSet(message->presenceVector, JAUS_WRENCH_PV_RESISTIVE_LINEAR_X_BIT))
		{
			// unpack resistive linear effort X
			if(!jausByteFromBuffer(&tempByte, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_BYTE_SIZE_BYTES;
			
			// Scaled Byte (0, 100)
			message->resistiveLinearEffortXPercent = jausByteToDouble(tempByte, 0, 100);
		}
		
		if(jausShortPresenceVectorIsBitSet(message->presenceVector, JAUS_WRENCH_PV_RESISTIVE_LINEAR_Y_BIT))
		{
			// unpack resistive linear effort Y
			if(!jausByteFromBuffer(&tempByte, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_BYTE_SIZE_BYTES;
			
			// Scaled Byte (0, 100)
			message->resistiveLinearEffortYPercent = jausByteToDouble(tempByte, 0, 100);
		}
		
		if(jausShortPresenceVectorIsBitSet(message->presenceVector, JAUS_WRENCH_PV_RESISTIVE_LINEAR_Z_BIT))
		{
			// unpack resistive linear effort Z
			if(!jausByteFromBuffer(&tempByte, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_BYTE_SIZE_BYTES;
			
			// Scaled Byte (0, 100)
			message->resistiveLinearEffortZPercent = jausByteToDouble(tempByte, 0, 100);
		}

		if(jausShortPresenceVectorIsBitSet(message->presenceVector, JAUS_WRENCH_PV_RESISTIVE_ROTATIONAL_X_BIT))
		{
			// unpack resistive rotational effort X
			if(!jausByteFromBuffer(&tempByte, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_BYTE_SIZE_BYTES;
			
			// Scaled Byte (0, 100)
			message->resistiveRotationalEffortXPercent = jausByteToDouble(tempByte, 0, 100);
		}
		
		if(jausShortPresenceVectorIsBitSet(message->presenceVector, JAUS_WRENCH_PV_RESISTIVE_ROTATIONAL_Y_BIT))
		{
			// unpack resistive rotational effort Y
			if(!jausByteFromBuffer(&tempByte, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_BYTE_SIZE_BYTES;
			
			// Scaled Byte (0, 100)
			message->resistiveRotationalEffortYPercent = jausByteToDouble(tempByte, 0, 100);
		}
		
		if(jausShortPresenceVectorIsBitSet(message->presenceVector, JAUS_WRENCH_PV_RESISTIVE_ROTATIONAL_Z_BIT))
		{
			// unpack resistive rotational effort Z
			if(!jausByteFromBuffer(&tempByte, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_BYTE_SIZE_BYTES;
			
			// Scaled Byte (0, 100)
			message->resistiveRotationalEffortZPercent = jausByteToDouble(tempByte, 0, 100);
		}
		return JAUS_TRUE;
	}
	else
	{
		return JAUS_FALSE;
	}
}

// Returns number of bytes put into the buffer
static int dataToBuffer(ReportWrenchEffortMessage message, unsigned char *buffer, unsigned int bufferSizeBytes)
{
	int index = 0;
	JausShort tempShort;
	JausByte tempByte;

	if(bufferSizeBytes >= message->dataSize)
	{
		// Pack Message Fields to Buffer
		// Pack according to Presence Vector
		if(!jausShortPresenceVectorToBuffer(message->presenceVector, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
		index += JAUS_SHORT_PRESENCE_VECTOR_SIZE_BYTES;

		if(jausShortPresenceVectorIsBitSet(message->presenceVector, JAUS_WRENCH_PV_PROPULSIVE_LINEAR_X_BIT))
		{
			// Scaled Short (-100, 100)
			tempShort = jausShortFromDouble(message->propulsiveLinearEffortXPercent, -100, 100);

			// pack propulsive linear effort X
			if(!jausShortToBuffer(tempShort, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_SHORT_SIZE_BYTES;
		}
		
		if(jausShortPresenceVectorIsBitSet(message->presenceVector, JAUS_WRENCH_PV_PROPULSIVE_LINEAR_Y_BIT))
		{
			// Scaled Short (-100, 100)
			tempShort = jausShortFromDouble(message->propulsiveLinearEffortYPercent, -100, 100);

			// pack propulsive linear effort Y
			if(!jausShortToBuffer(tempShort, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_SHORT_SIZE_BYTES;
		}
		
		if(jausShortPresenceVectorIsBitSet(message->presenceVector, JAUS_WRENCH_PV_PROPULSIVE_LINEAR_Z_BIT))
		{
			// Scaled Short (-100, 100)
			tempShort = jausShortFromDouble(message->propulsiveLinearEffortZPercent, -100, 100);

			// pack propulsive linear effort Z
			if(!jausShortToBuffer(tempShort, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_SHORT_SIZE_BYTES;
		}

		if(jausShortPresenceVectorIsBitSet(message->presenceVector, JAUS_WRENCH_PV_PROPULSIVE_ROTATIONAL_X_BIT))
		{
			// Scaled Short (-100, 100)
			tempShort = jausShortFromDouble(message->propulsiveRotationalEffortXPercent, -100, 100);

			// pack propulsive rotational effort X
			if(!jausShortToBuffer(tempShort, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_SHORT_SIZE_BYTES;
		}
		
		if(jausShortPresenceVectorIsBitSet(message->presenceVector, JAUS_WRENCH_PV_PROPULSIVE_ROTATIONAL_Y_BIT))
		{
			// Scaled Short (-100, 100)
			tempShort = jausShortFromDouble(message->propulsiveRotationalEffortYPercent, -100, 100);

			// pack propulsive rotational effort Y
			if(!jausShortToBuffer(tempShort, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_SHORT_SIZE_BYTES;
		}
		
		if(jausShortPresenceVectorIsBitSet(message->presenceVector, JAUS_WRENCH_PV_PROPULSIVE_ROTATIONAL_Z_BIT))
		{
			// Scaled Short (-100, 100)
			tempShort = jausShortFromDouble(message->propulsiveRotationalEffortZPercent, -100, 100);

			// pack propulsive rotational effort Z
			if(!jausShortToBuffer(tempShort, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_SHORT_SIZE_BYTES;
		}

		// Resistive
		if(jausShortPresenceVectorIsBitSet(message->presenceVector, JAUS_WRENCH_PV_RESISTIVE_LINEAR_X_BIT))
		{
			// Scaled Byte (0, 100)
			tempByte = jausByteFromDouble(message->resistiveLinearEffortXPercent, 0, 100);
		
			// pack resistive linear effort X
			if(!jausByteToBuffer(tempByte, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_BYTE_SIZE_BYTES;
		}
		
		if(jausShortPresenceVectorIsBitSet(message->presenceVector, JAUS_WRENCH_PV_RESISTIVE_LINEAR_Y_BIT))
		{
			// Scaled Byte (0, 100)
			tempByte = jausByteFromDouble(message->resistiveLinearEffortYPercent, 0, 100);
		
			// pack resistive linear effort Y
			if(!jausByteToBuffer(tempByte, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_BYTE_SIZE_BYTES;
		}
		
		if(jausShortPresenceVectorIsBitSet(message->presenceVector, JAUS_WRENCH_PV_RESISTIVE_LINEAR_Z_BIT))
		{
			// Scaled Byte (0, 100)
			tempByte = jausByteFromDouble(message->resistiveLinearEffortZPercent, 0, 100);
		
			// pack resistive linear effort Z
			if(!jausByteToBuffer(tempByte, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_BYTE_SIZE_BYTES;
		}

		if(jausShortPresenceVectorIsBitSet(message->presenceVector, JAUS_WRENCH_PV_RESISTIVE_ROTATIONAL_X_BIT))
		{
			// Scaled Byte (0, 100)
			tempByte = jausByteFromDouble(message->resistiveRotationalEffortXPercent, 0, 100);
		
			// pack resistive rotational effort X
			if(!jausByteToBuffer(tempByte, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_BYTE_SIZE_BYTES;
		}
		
		if(jausShortPresenceVectorIsBitSet(message->presenceVector, JAUS_WRENCH_PV_RESISTIVE_ROTATIONAL_Y_BIT))
		{
			// Scaled Byte (0, 100)
			tempByte = jausByteFromDouble(message->resistiveRotationalEffortYPercent, 0, 100);
		
			// pack resistive rotational effort Y
			if(!jausByteToBuffer(tempByte, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_BYTE_SIZE_BYTES;
		}
		
		if(jausShortPresenceVectorIsBitSet(message->presenceVector, JAUS_WRENCH_PV_RESISTIVE_ROTATIONAL_Z_BIT))
		{
			// Scaled Byte (0, 100)
			tempByte = jausByteFromDouble(message->resistiveRotationalEffortZPercent, 0, 100);
		
			// pack resistive rotational effort Z
			if(!jausByteToBuffer(tempByte, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_BYTE_SIZE_BYTES;
		}
	}
	return index;
}

// ************************************************************************************************************** //
//                                    NON-USER CONFIGURED FUNCTIONS
// ************************************************************************************************************** //

ReportWrenchEffortMessage reportWrenchEffortMessageCreate(void)
{
	ReportWrenchEffortMessage message;

	message = (ReportWrenchEffortMessage)malloc( sizeof(ReportWrenchEffortMessageStruct) );
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

void reportWrenchEffortMessageDestroy(ReportWrenchEffortMessage message)
{
	jausAddressDestroy(message->source);
	jausAddressDestroy(message->destination);
	free(message);
}

JausBoolean reportWrenchEffortMessageFromBuffer(ReportWrenchEffortMessage message, unsigned char* buffer, unsigned int bufferSizeBytes)
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

JausBoolean reportWrenchEffortMessageToBuffer(ReportWrenchEffortMessage message, unsigned char *buffer, unsigned int bufferSizeBytes)
{
	if(bufferSizeBytes < reportWrenchEffortMessageSize(message))
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
			return JAUS_FALSE; // headerToReportWrenchEffortBuffer failed
		}
	}
}

JausBoolean reportWrenchEffortMessageToUdpBuffer(ReportWrenchEffortMessage message, unsigned char *buffer, unsigned int bufferSizeBytes)
{
	if(bufferSizeBytes < reportWrenchEffortMessageUdpSize(message))
	{
		return JAUS_FALSE; // improper size
	}
	else
	{
		strncpy((char *)buffer, JAUS_UDP_HEADER, JAUS_UDP_HEADER_SIZE_BYTES); //copies the UDP header into the buffer
		return reportWrenchEffortMessageToBuffer(message, buffer+JAUS_UDP_HEADER_SIZE_BYTES, bufferSizeBytes - JAUS_UDP_HEADER_SIZE_BYTES);
	}
}

ReportWrenchEffortMessage reportWrenchEffortMessageFromJausMessage(JausMessage jausMessage)
{
	ReportWrenchEffortMessage message;
	
	if(jausMessage->commandCode != commandCode)
	{
		return NULL; // Wrong message type
	}
	else
	{
		message = (ReportWrenchEffortMessage)malloc( sizeof(ReportWrenchEffortMessageStruct) );
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

JausMessage reportWrenchEffortMessageToJausMessage(ReportWrenchEffortMessage message)
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

unsigned int reportWrenchEffortMessageUdpSize(ReportWrenchEffortMessage message)
{
	return (unsigned int)(message->dataSize + JAUS_HEADER_SIZE_BYTES + JAUS_UDP_HEADER_SIZE_BYTES);
}

unsigned int reportWrenchEffortMessageSize(ReportWrenchEffortMessage message)
{
	return (unsigned int)(message->dataSize + JAUS_HEADER_SIZE_BYTES);
}

//********************* PRIVATE HEADER FUNCTIONS **********************//

static JausBoolean headerFromBuffer(ReportWrenchEffortMessage message, unsigned char *buffer, unsigned int bufferSizeBytes)
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

static JausBoolean headerToBuffer(ReportWrenchEffortMessage message, unsigned char *buffer, unsigned int bufferSizeBytes)
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

