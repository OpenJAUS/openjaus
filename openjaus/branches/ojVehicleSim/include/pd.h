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
#include <openJaus.h>

#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE 1
#endif

#define PD_THREAD_DESIRED_RATE_HZ			50.0	// USER: Modify this rate as needed

// USER: All defines should start with "PD_", where your component acronym replaces "PD"

OjCmpt pdCreate(void);
void pdDestroy(OjCmpt pd);
JausState pdGetState(OjCmpt pd);
JausAddress pdGetAddress(OjCmpt pd);
double pdGetUpdateRate(OjCmpt pd);

// USER: Insert prototypes for added public function here
JausBoolean pdGetControllerScStatus(OjCmpt pd);
JausBoolean pdGetControllerStatus(OjCmpt pd);
JausState pdGetControllerState(OjCmpt pd);
JausAddress pdGetControllerAddress(OjCmpt pd);
SetWrenchEffortMessage pdGetWrenchEffort(OjCmpt pd);

#endif // PD_H
