// File Name: confirmComponentControlMessage.h
//
// Written By: Danny Kent (jaus AT dannykent DOT com), Tom Galluzzo 
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines the attributes of a ConfirmComponentControlMessage

#ifndef CONFIRM_COMPONENT_CONTROL_MESSAGE_H
#define CONFIRM_COMPONENT_CONTROL_MESSAGE_H

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

	JausByte responseCode;
	
}ConfirmComponentControlMessageStruct;

typedef ConfirmComponentControlMessageStruct* ConfirmComponentControlMessage;

ConfirmComponentControlMessage confirmComponentControlMessageCreate(void);
void confirmComponentControlMessageDestroy(ConfirmComponentControlMessage);

JausBoolean confirmComponentControlMessageFromBuffer(ConfirmComponentControlMessage message, unsigned char* buffer, unsigned int bufferSizeBytes);
JausBoolean confirmComponentControlMessageToBuffer(ConfirmComponentControlMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);
JausBoolean confirmComponentControlMessageToUdpBuffer(ConfirmComponentControlMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);

ConfirmComponentControlMessage confirmComponentControlMessageFromJausMessage(JausMessage jausMessage);
JausMessage confirmComponentControlMessageToJausMessage(ConfirmComponentControlMessage message);

unsigned int confirmComponentControlMessageUdpSize(ConfirmComponentControlMessage message);
unsigned int confirmComponentControlMessageSize(ConfirmComponentControlMessage message);


#endif // CONFIRM_COMPONENT_CONTROL_MESSAGE_H
