/*****************************************************************************
 *  Copyright (c) 2008, University of Florida
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
// File Name: jausService.c
//
// Written By: Bob Touchton, inspired by Danny Kent
//
// Version: 3.3.0a
//
// Date: 08/07/08
//
// Description: This file provides the general support functionality ReportServicesMessage

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jaus.h"

//********************************************************//
//				Report Services Support
//********************************************************//

// Services Vector Constructor
JausArray jausServicesCreate(void)
{
	JausArray jausServices;
	jausServices = jausArrayCreate();
	if(jausServices)
	{
		return jausServices;
	}
	else
	{
		return NULL;
	}
}

// Services Vector Destructor
void jausServicesDestroy(JausArray jausServices)
{
	jausArrayDestroy(jausServices, (void *)jausServiceDestroy);
}

JausArray jausServicesClone(JausArray sourceServices)
{
	JausArray destinationServices;
	JausService sourceService, destinationService;
	JausCommand sourceCommand;
	int i = 0;
	
	destinationServices = jausArrayCreate();
	if(!destinationServices) return NULL;
	
	for(i = 0; i < sourceServices->elementCount; i++)
	{
		sourceService = (JausService) sourceServices->elementData[i];
		destinationService = jausServiceCreate(sourceService->type);
		
		jausServiceAddService(destinationServices, destinationService);
		
		// Duplicate Input Commands from sourceService to destinationService
		sourceCommand = sourceService->inputCommandList;			
		while(sourceCommand)
		{
			if(!jausServiceAddInputCommand(destinationService, sourceCommand->commandCode, sourceCommand->presenceVector))
			{
				jausServicesDestroy(destinationServices);
				return NULL;
			}
			sourceCommand = sourceCommand->next;
		}
		
		// Duplicate Output Commands from sourceService to destinationService
		sourceCommand = sourceService->outputCommandList;			
		while(sourceCommand)
		{
			if(!jausServiceAddOutputCommand(destinationService, sourceCommand->commandCode, sourceCommand->presenceVector))
			{
				jausServicesDestroy(destinationServices);
				return NULL;
			}			
			sourceCommand = sourceCommand->next;
		}
	}
	
	return destinationServices;
}

// jausService Constructor
JausService jausServiceCreate(JausUnsignedShort type)
{
	JausService service;
	service = (JausService) malloc(sizeof(struct JausServiceStruct));
	if(service)
	{
		service->type = type;				// Service Type (default to Core Messages)
		service->inputCommandList = NULL;	// List of Input Commands
		service->inputCommandCount = 0;
		service->outputCommandList = NULL;	// List of Output Commands
		service->outputCommandCount = 0;
		service->next = NULL;
		
		return service;
	}
	else
	{
		return NULL;
	}
}

// jausService Destructor
void jausServiceDestroy(JausService service)
{
	JausCommand tempCommand;
	
	if(service)
	{
		while(service->inputCommandList)
		{
			tempCommand = service->inputCommandList;
			service->inputCommandList = tempCommand->next;
			jausCommandDestroy(tempCommand);
		};

		while(service->outputCommandList)
		{
			tempCommand = service->outputCommandList;
			service->outputCommandList = tempCommand->next;
			jausCommandDestroy(tempCommand);
		};
		
		free(service);
		service = NULL;
	}
}

// jausCommand Constructor
JausCommand jausCommandCreate(void)
{
	JausCommand command;
	
	command = (JausCommand) malloc(sizeof(struct JausCommandStruct));
	if(command)
	{
		command->commandCode = newJausUnsignedShort(0);				// Command Code (default to zero)
		command->presenceVector = newJausUnsignedInteger(JAUS_INTEGER_PRESENCE_VECTOR_ALL_ON);	// Presence Vector
		return command;
	}
	else
	{
		return NULL;
	}
}

// jausCommand Destructor
void jausCommandDestroy(JausCommand command)
{
	if(command)
	{
		free(command);
		command = NULL;
	}
}

// ************************************************************************************************************************************
//			Report Services End User Functions
// ************************************************************************************************************************************

