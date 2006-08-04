// File Name: reportVksObjectsCreationMessage.h
//
// Written By: Danny Kent (jaus AT dannykent DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines the attributes of a ReportVksObjectsCreationMessage

#ifndef REPORT_VKS_OBJECTS_CREATION_MESSAGE_H
#define REPORT_VKS_OBJECTS_CREATION_MESSAGE_H

#include "cimar/jaus.h"

typedef struct
{
	// Include all parameters from a JausMessage structure:
	// Header Properties
	union
	{
		struct
		{
			// Properties by bit fields
			#ifdef JAUS_BIG_ENDIAN
				JausUnsignedShort reserved:2;
				JausUnsignedShort version:6;
				JausUnsignedShort expFlag:1;
				JausUnsignedShort scFlag:1;
				JausUnsignedShort ackNak:2;
				JausUnsignedShort priority:4; 
			#elif JAUS_LITTLE_ENDIAN
				JausUnsignedShort priority:4; 
				JausUnsignedShort ackNak:2;
				JausUnsignedShort scFlag:1; 
				JausUnsignedShort expFlag:1;
				JausUnsignedShort version:6; 
				JausUnsignedShort reserved:2;
			#else
				#error "Please define system endianess (see jaus.h)"
			#endif
		};
		JausUnsignedShort properties;		
	};

	JausUnsignedShort commandCode; 

	JausAddress destination;

	JausAddress source;

	union
	{
		struct
		{
			JausUnsignedInteger dataSize;
			JausUnsignedInteger dataFlag;
		};
		JausUnsignedLong dataControl;		
	};
	
	JausUnsignedShort sequenceNumber;

	// MESSAGE DATA MEMBERS GO HERE
	JausByte requestId;					// 1: The request id sent by the requesting service
	JausUnsignedShort objectCount;		// 2: Total number of objects reported
	JausUnsignedInteger *objectIds;		// 3: unique id for object created, 0x0000000 is reserved for an error
	
}ReportVksObjectsCreationMessageStruct;

typedef ReportVksObjectsCreationMessageStruct* ReportVksObjectsCreationMessage;

ReportVksObjectsCreationMessage reportVksObjectsCreationMessageCreate(void);
void reportVksObjectsCreationMessageDestroy(ReportVksObjectsCreationMessage);

JausBoolean reportVksObjectsCreationMessageFromBuffer(ReportVksObjectsCreationMessage message, unsigned char* buffer, unsigned int bufferSizeBytes);
JausBoolean reportVksObjectsCreationMessageToBuffer(ReportVksObjectsCreationMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);
JausBoolean reportVksObjectsCreationMessageToUdpBuffer(ReportVksObjectsCreationMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);

ReportVksObjectsCreationMessage reportVksObjectsCreationMessageFromJausMessage(JausMessage jausMessage);
JausMessage reportVksObjectsCreationMessageToJausMessage(ReportVksObjectsCreationMessage message);

unsigned int reportVksObjectsCreationMessageUdpSize(ReportVksObjectsCreationMessage message);
unsigned int reportVksObjectsCreationMessageSize(ReportVksObjectsCreationMessage message);


#endif // REPORT_VKS_OBJECTS_CREATION_MESSAGE_H
