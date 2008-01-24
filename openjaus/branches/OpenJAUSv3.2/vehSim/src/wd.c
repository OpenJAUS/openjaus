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
// File:		wd.c 
//
// Version:		1.0
//
// Written by:	Danny Kent (jaus AT dannykent DOT com)
//
// Date:		08/24/06
//
// Description:	This file contains the skeleton C code for implementing a JAUS component in a Linux environment
//				This code is designed to work with the node manager and JAUS library software written by CIMAR

#include "properties.h"
#include "utm/utmLib.h"
#include <jaus.h>			// JAUS message set (USER: JAUS libraries must be installed first)
#include <nodeManager.h>	// Node managment functions for sending and receiving JAUS messages (USER: Node Manager must be installed)
#include <pthread.h>			// Multi-threading functions (standard to unix)
#include <stdlib.h>	
//#include <unistd.h>				// Unix standard functions
#include <string.h>
// USER: Add include files here as appropriate

#include "wd.h"
#include "vehicle.h"

#if defined (WIN32)
	#define SLEEP_MS(x) Sleep(x)
	#define _USE_MATH_DEFINES
	#include <math.h>
	#define CONFIG_DIRECTORY ".\\config\\"
#elif defined(__linux) || defined(linux) || defined(__linux__)
	#define SLEEP_MS(x) usleep(x*1000)
	#define CONFIG_DIRECTORY "./config/"
#endif

// GPOS Service Connection Defines
#define GPOS_SC_TIMEOUT_SECONDS 		1.0		// The timeout between receiving service connection messages
#define GPOS_SC_UPDATE_RATE_HZ 			20.0	// Requested service connection update rate
#define GPOS_SC_PRESENCE_VECTOR 		0xFF	// The GPOS Presence Vector, set this to the fields desired (default = ALL)
#define GPOS_SC_QUEUE_SIZE				0		// The Service Connection Manager's queue size (0 = infinite)

// VSS Service Connection Defines
#define VSS_SC_TIMEOUT_SECONDS	 		1.0		// The timeout between receiving service connection messages
#define VSS_SC_UPDATE_RATE_HZ 			20.0	// Requested service connection update rate
#define VSS_SC_PRESENCE_VECTOR	 		0xFF	// The VSS Presence Vector, set this to the fields desired (default = ALL)
#define VSS_SC_QUEUE_SIZE				0		// The Service Connection Manager's queue size (0 = infinite)

// PD Service Connection Defines
#define PD_WRENCH_SC_TIMEOUT_SECONDS 	1.0		// The timeout between receiving service connection messages
#define PD_WRENCH_SC_UPDATE_RATE_HZ 	20.0	// Requested service connection update rate
#define PD_WRENCH_SC_PRESENCE_VECTOR 	0xFF	// The PD Presence Vector, set this to the fields desired (default = ALL)
#define PD_WRENCH_SC_QUEUE_SIZE			0		// The Service Connection Manager's queue size (0 = infinite)

#define PD_STATUS_SC_TIMEOUT_SECONDS 	1.0		// The timeout between receiving service connection messages
#define PD_STATUS_SC_UPDATE_RATE_HZ 	20.0	// Requested service connection update rate
#define PD_STATUS_SC_PRESENCE_VECTOR 	0xFF	// The PD Presence Vector, set this to the fields desired (default = ALL)
#define PD_STATUS_SC_QUEUE_SIZE			1		// The Service Connection Manager's queue size (0 = infinite)

#define MPH_PER_MPS						2.23694
#define MPS_PER_MPH						0.44704

//#define ACCEL_GRAVITY_MPSPS				9.81	// Acceleration due to gravity

#define REQUEST_TIMEOUT_SEC				5.0 	// How long to wait between any requests

#define WAYPOINT_POP_DISTANCE_M						3.0
#define MISSION_FINISHED_DISTANCE_M					3.0
#define WD_DEFAULT_MIN_SPEED_MPS					1.0
#define WD_DEFAULT_MAX_SPEED_MPS					4.0 //11.18

// Gains
#define ACCELERATION_MPSPS				0.75	// Mps2
#define DECCELERATION_MPSPS				2.0		// Mps2
#define LINEAR_EFFORT_K_FF				14.0 	// %Effort / Mps
#define LINEAR_EFFORT_BIAS_FF  			-57.5	// %Effort
#define LINEAR_EFFORT_K_P				15.0 	// %Effort / (Mps Error)
#define LINEAR_EFFORT_K_I				6.5 	// %Effort / (M Error)
#define LINEAR_EFFORT_I_LIM				6.5 	// M Error
#define LINEAR_EFFORT_K_D				20.0
#define BRAKE_K							-1.3	// %Effort / %Effort
#define THROTTLE_K						0.65	// %Effort / %Effort
#define STICKTION_SPEED_MPS				0.5
#define STICKTION_EFFORT				-17.5
//#define PITCH_FF_EFFORT_PER_RAD			150
#define STEERING_FF_EFFORT				200
#define WHEEL_ROTATION_EFFORT_PER_RAD	100	
#define WHEEL_ROTATION_RAD_PER_EFFORT	0.006
// Private function prototypes
void *wdThread(void *);
void wdProcessMessage(JausMessage);
void wdStartupState(void);
void wdInitState(void);
void wdStandbyState(void);
void wdReadyState(void);
void wdEmergencyState(void);
void wdFailureState(void);
void wdShutdownState(void);
void wdAllState(void);
// USER: Insert any private function prototypes here
void wdExcecuteControl(VehicleState);
double wdAngleSubtract(double a, double b);

static JausComponent wd = NULL;
static JausNode wdNode;
static JausSubsystem wdSubsystem;

static int wdRun = FALSE;
static double wdThreadHz = 0;									// Stores the calculated update rate for main state thread
static int wdThreadRunning = FALSE;
static pthread_t wdThreadId;							// pthread component thread identifier

static Properties wdProperties;
static NodeManagerInterface wdNmi;	// A data structure containing the Node Manager Interface for this component

//
// Waypoint Driver "globals"
//

// Incomming Service Connections
static ServiceConnection gposSc = NULL;
static ServiceConnection vssSc = NULL;
static ServiceConnection pdWrenchSc = NULL;
static ServiceConnection pdStatusSc = NULL;