// Use this function to blast the default core services into the jausServices structure
// NOTE: This only adds those command codes that are explicitly coded into the core libraries and cmpt.c by default.  
//       Users will need to add any additional core messages that they handle, e.g.:
//  	     service = jausServiceRetrieveService(jausServices, CORE_MESSAGE_SUPPORT);
//	    	 jausServiceAddInputCommand(service, JAUS_SOME_OTHER_CORE_MESSAGE, SOME_PRESENCE_VECTOR);

JausBoolean jausServiceAddCoreServices(JausArray jausServices)
{
	JausService service;
	
	// create a new service for core message support
	service = jausServiceCreate(CORE_MESSAGE_SUPPORT);
	
	// add each supported core input message 
	jausServiceAddInputCommand(service, JAUS_SET_COMPONENT_AUTHORITY, NO_PRESENCE_VECTOR);
	jausServiceAddInputCommand(service, JAUS_SHUTDOWN, NO_PRESENCE_VECTOR);
	jausServiceAddInputCommand(service, JAUS_STANDBY, NO_PRESENCE_VECTOR);
	jausServiceAddInputCommand(service, JAUS_RESUME, NO_PRESENCE_VECTOR);
	jausServiceAddInputCommand(service, JAUS_RESET, NO_PRESENCE_VECTOR);
	jausServiceAddInputCommand(service, JAUS_SET_EMERGENCY, NO_PRESENCE_VECTOR);
	jausServiceAddInputCommand(service, JAUS_CLEAR_EMERGENCY, NO_PRESENCE_VECTOR);
	jausServiceAddInputCommand(service, JAUS_CREATE_SERVICE_CONNECTION, NO_PRESENCE_VECTOR);
	jausServiceAddInputCommand(service, JAUS_CONFIRM_SERVICE_CONNECTION, NO_PRESENCE_VECTOR);
	jausServiceAddInputCommand(service, JAUS_ACTIVATE_SERVICE_CONNECTION, NO_PRESENCE_VECTOR);
	jausServiceAddInputCommand(service, JAUS_SUSPEND_SERVICE_CONNECTION, NO_PRESENCE_VECTOR);
	jausServiceAddInputCommand(service, JAUS_TERMINATE_SERVICE_CONNECTION, NO_PRESENCE_VECTOR);
	jausServiceAddInputCommand(service, JAUS_REQUEST_COMPONENT_CONTROL, NO_PRESENCE_VECTOR);
	jausServiceAddInputCommand(service, JAUS_RELEASE_COMPONENT_CONTROL, NO_PRESENCE_VECTOR);
	jausServiceAddInputCommand(service, JAUS_CONFIRM_COMPONENT_CONTROL, NO_PRESENCE_VECTOR);
	jausServiceAddInputCommand(service, JAUS_REJECT_COMPONENT_CONTROL, NO_PRESENCE_VECTOR);
//	jausServiceAddInputCommand(service, JAUS_SET_TIME, 0xFF);
	jausServiceAddInputCommand(service, JAUS_QUERY_COMPONENT_AUTHORITY, NO_PRESENCE_VECTOR);
	jausServiceAddInputCommand(service, JAUS_QUERY_COMPONENT_STATUS, NO_PRESENCE_VECTOR);
//	jausServiceAddInputCommand(service, JAUS_QUERY_TIME, 0xFF);
	jausServiceAddInputCommand(service, JAUS_REPORT_COMPONENT_AUTHORITY, NO_PRESENCE_VECTOR);
	jausServiceAddInputCommand(service, JAUS_REPORT_COMPONENT_STATUS, NO_PRESENCE_VECTOR);
//	jausServiceAddInputCommand(service, JAUS_REPORT_TIME, 0xFF);
	jausServiceAddInputCommand(service, JAUS_QUERY_IDENTIFICATION, NO_PRESENCE_VECTOR);
	jausServiceAddInputCommand(service, JAUS_REPORT_CONFIGURATION, NO_PRESENCE_VECTOR);
	jausServiceAddInputCommand(service, JAUS_REPORT_SERVICES, NO_PRESENCE_VECTOR);
	
	// add each supported core output message
	jausServiceAddOutputCommand(service, JAUS_CREATE_SERVICE_CONNECTION, NO_PRESENCE_VECTOR);
	jausServiceAddOutputCommand(service, JAUS_CONFIRM_SERVICE_CONNECTION, NO_PRESENCE_VECTOR);
	jausServiceAddOutputCommand(service, JAUS_TERMINATE_SERVICE_CONNECTION, NO_PRESENCE_VECTOR);
	jausServiceAddOutputCommand(service, JAUS_CONFIRM_COMPONENT_CONTROL, NO_PRESENCE_VECTOR);
	jausServiceAddOutputCommand(service, JAUS_REJECT_COMPONENT_CONTROL, NO_PRESENCE_VECTOR);
	jausServiceAddOutputCommand(service, JAUS_REPORT_COMPONENT_AUTHORITY, NO_PRESENCE_VECTOR);
	jausServiceAddOutputCommand(service, JAUS_REPORT_COMPONENT_STATUS, NO_PRESENCE_VECTOR);
	jausServiceAddOutputCommand(service, JAUS_REPORT_IDENTIFICATION, NO_PRESENCE_VECTOR);
	jausServiceAddOutputCommand(service, JAUS_QUERY_CONFIGURATION, NO_PRESENCE_VECTOR);
	jausServiceAddOutputCommand(service, JAUS_QUERY_SERVICES, NO_PRESENCE_VECTOR);
	
	// add the service to the component's services jausArray
	if(jausServiceAddService(jausServices, service))
	{
		return JAUS_TRUE;
	}
	else
	{
		return JAUS_FALSE;
	}
}

