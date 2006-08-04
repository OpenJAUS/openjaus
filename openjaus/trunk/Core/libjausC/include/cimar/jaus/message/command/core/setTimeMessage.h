// File Name: setTimeMessage.h
//
// Written By: Danny Kent (jaus AT dannykent DOT com), Tom Galluzzo 
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines the attributes of a SetTimeMessage

#ifndef SET_TIME_MESSAGE_H
#define SET_TIME_MESSAGE_H

#include "cimar/jaus.h"

#ifndef JAUS_TIME_PV
#define JAUS_TIME_PV
#define JAUS_TIME_PV_TIME_STAMP_BIT 0
#define JAUS_TIME_PV_DATE_STAMP_BIT 1
#endif

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

	JausBytePresenceVector presenceVector;
	JausUnsignedInteger timeStamp;
	JausUnsignedShort dateStamp;
	
}SetTimeMessageStruct;

typedef SetTimeMessageStruct* SetTimeMessage;

SetTimeMessage setTimeMessageCreate(void);
void setTimeMessageDestroy(SetTimeMessage);

JausBoolean setTimeMessageFromBuffer(SetTimeMessage message, unsigned char* buffer, unsigned int bufferSizeBytes);
JausBoolean setTimeMessageToBuffer(SetTimeMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);
JausBoolean setTimeMessageToUdpBuffer(SetTimeMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);

SetTimeMessage setTimeMessageFromJausMessage(JausMessage jausMessage);
JausMessage setTimeMessageToJausMessage(SetTimeMessage message);

unsigned int setTimeMessageUdpSize(SetTimeMessage message);
unsigned int setTimeMessageSize(SetTimeMessage message);


#endif // SET_TIME_MESSAGE_H
