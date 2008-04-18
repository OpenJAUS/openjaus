// File:		vss.c 
// Version:		0.4 alpha
// Written by:	Tom Galluzzo (galluzzt@ufl.edu) and Danny Kent (kentd@ufl.edu)
// Date:		07/01/2005
// Description:	This file contains the skeleton C code for implementing a JAUS component in a Linux environment
//				This code is designed to work with the node manager and JAUS library software written by CIMAR

// How To Use This File:
// All comments labled "USER:" specify lines of code that the end user must change to implement thier individual component
// The end user must also change all functions and variables in this file begining with "vss" (case JAUS_sensitive do not change Cmpt)
// This substring must be changed to the component identifier acronym of the individual component, and
// this file should also be renamed likewise
// Also Change all "VSS" to your component acronym (ALL CAPS) (case JAUS_sensitive)
// The end user must also change all "USER_COMPONENT_ID_NUMBER_HERE" defines to the individual component define (see examples below)
// Ex: For a Primitive Driver component change all "vss" to "pd" and "VSS" to "PD"
// Ex: For a Primitive Driver change all "USER_COMPONENT_ID_NUMBER_HERE" defines to "PRIMITIVE_DRIVER" defines
// Note that for new/experimental components, the component ID will have to be defined in the header file 
// After all changes are implemented, change the file header information at the begining of the file accordingly

#include "properties.h"
#include <jaus.h>			// JAUS message set (USER: JAUS libraries must be installed first)
#include <openJaus.h>	// Node managment functions for sending and receiving JAUS messages (USER: Node Manager must be installed)
#include <pthread.h>			// Multi-threading functions (standard to unix)
#include <stdlib.h>	
//#include <unistd.h>				// Unix standard functions
#include <string.h>
// USER: Add include files here as appropriate

#include "vss.h"	// USER: Implement and rename this header file. Include prototypes for all public functions contained in this file.
#include "vehicleSim.h"	

#if defined (WIN32)
	#define SLEEP_MS(x) Sleep(x)
	#define CONFIG_DIRECTORY ".\\config\\"
#elif defined(__linux) || defined(linux) || defined(__linux__)
	#define SLEEP_MS(x) usleep(x*1000)
	#define CONFIG_DIRECTORY "./config/"
#endif

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

static JausComponent vss = NULL;
static JausNode vssNode;
static JausSubsystem vssSubsystem;

static int vssRun = FALSE;
static double vssThreadHz = 0;									// Stores the calculated update rate for main state thread
static int vssThreadRunning = FALSE;
static pthread_t vssThreadId;							// pthread component thread identifier

static Properties vssProperties;
static NodeManagerInterface vssNmi;	// A data structure containing the Node Manager Interface for this component

// Vss Variables
static ReportVelocityStateMessage vssMessage;
static JausBoolean vssScActive = JAUS_FALSE;

