// File:		node.h
//
// Version:		3.2
//
// Written by:	Tom Galluzzo (galluzzo AT gmail DOT com)
//
// Date:		08/04/06
//
// Description:	This file contains the header file code for the node level abstraction

#ifndef NODE_H
#define NODE_H

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

#define NODE_NAME_STRING			"Development" // USER: Change this to the name of your node 

#define NODE_CMPT_STARTUP_FAILED	-1

int nodeStartup(void);
int nodeShutdown(void);
const char *nodeGetName(void);

#endif // NODE_H
