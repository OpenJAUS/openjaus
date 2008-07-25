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
 // File:		vss.c 
// Version:		1.0
// Written by:	Danny Kent (jaus AT dannykent DOT com)
// Date:		08/05/2006
// Description:	This file contains a sample implementation of a Velocity State Sensor based on an RDDF file.
//				This code is designed to work with the node manager and JAUS library software written by CIMAR

#include <cimar.h>
#include <cimar/jaus.h>			// JAUS message set (USER: JAUS libraries must be installed first)
#include <cimar/nodeManager.h>	// Node managment functions for sending and receiving JAUS messages (USER: Node Manager must be installed)
#include <pthread.h>			// Multi-threading functions (standard to unix)
#include <stdlib.h>	
#include <unistd.h>				// Unix standard functions
#include <string.h>
// USER: Add include files here as appropriate
#include "vss.h"	
#include "posConstants.h"
#include "rddf.h"

// Private function prototypes
void *vssThread(void *);
void vssProcessMessage(JausMessage);
void vssStartupState(void);
void vssInitState(void);
void vssStandbyState(void);
void vssReadyState(void);
void vssEmergencyState(void);
void vssFailureState(void);
void vssShutdownState(void);
void vssAllState(void);
// USER: Insert any private function prototypes here

// Following are static initalizers for the JausComponent structure
static JausAddressStruct vssAddress =	{ { 0, JAUS_VELOCITY_STATE_SENSOR, 0, 0} }; 
static JausAddressStruct vssControllerAddress =	{ { 0 } }; 
static JausComponentStruct vssStruct =	{	"VSS Simulator",
											&vssAddress,
											JAUS_SHUTDOWN_STATE,
											0,
											NULL,
											NULL,
											{
												&vssControllerAddress,
												JAUS_UNDEFINED_STATE,
												0,
												JAUS_FALSE
											},
											0,
											0.0
										}; // All component specific information is stored in this CIMAR JAUS Library data structure
static JausComponent vss = &vssStruct;
static JausNode vssNode;
static JausSubsystem vssSubsystem;

static int vssRun = FALSE;					// Thread Control
static int vssThreadRunning = FALSE;		// Thread Control
static double vssThreadHz = 0;				// Stores the calculated update rate for main state thread
static pthread_t vssThreadId = 0;			// pthread component thread identifier

static Properties vssProperties;			// Handle to the properties structure which is read from the gpos.conf file
static NodeManagerInterface vssNmi;			// A data structure containing the Node Manager Interface for this component

// VSS Varibles
static ReportVelocityStateMessage vssMessage;	// ReportVelocityStateMessage which will be used to send messages and store the current state
int vssRunPauseFlag = VSS_PAUSE_MODE;			// Run / Pause switch to allow the starting and stopping of the simulator

// Function: 	vssStartup
// Access:		Public	
// Description: This function allows the abstracted component functionality contained in this file to be started from an external source.
// 				It must be called first before the component state machine and node manager interaction will begin
//				Each call to "vssStartup" should be followed by one call to the "vssShutdown" function
int vssStartup(void)
{
	FILE * propertyFile;
	pthread_attr_t attr;	// Thread attributed for the component threads spawned in this function
	
	if(vss->state == JAUS_SHUTDOWN_STATE)	// Execute the startup routines only if the component is not running
	{
		propertyFile = fopen("./config/vss.conf", "r");
		if(propertyFile)
		{
			vssProperties = propertiesCreate();
			vssProperties = propertiesLoad(vssProperties, propertyFile);
			fclose(propertyFile);
		}
		else
		{
			cError("vss: Cannot find or open properties file\n");
			return VSS_LOAD_CONFIGURATION_ERROR;
		}
		
		// Check in to the Node Manager and obtain Instance, Node and Subsystem IDs
		vssNode = jausNodeCreate();
		vssSubsystem = jausSubsystemCreate();
		vssNode->subsystem = vssSubsystem;
		vss->node = vssNode;
		vss->services = jausServicesCreate();
		
		vssNmi = nodeManagerOpen(vss); 
		if(vssNmi == NULL)
		{
			cError("vss: Could not open connection to node manager\n");
			return VSS_NODE_MANAGER_OPEN_ERROR; 
		}

		pthread_attr_init(&attr);
		pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

		vss->state = JAUS_INITIALIZE_STATE; // Set the state of the JAUS state machine to INITIALIZE
		vssRun = TRUE;

		if(pthread_create(&vssThreadId, &attr, vssThread, NULL) != 0)
		{
			cError("vss: Could not create vssThread\n");
			vssShutdown();
			pthread_attr_destroy(&attr);
			return VSS_THREAD_CREATE_ERROR;
		}
		pthread_attr_destroy(&attr);
	}
	else
	{
		cError("vss: Attempted startup while not shutdown\n");
		return VSS_STARTUP_BEFORE_SHUTDOWN_ERROR;
	}
	
	return 0;
}

