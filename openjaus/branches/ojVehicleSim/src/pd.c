// File:		pd.c 
// Version:		3.3
// Written by:	Tom Galluzzo (galluzzt@ufl.edu) and Danny Kent (kentd@ufl.edu)
// Date:		06/03/2008

#include <jaus.h>
#include <openJaus.h>
#include <stdlib.h>	
#include <string.h>
#include "vehicleSim.h"
#include "pd.h"

#define CONTROLLER_STATUS_SC_TIMEOUT_SECONDS 	1.5
#define CONTROLLER_STATUS_SC_UPDATE_RATE_HZ		5.0
#define CONTROLLER_STATUS_SC_QUEUE_SIZE			1
#define CONTROLLER_STATUS_SC_PRESENCE_VECTOR	0
#define CONFIRM_SC_TIMEOUT_SEC		3.0


// USER: Insert any private function prototypes here
void pdSendReportWrenchEffort(void);
void pdInitState(OjCmpt pd);
void pdReadyState(OjCmpt pd);
void pdProcessMessage(OjCmpt pd, JausMessage message);

typedef struct
{
	SetWrenchEffortMessage setWrenchEffort;
	SetDiscreteDevicesMessage setDiscreteDevices;
	ReportWrenchEffortMessage reportWrenchEffort;
	ReportComponentStatusMessage controllerStatus;
	int controllerSc;
}PdData;

OjCmpt pdCreate(void)
{
	OjCmpt cmpt;
	PdData *data;
	JausAddress pdAddr;
	
	cmpt = ojCmptCreate("pd", JAUS_PRIMITIVE_DRIVER, PD_THREAD_DESIRED_RATE_HZ);

	ojCmptAddService(cmpt, JAUS_PRIMITIVE_DRIVER);
	ojCmptAddServiceInputMessage(cmpt, JAUS_PRIMITIVE_DRIVER, JAUS_SET_WRENCH_EFFORT, 0xFF);
	ojCmptAddServiceInputMessage(cmpt, JAUS_PRIMITIVE_DRIVER, JAUS_SET_DISCRETE_DEVICES, 0xFF);
	ojCmptAddServiceInputMessage(cmpt, JAUS_PRIMITIVE_DRIVER, JAUS_QUERY_PLATFORM_SPECIFICATIONS, 0xFF);
	ojCmptAddServiceInputMessage(cmpt, JAUS_PRIMITIVE_DRIVER, JAUS_QUERY_WRENCH_EFFORT, 0xFF);
	ojCmptAddServiceOutputMessage(cmpt, JAUS_PRIMITIVE_DRIVER, JAUS_REPORT_PLATFORM_SPECIFICATIONS, 0xFF);
	ojCmptAddServiceOutputMessage(cmpt, JAUS_PRIMITIVE_DRIVER, JAUS_REPORT_WRENCH_EFFORT, 0xFF);
	ojCmptAddSupportedSc(cmpt, JAUS_REPORT_WRENCH_EFFORT);

	ojCmptSetMessageProcessorCallback(cmpt, pdProcessMessage);
	ojCmptSetStateCallback(cmpt, JAUS_INITIALIZE_STATE, pdInitState);
	ojCmptSetStateCallback(cmpt, JAUS_READY_STATE, pdReadyState);
	ojCmptSetState(cmpt, JAUS_INITIALIZE_STATE);
	
	pdAddr = ojCmptGetAddress(cmpt);

	data = (PdData*)malloc(sizeof(PdData));
	data->setWrenchEffort = setWrenchEffortMessageCreate();
	data->setDiscreteDevices = setDiscreteDevicesMessageCreate();
	data->reportWrenchEffort = reportWrenchEffortMessageCreate();
	data->controllerStatus = reportComponentStatusMessageCreate();
	jausAddressCopy(data->reportWrenchEffort->source, pdAddr);

	jausAddressDestroy(pdAddr);

	ojCmptSetUserData(cmpt, (void *)data);
		
	if(ojCmptRun(cmpt))
	{
		ojCmptDestroy(cmpt);
		return NULL;
	}

	return cmpt;
}

