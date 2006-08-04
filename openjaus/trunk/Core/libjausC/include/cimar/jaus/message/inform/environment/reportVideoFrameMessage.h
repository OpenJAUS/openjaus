// File Name: reportVideoFrameMessage.h
//
// Written By: Danny Kent (jaus AT dannykent DOT com), Tom Galluzzo 
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines the attributes of a ReportVideoFrameMessage

#ifndef REPORT_VIDEO_FRAME_MESSAGE_H
#define REPORT_VIDEO_FRAME_MESSAGE_H

#include "cimar/jaus.h"

typedef struct
{
	// Include all parameters from a JausMessage structure:
	// Header Properties
	union
	{
		struct
		{
			// Properties by bit fields
#ifdef __ppc__
			JausUnsignedShort ackNak:2;
			JausUnsignedShort priority:4; 
			JausUnsignedShort reserved:2;
			JausUnsignedShort version:6;
			JausUnsignedShort expFlag:1;
			JausUnsignedShort scFlag:1;
#else
			JausUnsignedShort priority:4; 
			JausUnsignedShort ackNak:2;
			JausUnsignedShort scFlag:1; 
			JausUnsignedShort expFlag:1;
			JausUnsignedShort version:6; 
			JausUnsignedShort reserved:2;
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
	
	JausByte cameraID;
	JausByte videoFormat;
	JausByte *data;  // or char* ?
	JausUnsignedInteger bufferSizeBytes;
	
}ReportVideoFrameMessageStruct;

typedef ReportVideoFrameMessageStruct* ReportVideoFrameMessage;

ReportVideoFrameMessage reportVideoFrameMessageCreate(void);
void reportVideoFrameMessageDestroy(ReportVideoFrameMessage);

JausBoolean reportVideoFrameMessageFromBuffer(ReportVideoFrameMessage message, unsigned char* buffer, unsigned int bufferSizeBytes);
JausBoolean reportVideoFrameMessageToBuffer(ReportVideoFrameMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);
JausBoolean reportVideoFrameMessageToUdpBuffer(ReportVideoFrameMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);

ReportVideoFrameMessage reportVideoFrameMessageFromJausMessage(JausMessage jausMessage);
JausMessage reportVideoFrameMessageToJausMessage(ReportVideoFrameMessage message);

unsigned int reportVideoFrameMessageUdpSize(ReportVideoFrameMessage message);
unsigned int reportVideoFrameMessageSize(ReportVideoFrameMessage message);


#endif // REPORT_VIDEO_FRAME_MESSAGE_H
