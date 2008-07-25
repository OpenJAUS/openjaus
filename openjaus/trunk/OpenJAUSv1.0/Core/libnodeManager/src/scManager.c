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
// File:		scManager.c
// Version:		3.2
// Written by:	Tom Galluzzo (galluzzo AT gmail DOT com) and 
//              Danny Kent (jaus AT dannykent DOT com)
// Date:		08/04/06
// Description:	Provides the core service connection management routines

#include <cimar.h>
#include <cimar/jaus.h>
#include <stdlib.h>
#include "nodeManager.h"

SupportedScMessage scFindSupportedScMsgInList(SupportedScMessage, unsigned short);
ServiceConnection scFindScInList(ServiceConnection, ServiceConnection);
int scGetAvailableInstanceId(ServiceConnection, ServiceConnection);

ServiceConnection serviceConnectionCreate(void)
{
	ServiceConnection sc;
	
	sc = (ServiceConnection) malloc(sizeof(ServiceConnectionStruct));
	if(sc)
	{
		sc->address = jausAddressCreate();
		sc->queryMessage = NULL;
		sc->queue = queueCreate();
		sc->serviceConnectionType = 0;
		return sc;
	}
	else
	{
		return NULL;
	}
}

void serviceConnectionDestroy(ServiceConnection sc)
{
	jausAddressDestroy(sc->address);
	if(sc->serviceConnectionType == SC_EVENT_TYPE) 
	{
		jausMessageDestroy(sc->queryMessage);
	}
	queueDestroy(sc->queue, (void *)jausMessageDestroy);
	free(sc);
}

ServiceConnectionManager scManagerCreate(void)
{
	ServiceConnectionManager scm = NULL;
	
	scm = (ServiceConnectionManager)malloc(sizeof(ServiceConnectionManagerStruct));
	if(scm == NULL)
	{
		return NULL;
	}
	
	scm->supportedScMsgList = NULL;
	scm->incommingSc = NULL;
	scm->supportedScMsgCount = 0;
	scm->outgoingScCount = 0;
	scm->incommingScCount = 0;
	
	return scm;	
}

void scManagerDestroy(ServiceConnectionManager scm)
{
	SupportedScMessage supportedScMsg;
	ServiceConnection sc;
	
	// Only attempt to destroy the scm if it is a non-NULL pointer
	if(scm == NULL)
	{
		return;
	}
	
	// Free the supported message list
	while(scm->supportedScMsgList)
	{
		supportedScMsg = scm->supportedScMsgList;
		scm->supportedScMsgList = supportedScMsg->nextSupportedScMsg;
		
		// Free all the service connections
		while(supportedScMsg->scList)
		{
			sc = supportedScMsg->scList;
			supportedScMsg->scList = sc->nextSc;
			serviceConnectionDestroy(sc);
		}
		
		free(supportedScMsg);
	}
	
	free(scm);	
}

void scManagerProcessConfirmScMessage(NodeManagerInterface nmi, ConfirmServiceConnectionMessage message)
{
	ServiceConnection prevSc = NULL;
	ServiceConnection sc = nmi->scm->incommingSc;
	TerminateServiceConnectionMessage terminateSc;	
	JausMessage txMessage;
	
	while(sc)
	{
		if(	sc->commandCode == message->serviceConnectionCommandCode && sc->address->id == message->source->id )
		{
			if( message->responseCode == JAUS_SC_SUCCESSFUL )
			{
				sc->confirmedUpdateRateHz = message->confirmedPeriodicUpdateRateHertz;
				sc->instanceId = message->instanceId;
				sc->isActive = JAUS_TRUE;
				sc->sequenceNumber = 65535;
				sc->lastSentTime = getTimeSeconds();
			}
			else
			{
				// Set SC Inactive
				sc->isActive = JAUS_FALSE;

				// Remove Service Connection
				if(prevSc)
				{
					prevSc->nextSc = sc->nextSc;
					sc->nextSc = NULL;
				}
				else
				{
					nmi->scm->incommingSc = sc->nextSc;
					sc->nextSc = NULL;
				}
				nmi->scm->incommingScCount--;
			}
			return;
		}
		prevSc = sc;
		sc = sc->nextSc;
	}

	// The SC was not found, so send a terminate to prevent streaming
	if( message->responseCode == JAUS_SC_SUCCESSFUL )
	{
		terminateSc = terminateServiceConnectionMessageCreate();
		terminateSc->source->id = nmi->cmpt->address->id;
		terminateSc->destination->id = message->source->id;
		terminateSc->serviceConnectionCommandCode = message->serviceConnectionCommandCode;
		terminateSc->instanceId = message->instanceId;
		
		txMessage = terminateServiceConnectionMessageToJausMessage(terminateSc);
		nodeManagerSend(nmi, txMessage);
		jausMessageDestroy(txMessage);
	
		terminateServiceConnectionMessageDestroy(terminateSc);
	}
}

