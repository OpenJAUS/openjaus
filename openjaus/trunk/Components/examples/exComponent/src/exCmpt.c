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
// File:		exCmpt.c
// Version:		1.0
// Written by:	Danny Kent (kentd@ufl.edu)
// Date:		07/13/2006
// Description:	This file contains code to demonstrate the creation of a VSS service connection
//				This code is designed to work with the node manager and JAUS library software written by CIMAR

#include <cimar.h>
#include <cimar/jaus.h>			// JAUS message set (USER: JAUS libraries must be installed first)
#include <cimar/nodeManager.h>	// Node managment functions for sending and receiving JAUS messages (USER: Node Manager must be installed)
#include <pthread.h>			// Multi-threading functions (standard to unix)
#include <stdlib.h>	
#include <unistd.h>				// Unix standard functions
#include <string.h>
// USER: Add include files here as appropriate

#include "exCmpt.h"	// USER: Implement and rename this header file. Include prototypes for all public functions contained in this file.

// VSS Service Connection Defines
#define VSS_SC_TIMEOUT_SECONDS 		1.0		// The timeout between receiving service connection messages
#define VSS_SC_UPDATE_RATE_HZ 		10.0	// Requested service connection update rate
#define VSS_SC_PRESENCE_VECTOR 		0xFF	// Presence Vector, set this to the fields desired (default = ALL)
#define VSS_SC_QUEUE_SIZE			1		// Service Connection Manager's queue size (0 = infinite)

#define SC_CREATE_WINDOW	1.0

// Private function prototypes
void *exCmptThread(void *);
void exCmptProcessMessage(JausMessage);
void exCmptStartupState(void);
void exCmptInitState(void);
void exCmptStandbyState(void);
void exCmptReadyState(void);
void exCmptEmergencyState(void);
void exCmptFailureState(void);
void exCmptShutdownState(void);
void exCmptAllState(void);
// USER: Insert any private function prototypes here

static JausAddressStruct exCmptAddress =	{ { 0, EX_COMPONENT_ID, 0, 0} }; 
static JausAddressStruct exCmptControllerAddress =	{ { 0, 0, 0, 0} }; 
static JausComponentStruct exCmptStruct =	{	"exCmpt",
											&exCmptAddress,
											JAUS_SHUTDOWN_STATE,
											0,
											NULL,
											NULL,
											{
												&exCmptControllerAddress,
												JAUS_UNDEFINED_STATE,
												0,
												JAUS_FALSE
											},
											0,
											0.0
										}; // All component specific information is stored in this CIMAR JAUS Library data structure
static JausComponent exCmpt = &exCmptStruct;
static JausNode exCmptNode;
static JausSubsystem exCmptSubsystem;

static int exCmptRun = FALSE;
static double exCmptThreadHz = 0;									// Stores the calculated update rate for main state thread
static int exCmptThreadRunning = FALSE;
static pthread_t exCmptThreadId = 0;							// pthread component thread identifier

static Properties exCmptProperties;
static NodeManagerInterface exCmptNmi;	// A data structure containing the Node Manager Interface for this component

// VSS Service Connection Varibles
static ServiceConnection vssSc = NULL;					// vssSc handle
static ReportVelocityStateMessage reportVss = NULL;		// Incoming reportVss message structure

