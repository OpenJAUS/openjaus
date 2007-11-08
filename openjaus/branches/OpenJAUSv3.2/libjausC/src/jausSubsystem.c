/*****************************************************************************
 *  Copyright (c) 2006, University of Florida.
 *  All rights reserved.
 *  
 *  This file is part of OpenJAUS.  OpenJAUS is distributed under the BSD 
 *  license.  See the LICENSE file for details.
 * 
 *  Redistribution and use in source and binary forms, with or without 
 *  modification, are permitted provided that the following conditions 
 *  are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer in the documentation and/or other materials provided
 *       with the distribution.
 *     * Neither the name of the University of Florida nor the names of its 
 *       contributors may be used to endorse or promote products derived from 
 *       this software without specific prior written permission.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
 *   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
 *   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR 
 *   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
 *   OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, 
 *   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY 
 *   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 ****************************************************************************/
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
#include <time.h>
#include "jaus.h"

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
	subsystem->nodes = jausArrayCreate();
	jausSubsystemUpdateTimestamp(subsystem);
	
	return subsystem;
}

void jausSubsystemDestroy(JausSubsystem subsystem)
{
	jausArrayDestroy(subsystem->nodes, (void *)jausNodeDestroy);
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
		clone->identification = (char *) malloc(strlen(subsystem->identification)+1);
		sprintf(clone->identification, "%s", subsystem->identification);
	}
	else
	{
		clone->identification = NULL;
	}
	
	clone->nodes = jausArrayCreate();
	for( i = 0; i < subsystem->nodes->elementCount; i++)
	{
		tempNode = jausNodeClone(subsystem->nodes->elementData[i]);
		jausArrayAdd(clone->nodes, tempNode);
	}
	
	jausSubsystemUpdateTimestamp(clone);
	
	return clone;
}

void jausSubsystemUpdateTimestamp(JausSubsystem subsystem)
{
	time(&subsystem->timeStampSec);  
}

JausBoolean jausSubsystemIsTimedOut(JausSubsystem subsystem)
{
	time_t now;
	time(&now);

	return difftime(now, subsystem->timeStampSec) > SUBSYSTEM_TIMEOUT_SEC? JAUS_TRUE : JAUS_FALSE;
}

JausBoolean jausSubsystemFreeMemory(JausSubsystem subsystem)
{
	if(subsystem->nodes == NULL)
	{
		return JAUS_FALSE;
	}
	else
	{
		jausArrayDestroy(subsystem->nodes, free);
	}

	return JAUS_TRUE;
}

JausBoolean jausSubsystemHasIdentification(JausSubsystem subs)
{
	if(subs && subs->identification)
	{
		return JAUS_TRUE;
	}
	else
	{
		return JAUS_FALSE;
	}
}

JausBoolean jausSubsystemHasConfiguration(JausSubsystem subs)
{
	if(subs && subs->nodes->elementCount > 0)
	{
		return JAUS_TRUE;
	}
	else
	{
		return JAUS_FALSE;
	}
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
	int k = 0;
	char tempBuf[256] = {0};
	JausNode node;
	JausComponent comp;
	JausService service;
	
	jausSubsystemToString(subsystem, tempBuf);
	sprintf(buf, "%s\n", tempBuf);
	
	for(i = 0; i < subsystem->nodes->elementCount; i++)
	{
		node = (JausNode)subsystem->nodes->elementData[i];

		jausNodeToString(node, tempBuf);
		
		sprintf(buf, "%s   %s\n", buf, tempBuf);
		
		for(j = 0; j < node->components->elementCount; j++)
		{
			comp = (JausComponent)node->components->elementData[j];

			memset(tempBuf, 0, 256);
			
			jausComponentToString(comp, tempBuf);
			
			sprintf(buf, "%s      %s\n", buf, tempBuf);
		
			memset(tempBuf, 0, 256);

			sprintf(tempBuf, "         Services (%d):", comp->services->elementCount);
			for(k = 0; k < comp->services->elementCount; k++)
			{
				service = (JausService) comp->services->elementData[k];
				sprintf(tempBuf, "%s %d,", tempBuf, service->type);
			}
			strncat(buf, tempBuf, strlen(tempBuf)-1);
			sprintf(buf, "%s\n", buf);
		}
	}

	return (int)strlen(buf);
}

int jausSubsystemTableToDetailedString(JausSubsystem subsystem, char *buf)
{
	int i = 0;
	int j = 0;
	int k = 0;
	char tempBuf[256] = {0};
	JausNode node;
	JausComponent comp;
	JausService service;
	JausCommand command;

	jausSubsystemToString(subsystem, tempBuf);
	sprintf(buf, "%s\n", tempBuf);
	
	for(i = 0; i < subsystem->nodes->elementCount; i++)
	{
		node = (JausNode)subsystem->nodes->elementData[i];

		jausNodeToString(node, tempBuf);
		
		sprintf(buf, "%s   %s\n", buf, tempBuf);
		
		for(j = 0; j < node->components->elementCount; j++)
		{
			comp = (JausComponent)node->components->elementData[j];

			memset(tempBuf, 0, 256);			
			
			jausComponentToString(comp, tempBuf);
			
			sprintf(buf, "%s      %s\n", buf, tempBuf);
			for(k = 0; k < comp->services->elementCount; k++)
			{
				service = (JausService) comp->services->elementData[k];
				sprintf(buf, "%s         Service Type: %d\n", buf, service->type);
				
				sprintf(buf, "%s         INPUT:\n", buf);
				command = service->inputCommandList;
				while(command)
				{
					sprintf(buf, "%s            %s (0x%04X)\n", buf, jausCommandCodeString(command->commandCode), command->presenceVector);
					command = command->next;
				}
				
				sprintf(buf, "%s         OUTPUT:\n", buf);
				command = service->outputCommandList;
				while(command)
				{
					sprintf(buf, "%s            %s (0x%04X)\n", buf, jausCommandCodeString(command->commandCode), command->presenceVector);
					command = command->next;
				};
			}
		}
	}
	
	return (int)strlen(buf);
}
