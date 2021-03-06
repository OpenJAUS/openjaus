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
// File Name: reportPayloadInterfaceMessage.c
//
// Written By: Bob Toucthon
//
// Version: 3.2
//
// Date: // Date: 3/13/06
//
// This file defines the functionality of a ReportPayloadInterfaceMessage
// NOTE WELL: this message will also be used for general purpose information exchange

#include <stdlib.h>
#include <string.h>
#include "cimar/jaus.h"

static const int commandCode = JAUS_REPORT_PAYLOAD_INTERFACE;
static const int maxDataSizeBytes = 512000;

static JausBoolean headerFromBuffer(ReportPayloadInterfaceMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);
static JausBoolean headerToBuffer(ReportPayloadInterfaceMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);

static JausBoolean dataFromBuffer(ReportPayloadInterfaceMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);
static int dataToBuffer(ReportPayloadInterfaceMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);
static void dataInitialize(ReportPayloadInterfaceMessage message);
static void dataDestroy(ReportPayloadInterfaceMessage message);

// ************************************************************************************************************** //
//                                    USER CONFIGURED FUNCTIONS
// ************************************************************************************************************** //

// Initializes the message-specific fields
static void dataInitialize(ReportPayloadInterfaceMessage message)
{
	// Set Experimental Flag
	message->expFlag = JAUS_EXPERIMENTAL_MESSAGE;

	// Set initial values of message fields
	message->jausPayloadInterface = NULL;
}

// Destructs the message-specific fields
static void dataDestroy(ReportPayloadInterfaceMessage message)
{
	// Free message fields
	// We Don't Destroy the message->jausPayloadInterface because it belongs to the component, not this message
	//jausPayloadInterfaceDestroy(message->jausPayloadInterface);
}

