// File Name: reportVksObjectsMessage.h
//
// Written By: Danny Kent (jaus AT dannykent DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines the attributes of a ReportVksObjectsMessage

#ifndef REPORT_VKS_OBJECTS_MESSAGE_H
#define REPORT_VKS_OBJECTS_MESSAGE_H

#include <cimar.h>
#include "cimar/jaus.h"

#ifndef VKS_PV_REPORT
#define VKS_PV_REPORT
#define VKS_PV_REPORT_DATA_BIT	0
#endif

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
	JausBytePresenceVector presenceVector;
	JausByte requestId;
	JausUnsignedShort objectCount;
	Vector vectorObjects;
	
}ReportVksObjectsMessageStruct;

typedef ReportVksObjectsMessageStruct* ReportVksObjectsMessage;

ReportVksObjectsMessage reportVksObjectsMessageCreate(void);
void reportVksObjectsMessageDestroy(ReportVksObjectsMessage);

JausBoolean reportVksObjectsMessageFromBuffer(ReportVksObjectsMessage message, unsigned char* buffer, unsigned int bufferSizeBytes);
JausBoolean reportVksObjectsMessageToBuffer(ReportVksObjectsMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);
JausBoolean reportVksObjectsMessageToUdpBuffer(ReportVksObjectsMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);

ReportVksObjectsMessage reportVksObjectsMessageFromJausMessage(JausMessage jausMessage);
JausMessage reportVksObjectsMessageToJausMessage(ReportVksObjectsMessage message);

unsigned int reportVksObjectsMessageUdpSize(ReportVksObjectsMessage message);
unsigned int reportVksObjectsMessageSize(ReportVksObjectsMessage message);


#endif // REPORT_VKS_OBJECTS_MESSAGE_H
