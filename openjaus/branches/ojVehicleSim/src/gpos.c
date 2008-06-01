// File:		gpos.c 
// Version:		0.4 alpha
// Written by:	Tom Galluzzo (galluzzt@ufl.edu) and Danny Kent (kentd@ufl.edu)
// Date:		07/01/2005
// Description:	This file contains the skeleton C code for implementing a JAUS component in a Linux environment
//				This code is designed to work with the node manager and JAUS library software written by CIMAR

#include <jaus.h>			// JAUS message set (USER: JAUS libraries must be installed first)
#include <openJaus.h>	// Node managment functions for sending and receiving JAUS messages (USER: Node Manager must be installed)
#include <stdlib.h>	
#include <string.h>


#include "gpos.h"	// USER: Implement and rename this header file. Include prototypes for all public functions contained in this file.
#include "vehicleSim.h"
#include "utm/pointLla.h"

#if defined (WIN32)
	#include <math.h>
#endif

// Private function prototypes
void gposReadyState(void);
void gposShutdownState(void);
void gposQueryGlobalPoseCallback(OjCmpt gpos, JausMessage query);

//Gpos Variables
static ReportGlobalPoseMessage gposMessage;
static JausBoolean gposScActive = JAUS_FALSE;

// Function: 	gposStartup
// Access:		Public	
// Description: This function allows the abstracted component functionality contained in this file to be started from an external source.
// 				It must be called first before the component state machine and node manager interaction will begin
//				Each call to "gposStartup" should be followed by one call to the "gposShutdown" function
OjCmpt gposCreate(void)
{

	OjCmpt gpos;
	JausAddress gposAddr;
	
	gpos = ojCmptCreate(JAUS_GLOBAL_POSE_SENSOR, "gpos", GPOS_THREAD_DESIRED_RATE_HZ);

	ojCmptAddService(gpos, JAUS_GLOBAL_POSE_SENSOR);
	ojCmptAddServiceInputMessage(gpos, JAUS_GLOBAL_POSE_SENSOR, JAUS_QUERY_GLOBAL_POSE, 0xFF);
	ojCmptAddServiceOutputMessage(gpos, JAUS_GLOBAL_POSE_SENSOR, JAUS_REPORT_GLOBAL_POSE, 0xFF);

 	ojCmptSetStateCallback(gpos, JAUS_READY_STATE, gposReadyState);

	ojCmptSetMessageCallback(gpos, JAUS_QUERY_GLOBAL_POSE, gposQueryGlobalPoseCallback);
	
	ojCmptAddSupportedSc(gpos, JAUS_REPORT_GLOBAL_POSE);
	
	if(ojCmptRun(gpos))
	{
		ojCmptDestroy(gpos);
		return NULL;
	}

	gposMessage = reportGlobalPoseMessageCreate();
	
	gposAddr = ojCmptGetAddress(gpos);
	jausAddressCopy(gposMessage->source, gposAddr);
	jausAddressDestroy(gposAddr);
			
	ojCmptSetState(gpos, JAUS_READY_STATE);
	
	return gpos;
}

// Function: gposShutdown
// Access:		Public	
// Description:	This function allows the abstracted component functionality contained in this file to be stoped from an external source.
// 				If the component is in the running state, this function will terminate all threads running in this file
//				This function will also close the Jms connection to the Node Manager and check out the component from the Node Manager
void gposDestroy(OjCmpt gpos)
{	
	// Remove support for ReportGlovalPose Service Connections
	ojCmptRemoveSupportedSc(gpos, JAUS_REPORT_GLOBAL_POSE);	
	ojCmptDestroy(gpos);

	reportGlobalPoseMessageDestroy(gposMessage);
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
	jausTimeSetCurrentTime(gposMessage->time);

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