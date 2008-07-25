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
// File:		gpos.c 
// Version:		1.0
// Written by:	Danny Kent (jaus AT dannykent DOT com)
// Date:		08/05/2006
// Description:	This file contains the functionality associated with a simulated Global Position Sensor. This sensor is based
//				off a RDDF file. The particular file to use is specified in the gpos.conf file.
//				This code is designed to work with the node manager and JAUS library software written by CIMAR

#include <cimar.h>
#include <cimar/jaus.h>			// JAUS message set (USER: JAUS libraries must be installed first)
#include <cimar/nodeManager.h>	// Node managment functions for sending and receiving JAUS messages (USER: Node Manager must be installed)
#include <pthread.h>			// Multi-threading functions (standard to unix)
#include <stdlib.h>	
#include <unistd.h>				// Unix standard functions
#include <string.h>

#include "gpos.h"	// USER: Implement and rename this header file. Include prototypes for all public functions contained in this file.

// USER: Add include files here as appropriate
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "posConstants.h"
#include "vss.h"
#include "rddf.h"

// Private function prototypes
void *gposThread(void *);
void gposProcessMessage(JausMessage);
void gposStartupState(void);
void gposInitState(void);
void gposStandbyState(void);
void gposReadyState(void);
void gposEmergencyState(void);
void gposFailureState(void);
void gposShutdownState(void);
void gposAllState(void);

// USER: Insert any private function prototypes here
extern void mainStopMainRunning(void);
int calculateNewPosition(double);

// Following are static initalizers for the JausComponent structure
static JausAddressStruct gposAddress =	{ { 0, JAUS_GLOBAL_POSE_SENSOR, 0, 0} }; 
static JausAddressStruct gposControllerAddress =	{ { 0 } }; 
static JausComponentStruct gposStruct =	{	"GPOS Simulator",
											&gposAddress,
											JAUS_SHUTDOWN_STATE,
											0,
											NULL,
											NULL,
											{
												&gposControllerAddress,
												JAUS_UNDEFINED_STATE,
												0,
												JAUS_FALSE
											},
											0,
											0.0
										}; // All component specific information is stored in this CIMAR JAUS Library data structure
static JausComponent gpos = &gposStruct;
static JausNode gposNode;
static JausSubsystem gposSubsystem;

static int gposRun = FALSE;					// Thread control
static int gposThreadRunning = FALSE;		// Thread Control
static double gposThreadHz = 0;				// Stores the calculated update rate for main state thread
static pthread_t gposThreadId = 0;			// pthread component thread identifier

static Properties gposProperties;			// Properties structure which is read from the gpos.conf file
static NodeManagerInterface gposNmi;		// A data structure containing the Node Manager Interface for this component

// GPOS Varibles
static ReportGlobalPoseMessage gposMessage = NULL;	// gposMessage which will be used to send messages and store the current state
static char *confRddfFilename = NULL;				// Name of the RDDF file read from the gpos.conf file

// Function: 	gposStartup
// Access:		Public	
// Description: This function allows the abstracted component functionality contained in this file to be started from an external source.
// 				It must be called first before the component state machine and node manager interaction will begin
//				Each call to "gposStartup" should be followed by one call to the "gposShutdown" function
int gposStartup(void)
{
	FILE * propertyFile;
	pthread_attr_t attr;	// Thread attributed for the component threads spawned in this function
	
	if(gpos->state == JAUS_SHUTDOWN_STATE)	// Execute the startup routines only if the component is not running
	{
		propertyFile = fopen("./config/gpos.conf", "r");
		if(propertyFile)
		{
			gposProperties = propertiesCreate();
			gposProperties = propertiesLoad(gposProperties, propertyFile);
			fclose(propertyFile);
		}
		else
		{
			cError("gpos: Cannot find or open properties file\n");
			return GPOS_LOAD_CONFIGURATION_ERROR;
		}
		
		// Check in to the Node Manager and obtain Instance, Node and Subsystem IDs
		gposNode = jausNodeCreate();
		gposSubsystem = jausSubsystemCreate();
		gposNode->subsystem = gposSubsystem;
		gpos->node = gposNode;
		gpos->services = jausServicesCreate();
		
		gposNmi = nodeManagerOpen(gpos); 
		if(gposNmi == NULL)
		{
			cError("gpos: Could not open connection to node manager\n");
			return GPOS_NODE_MANAGER_OPEN_ERROR; 
		}

		pthread_attr_init(&attr);
		pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

		gpos->state = JAUS_INITIALIZE_STATE; // Set the state of the JAUS state machine to INITIALIZE
		gposRun = TRUE;

		if(pthread_create(&gposThreadId, &attr, gposThread, NULL) != 0)
		{
			cError("gpos: Could not create gposThread\n");
			gposShutdown();
			pthread_attr_destroy(&attr);
			return GPOS_THREAD_CREATE_ERROR;
		}
		pthread_attr_destroy(&attr);
	}
	else
	{
		cError("gpos: Attempted startup while not shutdown\n");
		return GPOS_STARTUP_BEFORE_SHUTDOWN_ERROR;
	}
	
	return 0;
}