// Function: vssShutdown
// Access:		Public	
// Description:	This function allows the abstracted component functionality contained in this file to be stoped from an external source.
// 				If the component is in the running state, this function will terminate all threads running in this file
//				This function will also close the Jms connection to the Node Manager and check out the component from the Node Manager
int vssShutdown(void)
{
	double timeOutSec;

	if(vss->state != JAUS_SHUTDOWN_STATE)	// Execute the shutdown routines only if the component is running
	{
		vssRun = FALSE;

		timeOutSec = getTimeSeconds() + VSS_THREAD_TIMEOUT_SEC;
		while(vssThreadRunning)
		{
			usleep(100000);
			if(getTimeSeconds() >= timeOutSec)
			{
				pthread_cancel(vssThreadId);
				vssThreadRunning = FALSE;
				cError("vss: vssThread Shutdown Improperly\n");
				break;
			}
		}

		nodeManagerClose(vssNmi); // Close Node Manager Connection
		
		jausSubsystemDestroy(vss->node->subsystem);
		jausNodeDestroy(vss->node);

		vss->state = JAUS_SHUTDOWN_STATE;
		jausServicesDestroy(vss->services);

		propertiesDestroy(vssProperties);
	}

	return 0;
}

// The series of functions below allow public access to essential component information
// Access:		Public (All)
JausState vssGetState(void)
{
	return vss->state;
}

JausAddress vssGetAddress(void)
{
	return vss->address;
}

double vssGetUpdateRate(void)
{
	return vssThreadHz; 
}

// USER: Insert any additional public variable accessors here
// Returns the current velocity
double vssGetSpeed(void)
{ 
	return vssMessage? vssMessage->velocityXMps : 0.0; 
}

// Returns true if the VSS Service Connection is active
int vssGetScActive(void)
{ 
	return scManagerQueryActiveMessage(vssNmi, JAUS_REPORT_VELOCITY_STATE);
}

// Method to set the current speed of the VSS
int vssSetSpeedMph(double vel)
{
	if(vssMessage)
	{	
		vssMessage->velocityXMps = vel * MPH_TO_MPS;
	//	vssDataValidity = TRUE;
		return 0;
	}
	else
		return -1;
}

// Returns the state of the RunPause flag
int vssGetRunPause()
{
	return vssRunPauseFlag;
}

// Toggle Run/Pause
void vssToggleRunPause()
{
	vssRunPauseFlag = !vssRunPauseFlag;
}

// Set Run/Pause
void vssSetRunPause(int rp)
{
	vssRunPauseFlag = rp;
}

