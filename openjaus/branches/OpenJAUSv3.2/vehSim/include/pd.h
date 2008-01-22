// File:		pd.h
// Version:		0.4 alpha
// Written by:	Tom Galluzzo (galluzzt@ufl.edu)
// Date:		07/01/2005
// Description:	This file contains the skeleton C header file code for implementing the pd.c file

// How To Use This File:
// All comments labled "USER:" specify lines of code that the end user must change to implement thier individual component
// The end user must also change all functions and variables in this file begining with "pd"
// This substring must be changed to the component identifier acronym of the individual component, and
// this file should also be renamed likewise
// Ex: For a Primitive Driver component change all "pd" to "pd"
// Also Change all "PD" to your component acronym (ALL CAPS)

#ifndef PD_H
#define PD_H

#include <jaus.h>

#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE 1
#endif

#define PD_LOAD_CONFIGURATION_ERROR			-1
#define PD_NODE_MANAGER_OPEN_ERROR			-2
#define PD_STARTUP_BEFORE_SHUTDOWN_ERROR	-3
#define PD_THREAD_CREATE_ERROR				-4

#define PD_THREAD_TIMEOUT_SEC				1.0
#define PD_THREAD_DESIRED_RATE_HZ			50.0	// USER: Modify this rate as needed
// USER: Insert defines here

// USER: All defines should start with "PD_", where your component acronym replaces "PD"

int pdStartup(void);
int pdShutdown(void);
JausState pdGetState(void);
JausAddress pdGetAddress(void);
double pdGetUpdateRate(void);

// USER: Insert prototypes for added public function here
JausBoolean pdGetControllerScStatus(void);
JausBoolean pdGetControllerStatus(void);
JausState pdGetControllerState(void);
JausAddress pdGetControllerAddress(void);
SetWrenchEffortMessage pdGetWrenchEffort(void);

#endif // PD_H
