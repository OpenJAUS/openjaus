// File Name: jausService.c
//
// Written By: Bob Touchton, inspired by Danny Kent
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file provides the general support functionality ReportServicesMessage

#include <stdlib.h>
#include <string.h>
#include "cimar/jaus.h"

//********************************************************//
//				Report Services Support
//********************************************************//

// Services Vector Constructor
Vector jausServicesCreate(void)
{
	Vector jausServices;
	jausServices = vectorCreate();
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
void jausServicesDestroy(Vector jausServices)
{
	vectorDestroy(jausServices, (void *)jausServiceDestroy);
}

Vector jausServicesDuplicate(Vector sourceServices)
{
	Vector destinationServices;
	JausService sourceService, destinationService;
	JausCommand sourceCommand;
	int i = 0;
	int j = 0;
	
	destinationServices = vectorCreate();
	if(!destinationServices) return NULL;
	
	for(i = 0; i < sourceServices->elementCount; i++)
	{
		sourceService = (JausService) sourceServices->elementData[i];
		destinationService = jausServiceCreate(sourceService->type);
		
		jausServiceAddService(destinationServices, destinationService);
		
		// Duplicate Input Commands from sourceService to destinationService
		for(j = 0; j < sourceService->inputJausCommands->elementCount; j++)
		{
			sourceCommand = (JausCommand) sourceService->inputJausCommands->elementData[j];			
			if(!jausServiceAddInputCommand(destinationService, sourceCommand->commandCode, sourceCommand->presenceVector))
			{
				cError("jausService: jausServicesDuplicate: Cannot add input command to duplicate\n");
				jausServicesDestroy(destinationServices);
				return NULL;
			}
		}
		
		// Duplicate Output Commands from sourceService to destinationService
		for(j = 0; j < sourceService->outputJausCommands->elementCount; j++)
		{
			sourceCommand = (JausCommand) sourceService->outputJausCommands->elementData[j];			
			if(!jausServiceAddOutputCommand(destinationService, sourceCommand->commandCode, sourceCommand->presenceVector))
			{
				cError("jausService: jausServicesDuplicate: Cannot add output command to duplicate\n");
				jausServicesDestroy(destinationServices);
				return NULL;
			}			
		}
	}
	
	return destinationServices;
}

// jausService Constructor
JausService jausServiceCreate(JausByte type)
{
	JausService service;
	service = (JausService) malloc(sizeof(JausServiceStruct));
	if(service)
	{
		service->type = type;							// Service Type (default to Core Messages)
		service->inputJausCommands = vectorCreate();	// Dynamic Array of Input Commands
		service->outputJausCommands = vectorCreate();	// Dynamic Array of Output Commands
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
	if(service)
	{
		vectorDestroy(service->inputJausCommands, (void *)jausCommandDestroy);
		vectorDestroy(service->outputJausCommands, (void *)jausCommandDestroy);
		free(service);
		service = NULL;
	}
}

// jausCommand Constructor
JausCommand jausCommandCreate(void)
{
	JausCommand command;
	
	command = (JausCommand) malloc(sizeof(JausCommandStruct));
	if(command)
	{
		command->commandCode = newJausUnsignedShort(0);				// Command Code (default to zero)
		command->presenceVector = newJausIntegerPresenceVector();	// Presence Vector
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

JausBoolean jausServiceAddCoreServices(Vector jausServices)
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
	
	// add each supported core output message
	jausServiceAddOutputCommand(service, JAUS_CREATE_SERVICE_CONNECTION, NO_PRESENCE_VECTOR);
	jausServiceAddOutputCommand(service, JAUS_CONFIRM_SERVICE_CONNECTION, NO_PRESENCE_VECTOR);
	jausServiceAddOutputCommand(service, JAUS_TERMINATE_SERVICE_CONNECTION, NO_PRESENCE_VECTOR);
	jausServiceAddOutputCommand(service, JAUS_CONFIRM_COMPONENT_CONTROL, NO_PRESENCE_VECTOR);
	jausServiceAddOutputCommand(service, JAUS_REJECT_COMPONENT_CONTROL, NO_PRESENCE_VECTOR);
	jausServiceAddOutputCommand(service, JAUS_REPORT_COMPONENT_AUTHORITY, NO_PRESENCE_VECTOR);
	jausServiceAddOutputCommand(service, JAUS_REPORT_COMPONENT_STATUS, NO_PRESENCE_VECTOR);
	
	// experimental messages handled by default
	jausServiceAddInputCommand(service, JAUS_QUERY_IDENTIFICATION, NO_PRESENCE_VECTOR);
	jausServiceAddOutputCommand(service, JAUS_REPORT_IDENTIFICATION, NO_PRESENCE_VECTOR);
	jausServiceAddInputCommand(service, JAUS_REPORT_CONFIGURATION, NO_PRESENCE_VECTOR);
	jausServiceAddOutputCommand(service, JAUS_QUERY_CONFIGURATION, NO_PRESENCE_VECTOR);
	jausServiceAddOutputCommand(service, JAUS_CONFIGURATION_CHANGED_EVENT_SETUP, NO_PRESENCE_VECTOR);
	jausServiceAddInputCommand(service, JAUS_CONFIGURATION_CHANGED_EVENT_NOTIFICATION, NO_PRESENCE_VECTOR);
	
	
	// add the service to the component's services vector
	if(jausServiceAddService(jausServices, service))
	{
		return JAUS_TRUE;
	}
	else
	{
		return JAUS_FALSE;
	}
}

/*
JausService jausServiceCreateService(JausUnsignedShort serviceType)
{
	JausService service;
	service = jausServiceCreate();
	if(service)
	{
		 service->type = serviceType;
		 return service;
	}
	else
	{
		return NULL;
	}
}
*/

JausBoolean jausServiceAddInputCommand(JausService service, JausUnsignedShort commandCode, JausIntegerPresenceVector presenceVector)
{
	JausCommand command;
	command = jausCommandCreate();
	if(command)
	{
		command->commandCode = commandCode;
		command->presenceVector = presenceVector;
		vectorAdd(service->inputJausCommands, command);
		return JAUS_TRUE;
	}
	else
	{
		return JAUS_FALSE;
	}
}

JausBoolean jausServiceAddOutputCommand(JausService service, JausUnsignedShort commandCode, JausIntegerPresenceVector presenceVector)
{
	JausCommand command;
	command = jausCommandCreate();
	if(command)
	{
		command->commandCode = commandCode;
		command->presenceVector = presenceVector;
		vectorAdd(service->outputJausCommands, command);
		return JAUS_TRUE;
	}
	else
	{
		return JAUS_FALSE;
	}	
}

JausBoolean jausServiceAddService(Vector jausServices, JausService service)
{
	if(jausServiceRetrieveService(jausServices, service->type) == NULL)
	{
		vectorAdd(jausServices, service);
		return JAUS_TRUE;
	}
	else
	{
		return JAUS_FALSE;
	}
}

JausService jausServiceRetrieveService(Vector jausServices, JausUnsignedShort serviceType)
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
