// File Name: reportPlatformSpecificationsMessage.h
//
// Written By: Danny Kent (jaus AT dannykent DOT com), Tom Galluzzo 
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines the attributes of a ReportPlatformSpecificationsMessage

#ifndef REPORT_PLATFORM_SPEFICATIONS_MESSAGE_H
#define REPORT_PLATFORM_SPEFICATIONS_MESSAGE_H

#include "cimar/jaus.h"

#ifndef JAUS_DISCRETE_PV
#define JAUS_DISCRETE_PV
#define JAUS_DISCRETE_PV_PLATFORM_NAME_BIT		0
#define JAUS_DISCRETE_PV_FRONT_BIT				1
#define JAUS_DISCRETE_PV_BACK_BIT				2
#define JAUS_DISCRETE_PV_RIGHT_BIT				3
#define JAUS_DISCRETE_PV_LEFT_BIT				4
#define JAUS_DISCRETE_PV_BOTTOM_BIT				5
#define JAUS_DISCRETE_PV_TOP_BIT				6
#define JAUS_DISCRETE_PV_X_CG_BIT				7
#define JAUS_DISCRETE_PV_Y_CG_BIT				8
#define JAUS_DISCRETE_PV_Z_CG_BIT				9
#define JAUS_DISCRETE_PV_TURNING_RADIUS_BIT		10
#define JAUS_DISCRETE_PV_WHEEL_BASE_BIT			11
#define JAUS_DISCRETE_PV_TRACK_WIDTH_BIT		12
#define JAUS_DISCRETE_PV_PITCH_OVER_BIT			13
#define JAUS_DISCRETE_PV_ROLL_OVER_BIT			14
#define JAUS_DISCRETE_PV_MAX_VELOCITY_X_BIT		15
#define JAUS_DISCRETE_PV_MAX_VELOCITY_Y_BIT		16
#define JAUS_DISCRETE_PV_MAX_VELOCITY_Z_BIT		17
#define JAUS_DISCRETE_PV_MAX_ROLL_RATE_BIT		18
#define JAUS_DISCRETE_PV_MAX_PITCH_RATE_BIT		19
#define JAUS_DISCRETE_PV_MAX_YAW_RATE_BIT		20
#endif

#define JAUS_PLATFORM_NAME_LENGTH_BYTES			15

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

	JausIntegerPresenceVector presenceVector;
	char platformName[JAUS_PLATFORM_NAME_LENGTH_BYTES];
	JausDouble frontMeters;			// Scaled Unsigned Short (0, 32.767)
	JausDouble backMeters;			// Scaled Unsigned Short (0, 32.767)
	JausDouble rightMeters;			// Scaled Unsigned Short (0, 32.767)
	JausDouble leftMeters;			// Scaled Unsigned Short (0, 32.767)
	JausDouble bottomMeters;		// Scaled Unsigned Short (0, 32.767)
	JausDouble topMeters;			// Scaled Unsigned Short (0, 32.767)
	JausDouble xCgMeters;			// Scaled Unsigned Short (0, 32.767)
	JausDouble yCgMeters;			// Scaled Unsigned Short (0, 32.767)
	JausDouble zCgMeters;			// Scaled Unsigned Short (0, 32.767)
	JausDouble turningRadiusMeters; // Scaled Unsigned Short (0, 65.535)
	JausDouble wheelBaseMeters; 	// Scaled Unsigned Short (0, 65.535)
	JausDouble trackWidthMeters; 	// Scaled Unsigned Short (0, 65.535)
	JausDouble pitchOverRadians;	// Scaled Unsigned Short (0, 2.56)
	JausDouble rollOverRadians;		// Scaled Unsigned Short (0, 2.56)
	JausDouble maximumVelocityXMps;	// Scaled Unsigned Short (0, 65.535) Mps = Meters per Second
	JausDouble maximumVelocityYMps;	// Scaled Unsigned Short (0, 65.535) Mps = Meters per Second
	JausDouble maximumVelocityZMps;	// Scaled Unsigned Short (0, 65.535) Mps = Meters per Second		
	JausDouble maximumRollRateRps;	// Scaled Unsigned Short (0, 32.767) Rps = Radians per Second
	JausDouble maximumPitchRateRps;	// Scaled Unsigned Short (0, 32.767) Rps = Radians per Second
	JausDouble maximumYawRateRps;	// Scaled Unsigned Short (0, 32.767) Rps = Radians per Second	
	
}ReportPlatformSpecificationsMessageStruct;

typedef ReportPlatformSpecificationsMessageStruct* ReportPlatformSpecificationsMessage;

ReportPlatformSpecificationsMessage reportPlatformSpecificationsMessageCreate(void);
void reportPlatformSpecificationsMessageDestroy(ReportPlatformSpecificationsMessage);

JausBoolean reportPlatformSpecificationsMessageFromBuffer(ReportPlatformSpecificationsMessage message, unsigned char* buffer, unsigned int bufferSizeBytes);
JausBoolean reportPlatformSpecificationsMessageToBuffer(ReportPlatformSpecificationsMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);
JausBoolean reportPlatformSpecificationsMessageToUdpBuffer(ReportPlatformSpecificationsMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);

ReportPlatformSpecificationsMessage reportPlatformSpecificationsMessageFromJausMessage(JausMessage jausMessage);
JausMessage reportPlatformSpecificationsMessageToJausMessage(ReportPlatformSpecificationsMessage message);

unsigned int reportPlatformSpecificationsMessageUdpSize(ReportPlatformSpecificationsMessage message);
unsigned int reportPlatformSpecificationsMessageSize(ReportPlatformSpecificationsMessage message);


#endif // REPORT_PLATFORM_SPEFICATIONS_MESSAGE_H
