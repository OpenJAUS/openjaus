// File Name: queryVksFeatureClassMetadataMessage.h
//
// Written By: Danny Kent (jaus AT dannykent DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines the attributes of a QueryVksFeatureClassMetadataMessage

#ifndef QUERY_VKS_FEATURE_CLASS_METADATA_MESSAGE_H
#define QUERY_VKS_FEATURE_CLASS_METADATA_MESSAGE_H

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
	JausUnsignedShort featureClassId;
	
}QueryVksFeatureClassMetadataMessageStruct;

typedef QueryVksFeatureClassMetadataMessageStruct* QueryVksFeatureClassMetadataMessage;

QueryVksFeatureClassMetadataMessage queryVksFeatureClassMetadataMessageCreate(void);
void queryVksFeatureClassMetadataMessageDestroy(QueryVksFeatureClassMetadataMessage);

JausBoolean queryVksFeatureClassMetadataMessageFromBuffer(QueryVksFeatureClassMetadataMessage message, unsigned char* buffer, unsigned int bufferSizeBytes);
JausBoolean queryVksFeatureClassMetadataMessageToBuffer(QueryVksFeatureClassMetadataMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);
JausBoolean queryVksFeatureClassMetadataMessageToUdpBuffer(QueryVksFeatureClassMetadataMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);

QueryVksFeatureClassMetadataMessage queryVksFeatureClassMetadataMessageFromJausMessage(JausMessage jausMessage);
JausMessage queryVksFeatureClassMetadataMessageToJausMessage(QueryVksFeatureClassMetadataMessage message);

unsigned int queryVksFeatureClassMetadataMessageUdpSize(QueryVksFeatureClassMetadataMessage message);
unsigned int queryVksFeatureClassMetadataMessageSize(QueryVksFeatureClassMetadataMessage message);


#endif // QUERY_VKS_FEATURE_CLASS_METADATA_MESSAGE_H