void scManagerProcessCreateScMessage(NodeManagerInterface nmi, CreateServiceConnectionMessage message)
{
	SupportedScMessage supportedScMsg;
	ServiceConnection sc;
	ServiceConnection newSc;
	JausMessage txMessage;
	ConfirmServiceConnectionMessage confScMsg;
	
	supportedScMsg = scFindSupportedScMsgInList(nmi->scm->supportedScMsgList, message->serviceConnectionCommandCode);
	if(supportedScMsg == NULL)
	{
		confScMsg = confirmServiceConnectionMessageCreate();
		confScMsg->source->id = nmi->cmpt->address->id;
		confScMsg->destination->id = message->source->id;
		confScMsg->serviceConnectionCommandCode = message->serviceConnectionCommandCode;
		confScMsg->instanceId = 0;
		confScMsg->confirmedPeriodicUpdateRateHertz = 0;
		confScMsg->responseCode = JAUS_SC_COMPONENT_NOT_CAPABLE;
	
		txMessage = confirmServiceConnectionMessageToJausMessage(confScMsg); 
		nodeManagerSend(nmi, txMessage);
		jausMessageDestroy(txMessage);	
	
		confirmServiceConnectionMessageDestroy(confScMsg);
		return;
	}
	
	newSc = (ServiceConnection)malloc( sizeof(ServiceConnectionStruct) );
	if(newSc == NULL) 
	{
		// Send negative conf (could not create sc)
		confScMsg = confirmServiceConnectionMessageCreate();
		confScMsg->source->id = nmi->cmpt->address->id;
		confScMsg->destination->id = message->source->id;
		confScMsg->serviceConnectionCommandCode = sc->commandCode;
		confScMsg->instanceId = 0;
		confScMsg->confirmedPeriodicUpdateRateHertz = 0;
		confScMsg->responseCode = JAUS_SC_CONNECTION_REFUSED;
	
		txMessage = confirmServiceConnectionMessageToJausMessage(confScMsg); 
		nodeManagerSend(nmi, txMessage);
		jausMessageDestroy(txMessage);	
	
		confirmServiceConnectionMessageDestroy(confScMsg);
		return;
	}
	
	newSc->serviceConnectionType = SC_REFERENCE_TYPE;
	newSc->commandCode = message->serviceConnectionCommandCode;
	newSc->presenceVector = message->presenceVector;
	newSc->address = jausAddressCreate();
	newSc->address->id = message->source->id;
	newSc->instanceId = scGetAvailableInstanceId(supportedScMsg->scList, newSc);
	if(newSc->instanceId == -1)
	{
		// Send negative conf (could not create sc)
		confScMsg = confirmServiceConnectionMessageCreate();
		confScMsg->source->id = nmi->cmpt->address->id;
		confScMsg->destination->id = message->source->id;
		confScMsg->serviceConnectionCommandCode = sc->commandCode;
		confScMsg->instanceId = 0;
		confScMsg->confirmedPeriodicUpdateRateHertz = 0;
		confScMsg->responseCode = JAUS_SC_CONNECTION_REFUSED;
	
		txMessage = confirmServiceConnectionMessageToJausMessage(confScMsg); 
		nodeManagerSend(nmi, txMessage);
		jausMessageDestroy(txMessage);	
	
		confirmServiceConnectionMessageDestroy(confScMsg);

		jausAddressDestroy(newSc->address);
		free(newSc);
		return;
	}
	newSc->queue = NULL;
	newSc->queueSize = 0;

	sc = scFindScInList(supportedScMsg->scList, newSc);
	if(sc == NULL) // Test to see if the sc does not already exist	
	{
		// The sc doesent exist, so we insert the new one into the list
		sc = newSc;
		sc->nextSc = supportedScMsg->scList;
		supportedScMsg->scList = sc;
		nmi->scm->outgoingScCount++;
	}
	else
	{
		jausAddressDestroy(newSc->address);
		free(newSc);
	}

	sc->requestedUpdateRateHz = message->requestedPeriodicUpdateRateHertz;
	sc->lastSentTime = 0.0;
	sc->sequenceNumber = 0;
	sc->isActive = JAUS_TRUE;
	sc->confirmedUpdateRateHz = message->requestedPeriodicUpdateRateHertz;	// TODO: calculate confirmedUpdateRateHz
	
	confScMsg = confirmServiceConnectionMessageCreate();
	confScMsg->source->id = nmi->cmpt->address->id;
	confScMsg->destination->id = message->source->id;
	confScMsg->serviceConnectionCommandCode = sc->commandCode;
	confScMsg->instanceId = (JausByte)sc->instanceId;
	confScMsg->confirmedPeriodicUpdateRateHertz = sc->confirmedUpdateRateHz;
	confScMsg->responseCode = JAUS_SC_SUCCESSFUL;

	txMessage = confirmServiceConnectionMessageToJausMessage(confScMsg); 
	nodeManagerSend(nmi, txMessage);
	jausMessageDestroy(txMessage);	

	confirmServiceConnectionMessageDestroy(confScMsg);
}

void scManagerProcessActivateScMessage(NodeManagerInterface nmi, ActivateServiceConnectionMessage message)
{
	SupportedScMessage supportedScMsg;
	ServiceConnection sc;
	ServiceConnection messageSc;

	supportedScMsg = scFindSupportedScMsgInList(nmi->scm->supportedScMsgList, message->serviceConnectionCommandCode);
	if(supportedScMsg == NULL)
	{
		return;
	}

	messageSc = (ServiceConnection)malloc( sizeof(ServiceConnectionStruct) );
	if(messageSc == NULL) 
	{
		return;
	}

	messageSc->address = jausAddressCreate();
	messageSc->address->id = message->source->id;
	messageSc->instanceId = message->instanceId;

	sc = scFindScInList(supportedScMsg->scList, messageSc);
	if(sc != NULL)
	{
		sc->isActive = JAUS_TRUE;
	}
		
	jausAddressDestroy(messageSc->address);
	free(messageSc);	
}

