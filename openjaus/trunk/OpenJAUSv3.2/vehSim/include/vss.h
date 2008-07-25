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

#define VSS_LOAD_CONFIGURATION_ERROR		-1
#define VSS_NODE_MANAGER_OPEN_ERROR			-2
#define VSS_STARTUP_BEFORE_SHUTDOWN_ERROR	-3
#define VSS_THREAD_CREATE_ERROR				-4

#define VSS_THREAD_TIMEOUT_SEC				1.0
#define VSS_THREAD_DESIRED_RATE_HZ			50.0

// USER: All defines should start with "VSS_", where your component acronym replaces "VSS"

int vssStartup(void);
int vssShutdown(void);
JausState vssGetState(void);
JausAddress vssGetAddress(void);
double vssGetUpdateRate(void);
// USER: Insert prototypes for added public function here
JausComponent vssGetComponent(void);
double vssGetVelocityX(void);
int vssGetScActive(void);

#endif // VSS_H
