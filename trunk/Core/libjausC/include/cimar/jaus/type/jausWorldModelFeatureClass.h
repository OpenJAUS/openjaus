// File Name: jausWorldModelFeatureClass.h
//
// Written By: Danny Kent (jaus AT dannykent DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file describes all the functionality associated with a JausWorldModelFeatureClass. 
// FeatureClasses are used to support metadata and attributes associated with objects in the JausWorldModel message set.

#ifndef JAUS_WM_FEATURE_CLASS_H
#define JAUS_WM_FEATURE_CLASS_H

#define JAUS_WM_FC_METADATA_STRING_LENGTH 65535

#include "cimar/jaus.h"

// ************************************************************************************************************************************
//			JausWorldModelFeatureClassAttribute
// ************************************************************************************************************************************
typedef struct
{
	JausByte dataType;					// Enumeration, see above
	union								// Union of possible type values
	{
		JausByte byteValue;
		JausShort shortValue;
		JausInteger integerValue;
		JausLong longValue;
		JausUnsignedShort unsignedShortValue;
		JausUnsignedInteger unsignedIntegerValue;
		JausUnsignedLong unsignedLongValue;
		JausFloat floatValue;
		JausDouble doubleValue;
		struct
		{
			JausByte redValue;
			JausByte greenValue;
			JausByte blueValue;
		};
	};
}JausWorldModelFeatureClassAttributeStruct;
typedef JausWorldModelFeatureClassAttributeStruct *JausWorldModelFeatureClassAttribute;

// JausWorldModelFeatureClassAttribute Constructor
JausWorldModelFeatureClassAttribute featureClassAttributeCreate(void);

// JausWorldModelFeatureClassAttribute Constructor (from Buffer)
JausWorldModelFeatureClassAttribute featureClassAttributeFromBuffer(unsigned char *buffer, unsigned int bufferSizeBytes);

// JausWorldModelFeatureClassAttribute Destructor
void featureClassAttributeDestroy(JausWorldModelFeatureClassAttribute attribute);

// JausWorldModelFeatureClassAttribute To Buffer
JausBoolean featureClassAttributeToBuffer(JausWorldModelFeatureClassAttribute attribute, unsigned char *buffer, unsigned int bufferSizeBytes);

// JausWorldModelFeatureClassAttribute Buffer Size
unsigned int featureClassAttributeSizeBytes(JausWorldModelFeatureClassAttribute attribute);

// JausWorldModelFeatureClassAttribute Copy
JausWorldModelFeatureClassAttribute featureClassAttributeCopy(JausWorldModelFeatureClassAttribute attribute);

// JausWorldModelFeatureClassAttribute ToString
int featureClassAttributeToString(JausWorldModelFeatureClassAttribute attribute, char *string);

// JausWorldModelFeatureClassAttribute GetValue
JausUnsignedLong featureClassAttributeGetValue(JausWorldModelFeatureClassAttribute attribute);

// ************************************************************************************************************************************
//			FeatureClass
// ************************************************************************************************************************************
typedef struct
{
	JausUnsignedShort id;										// Enumeration, defined by system
	char metaData[JAUS_WM_FC_METADATA_STRING_LENGTH];			// String of Metadata information defined for this Feature Class
	JausWorldModelFeatureClassAttribute attribute;				// Feature Class Attribute data type and value
}JausWorldModelFeatureClassStruct;
typedef JausWorldModelFeatureClassStruct *JausWorldModelFeatureClass;

// JausWorldModelFeatureClass Constructor
JausWorldModelFeatureClass featureClassCreate(void);

// JausWorldModelFeatureClass Constructor (from Buffer)
JausWorldModelFeatureClass featureClassFromBuffer(unsigned char *buffer, unsigned int bufferSizeBytes);

// JausWorldModelFeatureClass Destructor
void featureClassDestroy(JausWorldModelFeatureClass fcClass);

// JausWorldModelFeatureClass To Buffer
JausBoolean featureClassToBuffer(JausWorldModelFeatureClass fcClass, unsigned char *buffer, unsigned int bufferSizeBytes);

// JausWorldModelFeatureClass Buffer Size
unsigned int featureClassSizeBytes(JausWorldModelFeatureClass fcClass);

// JausWorldModelFeatureClass Copy
JausWorldModelFeatureClass featureClassCopy(JausWorldModelFeatureClass fcClass);

#endif
