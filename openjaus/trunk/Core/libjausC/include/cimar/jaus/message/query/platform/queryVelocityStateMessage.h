// File Name: queryVelocityStateMessage.h
//
// Written By: Danny Kent (jaus AT dannykent DOT com), Tom Galluzzo 
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines the attributes of a QueryVelocityStateMessage

#ifndef QUERY_VELOCITY_STATE_MESSAGE_H
#define QUERY_VELOCITY_STATE_MESSAGE_H

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

	JausShortPresenceVector presenceVector;
	
}QueryVelocityStateMessageStruct;

typedef QueryVelocityStateMessageStruct* QueryVelocityStateMessage;

QueryVelocityStateMessage queryVelocityStateMessageCreate(void);
void queryVelocityStateMessageDestroy(QueryVelocityStateMessage);

JausBoolean queryVelocityStateMessageFromBuffer(QueryVelocityStateMessage message, unsigned char* buffer, unsigned int bufferSizeBytes);
JausBoolean queryVelocityStateMessageToBuffer(QueryVelocityStateMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);
JausBoolean queryVelocityStateMessageToUdpBuffer(QueryVelocityStateMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);

QueryVelocityStateMessage queryVelocityStateMessageFromJausMessage(JausMessage jausMessage);
JausMessage queryVelocityStateMessageToJausMessage(QueryVelocityStateMessage message);

unsigned int queryVelocityStateMessageUdpSize(QueryVelocityStateMessage message);
unsigned int queryVelocityStateMessageSize(QueryVelocityStateMessage message);


#endif // QUERY_VELOCITY_STATE_MESSAGE_H
