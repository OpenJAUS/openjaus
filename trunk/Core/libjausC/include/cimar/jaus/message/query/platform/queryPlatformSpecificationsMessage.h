// File Name: queryPlatformSpecificationsMessage.h
//
// Written By: Danny Kent (jaus AT dannykent DOT com), Tom Galluzzo 
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines the attributes of a QueryPlatformSpecificationsMessage

#ifndef QUERY_PLATFORM_SPECIFICATIONS_MESSAGE_H
#define QUERY_PLATFORM_SPECIFICATIONS_MESSAGE_H

#include "cimar/jaus.h"

#ifndef JAUS_PLATFORM_PV
#define JAUS_PLATFORM_PV
#define JAUS_PLATFORM_PV_PLATFORM_NAME_BIT		0
#define JAUS_PLATFORM_PV_FRONT_BIT				1
#define JAUS_PLATFORM_PV_BACK_BIT				2
#define JAUS_PLATFORM_PV_RIGHT_BIT				3
#define JAUS_PLATFORM_PV_LEFT_BIT				4
#define JAUS_PLATFORM_PV_BOTTOM_BIT				5
#define JAUS_PLATFORM_PV_TOP_BIT				6
#define JAUS_PLATFORM_PV_X_CG_BIT				7
#define JAUS_PLATFORM_PV_Y_CG_BIT				8
#define JAUS_PLATFORM_PV_Z_CG_BIT				9
#define JAUS_PLATFORM_PV_TURNING_RADIUS_BIT		10
#define JAUS_PLATFORM_PV_WHEEL_BASE_BIT			11
#define JAUS_PLATFORM_PV_TRACK_WIDTH_BIT		12
#define JAUS_PLATFORM_PV_PITCH_OVER_BIT			13
#define JAUS_PLATFORM_PV_ROLL_OVER_BIT			14
#define JAUS_PLATFORM_PV_MAX_VELOCITY_X_BIT		15
#define JAUS_PLATFORM_PV_MAX_VELOCITY_Y_BIT		16
#define JAUS_PLATFORM_PV_MAX_VELOCITY_Z_BIT		17
#define JAUS_PLATFORM_PV_MAX_ROLL_RATE_BIT		18
#define JAUS_PLATFORM_PV_MAX_PITCH_RATE_BIT		19
#define JAUS_PLATFORM_PV_MAX_YAW_RATE_BIT		20
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

	JausIntegerPresenceVector presenceVector;
	
}QueryPlatformSpecificationsMessageStruct;

typedef QueryPlatformSpecificationsMessageStruct* QueryPlatformSpecificationsMessage;

QueryPlatformSpecificationsMessage queryPlatformSpecificationsMessageCreate(void);
void queryPlatformSpecificationsMessageDestroy(QueryPlatformSpecificationsMessage);

JausBoolean queryPlatformSpecificationsMessageFromBuffer(QueryPlatformSpecificationsMessage message, unsigned char* buffer, unsigned int bufferSizeBytes);
JausBoolean queryPlatformSpecificationsMessageToBuffer(QueryPlatformSpecificationsMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);
JausBoolean queryPlatformSpecificationsMessageToUdpBuffer(QueryPlatformSpecificationsMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);

QueryPlatformSpecificationsMessage queryPlatformSpecificationsMessageFromJausMessage(JausMessage jausMessage);
JausMessage queryPlatformSpecificationsMessageToJausMessage(QueryPlatformSpecificationsMessage message);

unsigned int queryPlatformSpecificationsMessageUdpSize(QueryPlatformSpecificationsMessage message);
unsigned int queryPlatformSpecificationsMessageSize(QueryPlatformSpecificationsMessage message);


#endif // QUERY_PLATFORM_SPECIFICATIONS_MESSAGE_H
