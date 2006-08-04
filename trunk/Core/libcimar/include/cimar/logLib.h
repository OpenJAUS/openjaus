// File Name: logLib.h
//
// Written By: Tom Galluzzo (galluzzo AT gmail DOT com) and Danny Kent (jaus AT dannykent DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description:	This file contains the header file code for the CIMAR loging library

#ifndef LOG_LIB_H
#define LOG_LIB_H

#include <stdio.h>

#define DEBUG_GREATER_THAN	1
#define DEBUG_EQUAL_TO		0
#define DEBUG_LESS_THAN		-1

#define ERROR_DEBUG_INVALID_LEVEL	-10
#define ERROR_DEBUG_FILE_NOT_SET	-11
#define ERROR_DEBUG_INVALID_PARAMETER	-12

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

int cDebug(int, char *, ...);
int cError(char *, ...);
int cLog(char *, ...);
void pError(char *);

int setLogVerbose(int);
int setDebugLevel(int);
int setDebugLogic(int);
int setLogFile(FILE *);
int getLogVerbose();
int getDebugLevel();
int getDebugLogic();
const char *getDebugLogicString();

#endif // LOG_LIB_H
