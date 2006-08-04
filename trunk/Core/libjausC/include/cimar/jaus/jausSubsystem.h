// File Name: jausSubsystem.h
//
// Written By: Danny Kent (jaus AT dannykent DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines all the attributes of a JausSubsystem

#ifndef JAUS_SUBSYSTEM_H
#define JAUS_SUBSYSTEM_H

#include <cimar.h>
#include "cimar/jaus.h"

#define SUBSYSTEM_TIMEOUT_SEC 5.0

typedef struct
{
	char *identification;
	int id;
	Vector nodes;
	double timestamp;
}JausSubsystemStruct;

typedef JausSubsystemStruct *JausSubsystem;

JausSubsystem jausSubsystemCreate(void);
void jausSubsystemDestroy(JausSubsystem);
JausSubsystem jausSubsystemClone(JausSubsystem);

JausBoolean jausSubsystemFreeMemory(JausSubsystem);

void jausSubsystemUpdateTimestamp(JausSubsystem);
JausBoolean jausSubsystemIsTimedOut(JausSubsystem);
int jausSubsystemToString(JausSubsystem, char *);
int jausSubsystemTableToString(JausSubsystem, char *);

#endif
