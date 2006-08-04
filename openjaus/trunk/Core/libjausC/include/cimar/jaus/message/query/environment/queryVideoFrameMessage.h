// File Name: queryVideoFrameMessage.h
//
// Written By: Danny Kent (jaus AT dannykent DOT com), Tom Galluzzo 
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines the attributes of a QueryVideoFrameMessage

#ifndef QUERY_VIDEO_FRAME_MESSAGE_H
#define QUERY_VIDEO_FRAME_MESSAGE_H

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
	
}QueryVideoFrameMessageStruct;

typedef QueryVideoFrameMessageStruct* QueryVideoFrameMessage;

QueryVideoFrameMessage queryVideoFrameMessageCreate(void);
void queryVideoFrameMessageDestroy(QueryVideoFrameMessage);

JausBoolean queryVideoFrameMessageFromBuffer(QueryVideoFrameMessage message, unsigned char* buffer, unsigned int bufferSizeBytes);
JausBoolean queryVideoFrameMessageToBuffer(QueryVideoFrameMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);
JausBoolean queryVideoFrameMessageToUdpBuffer(QueryVideoFrameMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);

QueryVideoFrameMessage queryVideoFrameMessageFromJausMessage(JausMessage jausMessage);
JausMessage queryVideoFrameMessageToJausMessage(QueryVideoFrameMessage message);

unsigned int queryVideoFrameMessageUdpSize(QueryVideoFrameMessage message);
unsigned int queryVideoFrameMessageSize(QueryVideoFrameMessage message);


#endif // QUERY_VIDEO_FRAME_MESSAGE_H
