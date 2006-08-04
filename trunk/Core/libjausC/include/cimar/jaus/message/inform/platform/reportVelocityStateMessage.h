// File Name: reportVelocityStateMessage.h
//
// Written By: Danny Kent (jaus AT dannykent DOT com), Tom Galluzzo 
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines the attributes of a ReportVelocityStateMessage

#ifndef REPORT_VELOCITY_STATE_MESSAGE_H
#define REPORT_VELOCITY_STATE_MESSAGE_H

#include "cimar/jaus.h"

#ifndef JAUS_VELOCITY_PV
#define JAUS_VELOCITY_PV
#define JAUS_VELOCITY_PV_VELOCITY_X_BIT		0
#define JAUS_VELOCITY_PV_VELOCITY_Y_BIT		1
#define JAUS_VELOCITY_PV_VELOCITY_Z_BIT		2
#define JAUS_VELOCITY_PV_VELOCITY_RMS_BIT	3
#define JAUS_VELOCITY_PV_ROLL_RATE_BIT		4
#define JAUS_VELOCITY_PV_PITCH_RATE_BIT		5
#define JAUS_VELOCITY_PV_YAW_RATE_BIT		6
#define JAUS_VELOCITY_PV_RATE_RMS_BIT		7
#define JAUS_VELOCITY_PV_TIME_STAMP_BIT		8
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

	JausShortPresenceVector presenceVector;
	JausDouble velocityXMps;	// Scaled Int (-65.534, 65.534) 	Mps = Meters per Second
	JausDouble velocityYMps;	// Scaled Int (-65.534, 65.534) 	Mps = Meters per Second
	JausDouble velocityZMps;	// Scaled Int (-65.534, 65.534) 	Mps = Meters per Secon
	JausDouble velocityRmsMps;	// Scaled UInt (0, 100) 			Mps = Meters per Second
	JausDouble rollRateRps;		// Scaled Short (-32.767, 32.767) 	Rps = Radians per Second
	JausDouble pitchRateRps;	// Scaled Short (-32.767, 32.767) 	Rps = Radians per Second
	JausDouble yawRateRps;		// Scaled Short (-32.767, 32.767) 	Rps = Radians per Second
	JausDouble rateRmsRps;		// Scaled UShort (0, JAUS_PI) 		Rps = Radians per Second
	JausUnsignedInteger timeStamp;
	
}ReportVelocityStateMessageStruct;

typedef ReportVelocityStateMessageStruct* ReportVelocityStateMessage;

ReportVelocityStateMessage reportVelocityStateMessageCreate(void);
void reportVelocityStateMessageDestroy(ReportVelocityStateMessage);

JausBoolean reportVelocityStateMessageFromBuffer(ReportVelocityStateMessage message, unsigned char* buffer, unsigned int bufferSizeBytes);
JausBoolean reportVelocityStateMessageToBuffer(ReportVelocityStateMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);
JausBoolean reportVelocityStateMessageToUdpBuffer(ReportVelocityStateMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);

ReportVelocityStateMessage reportVelocityStateMessageFromJausMessage(JausMessage jausMessage);
JausMessage reportVelocityStateMessageToJausMessage(ReportVelocityStateMessage message);

unsigned int reportVelocityStateMessageUdpSize(ReportVelocityStateMessage message);
unsigned int reportVelocityStateMessageSize(ReportVelocityStateMessage message);


#endif // REPORT_VELOCITY_STATE_MESSAGE_H