// Function: gposShutdown
// Access:		Public	
// Description:	This function allows the abstracted component functionality contained in this file to be stoped from an external source.
// 				If the component is in the running state, this function will terminate all threads running in this file
//				This function will also close the Jms connection to the Node Manager and check out the component from the Node Manager
int gposShutdown(void)
{
	double timeOutSec;

	if(gpos->state != JAUS_SHUTDOWN_STATE)	// Execute the shutdown routines only if the component is running
	{
		gposRun = FALSE;

		timeOutSec = getTimeSeconds() + GPOS_THREAD_TIMEOUT_SEC;
		while(gposThreadRunning)
		{
			usleep(100000);
			if(getTimeSeconds() >= timeOutSec)
			{
				pthread_cancel(gposThreadId);
				gposThreadRunning = FALSE;
				cError("gpos: gposThread Shutdown Improperly\n");
				break;
			}
		}

		nodeManagerClose(gposNmi); // Close Node Manager Connection
		
		jausSubsystemDestroy(gpos->node->subsystem);
		jausNodeDestroy(gpos->node);
	
		gpos->state = JAUS_SHUTDOWN_STATE;
		jausServicesDestroy(gpos->services);
		
		propertiesDestroy(gposProperties);
	}

	return 0;
}

// The series of functions below allow public access to essential component information
// Access:		Public (All)
JausState gposGetState(void)
{
	return gpos->state;
}

JausAddress gposGetAddress(void)
{
	return gpos->address;
}

double gposGetUpdateRate(void)
{
	return gposThreadHz; 
}

// USER: Insert any additional public variable accessors here
// This function returns the current latitude
double gposGetLatitude(void)
{ 
	return gposMessage? gposMessage->latitudeDegrees : 0.0; 
}

// This function returns the current longitude
double gposGetLongitude(void)
{ 
	return gposMessage? gposMessage->longitudeDegrees : 0.0; 
}
// This function returns the current yaw
double gposGetYaw(void)
{ 
	return gposMessage? gposMessage->yawRadians : 0.0; 
}

// This function returns true if any components have successfully created a Service Connection to this component
JausBoolean gposGetScActive(void)
{ 
	return scManagerQueryActiveMessage(gposNmi, JAUS_REPORT_GLOBAL_POSE); 
}