// Function: 	vssStartup
// Access:		Public	
// Description: This function allows the abstracted component functionality contained in this file to be started from an external source.
// 				It must be called first before the component state machine and node manager interaction will begin
//				Each call to "vssStartup" should be followed by one call to the "vssShutdown" function
int vssStartup(void)
{
	FILE * propertyFile;
	pthread_attr_t attr;	// Thread attributed for the component threads spawned in this function
	char fileName[128] = {0};

	if(!vss)
	{
		vss = jausComponentCreate();
		vss->address->component = JAUS_VELOCITY_STATE_SENSOR;
		vss->identification  = "vss";
		vss->state = JAUS_SHUTDOWN_STATE;
	}

	if(vss->state == JAUS_SHUTDOWN_STATE)	// Execute the startup routines only if the component is not running
	{
		sprintf(fileName, "%svss.conf", CONFIG_DIRECTORY);
		propertyFile = fopen(fileName, "r");
		if(propertyFile)
		{
			vssProperties = propertiesCreate();
			vssProperties = propertiesLoad(vssProperties, propertyFile);
			fclose(propertyFile);
		}
		else
		{
			//cError("vss: Cannot find or open properties file\n");
			return VSS_LOAD_CONFIGURATION_ERROR;
		}
		
		// Check in to the Node Manager and obtain Instance, Node and Subsystem IDs
		vssNode = jausNodeCreate();
		vssSubsystem = jausSubsystemCreate();
		vssNode->subsystem = vssSubsystem;
		vss->node = vssNode;
		vss->services = jausServicesCreate();
		vss->state = JAUS_INITIALIZE_STATE; // Set the state of the JAUS state machine to INITIALIZE
		
		vssNmi = nodeManagerOpen(vss); 
		if(vssNmi == NULL)
		{
			//cError("vss: Could not open connection to node manager\n");
			return VSS_NODE_MANAGER_OPEN_ERROR; 
		}

		pthread_attr_init(&attr);
		pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

		vssRun = TRUE;

		if(pthread_create(&vssThreadId, &attr, vssThread, NULL) != 0)
		{
			//cError("vss: Could not create vssThread\n");
			vssShutdown();
			pthread_attr_destroy(&attr);
			return VSS_THREAD_CREATE_ERROR;
		}
		pthread_attr_destroy(&attr);
	}
	else
	{
		//cError("vss: Attempted startup while not shutdown\n");
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

	if(vss && vss->state != JAUS_SHUTDOWN_STATE)	// Execute the shutdown routines only if the component is running
	{
		vssRun = FALSE;

		timeOutSec = getTimeSeconds() + VSS_THREAD_TIMEOUT_SEC;
		while(vssThreadRunning)
		{
			SLEEP_MS(1000);
			if(getTimeSeconds() >= timeOutSec)
			{
				pthread_cancel(vssThreadId);
				vssThreadRunning = FALSE;
				//cError("vss: vssThread Shutdown Improperly\n");
				break;
			}
		}

		nodeManagerClose(vssNmi); // Close Node Manager Connection
				
		jausSubsystemDestroy(vss->node->subsystem);
		jausNodeDestroy(vss->node);
		jausServicesDestroy(vss->services);
	
		vss->state = JAUS_SHUTDOWN_STATE;

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

double vssGetVelocityX(void)
{
	return vssMessage->velocityXMps;
}

int vssGetScActive(void)
{
	return vssScActive;
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
				//cDebug(4, "VSS: Got message: %s from %d.%d.%d.%d\n", jausMessageCommandCodeString(rxMessage), rxMessage->source->subsystem, rxMessage->source->node, rxMessage->source->component, rxMessage->source->instance);
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
					//nanosleep(&sleepTime, NULL);
					SLEEP_MS(1);
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
		nodeManagerSendCoreServiceConnections(vssNmi);

		nextExcecuteTime = 2.0 * time + 1.0/VSS_THREAD_DESIRED_RATE_HZ - getTimeSeconds();
	}	
	
	vssShutdownState();
	
	//usleep(50000);	// Sleep for 50 milliseconds and then exit
	SLEEP_MS(50);

	vssThreadRunning = FALSE;
	
	return NULL;
}

// Function: vssProcessMessage
// Access:		Private
// Description:	This function is responsible for handling incoming JAUS messages from the Node Manager.
//				Incoming messages are processed according to message type.
void vssProcessMessage(JausMessage message)
{
	QueryVelocityStateMessage queryVelocityState;
	JausMessage txMessage;

	// This block of code is intended to reject commands from non-controlling components
	if(vss->controller.active && !jausAddressEqual(message->source, vss->controller.address) && jausMessageIsRejectableCommand(message))	
	{
		//cError("vss: Received command message %s from non-controlling component.\n", jausMessageCommandCodeString(message));
		jausMessageDestroy(message); // Ignore this message
		return;		
	}	

	switch(message->commandCode) // Switch the processing algorithm according to the JAUS message type
	{
		case JAUS_QUERY_VELOCITY_STATE:
			queryVelocityState = queryVelocityStateMessageFromJausMessage(message);
			if(queryVelocityState)
			{
				jausAddressCopy(vssMessage->destination, queryVelocityState->source);
				vssMessage->presenceVector = queryVelocityState->presenceVector;
				vssMessage->sequenceNumber = 0;
				vssMessage->properties.scFlag = 0;
				
				txMessage = reportVelocityStateMessageToJausMessage(vssMessage);
				nodeManagerSend(vssNmi, txMessage);
				jausMessageDestroy(txMessage);		
				
				queryVelocityStateMessageDestroy(queryVelocityState);
			}
			else
			{
				//cError("vss: Error unpacking %s message.\n", jausMessageCommandCodeString(message));
			}
			jausMessageDestroy(message);
			break;
		
		default:
			////cError("Test %04X : %d\n", message->commandCode, message->dataSize);
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
		//cError("vss: Addition of Core Services FAILED! Switching to FAILURE_STATE\n");
		vss->state = JAUS_FAILURE_STATE;
	}
	// USER: Add the rest of your component specific service(s) here

        // Add a new service to support the VSS input and output messages
        service = jausServiceCreate(vss->address->component);
        if(!service)
        {
                //cError("vss:%d: Creation of JausService FAILED! Switching to FAILURE_STATE\n", __LINE__);
                vss->state = JAUS_FAILURE_STATE;
        }
        jausServiceAddService(vss->services, service);
        jausServiceAddInputCommand(service, JAUS_QUERY_VELOCITY_STATE, 0xFF);
        jausServiceAddOutputCommand(service, JAUS_REPORT_VELOCITY_STATE, 0xFF);


	// Code run once through the init state
	vssMessage = reportVelocityStateMessageCreate();
	jausAddressCopy(vssMessage->source, vss->address);

	//add support for ReportGlovalPose Service Connections
	scManagerAddSupportedMessage(vssNmi, JAUS_REPORT_VELOCITY_STATE);
}

void vssInitState(void)
{
	vss->state = JAUS_READY_STATE;
}

void vssStandbyState(void)
{
	// USER: Insert Standby Code Here
}

void vssReadyState(void)
{
	JausMessage txMessage;
	ServiceConnection scList;
	ServiceConnection sc;
	char buf[64] = {0};
	char buf2[64] = {0};

	vssMessage->velocityXMps = vehicleSimGetSpeed();
	vssMessage->velocityYMps = 0;
	vssMessage->velocityZMps = 0;
	vssMessage->velocityRmsMps = 0.01;
	vssMessage->rollRateRps = 0.0;
	vssMessage->pitchRateRps = 0.0;
	vssMessage->yawRateRps = 0.0;
	vssMessage->rateRmsRps = 0;

	// send message
	if(scManagerQueryActiveMessage(vssNmi, JAUS_REPORT_VELOCITY_STATE))
	{
		vssScActive = JAUS_TRUE;
			
		scList = scManagerGetSendList(vssNmi, JAUS_REPORT_VELOCITY_STATE);
		sc = scList;
		while(sc)
		{
			jausAddressCopy(vssMessage->destination, sc->address);
			vssMessage->presenceVector = sc->presenceVector;
			vssMessage->sequenceNumber = sc->sequenceNumber;
			vssMessage->properties.scFlag = JAUS_SERVICE_CONNECTION_MESSAGE;
			
			txMessage = reportVelocityStateMessageToJausMessage(vssMessage);
			nodeManagerSend(vssNmi, txMessage);		
			jausMessageDestroy(txMessage);
	
			jausAddressToString(vssMessage->source, buf);
			jausAddressToString(vssMessage->destination, buf2);
			//cDebug(9, "Sent VSS SC from %s to %s\n", buf, buf2);
	
			sc = sc->nextSc;
		}
		
		scManagerDestroySendList(scList);
	}
	else
	{
		vssScActive = JAUS_FALSE;
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
		jausAddressCopy(rejectComponentControl->source, vss->address);
		jausAddressCopy(rejectComponentControl->destination, vss->controller.address);

		txMessage = rejectComponentControlMessageToJausMessage(rejectComponentControl);
		nodeManagerSend(vssNmi, txMessage);
		jausMessageDestroy(txMessage);

		rejectComponentControlMessageDestroy(rejectComponentControl);
	}
	
	// Remove support for ReportGlovalPose Service Connections
	scManagerRemoveSupportedMessage(vssNmi, JAUS_REPORT_VELOCITY_STATE);

	reportVelocityStateMessageDestroy(vssMessage);
}

void vssAllState(void)
{
	// USER: Insert Code Here that is Common to All states
}
