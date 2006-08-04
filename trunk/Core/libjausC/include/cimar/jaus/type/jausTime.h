// File Name: jausTime.h
//
// Written By: Danny Kent (jaus AT dannykent DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines the functionality of a JausTime object

#ifndef JAUS_TIME_H
#define JAUS_TIME_H

#include "cimar/jaus.h"

#define JAUS_TIME_STAMP_SIZE_BYTES		JAUS_UNSIGNED_INTEGER_SIZE_BYTES // size
#define JAUS_DATE_STAMP_SIZE_BYTES		JAUS_UNSIGNED_SHORT_SIZE_BYTES // size

// Bit Shift Defines
#define JAUS_TIME_STAMP_MILLISEC_SHIFT 	0
#define JAUS_TIME_STAMP_SECOND_SHIFT 	10
#define JAUS_TIME_STAMP_MINUTE_SHIFT 	16
#define JAUS_TIME_STAMP_HOUR_SHIFT 		22
#define JAUS_TIME_STAMP_DAY_SHIFT 		27
#define JAUS_DATE_STAMP_DAY_SHIFT 		0
#define JAUS_DATE_STAMP_MONTH_SHIFT 	5
#define JAUS_DATE_STAMP_YEAR_SHIFT 		9

// Bit Mask Defines
#define JAUS_TIME_STAMP_MILLISEC_MASK 	0x1FF 	// 9 bits
#define JAUS_TIME_STAMP_SECOND_MASK 	0x3F	// 6 bits
#define JAUS_TIME_STAMP_MINUTE_MASK 	0x3F	// 6 bits
#define JAUS_TIME_STAMP_HOUR_MASK 		0x1F	// 5 bits
#define JAUS_TIME_STAMP_DAY_MASK 		0x1F	// 5 bits
#define JAUS_DATE_STAMP_DAY_MASK 		0x1F	// 5 bits
#define JAUS_DATE_STAMP_MONTH_MASK 		0x0F	// 4 bits
#define JAUS_DATE_STAMP_YEAR_MASK 		0x7F	// 7 bits

typedef struct
{
	JausUnsignedInteger timeStamp;
	JausUnsignedShort dateStamp;

	JausUnsignedShort millisec;
	JausUnsignedShort second;
	JausUnsignedShort minute;
	JausUnsignedShort hour;
	JausUnsignedShort day;
	JausUnsignedShort month;
	JausUnsignedShort year;
	
}JausTimeStruct;

typedef JausTimeStruct *JausTime;

JausTime jausTimeCreate(void);
void jausTimeDestroy(JausTime time);

JausBoolean jausTimeSetCurrentTime(JausTime time);
JausBoolean jausTimeToString(JausTime time, char *buffer);

JausBoolean jausTimeStampFromBuffer(JausTime input, unsigned char *buf, unsigned int bufferSizeBytes);
JausBoolean jausTimeStampToBuffer(JausTime input, unsigned char *buf, unsigned int bufferSizeBytes);

JausBoolean jausDataStampFromBuffer(JausTime input, unsigned char *buf, unsigned int bufferSizeBytes);
JausBoolean jausDataStampToBuffer(JausTime input, unsigned char *buf, unsigned int bufferSizeBytes);

JausUnsignedInteger jausTimeGetTimeStamp(JausTime time);
JausUnsignedShort jausTimeGetDateStamp(JausTime time);

#endif
