/*****************************************************************************
 *  Copyright (c) 2006, University of Florida.
 *  All rights reserved.
 *  
 *  This file is part of OpenJAUS.  OpenJAUS is distributed under the BSD 
 *  license.  See the LICENSE file for details.
 * 
 *  Redistribution and use in source and binary forms, with or without 
 *  modification, are permitted provided that the following conditions 
 *  are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer in the documentation and/or other materials provided
 *       with the distribution.
 *     * Neither the name of the University of Florida nor the names of its 
 *       contributors may be used to endorse or promote products derived from 
 *       this software without specific prior written permission.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
 *   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
 *   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR 
 *   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
 *   OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, 
 *   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY 
 *   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 ****************************************************************************/
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
