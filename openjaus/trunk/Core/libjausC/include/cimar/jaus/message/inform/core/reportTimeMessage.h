// File Name: reportTimeMessage.h
//
// Written By: Danny Kent (jaus AT dannykent DOT com), Tom Galluzzo 
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines the attributes of a ReportTimeMessage

#ifndef REPORT_TIME_MESSAGE_H
#define REPORT_TIME_MESSAGE_H

#include "cimar/jaus.h"

#ifndef JAUS_TIME_PV
#define JAUS_TIME_PV
#define JAUS_TIME_PV_TIME_STAMP_BIT 0
#define JAUS_TIME_PV_DATE_STAMP_BIT 1
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

	// MESSAGE DATA MEMBERS GO HERE
	JausBytePresenceVector presenceVector;
	JausUnsignedInteger timeStamp;
	JausUnsignedShort dateStamp;
	
}ReportTimeMessageStruct;

typedef ReportTimeMessageStruct* ReportTimeMessage;

ReportTimeMessage reportTimeMessageCreate(void);
void reportTimeMessageDestroy(ReportTimeMessage);

JausBoolean reportTimeMessageFromBuffer(ReportTimeMessage message, unsigned char* buffer, unsigned int bufferSizeBytes);
JausBoolean reportTimeMessageToBuffer(ReportTimeMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);
JausBoolean reportTimeMessageToUdpBuffer(ReportTimeMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);

ReportTimeMessage reportTimeMessageFromJausMessage(JausMessage jausMessage);
JausMessage reportTimeMessageToJausMessage(ReportTimeMessage message);

unsigned int reportTimeMessageUdpSize(ReportTimeMessage message);
unsigned int reportTimeMessageSize(ReportTimeMessage message);


#endif // REPORT_TIME_MESSAGE_H
