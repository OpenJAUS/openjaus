// File Name: queryVksObjectsMessage.h
//
// Written By: Danny Kent (jaus AT dannykent DOT com) 
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines the attributes of a QueryVksObjectsMessage

#ifndef QUERY_VKS_OBJECTS_MESSAGE_H
#define QUERY_VKS_OBJECTS_MESSAGE_H

#include "cimar/jaus.h"

// Note: The PV for this message is a bit over-defined
// If the VKS_PV_QUERY_OBJECTS_REGION_BIT is set, then the VKS_PV_QUERY_OBJECTS_POINT_COUNT_BIT is required
// The VKS_PV_QUERY_OBJECTS_BUFFER_BIT cannot be set without the VKS_PV_QUERY_OBJECTS_REGION_BIT
//
// If the VKS_PV_QUERY_OBJECTS_FEATURE_CLASS_BIT is set or the VKS_PV_QUERY_OBJECTS_ATTRIBUTE_BIT is set, 
// then the VKS_PV_QUERY_OBJECTS_FC_COUNT_BIT is required
#ifndef VKS_PV_QUERY_OBJECTS
#define VKS_PV_QUERY_OBJECTS
#define VKS_PV_QUERY_OBJECTS_ID_BIT					0
#define VKS_PV_QUERY_OBJECTS_REGION_BIT				1
#define VKS_PV_QUERY_OBJECTS_BUFFER_BIT				2
#define VKS_PV_QUERY_OBJECTS_FC_COUNT_BIT			3
#define VKS_PV_QUERY_OBJECTS_FEATURE_CLASS_BIT		4
#define VKS_PV_QUERY_OBJECTS_ATTRIBUTE_BIT			5
#define VKS_PV_QUERY_OBJECTS_POINT_COUNT_BIT		6
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
	JausBytePresenceVector presenceVector;				// 1: Presence Vector
	JausBytePresenceVector responsePresenceVector;		// 2: Presence Vector to be used in response (defines the data requested)
	JausByte requestId;									// 3: Local Request Id
	JausUnsignedShort objectCount;						// 4: Count of specific object ids requested
	JausUnsignedInteger *objectIds;						// 5: Array of specific object ids
	JausWorldModelVectorObject queryRegion;				// 6: Query region with associated FCs and attributes
	
}QueryVksObjectsMessageStruct;

typedef QueryVksObjectsMessageStruct* QueryVksObjectsMessage;

QueryVksObjectsMessage queryVksObjectsMessageCreate(void);
void queryVksObjectsMessageDestroy(QueryVksObjectsMessage);

JausBoolean queryVksObjectsMessageFromBuffer(QueryVksObjectsMessage message, unsigned char* buffer, unsigned int bufferSizeBytes);
JausBoolean queryVksObjectsMessageToBuffer(QueryVksObjectsMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);
JausBoolean queryVksObjectsMessageToUdpBuffer(QueryVksObjectsMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);

QueryVksObjectsMessage queryVksObjectsMessageFromJausMessage(JausMessage jausMessage);
JausMessage queryVksObjectsMessageToJausMessage(QueryVksObjectsMessage message);

unsigned int queryVksObjectsMessageUdpSize(QueryVksObjectsMessage message);
unsigned int queryVksObjectsMessageSize(QueryVksObjectsMessage message);


#endif // QUERY_VKS_OBJECTS_MESSAGE_H