// Function: gposThread
// Access:		Private
// Description:	All core component functionality is contained in this thread.
//				All of the JAUS component state machine code can be found here.
void *gposThread(void *threadData)
{
	JausMessage rxMessage;
	double time, prevTime, nextExcecuteTime = 0.0;
	struct timespec sleepTime;

	gposThreadRunning = TRUE;

	sleepTime.tv_sec = 0;
	sleepTime.tv_nsec = 1000;

	time = getTimeSeconds();
	gpos->state = JAUS_INITIALIZE_STATE; // Set JAUS state to INITIALIZE
	
	gposStartupState();
		
	while(gposRun) // Execute state machine code while not in the SHUTDOWN state
	{
		do
		{
//			printf("gposThread: rxMessage before receive= %x\n", &rxMessage);
			if(nodeManagerReceive(gposNmi, &rxMessage))
			{
//			printf("gposThread: rxMessage after receive= %x\n", &rxMessage);
				cDebug(4, "GPOS: Got message: %s\n", jausMessageCommandCodeString(rxMessage));
				gposProcessMessage(rxMessage);
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
		gposThreadHz = 1.0/(time-prevTime); // Compute the update rate of this thread
		
		switch(gpos->state) // Switch component behavior based on which state the machine is in
		{
			case JAUS_INITIALIZE_STATE:
				gposInitState();
				break;
				
			case JAUS_STANDBY_STATE:
				gposStandbyState();
				break;
				
			case JAUS_READY_STATE:
				gposReadyState();
				break;
				
			case JAUS_EMERGENCY_STATE:
				gposEmergencyState();
				break;
				
			case JAUS_FAILURE_STATE:
				gposFailureState();
				break;		
						
			case JAUS_SHUTDOWN_STATE:
				gposRun = FALSE;			
				break;		

			default:
				gpos->state = JAUS_FAILURE_STATE; // The default case JAUS_is undefined, therefore go into Failure State
				break;
		}	
		
		gposAllState();

		nextExcecuteTime = 2.0 * time + 1.0/GPOS_THREAD_DESIRED_RATE_HZ - getTimeSeconds();
	}	
	
	gposShutdownState();
	
	usleep(50000);	// Sleep for 50 milliseconds and then exit

	gposThreadRunning = FALSE;
	
	return NULL;
}

// Function: gposProcessMessage
// Access:		Private
// Description:	This function is responsible for handling incoming JAUS messages from the Node Manager.
//				Incoming messages are processed according to message type.
void gposProcessMessage(JausMessage message)
{
	JausMessage txMessage;
	ConfirmComponentControlMessage confirmComponentControl;
	RejectComponentControlMessage rejectComponentControl;
	ReportComponentAuthorityMessage reportComponentAuthority;
	ReportComponentStatusMessage reportComponentStatus;
	QueryGlobalPoseMessage queryGpos;
	
	if (message == NULL) {
		printf("gposProcessMessage: Got a NULL message!\n");
		return;
	}
	
	// This block of code is intended to reject commands from non-controlling components
	// However, the one exception allowed is a REQUEST_COMPONENT_CONTROL
	if(gpos->controller.active && message->commandCode < 0x2000) // If not currently under control or it's not a command, then go to the switch statement
	{
		// If the source component isn't the one in control, and it's not a request to gain control, then exit this iteration of the while loop
		if(gpos->controller.address->id != message->source->id && message->commandCode != JAUS_REQUEST_COMPONENT_CONTROL)
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
				cError("gpos: Error unpacking %s message.\n", jausMessageCommandCodeString(message));
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
				cError("gpos: Error unpacking %s message.\n", jausMessageCommandCodeString(message));
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
				cError("gpos: Error unpacking %s message.\n", jausMessageCommandCodeString(message));
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
				cError("gpos: Error unpacking %s message.\n", jausMessageCommandCodeString(message));
			}
			jausMessageDestroy(message);
			break;
		

		// JAUS_QUERY_GLOBAL_POSE
		// This case allows this component to handle individual queries for GPOS information
		case JAUS_QUERY_GLOBAL_POSE:
			queryGpos = queryGlobalPoseMessageFromJausMessage(message);
			if(queryGpos)
			{
				if(queryGpos->scFlag == JAUS_SERVICE_CONNECTION_MESSAGE)
				{
					// Service Connection Query
					gposMessage->scFlag = JAUS_SERVICE_CONNECTION_MESSAGE;
					gposMessage->sequenceNumber = message->sequenceNumber;
				}
				else
				{
					// Non SC Query
					gposMessage->scFlag = JAUS_NOT_SERVICE_CONNECTION_MESSAGE;
					gposMessage->sequenceNumber = 0;					
				}				
				gposMessage->destination->id = queryGpos->source->id;
				gposMessage->presenceVector = queryGpos->presenceVector;

				txMessage = reportGlobalPoseMessageToJausMessage(gposMessage);	
				nodeManagerSend(gposNmi, txMessage);
				jausMessageDestroy(txMessage);
				queryGlobalPoseMessageDestroy(queryGpos);				
			}
			else
			{
				cError("gpos: Error unpacking %s message.\n", jausMessageCommandCodeString(message));
			}
			jausMessageDestroy(message);
			break;
			
		
		default:
			defaultJausMessageProcessor(message, gposNmi, gpos);
			break;
	}
}

void gposStartupState(void)
{
	JausService service;
	
	// Populate Core Service
	if(!jausServiceAddCoreServices(gpos->services))
	{
		cError("gpos: Addition of Core Services FAILED! Switching to FAILURE_STATE\n");
		gpos->state = JAUS_FAILURE_STATE;
	}

	// Add a new service to support the GPOS input and output messages
	service = jausServiceCreate(gpos->address->component);
	if(!service)
	{
		cError("gpos:%d: Creation of JausService FAILED! Switching to FAILURE_STATE\n", __LINE__);
		gpos->state = JAUS_FAILURE_STATE;
	}
	jausServiceAddService(gpos->services, service);
	jausServiceAddInputCommand(service, JAUS_QUERY_GLOBAL_POSE, 0xFF);
	jausServiceAddOutputCommand(service, JAUS_REPORT_GLOBAL_POSE, 0xFF);

	// Initialize the gposMessage object
	gposMessage = reportGlobalPoseMessageCreate();
	if(gposMessage == NULL)
	{
		cError("FAILURE: gpos: gposMessage object failed to construct. Switching to FAILURE State");
		gpos->state = JAUS_FAILURE_STATE;
		return;
	}
	else
	{
		// Set the source of the message to this component 
		gposMessage->source->id = gpos->address->id;
	}
	
	// Read Parameters
	confRddfFilename = propertiesGetProperty(gposProperties, "RDDF_FILE");
	if(confRddfFilename == NULL)
	{
		cError("FAILURE: gpos: RDDF_FILE not found in gpos.conf. Switching to FAILURE State");
		gpos->state = JAUS_FAILURE_STATE;
		return;
	}
}

void gposInitState(void)
{
	//fake Gpos Inputs
	PointLla seed;
	RddfWaypoint *point;

	// Check if the RDDF File has been opened before, this is important because Init state can run multiple times
	if(rddfGetDataValidity())
	{
		point = rddfGetCurrentWaypoint();
		if(point != NULL)
		{
			// Populate initial message parameters
			gposMessage->latitudeDegrees = point->latitudeDeg;
			gposMessage->longitudeDegrees = point->longitudeDeg;
			gposMessage->yawRadians = rddfGetCurrentHeadingRad(gposMessage->latitudeDegrees, gposMessage->longitudeDegrees);

			// Seed the UTM conversion engine with the current latitude and longitude
			// This allows the UTM engine to select the proper zone for calculations
			seed = pointLlaCreate();
			if(seed)
			{
				seed->latitudeRadians = gposMessage->latitudeDegrees * DEG_TO_RAD;
				seed->longitudeRadians = gposMessage->longitudeDegrees * DEG_TO_RAD;
			
				utmConversionInit(seed);
				pointLlaDestroy(seed);
				
				//add support for ReportGlobalPose Service Connections
				scManagerAddSupportedMessage(gposNmi, JAUS_REPORT_GLOBAL_POSE);
			
				// Transition to the Standby State
				gpos->state = JAUS_STANDBY_STATE;
			}
		}
	}
	else // RDDF File is not open
	{
		cDebug(9, "RDDF Filename: %s\n", confRddfFilename);
		if(rddfReadData(confRddfFilename) < 0)
		{
			cError("FAILURE: gpos: Problem reading %s file for RDDF information. Switching to FAILURE State", confRddfFilename);
			gpos->state = JAUS_FAILURE_STATE;
			return;
		}
	}
}

void gposStandbyState(void)
{
	// Nothing to do, transition to Ready
	gpos->state = JAUS_READY_STATE;
}

void gposReadyState(void)
{
	JausMessage message;
	JausMessage txMessage;
	ServiceConnection scList;
	ServiceConnection pointer;

	if( !calculateNewPosition(vssGetSpeed()) ) // Modifies lat & lon to new values
	{
		rddfUpdatePosition(gposMessage->latitudeDegrees, gposMessage->longitudeDegrees);
		gposMessage->yawRadians = rddfGetCurrentHeadingRad(gposMessage->latitudeDegrees, gposMessage->longitudeDegrees);
	
		// send message
		if(scManagerQueryActiveMessage(gposNmi, JAUS_REPORT_GLOBAL_POSE))
		{			
			scList = scManagerGetSendList(gposNmi, JAUS_REPORT_GLOBAL_POSE);
			pointer = scList;

			// *****************************
			// Changed 11/07/05 for OPC 2.75
			// *****************************
			while(scList)
			{	
				// This test will indicate if it is the new style using event messages or not
				if(scList->serviceConnectionType == SC_EVENT_TYPE)
				{
					// Event based	
					// Need to make a copy of the scList->queryMessage
					// This is because we don't want the message processor to destroy 
					// the one attached to the sc
					message = jausMessageDuplicate(scList->queryMessage);
					if(message)
					{
						message->sequenceNumber = scList->sequenceNumber;
						message->scFlag = JAUS_SERVICE_CONNECTION_MESSAGE;
						gposProcessMessage(message);
					}
					else
					{
						cError("gposReadyState: Failed to create a duplicate message\n");
					}
				}
				else
				{
					// SC Message based
					gposMessage->destination->id = scList->address->id;
					gposMessage->presenceVector = scList->presenceVector;
					gposMessage->sequenceNumber = scList->sequenceNumber;
					gposMessage->scFlag = JAUS_SERVICE_CONNECTION_MESSAGE;
					
					txMessage = reportGlobalPoseMessageToJausMessage(gposMessage);
					
					nodeManagerSend(gposNmi, txMessage);
					jausMessageDestroy(txMessage);					
				}
		
				scList = scList->nextSc;
			}
			scManagerDestroySendList(pointer);
		}
	}
	else
	{
		cError("gpos: calculateNewPosition failed.\n");
	}
}

void gposEmergencyState(void)
{
	// USER: Insert Emergency Code Here
}

void gposFailureState(void)
{
	// USER: Insert Failure Code Here
}

void gposShutdownState(void)
{
	RejectComponentControlMessage rejectComponentControl;
	JausMessage txMessage;
		
	if(gpos->controller.active)
	{
		// Terminate control of current component
		rejectComponentControl = rejectComponentControlMessageCreate();
		rejectComponentControl->source->id = gpos->address->id;
		rejectComponentControl->destination->id = gpos->controller.address->id;

		txMessage = rejectComponentControlMessageToJausMessage(rejectComponentControl);
		nodeManagerSend(gposNmi, txMessage);
		jausMessageDestroy(txMessage);

		rejectComponentControlMessageDestroy(rejectComponentControl);
	}
	
	// USER: Insert Shutdown Code Here, NOTE: Terminate any active service connections
	// Remove support for Grid Map Service Connections
	scManagerRemoveSupportedMessage(gposNmi, JAUS_REPORT_GLOBAL_POSE);

	// Free the RDDF File
	if(rddfGetDataValidity())
	{
		rddfReleaseMemory();
	}

	// Destroy the gposMessage object
	reportGlobalPoseMessageDestroy(gposMessage);
	
}

void gposAllState(void)
{
	// USER: Insert Code Here that is Common to All states
}

int calculateNewPosition(double speedMps)
{
	static double prevTime = 0;
	double time;
	double timeDiff = 0;
	
	PointUtm positionUtm = NULL;
	PointLla positionLla = NULL;
		
	positionLla = pointLlaCreate();
	if(positionLla == NULL)
	{
		return -1;
	}
	
	time = getTimeSeconds();
	if(prevTime)
	{	
		timeDiff = time - prevTime;

		positionLla->latitudeRadians = gposMessage->latitudeDegrees * RAD_PER_DEG;
		positionLla->longitudeRadians = gposMessage->longitudeDegrees * RAD_PER_DEG;
		
		positionUtm = pointLlaToPointUtm(positionLla);
		pointLlaDestroy(positionLla);

		positionUtm->xMeters += cos(PI/2-gposMessage->yawRadians) * (timeDiff*speedMps);
		positionUtm->yMeters += sin(PI/2-gposMessage->yawRadians) * (timeDiff*speedMps);
		
		positionLla = pointUtmToPointLla(positionUtm);
		pointUtmDestroy(positionUtm);
		
		gposMessage->latitudeDegrees = positionLla->latitudeRadians * DEG_PER_RAD;
		gposMessage->longitudeDegrees = positionLla->longitudeRadians * DEG_PER_RAD;
		pointLlaDestroy(positionLla);
	}
	else
	{
		pointUtmDestroy(positionUtm);
		pointLlaDestroy(positionLla);
	}

	prevTime = time;

	return 0;
}