void pdDestroy(OjCmpt pd)
{
	PdData *data;
	
	data = (PdData*)ojCmptGetUserData(pd);

	if(ojCmptIsIncomingScActive(pd, data->controllerSc))
	{
		ojCmptTerminateSc(pd, data->controllerSc);
	}
	ojCmptRemoveSupportedSc(pd, JAUS_REPORT_WRENCH_EFFORT);
	ojCmptDestroy(pd);


	setWrenchEffortMessageDestroy(data->setWrenchEffort);
	setDiscreteDevicesMessageDestroy(data->setDiscreteDevices);
	reportWrenchEffortMessageDestroy(data->reportWrenchEffort);
	reportComponentStatusMessageDestroy(data->controllerStatus);
	free(data);
}

//// The series of functions below allow public access to essential component information
//// Access:		Public (All)
//JausState pdGetState(void)
//{
//	return pd->state;
//}
//
//JausAddress pdGetAddress(void)
//{
//	return pd->address;
//}
//
//double pdGetUpdateRate(void)
//{
//	return pdThreadHz; 
//}
//
//JausBoolean pdGetControllerScStatus(void)
//{
//	return controllerStatusSc ? controllerStatusSc->isActive : JAUS_FALSE;
//}
//
//JausBoolean pdGetControllerStatus(void)
//{
//	return pd->controller.active;
//}
//
//JausState pdGetControllerState(void)
//{
//	return pd->controller.state;
//}
//
//JausAddress pdGetControllerAddress(void)
//{
//	return pd->controller.address;
//}
//
//SetWrenchEffortMessage pdGetWrenchEffort(void)
//{
//	return setWrenchEffort;
//}
//
//// Function: pdProcessMessage
//// Access:		Private
//// Description:	This function is responsible for handling incoming JAUS messages from the Node Manager.
////				Incoming messages are processed according to message type.
//void pdProcessMessage(JausMessage message)
//{
//	ReportComponentStatusMessage reportComponentStatus;
//	QueryPlatformSpecificationsMessage queryPlatformSpecifications;
//	ReportPlatformSpecificationsMessage reportPlatformSpecifications;
//	JausMessage txMessage;
//	char buf[64] = {0};
//
//	// This block of code is intended to reject commands from non-controlling components
//	if(pd->controller.active && !jausAddressEqual(message->source, pd->controller.address) && jausMessageIsRejectableCommand(message) )
//	{
//		jausAddressToString(message->source, buf);
//		//cError("pd: Received command message %s from non-controlling component (%s).\n", jausMessageCommandCodeString(message), buf);
//		jausMessageDestroy(message); // Ignore this message
//		return;		
//	}	
//
//	switch(message->commandCode) // Switch the processing algorithm according to the JAUS message type
//	{
//		case JAUS_REPORT_COMPONENT_STATUS:
//			reportComponentStatus = reportComponentStatusMessageFromJausMessage(message);
//			if(reportComponentStatus)
//			{
//				if(jausAddressEqual(reportComponentStatus->source, pd->controller.address))
//				{
//					pd->controller.state = reportComponentStatus->primaryStatusCode;
//				}
//				reportComponentStatusMessageDestroy(reportComponentStatus);
//			}
//			else
//			{
//				//cError("pd: Error unpacking %s message.\n", jausMessageCommandCodeString(message));
//			}
//			jausMessageDestroy(message);
//			break;
//		
//		case JAUS_SET_WRENCH_EFFORT:
//			if(setWrenchEffort)
//			{
//				setWrenchEffortMessageDestroy(setWrenchEffort);
//			}
//			
//			setWrenchEffort = setWrenchEffortMessageFromJausMessage(message);
//			if(!setWrenchEffort)
//			{
//				//cError("pd: Error unpacking %s message\n", jausMessageCommandCodeString(message));
//			}
//			jausMessageDestroy(message);
//			break;
//
//		case JAUS_SET_DISCRETE_DEVICES:
//			if(setDiscreteDevices)
//			{
//				setDiscreteDevicesMessageDestroy(setDiscreteDevices);
//			}
//			
//			setDiscreteDevices = setDiscreteDevicesMessageFromJausMessage(message);
//			if(!setDiscreteDevices)
//			{
//				//cError("pd: Error unpacking %s message\n", jausMessageCommandCodeString(message));
//			}
//			jausMessageDestroy(message);
//			break;
//
//		case JAUS_QUERY_PLATFORM_SPECIFICATIONS:
//			queryPlatformSpecifications = queryPlatformSpecificationsMessageFromJausMessage(message);
//			if(!queryPlatformSpecifications)
//			{
//				reportPlatformSpecifications = reportPlatformSpecificationsMessageCreate();
//				
//				jausAddressCopy(reportPlatformSpecifications->destination, queryPlatformSpecifications->source);
//				jausAddressCopy(reportPlatformSpecifications->source, queryPlatformSpecifications->destination);
//				
//				reportPlatformSpecifications->maximumVelocityXMps = 10.0;
//				
//				txMessage = reportPlatformSpecificationsMessageToJausMessage(reportPlatformSpecifications);
//				nodeManagerSend(pdNmi, txMessage);		
//				jausMessageDestroy(txMessage);
//				
//				
//				//cError("pd: Error unpacking %s message\n", jausMessageCommandCodeString(message));
//			}
//			jausMessageDestroy(message);
//			
//			break;
//
//		default:
//			defaultJausMessageProcessor(message, pdNmi, pd);
//			break;
//	}
//}
//
//void pdInitState(void)
//{
//	if(	vehicleSimGetState() == VEHICLE_SIM_READY_STATE	)
//	{
//		pd->state = JAUS_READY_STATE;
//	}
//	pdSendReportWrenchEffort();
//}
//
//void pdReadyState(void)
//{
//	static double scSendCreateTime = -1;
//	char buf[128] = {0};
//	
//	if(	vehicleSimGetState() != VEHICLE_SIM_READY_STATE )
//	{
//		pd->state = JAUS_EMERGENCY_STATE;
//		//cError("pd: Emergency, vehicle sim: %d", vehicleSimGetState() );
//		return;
//	}
//
//	if(vehicleSimGetRunPause() != VEHICLE_SIM_RUN)
//	{
//		pd->state = JAUS_STANDBY_STATE;
//		return;
//	}		
//	
//	//cDebug(5, "%s", pd->controller.active? "True" : "False");
//
//	if(pd->controller.active)
//	{
//		if(!controllerStatusSc->isActive)
//		{
//			if(getTimeSeconds() > scSendCreateTime)
//			{
//				// set up the service connection
//				jausAddressCopy(controllerStatusSc->address, pd->controller.address);
//				scManagerCreateServiceConnection(pdNmi, controllerStatusSc);
//				scSendCreateTime = getTimeSeconds() + 1.0;
//				
//				jausAddressToString(controllerStatusSc->address, buf);
//				//cDebug(5, "Sent SC Request to Controller (%s)", buf);
//			}
//			vehicleSimSetCommand(0, 80, 0);
//		}		
//		else if(getTimeSeconds() - controllerStatusSc->lastSentTime > CONTROLLER_STATUS_SC_TIMEOUT_SECONDS)
//		{
//			pd->state = JAUS_EMERGENCY_STATE;
//			//cError("pd: Emergency, Controller status service connection timed out\n");
//
//			if(scManagerTerminateServiceConnection(pdNmi, controllerStatusSc))
//			{
//				//cDebug(2, "pd: Terminated Component Status Sc\n");
//			}
//			else
//			{
//				//cError("pd: Failed to terminate controller status service connection\n");
//			}
//			ojSleepMsec(500);
//
//			controllerStatusSc->isActive = JAUS_FALSE;
//			pd->controller.state = JAUS_UNKNOWN_STATE;
//		}
//		else
//		{
//			if(pd->controller.state == JAUS_READY_STATE || pd->controller.state == JAUS_STANDBY_STATE)
//			{
//				vehicleSimSetCommand(	setWrenchEffort->propulsiveLinearEffortXPercent,
//										setWrenchEffort->resistiveLinearEffortXPercent,
//										setWrenchEffort->propulsiveRotationalEffortZPercent
//									);
//			}
//			else
//			{
//				vehicleSimSetCommand(0, 80, 0);
//			}			
//		}
//		
//	}
//	else
//	{
//		vehicleSimSetCommand(0, 80, 0);
//
//		if(controllerStatusSc->isActive)
//		{
//			if(scManagerTerminateServiceConnection(pdNmi, controllerStatusSc))
//			{
//				//cDebug(2, "Terminated Component Status Sc\n");
//			}
//			else
//			{
//				//cError("pd: Failed to terminate controller status service connection\n");
//			}
//			ojSleepMsec(500);
//			controllerStatusSc->isActive = JAUS_FALSE;
//			pd->controller.state = JAUS_UNKNOWN_STATE;
//		}
//	}
//	pdSendReportWrenchEffort();
//}
//
//void pdEmergencyState(void)
//{
//	vehicleSimSetCommand(0, 70, setWrenchEffort->propulsiveRotationalEffortZPercent );
//
//	if(controllerStatusSc->isActive)
//	{
//		if(scManagerTerminateServiceConnection(pdNmi, controllerStatusSc))
//		{
//			//cDebug(2, "Terminated Component Status Sc\n");
//		}
//		else
//		{
//			//cError("pd: Failed to terminate controller status service connection\n");
//		}
//		ojSleepMsec(500);
//		controllerStatusSc->isActive = JAUS_FALSE;
//		pd->controller.state = JAUS_UNKNOWN_STATE;
//	}
//
//	if(vehicleSimGetState() == VEHICLE_SIM_MANUAL_STATE)
//	{
//		pd->state = JAUS_INITIALIZE_STATE;		
//	}
//
//	pdSendReportWrenchEffort();
//}
//
//void pdFailureState(void)
//{
//	RejectComponentControlMessage rejectComponentControl;
//	JausMessage txMessage;
//
//	if(pd->controller.active)
//	{
//		// Terminate control of current component
//		rejectComponentControl = rejectComponentControlMessageCreate();
//		jausAddressCopy(rejectComponentControl->source, pd->address);
//		jausAddressCopy(rejectComponentControl->destination, pd->controller.address);
//		
//		txMessage = rejectComponentControlMessageToJausMessage(rejectComponentControl);
//		nodeManagerSend(pdNmi, txMessage);
//		jausMessageDestroy(txMessage);
//		
//		rejectComponentControlMessageDestroy(rejectComponentControl);
//	}
//	
//	if(controllerStatusSc)
//	{
//		if(scManagerTerminateServiceConnection(pdNmi, controllerStatusSc))
//		{
//			//cDebug(2, "Terminated Component Status Sc\n");
//		}
//		else
//		{
//			//cError("pd: Failed to terminate controller status service connection\n");
//		}
//		controllerStatusSc = NULL;
//		pd->controller.state = JAUS_UNKNOWN_STATE;
//	}
//}
//
//void pdShutdownState(void)
//{
//	RejectComponentControlMessage rejectComponentControl;
//	JausMessage txMessage;
//
//	scManagerRemoveSupportedMessage(pdNmi, JAUS_REPORT_COMPONENT_STATUS);
//	scManagerRemoveSupportedMessage(pdNmi, JAUS_REPORT_WRENCH_EFFORT);
//		
//	if(controllerStatusSc->isActive)
//	{
//		if(scManagerTerminateServiceConnection(pdNmi, controllerStatusSc))
//		{
//			//cDebug(2, "Terminated Component Status Sc\n");
//		}
//		else
//		{
//			//cError("pd: Failed to terminate controller status service connection\n");
//		}
//		pd->controller.state = JAUS_UNKNOWN_STATE;
//	}
//	serviceConnectionDestroy(controllerStatusSc);
//
//	if(pd->controller.active)
//	{
//		// Terminate control of current component
//		rejectComponentControl = rejectComponentControlMessageCreate();
//		jausAddressCopy(rejectComponentControl->source, pd->address);
//		jausAddressCopy(rejectComponentControl->destination, pd->controller.address);
//
//		txMessage = rejectComponentControlMessageToJausMessage(rejectComponentControl);
//		nodeManagerSend(pdNmi, txMessage);
//		jausMessageDestroy(txMessage);
//
//		rejectComponentControlMessageDestroy(rejectComponentControl);
//	}
//	
//	setWrenchEffortMessageDestroy(setWrenchEffort);
//	setDiscreteDevicesMessageDestroy(setDiscreteDevices);
//}
//
//void pdSendReportWrenchEffort(void)
//{
//	JausMessage txMessage;
//	ServiceConnection scList;
//	ServiceConnection sc;
//
//	scList = scManagerGetSendList(pdNmi, JAUS_REPORT_WRENCH_EFFORT);
//	sc = scList;
//	while(sc)
//	{
//		jausAddressCopy(reportWrenchEffort->destination, sc->address);
//		reportWrenchEffort->presenceVector = sc->presenceVector;
//		reportWrenchEffort->sequenceNumber = sc->sequenceNumber;
//		reportWrenchEffort->properties.scFlag = JAUS_SERVICE_CONNECTION_MESSAGE;
//		
//		txMessage = reportWrenchEffortMessageToJausMessage(reportWrenchEffort);
//		nodeManagerSend(pdNmi, txMessage);		
//		jausMessageDestroy(txMessage);
//
//		sc = sc->nextSc;
//	}
//	
//	scManagerDestroySendList(scList);
//}
//
