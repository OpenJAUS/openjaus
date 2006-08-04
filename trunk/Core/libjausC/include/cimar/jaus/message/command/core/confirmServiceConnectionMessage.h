// File Name: confirmServiceConnectionMessage.h
//
// Written By: Danny Kent (jaus AT dannykent DOT com), Tom Galluzzo 
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines the attributes of a ConfirmServiceConnectionMessage

#ifndef CONFIRM_SERVICE_CONNECTION_MESSAGE_H
#define CONFIRM_SERVICE_CONNECTION_MESSAGE_H

#include "cimar/jaus.h"

#define JAUS_SC_SUCCESSFUL				0
#define JAUS_SC_NODE_NOT_CAPABLE		1
#define JAUS_SC_COMPONENT_NOT_CAPABLE	2
#define JAUS_SC_INSUFFICIENT_AUTHORITY	3
#define JAUS_SC_CONNECTION_REFUSED		4
#define JAUS_SC_INVALID_PARAMETER		5
#define JAUS_SC_COMMAND_NOT_SUPPORTED	6

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
	JausUnsignedShort confirmedPeriodicUpdateRateHertz;
	JausByte responseCode;
	
}ConfirmServiceConnectionMessageStruct;

typedef ConfirmServiceConnectionMessageStruct* ConfirmServiceConnectionMessage;

ConfirmServiceConnectionMessage confirmServiceConnectionMessageCreate(void);
void confirmServiceConnectionMessageDestroy(ConfirmServiceConnectionMessage);

JausBoolean confirmServiceConnectionMessageFromBuffer(ConfirmServiceConnectionMessage message, unsigned char* buffer, unsigned int bufferSizeBytes);
JausBoolean confirmServiceConnectionMessageToBuffer(ConfirmServiceConnectionMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);
JausBoolean confirmServiceConnectionMessageToUdpBuffer(ConfirmServiceConnectionMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);

ConfirmServiceConnectionMessage confirmServiceConnectionMessageFromJausMessage(JausMessage jausMessage);
JausMessage confirmServiceConnectionMessageToJausMessage(ConfirmServiceConnectionMessage message);

unsigned int confirmServiceConnectionMessageUdpSize(ConfirmServiceConnectionMessage message);
unsigned int confirmServiceConnectionMessageSize(ConfirmServiceConnectionMessage message);


#endif // CONFIRM_SERVICE_CONNECTION_MESSAGE_H
