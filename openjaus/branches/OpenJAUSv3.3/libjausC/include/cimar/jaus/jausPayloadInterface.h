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
// File Name: jausPayloadInterface.h
//
// Written By: Bob Touchton (btouch AT comcast DOT net)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines the attributes of a ReportPayloadInterfaceMessage support functions

#ifndef REPORT_PAYLOAD_INTERFACE_H
#define REPORT_PAYLOAD_INTERFACE_H

#include "cimar/jaus.h"

#define NO_ENUM 	0
#define NO_HMI	 	0
//#define FAILURE 	-1
#define SUCCESS		1
#define FAILURE		0

// Type Codes
#define TYPE_CODE_SHORT			1
#define TYPE_CODE_INTEGER		2
#define TYPE_CODE_LONG			3
#define TYPE_CODE_BYTE			4
#define TYPE_CODE_U_SHORT		5
#define TYPE_CODE_U_INTEGER		6
#define TYPE_CODE_U_LONG		7
#define TYPE_CODE_FLOAT			8
#define TYPE_CODE_DOUBLE		9

#define TYPE_CODE_SCALED_U_BYTE			10
#define TYPE_CODE_SCALED_SHORT			11
#define TYPE_CODE_SCALED_U_SHORT		12
#define TYPE_CODE_SCALED_INTEGER		13
#define TYPE_CODE_SCALED_U_INTEGER		14
#define TYPE_CODE_SCALED_LONG			15
#define TYPE_CODE_SCALED_U_LONG			16

#define TYPE_CODE_ENUM			17
#define TYPE_CODE_BOOLEAN		18
#define TYPE_CODE_STRING		19

#define TYPE_CODE_U_BYTE_TUPLE			20
#define TYPE_CODE_U_SHORT_TUPLE			21
#define TYPE_CODE_U_INTEGER_TUPLE		22

// Presence Vector Bits
#ifndef JAUS_PAYLOAD_INTERFACE_PV
#define JAUS_PAYLOAD_INTERFACE_PV
#define JAUS_PAYLOAD_INTERFACE_PV_HMI_RECOMMENDATION_BIT		0
#define JAUS_PAYLOAD_INTERFACE_PV_HMI_XPOS_BIT		1
#define JAUS_PAYLOAD_INTERFACE_PV_HMI_YPOS_BIT		2
#define JAUS_PAYLOAD_INTERFACE_PV_HMI_WIDTH_BIT		3
#define JAUS_PAYLOAD_INTERFACE_PV_HMI_HEIGHT_BIT	4
#endif

// ************************************************************************************************************************************
//			Report PayloadInterface Support
// ************************************************************************************************************************************

typedef union
{
	JausShort shortValue;
	JausInteger integerValue;
	JausLong longValue;
	JausByte byteValue;
	JausUnsignedShort uShortValue;
	JausUnsignedInteger uIntegerValue;
	JausUnsignedLong uLongValue;
	JausFloat floatValue;
	JausDouble longFloatValue;	
	JausByte enumValue;
	JausBoolean booleanValue;
	struct
	{
		JausUnsignedShort length;
		char * value;
	}string;
	struct
	{
		JausByte one;
		JausByte two;		
	}byteTuple;
	struct
	{
		JausUnsignedShort one;
		JausUnsignedShort two;		
	}shortTuple;
	struct
	{
		JausUnsignedInteger one;
		JausUnsignedInteger two;		
	}integerTuple;
}JausTypeCode;

typedef struct
{
	JausBytePresenceVector presenceVector;	
	Vector jausCommandInterfaces;		// Dynamic Array of command interfaces
	Vector jausInformationInterfaces;	// Dynamic Array of information interfaces
}JausPayloadInterfaceStruct;
typedef JausPayloadInterfaceStruct *JausPayloadInterface;

