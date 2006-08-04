// File Name: reportIdentificationMessage.h
//
// Written By: Danny Kent (jaus AT dannykent DOT com), Tom Galluzzo 
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines the attributes of a ReportIdentificationMessage

#ifndef REPORT_IDENTIFICATION_MESSAGE_H
#define REPORT_IDENTIFICATION_MESSAGE_H

#include "cimar/jaus.h"

#ifndef JAUS_IDENTIFICATION_TYPE
#define JAUS_IDENTIFICATION_TYPE
#define JAUS_QUERY_FIELD_RESERVED			0
#define JAUS_QUERY_FIELD_SYSTEM_IDENTITY	1
#define JAUS_QUERY_FIELD_SS_IDENTITY		2
#define JAUS_QUERY_FIELD_NODE_IDENTITY		3
#define JAUS_QUERY_FIELD_COMPONENT_IDENTITY	4
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

	JausByte queryType;
	JausByte authority;
	JausUnsignedShort type;
	char identification[80];
	
}ReportIdentificationMessageStruct;

typedef ReportIdentificationMessageStruct* ReportIdentificationMessage;

ReportIdentificationMessage reportIdentificationMessageCreate(void);
void reportIdentificationMessageDestroy(ReportIdentificationMessage);

JausBoolean reportIdentificationMessageFromBuffer(ReportIdentificationMessage message, unsigned char* buffer, unsigned int bufferSizeBytes);
JausBoolean reportIdentificationMessageToBuffer(ReportIdentificationMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);
JausBoolean reportIdentificationMessageToUdpBuffer(ReportIdentificationMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);

ReportIdentificationMessage reportIdentificationMessageFromJausMessage(JausMessage jausMessage);
JausMessage reportIdentificationMessageToJausMessage(ReportIdentificationMessage message);

unsigned int reportIdentificationMessageUdpSize(ReportIdentificationMessage message);
unsigned int reportIdentificationMessageSize(ReportIdentificationMessage message);


#endif // REPORT_IDENTIFICATION_MESSAGE_H