static JausBoolean wdInControl = JAUS_FALSE;
static JausBoolean wdRequestControl = JAUS_FALSE;

static JausArray wdWaypoints = NULL;					// Array of commaned waypoints
static int currentWaypointIndex = 0;
static double wdWaypointDistance = 0;

static ReportWrenchEffortMessage wdReportWrench = NULL;
static ReportGlobalPoseMessage wdReportGpos = NULL;
static ReportVelocityStateMessage wdReportVss = NULL;
static SetWrenchEffortMessage wdWrench = NULL;
static SetTravelSpeedMessage wdSpeed = NULL;
static SetGlobalWaypointMessage wdGlobalWaypoint = NULL;

static VehicleState vehicleState = NULL;
static JausComponent pd = NULL;

// Function: 	wdStartup
// Access:		Public	
// Description: This function allows the abstracted component functionality contained in this file to be started from an external source.
// 				It must be called first before the component state machine and node manager interaction will begin
//				Each call to "wdStartup" should be followed by one call to the "wdShutdown" function
int wdStartup(void)
{
	FILE * propertyFile;
	pthread_attr_t attr;	// Thread attributed for the component threads spawned in this function
	char fileName[128] = {0};

	if(!wd)
	{
		wd = jausComponentCreate();
		wd->address->component = JAUS_GLOBAL_WAYPOINT_DRIVER;
		wd->identification  = "Waypoint Driver";
		wd->state = JAUS_SHUTDOWN_STATE;
	}

	if(wd->state == JAUS_SHUTDOWN_STATE)	// Execute the startup routines only if the component is not running
	{
		sprintf(fileName, "%swd.conf", CONFIG_DIRECTORY);
		propertyFile = fopen(fileName, "r");
		if(propertyFile)
		{
			wdProperties = propertiesCreate();
			wdProperties = propertiesLoad(wdProperties, propertyFile);
			fclose(propertyFile);
		}
		else
		{
			//cError("wd: Cannot find or open properties file\n");
			return WD_LOAD_CONFIGURATION_ERROR;
		}
		
		// Check in to the Node Manager and obtain Instance, Node and Subsystem IDs
		wdNode = jausNodeCreate();
		wdSubsystem = jausSubsystemCreate();
		wdNode->subsystem = wdSubsystem;
		wd->node = wdNode;
		wd->services = jausServicesCreate();
		wd->state = JAUS_INITIALIZE_STATE; // Set the state of the JAUS state machine to INITIALIZE
		
		wdNmi = nodeManagerOpen(wd); 
		if(wdNmi == NULL)
		{
			//cError("wd: Could not open connection to node manager\n");
			return WD_NODE_MANAGER_OPEN_ERROR; 
		}

		pthread_attr_init(&attr);
		pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

		wdRun = TRUE;

		if(pthread_create(&wdThreadId, &attr, wdThread, NULL) != 0)
		{
			//cError("wd: Could not create wdThread\n");
			wdShutdown();
			pthread_attr_destroy(&attr);
			return WD_THREAD_CREATE_ERROR;
		}
		pthread_attr_destroy(&attr);
	}
	else
	{
		//cError("wd: Attempted startup while not shutdown\n");
		return WD_STARTUP_BEFORE_SHUTDOWN_ERROR;
	}
	
	return 0;
}

// Function: wdShutdown
// Access:		Public	
// Description:	This function allows the abstracted component functionality contained in this file to be stoped from an external source.
// 				If the component is in the running state, this function will terminate all threads running in this file
//				This function will also close the Jms connection to the Node Manager and check out the component from the Node Manager
int wdShutdown(void)
{
	double timeOutSec;

	if(wd && wd->state != JAUS_SHUTDOWN_STATE)	// Execute the shutdown routines only if the component is running
	{
		wdRun = FALSE;

		timeOutSec = getTimeSeconds() + WD_THREAD_TIMEOUT_SEC;
		while(wdThreadRunning)
		{
			SLEEP_MS(1000);
			if(getTimeSeconds() >= timeOutSec)
			{
				pthread_cancel(wdThreadId);
				wdThreadRunning = FALSE;
				//cError("wd: wdThread Shutdown Improperly\n");
				break;
			}
		}

		nodeManagerClose(wdNmi); // Close Node Manager Connection
				
		jausSubsystemDestroy(wd->node->subsystem);
		jausNodeDestroy(wd->node);
		jausServicesDestroy(wd->services);
	
		wd->state = JAUS_SHUTDOWN_STATE;

		propertiesDestroy(wdProperties);
	}

	return 0;
}

// The series of functions below allow public access to essential component information
// Access:		Public (All)
JausState wdGetState(void)
{
	return wd->state;
}

JausAddress wdGetAddress(void)
{
	return wd->address;
}

JausAddress wdGetControllerAddress(void)
{
	return wd->controller.active? wd->controller.address : NULL;
}

double wdGetUpdateRate(void)
{
	return wdThreadHz; 
}

// USER: Insert any additional public variable accessors here
ReportWrenchEffortMessage wdGetReportedWrench(void)
{ 
	if(pdWrenchSc && pdWrenchSc->isActive)
	{
		return wdReportWrench; 
	}
	else
	{
		return NULL;
	}
}

SetWrenchEffortMessage wdGetCommandedWrench(void)
{ 
	return wdWrench; 
}

ReportVelocityStateMessage wdGetVss(void)
{ 
	return wdReportVss; 
}

ReportGlobalPoseMessage wdGetGpos(void)
{ 
	return wdReportGpos; 
}

SetTravelSpeedMessage wdGetTravelSpeed(void)
{
	return wdSpeed;
}

SetGlobalWaypointMessage wdGetGlobalWaypoint(void)
{
	if(currentWaypointIndex < wdWaypoints->elementCount)
	{
		return (SetGlobalWaypointMessage) wdWaypoints->elementData[currentWaypointIndex];
	}
	else
	{
		return NULL;
	} 
}

JausState wdGetPdState(void)
{
	return pd? pd->state : JAUS_UNKNOWN_STATE;
}

JausBoolean wdGetPdWrenchScStatus(void)
{
	return pdWrenchSc? pdWrenchSc->isActive : JAUS_FALSE;
}

