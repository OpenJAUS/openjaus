// File:		gpos.c 
// Version:		0.4 alpha
// Written by:	Tom Galluzzo (galluzzt@ufl.edu) and Danny Kent (kentd@ufl.edu)
// Date:		07/01/2005
// Description:	This file contains the skeleton C code for implementing a JAUS component in a Linux environment
//				This code is designed to work with the node manager and JAUS library software written by CIMAR

#include "jaus.h"			// JAUS message set (USER: JAUS libraries must be installed first)
#include "nodeManager.h"	// Node managment functions for sending and receiving JAUS messages (USER: Node Manager must be installed)
#include <pthread.h>			// Multi-threading functions (standard to unix)
#include <stdlib.h>	
#include <unistd.h>				// Unix standard functions
#include <string.h>
#include "properties.h"
// USER: Add include files here as appropriate

#include "gpos.h"	// USER: Implement and rename this header file. Include prototypes for all public functions contained in this file.
#include "vehicleSim.h"
#include "utm/pointLla.h"

// Private function prototypes
void *gposThread(void *);
void gposProcessMessage(JausMessage rxMessage);
void gposStartupState(void);
void gposInitState(void);
void gposStandbyState(void);
void gposReadyState(void);
void gposEmergencyState(void);
void gposFailureState(void);
void gposShutdownState(void);
void gposAllState(void);

static JausComponent gpos = NULL;
static JausNode gposNode;
static JausSubsystem gposSubsystem;

static int gposRun = FALSE;
static double gposThreadHz = 0;									// Stores the calculated update rate for main state thread
static int gposThreadRunning = FALSE;
static pthread_t gposThreadId = 0;							// pthread component thread identifier

static Properties gposProperties;
static NodeManagerInterface gposNmi;	// A data structure containing the Node Manager Interface for this component

//Gpos Variables
static ReportGlobalPoseMessage gposMessage;
static JausBoolean gposScActive = JAUS_FALSE;

// Function: 	gposStartup
// Access:		Public	
// Description: This function allows the abstracted component functionality contained in this file to be started from an external source.
// 				It must be called first before the component state machine and node manager interaction will begin
//				Each call to "gposStartup" should be followed by one call to the "gposShutdown" function
int gposStartup(void)
{
	FILE * propertyFile;
	pthread_attr_t attr;	// Thread attributed for the component threads spawned in this function
	
	if(!gpos)
	{
		gpos = jausComponentCreate();
		gpos->address->component = JAUS_GLOBAL_POSE_SENSOR;
		gpos->identification  = "gpos";
		gpos->state = JAUS_SHUTDOWN_STATE;
	}
	
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
			////cError("gpos: Cannot find or open properties file\n");
			return GPOS_LOAD_CONFIGURATION_ERROR;
		}
		
		// Check in to the Node Manager and obtain Instance, Node and Subsystem IDs
		gposNode = jausNodeCreate();
		gposSubsystem = jausSubsystemCreate();
		gposNode->subsystem = gposSubsystem;
		gpos->node = gposNode;
		gpos->services = jausServicesCreate();
		gpos->state = JAUS_INITIALIZE_STATE; // Set the state of the JAUS state machine to INITIALIZE
		
		gposNmi = nodeManagerOpen(gpos); 
		if(gposNmi == NULL)
		{
			////cError("gpos: Could not open connection to node manager\n");
			return GPOS_NODE_MANAGER_OPEN_ERROR; 
		}

		pthread_attr_init(&attr);
		pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

		gposRun = TRUE;

		if(pthread_create(&gposThreadId, &attr, gposThread, NULL) != 0)
		{
			////cError("gpos: Could not create gposThread\n");
			gposShutdown();
			pthread_attr_destroy(&attr);
			return GPOS_THREAD_CREATE_ERROR;
		}
		pthread_attr_destroy(&attr);
	}
	else
	{
		////cError("gpos: Attempted startup while not shutdown\n");
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
				////cError("gpos: gposThread Shutdown Improperly\n");
				break;
			}
		}

		nodeManagerClose(gposNmi); // Close Node Manager Connection
				
		jausSubsystemDestroy(gpos->node->subsystem);
		jausNodeDestroy(gpos->node);
		jausServicesDestroy(gpos->services);
	
		gpos->state = JAUS_SHUTDOWN_STATE;

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

double gposGetLatitude(void)
{
	return gposMessage->latitudeDegrees;
}

double gposGetLongitude(void)
{
	return gposMessage->longitudeDegrees;
}

double gposGetYaw(void)
{
	return gposMessage->yawRadians;
}

