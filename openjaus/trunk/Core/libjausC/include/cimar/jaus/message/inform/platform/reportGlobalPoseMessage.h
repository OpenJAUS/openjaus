// File Name: reportGlobalPoseMessage.h
//
// Written By: Danny Kent (jaus AT dannykent DOT com), Tom Galluzzo 
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines the attributes of a ReportGlobalPoseMessage

#ifndef REPORT_GLOBAL_POSE_MESSAGE_H
#define REPORT_GLOBAL_POSE_MESSAGE_H

#include "cimar/jaus.h"

#ifndef JAUS_POSE_PV
#define JAUS_POSE_PV
#define JAUS_POSE_PV_LATITUDE_BIT		0
#define JAUS_POSE_PV_LONGITUDE_BIT		1
#define JAUS_POSE_PV_ELEVATION_BIT		2
#define JAUS_POSE_PV_POSITION_RMS_BIT	3
#define JAUS_POSE_PV_ROLL_BIT			4
#define JAUS_POSE_PV_PITCH_BIT			5
#define JAUS_POSE_PV_YAW_BIT			6
#define JAUS_POSE_PV_ATTITUDE_RMS_BIT	7
#define JAUS_POSE_PV_TIME_STAMP_BIT		8
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
	JausDouble latitudeDegrees;				// Scaled Int (-90, 90)
	JausDouble longitudeDegrees;			// Scaled Int (-180, 180)
	JausDouble elevationMeters;				// Scaled Int (-10000, 35000)
	JausDouble positionRmsMeters;			// Scaled UInt (0, 100)
	JausDouble rollRadians;					// Scaled Short (-JAUS_PI, JAUS_PI)
	JausDouble pitchRadians;				// Scaled Short (-JAUS_PI, JAUS_PI)
	JausDouble yawRadians;					// Scaled Short (-JAUS_PI, JAUS_PI)
	JausDouble attitudeRmsRadians;			// Scaled Short (0, JAUS_PI)
	JausUnsignedInteger timeStamp;
	
}ReportGlobalPoseMessageStruct;

typedef ReportGlobalPoseMessageStruct* ReportGlobalPoseMessage;

ReportGlobalPoseMessage reportGlobalPoseMessageCreate(void);
void reportGlobalPoseMessageDestroy(ReportGlobalPoseMessage);

JausBoolean reportGlobalPoseMessageFromBuffer(ReportGlobalPoseMessage message, unsigned char* buffer, unsigned int bufferSizeBytes);
JausBoolean reportGlobalPoseMessageToBuffer(ReportGlobalPoseMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);
JausBoolean reportGlobalPoseMessageToUdpBuffer(ReportGlobalPoseMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);

ReportGlobalPoseMessage reportGlobalPoseMessageFromJausMessage(JausMessage jausMessage);
JausMessage reportGlobalPoseMessageToJausMessage(ReportGlobalPoseMessage message);

unsigned int reportGlobalPoseMessageUdpSize(ReportGlobalPoseMessage message);
unsigned int reportGlobalPoseMessageSize(ReportGlobalPoseMessage message);


#endif // REPORT_GLOBAL_POSE_MESSAGE_H