void scManagerProcessSuspendScMessage(NodeManagerInterface nmi, SuspendServiceConnectionMessage message)
{
	SupportedScMessage supportedScMsg;
	ServiceConnection sc;
	ServiceConnection messageSc;

	supportedScMsg = scFindSupportedScMsgInList(nmi->scm->supportedScMsgList, message->serviceConnectionCommandCode);
	if(supportedScMsg == NULL)
	{
		return;
	}

	messageSc = (ServiceConnection)malloc( sizeof(ServiceConnectionStruct) );
	if(messageSc == NULL) 
	{
		return;
	}

	messageSc->address = jausAddressCreate();
	messageSc->address->id = message->source->id;
	messageSc->instanceId = message->instanceId;

	sc = scFindScInList(supportedScMsg->scList, messageSc);
	if(sc != NULL)
	{
		sc->isActive = JAUS_FALSE;
	}
	
	jausAddressDestroy(messageSc->address);
	free(messageSc);		
}

void scManagerProcessTerminateScMessage(NodeManagerInterface nmi, TerminateServiceConnectionMessage message)
{
	SupportedScMessage supportedScMsg;
	ServiceConnection sc;
	ServiceConnection prevSc;
	
	supportedScMsg = scFindSupportedScMsgInList(nmi->scm->supportedScMsgList, message->serviceConnectionCommandCode);
	if(supportedScMsg == NULL)
	{
		return;
	}

	if( supportedScMsg->scList == NULL )
	{
		return;
	}

	sc = supportedScMsg->scList;
	
	if(	sc->address->id == message->source->id &&
		sc->commandCode == message->serviceConnectionCommandCode &&
		sc->instanceId == message->instanceId )
	{
		// Remove sc from list
		supportedScMsg->scList = sc->nextSc;
		serviceConnectionDestroy(sc);
		nmi->scm->outgoingScCount--;
		return;
	}
	
	prevSc = sc;
	sc = prevSc->nextSc;
	while(sc)
	{
		if(	sc->address->id == message->source->id &&
			sc->commandCode == message->serviceConnectionCommandCode &&
			sc->instanceId == message->instanceId )
		{
			// Remove sc from list
			prevSc->nextSc = sc->nextSc;			
			serviceConnectionDestroy(sc);
			nmi->scm->outgoingScCount--;
			return;
		}	
		prevSc = sc;	
		sc = sc->nextSc;
	}
	
}

void scManagerProcessUpdatedSubystem(NodeManagerInterface nmi, JausSubsystem subsystem)
{
	SupportedScMessage supportedScMsg;
	ServiceConnection sc;
	ServiceConnection prevSc;

	supportedScMsg = nmi->scm->supportedScMsgList;
	while(supportedScMsg)
	{
		prevSc = NULL;
		sc = supportedScMsg->scList;
		while(sc)
		{
			//if(!ssManagerCheckAddress(subsystem, sc->address) )
			if(	!nodeManagerVerifyAddress(nmi, sc->address) )
			{
				// Remove sc from list
				if(prevSc)
				{
					prevSc->nextSc = sc->nextSc;
					serviceConnectionDestroy(sc);
					sc = prevSc->nextSc;
				}
				else
				{
					supportedScMsg->scList = sc->nextSc;
					serviceConnectionDestroy(sc);
					sc = supportedScMsg->scList;
				}
				nmi->scm->outgoingScCount--;
			}
			else
			{
				prevSc = sc;	
				sc = sc->nextSc;
			}
		}
		supportedScMsg = supportedScMsg->nextSupportedScMsg;
	}

	prevSc = NULL;
	sc = nmi->scm->incommingSc;
	while(sc)
	{
		//if(!ssManagerCheckAddress(subsystem, sc->address) )
		if( !nodeManagerVerifyAddress(nmi, sc->address) )
		{
			// Remove sc from list
			sc->isActive = JAUS_FALSE;			

			// Clear out Inbound Queue
			while(sc->queue->size)
			{
				jausMessageDestroy(queuePop(sc->queue));
			}
			
			if(prevSc)
			{
				prevSc->nextSc = sc->nextSc;
				sc->nextSc = NULL;
				sc = prevSc->nextSc;
			}
			else
			{
				nmi->scm->incommingSc = sc->nextSc;
				sc->nextSc = NULL;
				sc = nmi->scm->incommingSc;
			}
			nmi->scm->incommingScCount--;
		}
		else
		{
			prevSc = sc;
			sc = sc->nextSc;
		}
	}
}

void scManagerAddSupportedMessage(NodeManagerInterface nmi, unsigned short commandCode)
{
	SupportedScMessage supportedScMsg;

	supportedScMsg = scFindSupportedScMsgInList(nmi->scm->supportedScMsgList, commandCode);
	if(supportedScMsg == NULL)
	{																					
		supportedScMsg = (SupportedScMessage)malloc(sizeof(struct SupportedScMessageStruct));
		if(supportedScMsg == NULL) 
		{
			// TODO: Throw error
			return;
		}

		supportedScMsg->commandCode = commandCode; 
		supportedScMsg->scList = NULL;
		
		supportedScMsg->nextSupportedScMsg = nmi->scm->supportedScMsgList;
		nmi->scm->supportedScMsgList = supportedScMsg;
		nmi->scm->supportedScMsgCount++;
	}
}

