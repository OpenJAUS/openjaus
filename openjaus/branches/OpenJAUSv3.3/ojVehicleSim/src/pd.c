// File:		pd.c 
// Version:		0.4 alpha
// Written by:	Tom Galluzzo (galluzzt@ufl.edu) and Danny Kent (kentd@ufl.edu)
// Date:		07/01/2005
// Description:	This file contains the skeleton C code for implementing a JAUS component in a Linux environment
//				This code is designed to work with the node manager and JAUS library software written by CIMAR

#include "jaus.h"			// JAUS message set (USER: JAUS libraries must be installed first)
#include "openJaus.h"	// Node managment functions for sending and receiving JAUS messages (USER: Node Manager must be installed)
#include <pthread.h>			// Multi-threading functions (standard to unix)
#include <stdlib.h>	
//#include <unistd.h>				// Unix standard functions
#include <string.h>
#include "properties.h"

#include "vehicleSim.h"
#include "pd.h"	// USER: Implement and rename this header file. Include prototypes for all public functions contained in this file.

#if defined (WIN32)
	#define CONFIG_DIRECTORY ".\\config\\"
#elif defined(__linux) || defined(linux) || defined(__linux__) || defined(__APPLE__)
	#define CONFIG_DIRECTORY "./config/"
#endif

#define CONTROLLER_STATUS_SC_TIMEOUT_SECONDS 	1.5
#define CONTROLLER_STATUS_SC_UPDATE_RATE_HZ		5.0
#define CONTROLLER_STATUS_SC_QUEUE_SIZE			1
#define CONTROLLER_STATUS_SC_PRESENCE_VECTOR	0

#define CONFIRM_SC_TIMEOUT_SEC		3.0

// Private function prototypes
void *pdThread(void *);
void pdProcessMessage(JausMessage rxMessage);
void pdStartupState(void);
void pdInitState(void);
void pdStandbyState(void);
void pdReadyState(void);
void pdEmergencyState(void);
void pdFailureState(void);
void pdShutdownState(void);
void pdAllState(void);
// USER: Insert any private function prototypes here
void pdSendReportWrenchEffort(void);

static JausComponent pd = NULL;
static JausNode pdNode;
static JausSubsystem pdSubsystem;

static int pdRun = FALSE;
static double pdThreadHz = 0;		// Stores the calculated update rate for main state thread
static int pdThreadRunning = FALSE;
static pthread_t pdThreadId;		// pthread component thread identifier

static Properties pdProperties;
static NodeManagerInterface pdNmi;	// A data structure containing the Node Manager Interface for this component

static ServiceConnection controllerStatusSc = NULL;
static SetWrenchEffortMessage setWrenchEffort = NULL;
static ReportWrenchEffortMessage reportWrenchEffort = NULL;
static SetDiscreteDevicesMessage setDiscreteDevices = NULL;

