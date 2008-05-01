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
// File:		cmpt.c 
//
// Version:		3.2
//
// Written by:	Tom Galluzzo (galluzzo AT gmail DOT com) and Danny Kent (jaus AT dannykent DOT com)
//
// Date:		08/04/06
//
// Description:	This file contains the skeleton C code for implementing a JAUS component in a Linux environment
//				This code is designed to work with the node manager and JAUS library software written by CIMAR

// How To Use This File:
// All comments labled "USER:" specify lines of code that the end user must change to implement thier individual component
// The end user must also change all functions and variables in this file begining with "cmpt" (case JAUS_sensitive do not change Cmpt)
// This substring must be changed to the component identifier acronym of the individual component, and
// this file should also be renamed likewise
// Also Change all "CMPT" to your component acronym (ALL CAPS) (case JAUS_sensitive)
// The end user must also change all "USER_COMPONENT_ID_NUMBER_HERE" defines to the individual component define (see examples below)
// Ex: For a Primitive Driver component change all "cmpt" to "cmpt" and "CMPT" to "CMPT"
// Ex: For a Primitive Driver change all "USER_COMPONENT_ID_NUMBER_HERE" defines to "PRIMITIVE_DRIVER" defines
// Note that for new/experimental components, the component ID will have to be defined in the header file 
// After all changes are implemented, change the file header information at the begining of the file accordingly

#include "jaus.h"			// JAUS message set (USER: JAUS libraries must be installed first)
#include "openJaus.h"	// Node managment functions for sending and receiving JAUS messages (USER: Node Manager must be installed)
#include <pthread.h>			// Multi-threading functions (standard to unix)
#include <stdlib.h>	
#include <string.h>
#include "properties.h"

#include "cmpt.h"	// USER: Implement and rename this header file. Include prototypes for all public functions contained in this file.

#if defined (WIN32)
	#define CONFIG_DIRECTORY ".\\config\\"
#elif defined(__linux) || defined(linux) || defined(__linux__)
	#define CONFIG_DIRECTORY "./config/"
#endif

// Private function prototypes
void *cmptThread(void *);
void cmptProcessMessage(JausMessage rxMessage);
void cmptStartupState(void);
void cmptInitState(void);
void cmptStandbyState(void);
void cmptReadyState(void);
void cmptEmergencyState(void);
void cmptFailureState(void);
void cmptShutdownState(void);
void cmptAllState(void);
// USER: Insert any private function prototypes here

static JausComponent cmpt = NULL;
static JausNode cmptNode;
static JausSubsystem cmptSubsystem;

static int cmptRun = FALSE;
static double cmptThreadHz = 0;		// Stores the calculated ucmptate rate for main state thread
static int cmptThreadRunning = FALSE;
static pthread_t cmptThreadId;		// pthread component thread identifier

static Properties cmptProperties;
static NodeManagerInterface cmptNmi;	// A data structure containing the Node Manager Interface for this component

static ServiceConnection controllerStatusSc = NULL;
static SetWrenchEffortMessage setWrenchEffort = NULL;
static ReportWrenchEffortMessage reportWrenchEffort = NULL;
static SetDiscreteDevicesMessage setDiscreteDevices = NULL;

// Function: 	cmptStartup
// Access:		Public	
// Description: This function allows the abstracted component functionality contained in this file to be started from an external source.
// 				It must be called first before the component state machine and node manager interaction will begin
//				Each call to "cmptStartup" should be followed by one call to the "cmptShutdown" function
int cmptStartup(void)
{
	FILE * propertyFile;
	pthread_attr_t attr;	// Thread attributed for the component threads spawned in this function
	char fileName[128] = {0};

	if(!cmpt)
	{
		cmpt = jausComponentCreate();
		cmpt->address->component = JAUS_PRIMITIVE_DRIVER;
		cmpt->identification  = "cmpt";
		cmpt->state = JAUS_SHUTDOWN_STATE;
	}

	if(cmpt->state == JAUS_SHUTDOWN_STATE)	// Execute the startup routines only if the component is not running
	{
		sprintf(fileName, "%scmpt.conf", CONFIG_DIRECTORY);
		propertyFile = fopen(fileName, "r");
		if(propertyFile)
		{
			cmptProperties = propertiesCreate();
			cmptProperties = propertiesLoad(cmptProperties, propertyFile);
			fclose(propertyFile);
		}
		else
		{
			printf("cmpt: Cannot find or open properties file\n");
			return CMPT_LOAD_CONFIGURATION_ERROR;
		}
		
		// Check in to the Node Manager and obtain Instance, Node and Subsystem IDs
		cmptNode = jausNodeCreate();
		cmptSubsystem = jausSubsystemCreate();
		cmptNode->subsystem = cmptSubsystem;
		cmpt->node = cmptNode;
		cmpt->services = jausServicesCreate();
		cmpt->state = JAUS_INITIALIZE_STATE; // Set the state of the JAUS state machine to INITIALIZE
		
		cmptNmi = nodeManagerOpen(cmpt); 
		if(cmptNmi == NULL)
		{
			printf("cmpt: Could not open connection to node manager\n");
			return CMPT_NODE_MANAGER_OPEN_ERROR; 
		}

		pthread_attr_init(&attr);
		pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

		cmptRun = TRUE;

		if(pthread_create(&cmptThreadId, &attr, cmptThread, NULL) != 0)
		{
			//cError("cmpt: Could not create cmptThread\n");
			cmptShutdown();
			pthread_attr_destroy(&attr);
			return CMPT_THREAD_CREATE_ERROR;
		}
		pthread_attr_destroy(&attr);
	}
	else
	{
		//cError("cmpt: Attempted startup while not shutdown\n");
		return CMPT_STARTUP_BEFORE_SHUTDOWN_ERROR;
	}
	
	return 0;
}

