// File Name: resumeMessage.h
//
// Written By: Danny Kent (jaus AT dannykent DOT com), Tom Galluzzo 
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines the attributes of a ResumeMessage

#ifndef RESUME_MESSAGE_H
#define RESUME_MESSAGE_H

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
	
}ResumeMessageStruct;

typedef ResumeMessageStruct* ResumeMessage;

ResumeMessage resumeMessageCreate(void);
void resumeMessageDestroy(ResumeMessage);

JausBoolean resumeMessageFromBuffer(ResumeMessage message, unsigned char* buffer, unsigned int bufferSizeBytes);
JausBoolean resumeMessageToBuffer(ResumeMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);
JausBoolean resumeMessageToUdpBuffer(ResumeMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);

ResumeMessage resumeMessageFromJausMessage(JausMessage jausMessage);
JausMessage resumeMessageToJausMessage(ResumeMessage message);

unsigned int resumeMessageUdpSize(ResumeMessage message);
unsigned int resumeMessageSize(ResumeMessage message);


#endif // RESUME_MESSAGE_H