// Return boolean of success
static JausBoolean dataFromBuffer(ReportPayloadInterfaceMessage message, unsigned char *buffer, unsigned int bufferSizeBytes)
{
	int index = 0, i = 0, len = 0;
	JausByte payloadCommandInterfaceCount = 0;
	JausByte payloadInformationInterfaceCount = 0;
	JausByte tempByte, typeCode;
	JausUnsignedShort tempUShort, tempX=0, tempY=0, tempW=0, tempH=0;
	char * identifierString = NULL;
	char * tempString = NULL;
	JausTypeCode minValue, defaultValue, maxValue;
	
	if(bufferSizeBytes == message->dataSize)
	{
		// Unpack Message Fields from Buffer
		// unpack presence vector
		if(!jausByteFromBuffer(&message->jausPayloadInterface->presenceVector, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
		index += JAUS_BYTE_SIZE_BYTES;
		
		// # payload interfaces
		if(!jausByteFromBuffer(&payloadCommandInterfaceCount, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
		index += JAUS_BYTE_SIZE_BYTES;
		
		if(!jausByteFromBuffer(&payloadInformationInterfaceCount, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
		index += JAUS_BYTE_SIZE_BYTES;
		
		if((payloadCommandInterfaceCount + payloadInformationInterfaceCount) < 1) return JAUS_FALSE;
		
		for(i = 0; i < payloadCommandInterfaceCount; i++)
		{			
			// unpack command identifier
			len = strlen((char *)(buffer+index));
			identifierString = malloc(len + 1);
			strncpy(identifierString, (char *)(buffer+index), bufferSizeBytes-index);
			index += len + 1;
			
			// unpack payloadInterface type
			if(!jausByteFromBuffer(&typeCode, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_BYTE_SIZE_BYTES;
		
			// Create payloadInterface with this identifier and typeCode
			jausAddNewCommandInterface(message->jausPayloadInterface, identifierString, typeCode);
			
			// unpack/set units
			if(!jausByteFromBuffer(&tempByte, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			jausSetCommandInterfaceUnits(message->jausPayloadInterface, identifierString, tempByte);
			index += JAUS_BYTE_SIZE_BYTES;
			
			// unpack/set blocking flag
			if(!jausByteFromBuffer(&tempByte, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			if(tempByte & 0x01) jausSetCommandInterfaceBlockingFlag(message->jausPayloadInterface, identifierString);
			index += JAUS_BYTE_SIZE_BYTES;
			
			// unpack/set min/default/max values
			if(!jausMinMaxDefaultFromBuffer(&minValue, buffer+index, bufferSizeBytes-index, typeCode)) return JAUS_FALSE;
			index += jausMinMaxDefaultSizeBytes(typeCode);

			if(!jausMinMaxDefaultFromBuffer(&defaultValue, buffer+index, bufferSizeBytes-index, typeCode)) return JAUS_FALSE;
			index += jausMinMaxDefaultSizeBytes(typeCode);
			
			if(!jausMinMaxDefaultFromBuffer(&maxValue, buffer+index, bufferSizeBytes-index, typeCode)) return JAUS_FALSE;
			index += jausMinMaxDefaultSizeBytes(typeCode);

			jausSetCommandInterfaceMinMax(message->jausPayloadInterface, identifierString, minValue, maxValue);
			jausSetCommandInterfaceDefault(message->jausPayloadInterface, identifierString, defaultValue);
			
			// unpack enumeration length
			if(!jausUnsignedShortFromBuffer(&tempUShort, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
			
			// unpack/set enumeration if present
			if(tempUShort != 0)
			{
				tempString = malloc(tempUShort);
				strcpy(tempString, (char *)(buffer+index));
				index += tempUShort;
				jausSetCommandInterfaceEnumeration(message->jausPayloadInterface, identifierString, tempString);
			}

			// unpack/set HMI recommendation, if in PV
			if(jausBytePresenceVectorIsBitSet(message->jausPayloadInterface->presenceVector, JAUS_PAYLOAD_INTERFACE_PV_HMI_RECOMMENDATION_BIT))		
			{
				if(!jausByteFromBuffer(&tempByte, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
				jausSetCommandInterfaceHmiRecommendation(message->jausPayloadInterface, identifierString, tempByte);
				index += JAUS_BYTE_SIZE_BYTES;
			}
			
			// unpack/set HMI location, if in PV
			tempUShort = index; // set to test if any new parameters were available
			if(jausBytePresenceVectorIsBitSet(message->jausPayloadInterface->presenceVector, JAUS_PAYLOAD_INTERFACE_PV_HMI_XPOS_BIT))
			{
				if(!jausUnsignedShortFromBuffer(&tempX, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
				index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
			}			
			if(jausBytePresenceVectorIsBitSet(message->jausPayloadInterface->presenceVector, JAUS_PAYLOAD_INTERFACE_PV_HMI_YPOS_BIT))
			{
				if(!jausUnsignedShortFromBuffer(&tempY, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
				index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
			}			
			if(jausBytePresenceVectorIsBitSet(message->jausPayloadInterface->presenceVector, JAUS_PAYLOAD_INTERFACE_PV_HMI_WIDTH_BIT))
			{
				if(!jausUnsignedShortFromBuffer(&tempW, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
				index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
			}			
			if(jausBytePresenceVectorIsBitSet(message->jausPayloadInterface->presenceVector, JAUS_PAYLOAD_INTERFACE_PV_HMI_HEIGHT_BIT))
			{
				if(!jausUnsignedShortFromBuffer(&tempH, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
				index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
			}			
			if(tempUShort != index)
			{			
				jausSetCommandInterfaceHmiParameters(message->jausPayloadInterface, identifierString, tempX,tempY,tempW,tempH);
			}
		}

		for(i = 0; i < payloadInformationInterfaceCount; i++)
		{			
			// unpack command identifier
			len = strlen((char *)(buffer+index));
			identifierString = malloc(len +1);
			strncpy(identifierString, (char *)(buffer+index), bufferSizeBytes-index);
			index += len + 1;
			
			// unpack command association
			if(!jausByteFromBuffer(&tempByte, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_BYTE_SIZE_BYTES;
			
			// unpack jausPayloadInterface type
			if(!jausByteFromBuffer(&typeCode, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_BYTE_SIZE_BYTES;
		
			// Create payloadInterface with this identifier and typeCode
			jausAddNewInformationInterface(message->jausPayloadInterface, identifierString, typeCode);
			
			// set command association
			jausSetInformationInterfaceCommandInterfaceAssoc(message->jausPayloadInterface, identifierString, tempByte);

			// unpack/set units
			if(!jausByteFromBuffer(&tempByte, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			jausSetInformationInterfaceUnits(message->jausPayloadInterface, identifierString, tempByte);
			index += JAUS_BYTE_SIZE_BYTES;
			
			// unpack/set min/default/max values
			if(!jausMinMaxDefaultFromBuffer(&minValue, buffer+index, bufferSizeBytes-index, typeCode)) return JAUS_FALSE;
			index += jausMinMaxDefaultSizeBytes(typeCode);

			if(!jausMinMaxDefaultFromBuffer(&defaultValue, buffer+index, bufferSizeBytes-index, typeCode)) return JAUS_FALSE;
			index += jausMinMaxDefaultSizeBytes(typeCode);
			
			if(!jausMinMaxDefaultFromBuffer(&maxValue, buffer+index, bufferSizeBytes-index, typeCode)) return JAUS_FALSE;
			index += jausMinMaxDefaultSizeBytes(typeCode);

			jausSetInformationInterfaceMinMax(message->jausPayloadInterface, identifierString, minValue, maxValue);
			jausSetInformationInterfaceDefault(message->jausPayloadInterface, identifierString, defaultValue);
			
			// unpack enumeration length
			if(!jausUnsignedShortFromBuffer(&tempUShort, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
			
			// unpack/set enumeration if present
			if(tempUShort != 0)
			{
				tempString = malloc(tempUShort);
				strcpy(tempString, (char *)(buffer+index));
				index += tempUShort;
				jausSetInformationInterfaceEnumeration(message->jausPayloadInterface, identifierString, tempString);
			}

			// unpack/set HMI recommendation, if in PV
			if(jausBytePresenceVectorIsBitSet(message->jausPayloadInterface->presenceVector, JAUS_PAYLOAD_INTERFACE_PV_HMI_RECOMMENDATION_BIT))		
			{
				if(!jausByteFromBuffer(&tempByte, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
				jausSetInformationInterfaceHmiRecommendation(message->jausPayloadInterface, identifierString, tempByte);
				index += JAUS_BYTE_SIZE_BYTES;
			}
			
			// unpack/set HMI location, if in PV
			tempUShort = index; // set to test if any new parameters were available
			if(jausBytePresenceVectorIsBitSet(message->jausPayloadInterface->presenceVector, JAUS_PAYLOAD_INTERFACE_PV_HMI_XPOS_BIT))
			{
				if(!jausUnsignedShortFromBuffer(&tempX, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
				index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
			}			
			if(jausBytePresenceVectorIsBitSet(message->jausPayloadInterface->presenceVector, JAUS_PAYLOAD_INTERFACE_PV_HMI_YPOS_BIT))
			{
				if(!jausUnsignedShortFromBuffer(&tempY, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
				index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
			}			
			if(jausBytePresenceVectorIsBitSet(message->jausPayloadInterface->presenceVector, JAUS_PAYLOAD_INTERFACE_PV_HMI_WIDTH_BIT))
			{
				if(!jausUnsignedShortFromBuffer(&tempW, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
				index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
			}			
			if(jausBytePresenceVectorIsBitSet(message->jausPayloadInterface->presenceVector, JAUS_PAYLOAD_INTERFACE_PV_HMI_HEIGHT_BIT))
			{
				if(!jausUnsignedShortFromBuffer(&tempH, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
				index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
			}			
			if(tempUShort != index) // only bother doing this if something new was available
			{			
				jausSetInformationInterfaceHmiParameters(message->jausPayloadInterface, identifierString, tempX,tempY,tempW,tempH);
			}
		}
		return JAUS_TRUE;
	}
	else
	{
		return JAUS_FALSE;
	}
}

// Returns number of bytes put into the buffer
static int dataToBuffer(ReportPayloadInterfaceMessage message, unsigned char *buffer, unsigned int bufferSizeBytes)
{
	int index = 0, len = 0;
	int i = 0;
	int successFlag = SUCCESS;
	JausByte payloadCommandInterfaceCount = 0;
	JausByte payloadInformationInterfaceCount = 0;
	JausByte tempByte, typeCode;
	JausUnsignedShort tempUShort;
	char * identifierString = NULL;
	char * tempString = NULL;
	JausTypeCode minValue, defaultValue, maxValue;

	if(bufferSizeBytes >= message->dataSize)
	{
		// Pack Message Fields to Buffer
		// pack presence vector
		if(!jausByteToBuffer(message->jausPayloadInterface->presenceVector, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
		index += JAUS_BYTE_SIZE_BYTES;
		
		// # payload interfaces
		payloadCommandInterfaceCount = message->jausPayloadInterface->jausCommandInterfaces->elementCount;
		payloadInformationInterfaceCount = message->jausPayloadInterface->jausInformationInterfaces->elementCount;
		
		if(!jausByteToBuffer(payloadCommandInterfaceCount, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
		index += JAUS_BYTE_SIZE_BYTES;
		
		if(!jausByteToBuffer(payloadInformationInterfaceCount, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
		index += JAUS_BYTE_SIZE_BYTES;
		
		for(i = 0; i < payloadCommandInterfaceCount; i++)
		{			
			// get/pack command identifier
			successFlag = SUCCESS;
			identifierString = jausGetCommandInterfaceIdentifierByIndex(message->jausPayloadInterface, i + 1, &successFlag);
			if (successFlag)
			{
				len = strlen(identifierString);
				strncpy((char *)(buffer+index), identifierString, bufferSizeBytes-index);
				index += len + 1;
			}
			
			// get/pack payloadInterface type
			successFlag = SUCCESS;
			typeCode = jausGetCommandInterfaceTypeCode(message->jausPayloadInterface, identifierString, &successFlag);
			if (successFlag)
			{
				if(!jausByteToBuffer(typeCode, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
				index += JAUS_BYTE_SIZE_BYTES;
			}
		
			// get/pack units
			successFlag = SUCCESS;
			tempByte = jausGetCommandInterfaceUnits(message->jausPayloadInterface, identifierString, &successFlag);
			if (successFlag)
			{
				if(!jausByteToBuffer(tempByte, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
				index += JAUS_BYTE_SIZE_BYTES;
			}

			// get/pack blocking flag
			successFlag = SUCCESS;
			if(jausGetCommandInterfaceBlockingFlag(message->jausPayloadInterface, identifierString, &successFlag))
			{
				if(!jausByteToBuffer(0x01, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
				index += JAUS_BYTE_SIZE_BYTES;
			}
			else if (successFlag)
			{
				if(!jausByteToBuffer(0x00, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
				index += JAUS_BYTE_SIZE_BYTES;				
			}

			// get/pack min/default/max values
			successFlag = SUCCESS;
			minValue = jausGetCommandInterfaceMin(message->jausPayloadInterface, identifierString, &successFlag);
			if (successFlag)
			{
				if(!jausMinMaxDefaultToBuffer(minValue, buffer+index, bufferSizeBytes-index, typeCode)) return JAUS_FALSE;
				index += jausMinMaxDefaultSizeBytes(typeCode);
			}
			
			successFlag = SUCCESS;
			defaultValue = jausGetCommandInterfaceDefault(message->jausPayloadInterface, identifierString, &successFlag);
			if (successFlag)
			{
				if(!jausMinMaxDefaultToBuffer(defaultValue, buffer+index, bufferSizeBytes-index, typeCode)) return JAUS_FALSE;
				index += jausMinMaxDefaultSizeBytes(typeCode);
			}
			
			successFlag = SUCCESS;
			maxValue = jausGetCommandInterfaceMax(message->jausPayloadInterface, identifierString, &successFlag);
			if (successFlag)
			{
				if(!jausMinMaxDefaultToBuffer(maxValue, buffer+index, bufferSizeBytes-index, typeCode)) return JAUS_FALSE;
				index += jausMinMaxDefaultSizeBytes(typeCode);
			}
			
			// get/pack enumeration length
			successFlag = SUCCESS;
			tempUShort = jausGetCommandInterfaceEnumerationLength(message->jausPayloadInterface, identifierString, &successFlag);
			if (successFlag)
			{
				if(!jausUnsignedShortToBuffer(tempUShort, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
				index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
			}
			
			// get/pack enumeration if present
			if(tempUShort != 0)
			{
				tempString = jausGetCommandInterfaceEnumeration(message->jausPayloadInterface, identifierString, &successFlag);
				strcpy((char *)(buffer+index), tempString);
				index += tempUShort;
			}

			// get/pack HMI recommendation, if in PV
			if(jausBytePresenceVectorIsBitSet(message->jausPayloadInterface->presenceVector, JAUS_PAYLOAD_INTERFACE_PV_HMI_RECOMMENDATION_BIT))		
			{
				successFlag = SUCCESS;
				tempByte = jausGetCommandInterfaceHmiRecommendation(message->jausPayloadInterface, identifierString, &successFlag);
				if (successFlag)
				{
					if(!jausByteToBuffer(tempByte, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
					index += JAUS_BYTE_SIZE_BYTES;
				}
			}
			// get/pack HMI location, if in PV
			if(jausBytePresenceVectorIsBitSet(message->jausPayloadInterface->presenceVector, JAUS_PAYLOAD_INTERFACE_PV_HMI_XPOS_BIT))
			{
				tempUShort = jausGetCommandInterfaceHmiXPositionPixels(message->jausPayloadInterface, identifierString, &successFlag);
				if (successFlag)
				{
					if(!jausUnsignedShortToBuffer(tempUShort, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
					index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
				}
			}

			if(jausBytePresenceVectorIsBitSet(message->jausPayloadInterface->presenceVector, JAUS_PAYLOAD_INTERFACE_PV_HMI_YPOS_BIT))
			{
				tempUShort = jausGetCommandInterfaceHmiYPositionPixels(message->jausPayloadInterface, identifierString, &successFlag);
				if (successFlag)
				{
					if(!jausUnsignedShortToBuffer(tempUShort, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
					index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
				}
			}

			if(jausBytePresenceVectorIsBitSet(message->jausPayloadInterface->presenceVector, JAUS_PAYLOAD_INTERFACE_PV_HMI_WIDTH_BIT))
			{
				tempUShort = jausGetCommandInterfaceHmiWidthPixels(message->jausPayloadInterface, identifierString, &successFlag);
				if (successFlag)
				{
					if(!jausUnsignedShortToBuffer(tempUShort, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
					index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
				}
			}

			if(jausBytePresenceVectorIsBitSet(message->jausPayloadInterface->presenceVector, JAUS_PAYLOAD_INTERFACE_PV_HMI_HEIGHT_BIT))
			{
				tempUShort = jausGetCommandInterfaceHmiHeightPixels(message->jausPayloadInterface, identifierString, &successFlag);
				if (successFlag)
				{
					if(!jausUnsignedShortToBuffer(tempUShort, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
					index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
				}
			}
		}

		for(i = 0; i < payloadInformationInterfaceCount; i++)
		{			
			// get/pack information identifier
			successFlag = SUCCESS;
			identifierString = jausGetInformationInterfaceIdentifierByIndex(message->jausPayloadInterface, i + 1, &successFlag);
			if (successFlag)
			{
				len = strlen(identifierString);
				strncpy((char *)(buffer+index), identifierString, bufferSizeBytes-index);
				index += len + 1;
			}
			
			// get/pack command interface association
			successFlag = SUCCESS;
			tempByte = jausGetInformationInterfaceCommandInterfaceAssoc(message->jausPayloadInterface, identifierString, &successFlag);
			if (successFlag)
			{
				if(!jausByteToBuffer(tempByte, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
				index += JAUS_BYTE_SIZE_BYTES;
			}

			// get/pack payloadInterface type
			successFlag = SUCCESS;
			typeCode = jausGetInformationInterfaceTypeCode(message->jausPayloadInterface, identifierString, &successFlag);
			if (successFlag)
			{
				if(!jausByteToBuffer(typeCode, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
				index += JAUS_BYTE_SIZE_BYTES;
			}
		
			// get/pack units
			successFlag = SUCCESS;
			tempByte = jausGetInformationInterfaceUnits(message->jausPayloadInterface, identifierString, &successFlag);
			if (successFlag)
			{
				if(!jausByteToBuffer(tempByte, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
				index += JAUS_BYTE_SIZE_BYTES;
			}

			// get/pack min/default/max values
			successFlag = SUCCESS;
			minValue = jausGetInformationInterfaceMin(message->jausPayloadInterface, identifierString, &successFlag);
			if (successFlag)
			{
				if(!jausMinMaxDefaultToBuffer(minValue, buffer+index, bufferSizeBytes-index, typeCode)) return JAUS_FALSE;
				index += jausMinMaxDefaultSizeBytes(typeCode);
			}
			
			successFlag = SUCCESS;
			defaultValue = jausGetInformationInterfaceDefault(message->jausPayloadInterface, identifierString, &successFlag);
			if (successFlag)
			{
				if(!jausMinMaxDefaultToBuffer(defaultValue, buffer+index, bufferSizeBytes-index, typeCode)) return JAUS_FALSE;
				index += jausMinMaxDefaultSizeBytes(typeCode);
			}
			
			successFlag = SUCCESS;
			maxValue = jausGetInformationInterfaceMax(message->jausPayloadInterface, identifierString, &successFlag);
			if (successFlag)
			{
				if(!jausMinMaxDefaultToBuffer(maxValue, buffer+index, bufferSizeBytes-index, typeCode)) return JAUS_FALSE;
				index += jausMinMaxDefaultSizeBytes(typeCode);
			}
			
			// get/pack enumeration length
			successFlag = SUCCESS;
			tempUShort = jausGetInformationInterfaceEnumerationLength(message->jausPayloadInterface, identifierString, &successFlag);
			if (successFlag)
			{
				if(!jausUnsignedShortToBuffer(tempUShort, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
				index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
			}
			
			// get/pack enumeration if present
			if(tempUShort != 0)
			{
				tempString = jausGetInformationInterfaceEnumeration(message->jausPayloadInterface, identifierString, &successFlag);
				strcpy((char *)(buffer+index), tempString);
				index += tempUShort;
			}

			// get/pack HMI recommendation, if in PV
			if(jausBytePresenceVectorIsBitSet(message->jausPayloadInterface->presenceVector, JAUS_PAYLOAD_INTERFACE_PV_HMI_RECOMMENDATION_BIT))		
			{
				successFlag = SUCCESS;
				tempByte = jausGetInformationInterfaceHmiRecommendation(message->jausPayloadInterface, identifierString, &successFlag);
				if (successFlag)
				{
					if(!jausByteToBuffer(tempByte, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
					index += JAUS_BYTE_SIZE_BYTES;
				}
			}
			// get/pack HMI location, if in PV
			if(jausBytePresenceVectorIsBitSet(message->jausPayloadInterface->presenceVector, JAUS_PAYLOAD_INTERFACE_PV_HMI_XPOS_BIT))
			{
				tempUShort = jausGetInformationInterfaceHmiXPositionPixels(message->jausPayloadInterface, identifierString, &successFlag);
				if (successFlag)
				{
					if(!jausUnsignedShortToBuffer(tempUShort, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
					index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
				}
			}

			if(jausBytePresenceVectorIsBitSet(message->jausPayloadInterface->presenceVector, JAUS_PAYLOAD_INTERFACE_PV_HMI_YPOS_BIT))
			{
				tempUShort = jausGetInformationInterfaceHmiYPositionPixels(message->jausPayloadInterface, identifierString, &successFlag);
				if (successFlag)
				{
					if(!jausUnsignedShortToBuffer(tempUShort, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
					index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
				}
			}

			if(jausBytePresenceVectorIsBitSet(message->jausPayloadInterface->presenceVector, JAUS_PAYLOAD_INTERFACE_PV_HMI_WIDTH_BIT))
			{
				tempUShort = jausGetInformationInterfaceHmiWidthPixels(message->jausPayloadInterface, identifierString, &successFlag);
				if (successFlag)
				{
					if(!jausUnsignedShortToBuffer(tempUShort, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
					index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
				}
			}

			if(jausBytePresenceVectorIsBitSet(message->jausPayloadInterface->presenceVector, JAUS_PAYLOAD_INTERFACE_PV_HMI_HEIGHT_BIT))
			{
				tempUShort = jausGetInformationInterfaceHmiHeightPixels(message->jausPayloadInterface, identifierString, &successFlag);
				if (successFlag)
				{
					if(!jausUnsignedShortToBuffer(tempUShort, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
					index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
				}
			}
		}
	}
	return index;
}

// ************************************************************************************************************** //
//                                    NON-USER CONFIGURED FUNCTIONS
// ************************************************************************************************************** //

ReportPayloadInterfaceMessage reportPayloadInterfaceMessageCreate(void)
{
	ReportPayloadInterfaceMessage message;

	message = (ReportPayloadInterfaceMessage)malloc( sizeof(ReportPayloadInterfaceMessageStruct) );
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

void reportPayloadInterfaceMessageDestroy(ReportPayloadInterfaceMessage message)
{
	dataDestroy(message);
	jausAddressDestroy(message->source);
	jausAddressDestroy(message->destination);
	free(message);
}

JausBoolean reportPayloadInterfaceMessageFromBuffer(ReportPayloadInterfaceMessage message, unsigned char* buffer, unsigned int bufferSizeBytes)
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

JausBoolean reportPayloadInterfaceMessageToBuffer(ReportPayloadInterfaceMessage message, unsigned char *buffer, unsigned int bufferSizeBytes)
{
	if(bufferSizeBytes < reportPayloadInterfaceMessageSize(message))
	{
		return JAUS_FALSE; //improper size	
	}
	else
	{	
		if(headerToBuffer(message, buffer, bufferSizeBytes))
		{
			message->dataSize = dataToBuffer(message, buffer+JAUS_HEADER_SIZE_BYTES, bufferSizeBytes - JAUS_HEADER_SIZE_BYTES);
			return JAUS_TRUE;
		}
		else
		{
			return JAUS_FALSE; // headerToReportPayloadInterfaceBuffer failed
		}
	}
}

JausBoolean reportPayloadInterfaceMessageToUdpBuffer(ReportPayloadInterfaceMessage message, unsigned char *buffer, unsigned int bufferSizeBytes)
{
	if(bufferSizeBytes < reportPayloadInterfaceMessageUdpSize(message))
	{
		return JAUS_FALSE; // improper size
	}
	else
	{
		strncpy( (char *) buffer, JAUS_UDP_HEADER, JAUS_UDP_HEADER_SIZE_BYTES); //copies the UDP header into the buffer
		return reportPayloadInterfaceMessageToBuffer(message, buffer+JAUS_UDP_HEADER_SIZE_BYTES, bufferSizeBytes - JAUS_UDP_HEADER_SIZE_BYTES);
	}
}

ReportPayloadInterfaceMessage reportPayloadInterfaceMessageFromJausMessage(JausMessage jausMessage)
{
	ReportPayloadInterfaceMessage message;
	
	if(jausMessage->commandCode != commandCode)
	{
		return NULL; // Wrong message type
	}
	else
	{
		message = (ReportPayloadInterfaceMessage)malloc( sizeof(ReportPayloadInterfaceMessageStruct) );
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

JausMessage reportPayloadInterfaceMessageToJausMessage(ReportPayloadInterfaceMessage message)
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

unsigned int reportPayloadInterfaceMessageUdpSize(ReportPayloadInterfaceMessage message)
{
	return (unsigned int)(message->dataSize + JAUS_HEADER_SIZE_BYTES + JAUS_UDP_HEADER_SIZE_BYTES);
}

unsigned int reportPayloadInterfaceMessageSize(ReportPayloadInterfaceMessage message)
{
	return (unsigned int)(message->dataSize + JAUS_HEADER_SIZE_BYTES);
}

//********************* PRIVATE HEADER FUNCTIONS **********************//

static JausBoolean headerFromBuffer(ReportPayloadInterfaceMessage message, unsigned char *buffer, unsigned int bufferSizeBytes)
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

static JausBoolean headerToBuffer(ReportPayloadInterfaceMessage message, unsigned char *buffer, unsigned int bufferSizeBytes)
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

