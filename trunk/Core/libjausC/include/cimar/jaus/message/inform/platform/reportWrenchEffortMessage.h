// File Name: reportWrenchEffortMessage.h
//
// Written By: Danny Kent (jaus AT dannykent DOT com), Tom Galluzzo 
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines the attributes of a ReportWrenchEffortMessage

#ifndef REPORT_WRENCH_EFFORT_MESSAGE_H
#define REPORT_WRENCH_EFFORT_MESSAGE_H

#include "cimar/jaus.h"

#ifndef JAUS_WRENCH_PV
#define JAUS_WRENCH_PV
#define JAUS_WRENCH_PV_PROPULSIVE_LINEAR_X_BIT		0
#define JAUS_WRENCH_PV_PROPULSIVE_LINEAR_Y_BIT		1
#define JAUS_WRENCH_PV_PROPULSIVE_LINEAR_Z_BIT		2
#define JAUS_WRENCH_PV_PROPULSIVE_ROTATIONAL_X_BIT	3
#define JAUS_WRENCH_PV_PROPULSIVE_ROTATIONAL_Y_BIT	4
#define JAUS_WRENCH_PV_PROPULSIVE_ROTATIONAL_Z_BIT	5
#define JAUS_WRENCH_PV_RESISTIVE_LINEAR_X_BIT		6
#define JAUS_WRENCH_PV_RESISTIVE_LINEAR_Y_BIT		7
#define JAUS_WRENCH_PV_RESISTIVE_LINEAR_Z_BIT		8
#define JAUS_WRENCH_PV_RESISTIVE_ROTATIONAL_X_BIT	9
#define JAUS_WRENCH_PV_RESISTIVE_ROTATIONAL_Y_BIT	10
#define JAUS_WRENCH_PV_RESISTIVE_ROTATIONAL_Z_BIT	11
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

	// Message Fields:
	JausShortPresenceVector presenceVector;
	JausDouble propulsiveLinearEffortXPercent;		// Scaled Short (-100, 100)
	JausDouble propulsiveLinearEffortYPercent;		// Scaled Short (-100, 100)
	JausDouble propulsiveLinearEffortZPercent;		// Scaled Short (-100, 100)
	JausDouble propulsiveRotationalEffortXPercent;	// Scaled Short (-100, 100)
	JausDouble propulsiveRotationalEffortZPercent;	// Scaled Short (-100, 100)
	JausDouble propulsiveRotationalEffortYPercent;	// Scaled Short (-100, 100)
	JausDouble resistiveLinearEffortXPercent;		// Scaled Byte (0, 100)
	JausDouble resistiveLinearEffortYPercent;		// Scaled Byte (0, 100)
	JausDouble resistiveLinearEffortZPercent;		// Scaled Byte (0, 100)
	JausDouble resistiveRotationalEffortXPercent;	// Scaled Byte (0, 100)
	JausDouble resistiveRotationalEffortZPercent;	// Scaled Byte (0, 100)
	JausDouble resistiveRotationalEffortYPercent;	// Scaled Byte (0, 100)
	
}ReportWrenchEffortMessageStruct;

typedef ReportWrenchEffortMessageStruct* ReportWrenchEffortMessage;

ReportWrenchEffortMessage reportWrenchEffortMessageCreate(void);
void reportWrenchEffortMessageDestroy(ReportWrenchEffortMessage);

JausBoolean reportWrenchEffortMessageFromBuffer(ReportWrenchEffortMessage message, unsigned char* buffer, unsigned int bufferSizeBytes);
JausBoolean reportWrenchEffortMessageToBuffer(ReportWrenchEffortMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);
JausBoolean reportWrenchEffortMessageToUdpBuffer(ReportWrenchEffortMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);

ReportWrenchEffortMessage reportWrenchEffortMessageFromJausMessage(JausMessage jausMessage);
JausMessage reportWrenchEffortMessageToJausMessage(ReportWrenchEffortMessage message);

unsigned int reportWrenchEffortMessageUdpSize(ReportWrenchEffortMessage message);
unsigned int reportWrenchEffortMessageSize(ReportWrenchEffortMessage message);


#endif // REPORT_WRENCH_EFFORT_MESSAGE_H
