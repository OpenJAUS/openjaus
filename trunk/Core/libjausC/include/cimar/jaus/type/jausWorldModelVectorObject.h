// File Name: jausWorldModelVectorObject.h
//
// Written By: Danny Kent (jaus AT dannykent DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file describes all the functionality associated with a JausWorldModelVectorObject. 
// JausWorldModelVectorObjects are used to support the storage and transfer of vector objects using the World Model message set.

#ifndef JAUS_WM_VECTOR_OBJECT_H
#define JAUS_WM_VECTOR_OBJECT_H

#include <cimar.h>
#include <cimar/jaus.h>

// Vector Object types as defined in WMVKS Document v1.3
#ifndef JAUS_WM_OBJECT_TYPES
#define JAUS_WM_OBJECT_TYPES
#define JAUS_WM_UNKNOWN_TYPE	255
#define JAUS_WM_POINT_TYPE		0
#define JAUS_WM_LINE_TYPE		1
#define JAUS_WM_POLYGON_TYPE	2
#endif

// Attribute Data Types as defined in WMVKS Document v1.3
#ifndef JAUS_WM_OBJECT_DATA_TYPE
#define JAUS_WM_OBJECT_DATA_TYPE
#define JAUS_WM_OBJECT_DEFAULT_DATA				255
#define JAUS_WM_OBJECT_BYTE_DATA				0
#define JAUS_WM_OBJECT_SHORT_DATA				1
#define JAUS_WM_OBJECT_INTEGER_DATA				2
#define JAUS_WM_OBJECT_LONG_DATA				3
#define JAUS_WM_OBJECT_UNSIGNED_SHORT_DATA		4
#define JAUS_WM_OBJECT_UNSIGNED_INTEGER_DATA	5
#define JAUS_WM_OBJECT_UNSIGNED_LONG_DATA		6
#define JAUS_WM_OBJECT_FLOAT_DATA				7
#define JAUS_WM_OBJECT_DOUBLE_DATA				8
#define JAUS_WM_OBJECT_RGB_DATA					9
#endif

// ************************************************************************************************************************************
//			JausWorldModelVectorObject
// ************************************************************************************************************************************
typedef struct
{
	JausUnsignedShort id;		// Unique Object Id
	JausByte type;				// Enumeration, see above
	JausFloat bufferMeters;		// Buffer Size in meters
	Vector featureClasses;		// Dynamic Array of FeatureClass data
	Vector dataPoints;			// Dynamic Array of PointLla data
}JausWorldModelVectorObjectStruct;
typedef JausWorldModelVectorObjectStruct *JausWorldModelVectorObject;

// JausWorldModelVectorObject Constructor
JausWorldModelVectorObject vectorObjectCreate(void);

// JausWorldModelVectorObject Constructor (from Buffer)
JausWorldModelVectorObject vectorObjectFromBuffer(unsigned char *buffer, unsigned int bufferSizeBytes, JausBoolean objectBuffered);

// JausWorldModelVectorObject To Buffer
JausBoolean vectorObjectToBuffer(JausWorldModelVectorObject object, unsigned char *buffer, unsigned int bufferSizeBytes, JausBoolean objectBuffered);

// JausWorldModelVectorObject Destructor
void vectorObjectDestroy(JausWorldModelVectorObject object);

// JausWorldModelVectorObject Buffer Size
unsigned int vectorObjectSizeBytes(JausWorldModelVectorObject object, JausBoolean objectBuffered);

// JausWorldModelVectorObject To String
int vectorObjectTypeToString(JausWorldModelVectorObject object, char *string);

// JausWorldModelVectorObject Copy
JausWorldModelVectorObject vectorObjectCopy(JausWorldModelVectorObject input);

#endif // VECTOROBJECT_H