JausBoolean wdGetPdStatusScStatus(void)
{
	return pdStatusSc? pdStatusSc->isActive : JAUS_FALSE;
}

JausBoolean wdGetVssScStatus(void)
{
	return vssSc? vssSc->isActive : JAUS_FALSE;
}

JausBoolean wdGetGposScStatus(void)
{
	return gposSc? gposSc->isActive : JAUS_FALSE;
}

JausBoolean wdGetInControlStatus(void)
{
	return wdInControl;
}

VehicleState wdGetDesiredVehicleState(void)
{
	return vehicleState;
}

double wdGetWaypointDistanceM(void)
{
	return wdWaypointDistance;
}

int wdGetActiveWaypoint(void)
{
	return currentWaypointIndex;
}

int wdGetWaypointCount(void)
{
	return wdWaypoints ? wdWaypoints->elementCount : 0;
}

void wdToggleRequestControl(void)
{
	wdRequestControl = !wdRequestControl;
}

JausBoolean wdGetRequestControl(void)
{
	return wdRequestControl;
}

void wdCreateWaypoint(void)
{
	SetGlobalWaypointMessage setWaypoint = NULL;
	JausMessage message = NULL;
	
	setWaypoint = setGlobalWaypointMessageCreate();
	setWaypoint->latitudeDegrees = 29.001;
	setWaypoint->longitudeDegrees = -80.001;
	
	message = setGlobalWaypointMessageToJausMessage(setWaypoint);
	setGlobalWaypointMessageDestroy(setWaypoint);
	wdProcessMessage(message);	
}

void wdSetSpeed(void)
{
	SetTravelSpeedMessage setSpeed = NULL;
	JausMessage message = NULL;
	
	setSpeed = setTravelSpeedMessageCreate();
	setSpeed->speedMps = 4.0;
	
	message = setTravelSpeedMessageToJausMessage(setSpeed);
	setTravelSpeedMessageDestroy(setSpeed);
	wdProcessMessage(message);
}


// Function: wdThread
// Access:		Private
// Description:	All core component functionality is contained in this thread.
//				All of the JAUS component state machine code can be found here.
void *wdThread(void *threadData)
{
	JausMessage rxMessage;
	double time, prevTime, nextExcecuteTime = 0.0;
	struct timespec sleepTime;

	wdThreadRunning = TRUE;

	sleepTime.tv_sec = 0;
	sleepTime.tv_nsec = 1000;

	time = getTimeSeconds();
	wd->state = JAUS_INITIALIZE_STATE; // Set JAUS state to INITIALIZE
	
	wdStartupState();
		
	while(wdRun) // Execute state machine code while not in the SHUTDOWN state
	{
		do
		{
			if(nodeManagerReceive(wdNmi, &rxMessage))
			{
				//cDebug(4, "WD: Got message: %s from %d.%d.%d.%d\n", jausMessageCommandCodeString(rxMessage), rxMessage->source->subsystem, rxMessage->source->node, rxMessage->source->component, rxMessage->source->instance);
				wdProcessMessage(rxMessage);
			}
			else 
			{
				if(getTimeSeconds() > nextExcecuteTime)
				{
					break;
				}
				else
				{
					//nanosleep(&sleepTime, NULL);
					SLEEP_MS(1);
				}
			}
		}while(getTimeSeconds() < nextExcecuteTime);
		
		prevTime = time;
		time = getTimeSeconds();
		wdThreadHz = 1.0/(time-prevTime); // Compute the update rate of this thread
		
		switch(wd->state) // Switch component behavior based on which state the machine is in
		{
			case JAUS_INITIALIZE_STATE:
				wdInitState();
				break;
				
			case JAUS_STANDBY_STATE:
				wdStandbyState();
				break;
				
			case JAUS_READY_STATE:
				wdReadyState();
				break;
				
			case JAUS_EMERGENCY_STATE:
				wdEmergencyState();
				break;
				
			case JAUS_FAILURE_STATE:
				wdFailureState();
				break;		
						
			case JAUS_SHUTDOWN_STATE:
				wdRun = FALSE;			
				break;		

			default:
				wd->state = JAUS_FAILURE_STATE; // The default case JAUS_is undefined, therefore go into Failure State
				break;
		}	
		
		wdAllState();
		nodeManagerSendCoreServiceConnections(wdNmi);

		nextExcecuteTime = 2.0 * time + 1.0/WD_THREAD_DESIRED_RATE_HZ - getTimeSeconds();
	}	
	
	wdShutdownState();
	
	//usleep(50000);	// Sleep for 50 milliseconds and then exit
	SLEEP_MS(50);

	wdThreadRunning = FALSE;
	
	return NULL;
}

