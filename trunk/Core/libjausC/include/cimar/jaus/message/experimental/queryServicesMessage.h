// File Name: queryServicesMessage.h
//
// Written By: Bob Touchton, inspired by Danny Kent
//
// Version: 3.2
//
// Date: 08/04/06
//
// This file defines the attributes of a QueryServicesMessage

#ifndef QUERY_SERVICES_MESSAGE_H
#define QUERY_SERVICES_MESSAGE_H

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
	
}QueryServicesMessageStruct;

typedef QueryServicesMessageStruct* QueryServicesMessage;

QueryServicesMessage queryServicesMessageCreate(void);
void queryServicesMessageDestroy(QueryServicesMessage);

JausBoolean queryServicesMessageFromBuffer(QueryServicesMessage message, unsigned char* buffer, unsigned int bufferSizeBytes);
JausBoolean queryServicesMessageToBuffer(QueryServicesMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);
JausBoolean queryServicesMessageToUdpBuffer(QueryServicesMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);

QueryServicesMessage queryServicesMessageFromJausMessage(JausMessage jausMessage);
JausMessage queryServicesMessageToJausMessage(QueryServicesMessage message);

unsigned int queryServicesMessageUdpSize(QueryServicesMessage message);
unsigned int queryServicesMessageSize(QueryServicesMessage message);


#endif // QUERY_SERVICES_MESSAGE_H
