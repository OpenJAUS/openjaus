// File Name: setGlobalVectorMessage.h
//
// Written By: Danny Kent (jaus AT dannykent DOT com), Tom Galluzzo 
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines the attributes of a SetGlobalVectorMessage

#ifndef SET_GLOBAL_VECTOR_MESSAGE_H
#define SET_GLOBAL_VECTOR_MESSAGE_H

#include "cimar/jaus.h"

#ifndef JAUS_VECTOR_PV
#define JAUS_VECTOR_PV
#define JAUS_VECTOR_PV_SPEED_BIT 	0
#define JAUS_VECTOR_PV_ALTITUDE_BIT 1
#define JAUS_VECTOR_PV_HEADING_BIT 	2
#define JAUS_VECTOR_PV_ROLL_BIT 	3
#define JAUS_VECTOR_PV_PITCH_BIT 	4
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
	JausDouble speedMps; 		// Scaled Unsigned Short (0, 10000) Mps = Meters Per Second
	JausDouble altitudeMeters; 	// Scaled Integer (-10000, 35000)  
	JausDouble headingRadians; 	// Scaled Short (-JAUS_PI, JAUS_PI)
	JausDouble rollRadians; 	// Scaled Short (-JAUS_PI, JAUS_PI)	
	JausDouble pitchRadians; 	// Scaled Short (-JAUS_PI, JAUS_PI)
		
}SetGlobalVectorMessageStruct;

typedef SetGlobalVectorMessageStruct* SetGlobalVectorMessage;

SetGlobalVectorMessage setGlobalVectorMessageCreate(void);
void setGlobalVectorMessageDestroy(SetGlobalVectorMessage);

JausBoolean setGlobalVectorMessageFromBuffer(SetGlobalVectorMessage message, unsigned char* buffer, unsigned int bufferSizeBytes);
JausBoolean setGlobalVectorMessageToBuffer(SetGlobalVectorMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);
JausBoolean setGlobalVectorMessageToUdpBuffer(SetGlobalVectorMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);

SetGlobalVectorMessage setGlobalVectorMessageFromJausMessage(JausMessage jausMessage);
JausMessage setGlobalVectorMessageToJausMessage(SetGlobalVectorMessage message);

unsigned int setGlobalVectorMessageUdpSize(SetGlobalVectorMessage message);
unsigned int setGlobalVectorMessageSize(SetGlobalVectorMessage message);


#endif // SET_GLOBAL_VECTOR_MESSAGE_H