// Function: wdProcessMessage
// Access:		Private
// Description:	This function is responsible for handling incoming JAUS messages from the Node Manager.
//				Incoming messages are processed according to message type.
void wdProcessMessage(JausMessage message)
{
	JausMessage txMessage;
	ConfirmComponentControlMessage confirmComponentControl;
	RejectComponentControlMessage rejectComponentControl;
	ReportComponentStatusMessage reportComponentStatus;
	QueryGlobalWaypointMessage queryGlobalWaypointMessage;
	ReportGlobalWaypointMessage reportGlobalWaypointMessage;
	QueryWaypointCountMessage queryWaypointCountMessage;
	ReportWaypointCountMessage reportWaypointCountMessage;
	int i;
	char buf[64] = {0};

	// This block of code is intended to reject commands from non-controlling components
	if(wd->controller.active && !jausAddressEqual(message->source, wd->controller.address) && jausMessageIsRejectableCommand(message))
	{
		//cError("wd: Received command message %s from non-controlling component.\n", jausMessageCommandCodeString(message));
		jausMessageDestroy(message); // Ignore this message
		return;		
	}	

	switch(message->commandCode) // Switch the processing algorithm according to the JAUS message type
	{	
		case JAUS_REPORT_COMPONENT_STATUS:
			reportComponentStatus = reportComponentStatusMessageFromJausMessage(message);
			if(reportComponentStatus)
			{
				if(jausAddressEqual(reportComponentStatus->source, pd->address))
				{
					pd->state = reportComponentStatus->primaryStatusCode;
				}
				reportComponentStatusMessageDestroy(reportComponentStatus);
			}
			else
			{
				//cError("wd: Error unpacking %s message.\n", jausMessageCommandCodeString(message));
			}
			jausMessageDestroy(message);
			break;

		case JAUS_CONFIRM_COMPONENT_CONTROL:
			confirmComponentControl = confirmComponentControlMessageFromJausMessage(message);
			if(confirmComponentControl)
			{
				if(jausAddressEqual(confirmComponentControl->source, pd->address))
				{
					//cDebug(4,"wd: Confirmed control of PD\n");
					wdInControl = JAUS_TRUE;
				}
				confirmComponentControlMessageDestroy(confirmComponentControl);
			}
			else
			{
				//cError("wd: Error unpacking %s message.\n", jausMessageCommandCodeString(message));
			}
			jausMessageDestroy(message);
			break;
			
		case JAUS_REJECT_COMPONENT_CONTROL:
			rejectComponentControl = rejectComponentControlMessageFromJausMessage(message);
			if(rejectComponentControl)
			{
				if(jausAddressEqual(rejectComponentControl->source, pd->address))
				{			
					//cDebug(4,"wd: Lost control of PD\n");
					wdInControl = JAUS_FALSE;
				}
				rejectComponentControlMessageDestroy(rejectComponentControl);
			}
			else
			{
				//cError("wd: Error unpacking %s message.\n", jausMessageCommandCodeString(message));
			}
			jausMessageDestroy(message);
			break;
			
		case JAUS_SET_TRAVEL_SPEED:
			if(wdSpeed)
			{
				setTravelSpeedMessageDestroy(wdSpeed);
			}
			
			wdSpeed = setTravelSpeedMessageFromJausMessage(message);
			if(!wdSpeed)
			{
				//cError("wd: Error unpacking %s message.\n", jausMessageCommandCodeString(message));
			}
			jausMessageDestroy(message);
			break;

		case JAUS_REPORT_GLOBAL_POSE:
			if(wdReportGpos)
			{
				reportGlobalPoseMessageDestroy(wdReportGpos);
			}
			
			wdReportGpos = reportGlobalPoseMessageFromJausMessage(message);
			if(wdReportGpos)
			{
				// Nothing to do
				jausAddressToString(message->source, buf);
				//cDebug(9, "Recv GPOS msg from %s\n", buf);
				
			}
			else
			{
				//cError("wd: Error unpacking %s message.\n", jausMessageCommandCodeString(message));
			}

			if(currentWaypointIndex < wdWaypoints->elementCount)
			{
				// update waypoint index
				SetGlobalWaypointMessage tempGlobalWaypoint;
				tempGlobalWaypoint = (SetGlobalWaypointMessage) wdWaypoints->elementData[currentWaypointIndex];
				wdWaypointDistance = greatCircleDistance(wdReportGpos->latitudeDegrees * RAD_PER_DEG, wdReportGpos->longitudeDegrees * RAD_PER_DEG, tempGlobalWaypoint->latitudeDegrees * RAD_PER_DEG, tempGlobalWaypoint->longitudeDegrees * RAD_PER_DEG);
								
				if(wdWaypointDistance < WAYPOINT_POP_DISTANCE_M)
				{
					//cError("wd: popping waypoint: %d\n",currentWaypointIndex); 
					currentWaypointIndex++;
				}
			}
//			else
//			{
//				if(wdSpeed) wdSpeed->speedMps = 0;
//			}
			
			jausMessageDestroy(message);
			break;

		case JAUS_REPORT_VELOCITY_STATE:
			if(wdReportVss)
			{
				reportVelocityStateMessageDestroy(wdReportVss);
			}
			
			wdReportVss = reportVelocityStateMessageFromJausMessage(message);
			if(!wdReportVss)
			{
				//cError("wd: Error unpacking %s message.\n", jausMessageCommandCodeString(message));
			}
			jausMessageDestroy(message);
			break;

		case JAUS_REPORT_WRENCH_EFFORT:
			if(wdReportWrench)
			{
				reportWrenchEffortMessageDestroy(wdReportWrench);
			}
			
			wdReportWrench = reportWrenchEffortMessageFromJausMessage(message);
			if(!wdReportWrench)
			{
				//cError("wd: Error unpacking %s message.\n", jausMessageCommandCodeString(message));
			}
			jausMessageDestroy(message);
			break;
			
		case JAUS_SET_GLOBAL_WAYPOINT:
			wdGlobalWaypoint = setGlobalWaypointMessageFromJausMessage(message);
			if(!wdGlobalWaypoint)
			{
				//cError("wd: Error unpacking %s message.\n", jausMessageCommandCodeString(message));
			}
			jausMessageDestroy(message);
			jausArrayAdd(wdWaypoints, wdGlobalWaypoint);
			break;

		case JAUS_QUERY_GLOBAL_WAYPOINT:
			queryGlobalWaypointMessage = queryGlobalWaypointMessageFromJausMessage(message);
			if(!queryGlobalWaypointMessage)
			{
				//cError("wd: Error unpacking %s message.\n", jausMessageCommandCodeString(message));
			}
			// loop thru waypoints to find the one that matches the request
			// if there's a match, prepare/send the report, else whine

			for(i = 0; i < wdWaypoints->elementCount; i++)
			{
				SetGlobalWaypointMessage tempGlobalWaypoint;
				tempGlobalWaypoint = (SetGlobalWaypointMessage) wdWaypoints->elementData[i];
				if(tempGlobalWaypoint->waypointNumber == queryGlobalWaypointMessage->waypointNumber)
				{
					reportGlobalWaypointMessage = reportGlobalWaypointMessageCreate();
					jausAddressCopy(reportGlobalWaypointMessage->destination, queryGlobalWaypointMessage->source);
					jausAddressCopy(reportGlobalWaypointMessage->source, wd->address);
					reportGlobalWaypointMessage->presenceVector = NO_PRESENCE_VECTOR;
					reportGlobalWaypointMessage->waypointNumber = tempGlobalWaypoint->waypointNumber;
					reportGlobalWaypointMessage->latitudeDegrees = tempGlobalWaypoint->latitudeDegrees;
					reportGlobalWaypointMessage->longitudeDegrees = tempGlobalWaypoint->longitudeDegrees;
					txMessage = reportGlobalWaypointMessageToJausMessage(reportGlobalWaypointMessage);
					reportGlobalWaypointMessageDestroy(reportGlobalWaypointMessage);
					nodeManagerSend(wdNmi, txMessage);
					jausMessageDestroy(txMessage);
				}
			}
			queryGlobalWaypointMessageDestroy(queryGlobalWaypointMessage);
			jausMessageDestroy(message);
			break;
			
		case JAUS_QUERY_WAYPOINT_COUNT:
			queryWaypointCountMessage = queryWaypointCountMessageFromJausMessage(message);
			if(!queryWaypointCountMessage)
			{
				//cError("wd: Error unpacking %s message.\n", jausMessageCommandCodeString(message));
			}
			reportWaypointCountMessage = reportWaypointCountMessageCreate();
			jausAddressCopy(reportWaypointCountMessage->destination, queryWaypointCountMessage->source);
			jausAddressCopy(reportWaypointCountMessage->source, wd->address);
			reportWaypointCountMessage->waypointCount = wdWaypoints->elementCount;
			txMessage = reportWaypointCountMessageToJausMessage(reportWaypointCountMessage);
			reportWaypointCountMessageDestroy(reportWaypointCountMessage);
			nodeManagerSend(wdNmi, txMessage);
			queryWaypointCountMessageDestroy(queryWaypointCountMessage);
			jausMessageDestroy(message);
			break;
		
		default:
			defaultJausMessageProcessor(message, wdNmi, wd);
			break;
	}
}