typedef struct
{
	char* commandIdentifier;	// null-terminated string
	JausByte typeCode;				// per TYPE CODE table
	JausByte units;					// per UNITS table
	JausByte blockingFlag;			// 0 for blocking, 1 for non-blocking
	JausTypeCode minValue;					// minimum acceptable value
	JausTypeCode defaultValue;				// default value
	JausTypeCode maxValue;					// maximum acceptable value
	JausUnsignedShort enumerationLength; // length = 0 means no enumeration field; includes NULL character
	char* enumeration;				// enumeration content, comma delimited, NULL terminated
	JausByte hmiRecommendation;		// per HMI table
	JausUnsignedShort hmiRecommendedPositionXPixels;	
	JausUnsignedShort hmiRecommendedPositionYPixels;
	JausUnsignedShort hmiRecommendedPositionWidthPixels;
	JausUnsignedShort hmiRecommendedPositionHeightPixels;
	JausTypeCode currentValue;	// extra field to store the current data value
}JausCommandInterfaceStruct;
typedef JausCommandInterfaceStruct *JausCommandInterface;

typedef struct
{
	char* informationIdentifier;	// null-terminated string
	JausByte commandInterfaceAssociation; // index number of the assoc. command interface, 0 if none
	JausByte typeCode;				// per TYPE CODE table
	JausByte units;					// per UNITS table
	JausTypeCode minValue;					// minimum acceptable value
	JausTypeCode defaultValue;				// default value
	JausTypeCode maxValue;					// maximum acceptable value
	JausUnsignedShort enumerationLength; // length = 0 means no enumeration field; includes NULL character
	char* enumeration;				// enumeration content, comma delimited, NULL terminated
	JausByte hmiRecommendation;		// per HMI table
	JausUnsignedShort hmiRecommendedPositionXPixels;	
	JausUnsignedShort hmiRecommendedPositionYPixels;
	JausUnsignedShort hmiRecommendedPositionWidthPixels;
	JausUnsignedShort hmiRecommendedPositionHeightPixels;
	JausTypeCode currentValue;	// extra field to store the current data value
}JausInformationInterfaceStruct;
typedef JausInformationInterfaceStruct *JausInformationInterface;

// container to support multiple payload data element messages
typedef struct
{
	JausPayloadInterface payloadInterface;
	//JausByte numberInformationInterfaces;	
	Vector jausPayloadDataElements;	// Dynamic Array of data elements
}JausPayloadDataElementsStruct;
typedef JausPayloadDataElementsStruct *JausPayloadDataElements;

// container to provide a specific payload data element
typedef struct
{
	char* dataElementIdentifier;	// null-terminated string
	JausByte dataElementIndex;
	JausTypeCode Value;
}JausPayloadDataElementStruct;
typedef JausPayloadDataElementStruct *JausPayloadDataElement;


// Command Interface Constructor
JausCommandInterface jausCommandInterfaceCreate(void);

// Information Interface Constructor
JausInformationInterface jausInformationInterfaceCreate(void);

// Command Interface Destructor
void jausCommandInterfaceDestroy(JausCommandInterface commandInterface);

// Information Interface Destructor
void jausInformationInterfaceDestroy(JausInformationInterface informationInterface);

// Interface Retrievers
JausCommandInterface jausCommandInterfaceRetrieve(JausPayloadInterface payloadInterface, char* identifier);

JausInformationInterface jausInformationInterfaceRetrieve(JausPayloadInterface payloadInterface, char* identifier);

// ************************************************************************************************************************************
//			Report PayloadInterface End User Functions
// ************************************************************************************************************************************

// Payload Interface Constructor
JausPayloadInterface jausPayloadInterfaceCreate(void);

// Payload Interface Destructor
void jausPayloadInterfaceDestroy(JausPayloadInterface payloadInterface);

// Interface Adders
JausCommandInterface jausAddNewCommandInterface(JausPayloadInterface payloadInterface, char* identifier, JausByte typeCode);
JausInformationInterface jausAddNewInformationInterface(JausPayloadInterface payloadInterface, char* identifier, JausByte typeCode);

// Report Payload Interface Message Support Functions

