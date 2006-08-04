// File Name: reportPayloadDataElementMessage.h
//
// Written By: Bob Touchton
//
// Version: 3.2
//
// Date: 3/20/06
//
// This file defines the attributes of a reportPayloadDataElementMessage
// NOTE WELL: this message will also be used for general purpose information exchange

#ifndef REPORT_PAYLOAD_DATA_ELEMENT_MESSAGE_H
#define REPORT_PAYLOAD_DATA_ELEMENT_MESSAGE_H

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
	//message-specific fields
	JausPayloadInterface jausPayloadInterface;
	int numberInterfaces;
	int* indexes;
	
}ReportPayloadDataElementMessageStruct;

typedef ReportPayloadDataElementMessageStruct* ReportPayloadDataElementMessage;

ReportPayloadDataElementMessage reportPayloadDataElementMessageCreate(void);
void reportPayloadDataElementMessageDestroy(ReportPayloadDataElementMessage);

JausBoolean reportPayloadDataElementMessageFromBuffer(ReportPayloadDataElementMessage message, unsigned char* buffer, unsigned int bufferSizeBytes);
JausBoolean reportPayloadDataElementMessageToBuffer(ReportPayloadDataElementMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);
JausBoolean reportPayloadDataElementMessageToUdpBuffer(ReportPayloadDataElementMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);

ReportPayloadDataElementMessage reportPayloadDataElementMessageFromJausMessage(JausMessage jausMessage);
JausMessage reportPayloadDataElementMessageToJausMessage(ReportPayloadDataElementMessage message);

unsigned int reportPayloadDataElementMessageUdpSize(ReportPayloadDataElementMessage message);
unsigned int reportPayloadDataElementMessageSize(ReportPayloadDataElementMessage message);

#endif




