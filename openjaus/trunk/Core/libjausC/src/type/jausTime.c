// File Name: jausTime.c
//
// Written By: Danny Kent (jaus AT dannykent DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines the functionality of a JausTime object

#include <malloc.h>
#include <time.h>
#include "cimar/jaus.h"

// Private Function Prototypes
JausBoolean calculateTimeStamp(JausTime time);
JausBoolean calculateDateStamp(JausTime time);

JausTime jausTimeCreate(void)
{
	JausTime time = (JausTime)malloc(sizeof(JausTimeStruct));
	
	time->timeStamp = newJausUnsignedInteger(0);
	time->dateStamp = newJausUnsignedShort(0);

	time->millisec = newJausUnsignedShort(0);
	time->second = newJausUnsignedShort(0);
	time->minute = newJausUnsignedShort(0);
	time->hour = newJausUnsignedShort(0);
	time->day = newJausUnsignedShort(0);
	time->month = newJausUnsignedShort(0);
	time->year = newJausUnsignedShort(0);

	return time;
}

void jausTimeDestroy(JausTime time)
{
	free(time);
}

JausBoolean jausTimeSetCurrentTime(JausTime time)
{
	static struct tm *gmTime;
	static struct timeval timeVal;
	
	// Get SystemTime
	gettimeofday(&timeVal, NULL);
	gmTime = gmtime(&timeVal.tv_sec);

	// Populate members
	time->millisec =	(unsigned short) (timeVal.tv_usec / 1.0e3);
	time->second = 		(unsigned short) gmTime->tm_sec;
	time->minute = 		(unsigned short) gmTime->tm_min;
	time->hour = 		(unsigned short) gmTime->tm_hour;
	time->day = 		(unsigned short) gmTime->tm_mday;
	time->month = 		(unsigned short) gmTime->tm_mon;
	time->year = 		(unsigned short) gmTime->tm_year + 1900;

	// Calculate TimeStamp & DataStamp
	calculateTimeStamp(time);
	calculateDateStamp(time);

	return JAUS_TRUE;
}

JausBoolean jausTimeToString(JausTime time, char *buffer)
{
	const char *months[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

	if(time)
	{		
		sprintf(buffer, "%s %02d, %04d  %02d:%02d:%02d.%d\n", months[time->month], time->day, time->year, time->hour, time->minute, time->second, time->millisec);
		return JAUS_TRUE;
	}
	else
		return JAUS_FALSE;
}

JausBoolean jausTimeStampFromBuffer(JausTime input, unsigned char *buffer, unsigned int bufferSizeBytes)
{
	// Unpack TimeStamp
	if(!jausUnsignedIntegerFromBuffer(&input->timeStamp, buffer, bufferSizeBytes)) return JAUS_FALSE;
		
	// Calculate Members from TimeStamp
	input->millisec = (input->timeStamp >> JAUS_TIME_STAMP_MILLISEC_SHIFT) & JAUS_TIME_STAMP_MILLISEC_MASK;
	input->second = (input->timeStamp >> JAUS_TIME_STAMP_SECOND_SHIFT) & JAUS_TIME_STAMP_SECOND_MASK;
	input->minute = (input->timeStamp >> JAUS_TIME_STAMP_MINUTE_SHIFT) & JAUS_TIME_STAMP_MINUTE_MASK;
	input->hour = (input->timeStamp >> JAUS_TIME_STAMP_HOUR_SHIFT) & JAUS_TIME_STAMP_HOUR_MASK;
	input->day = (input->timeStamp >> JAUS_TIME_STAMP_DAY_SHIFT) & JAUS_TIME_STAMP_DAY_MASK;
	
	return JAUS_TRUE;
}

JausBoolean jausDateStampFromBuffer(JausTime input, unsigned char *buffer, unsigned int bufferSizeBytes)
{
	// Unpack DateStamp
	if(!jausUnsignedShortFromBuffer(&input->dateStamp, buffer, bufferSizeBytes)) return JAUS_FALSE;
		
	// Calculate Members from DateStamp
	input->day = (input->dateStamp >> JAUS_DATE_STAMP_DAY_SHIFT) & JAUS_DATE_STAMP_DAY_MASK;
	input->month = (input->dateStamp >> JAUS_DATE_STAMP_MONTH_SHIFT) & JAUS_DATE_STAMP_MONTH_MASK;
	input->year = (input->dateStamp >> JAUS_DATE_STAMP_YEAR_SHIFT) & JAUS_DATE_STAMP_YEAR_MASK;

	return JAUS_TRUE;
}

JausBoolean jausTimeStampToBuffer(JausTime input, unsigned char *buffer, unsigned int bufferSizeBytes)
{
	// Calculate TimeStamp
	calculateTimeStamp(input);
	
	// Pack TimeStamp
	if(!jausUnsignedIntegerToBuffer(input->timeStamp, buffer, bufferSizeBytes)) return JAUS_FALSE;
	
	return JAUS_TRUE;
}

JausBoolean jausDateStampToBuffer(JausTime input, unsigned char *buffer, unsigned int bufferSizeBytes)
{
	// Calculate DateStamp
	calculateDateStamp(input);
	
	// Pack TimeStamp
	if(!jausUnsignedShortToBuffer(input->dateStamp, buffer, bufferSizeBytes)) return JAUS_FALSE;
	
	return JAUS_TRUE;
}

JausUnsignedInteger jausTimeGetTimeStamp(JausTime time)
{
	// Calculate TimeStamp
	calculateTimeStamp(time);
	
	return time->timeStamp;	
}

JausUnsignedShort jausTimeGetDateStamp(JausTime time)
{
	// Calculate DateStamp
	calculateDateStamp(time);
	
	return time->dateStamp;
}

// Private Functions
JausBoolean calculateTimeStamp(JausTime time)
{
	time->timeStamp = 0;
	time->timeStamp |= (time->millisec & JAUS_TIME_STAMP_MILLISEC_MASK) << JAUS_TIME_STAMP_MILLISEC_SHIFT;
	time->timeStamp |= (time->second & JAUS_TIME_STAMP_SECOND_MASK) << JAUS_TIME_STAMP_SECOND_SHIFT;
	time->timeStamp |= (time->minute & JAUS_TIME_STAMP_MINUTE_MASK) << JAUS_TIME_STAMP_MINUTE_SHIFT;
	time->timeStamp |= (time->hour & JAUS_TIME_STAMP_HOUR_MASK) << JAUS_TIME_STAMP_HOUR_SHIFT;
	time->timeStamp |= (time->day & JAUS_TIME_STAMP_DAY_MASK) << JAUS_TIME_STAMP_DAY_SHIFT;

	return JAUS_TRUE;
}

JausBoolean calculateDateStamp(JausTime time)
{
	time->dateStamp = 0;
	time->dateStamp |= (time->day & JAUS_DATE_STAMP_DAY_MASK) << JAUS_DATE_STAMP_DAY_SHIFT;
	time->dateStamp |= (time->month & JAUS_DATE_STAMP_MONTH_MASK) << JAUS_DATE_STAMP_MONTH_SHIFT;
	time->dateStamp |= (time->year & JAUS_DATE_STAMP_YEAR_MASK) << JAUS_DATE_STAMP_YEAR_SHIFT;
	
	return JAUS_TRUE;
}