void wdStartupState(void)
{
	JausService service;
	
	// Populate Core Service
	if(!jausServiceAddCoreServices(wd->services))
	{
		//cError("wd: Addition of Core Services FAILED! Switching to FAILURE_STATE\n");
		wd->state = JAUS_FAILURE_STATE;
	}
	// USER: Add the rest of your component specific service(s) here
	
	// create a new service for waypoint driver message support
	service = jausServiceCreate(JAUS_GLOBAL_WAYPOINT_DRIVER); 
	
	// add each supported waypoint driver input message 
	jausServiceAddInputCommand(service, JAUS_SET_TRAVEL_SPEED, NO_PRESENCE_VECTOR);
	jausServiceAddInputCommand(service, JAUS_SET_GLOBAL_WAYPOINT, NO_PRESENCE_VECTOR);//actually, there is a PV and it's equal to zero
	jausServiceAddInputCommand(service, JAUS_QUERY_WAYPOINT_COUNT, NO_PRESENCE_VECTOR);
	jausServiceAddInputCommand(service, JAUS_QUERY_GLOBAL_WAYPOINT, NO_PRESENCE_VECTOR);

	// add each supported waypoint driver output message
	jausServiceAddOutputCommand(service, JAUS_REPORT_WAYPOINT_COUNT, NO_PRESENCE_VECTOR);
	jausServiceAddOutputCommand(service, JAUS_REPORT_GLOBAL_WAYPOINT, NO_PRESENCE_VECTOR);

	// add the service to the component's services vector
	if(!jausServiceAddService(wd->services, service))
	{
		//cError("wd: Could not add services");
	}

	wd->authority = 127;

	pd = jausComponentCreate();
	pd->address->component = JAUS_PRIMITIVE_DRIVER;
	
	// Setup GPOS Service Connection handle
	gposSc = serviceConnectionCreate();
	gposSc->requestedUpdateRateHz = GPOS_SC_UPDATE_RATE_HZ;
	gposSc->address->component = JAUS_GLOBAL_POSE_SENSOR;
	gposSc->presenceVector = GPOS_SC_PRESENCE_VECTOR;
	gposSc->commandCode = JAUS_REPORT_GLOBAL_POSE;
	gposSc->isActive = JAUS_FALSE;
	gposSc->queueSize = GPOS_SC_QUEUE_SIZE;
	gposSc->timeoutSec = GPOS_SC_TIMEOUT_SECONDS;

	// Setup VSS Service Connection handle
	vssSc = serviceConnectionCreate();
	vssSc->requestedUpdateRateHz = VSS_SC_UPDATE_RATE_HZ;
	vssSc->address->component = JAUS_VELOCITY_STATE_SENSOR;
	vssSc->presenceVector = VSS_SC_PRESENCE_VECTOR;
	vssSc->commandCode = JAUS_REPORT_VELOCITY_STATE;
	vssSc->isActive = JAUS_FALSE;
	vssSc->queueSize = VSS_SC_QUEUE_SIZE;
	vssSc->timeoutSec = VSS_SC_TIMEOUT_SECONDS;

	// Setup PD Service Connection handle
	pdWrenchSc = serviceConnectionCreate();
	pdWrenchSc->requestedUpdateRateHz = PD_WRENCH_SC_UPDATE_RATE_HZ;
	pdWrenchSc->address->component = JAUS_PRIMITIVE_DRIVER;
	pdWrenchSc->presenceVector = PD_WRENCH_SC_PRESENCE_VECTOR;
	pdWrenchSc->commandCode = JAUS_REPORT_WRENCH_EFFORT;
	pdWrenchSc->isActive = JAUS_FALSE;
	pdWrenchSc->queueSize = PD_WRENCH_SC_QUEUE_SIZE;
	pdWrenchSc->timeoutSec = PD_WRENCH_SC_TIMEOUT_SECONDS;

	pdStatusSc = serviceConnectionCreate();
	pdStatusSc->requestedUpdateRateHz = PD_STATUS_SC_UPDATE_RATE_HZ;
	pdStatusSc->address->component = JAUS_PRIMITIVE_DRIVER;
	pdStatusSc->presenceVector = PD_STATUS_SC_PRESENCE_VECTOR;
	pdStatusSc->commandCode = JAUS_REPORT_COMPONENT_STATUS;
	pdStatusSc->isActive = JAUS_FALSE;
	pdStatusSc->queueSize = PD_STATUS_SC_QUEUE_SIZE;
	pdStatusSc->timeoutSec = PD_STATUS_SC_TIMEOUT_SECONDS;
	
	// Setup message to be sent to the PD
	wdWrench = setWrenchEffortMessageCreate();
	jausAddressCopy(wdWrench->source, wd->address);
	jausShortPresenceVectorSetBit(&wdWrench->presenceVector, JAUS_WRENCH_PV_PROPULSIVE_LINEAR_X_BIT);
	jausShortPresenceVectorSetBit(&wdWrench->presenceVector, JAUS_WRENCH_PV_PROPULSIVE_ROTATIONAL_Z_BIT);
	jausShortPresenceVectorSetBit(&wdWrench->presenceVector, JAUS_WRENCH_PV_RESISTIVE_LINEAR_X_BIT);

	scManagerAddSupportedMessage(wdNmi, JAUS_REPORT_COMPONENT_STATUS);

	wdWaypoints = jausArrayCreate();
	
	vehicleState = vehicleStateCreate();

}