int gposGetScActive(void)
{
	return gposScActive;
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
			if(nodeManagerReceive(gposNmi, &rxMessage))
			{
				////cDebug(4, "GPOS: Got message: %s from %d.%d.%d.%d\n", jausMessageCommandCodeString(rxMessage), rxMessage->source->subsystem, rxMessage->source->node, rxMessage->source->component, rxMessage->source->instance);
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
		nodeManagerSendCoreServiceConnections(gposNmi);

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
	QueryGlobalPoseMessage queryGlobalPose;
	JausMessage txMessage;

	// This block of code is intended to reject commands from non-controlling components
	if(gpos->controller.active && !jausAddressEqual(message->source, gpos->controller.address) && jausMessageIsRejectableCommand(message) )
	{
		////cError("gpos: Received command message %s from non-controlling component.\n", jausMessageCommandCodeString(message));
		jausMessageDestroy(message); // Ignore this message
		return;		
	}	

	switch(message->commandCode) // Switch the processing algorithm according to the JAUS message type
	{
		case JAUS_QUERY_GLOBAL_POSE:
			queryGlobalPose = queryGlobalPoseMessageFromJausMessage(message);
			if(queryGlobalPose)
			{
				jausAddressCopy(gposMessage->destination, queryGlobalPose->source);
				gposMessage->presenceVector = queryGlobalPose->presenceVector;
				gposMessage->sequenceNumber = 0;
				gposMessage->properties.scFlag = 0;
				
				txMessage = reportGlobalPoseMessageToJausMessage(gposMessage);
				nodeManagerSend(gposNmi, txMessage);		
				jausMessageDestroy(txMessage);
				
				queryGlobalPoseMessageDestroy(queryGlobalPose);
			}
			else
			{
				////cError("gpos: Error unpacking %s message.\n", jausMessageCommandCodeString(message));
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
		////cError("gpos: Addition of Core Services FAILED! Switching to FAILURE_STATE\n");
		gpos->state = JAUS_FAILURE_STATE;
	}
	// USER: Add the rest of your component specific service(s) here
	service = jausServiceCreate(gpos->address->component);
        if(!service)
        {
                ////cError("gpos:%d: Creation of JausService FAILED! Switching to FAILURE_STATE\n", __LINE__);
                gpos->state = JAUS_FAILURE_STATE;
        }
        jausServiceAddService(gpos->services, service);
        jausServiceAddInputCommand(service, JAUS_QUERY_GLOBAL_POSE, 0xFF);
        jausServiceAddOutputCommand(service, JAUS_REPORT_GLOBAL_POSE, 0xFF);
	

	gposMessage = reportGlobalPoseMessageCreate();
	jausAddressCopy(gposMessage->source, gpos->address);

	//add support for ReportGlovalPose Service Connections
	scManagerAddSupportedMessage(gposNmi, JAUS_REPORT_GLOBAL_POSE);
}

void gposInitState(void)
{
	gpos->state = JAUS_READY_STATE;
}

void gposStandbyState(void)
{
	// USER: Insert Standby Code Here
}

void gposReadyState(void)
{
	JausMessage txMessage;
	ServiceConnection scList;
	ServiceConnection sc;
	char buf[64] = {0};
	char buf2[64] = {0};
	
	PointLla vehiclePosLla;
	
	vehiclePosLla = vehicleSimGetPositionLla();
	if(vehiclePosLla)
	{		
		gposMessage->latitudeDegrees = vehiclePosLla->latitudeRadians * DEG_PER_RAD;
		gposMessage->longitudeDegrees = vehiclePosLla->longitudeRadians * DEG_PER_RAD;
	}
	
	gposMessage->yawRadians = -(vehicleSimGetH() - M_PI/2.0);

	gposMessage->elevationMeters = 0;
	gposMessage->positionRmsMeters = 1.0;
	gposMessage->rollRadians = 0.0;
	gposMessage->pitchRadians = 0.0;
	gposMessage->attitudeRmsRadians = 0.05;
	gposMessage->timeStamp = 0;

	// Send message
	if(scManagerQueryActiveMessage(gposNmi, JAUS_REPORT_GLOBAL_POSE))
	{
		gposScActive = JAUS_TRUE;
			
		scList = scManagerGetSendList(gposNmi, JAUS_REPORT_GLOBAL_POSE);
		sc = scList;
		while(sc)
		{
			jausAddressCopy(gposMessage->destination, sc->address);
			gposMessage->presenceVector = sc->presenceVector;
			gposMessage->sequenceNumber = sc->sequenceNumber;
			gposMessage->properties.scFlag = JAUS_SERVICE_CONNECTION_MESSAGE;
			
			txMessage = reportGlobalPoseMessageToJausMessage(gposMessage);
			nodeManagerSend(gposNmi, txMessage);
			jausMessageDestroy(txMessage);
	
			jausAddressToString(gposMessage->source, buf);
			jausAddressToString(gposMessage->destination, buf2);
			//cDebug(9, "Sent GPOS SC from %s to %s\n", buf, buf2);
	
			sc = sc->nextSc;
		}
		
		scManagerDestroySendList(scList);
	}
	else
	{
		gposScActive = JAUS_FALSE;
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
		jausAddressCopy(rejectComponentControl->source, gpos->address);
		jausAddressCopy(rejectComponentControl->destination, gpos->controller.address);

		txMessage = rejectComponentControlMessageToJausMessage(rejectComponentControl);
		nodeManagerSend(gposNmi, txMessage);
		jausMessageDestroy(txMessage);

		rejectComponentControlMessageDestroy(rejectComponentControl);
	}
	
	// Remove support for ReportGlovalPose Service Connections
	scManagerRemoveSupportedMessage(gposNmi, JAUS_REPORT_GLOBAL_POSE);

	reportGlobalPoseMessageDestroy(gposMessage);
}

void gposAllState(void)
{
	// USER: Insert Code Here that is Common to All states
}