JausBoolean jausServiceAddInputCommand(JausService service, JausUnsignedShort commandCode, JausUnsignedInteger presenceVector)
{
	JausCommand command;
	JausCommand tempCommand;
	
	command = jausCommandCreate();
	if(command && service && service->inputCommandCount < JAUS_BYTE_MAX_VALUE)
	{
		command->commandCode = commandCode;
		command->presenceVector = presenceVector;
		command->next = NULL;
		
		if(service->inputCommandList)
		{
			tempCommand = service->inputCommandList;
			while(tempCommand->next)
			{
				tempCommand = tempCommand->next;
			}
			tempCommand->next = command;			
		}
		else
		{
			service->inputCommandList = command;
		}
		service->inputCommandCount++;
		
		return JAUS_TRUE;
	}
	else
	{
		return JAUS_FALSE;
	}
}

JausBoolean jausServiceAddOutputCommand(JausService service, JausUnsignedShort commandCode, JausUnsignedInteger presenceVector)
{
	JausCommand command;
	JausCommand tempCommand;

	command = jausCommandCreate();
	if(command && service && service->outputCommandCount < JAUS_BYTE_MAX_VALUE)
	{
		command->commandCode = commandCode;
		command->presenceVector = presenceVector;
		command->next = NULL;

		if(service->outputCommandList)
		{
			tempCommand = service->outputCommandList;
			while(tempCommand->next)
			{
				tempCommand = tempCommand->next;
			}
			tempCommand->next = command;			
		}
		else
		{
			service->outputCommandList = command;
		}
		service->outputCommandCount++;

		return JAUS_TRUE;
	}
	else
	{
		return JAUS_FALSE;
	}	
}

JausBoolean jausServiceAddService(JausArray jausServices, JausService service)
{
	if(jausServiceRetrieveService(jausServices, service->type) == NULL)
	{
		jausArrayAdd(jausServices, service);
		return JAUS_TRUE;
	}
	else
	{
		return JAUS_FALSE;
	}
}

JausService jausServiceRetrieveService(JausArray jausServices, JausUnsignedShort serviceType)
{
	// iterate thru jausServices until a match is found with serviceType. return matching service, else NULL
	int i = 0;
	JausService candidateService;
	for(i = 0; i < jausServices->elementCount; i++)
	{
		candidateService = (JausService) jausServices->elementData[i];
		if(candidateService->type == serviceType)
		{
			return candidateService;
		}
	}
	return NULL;
}


char* jausCommandToString(JausCommand command)
{
  char* buffer = (char*)malloc(sizeof(char)*300);
  
  if(command)
    sprintf(buffer, "Command Code: 0X%X %s  Presence Vector: 0X%X", command->commandCode, jausCommandCodeString(command->commandCode), command->presenceVector);
  else
    strcpy(buffer, "No Jaus Command");
  
  return buffer;
}

