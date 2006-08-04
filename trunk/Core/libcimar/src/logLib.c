// File Name: logLib.c
//
// Written By: Tom Galluzzo (galluzzo AT gmail DOT com) and Danny Kent (jaus AT dannykent DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description:	This file contains the header file code for the CIMAR loging library

#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <string.h>
#include <errno.h>

#include "cimar.h"

// Private Global Varibles
static int debugLevel = 0;
static int debugLogic = DEBUG_EQUAL_TO;

static int logVerbose = FALSE;
static FILE *logLibFile = NULL;


int cDebug(int level, char *format, ...)
{
	va_list data;
	time_t timeStamp;
	char timeString[64];
	
	//Check for Valid Debug Level
	if(level <= 0)
		return ERROR_DEBUG_INVALID_LEVEL;

	//Check Debug Logic Mode
	if(	(debugLogic == DEBUG_EQUAL_TO && level == debugLevel) ||
		(debugLogic == DEBUG_GREATER_THAN && level >= debugLevel) ||
		(debugLogic == DEBUG_LESS_THAN && level <= debugLevel))
	{
		if(logVerbose == TRUE)
		{
			//print to screen
			va_start(data, format);
			vfprintf(stdout, format, data);
			va_end(data);
			if(format[strlen(format) - 1] != '\n') printf("\n");
		}
		
		//Check for Valid File
		if(logLibFile != NULL)
		{
			//Get and Format Time String
			time(&timeStamp);
			strftime(timeString, 63, "%m-%d-%Y %X", localtime(&timeStamp));
			//print to log
			fprintf(logLibFile, "%s: ", timeString);
			va_start(data, format);
			vfprintf(logLibFile, format, data);
			va_end(data);
			if(format[strlen(format) - 1] != '\n') fprintf(logLibFile, "\n");
		}
	}
	else
	{
		return ERROR_DEBUG_INVALID_PARAMETER;
	}
	
	return 0;
}

int cLog(char *format, ...)
{
	va_list data;
	time_t timeStamp;
	char timeString[64];
	
	// Print to screen
	va_start(data, format);
	vfprintf(stdout, format, data);
	va_end(data);
	
	// Check for Valid File
	if(logLibFile != NULL)
	{
		// Get and Format Time String
		time(&timeStamp);
		strftime(timeString, 63, "%m-%d-%Y %X", localtime(&timeStamp));
		
		// Print to log
		fprintf(logLibFile, "%s: ", timeString);
		va_start(data, format);
		vfprintf(logLibFile, format, data);
		va_end(data);
	}

	return 0;
}


int cError(char *format, ...)
{
	va_list data;
	time_t timeStamp;
	char timeString[64];
	
	//Get and Format Time String
	time(&timeStamp);
	strftime(timeString, 63, "%m-%d-%Y %X", localtime(&timeStamp));

	//print to screen
	fprintf(stderr, "%s: ERROR: ", timeString);
	va_start(data, format);
	vfprintf(stderr, format, data);
	va_end(data);
	if(format[strlen(format) - 1] != '\n') printf("\n");
	
	//Check for Valid File
	if(logLibFile != NULL)
	{
		fprintf(logLibFile, "%s: ERROR: ", timeString);
		va_start(data, format);
		vfprintf(logLibFile, format, data);
		va_end(data);
		if(format[strlen(format) - 1] != '\n') fprintf(logLibFile, "\n");
	}

	return 0;
}

void pError(char *message)
{
	time_t timeStamp;
	char timeString[64];
	
	//Get and Format Time String
	time(&timeStamp);
	strftime(timeString, 63, "%m-%d-%Y %X", localtime(&timeStamp));

	if(message[strlen(message) - 1] == '\n') message[strlen(message) - 1] = 0;

	if(logVerbose == TRUE)
		fprintf(stderr, "%s: %s\n", message, strerror(errno)); //print to screen

	if(logLibFile != NULL)
		fprintf(logLibFile, "%s: %s: %s\n", timeString, message, strerror(errno));
}

int setLogVerbose(int value)
{
	if(value == TRUE || value == FALSE)
	{
		logVerbose = value;
		return 0;
	}
	else return -1;
}

int setLogFile(FILE *filePointer)
{
	logLibFile = filePointer;
	return 0;
}

int setDebugLevel(int level)
{
	debugLevel = level;
	return 0;
}

int getLogVerbose()
{
	return logVerbose;
}

int getDebugLevel()
{
	return debugLevel;
}

int setDebugLogic(int logic)
{
	//Check for valid logic state
	if(logic == DEBUG_GREATER_THAN || logic == DEBUG_EQUAL_TO || logic == DEBUG_LESS_THAN)
	{
		debugLogic = logic;
		return 0;
	}
	else return -1;
}

int getDebugLogic()
{
	return debugLogic;
}

const char *getDebugLogicString()
{
	static const char *logicString[3] = {	"Less Than",
											"Equal To",
											"Greater Than"};
	return logicString[debugLogic+1];
}
