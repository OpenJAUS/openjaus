// File Name: reportServicesMessage.h
//
// Written By: Bob Touchton, inspired by Danny Kent
//
// Version: 3.2
//
// Date: 08/04/06
//
// This file defines the attributes of a ReportServicesMessage

#ifndef REPORT_SERVICES_MESSAGE_H
#define REPORT_SERVICES_MESSAGE_H

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
	Vector jausServices;
	
}ReportServicesMessageStruct;

typedef ReportServicesMessageStruct* ReportServicesMessage;

ReportServicesMessage reportServicesMessageCreate(void);
void reportServicesMessageDestroy(ReportServicesMessage);

JausBoolean reportServicesMessageFromBuffer(ReportServicesMessage message, unsigned char* buffer, unsigned int bufferSizeBytes);
JausBoolean reportServicesMessageToBuffer(ReportServicesMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);
JausBoolean reportServicesMessageToUdpBuffer(ReportServicesMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);

ReportServicesMessage reportServicesMessageFromJausMessage(JausMessage jausMessage);
JausMessage reportServicesMessageToJausMessage(ReportServicesMessage message);

unsigned int reportServicesMessageUdpSize(ReportServicesMessage message);
unsigned int reportServicesMessageSize(ReportServicesMessage message);

#endif




