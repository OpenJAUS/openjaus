// File Name: reportGlobalVectorMessage.h
//
// Written By: Danny Kent (jaus AT dannykent DOT com), Tom Galluzzo 
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines the attributes of a ReportGlobalVectorMessage

#ifndef REPORT_GLOBAL_VECTOR_MESSAGE_H
#define REPORT_GLOBAL_VECTOR_MESSAGE_H

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
	
}ReportGlobalVectorMessageStruct;

typedef ReportGlobalVectorMessageStruct* ReportGlobalVectorMessage;

ReportGlobalVectorMessage reportGlobalVectorMessageCreate(void);
void reportGlobalVectorMessageDestroy(ReportGlobalVectorMessage);

JausBoolean reportGlobalVectorMessageFromBuffer(ReportGlobalVectorMessage message, unsigned char* buffer, unsigned int bufferSizeBytes);
JausBoolean reportGlobalVectorMessageToBuffer(ReportGlobalVectorMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);
JausBoolean reportGlobalVectorMessageToUdpBuffer(ReportGlobalVectorMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);

ReportGlobalVectorMessage reportGlobalVectorMessageFromJausMessage(JausMessage jausMessage);
JausMessage reportGlobalVectorMessageToJausMessage(ReportGlobalVectorMessage message);

unsigned int reportGlobalVectorMessageUdpSize(ReportGlobalVectorMessage message);
unsigned int reportGlobalVectorMessageSize(ReportGlobalVectorMessage message);


#endif // REPORT_GLOBAL_VECTOR_MESSAGE_H
