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

#define GPOS_THREAD_DESIRED_RATE_HZ			50.0

typedef struct GposData
{
	ReportGlobalPoseMessage message;
	JausBoolean scActive;
}*GposData;

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
	GposData gposData;
	JausAddress gposAddr;
	
	cmpt = ojCmptCreate("gpos", JAUS_GLOBAL_POSE_SENSOR, GPOS_THREAD_DESIRED_RATE_HZ);

	ojCmptAddService(cmpt, JAUS_GLOBAL_POSE_SENSOR);
	ojCmptAddServiceInputMessage(cmpt, JAUS_GLOBAL_POSE_SENSOR, JAUS_QUERY_GLOBAL_POSE, 0xFF);
	ojCmptAddServiceOutputMessage(cmpt, JAUS_GLOBAL_POSE_SENSOR, JAUS_REPORT_GLOBAL_POSE, 0xFF);

	ojCmptSetStateCallback(cmpt, JAUS_READY_STATE, gposReadyState);
	ojCmptSetMessageCallback(cmpt, JAUS_QUERY_GLOBAL_POSE, gposQueryGlobalPoseCallback);
	ojCmptAddSupportedSc(cmpt, JAUS_REPORT_GLOBAL_POSE);
	
	gposData = (GposData)malloc(sizeof(struct GposData));
	
	gposData->message = reportGlobalPoseMessageCreate();
	gposAddr = ojCmptGetAddress(cmpt);
	jausAddressCopy(gposData->message->source, gposAddr);
	jausAddressDestroy(gposAddr);
	
	ojCmptSetUserData(cmpt, (void *)gposData);
	
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
	GposData gposData;

	gposData = (GposData)ojCmptGetUserData(gpos);

	// Remove support for ReportGlovalPose Service Connections
	ojCmptRemoveSupportedSc(gpos, JAUS_REPORT_GLOBAL_POSE);	
	ojCmptDestroy(gpos);

	reportGlobalPoseMessageDestroy(gposData->message);	
	free(gposData);
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
	GposData gposData;

	gposData = (GposData)ojCmptGetUserData(gpos);
	
	return gposData->message->latitudeDegrees;
}

double gposGetLongitude(OjCmpt gpos)
{
	GposData gposData;

	gposData = (GposData)ojCmptGetUserData(gpos);
	return gposData->message->longitudeDegrees;
}

double gposGetYaw(OjCmpt gpos)
{
	GposData gposData;

	gposData = (GposData)ojCmptGetUserData(gpos);
	return gposData->message->yawRadians;
}

int gposGetScActive(OjCmpt gpos)
{
	return ojCmptIsOutgoingScActive(gpos, JAUS_REPORT_GLOBAL_POSE);
}

void gposQueryGlobalPoseCallback(OjCmpt gpos, JausMessage query)
{
	GposData gposData;
	JausMessage txMessage;
	QueryGlobalPoseMessage queryGlobalPose;
	
	gposData = (GposData)ojCmptGetUserData(gpos);

	queryGlobalPose = queryGlobalPoseMessageFromJausMessage(query);
	if(queryGlobalPose)
	{
		jausAddressCopy(gposData->message->destination, queryGlobalPose->source);
		gposData->message->presenceVector = queryGlobalPose->presenceVector;
		gposData->message->sequenceNumber = 0;
		gposData->message->properties.scFlag = 0;
		
		txMessage = reportGlobalPoseMessageToJausMessage(gposData->message);
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
	//char buf[64] = {0};
	//char buf2[64] = {0};
	PointLla vehiclePosLla;
	GposData gposData;
	
	gposData = (GposData)ojCmptGetUserData(gpos);
	
	vehiclePosLla = vehicleSimGetPositionLla();
	if(vehiclePosLla)
	{		
		gposData->message->latitudeDegrees = vehiclePosLla->latitudeRadians * DEG_PER_RAD;
		gposData->message->longitudeDegrees = vehiclePosLla->longitudeRadians * DEG_PER_RAD;
	}
	
	gposData->message->yawRadians = -(vehicleSimGetH() - M_PI/2.0);

	gposData->message->elevationMeters = 0;
	gposData->message->positionRmsMeters = 1.0;
	gposData->message->rollRadians = 0.0;
	gposData->message->pitchRadians = 0.0;
	gposData->message->attitudeRmsRadians = 0.05;
	jausTimeSetCurrentTime(gposData->message->time);

	// Send message
	if(ojCmptIsOutgoingScActive(gpos, JAUS_REPORT_GLOBAL_POSE))
	{
		scList = ojCmptGetScSendList(gpos, JAUS_REPORT_GLOBAL_POSE);
		sc = scList;
		while(sc)
		{
			jausAddressCopy(gposData->message->destination, sc->address);
			gposData->message->presenceVector = sc->presenceVector;
			gposData->message->sequenceNumber = sc->sequenceNumber;
			gposData->message->properties.scFlag = JAUS_SERVICE_CONNECTION_MESSAGE;
			
			txMessage = reportGlobalPoseMessageToJausMessage(gposData->message);
			ojCmptSendMessage(gpos, txMessage);
			jausMessageDestroy(txMessage);
	
			//jausAddressToString(gposData->message->source, buf);
			//jausAddressToString(gposData->message->destination, buf2);
			//cDebug(9, "Sent GPOS SC from %s to %s\n", buf, buf2);
	
			sc = sc->nextSc;
		}
		
		ojCmptDestroySendList(scList);
	}
}
