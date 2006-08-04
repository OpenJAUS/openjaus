// File Name: deleteVksObjectsMessage.h
//
// Written By: Danny Kent (jaus AT dannykent DOT com), Tom Galluzzo 
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines the attributes of a DeleteVksObjectsMessage

#ifndef DELETE_VKS_OBJECTS_MESSAGE_H
#define DELETE_VKS_OBJECTS_MESSAGE_H

#include "cimar/jaus.h"

// Note: The PV for this message is a bit over-defined
// If the VKS_PV_DELETE_OBJECTS_REGION_BIT is set, then the VKS_PV_DELETE_OBJECTS_POINT_COUNT_BIT is required
// The VKS_PV_DELETE_OBJECTS_BUFFER_BIT cannot be set without the VKS_PV_DELETE_OBJECTS_REGION_BIT
//
// If the VKS_PV_DELETE_OBJECTS_FEATURE_CLASS_BIT is set or the VKS_PV_DELETE_OBJECTS_ATTRIBUTE_BIT is set, 
// then the VKS_PV_DELETE_OBJECTS_FC_COUNT_BIT is required
#ifndef VKS_PV_DELETE_OBJECTS
#define VKS_PV_DELETE_OBJECTS
#define VKS_PV_DELETE_OBJECTS_ID_BIT					0
#define VKS_PV_DELETE_OBJECTS_REGION_BIT				1
#define VKS_PV_DELETE_OBJECTS_BUFFER_BIT				2
#define VKS_PV_DELETE_OBJECTS_FC_COUNT_BIT				3
#define VKS_PV_DELETE_OBJECTS_FEATURE_CLASS_BIT			4
#define VKS_PV_DELETE_OBJECTS_ATTRIBUTE_BIT				5
#define VKS_PV_DELETE_OBJECTS_POINT_COUNT_BIT			6
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
	JausBytePresenceVector presenceVector;	// 1: Presence Vector
	JausByte requestId;						// 2: Id to respond to this message with
	JausUnsignedShort objectCount;			// 3: Count of specific object ids to delete
	JausUnsignedInteger *objectIds;			// 4: Array of specific object ids
	JausWorldModelVectorObject deletionRegion;			// 5: Deletion region with associated FCs and attributes
	
}DeleteVksObjectsMessageStruct;

typedef DeleteVksObjectsMessageStruct* DeleteVksObjectsMessage;

DeleteVksObjectsMessage deleteVksObjectsMessageCreate(void);
void deleteVksObjectsMessageDestroy(DeleteVksObjectsMessage);

JausBoolean deleteVksObjectsMessageFromBuffer(DeleteVksObjectsMessage message, unsigned char* buffer, unsigned int bufferSizeBytes);
JausBoolean deleteVksObjectsMessageToBuffer(DeleteVksObjectsMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);
JausBoolean deleteVksObjectsMessageToUdpBuffer(DeleteVksObjectsMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);

DeleteVksObjectsMessage deleteVksObjectsMessageFromJausMessage(JausMessage jausMessage);
JausMessage deleteVksObjectsMessageToJausMessage(DeleteVksObjectsMessage message);

unsigned int deleteVksObjectsMessageUdpSize(DeleteVksObjectsMessage message);
unsigned int deleteVksObjectsMessageSize(DeleteVksObjectsMessage message);


#endif // DELETE_VKS_OBJECTS_MESSAGE_H