// Function: 	pdStartup
// Access:		Public	
// Description: This function allows the abstracted component functionality contained in this file to be started from an external source.
// 				It must be called first before the component state machine and node manager interaction will begin
//				Each call to "pdStartup" should be followed by one call to the "pdShutdown" function
int pdStartup(void)
{
	FILE * propertyFile;
	pthread_attr_t attr;	// Thread attributed for the component threads spawned in this function
	char fileName[128] = {0};

	if(!pd)
	{
		pd = jausComponentCreate();
		pd->address->component = JAUS_PRIMITIVE_DRIVER;
		pd->identification  = "pd";
		pd->state = JAUS_SHUTDOWN_STATE;
	}

	if(pd->state == JAUS_SHUTDOWN_STATE)	// Execute the startup routines only if the component is not running
	{
		sprintf(fileName, "%spd.conf", CONFIG_DIRECTORY);
		propertyFile = fopen(fileName, "r");
		if(propertyFile)
		{
			pdProperties = propertiesCreate();
			pdProperties = propertiesLoad(pdProperties, propertyFile);
			fclose(propertyFile);
		}
		else
		{
			printf("pd: Cannot find or open properties file\n");
			return PD_LOAD_CONFIGURATION_ERROR;
		}
		
		// Check in to the Node Manager and obtain Instance, Node and Subsystem IDs
		pdNode = jausNodeCreate();
		pdSubsystem = jausSubsystemCreate();
		pdNode->subsystem = pdSubsystem;
		pd->node = pdNode;
		pd->services = jausServicesCreate();
		pd->state = JAUS_INITIALIZE_STATE; // Set the state of the JAUS state machine to INITIALIZE
		
		pdNmi = nodeManagerOpen(pd); 
		if(pdNmi == NULL)
		{
			printf("pd: Could not open connection to node manager\n");
			return PD_NODE_MANAGER_OPEN_ERROR; 
		}

		pthread_attr_init(&attr);
		pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

		pdRun = TRUE;

		if(pthread_create(&pdThreadId, &attr, pdThread, NULL) != 0)
		{
			//cError("pd: Could not create pdThread\n");
			pdShutdown();
			pthread_attr_destroy(&attr);
			return PD_THREAD_CREATE_ERROR;
		}
		pthread_attr_destroy(&attr);
	}
	else
	{
		//cError("pd: Attempted startup while not shutdown\n");
		return PD_STARTUP_BEFORE_SHUTDOWN_ERROR;
	}
	
	return 0;
}

// Function: pdShutdown
// Access:		Public	
// Description:	This function allows the abstracted component functionality contained in this file to be stoped from an external source.
// 				If the component is in the running state, this function will terminate all threads running in this file
//				This function will also close the Jms connection to the Node Manager and check out the component from the Node Manager
int pdShutdown(void)
{
	double timeOutSec;

	if(pd && pd->state != JAUS_SHUTDOWN_STATE)	// Execute the shutdown routines only if the component is running
	{
		pdRun = FALSE;

		timeOutSec = getTimeSeconds() + PD_THREAD_TIMEOUT_SEC;
		while(pdThreadRunning)
		{
			ojSleepMsec(100);
			if(getTimeSeconds() >= timeOutSec)
			{
				pthread_cancel(pdThreadId);
				pdThreadRunning = FALSE;
				//cError("pd: pdThread Shutdown Improperly\n");
				break;
			}
		}

		nodeManagerClose(pdNmi); // Close Node Manager Connection
				
		jausSubsystemDestroy(pd->node->subsystem);
		jausNodeDestroy(pd->node);
		jausServicesDestroy(pd->services);
	
		pd->state = JAUS_SHUTDOWN_STATE;

		propertiesDestroy(pdProperties);
	}

	return 0;
}

// The series of functions below allow public access to essential component information
// Access:		Public (All)
JausState pdGetState(void)
{
	return pd->state;
}

JausAddress pdGetAddress(void)
{
	return pd->address;
}

double pdGetUpdateRate(void)
{
	return pdThreadHz; 
}

JausBoolean pdGetControllerScStatus(void)
{
	return controllerStatusSc ? controllerStatusSc->isActive : JAUS_FALSE;
}

JausBoolean pdGetControllerStatus(void)
{
	return pd->controller.active;
}

JausState pdGetControllerState(void)
{
	return pd->controller.state;
}

JausAddress pdGetControllerAddress(void)
{
	return pd->controller.address;
}

SetWrenchEffortMessage pdGetWrenchEffort(void)
{
	return setWrenchEffort;
}

