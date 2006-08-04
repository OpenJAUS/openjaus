// File Name: jausNode.c
//
// Written By: Danny Kent (jaus AT dannykent DOT com), Tom Galluzzo (galluzzo AT gmail DOT com)
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

JausNode jausNodeCreate(void)
{
	JausNode node;
	
	node = (JausNode)malloc( sizeof(JausNodeStruct) );
	if(node == NULL)
	{
		return NULL;
	}
	
	//Init Values
	node->ipAddress = inetAddressCreate();
	node->ipAddress->value = 0;
	node->identification = NULL;
	node->id = 0;
	node->components = vectorCreate();
	node->subsystem = NULL;

	jausNodeUpdateTimestamp(node);

	return node;
}

void jausNodeDestroy(JausNode node)
{
	vectorDestroy(node->components, (void *)jausComponentDestroy);
	inetAddressDestroy(node->ipAddress);
	free(node);
}

JausNode jausNodeClone(JausNode node)
{
	JausNode clone;
	JausComponent tempCmpt;
	int i;
	
	clone = (JausNode)malloc( sizeof(JausNodeStruct) );
	if(clone == NULL)
	{
		return NULL;
	}
	
	//Init Values
	clone->ipAddress = inetAddressCreate();
	clone->ipAddress->value = node->ipAddress->value;
	if(node->identification)
	{
		sprintf(clone->identification, "%s", node->identification);
	}
	else
	{
		clone->identification = NULL;
	}
	clone->id = node->id;
	clone->components = vectorCreate();
	for( i = 0; i < node->components->elementCount; i++)
	{
		tempCmpt = jausComponentClone(node->components->elementData[i]);
		vectorAdd(clone->components, tempCmpt);
	}
	
	clone->subsystem = node->subsystem;

	jausNodeUpdateTimestamp(clone);

	return clone;
}

JausBoolean jausNodeFreeMemory(JausNode node)
{
	if(node->components == NULL) return JAUS_FALSE;
	
	free(node->components);
	return JAUS_TRUE;
}

void jausNodeUpdateTimestamp(JausNode node)
{
	node->timestamp = getTimeSeconds();  
}

JausBoolean jausNodeHasTimedOut(JausNode node)
{
	return (getTimeSeconds() - NODE_TIMEOUT_SEC) > node->timestamp ? JAUS_TRUE : JAUS_FALSE;
}

int jausNodeToString(JausNode node, char *buf)
{
	char ipString[16];
	
	if(node->identification)
	{
		if(node->ipAddress)
		{
			inetAddressToString(node->ipAddress, ipString); 
			return sprintf(buf, "%s-%d (IP: %s )", node->identification, node->id, ipString);
		}
		else
		{
			return sprintf(buf, "%s-%d", node->identification, node->id);
		}
	}
	else
	{
		if(node->ipAddress)
		{
			inetAddressToString(node->ipAddress, ipString); 
			return sprintf(buf, "JausNode-%d (IP: %s )", node->id, ipString);
		}
		else
		{
			return sprintf(buf, "JausNode-%d", node->id);
		}
	}
}
