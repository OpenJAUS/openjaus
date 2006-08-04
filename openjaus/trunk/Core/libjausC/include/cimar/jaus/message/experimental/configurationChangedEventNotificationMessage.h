// File Name: configurationChangedEventNotificationMessage.h
//
// Written By: Danny Kent (jaus AT dannykent DOT com), Tom Galluzzo 
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines the attributes of a ConfigurationChangedEventNotificationMessage

#ifndef CONFIGURATION_CHANGED_EVENT_NOTIFICATION_MESSAGE_H
#define CONFIGURATION_CHANGED_EVENT_NOTIFICATION_MESSAGE_H

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

	// No data for this message
	
}ConfigurationChangedEventNotificationMessageStruct;

typedef ConfigurationChangedEventNotificationMessageStruct* ConfigurationChangedEventNotificationMessage;

ConfigurationChangedEventNotificationMessage configurationChangedEventNotificationMessageCreate(void);
void configurationChangedEventNotificationMessageDestroy(ConfigurationChangedEventNotificationMessage);

JausBoolean configurationChangedEventNotificationMessageFromBuffer(ConfigurationChangedEventNotificationMessage message, unsigned char* buffer, unsigned int bufferSizeBytes);
JausBoolean configurationChangedEventNotificationMessageToBuffer(ConfigurationChangedEventNotificationMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);
JausBoolean configurationChangedEventNotificationMessageToUdpBuffer(ConfigurationChangedEventNotificationMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);

ConfigurationChangedEventNotificationMessage configurationChangedEventNotificationMessageFromJausMessage(JausMessage jausMessage);
JausMessage configurationChangedEventNotificationMessageToJausMessage(ConfigurationChangedEventNotificationMessage message);

unsigned int configurationChangedEventNotificationMessageUdpSize(ConfigurationChangedEventNotificationMessage message);
unsigned int configurationChangedEventNotificationMessageSize(ConfigurationChangedEventNotificationMessage message);


#endif // CONFIGURATION_CHANGED_EVENT_NOTIFICATION_MESSAGE_H