// Function: pdThread
// Access:		Private
// Description:	All core component functionality is contained in this thread.
//				All of the JAUS component state machine code can be found here.
void *pdThread(void *threadData)
{
	JausMessage rxMessage;
	double time, prevTime, nextExcecuteTime = 0.0;

	pdThreadRunning = TRUE;

	time = getTimeSeconds();
	pd->state = JAUS_INITIALIZE_STATE; // Set JAUS state to INITIALIZE
	
	pdStartupState();
		
	while(pdRun) // Execute state machine code while not in the SHUTDOWN state
	{
		do
		{
			if(nodeManagerReceive(pdNmi, &rxMessage))
			{
				//cDebug(4, "PD: Got message: %s from %d.%d.%d.%d\n", jausMessageCommandCodeString(rxMessage), rxMessage->source->subsystem, rxMessage->source->node, rxMessage->source->component, rxMessage->source->instance);
				pdProcessMessage(rxMessage);
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
		pdThreadHz = 1.0/(time-prevTime); // Compute the update rate of this thread
		
		switch(pd->state) // Switch component behavior based on which state the machine is in
		{
			case JAUS_INITIALIZE_STATE:
				pdInitState();
				break;
				
			case JAUS_STANDBY_STATE:
				pdStandbyState();
				break;
				
			case JAUS_READY_STATE:
				pdReadyState();
				break;
				
			case JAUS_EMERGENCY_STATE:
				pdEmergencyState();
				break;
				
			case JAUS_FAILURE_STATE:
				pdFailureState();
				break;		
						
			case JAUS_SHUTDOWN_STATE:
				pdRun = FALSE;			
				break;		

			default:
				pd->state = JAUS_FAILURE_STATE; // The default case JAUS_is undefined, therefore go into Failure State
				break;
		}	
		
		pdAllState();
		nodeManagerSendCoreServiceConnections(pdNmi);

		nextExcecuteTime = 2.0 * time + 1.0/PD_THREAD_DESIRED_RATE_HZ - getTimeSeconds();
	}	
	
	pdShutdownState();
	
	// Sleep for 50 milliseconds and then exit
	ojSleepMsec(50);

	pdThreadRunning = FALSE;
	
	return NULL;
}

// Function: pdProcessMessage
// Access:		Private
// Description:	This function is responsible for handling incoming JAUS messages from the Node Manager.
//				Incoming messages are processed according to message type.
void pdProcessMessage(JausMessage message)
{
	ReportComponentStatusMessage reportComponentStatus;
	QueryPlatformSpecificationsMessage queryPlatformSpecifications;
	ReportPlatformSpecificationsMessage reportPlatformSpecifications;
	JausMessage txMessage;
	char buf[64] = {0};

	// This block of code is intended to reject commands from non-controlling components
	if(pd->controller.active && !jausAddressEqual(message->source, pd->controller.address) && jausMessageIsRejectableCommand(message) )
	{
		jausAddressToString(message->source, buf);
		//cError("pd: Received command message %s from non-controlling component (%s).\n", jausMessageCommandCodeString(message), buf);
		jausMessageDestroy(message); // Ignore this message
		return;		
	}	

	switch(message->commandCode) // Switch the processing algorithm according to the JAUS message type
	{
		case JAUS_REPORT_COMPONENT_STATUS:
			reportComponentStatus = reportComponentStatusMessageFromJausMessage(message);
			if(reportComponentStatus)
			{
				if(jausAddressEqual(reportComponentStatus->source, pd->controller.address))
				{
					pd->controller.state = reportComponentStatus->primaryStatusCode;
				}
				reportComponentStatusMessageDestroy(reportComponentStatus);
			}
			else
			{
				//cError("pd: Error unpacking %s message.\n", jausMessageCommandCodeString(message));
			}
			jausMessageDestroy(message);
			break;
		
		case JAUS_SET_WRENCH_EFFORT:
			if(setWrenchEffort)
			{
				setWrenchEffortMessageDestroy(setWrenchEffort);
			}
			
			setWrenchEffort = setWrenchEffortMessageFromJausMessage(message);
			if(!setWrenchEffort)
			{
				//cError("pd: Error unpacking %s message\n", jausMessageCommandCodeString(message));
			}
			jausMessageDestroy(message);
			break;

		case JAUS_SET_DISCRETE_DEVICES:
			if(setDiscreteDevices)
			{
				setDiscreteDevicesMessageDestroy(setDiscreteDevices);
			}
			
			setDiscreteDevices = setDiscreteDevicesMessageFromJausMessage(message);
			if(!setDiscreteDevices)
			{
				//cError("pd: Error unpacking %s message\n", jausMessageCommandCodeString(message));
			}
			jausMessageDestroy(message);
			break;

		case JAUS_QUERY_PLATFORM_SPECIFICATIONS:
			queryPlatformSpecifications = queryPlatformSpecificationsMessageFromJausMessage(message);
			if(!queryPlatformSpecifications)
			{
				reportPlatformSpecifications = reportPlatformSpecificationsMessageCreate();
				
				jausAddressCopy(reportPlatformSpecifications->destination, queryPlatformSpecifications->source);
				jausAddressCopy(reportPlatformSpecifications->source, queryPlatformSpecifications->destination);
				
				reportPlatformSpecifications->maximumVelocityXMps = 10.0;
				
				txMessage = reportPlatformSpecificationsMessageToJausMessage(reportPlatformSpecifications);
				nodeManagerSend(pdNmi, txMessage);		
				jausMessageDestroy(txMessage);
				
				
				//cError("pd: Error unpacking %s message\n", jausMessageCommandCodeString(message));
			}
			jausMessageDestroy(message);
			
			break;

		default:
			defaultJausMessageProcessor(message, pdNmi, pd);
			break;
	}
}

void pdStartupState(void)
{
	JausService service;	

	// Populate Core Service
	if(!jausServiceAddCoreServices(pd->services))
	{
		//cError("pd: Addition of Core Services FAILED! Switching to FAILURE_STATE\n");
		pd->state = JAUS_FAILURE_STATE;
	}
	service = jausServiceCreate(pd->address->component); 
        jausServiceAddService(pd->services, service);
		

	// add each supported primitive driver input message 
	jausServiceAddInputCommand(service, JAUS_SET_WRENCH_EFFORT, 0xFF);
	jausServiceAddInputCommand(service, JAUS_SET_DISCRETE_DEVICES, 0xFF);
	
	// add each supported primitive driver output message

	scManagerAddSupportedMessage(pdNmi, JAUS_REPORT_COMPONENT_STATUS);
	scManagerAddSupportedMessage(pdNmi, JAUS_REPORT_WRENCH_EFFORT);

	setWrenchEffort = setWrenchEffortMessageCreate();

	reportWrenchEffort = reportWrenchEffortMessageCreate();
	jausAddressCopy(reportWrenchEffort->source, pd->address);

	controllerStatusSc = serviceConnectionCreate();
	controllerStatusSc->requestedUpdateRateHz = CONTROLLER_STATUS_SC_UPDATE_RATE_HZ;
	controllerStatusSc->presenceVector = CONTROLLER_STATUS_SC_PRESENCE_VECTOR;
	controllerStatusSc->commandCode = JAUS_REPORT_COMPONENT_STATUS;
	controllerStatusSc->isActive = JAUS_FALSE;
	controllerStatusSc->queueSize = CONTROLLER_STATUS_SC_QUEUE_SIZE;
	controllerStatusSc->timeoutSec = CONTROLLER_STATUS_SC_TIMEOUT_SECONDS;

	setDiscreteDevices = setDiscreteDevicesMessageCreate();
}

void pdInitState(void)
{
	if(	vehicleSimGetState() == VEHICLE_SIM_READY_STATE	)
	{
		pd->state = JAUS_STANDBY_STATE;
	}

}

void pdStandbyState(void)
{
	static double readyTransitionTime = -1;
	static int runPause = -1;
	static int prevRunPause = -1;	

	if(	vehicleSimGetState() != VEHICLE_SIM_READY_STATE )
	{
		pd->state = JAUS_EMERGENCY_STATE;
		//cError("pd: Emergency, vehicle Sim State: %d", vehicleSimGetState() );
		return;
	}

	pd->state = JAUS_READY_STATE;
	return;
}

void pdReadyState(void)
{
	static double scSendCreateTime = -1;
	char buf[128] = {0};
	
	if(	vehicleSimGetState() != VEHICLE_SIM_READY_STATE )
	{
		pd->state = JAUS_EMERGENCY_STATE;
		//cError("pd: Emergency, vehicle sim: %d", vehicleSimGetState() );
		return;
	}

	if(vehicleSimGetRunPause() != VEHICLE_SIM_RUN)
	{
		pd->state = JAUS_STANDBY_STATE;
		return;
	}		
	
	//cDebug(5, "%s", pd->controller.active? "True" : "False");

	if(pd->controller.active)
	{
		if(!controllerStatusSc->isActive)
		{
			if(getTimeSeconds() > scSendCreateTime)
			{
				// set up the service connection
				jausAddressCopy(controllerStatusSc->address, pd->controller.address);
				scManagerCreateServiceConnection(pdNmi, controllerStatusSc);
				scSendCreateTime = getTimeSeconds() + 1.0;
				
				jausAddressToString(controllerStatusSc->address, buf);
				//cDebug(5, "Sent SC Request to Controller (%s)", buf);
			}
			vehicleSimSetCommand(0, 80, 0);
		}		
		else if(getTimeSeconds() - controllerStatusSc->lastSentTime > CONTROLLER_STATUS_SC_TIMEOUT_SECONDS)
		{
			pd->state = JAUS_EMERGENCY_STATE;
			//cError("pd: Emergency, Controller status service connection timed out\n");

			if(scManagerTerminateServiceConnection(pdNmi, controllerStatusSc))
			{
				//cDebug(2, "pd: Terminated Component Status Sc\n");
			}
			else
			{
				//cError("pd: Failed to terminate controller status service connection\n");
			}
			ojSleepMsec(500);

			controllerStatusSc->isActive = JAUS_FALSE;
			pd->controller.state = JAUS_UNKNOWN_STATE;
		}
		else
		{
			if(pd->controller.state == JAUS_READY_STATE || pd->controller.state == JAUS_STANDBY_STATE)
			{
				vehicleSimSetCommand(	setWrenchEffort->propulsiveLinearEffortXPercent,
										setWrenchEffort->resistiveLinearEffortXPercent,
										setWrenchEffort->propulsiveRotationalEffortZPercent
									);
			}
			else
			{
				vehicleSimSetCommand(0, 80, 0);
			}			
		}
		
	}
	else
	{
		vehicleSimSetCommand(0, 80, 0);

		if(controllerStatusSc->isActive)
		{
			if(scManagerTerminateServiceConnection(pdNmi, controllerStatusSc))
			{
				//cDebug(2, "Terminated Component Status Sc\n");
			}
			else
			{
				//cError("pd: Failed to terminate controller status service connection\n");
			}
			ojSleepMsec(500);
			controllerStatusSc->isActive = JAUS_FALSE;
			pd->controller.state = JAUS_UNKNOWN_STATE;
		}
	}
}

void pdEmergencyState(void)
{
	vehicleSimSetCommand(0, 70, setWrenchEffort->propulsiveRotationalEffortZPercent );

	if(controllerStatusSc->isActive)
	{
		if(scManagerTerminateServiceConnection(pdNmi, controllerStatusSc))
		{
			//cDebug(2, "Terminated Component Status Sc\n");
		}
		else
		{
			//cError("pd: Failed to terminate controller status service connection\n");
		}
		ojSleepMsec(500);
		controllerStatusSc->isActive = JAUS_FALSE;
		pd->controller.state = JAUS_UNKNOWN_STATE;
	}

	if(vehicleSimGetState() == VEHICLE_SIM_MANUAL_STATE)
	{
		pd->state = JAUS_INITIALIZE_STATE;		
	}

}

void pdFailureState(void)
{
	RejectComponentControlMessage rejectComponentControl;
	JausMessage txMessage;

	if(pd->controller.active)
	{
		// Terminate control of current component
		rejectComponentControl = rejectComponentControlMessageCreate();
		jausAddressCopy(rejectComponentControl->source, pd->address);
		jausAddressCopy(rejectComponentControl->destination, pd->controller.address);
		
		txMessage = rejectComponentControlMessageToJausMessage(rejectComponentControl);
		nodeManagerSend(pdNmi, txMessage);
		jausMessageDestroy(txMessage);
		
		rejectComponentControlMessageDestroy(rejectComponentControl);
	}
	
	if(controllerStatusSc)
	{
		if(scManagerTerminateServiceConnection(pdNmi, controllerStatusSc))
		{
			//cDebug(2, "Terminated Component Status Sc\n");
		}
		else
		{
			//cError("pd: Failed to terminate controller status service connection\n");
		}
		controllerStatusSc = NULL;
		pd->controller.state = JAUS_UNKNOWN_STATE;
	}
}

void pdShutdownState(void)
{
	RejectComponentControlMessage rejectComponentControl;
	JausMessage txMessage;

	scManagerRemoveSupportedMessage(pdNmi, JAUS_REPORT_COMPONENT_STATUS);
	scManagerRemoveSupportedMessage(pdNmi, JAUS_REPORT_WRENCH_EFFORT);
		
	if(controllerStatusSc->isActive)
	{
		if(scManagerTerminateServiceConnection(pdNmi, controllerStatusSc))
		{
			//cDebug(2, "Terminated Component Status Sc\n");
		}
		else
		{
			//cError("pd: Failed to terminate controller status service connection\n");
		}
		pd->controller.state = JAUS_UNKNOWN_STATE;
	}
	serviceConnectionDestroy(controllerStatusSc);

	if(pd->controller.active)
	{
		// Terminate control of current component
		rejectComponentControl = rejectComponentControlMessageCreate();
		jausAddressCopy(rejectComponentControl->source, pd->address);
		jausAddressCopy(rejectComponentControl->destination, pd->controller.address);

		txMessage = rejectComponentControlMessageToJausMessage(rejectComponentControl);
		nodeManagerSend(pdNmi, txMessage);
		jausMessageDestroy(txMessage);

		rejectComponentControlMessageDestroy(rejectComponentControl);
	}
	
	setWrenchEffortMessageDestroy(setWrenchEffort);
	setDiscreteDevicesMessageDestroy(setDiscreteDevices);
}

void pdAllState(void)
{
	JausMessage message;
	
	if(controllerStatusSc->isActive)
	{
		if(scManagerReceiveServiceConnection(pdNmi, controllerStatusSc, &message))
		{
			pdProcessMessage(message);
		}
	}
	
	pdSendReportWrenchEffort();
}

void pdSendReportWrenchEffort(void)
{
	JausMessage txMessage;
	ServiceConnection scList;
	ServiceConnection sc;

	scList = scManagerGetSendList(pdNmi, JAUS_REPORT_WRENCH_EFFORT);
	sc = scList;
	while(sc)
	{
		jausAddressCopy(reportWrenchEffort->destination, sc->address);
		reportWrenchEffort->presenceVector = sc->presenceVector;
		reportWrenchEffort->sequenceNumber = sc->sequenceNumber;
		reportWrenchEffort->properties.scFlag = JAUS_SERVICE_CONNECTION_MESSAGE;
		
		txMessage = reportWrenchEffortMessageToJausMessage(reportWrenchEffort);
		nodeManagerSend(pdNmi, txMessage);		
		jausMessageDestroy(txMessage);

		sc = sc->nextSc;
	}
	
	scManagerDestroySendList(scList);
}

