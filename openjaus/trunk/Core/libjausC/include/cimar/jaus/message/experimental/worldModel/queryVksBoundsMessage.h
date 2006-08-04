// File Name: queryVksBoundsMessage.h
//
// Written By: Danny Kent (jaus AT dannykent DOT com) 
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines the attributes of a QueryVksBoundsMessage

#ifndef QUERY_VKS_BOUNDS_MESSAGE_H
#define QUERY_VKS_BOUNDS_MESSAGE_H

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
	JausByte requestId;
	JausUnsignedShort featureClassId;
	
}QueryVksBoundsMessageStruct;

typedef QueryVksBoundsMessageStruct* QueryVksBoundsMessage;

QueryVksBoundsMessage queryVksBoundsMessageCreate(void);
void queryVksBoundsMessageDestroy(QueryVksBoundsMessage);

JausBoolean queryVksBoundsMessageFromBuffer(QueryVksBoundsMessage message, unsigned char* buffer, unsigned int bufferSizeBytes);
JausBoolean queryVksBoundsMessageToBuffer(QueryVksBoundsMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);
JausBoolean queryVksBoundsMessageToUdpBuffer(QueryVksBoundsMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);

QueryVksBoundsMessage queryVksBoundsMessageFromJausMessage(JausMessage jausMessage);
JausMessage queryVksBoundsMessageToJausMessage(QueryVksBoundsMessage message);

unsigned int queryVksBoundsMessageUdpSize(QueryVksBoundsMessage message);
unsigned int queryVksBoundsMessageSize(QueryVksBoundsMessage message);


#endif // QUERY_VKS_BOUNDS_MESSAGE_H