void wdInitState(void)
{
	static double nextRequestTimeSec = 0.0;
	RequestComponentControlMessage requestControl = NULL;
	JausMessage txMessage = NULL;
	char buf[64] = {0};
		
	// Check for critcal service connections or conditions here
	if(gposSc->isActive && vssSc->isActive && pdWrenchSc->isActive && pdStatusSc->isActive && wdInControl && wdRequestControl)
	{
		// Transition to Standby
		wd->state = JAUS_STANDBY_STATE;
		//cDebug(4, "wd: Switching to STANDBY State\n");
	}
	else if(getTimeSeconds() > nextRequestTimeSec)
	{
		if(!gposSc->isActive)
		{
			if(scManagerCreateServiceConnection(wdNmi, gposSc))
			{
				//cDebug(4, "wd: Sent GPOS SC Request\n");
			}
		}
		
		if(!vssSc->isActive)
		{
			if(scManagerCreateServiceConnection(wdNmi, vssSc))
			{
				//cDebug(4, "wd: Sent VSS SC Request\n");
			}
		}

		if(!pdWrenchSc->isActive && wdInControl)
		{
			if(scManagerCreateServiceConnection(wdNmi, pdWrenchSc))
			{
				//cDebug(4, "wd: Sent PD Wrench SC Request\n");
			}
		}

		if(!pdStatusSc->isActive && wdInControl)
		{
			if(scManagerCreateServiceConnection(wdNmi, pdStatusSc))
			{
				//cDebug(4, "wd: Sent PD Status SC Request\n");
			}
		}
		
		nextRequestTimeSec = getTimeSeconds() + REQUEST_TIMEOUT_SEC;
		
	}
	
	if(!wdInControl && wdRequestControl)
	{
		if(!pd->address->node)
		{
			pd->address->subsystem = wd->address->subsystem;
			
			if(nodeManagerLookupAddress(wdNmi, pd->address))
			{
				jausAddressCopy(wdWrench->destination, pd->address);
			}
		}
		
		if(pd->address->node)
		{
			jausAddressToString(pd->address, buf);
			//cDebug(4, "wd: Requesting control of PD %s\n", buf);
	
			requestControl = requestComponentControlMessageCreate();
			jausAddressCopy(requestControl->source, wd->address);
			jausAddressCopy(requestControl->destination, pd->address);
			requestControl->authorityCode = wd->authority;
			
			txMessage = requestComponentControlMessageToJausMessage(requestControl);
			nodeManagerSend(wdNmi, txMessage);
			jausMessageDestroy(txMessage);
			
			requestComponentControlMessageDestroy(requestControl);

			if(scManagerCreateServiceConnection(wdNmi, pdStatusSc))
			{
				//cDebug(4, "wd: Sent PD Status SC Request\n");
			}

			if(scManagerCreateServiceConnection(wdNmi, pdWrenchSc))
			{
				//cDebug(4, "wd: Sent PD Wrench SC Request\n");
			}

			nextRequestTimeSec = getTimeSeconds() + REQUEST_TIMEOUT_SEC;
		}
	}	
}

void wdStandbyState(void)
{
	if(!gposSc->isActive || !vssSc->isActive || !pdWrenchSc->isActive || !pdStatusSc->isActive || !wdInControl)
	{
		wd->state = JAUS_EMERGENCY_STATE;
		
//		cError(	"wd: Switching to EMERGENCY: GposSc: %s, VssSc: %s, PdWrenchSc: %s, PdStatusSc: %s, Rd: %s\n", 
//				gposSc->isActive? "Active" : "Inactive",
//				vssSc->isActive? "Active" : "Inactive",
//				pdWrenchSc->isActive? "Active" : "Inactive",
//				pdStatusSc->isActive? "Active" : "Inactive",
//				wdInControl? "In Control" : "Not In Control" 
//				);
				
		return;
	}
		
	// Setup Vehicle State		
	vehicleState->desiredSpeedMps = 0;
	vehicleState->desiredPhiEffort = 0;
	wdExcecuteControl(vehicleState);
	
	if(pd->state == JAUS_READY_STATE)
	{
		wd->state = JAUS_READY_STATE;
	}	
}

void wdReadyState(void)
{
	double waypointHeading = 0;
	double headingDelta = 0;

	if(!gposSc->isActive || !vssSc->isActive || !pdWrenchSc->isActive || !pdStatusSc->isActive || !wdInControl)
	{
		wd->state = JAUS_EMERGENCY_STATE;
		
//		cError(	"wd: Switching to EMERGENCY: GposSc: %s, VssSc: %s, PdWrenchSc: %s, PdStatusSc: %s, Rd: %s\n", 
//				gposSc->isActive? "Active" : "Inactive",
//				vssSc->isActive? "Active" : "Inactive",
//				pdWrenchSc->isActive? "Active" : "Inactive",
//				pdStatusSc->isActive? "Active" : "Inactive",
//				wdInControl? "In Control" : "Not In Control" 
//				);
				
		return;
	}
	
	if(pd->state != JAUS_READY_STATE)
	{
		wd->state = JAUS_STANDBY_STATE;
		return;
	}	
	
	vehicleState->speedMps = wdReportVss? (float) wdReportVss->velocityXMps : (float) 0.0;

	if(currentWaypointIndex < wdWaypoints->elementCount)
	{
		SetGlobalWaypointMessage tempGlobalWaypoint;
		tempGlobalWaypoint = (SetGlobalWaypointMessage) wdWaypoints->elementData[currentWaypointIndex];

		waypointHeading = greatCircleCourse(wdReportGpos->latitudeDegrees * RAD_PER_DEG, wdReportGpos->longitudeDegrees * RAD_PER_DEG, tempGlobalWaypoint->latitudeDegrees * RAD_PER_DEG, tempGlobalWaypoint->longitudeDegrees * RAD_PER_DEG);
		wdWaypointDistance = greatCircleDistance(wdReportGpos->latitudeDegrees * RAD_PER_DEG, wdReportGpos->longitudeDegrees * RAD_PER_DEG, tempGlobalWaypoint->latitudeDegrees * RAD_PER_DEG, tempGlobalWaypoint->longitudeDegrees * RAD_PER_DEG);
		
		headingDelta = wdAngleSubtract(waypointHeading, wdReportGpos->yawRadians);
		
		//cLog("HeadingDelta: %7.2f\n", headingDelta);
		vehicleState->desiredPhiEffort = (float) (WHEEL_ROTATION_EFFORT_PER_RAD * headingDelta);
		vehicleState->desiredSpeedMps = wdSpeed? (float) wdSpeed->speedMps : (float) 0.0;
		//cLog("vehicleState->desiredPhiEffort: %7.2f\n", vehicleState->desiredPhiEffort);		
	}
	else
	{
		//hang out
		vehicleState->desiredSpeedMps = 0;
		vehicleState->desiredPhiEffort = 0;
	}
	
	wdExcecuteControl(vehicleState);
}

