// File Name: createVksObjectsMessage.h
//
// Written By: Danny Kent (jaus AT dannykent DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines the attributes of a CreateVksObjectsMessage

#ifndef CREATE_VKS_OBJECTS_MESSAGE_H
#define CREATE_VKS_OBJECTS_MESSAGE_H

#include <cimar.h>
#include "cimar/jaus.h"

#ifndef VKS_PV_CREATE
#define VKS_PV_CREATE_BUFFERED_BIT	0
#endif

#ifndef VKS_CREATE_PROPERTIES
#define VKS_CREATE_PROPERTIES_CONFIRMATION_BIT	0
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
	JausBytePresenceVector presenceVector;		// presenceVector
	JausBytePresenceVector messageProperties; 	// Bit Field, use Presence Vector for ease
	JausByte requestId;							// Local Request ID
	Vector vectorObjects;						// Dynamic Array of Vector Objects
}CreateVksObjectsMessageStruct;

typedef CreateVksObjectsMessageStruct* CreateVksObjectsMessage;

CreateVksObjectsMessage createVksObjectsMessageCreate(void);
void createVksObjectsMessageDestroy(CreateVksObjectsMessage);

JausBoolean createVksObjectsMessageFromBuffer(CreateVksObjectsMessage message, unsigned char* buffer, unsigned int bufferSizeBytes);
JausBoolean createVksObjectsMessageToBuffer(CreateVksObjectsMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);
JausBoolean createVksObjectsMessageToUdpBuffer(CreateVksObjectsMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);

CreateVksObjectsMessage createVksObjectsMessageFromJausMessage(JausMessage jausMessage);
JausMessage createVksObjectsMessageToJausMessage(CreateVksObjectsMessage message);

unsigned int createVksObjectsMessageUdpSize(CreateVksObjectsMessage message);
unsigned int createVksObjectsMessageSize(CreateVksObjectsMessage message);


#endif // CREATE_VKS_OBJECTS_MESSAGE_H
