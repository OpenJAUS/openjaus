// File Name: reportGlobalWaypointMessage.h
//
// Written By: Danny Kent (jaus AT dannykent DOT com), Tom Galluzzo 
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines the attributes of a ReportGlobalWaypointMessage

#ifndef REPORT_GLOBAL_WAYPOINT_MESSAGE_H
#define REPORT_GLOBAL_WAYPOINT_MESSAGE_H

#include "cimar/jaus.h"

#ifndef JAUS_WAYPOINT_PV
#define JAUS_WAYPOINT_PV
#define JAUS_WAYPOINT_PV_ELEVATION_BIT	0
#define JAUS_WAYPOINT_PV_ROLL_BIT		1
#define JAUS_WAYPOINT_PV_PITCH_BIT		2
#define JAUS_WAYPOINT_PV_YAW_BIT		3
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
	JausUnsignedShort waypointNumber;
	JausDouble latitudeDegrees;		// Scaled Integer (-90, 90)
	JausDouble longitudeDegrees; 	// Scaled Integer (-180, 180)
	JausDouble elevationMeters; 	// Scaled Integer (-10000, 35000)
	JausDouble rollRadians;			// Scaled Short (-JAUS_PI, JAUS_PI)
	JausDouble pitchRadians;		// Scaled Short (-JAUS_PI, JAUS_PI)
	JausDouble yawRadians;			// Scaled Short (-JAUS_PI, JAUS_PI)
	
}ReportGlobalWaypointMessageStruct;

typedef ReportGlobalWaypointMessageStruct* ReportGlobalWaypointMessage;

ReportGlobalWaypointMessage reportGlobalWaypointMessageCreate(void);
void reportGlobalWaypointMessageDestroy(ReportGlobalWaypointMessage);

JausBoolean reportGlobalWaypointMessageFromBuffer(ReportGlobalWaypointMessage message, unsigned char* buffer, unsigned int bufferSizeBytes);
JausBoolean reportGlobalWaypointMessageToBuffer(ReportGlobalWaypointMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);
JausBoolean reportGlobalWaypointMessageToUdpBuffer(ReportGlobalWaypointMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);

ReportGlobalWaypointMessage reportGlobalWaypointMessageFromJausMessage(JausMessage jausMessage);
JausMessage reportGlobalWaypointMessageToJausMessage(ReportGlobalWaypointMessage message);

unsigned int reportGlobalWaypointMessageUdpSize(ReportGlobalWaypointMessage message);
unsigned int reportGlobalWaypointMessageSize(ReportGlobalWaypointMessage message);


#endif // REPORT_GLOBAL_WAYPOINT_MESSAGE_H