void wdEmergencyState(void)
{
	// USER: Insert Emergency Code Here
	wd->state = JAUS_INITIALIZE_STATE;

}

void wdFailureState(void)
{
	// USER: Insert Failure Code Here
}

void wdShutdownState(void)
{
	RejectComponentControlMessage rejectComponentControl;
	ReleaseComponentControlMessage releaseControl = NULL;
	JausMessage txMessage;
		
	scManagerRemoveSupportedMessage(wdNmi, JAUS_REPORT_COMPONENT_STATUS);	

	if(wd->controller.active)
	{
		// Terminate control of current component
		rejectComponentControl = rejectComponentControlMessageCreate();
		jausAddressCopy(rejectComponentControl->source, wd->address);
		jausAddressCopy(rejectComponentControl->destination, wd->controller.address);

		txMessage = rejectComponentControlMessageToJausMessage(rejectComponentControl);
		nodeManagerSend(wdNmi, txMessage);
		jausMessageDestroy(txMessage);

		rejectComponentControlMessageDestroy(rejectComponentControl);
	}
	
	// USER: Insert Shutdown Code Here, NOTE: Terminate any active service connections
	
	// Release Control
	if(wdInControl)
	{
		//cDebug(4, "wd: Releasing control of PD\n");
	
		releaseControl = releaseComponentControlMessageCreate();
		jausAddressCopy(releaseControl->source, wd->address);
		jausAddressCopy(releaseControl->destination, pd->address);
		
		txMessage = releaseComponentControlMessageToJausMessage(releaseControl);
		nodeManagerSend(wdNmi, txMessage);
		jausMessageDestroy(txMessage);
		
		releaseComponentControlMessageDestroy(releaseControl);
		
		wdInControl = JAUS_FALSE;
		wd->state = JAUS_INITIALIZE_STATE;
	}
	
	if(pdStatusSc->isActive)
	{	
		scManagerTerminateServiceConnection(wdNmi, pdStatusSc);
		serviceConnectionDestroy(pdStatusSc);
	}
	
	if(pdWrenchSc->isActive)
	{	
		scManagerTerminateServiceConnection(wdNmi, pdWrenchSc);		
		serviceConnectionDestroy(pdWrenchSc);
	}	

	if(gposSc->isActive)
	{	
		scManagerTerminateServiceConnection(wdNmi, gposSc);		
		serviceConnectionDestroy(gposSc);
	}	

	if(vssSc->isActive)
	{	
		scManagerTerminateServiceConnection(wdNmi, vssSc);		
		serviceConnectionDestroy(vssSc);
	}
	
	// Destory Global Messages
	if(wdSpeed)
	{
		setTravelSpeedMessageDestroy(wdSpeed);
	}

	if(wdReportGpos)
	{
		reportGlobalPoseMessageDestroy(wdReportGpos);
	}

	if(wdReportVss)
	{
		reportVelocityStateMessageDestroy(wdReportVss);
	}

	if(wdReportWrench)
	{
		reportWrenchEffortMessageDestroy(wdReportWrench);
	}

	// Destroy Global Variables
	vehicleStateDestroy(vehicleState);	
	jausArrayDestroy(wdWaypoints, (void *)setGlobalWaypointMessageDestroy);
	setWrenchEffortMessageDestroy(wdWrench);
	jausComponentDestroy(pd);
}

void wdAllState(void)
{
	JausMessage message = NULL;
	ServiceConnection scList;
	ServiceConnection sc;
	ReportComponentStatusMessage reportStatus;	
	ReleaseComponentControlMessage releaseControl = NULL;

	// Retrieve the Gpos SC Message
	if(gposSc && gposSc->isActive)
	{
		if(scManagerReceiveServiceConnection(wdNmi, gposSc, &message))
		{
			wdProcessMessage(message);
		}
	}

	if(vssSc && vssSc->isActive)
	{
		if(scManagerReceiveServiceConnection(wdNmi, vssSc, &message))
		{
			wdProcessMessage(message);
		}
	}

	if(pdWrenchSc && pdWrenchSc->isActive)
	{
		if(scManagerReceiveServiceConnection(wdNmi, pdWrenchSc, &message))
		{
			wdProcessMessage(message);
		}
	}

	if(pdStatusSc && pdStatusSc->isActive)
	{
		if(scManagerReceiveServiceConnection(wdNmi, pdStatusSc, &message))
		{
			wdProcessMessage(message);
		}
	}

	// Respond to a ReportComponentStatus Service Connection
	scList = scManagerGetSendList(wdNmi, JAUS_REPORT_COMPONENT_STATUS);
	if(scList)
	{
		reportStatus = reportComponentStatusMessageCreate();
		jausAddressCopy(reportStatus->source, wd->address);
		reportStatus->properties.scFlag = JAUS_SERVICE_CONNECTION_MESSAGE;
		reportStatus->primaryStatusCode = wd->state;

		sc = scList;
		while(sc)
		{
				jausAddressCopy(reportStatus->destination, sc->address);
				reportStatus->sequenceNumber = sc->sequenceNumber;

				message = reportComponentStatusMessageToJausMessage(reportStatus);
				nodeManagerSend(wdNmi, message);
				jausMessageDestroy(message);

				sc = sc->nextSc;
		}
		reportComponentStatusMessageDestroy(reportStatus);
	}
	scManagerDestroySendList(scList);

	// Check Control
	if(!wdRequestControl && wdInControl)
	{
		// Release Control
		//cDebug(4, "wd: Releasing control of PD\n");

		releaseControl = releaseComponentControlMessageCreate();
		jausAddressCopy(releaseControl->source, wd->address);
		jausAddressCopy(releaseControl->destination, pd->address);
		
		message = releaseComponentControlMessageToJausMessage(releaseControl);
		nodeManagerSend(wdNmi, message);
		jausMessageDestroy(message);
		
		releaseComponentControlMessageDestroy(releaseControl);
		
		wdInControl = JAUS_FALSE;
		pd->state = JAUS_UNKNOWN_STATE;
		
		if(pdStatusSc->isActive)
		{	
			scManagerTerminateServiceConnection(wdNmi, pdStatusSc);
		}
		
		if(pdWrenchSc->isActive)
		{	
			scManagerTerminateServiceConnection(wdNmi, pdWrenchSc);		
		}	

		wd->state = JAUS_INITIALIZE_STATE;

	}
}

