// File Name: terminateServiceConnectionMessage.h
//
// Written By: Danny Kent (jaus AT dannykent DOT com), Tom Galluzzo 
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines the attributes of a TerminateServiceConnectionMessage

#ifndef TERMINATE_SERVICE_CONNECTION_MESSAGE_H
#define TERMINATE_SERVICE_CONNECTION_MESSAGE_H

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
	
}TerminateServiceConnectionMessageStruct;

typedef TerminateServiceConnectionMessageStruct* TerminateServiceConnectionMessage;

TerminateServiceConnectionMessage terminateServiceConnectionMessageCreate(void);
void terminateServiceConnectionMessageDestroy(TerminateServiceConnectionMessage);

JausBoolean terminateServiceConnectionMessageFromBuffer(TerminateServiceConnectionMessage message, unsigned char* buffer, unsigned int bufferSizeBytes);
JausBoolean terminateServiceConnectionMessageToBuffer(TerminateServiceConnectionMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);
JausBoolean terminateServiceConnectionMessageToUdpBuffer(TerminateServiceConnectionMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);

TerminateServiceConnectionMessage terminateServiceConnectionMessageFromJausMessage(JausMessage jausMessage);
JausMessage terminateServiceConnectionMessageToJausMessage(TerminateServiceConnectionMessage message);

unsigned int terminateServiceConnectionMessageUdpSize(TerminateServiceConnectionMessage message);
unsigned int terminateServiceConnectionMessageSize(TerminateServiceConnectionMessage message);


#endif // TERMINATE_SERVICE_CONNECTION_MESSAGE_H
