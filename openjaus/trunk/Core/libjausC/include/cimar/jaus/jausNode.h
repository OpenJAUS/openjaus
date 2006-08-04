// File Name: jausNode.h
//
// Written By: Danny Kent (jaus AT dannykent DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines all the attributes of a JausNode

#ifndef JAUS_NODE_H
#define JAUS_NODE_H

#define NODE_TIMEOUT_SEC 5.0

#include <cimar.h>
#include "cimar/jaus.h"

typedef struct
{
	char *identification;
	JausByte id;
	JausSubsystem subsystem;
	Vector components;

	InetAddress ipAddress;
	double timestamp;
}JausNodeStruct;

typedef JausNodeStruct *JausNode;

JausNode jausNodeCreate(void);
void jausNodeDestroy(JausNode);
JausNode jausNodeClone(JausNode);

JausBoolean jausNodeFreeMemory(JausNode);
void jausNodeUpdateTimestamp(JausNode);
JausBoolean jausNodeIsTimedOut(JausNode);
int jausNodeToString(JausNode, char *);

#endif //JAUS_NODE_H