void scManagerRemoveSupportedMessage(NodeManagerInterface nmi, unsigned short commandCode)
{
	SupportedScMessage prevSupportedScMsg = NULL;
	SupportedScMessage supportedScMsg = nmi->scm->supportedScMsgList;
	ServiceConnection sc;
	TerminateServiceConnectionMessage terminateSc;	
	CancelEventMessage cancelEvent;
	JausMessage txMessage;
	
	while(supportedScMsg)
	{
		if(supportedScMsg->commandCode == commandCode)
		{
			// Remove Service Connection
			if(prevSupportedScMsg)
			{
				prevSupportedScMsg->nextSupportedScMsg = supportedScMsg->nextSupportedScMsg;
			}
			else
			{
				nmi->scm->supportedScMsgList = supportedScMsg->nextSupportedScMsg;
			}
			
			// Terminate and free all the service connections
			while(supportedScMsg->scList)
			{
				sc = supportedScMsg->scList;
				supportedScMsg->scList = sc->nextSc;
				
				// This test will indicate if it is the new style using event messages or not
				if(sc->serviceConnectionType == SC_EVENT_TYPE)
				{
					cancelEvent = cancelEventMessageCreate();
					cancelEvent->source->id = nmi->cmpt->address->id;
					cancelEvent->destination->id = sc->address->id;
					cancelEvent->messageCode = sc->commandCode;
					cancelEvent->eventId = sc->instanceId;

					txMessage = cancelEventMessageToJausMessage(cancelEvent);
					nodeManagerSend(nmi, txMessage);
					jausMessageDestroy(txMessage);
					
					cancelEventMessageDestroy(cancelEvent);
					jausMessageDestroy(sc->queryMessage);
				}
				else
				{
					terminateSc = terminateServiceConnectionMessageCreate();
					terminateSc->source->id = nmi->cmpt->address->id;
					terminateSc->destination->id = sc->address->id;
					terminateSc->serviceConnectionCommandCode = sc->commandCode;
					terminateSc->instanceId = sc->instanceId;
		
					txMessage = terminateServiceConnectionMessageToJausMessage(terminateSc);
					nodeManagerSend(nmi, txMessage);
					jausMessageDestroy(txMessage);
	
					terminateServiceConnectionMessageDestroy(terminateSc);
				}

				serviceConnectionDestroy(sc);
			}
			free(supportedScMsg);
			nmi->scm->supportedScMsgCount--;
			return;
		}
		prevSupportedScMsg = supportedScMsg;
		supportedScMsg = supportedScMsg->nextSupportedScMsg;
	}
}

JausBoolean scManagerQueryActiveMessage(NodeManagerInterface nmi, unsigned short commandCode)
{
	SupportedScMessage supportedScMsg;
	
	supportedScMsg = scFindSupportedScMsgInList(nmi->scm->supportedScMsgList, commandCode);

	if(supportedScMsg != NULL && supportedScMsg->scList != NULL)
	{
		return JAUS_TRUE;
	}
	else
	{
		return JAUS_FALSE;
	}
}

ServiceConnection scManagerGetSendList(NodeManagerInterface nmi, unsigned short commandCode)
{
	SupportedScMessage supportedScMsg;
	ServiceConnection sc;
	ServiceConnection newSc = NULL;
	ServiceConnection firstSc = NULL;
	double currentTime = getTimeSeconds();
	
	// find the SC object associated with this command code
	supportedScMsg = scFindSupportedScMsgInList(nmi->scm->supportedScMsgList, commandCode);
	if(supportedScMsg)
	{
		sc = supportedScMsg->scList;
	}
	else
	{
		return NULL;
	}
	
	while(sc)
	{
		// Check for update rate
		if(sc->isActive && sc->lastSentTime < (currentTime - 1.0/sc->confirmedUpdateRateHz))
		{
			sc->lastSentTime = currentTime;
			if(newSc == NULL)
			{
				newSc = (ServiceConnection)malloc(sizeof(ServiceConnectionStruct));
				firstSc = newSc;
			}
			else
			{
				newSc->nextSc = (ServiceConnection)malloc(sizeof(ServiceConnectionStruct));
				newSc = newSc->nextSc;
			}
			
			*newSc = *sc;
			newSc->nextSc = NULL;
			sc->sequenceNumber++;
		}

		sc = sc->nextSc;
	}
	
	return firstSc;
}

void scManagerDestroySendList(ServiceConnection sc)
{
	ServiceConnection deadSc;
	
	while(sc)
	{
		deadSc = sc;
		sc = sc->nextSc;
		free(deadSc);
	}
}

SupportedScMessage scFindSupportedScMsgInList(SupportedScMessage supportedScMsg, unsigned short commandCode)
{
	while(supportedScMsg)
	{
		if(supportedScMsg->commandCode == commandCode)
		{
			return supportedScMsg;
		}
		supportedScMsg = supportedScMsg->nextSupportedScMsg;
	}
	
	return NULL;
}

ServiceConnection scFindScInList(ServiceConnection sc, ServiceConnection newSc)
{
	// NOTE: destination, commandCode and presenceVector define the sc equals (==) functionality
	//		 the updateRate is not included 
	
	while(sc)
	{
		if(	sc->address->id == newSc->address->id && sc->instanceId == newSc->instanceId )
		{
			return sc;
		}		
		sc = sc->nextSc;
	}
	
	return NULL;	
}

int scGetAvailableInstanceId(ServiceConnection sc, ServiceConnection newSc)
{
	int i;
	unsigned char instanceAvailable[256];
	
	memset(instanceAvailable, 1, 256);
	
	while(sc)
	{
		if(sc->address->id == newSc->address->id)
		{
			if(sc->presenceVector == newSc->presenceVector)
			{
				return sc->instanceId;
			}
			else
			{
				instanceAvailable[sc->instanceId] = 0;
			}
		}
		sc = sc->nextSc;
	}
	
	for(i = 0; i<256; i++)
	{
		if(instanceAvailable[i])
		{
			return i;
		}
	}

	return -1;
}

