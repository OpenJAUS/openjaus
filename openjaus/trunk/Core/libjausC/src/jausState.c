// File Name: jausState.c
//
// Written By: Danny Kent (jaus AT dannykent DOT com), Tom Galluzzo (galluzzo AT gmail DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: 

#include <string.h>
#include <stdlib.h>
#include "cimar/jaus.h"

int jausStateToString(JausState state, char * buf)
{
	return sprintf(buf, "%s", jausStateGetString(state));
}

char *jausStateGetString(JausState state)
{
	static char *jausStateString[7] =	{	"Initialize",
											"Ready",
											"Standby",
											"Shutdown",
											"Failure",
											"Emergency",
											"Undefined" 
										};
	
	// If the state is unknown or out of bounds													
	if(state < JAUS_INITIALIZE_STATE || state > JAUS_EMERGENCY_STATE)
	{
		return jausStateString[6];
	}
	else
	{
		return jausStateString[state];
	}
}
