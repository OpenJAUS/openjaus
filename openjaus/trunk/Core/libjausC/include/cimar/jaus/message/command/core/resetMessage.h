// File Name: resetMessage.h
//
// Written By: Danny Kent (jaus AT dannykent DOT com), Tom Galluzzo 
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines the attributes of a ResetMessage

#ifndef RESET_MESSAGE_H
#define RESET_MESSAGE_H

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
	
}ResetMessageStruct;

typedef ResetMessageStruct* ResetMessage;

ResetMessage resetMessageCreate(void);
void resetMessageDestroy(ResetMessage);

JausBoolean resetMessageFromBuffer(ResetMessage message, unsigned char* buffer, unsigned int bufferSizeBytes);
JausBoolean resetMessageToBuffer(ResetMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);
JausBoolean resetMessageToUdpBuffer(ResetMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);

ResetMessage resetMessageFromJausMessage(JausMessage jausMessage);
JausMessage resetMessageToJausMessage(ResetMessage message);

unsigned int resetMessageUdpSize(ResetMessage message);
unsigned int resetMessageSize(ResetMessage message);


#endif // RESET_MESSAGE_H
