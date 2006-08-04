// File Name: cancelEventMessage.h
//
// Written By: Danny Kent (jaus AT dannykent DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines the attributes of a CancelEventMessage

#ifndef CANCEL_EVENT_MESSAGE_H
#define CANCEL_EVENT_MESSAGE_H

#include <cimar/jaus.h>

#define JAUS_CANCEL_EVENT	0xF00B

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
	JausUnsignedShort messageCode;
	JausByte eventId;
	
}CancelEventMessageStruct;

typedef CancelEventMessageStruct* CancelEventMessage;

CancelEventMessage cancelEventMessageCreate(void);
void cancelEventMessageDestroy(CancelEventMessage);

JausBoolean cancelEventMessageFromBuffer(CancelEventMessage message, unsigned char* buffer, unsigned int bufferSizeBytes);
JausBoolean cancelEventMessageToBuffer(CancelEventMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);
JausBoolean cancelEventMessageToUdpBuffer(CancelEventMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);

CancelEventMessage cancelEventMessageFromJausMessage(JausMessage jausMessage);
JausMessage cancelEventMessageToJausMessage(CancelEventMessage message);

unsigned int cancelEventMessageUdpSize(CancelEventMessage message);
unsigned int cancelEventMessageSize(CancelEventMessage message);


#endif // CANCEL_EVENT_MESSAGE_H
