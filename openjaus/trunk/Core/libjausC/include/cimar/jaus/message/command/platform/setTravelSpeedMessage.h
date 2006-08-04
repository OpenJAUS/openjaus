// File Name: setTravelSpeedMessage.h
//
// Written By: Danny Kent (jaus AT dannykent DOT com), Tom Galluzzo 
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines the attributes of a SetTravelSpeedMessage

#ifndef SET_TRAVEL_SPEED_MESSAGE_H
#define SET_TRAVEL_SPEED_MESSAGE_H

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

	JausDouble speedMps; //Scaled Unsigned Short (0, 10000) Mps = Meters Per Second
	
}SetTravelSpeedMessageStruct;

typedef SetTravelSpeedMessageStruct* SetTravelSpeedMessage;

SetTravelSpeedMessage setTravelSpeedMessageCreate(void);
void setTravelSpeedMessageDestroy(SetTravelSpeedMessage);

JausBoolean setTravelSpeedMessageFromBuffer(SetTravelSpeedMessage message, unsigned char* buffer, unsigned int bufferSizeBytes);
JausBoolean setTravelSpeedMessageToBuffer(SetTravelSpeedMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);
JausBoolean setTravelSpeedMessageToUdpBuffer(SetTravelSpeedMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);

SetTravelSpeedMessage setTravelSpeedMessageFromJausMessage(JausMessage jausMessage);
JausMessage setTravelSpeedMessageToJausMessage(SetTravelSpeedMessage message);

unsigned int setTravelSpeedMessageUdpSize(SetTravelSpeedMessage message);
unsigned int setTravelSpeedMessageSize(SetTravelSpeedMessage message);


#endif // SET_TRAVEL_SPEED_MESSAGE_H
