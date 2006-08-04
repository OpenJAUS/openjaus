// File Name: queryTimeMessage.h
//
// Written By: Danny Kent (jaus AT dannykent DOT com), Tom Galluzzo 
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines the attributes of a queryTimeMessage

#ifndef QUERY_TIME_MESSAGE_H
#define QUERY_TIME_MESSAGE_H

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
	JausBytePresenceVector presenceVector;
	
}QueryTimeMessageStruct;

typedef QueryTimeMessageStruct* QueryTimeMessage;

QueryTimeMessage queryTimeMessageCreate(void);
void queryTimeMessageDestroy(QueryTimeMessage);

JausBoolean queryTimeMessageFromBuffer(QueryTimeMessage message, unsigned char* buffer, unsigned int bufferSizeBytes);
JausBoolean queryTimeMessageToBuffer(QueryTimeMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);
JausBoolean queryTimeMessageToUdpBuffer(QueryTimeMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);

QueryTimeMessage queryTimeMessageFromJausMessage(JausMessage jausMessage);
JausMessage queryTimeMessageToJausMessage(QueryTimeMessage message);

unsigned int queryTimeMessageUdpSize(QueryTimeMessage message);
unsigned int queryTimeMessageSize(QueryTimeMessage message);


#endif // QUERY_TIME_MESSAGE_H
