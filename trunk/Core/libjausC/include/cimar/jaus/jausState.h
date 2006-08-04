// File Name: jausState.h
//
// Written By: Danny Kent (jaus AT dannykent DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: Functionality associated with the possible states of a JAUS Component.

#ifndef JAUS_STATE_H
#define JAUS_STATE_H

typedef enum
{
	JAUS_UNDEFINED_STATE = -1,
	JAUS_UNKNOWN_STATE = -1,
	JAUS_INVALID_STATE = -1,
	JAUS_INITIALIZE_STATE = 0,
	JAUS_READY_STATE = 1,
	JAUS_STANDBY_STATE = 2,
	JAUS_SHUTDOWN_STATE = 3,
	JAUS_FAILURE_STATE = 4,
	JAUS_EMERGENCY_STATE = 5
}JausState;

int jausStateToString(JausState, char *);
char *jausStateGetString(JausState);

#endif