char* jausServicesToString(JausArray services)
{
  char* buffer = (char*)malloc(sizeof(char)*3000);
  int serv = 0;
  int cmd = 0;
  JausCommand tmpCommand = NULL;

  if(services->elementCount > 0)
  {
    for(serv=0; serv<services->elementCount; serv++)
    {
      strcpy(buffer, "Type: ");
      jausUnsignedShortToString(((JausService)(services->elementData[serv]))->type, buffer+strlen(buffer));
      switch(((JausService)(services->elementData[serv]))->type)
      {
        case 0:
          strcat(buffer, " Core Message Support");
          break;
          
        case 32:
          strcat(buffer, " Subsystem Commander");
          break;
          
        case 33:
          strcat(buffer, " Primitive Driver");
          break;
          
        case 34:
          strcat(buffer, " Global Vector Driver");
          break;
          
        case 35:
          strcat(buffer, " Communicator");
          break;
          
        case 37:
          strcat(buffer, " Visual Sensor");
          break;
          
        case 38:
          strcat(buffer, " Global Pose Sensor");
          break;
          
        case 40:
          strcat(buffer, " System Commander");
          break;
          
        case 41:
          strcat(buffer, " Local Pose Sensor");
          break;
          
        case 42:
          strcat(buffer, " Velocity State Sensor");
          break;
          
        case 43:
          strcat(buffer, " Reflexive Driver");
          break;
          
        case 44:
          strcat(buffer, " Local Vector Driver");
          break;
          
        case 45:
          strcat(buffer, " Global Waypoint Driver");
          break;
          
        case 46:
          strcat(buffer, " Local Waypoint Driver");
          break;
          
        case 47:
          strcat(buffer, " Global Path Segment Driver");
          break;
          
        case 48:
          strcat(buffer, " Local Path Segment Driver");
          break;
          
        case 49:
          strcat(buffer, " Primitive Manipulator");
          break;
          
        case 50:
          strcat(buffer, " Range Sensor");
          break;
          
        case 51:
          strcat(buffer, " Manipulator Joint Position Sensor");
          break;
          
        case 52:
          strcat(buffer, " Manipulator Joint Velocity Sensor");
          break;
          
        case 53:
          strcat(buffer, " Manipulator Joint Force/Torque Sensor");
          break;
          
        case 54: 
          strcat(buffer, " Manipulator Joint Positions Driver");
          break;
          
        case 55:
          strcat(buffer, " Manipulator End-Effector Pose Driver");
          break;
          
        case 56:
          strcat(buffer, " Manipulator Joint Velocities Driver");
          break;
          
        case 57:
          strcat(buffer, " Manipulator End-Effector Velocity State Driver");
          break;
          
        case 58:
          strcat(buffer, " Manipulator Joint Move Driver");
          break;
          
        case 59:
          strcat(buffer, " Manipulator End-Effector Discrete Pose Driver");
          break;
      }
      
      strcat(buffer, "\nInput Command List: Count:");
      jausByteToString(((JausService)(services->elementData[serv]))->inputCommandCount, buffer+strlen(buffer));
      
      if(((JausService)(services->elementData[serv]))->inputCommandCount == 0)
        strcat(buffer, " No Input Commands");
      else
      {
        JausCommand tmpCmd = ((JausService)(services->elementData[serv]))->inputCommandList;
        for(cmd=0; cmd<((JausService)(services->elementData[serv]))->inputCommandCount ;cmd++)
        {
          strcat(buffer, "\n");
          strcat(buffer, jausCommandToString(tmpCmd));
          tmpCmd = tmpCmd->next;
        }
      }
      
      strcat(buffer, "\nOutput Command List: Count:");
      jausByteToString(((JausService)(services->elementData[serv]))->outputCommandCount, buffer+strlen(buffer));
      
      if(((JausService)(services->elementData[serv]))->outputCommandCount == 0)
        strcat(buffer, " No Output Commands");
      else
      {
        tmpCommand = ((JausService)(services->elementData[serv]))->outputCommandList;
        for(cmd=0; cmd<((JausService)(services->elementData[serv]))->outputCommandCount ;cmd++)
        {
          strcat(buffer, "\n");
          strcat(buffer, jausCommandToString(tmpCommand));
          tmpCommand = tmpCommand->next;
        }
      }
    }
  }
  else
    strcpy(buffer, " No Services");
  
  return buffer;
}
