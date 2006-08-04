// File Name: reportVksFeatureClassMetadataMessage.h
//
// Written By: Danny Kent (jaus AT dannykent DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines the attributes of a ReportVksFeatureClassMetadataMessage

#ifndef REPORT_VKS_FEATURE_CLASS_METADATA_MESSAGE_H
#define REPORT_VKS_FEATURE_CLASS_METADATA_MESSAGE_H

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

	JausWorldModelFeatureClass fcClass;	
}ReportVksFeatureClassMetadataMessageStruct;

typedef ReportVksFeatureClassMetadataMessageStruct* ReportVksFeatureClassMetadataMessage;

ReportVksFeatureClassMetadataMessage reportVksFeatureClassMetadataMessageCreate(void);
void reportVksFeatureClassMetadataMessageDestroy(ReportVksFeatureClassMetadataMessage);

JausBoolean reportVksFeatureClassMetadataMessageFromBuffer(ReportVksFeatureClassMetadataMessage message, unsigned char* buffer, unsigned int bufferSizeBytes);
JausBoolean reportVksFeatureClassMetadataMessageToBuffer(ReportVksFeatureClassMetadataMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);
JausBoolean reportVksFeatureClassMetadataMessageToUdpBuffer(ReportVksFeatureClassMetadataMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);

ReportVksFeatureClassMetadataMessage reportVksFeatureClassMetadataMessageFromJausMessage(JausMessage jausMessage);
JausMessage reportVksFeatureClassMetadataMessageToJausMessage(ReportVksFeatureClassMetadataMessage message);

unsigned int reportVksFeatureClassMetadataMessageUdpSize(ReportVksFeatureClassMetadataMessage message);
unsigned int reportVksFeatureClassMetadataMessageSize(ReportVksFeatureClassMetadataMessage message);


#endif // REPORT_VKS_FEATURE_CLASS_METADATA_MESSAGE_H
