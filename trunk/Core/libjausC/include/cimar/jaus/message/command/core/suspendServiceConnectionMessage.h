// File Name: suspendServiceConnectionMessage.h
//
// Written By: Danny Kent (jaus AT dannykent DOT com), Tom Galluzzo 
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines the attributes of a SuspendServiceConnectionMessage

#ifndef SUSPEND_SERVICE_CONNECTION_MESSAGE_H
#define SUSPEND_SERVICE_CONNECTION_MESSAGE_H

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

	JausUnsignedShort serviceConnectionCommandCode;
	JausByte instanceId;
	
}SuspendServiceConnectionMessageStruct;

typedef SuspendServiceConnectionMessageStruct* SuspendServiceConnectionMessage;

SuspendServiceConnectionMessage suspendServiceConnectionMessageCreate(void);
void suspendServiceConnectionMessageDestroy(SuspendServiceConnectionMessage);

JausBoolean suspendServiceConnectionMessageFromBuffer(SuspendServiceConnectionMessage message, unsigned char* buffer, unsigned int bufferSizeBytes);
JausBoolean suspendServiceConnectionMessageToBuffer(SuspendServiceConnectionMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);
JausBoolean suspendServiceConnectionMessageToUdpBuffer(SuspendServiceConnectionMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);

SuspendServiceConnectionMessage suspendServiceConnectionMessageFromJausMessage(JausMessage jausMessage);
JausMessage suspendServiceConnectionMessageToJausMessage(SuspendServiceConnectionMessage message);

unsigned int suspendServiceConnectionMessageUdpSize(SuspendServiceConnectionMessage message);
unsigned int suspendServiceConnectionMessageSize(SuspendServiceConnectionMessage message);


#endif // SUSPEND_SERVICE_CONNECTION_MESSAGE_H
