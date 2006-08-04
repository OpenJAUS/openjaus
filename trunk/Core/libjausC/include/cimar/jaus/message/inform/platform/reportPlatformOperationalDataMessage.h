// File Name: reportPlatformOperationalDataMessage.h
//
// Written By: Danny Kent (jaus AT dannykent DOT com), Tom Galluzzo 
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines the attributes of a ReportPlatformOperationalDataMessage

#ifndef REPORT_PLATFORM_OPERATIONAL_DATA_MESSAGE_H
#define REPORT_PLATFORM_OPERATIONAL_DATA_MESSAGE_H

#include "cimar/jaus.h"

#ifndef JAUS_OPERATIONAL_PV
#define JAUS_OPERATIONAL_PV
#define JAUS_OPERATIONAL_PV_ENGINE_BIT 		0
#define JAUS_OPERATIONAL_PV_ODOMETER_BIT	1
#define JAUS_OPERATIONAL_PV_BATTERY_BIT 	2
#define JAUS_OPERATIONAL_PV_FUEL_BIT 		3
#define JAUS_OPERATIONAL_PV_OIL_BIT 		4
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
	JausDouble engineTemperatureCelsius;	// Scaled Short (-75, 180)
	JausUnsignedInteger odometerMeters;
	JausDouble batteryVoltagePercent;		// Scaled Byte (0, 127)
	JausDouble fuelLevelPercent;			// Scaled Byte (0, 100)
	JausDouble oilPressurePercent;			// Scaled Byte (0, 127)
	
}ReportPlatformOperationalDataMessageStruct;

typedef ReportPlatformOperationalDataMessageStruct* ReportPlatformOperationalDataMessage;

ReportPlatformOperationalDataMessage reportPlatformOperationalDataMessageCreate(void);
void reportPlatformOperationalDataMessageDestroy(ReportPlatformOperationalDataMessage);

JausBoolean reportPlatformOperationalDataMessageFromBuffer(ReportPlatformOperationalDataMessage message, unsigned char* buffer, unsigned int bufferSizeBytes);
JausBoolean reportPlatformOperationalDataMessageToBuffer(ReportPlatformOperationalDataMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);
JausBoolean reportPlatformOperationalDataMessageToUdpBuffer(ReportPlatformOperationalDataMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);

ReportPlatformOperationalDataMessage reportPlatformOperationalDataMessageFromJausMessage(JausMessage jausMessage);
JausMessage reportPlatformOperationalDataMessageToJausMessage(ReportPlatformOperationalDataMessage message);

unsigned int reportPlatformOperationalDataMessageUdpSize(ReportPlatformOperationalDataMessage message);
unsigned int reportPlatformOperationalDataMessageSize(ReportPlatformOperationalDataMessage message);


#endif // REPORT_PLATFORM_OPERATIONAL_DATA_MESSAGE_H
