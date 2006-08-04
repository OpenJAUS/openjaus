// File Name: JausEventLimit.h
//
// Written By: Danny Kent (jaus AT dannykent DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file describes the stucture and functionality associated with an 
// EventLimit for use with the Jaus Events Message Set
#ifndef EVENT_LIMITS_H
#define EVENT_LIMITS_H

// Attribute Data Types as defined in Events Document v1.8
#ifndef EVENT_LIMIT_DATA_TYPE
#define EVENT_LIMIT_DATA_TYPE
#define EVENT_LIMIT_DEFAULT_DATA			255
#define EVENT_LIMIT_BYTE_DATA				0
#define EVENT_LIMIT_SHORT_DATA				1
#define EVENT_LIMIT_INTEGER_DATA			2
#define EVENT_LIMIT_LONG_DATA				3
#define EVENT_LIMIT_UNSIGNED_SHORT_DATA		4
#define EVENT_LIMIT_UNSIGNED_INTEGER_DATA	5
#define EVENT_LIMIT_UNSIGNED_LONG_DATA		6
#define EVENT_LIMIT_FLOAT_DATA				7
#define EVENT_LIMIT_DOUBLE_DATA				8
#define EVENT_LIMIT_RGB_DATA				9
#endif

typedef union
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
}JausEventLimitStruct;

typedef JausEventLimitStruct *JausEventLimit;

typedef struct JausEventListStruct
{
	void *eventMessage;
	JausByte eventId;
	JausEventLimit previousLimitValue;
}JausEventStruct;

typedef JausEventStruct *JausEvent;

// JausEventLimit Constructor
JausEventLimit jausEventLimitCreate();

// JausEventLimit Destructor
void jausEventLimitDestroy(JausEventLimit limit);

// JausEventLimit Constructor (from Buffer)
JausEventLimit jausEventLimitFromBuffer(unsigned char *buffer, unsigned int bufferSizeBytes, JausByte dataType);

// JausEventLimit To Buffer
JausBoolean jausEventLimitToBuffer(JausEventLimit limit, unsigned char *buffer, unsigned int bufferSizeBytes, JausByte dataType);

unsigned int jausEventLimitByteSize(JausByte dataType);

JausEvent jausEventCreate();
void jausEventDestroy(JausEvent event);

#endif
