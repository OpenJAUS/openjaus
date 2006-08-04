// File Name: queryPayloadInterfaceMessage.h
//
// Written By: Bob Touchton
//
// Version: 3.2
//
// Date: 3/20/06
//
// This file defines the attributes of a QueryPayloadInterfaceMessage

#ifndef QUERY_PAYLOAD_INTERFACE_MESSAGE_H
#define QUERY_PAYLOAD_INTERFACE_MESSAGE_H

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

	// No Message Fields
	
}QueryPayloadInterfaceMessageStruct;

typedef QueryPayloadInterfaceMessageStruct* QueryPayloadInterfaceMessage;

QueryPayloadInterfaceMessage queryPayloadInterfaceMessageCreate(void);
void queryPayloadInterfaceMessageDestroy(QueryPayloadInterfaceMessage);

JausBoolean queryPayloadInterfaceMessageFromBuffer(QueryPayloadInterfaceMessage message, unsigned char* buffer, unsigned int bufferSizeBytes);
JausBoolean queryPayloadInterfaceMessageToBuffer(QueryPayloadInterfaceMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);
JausBoolean queryPayloadInterfaceMessageToUdpBuffer(QueryPayloadInterfaceMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);

QueryPayloadInterfaceMessage queryPayloadInterfaceMessageFromJausMessage(JausMessage jausMessage);
JausMessage queryPayloadInterfaceMessageToJausMessage(QueryPayloadInterfaceMessage message);

unsigned int queryPayloadInterfaceMessageUdpSize(QueryPayloadInterfaceMessage message);
unsigned int queryPayloadInterfaceMessageSize(QueryPayloadInterfaceMessage message);


#endif // QUERY_PAYLOAD_INTERFACE_MESSAGE_H