void wdExcecuteControl(VehicleState vehicleState)
{
	static double speedCommand = 0;
	static double prevSpeedError = 0;
	static double dampedSpeedErrorDerivative = 0;
	static double acceleration = ACCELERATION_MPSPS; //Mpsps
	static double decceleration = DECCELERATION_MPSPS; //Mpsps
	static double lastExcecuteTime = -1; 
	static double dt;
	static double linearEffortInt = 0.0;
	double linearEffort;
	double speedError;
	JausMessage txMessage;
	
	if(lastExcecuteTime < 0)
	{
		lastExcecuteTime = getTimeSeconds();
		dt = 1.0 / WD_THREAD_DESIRED_RATE_HZ;
	}
	else
	{
		dt = getTimeSeconds() - lastExcecuteTime;
		lastExcecuteTime = getTimeSeconds();
	}
	
	if(speedCommand < vehicleState->desiredSpeedMps)
	{
		speedCommand += acceleration * dt;
		if(speedCommand > vehicleState->desiredSpeedMps)
		{
			speedCommand = vehicleState->desiredSpeedMps;
		}
	}	
	else
	{
		speedCommand -= decceleration * dt;		
		if(speedCommand < vehicleState->desiredSpeedMps)
		{
			speedCommand = vehicleState->desiredSpeedMps;
		}
	}
	
	speedError = speedCommand - vehicleState->speedMps;	

	linearEffortInt += speedError * dt;
	if(linearEffortInt > LINEAR_EFFORT_I_LIM)
	{
		linearEffortInt = LINEAR_EFFORT_I_LIM;
	}
	if(linearEffortInt < -LINEAR_EFFORT_I_LIM)
	{
		linearEffortInt = -LINEAR_EFFORT_I_LIM;
	}

	if(dt > 0.001)
	{
		dampedSpeedErrorDerivative = 0.9 * dampedSpeedErrorDerivative + 0.1 * (speedError - prevSpeedError) / dt;
		prevSpeedError = speedError;
	}

	linearEffort = LINEAR_EFFORT_K_FF * speedCommand + LINEAR_EFFORT_BIAS_FF; 
	linearEffort += LINEAR_EFFORT_K_P * speedError;
	linearEffort += LINEAR_EFFORT_K_I * linearEffortInt;
	linearEffort += LINEAR_EFFORT_K_D * dampedSpeedErrorDerivative;
	
	// Pitch feed forward
	//linearEffort += PITCH_FF_EFFORT_PER_RAD * sin(wdDampedPitchRad); // Pitch feed forward effort
	
	// Steering feed forward
	if(wdReportWrench)
	{
		linearEffort += STEERING_FF_EFFORT * (1.0/cos(wdReportWrench->propulsiveRotationalEffortZPercent * WHEEL_ROTATION_RAD_PER_EFFORT) - 1.0);
	}
	
	// Sticktion feed forward
	if(speedCommand < WD_DEFAULT_MIN_SPEED_MPS)
	{
		linearEffort += STICKTION_EFFORT; 
	}

	if(linearEffort > 0)
	{
		wdWrench->propulsiveLinearEffortXPercent = THROTTLE_K * linearEffort;
		wdWrench->resistiveLinearEffortXPercent = 0;
	}
	else
	{
		wdWrench->propulsiveLinearEffortXPercent = 0;
		wdWrench->resistiveLinearEffortXPercent = BRAKE_K * linearEffort;
	}

	if(wdWrench->propulsiveLinearEffortXPercent > 100.0)
	{
		wdWrench->propulsiveLinearEffortXPercent = 100.0;
	}
	if(wdWrench->propulsiveLinearEffortXPercent < 0.0)
	{
		wdWrench->propulsiveLinearEffortXPercent = 0.0;
	}

	if(wdWrench->resistiveLinearEffortXPercent > 100.0)
	{
		wdWrench->resistiveLinearEffortXPercent = 100.0;
	}
	if(wdWrench->resistiveLinearEffortXPercent < 0.0)
	{
		wdWrench->resistiveLinearEffortXPercent = 0.0;
	}

	wdWrench->propulsiveRotationalEffortZPercent = vehicleState->desiredPhiEffort;

	if(wdWrench->propulsiveRotationalEffortZPercent > 100.0)
	{
		wdWrench->propulsiveRotationalEffortZPercent = 100.0;
	}
	if(wdWrench->propulsiveRotationalEffortZPercent < -100.0)
	{
		wdWrench->propulsiveRotationalEffortZPercent = -100.0;
	}

	jausAddressCopy(wdWrench->destination, pd->address);

	txMessage = setWrenchEffortMessageToJausMessage(wdWrench);
	nodeManagerSend(wdNmi, txMessage);		
	jausMessageDestroy(txMessage);
	
	return;
}

// Function calculates angle a minus angle b
double wdAngleSubtract(double a, double b)
{
   return atan2(sin(a-b), cos(a-b));
} 
