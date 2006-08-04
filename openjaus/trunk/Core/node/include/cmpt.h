// File:		cmpt.h
//
// Version:		3.2
//
// Written by:	Tom Galluzzo (galluzzo AT gmail DOT com)
//
// Date:		08/04/06
//
// Description:	This file contains the skeleton C header file code for implementing the cmpt.c file

// How To Use This File:
// All comments labled "USER:" specify lines of code that the end user must change to implement thier individual component
// The end user must also change all functions and variables in this file begining with "cmpt"
// This substring must be changed to the component identifier acronym of the individual component, and
// this file should also be renamed likewise
// Ex: For a Primitive Driver component change all "cmpt" to "pd"
// Also Change all "CMPT" to your component acronym (ALL CAPS)

#ifndef CMPT_H
#define CMPT_H

#include <cimar/jaus.h>

#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE 1
#endif

#define CMPT_LOAD_CONFIGURATION_ERROR		-1
#define CMPT_NODE_MANAGER_OPEN_ERROR		-2
#define CMPT_STARTUP_BEFORE_SHUTDOWN_ERROR	-3
#define CMPT_THREAD_CREATE_ERROR			-4

#define CMPT_THREAD_TIMEOUT_SEC				1.0
#define CMPT_THREAD_DESIRED_RATE_HZ			50.0	// USER: Modify this rate as needed
// USER: Insert defines here
#define USER_COMPONENT_ID_NUMBER_HERE	254 // USER: Remove this define

// USER: All defines should start with "CMPT_", where your component acronym replaces "CMPT"

int cmptStartup(void);
int cmptShutdown(void);
JausState cmptGetState(void);
JausAddress cmptGetAddress(void);
double cmptGetUpdateRate(void);
// USER: Insert prototypes for added public function here

#endif // CMPT_H
