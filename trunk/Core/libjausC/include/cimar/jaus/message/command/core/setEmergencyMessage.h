// File Name: setEmergencyMessage.h
//
// Written By: Danny Kent (jaus AT dannykent DOT com), Tom Galluzzo 
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines the attributes of a SetEmergencyMessage

#ifndef SET_EMERGENCY_MESSAGE_H
#define SET_EMERGENCY_MESSAGE_H

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

	// MESSAGE DATA MEMBERS GO HERE
	JausUnsignedShort emergencyCode;
	
}SetEmergencyMessageStruct;

typedef SetEmergencyMessageStruct* SetEmergencyMessage;

SetEmergencyMessage setEmergencyMessageCreate(void);
void setEmergencyMessageDestroy(SetEmergencyMessage);

JausBoolean setEmergencyMessageFromBuffer(SetEmergencyMessage message, unsigned char* buffer, unsigned int bufferSizeBytes);
JausBoolean setEmergencyMessageToBuffer(SetEmergencyMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);
JausBoolean setEmergencyMessageToUdpBuffer(SetEmergencyMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);

SetEmergencyMessage setEmergencyMessageFromJausMessage(JausMessage jausMessage);
JausMessage setEmergencyMessageToJausMessage(SetEmergencyMessage message);

unsigned int setEmergencyMessageUdpSize(SetEmergencyMessage message);
unsigned int setEmergencyMessageSize(SetEmergencyMessage message);


#endif // SET_EMERGENCY_MESSAGE_H
