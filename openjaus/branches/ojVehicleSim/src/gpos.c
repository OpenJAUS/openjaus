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
	#define _USE_MATH_DEFINES
	#include <math.h>
#endif

#define GPOS_THREAD_DESIRED_RATE_HZ			50.0

// Private function prototypes
void gposReadyState(OjCmpt gpos);
void gposQueryGlobalPoseCallback(OjCmpt gpos, JausMessage query);

// Function: 	gposStartup
// Access:		Public	
// Description: This function allows the abstracted component functionality contained in this file to be started from an external source.
// 				It must be called first before the component state machine and node manager interaction will begin
//				Each call to "gposStartup" should be followed by one call to the "gposShutdown" function
OjCmpt gposCreate(void)
{
	OjCmpt cmpt;
	ReportGlobalPoseMessage message;
	JausAddress gposAddr;
	
	cmpt = ojCmptCreate("gpos", JAUS_GLOBAL_POSE_SENSOR, GPOS_THREAD_DESIRED_RATE_HZ);

	ojCmptAddService(cmpt, JAUS_GLOBAL_POSE_SENSOR);
	ojCmptAddServiceInputMessage(cmpt, JAUS_GLOBAL_POSE_SENSOR, JAUS_QUERY_GLOBAL_POSE, 0xFF);
	ojCmptAddServiceOutputMessage(cmpt, JAUS_GLOBAL_POSE_SENSOR, JAUS_REPORT_GLOBAL_POSE, 0xFF);

	ojCmptSetStateCallback(cmpt, JAUS_READY_STATE, gposReadyState);
	ojCmptSetMessageCallback(cmpt, JAUS_QUERY_GLOBAL_POSE, gposQueryGlobalPoseCallback);
	ojCmptAddSupportedSc(cmpt, JAUS_REPORT_GLOBAL_POSE);
	
	message = reportGlobalPoseMessageCreate();
	gposAddr = ojCmptGetAddress(cmpt);
	jausAddressCopy(message->source, gposAddr);
	jausAddressDestroy(gposAddr);
	
	ojCmptSetUserData(cmpt, (void *)message);
	
	ojCmptSetState(cmpt, JAUS_READY_STATE);

	if(ojCmptRun(cmpt))
	{
		ojCmptDestroy(cmpt);
		return NULL;
	}

	return cmpt;
}

// Function: gposShutdown
// Access:		Public	
// Description:	This function allows the abstracted component functionality contained in this file to be stoped from an external source.
// 				If the component is in the running state, this function will terminate all threads running in this file
//				This function will also close the Jms connection to the Node Manager and check out the component from the Node Manager
void gposDestroy(OjCmpt gpos)
{	
	ReportGlobalPoseMessage message;
	
	message = (ReportGlobalPoseMessage)ojCmptGetUserData(gpos);

	// Remove support for ReportGlovalPose Service Connections
	ojCmptRemoveSupportedSc(gpos, JAUS_REPORT_GLOBAL_POSE);	
	ojCmptDestroy(gpos);

	reportGlobalPoseMessageDestroy(message);	
}

// The series of functions below allow public access to essential component information
// Access:		Public (All)
JausState gposGetState(OjCmpt gpos)
{
	return ojCmptGetState(gpos);
}

JausAddress gposGetAddress(OjCmpt gpos)
{
	return ojCmptGetAddress(gpos);
}

double gposGetUpdateRate(OjCmpt gpos)
{
	return ojCmptGetRateHz(gpos); 
}

double gposGetLatitude(OjCmpt gpos)
{
	ReportGlobalPoseMessage message;

	message = (ReportGlobalPoseMessage)ojCmptGetUserData(gpos);
	
	return message->latitudeDegrees;
}

double gposGetLongitude(OjCmpt gpos)
{
	ReportGlobalPoseMessage message;

	message = (ReportGlobalPoseMessage)ojCmptGetUserData(gpos);
	return message->longitudeDegrees;
}

double gposGetYaw(OjCmpt gpos)
{
	ReportGlobalPoseMessage message;

	message = (ReportGlobalPoseMessage)ojCmptGetUserData(gpos);
	return message->yawRadians;
}

int gposGetScActive(OjCmpt gpos)
{
	return ojCmptIsOutgoingScActive(gpos, JAUS_REPORT_GLOBAL_POSE);
}

void gposQueryGlobalPoseCallback(OjCmpt gpos, JausMessage query)
{
	ReportGlobalPoseMessage message;
	JausMessage txMessage;
	QueryGlobalPoseMessage queryGlobalPose;
	
	message = (ReportGlobalPoseMessage)ojCmptGetUserData(gpos);

	queryGlobalPose = queryGlobalPoseMessageFromJausMessage(query);
	if(queryGlobalPose)
	{
		jausAddressCopy(message->destination, queryGlobalPose->source);
		message->presenceVector = queryGlobalPose->presenceVector;
		message->sequenceNumber = 0;
		message->properties.scFlag = 0;
		
		txMessage = reportGlobalPoseMessageToJausMessage(message);
		ojCmptSendMessage(gpos, txMessage);		
		jausMessageDestroy(txMessage);
		
		queryGlobalPoseMessageDestroy(queryGlobalPose);
	}
	else
	{
		////cError("gpos: Error unpacking %s message.\n", jausMessageCommandCodeString(message));
	}
	
	jausMessageDestroy(query);
}

void gposReadyState(OjCmpt gpos)
{
	JausMessage txMessage;
	ServiceConnection scList;
	ServiceConnection sc;
	PointLla vehiclePosLla;
	ReportGlobalPoseMessage message;
	
	message = (ReportGlobalPoseMessage)ojCmptGetUserData(gpos);
	
	vehiclePosLla = vehicleSimGetPositionLla();
	if(vehiclePosLla)
	{		
		message->latitudeDegrees = vehiclePosLla->latitudeRadians * DEG_PER_RAD;
		message->longitudeDegrees = vehiclePosLla->longitudeRadians * DEG_PER_RAD;
	}
	
	message->yawRadians = -(vehicleSimGetH() - M_PI/2.0);

	message->elevationMeters = 0;
	message->positionRmsMeters = 1.0;
	message->rollRadians = 0.0;
	message->pitchRadians = 0.0;
	message->attitudeRmsRadians = 0.05;
	jausTimeSetCurrentTime(message->time);

	// Send message
	if(ojCmptIsOutgoingScActive(gpos, JAUS_REPORT_GLOBAL_POSE))
	{
		scList = ojCmptGetScSendList(gpos, JAUS_REPORT_GLOBAL_POSE);
		sc = scList;
		while(sc)
		{
			jausAddressCopy(message->destination, sc->address);
			message->presenceVector = sc->presenceVector;
			message->sequenceNumber = sc->sequenceNumber;
			message->properties.scFlag = JAUS_SERVICE_CONNECTION_MESSAGE;
			
			txMessage = reportGlobalPoseMessageToJausMessage(message);
			ojCmptSendMessage(gpos, txMessage);
			jausMessageDestroy(txMessage);
	
			sc = sc->nextSc;
		}
		
		ojCmptDestroySendList(scList);
	}
}