JausBoolean scManagerCreateServiceConnection(NodeManagerInterface nmi, ServiceConnection sc)
{
	CreateServiceConnectionMessage createSc;
	JausMessage txMessage;
	JausAddress localAddress;
	
	ServiceConnection prevSc = NULL;
	ServiceConnection testSc = nmi->scm->incommingSc;
	
	if(!sc)
	{
		return JAUS_FALSE;
	}
	
	while(testSc)
	{                      
		if(sc == testSc)
		{               
			if(prevSc)
			{
				prevSc->nextSc = testSc->nextSc;
			}
			else
			{
		        nmi->scm->incommingSc = testSc->nextSc;
			}
			nmi->scm->incommingScCount--;
		}
		
		prevSc = testSc;
		testSc = testSc->nextSc;
	}
	
	sc->confirmedUpdateRateHz = 0;
	sc->lastSentTime = 0;
	sc->sequenceNumber = 65535;
	sc->instanceId = -1;
	sc->isActive = JAUS_FALSE;
	sc->nextSc = NULL;

	createSc = createServiceConnectionMessageCreate();
	createSc->source->id = nmi->cmpt->address->id;
	createSc->serviceConnectionCommandCode = sc->commandCode;
	createSc->requestedPeriodicUpdateRateHertz = sc->requestedUpdateRateHz;
	createSc->presenceVector = sc->presenceVector;
	
	if(sc->address && sc->address->subsystem != 0)
	{
		createSc->destination->id = sc->address->id;
			
		txMessage = createServiceConnectionMessageToJausMessage(createSc);
		nodeManagerSend(nmi, txMessage);
		jausMessageDestroy(txMessage);
		createServiceConnectionMessageDestroy(createSc);

		sc->nextSc = nmi->scm->incommingSc;
		nmi->scm->incommingSc = sc;		
		nmi->scm->incommingScCount++;
		return JAUS_TRUE;
	}
	else
	{		
		localAddress = jausAddressCreate();
		localAddress->subsystem = nmi->cmpt->address->subsystem;
		localAddress->node = 0;
		localAddress->component = sc->address->component;
		localAddress->instance = 0;
		
		// Lookup Address from nodeManager
		// Tests if the target component exists or not
		if(nodeManagerLookupAddress(nmi, localAddress))
		{
			createSc->destination->id = localAddress->id;
			sc->address->id = localAddress->id;
				
			txMessage = createServiceConnectionMessageToJausMessage(createSc);
			nodeManagerSend(nmi, txMessage);
			jausMessageDestroy(txMessage);
			
			jausAddressDestroy(localAddress);
			createServiceConnectionMessageDestroy(createSc);
	
			sc->nextSc = nmi->scm->incommingSc;
			nmi->scm->incommingSc = sc;		
			nmi->scm->incommingScCount++;
			return JAUS_TRUE;
		}
		else
		{
			jausAddressDestroy(localAddress);
			createServiceConnectionMessageDestroy(createSc);
			return JAUS_FALSE;
		}
	}
}

JausBoolean scManagerTerminateServiceConnection(NodeManagerInterface nmi, ServiceConnection deadSc)
{
	TerminateServiceConnectionMessage terminateSc;
	JausMessage txMessage;
	ServiceConnection prevSc = NULL;
	ServiceConnection sc = nmi->scm->incommingSc;

	while(sc)
	{
		if(sc->commandCode == deadSc->commandCode && sc->address->id == deadSc->address->id )
		{
			if(sc->instanceId > -1)
			{
				terminateSc = terminateServiceConnectionMessageCreate();
				terminateSc->source->id = nmi->cmpt->address->id;
				terminateSc->destination->id = deadSc->address->id;
				terminateSc->serviceConnectionCommandCode = deadSc->commandCode;
				terminateSc->instanceId = deadSc->instanceId;
	
				txMessage = terminateServiceConnectionMessageToJausMessage(terminateSc);
				nodeManagerSend(nmi, txMessage);
				jausMessageDestroy(txMessage);

				terminateServiceConnectionMessageDestroy(terminateSc);
			}			

			// Set SC to inactive
			sc->isActive = JAUS_FALSE;
			
			// Empty any Remaining Queue
			while(sc->queue->size)
			{
				jausMessageDestroy(queuePop(sc->queue));
			}			

			// Remove Service Connection
			if(prevSc)
			{
				prevSc->nextSc = sc->nextSc;
				sc->nextSc = NULL;
			}
			else
			{
				nmi->scm->incommingSc = sc->nextSc;
				sc->nextSc = NULL;
			}
			
			nmi->scm->incommingScCount--;
			return JAUS_TRUE;
		}
		else
		{
			prevSc = sc;
			sc = sc->nextSc;
		}
	}
	return JAUS_FALSE;
}

JausBoolean scManagerReceiveServiceConnection(NodeManagerInterface nmi, ServiceConnection requestSc, JausMessage *message)
{
	ServiceConnection prevSc;
	ServiceConnection sc = nmi->scm->incommingSc;

	prevSc = NULL;
	while(sc)
	{
		if(sc->commandCode == requestSc->commandCode && sc->address->id == requestSc->address->id )
		{
			if(getTimeSeconds() > (sc->lastSentTime + sc->timeoutSec))
			{
				// Connection has Timed Out
				sc->isActive = JAUS_FALSE;
				while(sc->queue->size)
				{
					jausMessageDestroy(queuePop(sc->queue));
				}
				
				// Remove Service Connection
				if(prevSc)
				{
					prevSc->nextSc = sc->nextSc;
					sc->nextSc = NULL;
				}
				else
				{
					nmi->scm->incommingSc = sc->nextSc;
					sc->nextSc = NULL;
				}
				nmi->scm->incommingScCount--;
				return JAUS_FALSE;
			}

			if(sc->queue->size)
			{
				*message = (JausMessage)queuePop(sc->queue);
				return JAUS_TRUE;
			}
			else
			{
				return JAUS_FALSE;
			}			
		}
		else
		{
			prevSc = sc;
			sc = sc->nextSc;
		}
	}

	cError(	"libnodeManager: scManagerServiceConnectionReceive: Requested SC does not exist\n" );
	return JAUS_FALSE;
}

