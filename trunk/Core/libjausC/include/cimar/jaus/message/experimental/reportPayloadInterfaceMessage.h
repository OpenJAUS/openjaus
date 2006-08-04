// File Name: reportPayloadInterfaceMessage.h
//
// Written By: Bob Touchton
//
// Version: 3.2
//
// Date: 3/13/06
//
// This file defines the attributes of a ReportPayloadInterfaceMessage
// NOTE WELL: this message will also be used for general purpose information exchange

#ifndef REPORT_PAYLOAD_INTERFACE_MESSAGE_H
#define REPORT_PAYLOAD_INTERFACE_MESSAGE_H

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
	
}ReportPayloadInterfaceMessageStruct;

typedef ReportPayloadInterfaceMessageStruct* ReportPayloadInterfaceMessage;

ReportPayloadInterfaceMessage reportPayloadInterfaceMessageCreate(void);
void reportPayloadInterfaceMessageDestroy(ReportPayloadInterfaceMessage);

JausBoolean reportPayloadInterfaceMessageFromBuffer(ReportPayloadInterfaceMessage message, unsigned char* buffer, unsigned int bufferSizeBytes);
JausBoolean reportPayloadInterfaceMessageToBuffer(ReportPayloadInterfaceMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);
JausBoolean reportPayloadInterfaceMessageToUdpBuffer(ReportPayloadInterfaceMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);

ReportPayloadInterfaceMessage reportPayloadInterfaceMessageFromJausMessage(JausMessage jausMessage);
JausMessage reportPayloadInterfaceMessageToJausMessage(ReportPayloadInterfaceMessage message);

unsigned int reportPayloadInterfaceMessageUdpSize(ReportPayloadInterfaceMessage message);
unsigned int reportPayloadInterfaceMessageSize(ReportPayloadInterfaceMessage message);

#endif




