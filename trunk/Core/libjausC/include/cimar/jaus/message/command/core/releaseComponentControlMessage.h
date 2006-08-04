// File Name: releaseComponentControlMessage.h
//
// Written By: Danny Kent (jaus AT dannykent DOT com), Tom Galluzzo 
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines the attributes of a ReleaseComponentControlMessage

#ifndef RELEASE_COMPONENT_CONTROL_MESSAGE_H
#define RELEASE_COMPONENT_CONTROL_MESSAGE_H

#include "cimar/jaus.h"

#define JAUS_RESPONSE_CODE_CONTROL_ACCEPTED			0
#define JAUS_RESPONSE_CODE_CONTROL_NOT_SUPPORTED	1
#define JAUS_RESPONSE_CODE_CONTROL_NOT_ACCEPTED		2

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
	
}ReleaseComponentControlMessageStruct;

typedef ReleaseComponentControlMessageStruct* ReleaseComponentControlMessage;

ReleaseComponentControlMessage releaseComponentControlMessageCreate(void);
void releaseComponentControlMessageDestroy(ReleaseComponentControlMessage);

JausBoolean releaseComponentControlMessageFromBuffer(ReleaseComponentControlMessage message, unsigned char* buffer, unsigned int bufferSizeBytes);
JausBoolean releaseComponentControlMessageToBuffer(ReleaseComponentControlMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);
JausBoolean releaseComponentControlMessageToUdpBuffer(ReleaseComponentControlMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);

ReleaseComponentControlMessage releaseComponentControlMessageFromJausMessage(JausMessage jausMessage);
JausMessage releaseComponentControlMessageToJausMessage(ReleaseComponentControlMessage message);

unsigned int releaseComponentControlMessageUdpSize(ReleaseComponentControlMessage message);
unsigned int releaseComponentControlMessageSize(ReleaseComponentControlMessage message);


#endif // RELEASE_COMPONENT_CONTROL_MESSAGE_H