// NOTE: this function assumes end user is starting their index at 1, iaw the numbering scheme in the JAUS OPC ICD
char* jausGetCommandInterfaceIdentifierByIndex(JausPayloadInterface payloadInterface, int index, int* successFlag);

char* jausGetInformationInterfaceIdentifierByIndex(JausPayloadInterface payloadInterface, int index, int* successFlag);

JausByte jausGetCommandInterfaceTypeCode(JausPayloadInterface payloadInterface, char* identifier, int* successFlag);

JausByte jausGetInformationInterfaceTypeCode(JausPayloadInterface payloadInterface, char* identifier, int* successFlag);

JausBoolean jausSetCommandInterfaceUnits(JausPayloadInterface payloadInterface, char* identifier, JausByte units);

JausByte jausGetCommandInterfaceUnits(JausPayloadInterface payloadInterface, char* identifier, int* successFlag);

JausBoolean jausSetCommandInterfaceBlockingFlag(JausPayloadInterface payloadInterface, char* identifier);

JausBoolean jausClearCommandInterfaceBlockingFlag(JausPayloadInterface payloadInterface, char* identifier);

JausBoolean jausGetCommandInterfaceBlockingFlag(JausPayloadInterface payloadInterface, char* identifier, int* successFlag);

JausBoolean jausSetCommandInterfaceMinMax(JausPayloadInterface payloadInterface, char* identifier, JausTypeCode minValue, JausTypeCode maxValue);

JausTypeCode jausGetCommandInterfaceMin(JausPayloadInterface payloadInterface, char* identifier, int* successFlag);

JausTypeCode jausGetCommandInterfaceMax(JausPayloadInterface payloadInterface, char* identifier, int* successFlag);

JausBoolean jausSetCommandInterfaceDefault(JausPayloadInterface payloadInterface, char* identifier, JausTypeCode defaultValue);

JausTypeCode jausGetCommandInterfaceDefault(JausPayloadInterface payloadInterface, char* identifier, int* successFlag);

JausBoolean jausSetCommandInterfaceEnumeration(JausPayloadInterface payloadInterface, char* identifier, char* enumeration);

char* jausGetCommandInterfaceEnumeration(JausPayloadInterface payloadInterface, char* identifier, int* successFlag);

JausUnsignedShort jausGetCommandInterfaceEnumerationLength(JausPayloadInterface payloadInterface, char* identifier, int* successFlag);

JausBoolean jausSetCommandInterfaceHmiRecommendation(JausPayloadInterface payloadInterface, char* identifier, JausByte hmiRecommendation);

JausByte jausGetCommandInterfaceHmiRecommendation(JausPayloadInterface payloadInterface, char* identifier, int* successFlag);

// NOTE: recommended HMI positioning must be set as a group
JausBoolean jausSetCommandInterfaceHmiParameters(JausPayloadInterface payloadInterface, char* identifier, JausUnsignedShort xPixels, JausUnsignedShort yPixels, JausUnsignedShort widthPixels, JausUnsignedShort heightPixels);

JausUnsignedShort jausGetCommandInterfaceHmiXPositionPixels(JausPayloadInterface payloadInterface, char* identifier, int* successFlag);

JausUnsignedShort jausGetCommandInterfaceHmiYPositionPixels(JausPayloadInterface payloadInterface, char* identifier, int* successFlag);

JausUnsignedShort jausGetCommandInterfaceHmiWidthPixels(JausPayloadInterface payloadInterface, char* identifier, int* successFlag);

JausUnsignedShort jausGetCommandInterfaceHmiHeightPixels(JausPayloadInterface payloadInterface, char* identifier, int* successFlag);

JausBoolean jausSetInformationInterfaceUnits(JausPayloadInterface payloadInterface, char* identifier, JausByte units);

JausByte jausGetInformationInterfaceUnits(JausPayloadInterface payloadInterface, char* identifier, int* successFlag);