// Function: 	exCmptStartup
// Access:		Public	
// Description: This function allows the abstracted component functionality contained in this file to be started from an external source.
// 				It must be called first before the component state machine and node manager interaction will begin
//				Each call to "exCmptStartup" should be followed by one call to the "exCmptShutdown" function
int exCmptStartup(void)
{
	FILE * propertyFile;
	pthread_attr_t attr;	// Thread attributed for the component threads spawned in this function
	
	if(exCmpt->state == JAUS_SHUTDOWN_STATE)	// Execute the startup routines only if the component is not running
	{
		propertyFile = fopen("./config/exCmpt.conf", "r");
		if(propertyFile)
		{
			exCmptProperties = propertiesCreate();
			exCmptProperties = propertiesLoad(exCmptProperties, propertyFile);
			fclose(propertyFile);
		}
		else
		{
			cError("exCmpt: Cannot find or open properties file\n");
			return EX_CMPT_LOAD_CONFIGURATION_ERROR;
		}
		
		// Check in to the Node Manager and obtain Instance, Node and Subsystem IDs
		exCmptNode = jausNodeCreate();
		exCmptSubsystem = jausSubsystemCreate();
		exCmptNode->subsystem = exCmptSubsystem;
		exCmpt->node = exCmptNode;
		exCmpt->services = jausServicesCreate();
		exCmpt->state = JAUS_INITIALIZE_STATE; // Set the state of the JAUS state machine to INITIALIZE
		
		exCmptNmi = nodeManagerOpen(exCmpt); 
		if(exCmptNmi == NULL)
		{
			cError("exCmpt: Could not open connection to node manager\n");
			return EX_CMPT_NODE_MANAGER_OPEN_ERROR; 
		}

		pthread_attr_init(&attr);
		pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

		exCmptRun = TRUE;

		if(pthread_create(&exCmptThreadId, &attr, exCmptThread, NULL) != 0)
		{
			cError("exCmpt: Could not create exCmptThread\n");
			exCmptShutdown();
			pthread_attr_destroy(&attr);
			return EX_CMPT_THREAD_CREATE_ERROR;
		}
		pthread_attr_destroy(&attr);
	}
	else
	{
		cError("exCmpt: Attempted startup while not shutdown\n");
		return EX_CMPT_STARTUP_BEFORE_SHUTDOWN_ERROR;
	}
	
	return 0;
}

// Function: exCmptShutdown
// Access:		Public	
// Description:	This function allows the abstracted component functionality contained in this file to be stoped from an external source.
// 				If the component is in the running state, this function will terminate all threads running in this file
//				This function will also close the Jms connection to the Node Manager and check out the component from the Node Manager
int exCmptShutdown(void)
{
	double timeOutSec;

	if(exCmpt->state != JAUS_SHUTDOWN_STATE)	// Execute the shutdown routines only if the component is running
	{
		exCmptRun = FALSE;

		timeOutSec = getTimeSeconds() + EX_CMPT_THREAD_TIMEOUT_SEC;
		while(exCmptThreadRunning)
		{
			usleep(100000);
			if(getTimeSeconds() >= timeOutSec)
			{
				pthread_cancel(exCmptThreadId);
				exCmptThreadRunning = FALSE;
				cError("exCmpt: exCmptThread Shutdown Improperly\n");
				break;
			}
		}

		nodeManagerClose(exCmptNmi); // Close Node Manager Connection
				
		jausSubsystemDestroy(exCmpt->node->subsystem);
		jausNodeDestroy(exCmpt->node);
		jausServicesDestroy(exCmpt->services);
	
		exCmpt->state = JAUS_SHUTDOWN_STATE;

		propertiesDestroy(exCmptProperties);
	}

	return 0;
}

// The series of functions below allow public access to essential component information
// Access:		Public (All)
JausState exCmptGetState(void)
{
	return exCmpt->state;
}

JausAddress exCmptGetAddress(void)
{
	return exCmpt->address;
}

double exCmptGetUpdateRate(void)
{
	return exCmptThreadHz; 
}

// USER: Insert any additional public variable accessors here
ReportVelocityStateMessage exCmptGetVss(void)
{ 
	return reportVss;
}

JausBoolean exCmptGetVssScStatus(void)
{ 
	return vssSc? vssSc->isActive : JAUS_FALSE;
}

