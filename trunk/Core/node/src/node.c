// File:		node.c 
//
// Version:		3.2
//
// Written by:	Tom Galluzzo (galluzzo AT gmail DOT com)
//
// Date:		08/04/06
//
// Description:	This file contains the skeleton C code for implementing a JAUS node in a Linux environment

#include <cimar.h>
#include "cmpt.h"
#include "node.h"

int nodeStartup(void)
{
	// USER: Rename cmpt to your individual component
	if(cmptStartup())
	{
		cError("node: cmptStartup failed\n");
		nodeShutdown();
		
		return NODE_CMPT_STARTUP_FAILED;	
	}
	
	return 0;
}

int nodeShutdown(void)
{
	cmptShutdown();
	
	return 0;
}

const char *nodeGetName(void)
{
	static const char *nodeName = NODE_NAME_STRING;
	
	return nodeName;	
}