void scManagerReceiveMessage(NodeManagerInterface nmi, JausMessage message)
{
	ServiceConnection sc = nmi->scm->incommingSc;
	char string[32] = {0};
	
	while(sc)
	{
		if(sc->commandCode == message->commandCode && sc->address->id == message->source->id )
		{
			if(sc->isActive)
			{
				sc->lastSentTime = getTimeSeconds();
				
				if(sc->queueSize && sc->queueSize == sc->queue->size)
				{
					jausMessageDestroy(queuePop(sc->queue));
					queuePush(sc->queue, (void *)message);
				}
				else
				{
					queuePush(sc->queue, (void *)message);
				} 
				// cDebug(3, "Queue Size: %d\n", sc->queue->size);
			}			
			else
			{
				// TODO: Error? received a message for inactive SC
				jausMessageDestroy(message);
			}
			return;		
		}
		sc = sc->nextSc;
	}

	jausAddressToString(message->source, string);
	cError("libnodeManager: scManangerReceiveMessage: No SC for: %s, from: %s\n", jausMessageCommandCodeString(message), string);
	jausMessageDestroy(message);
}

int scManagerUpdateServiceConnection(ServiceConnection sc, unsigned short sequenceNumber)
{
	int returnValue = JAUS_FALSE;

	sc->lastSentTime = getTimeSeconds();

	if(sequenceNumber == sc->sequenceNumber)
	{
		returnValue =  SC_ERROR_SEQUENCE_NUMBERS_EQUAL;
	}
	else if(sequenceNumber == 0 && sc->sequenceNumber != 65535)
	{
		returnValue = SC_ERROR_SEQUENCE_NUMBER_OUT_OF_SYNC;
	}
	else if(sequenceNumber - sc->sequenceNumber != 1 && sequenceNumber !=0)
	{
		returnValue = SC_ERROR_SEQUENCE_NUMBER_OUT_OF_SYNC;
	}
	else
	{
		returnValue = JAUS_TRUE;
	}
	
	sc->sequenceNumber = sequenceNumber;
	
	return returnValue;
}

// ***********************************************************
// 		Experimental Use of Event Messages for OPC 2.75
//		Danny Kent (jaus AT dannykent DOT com)
//		11/07/05
// ***********************************************************
void scManagerProccessCreateEvent(NodeManagerInterface nmi, CreateEventMessage message)
{
	SupportedScMessage supportedScMsg;
	ServiceConnection sc;
	ServiceConnection newSc;
	JausMessage txMessage;
	ConfirmEventMessage confirmEvent;
	
	// Look to see if the requested commandcode exists
	supportedScMsg = scFindSupportedScMsgInList(nmi->scm->supportedScMsgList, message->messageCode);
	if(supportedScMsg == NULL)
	{
		// Command Code Not Supported
		confirmEvent = confirmEventMessageCreate();
		if(confirmEvent)
		{
			confirmEvent->source->id = nmi->cmpt->address->id;
			confirmEvent->destination->id = message->source->id;
			
			confirmEvent->messageCode = message->messageCode;
			confirmEvent->eventId = 0;
			confirmEvent->responseCode = MESSAGE_UNSUPPORTED_RESPONSE;
			
			txMessage = confirmEventMessageToJausMessage(confirmEvent);
			confirmEventMessageDestroy(confirmEvent);
			
			nodeManagerSend(nmi, txMessage);
			jausMessageDestroy(txMessage);
		}
		else
		{
			cError("scManagerProccessCreateEvent: Cannot create confirmEvent\n");
		}
		return;
	}
	
	// Attempt to create a new ServiceConnection
	newSc = (ServiceConnection)malloc( sizeof(ServiceConnectionStruct) );
	if(newSc == NULL) 
	{
		// Send negative conf (could not create sc)
		confirmEvent = confirmEventMessageCreate();
		if(confirmEvent)
		{
			confirmEvent->source->id = nmi->cmpt->address->id;
			confirmEvent->destination->id = message->source->id;
			
			confirmEvent->messageCode = message->messageCode;
			confirmEvent->eventId = 0;
			confirmEvent->responseCode = CONNECTION_REFUSED_RESPONSE;
			
			txMessage = confirmEventMessageToJausMessage(confirmEvent);
			confirmEventMessageDestroy(confirmEvent);
			
			nodeManagerSend(nmi, txMessage);
			jausMessageDestroy(txMessage);
		}
		else
		{
			cError("scManagerProccessCreateEvent: Cannot create confirmEvent\n");
		}
		return;
	}
	
	// Create a copy of the QueryMessage
	newSc->queryMessage = jausMessageDuplicate(message->queryMessage);
	if(!newSc->queryMessage)
	{
		// error creating message
		free(newSc);
		return;		
	}
	newSc->serviceConnectionType = SC_EVENT_TYPE;
	newSc->commandCode = message->messageCode;
	newSc->presenceVector = 0;	
	newSc->address = jausAddressCreate();
	newSc->address->id = message->source->id;

	// Get Instance / Event Id value
	newSc->instanceId = scGetAvailableInstanceId(supportedScMsg->scList, newSc);
	if(newSc->instanceId == -1)
	{
		// Send negative conf (could not create sc)
		confirmEvent = confirmEventMessageCreate();
		if(confirmEvent)
		{
			confirmEvent->source->id = nmi->cmpt->address->id;
			confirmEvent->destination->id = message->source->id;
			
			confirmEvent->messageCode = message->messageCode;
			confirmEvent->eventId = 0;
			confirmEvent->responseCode = CONNECTION_REFUSED_RESPONSE;
			
			txMessage = confirmEventMessageToJausMessage(confirmEvent);
			confirmEventMessageDestroy(confirmEvent);
			
			nodeManagerSend(nmi, txMessage);
			jausMessageDestroy(txMessage);
		}
		else
		{
			cError("scManagerProccessCreateEvent: Cannot create confirmEvent\n");
		}
		jausMessageDestroy(newSc->queryMessage);
		jausAddressDestroy(newSc->address);
		free(newSc);
		return;
	}
	newSc->queue = NULL;
	newSc->queueSize = 0;

	sc = scFindScInList(supportedScMsg->scList, newSc);
	if(sc == NULL) // Test to see if the sc does not already exist	
	{
		// The sc doesent exist, so we insert the new one into the list
		sc = newSc;
		sc->nextSc = supportedScMsg->scList;
		supportedScMsg->scList = sc;
		nmi->scm->outgoingScCount++;
	}
	else
	{
		jausMessageDestroy(newSc->queryMessage);	
		jausAddressDestroy(newSc->address);
		free(newSc);
	}

	// Setup the SC control parameters
	sc->requestedUpdateRateHz = message->requestedUpdateRate;
	sc->confirmedUpdateRateHz = message->requestedUpdateRate;
	sc->lastSentTime = 0.0;
	sc->sequenceNumber = 0;
	sc->isActive = JAUS_TRUE;

	// Send confirmation
	confirmEvent = confirmEventMessageCreate();
	if(confirmEvent)
	{
		confirmEvent->source->id = nmi->cmpt->address->id;
		confirmEvent->destination->id = message->source->id;
		
		confirmEvent->messageCode = message->messageCode;
		confirmEvent->eventId = sc->instanceId;
		confirmEvent->responseCode = SUCCESSFUL_RESPONSE;
		
		txMessage = confirmEventMessageToJausMessage(confirmEvent);
		confirmEventMessageDestroy(confirmEvent);
		
		nodeManagerSend(nmi, txMessage);
		jausMessageDestroy(txMessage);
	}
	else
	{
		cError("scManagerProccessCreateEvent: Cannot create confirmEvent\n");
	}
}