// Function: exCmptThread
// Access:		Private
// Description:	All core component functionality is contained in this thread.
//				All of the JAUS component state machine code can be found here.
void *exCmptThread(void *threadData)
{
	JausMessage rxMessage;
	double time, prevTime, nextExcecuteTime = 0.0;
	struct timespec sleepTime;

	exCmptThreadRunning = TRUE;

	sleepTime.tv_sec = 0;
	sleepTime.tv_nsec = 1000;

	time = getTimeSeconds();
	exCmpt->state = JAUS_INITIALIZE_STATE; // Set JAUS state to INITIALIZE
	
	exCmptStartupState();
		
	while(exCmptRun) // Execute state machine code while not in the SHUTDOWN state
	{
		do
		{
			if(nodeManagerReceive(exCmptNmi, &rxMessage))
			{
				cDebug(4, "EX_CMPT: Got message: %s from %d.%d.%d.%d\n", jausMessageCommandCodeString(rxMessage), rxMessage->source->subsystem, rxMessage->source->node, rxMessage->source->component, rxMessage->source->instance);
				exCmptProcessMessage(rxMessage);
			}
			else 
			{
				if(getTimeSeconds() > nextExcecuteTime)
				{
					break;
				}
				else
				{
					nanosleep(&sleepTime, NULL);
				}
			}
		}while(getTimeSeconds() < nextExcecuteTime);
		
		prevTime = time;
		time = getTimeSeconds();
		exCmptThreadHz = 1.0/(time-prevTime); // Compute the update rate of this thread
		
		switch(exCmpt->state) // Switch component behavior based on which state the machine is in
		{
			case JAUS_INITIALIZE_STATE:
				exCmptInitState();
				break;
				
			case JAUS_STANDBY_STATE:
				exCmptStandbyState();
				break;
				
			case JAUS_READY_STATE:
				exCmptReadyState();
				break;
				
			case JAUS_EMERGENCY_STATE:
				exCmptEmergencyState();
				break;
				
			case JAUS_FAILURE_STATE:
				exCmptFailureState();
				break;		
						
			case JAUS_SHUTDOWN_STATE:
				exCmptRun = FALSE;			
				break;		

			default:
				exCmpt->state = JAUS_FAILURE_STATE; // The default case JAUS_is undefined, therefore go into Failure State
				break;
		}	
		
		exCmptAllState();
		nodeManagerSendCoreServiceConnections(exCmptNmi);

		nextExcecuteTime = 2.0 * time + 1.0/EX_CMPT_THREAD_DESIRED_RATE_HZ - getTimeSeconds();
	}	
	
	exCmptShutdownState();
	
	usleep(50000);	// Sleep for 50 milliseconds and then exit

	exCmptThreadRunning = FALSE;
	
	return NULL;
}

// Function: exCmptProcessMessage
// Access:		Private
// Description:	This function is responsible for handling incoming JAUS messages from the Node Manager.
//				Incoming messages are processed according to message type.
void exCmptProcessMessage(JausMessage message)
{
	ConfirmComponentControlMessage confirmComponentControl;
	RejectComponentControlMessage rejectComponentControl;
	ReportComponentAuthorityMessage reportComponentAuthority;
	ReportComponentStatusMessage reportComponentStatus;

	// This block of code is intended to reject commands from non-controlling components
	if(exCmpt->controller.active && message->source->id != exCmpt->controller.address->id && jausMessageIsRejectableCommand(message) )
	{
		cError("exCmpt: Received command message %s from non-controlling component.\n", jausMessageCommandCodeString(message));
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
				cError("exCmpt: Error unpacking %s message.\n", jausMessageCommandCodeString(message));
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
				cError("exCmpt: Error unpacking %s message.\n", jausMessageCommandCodeString(message));
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
				cError("exCmpt: Error unpacking %s message.\n", jausMessageCommandCodeString(message));
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
				cError("exCmpt: Error unpacking %s message.\n", jausMessageCommandCodeString(message));
			}
			jausMessageDestroy(message);
			break;
		
		// This case allows the component to recieve and parse a ReportVelocityState message
		case JAUS_REPORT_VELOCITY_STATE:
			if(reportVss) reportVelocityStateMessageDestroy(reportVss);

			reportVss = reportVelocityStateMessageFromJausMessage(message);
			if(reportVss)
			{
				// USER: Determine if anything needs done upon receipt of a VSS Message
			}
			else
			{
				cError("exCmpt: Error unpacking %s message.\n", jausMessageCommandCodeString(message));
			}
			jausMessageDestroy(message);
			break;

		default:
			defaultJausMessageProcessor(message, exCmptNmi, exCmpt);
			break;
	}
}

