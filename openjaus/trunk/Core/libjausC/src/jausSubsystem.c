// File Name: jausSubsystem.c
//
// Written By: Danny Kent (jaus AT dannykent DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description:

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/time.h>
#include "cimar/jaus.h"

JausSubsystem jausSubsystemCreate(void)
{
	JausSubsystem subsystem;
	
	subsystem = (JausSubsystem)malloc( sizeof(JausSubsystemStruct) );
	if(subsystem == NULL)
	{
		return NULL;
	}
	
	//Init Values
	subsystem->id = 0;
	subsystem->identification = NULL;
	subsystem->nodes = vectorCreate();
	jausSubsystemUpdateTimestamp(subsystem);
	
	return subsystem;
}

void jausSubsystemDestroy(JausSubsystem subsystem)
{
	vectorDestroy(subsystem->nodes, (void *)jausNodeDestroy);
	free(subsystem);
}

JausSubsystem jausSubsystemClone(JausSubsystem subsystem)
{
	JausSubsystem clone;
	JausNode tempNode;
	int i;
	
	clone = (JausSubsystem)malloc( sizeof(JausSubsystemStruct) );
	if(clone == NULL)
	{
		return NULL;
	}
	
	//Init Values
	clone->id = subsystem->id;
	if(subsystem->identification)
	{
		sprintf(clone->identification, "%s", subsystem->identification);
	}
	else
	{
		clone->identification = NULL;
	}
	
	clone->nodes = vectorCreate();
	for( i = 0; i < subsystem->nodes->elementCount; i++)
	{
		tempNode = jausNodeClone(subsystem->nodes->elementData[i]);
		vectorAdd(clone->nodes, tempNode);
	}
	
	jausSubsystemUpdateTimestamp(clone);
	
	return clone;
}

void jausSubsystemUpdateTimestamp(JausSubsystem subsystem)
{
	subsystem->timestamp = getTimeSeconds();  
}

JausBoolean jausSubsystemIsTimedOut(JausSubsystem subsystem)
{
	return (getTimeSeconds() - NODE_TIMEOUT_SEC) > subsystem->timestamp ? JAUS_TRUE : JAUS_FALSE;
}

JausBoolean jausSubsystemFreeMemory(JausSubsystem subsystem)
{
	if(subsystem->nodes == NULL)
	{
		return JAUS_FALSE;
	}
	else
	{
		vectorDestroy(subsystem->nodes, free);
	}

	return JAUS_TRUE;
}

int jausSubsystemToString(JausSubsystem subsystem, char *buf)
{
	if(subsystem->identification == NULL)
	{
		return sprintf(buf, "JausSubsystem-%d", subsystem->id);
	}
	else
	{
		return sprintf(buf, "%s-%d", subsystem->identification, subsystem->id);
	}
}

int jausSubsystemTableToString(JausSubsystem subsystem, char *buf)
{
	int i = 0;
	int j = 0;
	char tempBuf[256] = {0};
	JausNode node;
	JausComponent comp;
	
	jausSubsystemToString(subsystem, tempBuf);
	sprintf(buf, "%s\n", tempBuf);
	
	for(i = 0; i < subsystem->nodes->elementCount; i++)
	{
		node = (JausNode)subsystem->nodes->elementData[i];

		jausNodeToString(node, tempBuf);
		
		sprintf(buf, "%s\t%s\n", buf, tempBuf);
		
		for(j = 0; j < node->components->elementCount; j++)
		{
			comp = (JausComponent)node->components->elementData[j];

			memset(tempBuf, 0, 256);			
			
			jausComponentToString(comp, tempBuf);
			
			sprintf(buf, "%s\t\t%s\n", buf, tempBuf);
		}
	}
	
	return strlen(buf);
}

