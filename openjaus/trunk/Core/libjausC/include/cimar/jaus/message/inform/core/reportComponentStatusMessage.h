// File Name: reportComponentStatusMessage.h
//
// Written By: Danny Kent (jaus AT dannykent DOT com), Tom Galluzzo 
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines the attributes of a ReportComponentStatusMessage

#ifndef REPORT_COMPONENT_STATUS_MESSAGE_H
#define REPORT_COMPONENT_STATUS_MESSAGE_H

#define JAUS_STATUS_INITIALIZE	0
#define JAUS_STATUS_READY		1
#define JAUS_STATUS_STANDBY		2
#define JAUS_STATUS_SHUTDOWN	3
#define JAUS_STATUS_FAILURE		4
#define JAUS_STATUS_EMERGENCY	5

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
	JausByte primaryStatusCode;
	JausUnsignedInteger secondaryStatusCode;
	
}ReportComponentStatusMessageStruct;

typedef ReportComponentStatusMessageStruct* ReportComponentStatusMessage;

ReportComponentStatusMessage reportComponentStatusMessageCreate(void);
void reportComponentStatusMessageDestroy(ReportComponentStatusMessage);

JausBoolean reportComponentStatusMessageFromBuffer(ReportComponentStatusMessage message, unsigned char* buffer, unsigned int bufferSizeBytes);
JausBoolean reportComponentStatusMessageToBuffer(ReportComponentStatusMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);
JausBoolean reportComponentStatusMessageToUdpBuffer(ReportComponentStatusMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);

ReportComponentStatusMessage reportComponentStatusMessageFromJausMessage(JausMessage jausMessage);
JausMessage reportComponentStatusMessageToJausMessage(ReportComponentStatusMessage message);

unsigned int reportComponentStatusMessageUdpSize(ReportComponentStatusMessage message);
unsigned int reportComponentStatusMessageSize(ReportComponentStatusMessage message);


#endif // REPORT_COMPONENT_STATUS_MESSAGE_H