// Function: cmptShutdown
// Access:		Public	
// Description:	This function allows the abstracted component functionality contained in this file to be stoped from an external source.
// 				If the component is in the running state, this function will terminate all threads running in this file
//				This function will also close the Jms connection to the Node Manager and check out the component from the Node Manager
int cmptShutdown(void)
{
	double timeOutSec;

	if(cmpt && cmpt->state != JAUS_SHUTDOWN_STATE)	// Execute the shutdown routines only if the component is running
	{
		cmptRun = FALSE;

		timeOutSec = getTimeSeconds() + CMPT_THREAD_TIMEOUT_SEC;
		while(cmptThreadRunning)
		{
			ojSleepMsec(100);
			if(getTimeSeconds() >= timeOutSec)
			{
				pthread_cancel(cmptThreadId);
				cmptThreadRunning = FALSE;
				//cError("cmpt: cmptThread Shutdown Improperly\n");
				break;
			}
		}

		nodeManagerClose(cmptNmi); // Close Node Manager Connection
				
		jausSubsystemDestroy(cmpt->node->subsystem);
		jausNodeDestroy(cmpt->node);
		jausServicesDestroy(cmpt->services);
	
		cmpt->state = JAUS_SHUTDOWN_STATE;

		propertiesDestroy(cmptProperties);
	}

	return 0;
}

// The series of functions below allow public access to essential component information
// Access:		Public (All)
JausState cmptGetState(void)
{
	return cmpt->state;
}

JausAddress cmptGetAddress(void)
{
	return cmpt->address;
}

double cmptGetUcmptateRate(void)
{
	return cmptThreadHz; 
}

JausBoolean cmptGetControllerScStatus(void)
{
	return controllerStatusSc ? controllerStatusSc->isActive : JAUS_FALSE;
}

JausBoolean cmptGetControllerStatus(void)
{
	return cmpt->controller.active;
}

JausState cmptGetControllerState(void)
{
	return cmpt->controller.state;
}

JausAddress cmptGetControllerAddress(void)
{
	return cmpt->controller.address;
}

SetWrenchEffortMessage cmptGetWrenchEffort(void)
{
	return setWrenchEffort;
}

// Function: cmptThread
// Access:		Private
// Description:	All core component functionality is contained in this thread.
//				All of the JAUS component state machine code can be found here.
void *cmptThread(void *threadData)
{
	JausMessage rxMessage;
	double time, prevTime, nextExcecuteTime = 0.0;

	cmptThreadRunning = TRUE;

	time = getTimeSeconds();
	cmpt->state = JAUS_INITIALIZE_STATE; // Set JAUS state to INITIALIZE
	
	cmptStartupState();
		
	while(cmptRun) // Execute state machine code while not in the SHUTDOWN state
	{
		do
		{
			if(nodeManagerReceive(cmptNmi, &rxMessage))
			{
				cmptProcessMessage(rxMessage);
			}
			else 
			{
				if(getTimeSeconds() > nextExcecuteTime)
				{
					break;
				}
				else
				{
					ojSleepMsec(1);
				}
			}
		}while(getTimeSeconds() < nextExcecuteTime);
		
		prevTime = time;
		time = getTimeSeconds();
		cmptThreadHz = 1.0/(time-prevTime); // Compute the ucmptate rate of this thread
		
		switch(cmpt->state) // Switch component behavior based on which state the machine is in
		{
			case JAUS_INITIALIZE_STATE:
				cmptInitState();
				break;
				
			case JAUS_STANDBY_STATE:
				cmptStandbyState();
				break;
				
			case JAUS_READY_STATE:
				cmptReadyState();
				break;
				
			case JAUS_EMERGENCY_STATE:
				cmptEmergencyState();
				break;
				
			case JAUS_FAILURE_STATE:
				cmptFailureState();
				break;		
						
			case JAUS_SHUTDOWN_STATE:
				cmptRun = FALSE;			
				break;		

			default:
				cmpt->state = JAUS_FAILURE_STATE; // The default case JAUS_is undefined, therefore go into Failure State
				break;
		}	
		
		cmptAllState();
		nodeManagerSendCoreServiceConnections(cmptNmi);

		nextExcecuteTime = 2.0 * time + 1.0/CMPT_THREAD_DESIRED_RATE_HZ - getTimeSeconds();
	}	
	
	cmptShutdownState();
	
	ojSleepMsec(50);	// Sleep for 50 milliseconds and then exit

	cmptThreadRunning = FALSE;
	
	return NULL;
}