// Function: vssThread
// Access:		Private
// Description:	All core component functionality is contained in this thread.
//				All of the JAUS component state machine code can be found here.
void *vssThread(void *threadData)
{
	JausMessage rxMessage;
	double time, prevTime, nextExcecuteTime = 0.0;
	struct timespec sleepTime;

	vssThreadRunning = TRUE;

	sleepTime.tv_sec = 0;
	sleepTime.tv_nsec = 1000;

	time = getTimeSeconds();
	vss->state = JAUS_INITIALIZE_STATE; // Set JAUS state to INITIALIZE
	
	vssStartupState();
		
	while(vssRun) // Execute state machine code while not in the SHUTDOWN state
	{
		do
		{
			if(nodeManagerReceive(vssNmi, &rxMessage))
			{
				cDebug(4, "VSS: Got message: %s\n", jausMessageCommandCodeString(rxMessage));
				vssProcessMessage(rxMessage);
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
		vssThreadHz = 1.0/(time-prevTime); // Compute the update rate of this thread
		
		switch(vss->state) // Switch component behavior based on which state the machine is in
		{
			case JAUS_INITIALIZE_STATE:
				vssInitState();
				break;
				
			case JAUS_STANDBY_STATE:
				vssStandbyState();
				break;
				
			case JAUS_READY_STATE:
				vssReadyState();
				break;
				
			case JAUS_EMERGENCY_STATE:
				vssEmergencyState();
				break;
				
			case JAUS_FAILURE_STATE:
				vssFailureState();
				break;		
						
			case JAUS_SHUTDOWN_STATE:
				vssRun = FALSE;			
				break;		

			default:
				vss->state = JAUS_FAILURE_STATE; // The default case JAUS_is undefined, therefore go into Failure State
				break;
		}	
		
		vssAllState();

		nextExcecuteTime = 2.0 * time + 1.0/VSS_THREAD_DESIRED_RATE_HZ - getTimeSeconds();
	}	
	
	vssShutdownState();
	
	usleep(50000);	// Sleep for 50 milliseconds and then exit

	vssThreadRunning = FALSE;
	
	return NULL;
}

// Function: vssProcessMessage
// Access:		Private
// Description:	This function is responsible for handling incoming JAUS messages from the Node Manager.
//				Incoming messages are processed according to message type.
void vssProcessMessage(JausMessage message)
{
	JausMessage txMessage;
	ConfirmComponentControlMessage confirmComponentControl;
	RejectComponentControlMessage rejectComponentControl;
	ReportComponentAuthorityMessage reportComponentAuthority;
	ReportComponentStatusMessage reportComponentStatus;
	QueryVelocityStateMessage queryVss;

	// This block of code is intended to reject commands from non-controlling components
	// However, the one exception allowed is a REQUEST_COMPONENT_CONTROL
	if(vss->controller.active && message->commandCode < 0x2000) // If not currently under control or it's not a command, then go to the switch statement
	{
		// If the source component isn't the one in control, and it's not a request to gain control, then exit this iteration of the while loop
		if(vss->controller.address->id != message->source->id && message->commandCode != JAUS_REQUEST_COMPONENT_CONTROL)
		{
			cError("DefaultMessageProcessor: Received Command Message from Non-controling Component\n");
			jausMessageDestroy(message);
			return; // Ignore this message
		}
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
				cError("vss: Error unpacking %s message.\n", jausMessageCommandCodeString(message));
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
				cError("vss: Error unpacking %s message.\n", jausMessageCommandCodeString(message));
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
				cError("vss: Error unpacking %s message.\n", jausMessageCommandCodeString(message));
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
				cError("vss: Error unpacking %s message.\n", jausMessageCommandCodeString(message));
			}
			jausMessageDestroy(message);
			break;
		
		case JAUS_QUERY_VELOCITY_STATE:
			queryVss = queryVelocityStateMessageFromJausMessage(message);
			if(queryVss)
			{
				if(queryVss->scFlag == JAUS_SERVICE_CONNECTION_MESSAGE)
				{
					// Service Connection Query
					vssMessage->scFlag = JAUS_SERVICE_CONNECTION_MESSAGE;
					vssMessage->sequenceNumber = message->sequenceNumber;
				}
				else
				{
					// Non SC Query
					vssMessage->scFlag = JAUS_NOT_SERVICE_CONNECTION_MESSAGE;
					vssMessage->sequenceNumber = 0;					
				}
				vssMessage->destination->id = queryVss->source->id;
				vssMessage->presenceVector = queryVss->presenceVector;			
				
				txMessage = reportVelocityStateMessageToJausMessage(vssMessage);	
				nodeManagerSend(vssNmi, txMessage);
				jausMessageDestroy(txMessage);
				queryVelocityStateMessageDestroy(queryVss);
			}
			else
			{
				cError("gpos: Error unpacking %s message.\n", jausMessageCommandCodeString(message));
			}
			jausMessageDestroy(message);
			break;		
		
		default:
			defaultJausMessageProcessor(message, vssNmi, vss);
			break;
	}
}

void vssStartupState(void)
{
	JausService service;
	// Populate Core Service
	if(!jausServiceAddCoreServices(vss->services))
	{
		cError("vss: Addition of Core Services FAILED! Switching to FAILURE_STATE\n");
		vss->state = JAUS_FAILURE_STATE;
	}

	// Add a new service to support the VSS input and output messages
	service = jausServiceCreate(vss->address->component);
	if(!service)
	{
		cError("vss:%d: Creation of JausService FAILED! Switching to FAILURE_STATE\n", __LINE__);
		vss->state = JAUS_FAILURE_STATE;
	}
	jausServiceAddService(vss->services, service);
	jausServiceAddInputCommand(service, JAUS_QUERY_VELOCITY_STATE, 0xFF);
	jausServiceAddOutputCommand(service, JAUS_REPORT_VELOCITY_STATE, 0xFF);


	// Setup the vssMessage object
	vssMessage = reportVelocityStateMessageCreate();
	if(vssMessage == NULL)
	{
		cError("FAILURE: vss: vssMessage object failed to construct. Switching to FAILURE State");
		vss->state = JAUS_FAILURE_STATE;
		return;
	}
	else
	{
		// Set message source to this component
		vssMessage->source->id = vss->address->id;
	}
}

void vssInitState(void)
{
	static double timeout = 0;
	if(timeout == 0)
	{
		// 5 seconds is the maximum time to wait for the RDDF information to become valid		
		timeout = getTimeSeconds() + 5.0;
	}
	
	if(rddfGetDataValidity())
	{
		// Set the current speed
		vssMessage->velocityXMps = rddfGetCurrentSpeedMph() * MPH_TO_MPS;
		
		//add support for ReportVelocityState Service Connections
		scManagerAddSupportedMessage(vssNmi, JAUS_REPORT_VELOCITY_STATE);

		// Transition to Standby
		vss->state = JAUS_STANDBY_STATE;
	}
	else if(getTimeSeconds() > timeout)
	{
		cError("FAILURE: vss: RDDF data never became valid (5 sec wait). Switching to FAILURE State");
		vss->state = JAUS_FAILURE_STATE;
	}
}

void vssStandbyState(void)
{
	// Nothing to do
	vss->state = JAUS_READY_STATE;
}

void vssReadyState(void)
{
	JausMessage message;
	JausMessage txMessage;
	ServiceConnection scList, pointer;
	
	// Checks the run/pause flag and sets the current speed to the speed associated with the current waypoint
	// or set the speed to 0
	if(vssRunPauseFlag == VSS_RUN_MODE && rddfGetDataValidity())
		vssMessage->velocityXMps = rddfGetCurrentSpeedMph() * MPH_TO_MPS;
	else
		vssMessage->velocityXMps = 0;

	if(scManagerQueryActiveMessage(vssNmi, JAUS_REPORT_VELOCITY_STATE))
	{
		scList = scManagerGetSendList(vssNmi, JAUS_REPORT_VELOCITY_STATE);
		pointer = scList;
		while(scList)
		{
			// *****************************
			// Changed 11/07/05 for OPC 2.75
			// *****************************
			
			// This test will indicate if it is the new style using event messages or not
			if(scList->serviceConnectionType == SC_EVENT_TYPE)
			{
				// Event-Based
				
				// Need to make a copy of the scList->queryMessage
				// This is because we don't want the message processor to destroy 
				// the one attached to the sc
				message = jausMessageDuplicate(scList->queryMessage);
				if(message)
				{
					message->sequenceNumber = scList->sequenceNumber;
					message->scFlag = JAUS_SERVICE_CONNECTION_MESSAGE;;
					vssProcessMessage(message);
				}
				else
				{
					cError("gposReadyState: Failed to create a duplicate message\n");
				}
			}
			else
			{
				// SC Message Based
				vssMessage->destination->id = scList->address->id;
				vssMessage->presenceVector = scList->presenceVector;
				vssMessage->sequenceNumber = scList->sequenceNumber;
				vssMessage->scFlag = JAUS_SERVICE_CONNECTION_MESSAGE;
	
				txMessage = reportVelocityStateMessageToJausMessage(vssMessage);
				nodeManagerSend(vssNmi, txMessage);	
				jausMessageDestroy(txMessage);
			}
			scList = scList->nextSc;
		}
		scManagerDestroySendList(pointer);
	}
}

void vssEmergencyState(void)
{
	// USER: Insert Emergency Code Here
}

void vssFailureState(void)
{
	// USER: Insert Failure Code Here
}

void vssShutdownState(void)
{
	RejectComponentControlMessage rejectComponentControl;
	JausMessage txMessage;
		
	if(vss->controller.active)
	{
		// Terminate control of current component
		rejectComponentControl = rejectComponentControlMessageCreate();
		rejectComponentControl->source->id = vss->address->id;
		rejectComponentControl->destination->id = vss->controller.address->id;

		txMessage = rejectComponentControlMessageToJausMessage(rejectComponentControl);
		nodeManagerSend(vssNmi, txMessage);
		jausMessageDestroy(txMessage);

		rejectComponentControlMessageDestroy(rejectComponentControl);
	}
	
	// USER: Insert Shutdown Code Here, NOTE: Terminate any active service connections

	// Remove support for Grid Map Service Connections
	scManagerRemoveSupportedMessage(vssNmi, JAUS_REPORT_VELOCITY_STATE);	
	
	// Destroy vssMessage object
	if(vssMessage)
	{
		reportVelocityStateMessageDestroy(vssMessage);
	}
}

void vssAllState(void)
{
	// USER: Insert Code Here that is Common to All states
}
