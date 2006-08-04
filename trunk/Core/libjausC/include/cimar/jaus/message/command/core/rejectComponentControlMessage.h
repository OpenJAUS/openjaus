// File Name: rejectComponentControlMessage.h
//
// Written By: Danny Kent (jaus AT dannykent DOT com), Tom Galluzzo 
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines the attributes of a RejectComponentControlMessage

#ifndef REJECT_COMPONENT_CONTROL_MESSAGE_H
#define REJECT_COMPONENT_CONTROL_MESSAGE_H

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

	// No data associated with message
	
}RejectComponentControlMessageStruct;

typedef RejectComponentControlMessageStruct* RejectComponentControlMessage;

RejectComponentControlMessage rejectComponentControlMessageCreate(void);
void rejectComponentControlMessageDestroy(RejectComponentControlMessage);

JausBoolean rejectComponentControlMessageFromBuffer(RejectComponentControlMessage message, unsigned char* buffer, unsigned int bufferSizeBytes);
JausBoolean rejectComponentControlMessageToBuffer(RejectComponentControlMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);
JausBoolean rejectComponentControlMessageToUdpBuffer(RejectComponentControlMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);

RejectComponentControlMessage rejectComponentControlMessageFromJausMessage(JausMessage jausMessage);
JausMessage rejectComponentControlMessageToJausMessage(RejectComponentControlMessage message);

unsigned int rejectComponentControlMessageUdpSize(RejectComponentControlMessage message);
unsigned int rejectComponentControlMessageSize(RejectComponentControlMessage message);


#endif // REJECT_COMPONENT_CONTROL_MESSAGE_H
