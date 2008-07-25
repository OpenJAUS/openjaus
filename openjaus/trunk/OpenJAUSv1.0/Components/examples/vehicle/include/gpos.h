// File:		gpos.h
// Version:		0.4 alpha
// Written by:	Tom Galluzzo (galluzzt@ufl.edu)
// Date:		07/01/2005
// Description:	This file contains the skeleton C header file code for implementing the gpos.c file

#ifndef GPOS_H
#define GPOS_H

#include <cimar/jaus.h>

#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE 1
#endif

#define GPOS_LOAD_CONFIGURATION_ERROR		-1
#define GPOS_NODE_MANAGER_OPEN_ERROR		-2
#define GPOS_STARTUP_BEFORE_SHUTDOWN_ERROR	-3
#define GPOS_THREAD_CREATE_ERROR			-4

#define GPOS_THREAD_TIMEOUT_SEC				1.0
#define GPOS_THREAD_DESIRED_RATE_HZ			50.0
// USER: Insert defines here

int gposStartup(void);
int gposShutdown(void);
JausState gposGetState(void);
JausAddress gposGetAddress(void);
double gposGetUpdateRate(void);
// USER: Insert prototypes for added public function here
double gposGetLatitude(void);
double gposGetLongitude(void);
double gposGetYaw(void);
int gposGetScActive(void);

#endif // GPOS_H