void exCmptStartupState(void)
{
	JausService service;
	
	// Populate Core Service
	if(!jausServiceAddCoreServices(exCmpt->services))
	{
		cError("ssCmpt: Addition of Core Services FAILED! Switching to FAILURE_STATE\n");
		exCmpt->state = JAUS_FAILURE_STATE;
	}

	// Add a service to support the reciept of a ReportVelocityState message
	service = jausServiceCreate(exCmpt->address->component);
	if(!service)
	{
		cError("exComponent: Cannot create JausService! Switching to FAILURE_STATE\n");
		exCmpt->state = JAUS_FAILURE_STATE;
		return;
	}
	jausServiceAddInputCommand(service, JAUS_REPORT_VELOCITY_STATE, VSS_SC_PRESENCE_VECTOR);
	jausServiceAddService(exCmpt->services, service);
		
	// Set up VSS Service Connection handle
	vssSc = serviceConnectionCreate();
	if(vssSc)
	{
		vssSc->requestedUpdateRateHz = 	VSS_SC_UPDATE_RATE_HZ;
		vssSc->address->component = 	JAUS_VELOCITY_STATE_SENSOR;
		vssSc->presenceVector = 		VSS_SC_PRESENCE_VECTOR;
		vssSc->commandCode = 			JAUS_REPORT_VELOCITY_STATE;
		vssSc->isActive = 				JAUS_FALSE;
		vssSc->queueSize = 				VSS_SC_QUEUE_SIZE;
		vssSc->timeoutSec = 			VSS_SC_TIMEOUT_SECONDS;
	}
	else
	{
		cError("FAILURE: ssCmpt: gposSc failed to construct. Switching to FAILURE_STATE");
		exCmpt->state = JAUS_FAILURE_STATE;
		return;
	}
}

void exCmptInitState(void)
{
	// Damp the request times for the VSS Service connection to prevent network spam
	static double nextRequestTime = 0.0;
	
	if(!vssSc->isActive)
	{
		if(getTimeSeconds() > nextRequestTime)
		{	
			// Ask the scManager to create a service connection to the vss
			if(scManagerCreateServiceConnection(exCmptNmi, vssSc))
			{
				cDebug(4, "exCmpt: Sent VSS SC Request\n");
			}
					
			// USER: Add other Service connection requests here
			nextRequestTime = getTimeSeconds() + SC_CREATE_WINDOW;
		}
	}
	else
	{
		// vssSc is active, therefore transition to ready state
		exCmpt->state = JAUS_READY_STATE;
	}
}

void exCmptStandbyState(void)
{
	// USER: Insert Standby Code Here
}

void exCmptReadyState(void)
{
	JausMessage message;
	
	// Read the VSS Service Connection  info
	if(vssSc && vssSc->isActive)
	{
		if(scManagerReceiveServiceConnection(exCmptNmi, vssSc, &message))
		{
			exCmptProcessMessage(message);
		}
	}
	else
	{
		cError("VSS Service Connection Failed. Switching to EMERGENCY State.");	
		exCmpt->state = JAUS_EMERGENCY_STATE;
	}	
}

void exCmptEmergencyState(void)
{
	// Nothing to do, if in Emergency, the VssSc failed.
	// Transition back to Init where the component will wait until the VSS is active again
		exCmpt->state = JAUS_INITIALIZE_STATE;
}

void exCmptFailureState(void)
{
	// USER: Insert Failure Code Here
}

void exCmptShutdownState(void)
{
	RejectComponentControlMessage rejectComponentControl;
	JausMessage txMessage;
		
	if(exCmpt->controller.active)
	{
		// Terminate control of current component
		rejectComponentControl = rejectComponentControlMessageCreate();
		rejectComponentControl->source->id = exCmpt->address->id;
		rejectComponentControl->destination->id = exCmpt->controller.address->id;

		txMessage = rejectComponentControlMessageToJausMessage(rejectComponentControl);
		nodeManagerSend(exCmptNmi, txMessage);
		jausMessageDestroy(txMessage);

		rejectComponentControlMessageDestroy(rejectComponentControl);
	}
	
	// USER: Insert Shutdown Code Here, NOTE: Terminate any active service connections
	// Terminate VSS Service Connection
	if(vssSc)
	{
		if(vssSc->isActive)
		{
			scManagerTerminateServiceConnection(exCmptNmi, vssSc);
		}
		serviceConnectionDestroy(vssSc);	
	}
	
	// Destroy the reportVss dataStructure
	if(reportVss) reportVelocityStateMessageDestroy(reportVss);
}

void exCmptAllState(void)
{
	// USER: Insert Code Here that is Common to All states
}