JausBoolean jausSetInformationInterfaceCommandInterfaceAssoc(JausPayloadInterface payloadInterface, char* identifier, JausByte commandInterfaceAssociation);

JausByte jausGetInformationInterfaceCommandInterfaceAssoc(JausPayloadInterface payloadInterface, char* identifier, int* successFlag);

JausBoolean jausSetInformationInterfaceMinMax(JausPayloadInterface payloadInterface, char* identifier, JausTypeCode minValue, JausTypeCode maxValue);

JausTypeCode jausGetInformationInterfaceMin(JausPayloadInterface payloadInterface, char* identifier, int* successFlag);

JausTypeCode jausGetInformationInterfaceMax(JausPayloadInterface payloadInterface, char* identifier, int* successFlag);

JausBoolean jausSetInformationInterfaceDefault(JausPayloadInterface payloadInterface, char* identifier, JausTypeCode defaultValue);

JausTypeCode jausGetInformationInterfaceDefault(JausPayloadInterface payloadInterface, char* identifier, int* successFlag);

JausBoolean jausSetInformationInterfaceEnumeration(JausPayloadInterface payloadInterface, char* identifier, char* enumeration);

char* jausGetInformationInterfaceEnumeration(JausPayloadInterface payloadInterface, char* identifier, int* successFlag);

JausUnsignedShort jausGetInformationInterfaceEnumerationLength(JausPayloadInterface payloadInterface, char* identifier, int* successFlag);

JausBoolean jausSetInformationInterfaceHmiRecommendation(JausPayloadInterface payloadInterface, char* identifier, JausByte hmiRecommendation);

JausByte jausGetInformationInterfaceHmiRecommendation(JausPayloadInterface payloadInterface, char* identifier, int* successFlag);

// NOTE: recommended HMI positioning must be set as a group
JausBoolean jausSetInformationInterfaceHmiParameters(JausPayloadInterface payloadInterface, char* identifier, JausUnsignedShort xPixels, JausUnsignedShort yPixels, JausUnsignedShort widthPixels, JausUnsignedShort heightPixels);

JausUnsignedShort jausGetInformationInterfaceHmiXPositionPixels(JausPayloadInterface payloadInterface, char* identifier, int* successFlag);

JausUnsignedShort jausGetInformationInterfaceHmiYPositionPixels(JausPayloadInterface payloadInterface, char* identifier, int* successFlag);

JausUnsignedShort jausGetInformationInterfaceHmiWidthPixels(JausPayloadInterface payloadInterface, char* identifier, int* successFlag);

JausUnsignedShort jausGetInformationInterfaceHmiHeightPixels(JausPayloadInterface payloadInterface, char* identifier, int* successFlag);

// decodes the Type Code value and returns the number of bytes required 
int jausMinMaxDefaultSizeBytes(JausByte typeCodeEnum);
int jausCommandValueSizeBytes(JausCommandInterface commandInterface);
int jausInformationValueSizeBytes(JausInformationInterface informationInterface);

// determines how to pack fields that have a JausTypeCode data type
int jausMinMaxDefaultToBuffer(JausTypeCode field, unsigned char* buffer, unsigned int bufferSizeBytes, JausByte typeCodeEnum);
int jausInformationValueToBuffer(JausInformationInterface informationInterface, unsigned char* buffer, unsigned int bufferSizeBytes);
int jausCommandValueToBuffer(JausCommandInterface commandInterface, unsigned char* buffer, unsigned int bufferSizeBytes);

// determines how to unpack fields that have a JausTypeCode data type
JausBoolean jausMinMaxDefaultFromBuffer(JausTypeCode *field, unsigned char* buffer, unsigned int bufferSizeBytes, JausByte typeCodeEnum);
JausBoolean jausInformationValueFromBuffer(JausInformationInterface informationInterface, unsigned char* buffer, unsigned int bufferSizeBytes);
JausBoolean jausCommandValueFromBuffer(JausCommandInterface commandInterface, unsigned char* buffer, unsigned int bufferSizeBytes);



#endif
