// File Name: configurationChangedEventSetupMessage.h
//
// Written By: Danny Kent (jaus AT dannykent DOT com), Tom Galluzzo 
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines the attributes of a ConfigurationChangedEventSetupMessage

#ifndef CONFIGURATION_CHANGED_EVENT_SETUP_MESSAGE_H
#define CONFIGURATION_CHANGED_EVENT_SETUP_MESSAGE_H

#include "cimar/jaus.h"

#define JAUS_NOTIFICATION_ALWAYS		1
#define JAUS_NOTIFICATION_ON_BOUNDS		2
#define JAUS_NOTIFICATION_TERMINATE		3

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

	JausByte notificationType;
	
}ConfigurationChangedEventSetupMessageStruct;

typedef ConfigurationChangedEventSetupMessageStruct* ConfigurationChangedEventSetupMessage;

ConfigurationChangedEventSetupMessage configurationChangedEventSetupMessageCreate(void);
void configurationChangedEventSetupMessageDestroy(ConfigurationChangedEventSetupMessage);

JausBoolean configurationChangedEventSetupMessageFromBuffer(ConfigurationChangedEventSetupMessage message, unsigned char* buffer, unsigned int bufferSizeBytes);
JausBoolean configurationChangedEventSetupMessageToBuffer(ConfigurationChangedEventSetupMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);
JausBoolean configurationChangedEventSetupMessageToUdpBuffer(ConfigurationChangedEventSetupMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);

ConfigurationChangedEventSetupMessage configurationChangedEventSetupMessageFromJausMessage(JausMessage jausMessage);
JausMessage configurationChangedEventSetupMessageToJausMessage(ConfigurationChangedEventSetupMessage message);

unsigned int configurationChangedEventSetupMessageUdpSize(ConfigurationChangedEventSetupMessage message);
unsigned int configurationChangedEventSetupMessageSize(ConfigurationChangedEventSetupMessage message);


#endif // CONFIGURATION_CHANGED_EVENT_SETUP_MESSAGE_H