// Function: cmptProcessMessage
// Access:		Private
// Description:	This function is responsible for handling incoming JAUS messages from the Node Manager.
//				Incoming messages are processed according to message type.
void cmptProcessMessage(JausMessage message)
{
	ConfirmComponentControlMessage confirmComponentControl;
	RejectComponentControlMessage rejectComponentControl;
	ReportComponentAuthorityMessage reportComponentAuthority;
	ReportComponentStatusMessage reportComponentStatus;
	char errorString[256] = {0};

	// This block of code is intended to reject commands from non-controlling components
	if(cmpt->controller.active && !jausAddressEqual(message->source, cmpt->controller.address) && jausMessageIsRejectableCommand(message) )
	{
		sprintf(errorString,"cmpt: Received command message %s from non-controlling component.\n", jausMessageCommandCodeString(message)); 
		printf(errorString);
		jausMessageDestroy(message); // Ignore this message
		return;		
	}	

	switch(message->commandCode) // Switch the processing algorithm according to the JAUS message type
	{
		case JAUS_CONFIRM_COMPONENT_CONTROL:
			confirmComponentControl = confirmComponentControlMessageFromJausMessage(message);
			if(confirmComponentControl)
			{
				// USER: Insert code here to handle the confirm component control message if needed
				confirmComponentControlMessageDestroy(confirmComponentControl);
			}
			else
			{
				sprintf(errorString,"cmpt: Error unpacking %s message.\n", jausMessageCommandCodeString(message));
				printf(errorString);
			}
			jausMessageDestroy(message);
			break;
			
		case JAUS_REJECT_COMPONENT_CONTROL:
			rejectComponentControl = rejectComponentControlMessageFromJausMessage(message);
			if(rejectComponentControl)
			{
				// USER: Insert code here to handle the reject component control message if needed
				rejectComponentControlMessageDestroy(rejectComponentControl);
			}
			else
			{
				sprintf(errorString,"cmpt: Error unpacking %s message.\n", jausMessageCommandCodeString(message));
				printf(errorString);
			}
			jausMessageDestroy(message);
			break;
			
		case JAUS_REPORT_COMPONENT_AUTHORITY:
			reportComponentAuthority = reportComponentAuthorityMessageFromJausMessage(message);
			if(reportComponentAuthority)
			{
				// USER: Insert code here to handle the report component authority message if needed
				reportComponentAuthorityMessageDestroy(reportComponentAuthority);
			}
			else
			{
				sprintf(errorString,"cmpt: Error unpacking %s message.\n", jausMessageCommandCodeString(message));
				printf(errorString);
			}
			jausMessageDestroy(message);
			break;
			
		case JAUS_REPORT_COMPONENT_STATUS:
			reportComponentStatus = reportComponentStatusMessageFromJausMessage(message);
			if(reportComponentStatus)
			{
				// USER: Insert code here to handle the report component status message if needed
				reportComponentStatusMessageDestroy(reportComponentStatus);
			}
			else
			{
				sprintf(errorString,"cmpt: Error unpacking %s message.\n", jausMessageCommandCodeString(message));
				printf(errorString);
			}
			jausMessageDestroy(message);
			break;
		
		default:
			defaultJausMessageProcessor(message, cmptNmi, cmpt);
			break;
	}
}

double cmptGetUpdateRate(void)
{
	return cmptThreadHz;
}

void cmptStartupState(void)
{
	// Populate Core Service
	if(!jausServiceAddCoreServices(cmpt->services))
	{
		printf("cmpt: Addition of Core Services FAILED! Switching to FAILURE_STATE\n");
		cmpt->state = JAUS_FAILURE_STATE;
	}
	// USER: Add the rest of your component specific service(s) here

	// USER: Insert Code Here that is only run once before the component goes to init state
}

void cmptInitState(void)
{
	// USER: Insert Init Code Here
}

void cmptStandbyState(void)
{
	// USER: Insert Standby Code Here
}

void cmptReadyState(void)
{
	// USER: Insert Ready Code Here
}

void cmptEmergencyState(void)
{
	// USER: Insert Emergency Code Here
}

void cmptFailureState(void)
{
	// USER: Insert Failure Code Here
}

void cmptShutdownState(void)
{
	RejectComponentControlMessage rejectComponentControl;
	JausMessage txMessage;
		
	if(cmpt->controller.active)
	{
		// Terminate control of current component
		rejectComponentControl = rejectComponentControlMessageCreate();
		jausAddressCopy(rejectComponentControl->source, cmpt->address);
		jausAddressCopy(rejectComponentControl->destination, cmpt->controller.address);

		txMessage = rejectComponentControlMessageToJausMessage(rejectComponentControl);
		nodeManagerSend(cmptNmi, txMessage);
		jausMessageDestroy(txMessage);

		rejectComponentControlMessageDestroy(rejectComponentControl);
	}
	
	// USER: Insert Shutdown Code Here, NOTE: Terminate any active service connections
}

void cmptAllState(void)
{
	// USER: Insert Code Here that is Common to All states
}
