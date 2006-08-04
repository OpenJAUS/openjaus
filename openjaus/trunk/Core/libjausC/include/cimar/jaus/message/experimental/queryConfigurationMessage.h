// File Name: queryConfigurationMessage.h
//
// Written By: Danny Kent (jaus AT dannykent DOT com), Tom Galluzzo 
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines the attributes of a QueryConfigurationMessage

#ifndef QUERY_CONFIGURATION_MESSAGE_H
#define QUERY_CONFIGURATION_MESSAGE_H

#include "cimar/jaus.h"

#define JAUS_SYSTEM_CONFIGURATION		1
#define JAUS_SUBSYSTEM_CONFIGURATION	2
#define JAUS_NODE_CONFIGURATION			3
#define JAUS_COMPONENT_CONFIGURATION	4
#define JAUS_INSTANCE_CONFIGURATION		5

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

	JausByte queryField;
	
}QueryConfigurationMessageStruct;

typedef QueryConfigurationMessageStruct* QueryConfigurationMessage;

QueryConfigurationMessage queryConfigurationMessageCreate(void);
void queryConfigurationMessageDestroy(QueryConfigurationMessage);

JausBoolean queryConfigurationMessageFromBuffer(QueryConfigurationMessage message, unsigned char* buffer, unsigned int bufferSizeBytes);
JausBoolean queryConfigurationMessageToBuffer(QueryConfigurationMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);
JausBoolean queryConfigurationMessageToUdpBuffer(QueryConfigurationMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);

QueryConfigurationMessage queryConfigurationMessageFromJausMessage(JausMessage jausMessage);
JausMessage queryConfigurationMessageToJausMessage(QueryConfigurationMessage message);

unsigned int queryConfigurationMessageUdpSize(QueryConfigurationMessage message);
unsigned int queryConfigurationMessageSize(QueryConfigurationMessage message);


#endif // QUERY_CONFIGURATION_MESSAGE_H
