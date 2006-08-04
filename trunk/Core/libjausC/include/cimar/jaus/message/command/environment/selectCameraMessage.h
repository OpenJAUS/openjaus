// File Name: selectCameraMessage.h
//
// Written By: Danny Kent (jaus AT dannykent DOT com), Tom Galluzzo 
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines the attributes of a SelectCameraMessage

#ifndef SELECT_CAMERA_MESSAGE_H
#define SELECT_CAMERA_MESSAGE_H

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
	
}SelectCameraMessageStruct;

typedef SelectCameraMessageStruct* SelectCameraMessage;

SelectCameraMessage selectCameraMessageCreate(void);
void selectCameraMessageDestroy(SelectCameraMessage);

JausBoolean selectCameraMessageFromBuffer(SelectCameraMessage message, unsigned char* buffer, unsigned int bufferSizeBytes);
JausBoolean selectCameraMessageToBuffer(SelectCameraMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);
JausBoolean selectCameraMessageToUdpBuffer(SelectCameraMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);

SelectCameraMessage selectCameraMessageFromJausMessage(JausMessage jausMessage);
JausMessage selectCameraMessageToJausMessage(SelectCameraMessage message);

unsigned int selectCameraMessageUdpSize(SelectCameraMessage message);
unsigned int selectCameraMessageSize(SelectCameraMessage message);


#endif // SELECT_CAMERA_MESSAGE_H
