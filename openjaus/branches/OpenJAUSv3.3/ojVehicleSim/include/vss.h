// File:		vss.h
// Version:		0.4 alpha
// Written by:	Tom Galluzzo (galluzzt@ufl.edu)
// Date:		07/01/2005
// Description:	This file contains the skeleton C header file code for implementing the vss.c file

#ifndef VSS_H
#define VSS_H

#include <jaus.h>

#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE 1
#endif

#define VSS_THREAD_DESIRED_RATE_HZ			50.0

// USER: All defines should start with "VSS_", where your component acronym replaces "VSS"

OjCmpt vssCreate(void);
void vssDestroy(OjCmpt vss);

// USER: Insert prototypes for added public function here
double vssGetVelocityX(OjCmpt vss);
int vssGetScActive(OjCmpt vss);

#endif // VSS_H