void scManagerProcessConfirmEvent(NodeManagerInterface nmi, ConfirmEventMessage message)
{
	ServiceConnection prevSc = NULL;
	ServiceConnection sc = nmi->scm->incommingSc;
	CancelEventMessage cancelEvent;	
	JausMessage txMessage;

	// Loop through all incomming SC's
	while(sc)
	{
		// Test if this incoming SC matches the one replied to
		if(	sc->commandCode == message->messageCode && sc->address->id == message->source->id )
		{
			// Success
			if( message->responseCode == SUCCESSFUL_RESPONSE )
			{
				sc->confirmedUpdateRateHz = message->confirmedUpdateRate;
				sc->instanceId = message->eventId;
				sc->isActive = JAUS_TRUE;
				sc->sequenceNumber = 65535;
				sc->lastSentTime = getTimeSeconds();
			}
			else // Failure
			{
				// Set SC Inactive
				sc->isActive = JAUS_FALSE;

				// Remove Service Connection
				if(prevSc)
				{
					prevSc->nextSc = sc->nextSc;
					sc->nextSc = NULL;
				}
				else
				{
					nmi->scm->incommingSc = sc->nextSc;
					sc->nextSc = NULL;
				}
				nmi->scm->incommingScCount--;
			}
			return;
		}
		prevSc = sc;
		sc = sc->nextSc;
	}

	// The SC was not found, so send a terminate to prevent streaming
	if( message->responseCode == SUCCESSFUL_RESPONSE )
	{
		cancelEvent = cancelEventMessageCreate();
		cancelEvent->source->id = nmi->cmpt->address->id;
		cancelEvent->destination->id = message->source->id;
		cancelEvent->messageCode = message->messageCode;
		cancelEvent->eventId = message->eventId;
		
		txMessage = cancelEventMessageToJausMessage(cancelEvent);
		nodeManagerSend(nmi, txMessage);
		jausMessageDestroy(txMessage);
	
		cancelEventMessageDestroy(cancelEvent);
	}	
}

void scManagerProcessCancelEvent(NodeManagerInterface nmi, CancelEventMessage message)
{
	SupportedScMessage supportedScMsg;
	ServiceConnection sc;
	ServiceConnection prevSc;
	
	// Find the outbound SC that matches the cancel event
	supportedScMsg = scFindSupportedScMsgInList(nmi->scm->supportedScMsgList, message->messageCode);
	if(supportedScMsg == NULL)
	{
		// Cancel Event message for SC type not found
		return;
	}

	if( supportedScMsg->scList == NULL )
	{
		// Cancel Event message for SC not found
		return;
	}
	sc = supportedScMsg->scList;
	
	if(	sc->address->id == message->source->id &&
		sc->commandCode == message->messageCode &&
		sc->instanceId == message->eventId )
	{
		// Remove sc from list
		supportedScMsg->scList = sc->nextSc;
		serviceConnectionDestroy(sc);
		nmi->scm->outgoingScCount--;
		return;
	}
	
	prevSc = sc;
	sc = prevSc->nextSc;
	while(sc)
	{
		if(	sc->address->id == message->source->id &&
			sc->commandCode == message->messageCode &&
			sc->instanceId == message->eventId )
		{
			// Remove sc from list
			prevSc->nextSc = sc->nextSc;			
			serviceConnectionDestroy(sc);
			nmi->scm->outgoingScCount--;
			return;
		}	
		prevSc = sc;	
		sc = sc->nextSc;
	}	
}

JausBoolean scManagerCreatePeriodicEvent(NodeManagerInterface nmi, ServiceConnection sc)
{
	CreateEventMessage createEvent;
	JausMessage txMessage;
	JausAddress localAddress;
	
	ServiceConnection prevSc = NULL;
	ServiceConnection testSc = nmi->scm->incommingSc;
	
	// Test to see if the SC requested is already on the incomming list
	// The sc sent to this function exists in the developer space, therefore
	// do not destroy it. This happens if a component attempts to create the same
	// service connection twice without removing it from the list first.
	while(testSc)
	{                      
		if(sc == testSc)
		{               
			if(prevSc)
			{
				prevSc->nextSc = testSc->nextSc;
			}
			else
			{
		        nmi->scm->incommingSc = testSc->nextSc;
			}
			nmi->scm->incommingScCount--;
		}
		prevSc = testSc;
		testSc = testSc->nextSc;
	}

	// Setup SC Control Parameters
	sc->confirmedUpdateRateHz = 0;
	sc->lastSentTime = 0;
	sc->sequenceNumber = 65535;
	sc->instanceId = -1;
	sc->isActive = JAUS_FALSE;
	sc->nextSc = NULL;

	// Setup the Create Event Message
	createEvent = createEventMessageCreate();
	createEvent->source->id = nmi->cmpt->address->id;
	jausBytePresenceVectorSetBit(&createEvent->presenceVector, CREATE_EVENT_PV_REQUESTED_RATE_BIT); // Set for Periodic Event, Specify the Requested Rate
	jausBytePresenceVectorSetBit(&createEvent->presenceVector, CREATE_EVENT_PV_MINIMUM_RATE_BIT); // Set for Periodic Event, Specify the Requested Rate
	createEvent->messageCode = sc->commandCode;
	createEvent->eventType = EVENT_PERIODIC_TYPE;
	createEvent->requestedMinimumRate = sc->requestedUpdateRateHz;
	createEvent->requestedUpdateRate = sc->requestedUpdateRateHz;
	jausMessageDestroy(createEvent->queryMessage);
	createEvent->queryMessage = jausMessageDuplicate(sc->queryMessage);

	localAddress = jausAddressCreate();
	localAddress->subsystem = nmi->cmpt->address->subsystem;
	localAddress->node = 0;
	localAddress->component = sc->address->component;
	localAddress->instance = 0;
	
	// Retrieve AddressList from nodeManager
	// Tests if the target component exists or not
	if(localAddress)
	{
		createEvent->destination->id = localAddress->id;
		sc->address->id = localAddress->id;
	
		txMessage = createEventMessageToJausMessage(createEvent);
		nodeManagerSend(nmi, txMessage);
		jausMessageDestroy(txMessage);
		
		jausAddressDestroy(localAddress);
		createEventMessageDestroy(createEvent);

		sc->nextSc = nmi->scm->incommingSc;
		nmi->scm->incommingSc = sc;		
		nmi->scm->incommingScCount++;
		return JAUS_TRUE;
	}
	else
	{
		jausAddressDestroy(localAddress);
		createEventMessageDestroy(createEvent);
		return JAUS_FALSE;
	}	
}

JausBoolean scManagerCancelPeriodicEvent(NodeManagerInterface nmi, ServiceConnection deadSc)
{
	CancelEventMessage cancelEvent;
	JausMessage txMessage;
	ServiceConnection prevSc = NULL;
	ServiceConnection sc = nmi->scm->incommingSc;
		
	while(sc)
	{
		if(sc->commandCode == deadSc->commandCode && sc->address->id == deadSc->address->id )
		{
			if(sc->instanceId > -1)
			{
				cancelEvent = cancelEventMessageCreate();
				cancelEvent->source->id = nmi->cmpt->address->id;
				cancelEvent->destination->id = deadSc->address->id;
				cancelEvent->messageCode = deadSc->commandCode;
				cancelEvent->eventId = deadSc->instanceId;
	
				txMessage = cancelEventMessageToJausMessage(cancelEvent);
				nodeManagerSend(nmi, txMessage);
				jausMessageDestroy(txMessage);

				cancelEventMessageDestroy(cancelEvent);
			}

			// Set SC to inactive
			sc->isActive = JAUS_FALSE;
			
			// Empty any Remaining Queue
			while(sc->queue->size)
			{
				jausMessageDestroy(queuePop(sc->queue));
			}			

			// Remove Service Connection
			if(prevSc)
			{
				prevSc->nextSc = sc->nextSc;
				sc->nextSc = NULL;
			}
			else
			{
				nmi->scm->incommingSc = sc->nextSc;
				sc->nextSc = NULL;
			}
			
			nmi->scm->incommingScCount--;
			return JAUS_TRUE;
		}
		else
		{
			prevSc = sc;
			sc = sc->nextSc;
		}
	}
	return JAUS_FALSE;	
}
