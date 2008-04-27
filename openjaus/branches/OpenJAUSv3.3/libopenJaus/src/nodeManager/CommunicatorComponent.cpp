/*****************************************************************************
 *  Copyright (c) 2008, OpenJAUS.com
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
// File Name: CommunicatorComponent.cpp
//
// Written By: Danny Kent (jaus AT dannykent DOT com) 
//
// Version: 3.3 BETA
//
// Date: 04/15/08
//
// Description: This file defines a CommunicatorComponent class.
// 				This is derived from a the LocalComponent class.

#include "nodeManager/CommunicatorComponent.h"
#include "nodeManager/JausComponentCommunicationManager.h"
#include "nodeManager/events/ErrorEvent.h"
#include "nodeManager/EventHandler.h"
#include "utils/timeLib.h"
#include "jaus.h"

CommunicatorComponent::CommunicatorComponent(FileLoader *configData, EventHandler *handler, JausComponentCommunicationManager *cmptComms)
{
	int subsystemId, nodeId;

	if(configData == NULL)
	{
		// OK, don't do this. This is bad.
		// TODO: Throw an exception? Log an error.
		return;
	}

	this->eventHandler = handler;

	if(cmptComms == NULL)
	{
		// OK, don't do this. This is bad.
		// TODO: Throw an exception? Log an error.
		return;
	}

	this->type = COMPONENT_INTERFACE;
	this->commMngr = cmptComms;
	this->configData = configData;
	this->name = "OpenJAUS Communicator";
	this->cmptRateHz = COMMUNICATOR_RATE_HZ;
	this->systemTree = cmptComms->getSystemTree();
	this->nodeManagerSubsystemEventConfirmed = false;
	for(int i = 0; i < MAXIMUM_EVENT_ID; i++)
	{
		eventId[i] = false;
	}

	// NOTE: These two values should exist in the properties file and should be checked 
	// in the NodeManager class prior to constructing this object
	subsystemId = configData->GetConfigDataInt("JAUS", "SubsystemId");
	if(subsystemId < JAUS_MINIMUM_SUBSYSTEM_ID || subsystemId > JAUS_MAXIMUM_SUBSYSTEM_ID)
	{
		// Invalid ID
		// TODO: Throw an exception? Log an error.
		return;
	}

	nodeId = configData->GetConfigDataInt("JAUS", "NodeId");
	if(nodeId < JAUS_MINIMUM_NODE_ID || nodeId > JAUS_MAXIMUM_NODE_ID)
	{
		// Invalid ID
		// TODO: Throw an exception? Log an error.
		return;
	}

	this->cmpt = jausComponentCreate();
	if(!this->cmpt)
	{
		// TODO: Throw exception? Log error.
		return;
	}

	this->cmpt->address->subsystem = subsystemId;
	this->cmpt->address->node = nodeId;
	this->cmpt->address->component = JAUS_COMMUNICATOR;
	this->cmpt->address->instance = JAUS_MINIMUM_INSTANCE_ID;
	this->cmpt->node = systemTree->getNode(subsystemId, nodeId);
	this->cmpt->identification = (char *)this->name.c_str();

	this->startupState();

	this->setupThread();
	if(!systemTree->addComponent(this->cmpt))
	{
		// TODO: Log Error, we can't add a node manager with instance 1
	}
}

CommunicatorComponent::~CommunicatorComponent(void){}

bool CommunicatorComponent::processMessage(JausMessage message)
{
	// Check for loopback of message from myself
	if(jausAddressEqual(message->source, cmpt->address))
	{
		// We sent a broadcast (*.*.255.255) message probably
		// Just eat it.
		jausMessageDestroy(message);
		return true;
	}

	//char buf[80] = {0};
	//jausAddressToString(message->source, buf);
	//printf("Com: Process %s from %s", jausMessageCommandCodeString(message), buf);
	//jausAddressToString(message->destination, buf);
	//printf(" to %s\n", buf);

	// TODO: Let's add our hack here for making every message look like a heartbeat!
	switch(message->commandCode)
	{
		case JAUS_SET_COMPONENT_AUTHORITY:
		case JAUS_SHUTDOWN:
		case JAUS_STANDBY:
		case JAUS_RESUME:
		case JAUS_RESET:
		case JAUS_SET_EMERGENCY:
		case JAUS_CLEAR_EMERGENCY:
			// These messages are ignored!
			jausMessageDestroy(message);
			return true;
		
		case JAUS_CREATE_SERVICE_CONNECTION:
			return processCreateServiceConnection(message);

		case JAUS_ACTIVATE_SERVICE_CONNECTION:
			return processActivateServiceConnection(message);

		case JAUS_SUSPEND_SERVICE_CONNECTION:
			return processSuspendServiceConnection(message);

		case JAUS_TERMINATE_SERVICE_CONNECTION:
			return processTerminateServiceConnection(message);

		case JAUS_REQUEST_COMPONENT_CONTROL:
			return processRequestComponentControl(message);

		case JAUS_QUERY_COMPONENT_AUTHORITY:
			return processQueryComponentAuthority(message);

		case JAUS_QUERY_COMPONENT_STATUS:
			return processQueryComponentStatus(message);

		case JAUS_QUERY_HEARTBEAT_PULSE:
			return processQueryHeartbeatPulse(message);

		case JAUS_REPORT_HEARTBEAT_PULSE:
			return processReportHeartbeatPulse(message);

		case JAUS_QUERY_CONFIGURATION:
			return processQueryConfiguration(message);

		case JAUS_QUERY_IDENTIFICATION:
			return processQueryIdentification(message);

		case JAUS_QUERY_SERVICES:
			return processQueryServices(message);

		case JAUS_REPORT_CONFIGURATION:
			return processReportConfiguration(message);

		case JAUS_REPORT_IDENTIFICATION:
			return processReportIdentification(message);

		case JAUS_REPORT_SERVICES:
			return processReportServices(message);

		case JAUS_CANCEL_EVENT:
			return processCancelEvent(message);

		case JAUS_CONFIRM_EVENT_REQUEST:
			return processConfirmEvent(message);

		case JAUS_CREATE_EVENT:
			return processCreateEvent(message);

		case JAUS_EVENT:
			return processEvent(message);

		default:
			// Unhandled message received by node manager component
			jausMessageDestroy(message);
			return false;
	}
}

std::string CommunicatorComponent::toString()
{
	return "Communicator Component";
}

void CommunicatorComponent::startupState()
{
	JausService service;
	service = jausServiceCreate(0);
	if(!service) return;
	jausServiceAddInputCommand(service, JAUS_SET_COMPONENT_AUTHORITY, NO_PRESENCE_VECTOR);
	jausServiceAddInputCommand(service, JAUS_SHUTDOWN, NO_PRESENCE_VECTOR);
	jausServiceAddInputCommand(service, JAUS_STANDBY, NO_PRESENCE_VECTOR);
	jausServiceAddInputCommand(service, JAUS_RESUME, NO_PRESENCE_VECTOR);
	jausServiceAddInputCommand(service, JAUS_RESET, NO_PRESENCE_VECTOR);
	jausServiceAddInputCommand(service, JAUS_SET_EMERGENCY, NO_PRESENCE_VECTOR);
	jausServiceAddInputCommand(service, JAUS_CLEAR_EMERGENCY, NO_PRESENCE_VECTOR);
	jausServiceAddInputCommand(service, JAUS_CREATE_SERVICE_CONNECTION, NO_PRESENCE_VECTOR);
	jausServiceAddInputCommand(service, JAUS_ACTIVATE_SERVICE_CONNECTION, NO_PRESENCE_VECTOR);
	jausServiceAddInputCommand(service, JAUS_SUSPEND_SERVICE_CONNECTION, NO_PRESENCE_VECTOR);
	jausServiceAddInputCommand(service, JAUS_TERMINATE_SERVICE_CONNECTION, NO_PRESENCE_VECTOR);
	jausServiceAddInputCommand(service, JAUS_REQUEST_COMPONENT_CONTROL, NO_PRESENCE_VECTOR);
	jausServiceAddInputCommand(service, JAUS_QUERY_COMPONENT_AUTHORITY, NO_PRESENCE_VECTOR);
	jausServiceAddInputCommand(service, JAUS_QUERY_COMPONENT_STATUS, NO_PRESENCE_VECTOR);
	jausServiceAddInputCommand(service, JAUS_QUERY_HEARTBEAT_PULSE, NO_PRESENCE_VECTOR);

	jausServiceAddOutputCommand(service, JAUS_CREATE_SERVICE_CONNECTION, NO_PRESENCE_VECTOR);
	jausServiceAddOutputCommand(service, JAUS_CONFIRM_SERVICE_CONNECTION, NO_PRESENCE_VECTOR);
	jausServiceAddOutputCommand(service, JAUS_TERMINATE_SERVICE_CONNECTION, NO_PRESENCE_VECTOR);
	jausServiceAddOutputCommand(service, JAUS_CONFIRM_COMPONENT_CONTROL, NO_PRESENCE_VECTOR);
	jausServiceAddOutputCommand(service, JAUS_REJECT_COMPONENT_CONTROL, NO_PRESENCE_VECTOR);
	jausServiceAddOutputCommand(service, JAUS_REPORT_COMPONENT_AUTHORITY, NO_PRESENCE_VECTOR);
	jausServiceAddOutputCommand(service, JAUS_REPORT_COMPONENT_STATUS, NO_PRESENCE_VECTOR);
	jausServiceAddOutputCommand(service, JAUS_REPORT_HEARTBEAT_PULSE, NO_PRESENCE_VECTOR);
	jausServiceAddOutputCommand(service, JAUS_QUERY_COMPONENT_STATUS, NO_PRESENCE_VECTOR);

	// Add Core Service
	jausServiceAddService(cmpt->services, service);

	service = jausServiceCreate(JAUS_COMMUNICATOR);
	if(!service) return;
	jausServiceAddInputCommand(service, JAUS_QUERY_CONFIGURATION, NO_PRESENCE_VECTOR);
	jausServiceAddInputCommand(service, JAUS_QUERY_IDENTIFICATION, NO_PRESENCE_VECTOR);
	jausServiceAddInputCommand(service, JAUS_QUERY_SERVICES, NO_PRESENCE_VECTOR);
	jausServiceAddInputCommand(service, JAUS_REPORT_CONFIGURATION, NO_PRESENCE_VECTOR);
	jausServiceAddInputCommand(service, JAUS_REPORT_IDENTIFICATION, NO_PRESENCE_VECTOR);
	jausServiceAddInputCommand(service, JAUS_REPORT_SERVICES, NO_PRESENCE_VECTOR);
	jausServiceAddInputCommand(service, JAUS_CANCEL_EVENT, NO_PRESENCE_VECTOR);
	jausServiceAddInputCommand(service, JAUS_CONFIRM_EVENT_REQUEST, NO_PRESENCE_VECTOR);
	jausServiceAddInputCommand(service, JAUS_CREATE_EVENT, NO_PRESENCE_VECTOR);

	jausServiceAddOutputCommand(service, JAUS_QUERY_CONFIGURATION, NO_PRESENCE_VECTOR);
	jausServiceAddOutputCommand(service, JAUS_QUERY_IDENTIFICATION, NO_PRESENCE_VECTOR);
	jausServiceAddOutputCommand(service, JAUS_QUERY_SERVICES, NO_PRESENCE_VECTOR);
	jausServiceAddOutputCommand(service, JAUS_REPORT_CONFIGURATION, NO_PRESENCE_VECTOR);
	jausServiceAddOutputCommand(service, JAUS_REPORT_IDENTIFICATION, NO_PRESENCE_VECTOR);
	jausServiceAddOutputCommand(service, JAUS_REPORT_SERVICES, NO_PRESENCE_VECTOR);
	jausServiceAddOutputCommand(service, JAUS_CANCEL_EVENT, NO_PRESENCE_VECTOR);
	jausServiceAddOutputCommand(service, JAUS_CONFIRM_EVENT_REQUEST, NO_PRESENCE_VECTOR);
	jausServiceAddOutputCommand(service, JAUS_CREATE_EVENT, NO_PRESENCE_VECTOR);

	// Add Node Manager Service
	jausServiceAddService(cmpt->services, service);
}

void CommunicatorComponent::intializeState()
{	
	// Switch to Ready State
	this->cmpt->state = JAUS_READY_STATE;
}

void CommunicatorComponent::standbyState()
{

}

void CommunicatorComponent::readyState()
{
	CreateEventMessage createEventMsg = NULL;
	QueryConfigurationMessage query = NULL;
	JausMessage txMessage = NULL;
	static double nextSendTime = 0;

	if(!nodeManagerSubsystemEventConfirmed && getTimeSeconds() > nextSendTime)
	{
		// Create query message
		query = queryConfigurationMessageCreate();
		if(!query)
		{
			// Constructor Failed
			return;
		}
		query->queryField = JAUS_SUBSYSTEM_CONFIGURATION;

		createEventMsg = createEventMessageCreate();
		if(!createEventMsg)
		{
			queryConfigurationMessageDestroy(query);
			return;
		}
		
		// Setup Create Event PV
		createEventMsg->presenceVector = 0;
		jausByteSetBit(&createEventMsg->presenceVector, CREATE_EVENT_PV_QUERY_MESSAGE_BIT);

		createEventMsg->reportMessageCode = jausMessageGetComplimentaryCommandCode(query->commandCode);
		createEventMsg->eventType = EVENT_EVERY_CHANGE_TYPE;
		createEventMsg->queryMessage = queryConfigurationMessageToJausMessage(query);
		if(!createEventMsg->queryMessage)
		{
			// Problem with queryConfigurationMessageToJausMessage
			createEventMessageDestroy(createEventMsg);
			queryConfigurationMessageDestroy(query);
			return;
		}
		
		txMessage = createEventMessageToJausMessage(createEventMsg);
		if(!txMessage)
		{
			// Problem with createEventMsgMessageToJausMessage
			createEventMessageDestroy(createEventMsg);
			queryConfigurationMessageDestroy(query);
			return;
		}

		txMessage->destination->subsystem = this->cmpt->address->subsystem;
		txMessage->destination->node = this->cmpt->address->node;
		txMessage->destination->component = JAUS_NODE_MANAGER_COMPONENT;
		txMessage->destination->instance = 1;

		jausAddressCopy(txMessage->source, cmpt->address);
		this->commMngr->receiveJausMessage(txMessage, this);

		nextSendTime = getTimeSeconds() + 1.0;
	}
}

void CommunicatorComponent::emergencyState()
{

}

void CommunicatorComponent::failureState()
{

}

void CommunicatorComponent::shutdownState()
{

}

void CommunicatorComponent::allState()
{
	generateHeartbeats();
	// TODO: Create SystemTree refresh trigger at some rate
	// TODO: Check for serviceConnections
}

bool CommunicatorComponent::processReportIdentification(JausMessage message)
{
	// This function follows the flowchart designed for the Communicator by D. Kent
	ReportIdentificationMessage reportId = NULL;
	
	reportId = reportIdentificationMessageFromJausMessage(message);
	if(!reportId)
	{
		// Error unpacking the reportId msg
		// TODO: Log Error. Throw Exception?
		jausMessageDestroy(message);
		return false;
	}

	switch(reportId->queryType)
	{
		case JAUS_QUERY_FIELD_SYSTEM_IDENTITY:
			// We don't care about this (actually we never ask for this, so this shouldn't happen)
			reportIdentificationMessageDestroy(reportId);
			jausMessageDestroy(message);
			return true;

		case JAUS_QUERY_FIELD_SS_IDENTITY:
			// Has Subs?
			if(!systemTree->hasSubsystem(reportId->source))
			{
				// Report ID from unknown Subsystem
				// TODO: Log Error. Throw Exception
				reportIdentificationMessageDestroy(reportId);
				jausMessageDestroy(message);
				return false;
			}

			// Add Identification
			systemTree->setSubsystemIdentification(reportId->source, reportId->identification);
			
			// Query Subs Conf & Setup event
			sendQuerySubsystemConfiguration(reportId->source, true);
			reportIdentificationMessageDestroy(reportId);
			jausMessageDestroy(message);
			return true;
			
		case JAUS_QUERY_FIELD_NODE_IDENTITY:
			// Has Node?
			if(!systemTree->hasNode(reportId->source))
			{
				// Report ID from unknown Node
				// TODO: Log Error. Throw Exception
				reportIdentificationMessageDestroy(reportId);
				jausMessageDestroy(message);
				return false;
			}

			// Add Identification
			systemTree->setNodeIdentification(reportId->source, reportId->identification);
			
			// Query Subs Conf & Setup event
			sendQueryNodeConfiguration(reportId->source, true);
			reportIdentificationMessageDestroy(reportId);
			jausMessageDestroy(message);
			return true;

		case JAUS_QUERY_FIELD_COMPONENT_IDENTITY:
			// Has Cmpt?
			if(!systemTree->hasComponent(reportId->source))
			{
				// Report ID from unknown Component
				// TODO: Log Error. Throw Exception
				reportIdentificationMessageDestroy(reportId);
				jausMessageDestroy(message);
				return false;
			}

			// Add Identification
			systemTree->setComponentIdentification(reportId->source, reportId->identification);
			reportIdentificationMessageDestroy(reportId);
			jausMessageDestroy(message);
			return true;

		default:
			// TODO: Log Error. Throw Exception.
			reportIdentificationMessageDestroy(reportId);
			jausMessageDestroy(message);
			return true;
	}

	reportIdentificationMessageDestroy(reportId);
	jausMessageDestroy(message);
	return true;
}

bool CommunicatorComponent::processReportConfiguration(JausMessage message)
{
	// This function follows the flowchart designed for NM 2.0 by D. Kent and T. Galluzzo
	ReportConfigurationMessage reportConf = NULL;

	// Check for a reportConf from our own NM
	if(reportConf->source->subsystem == this->cmpt->address->subsystem &&
		reportConf->source->component == JAUS_NODE_MANAGER_COMPONENT)
	{
		sendSubsystemChangedEvents();
		jausMessageDestroy(message);
		return true;
	}

	reportConf = reportConfigurationMessageFromJausMessage(message);
	if(!reportConf)
	{
		// Error unpacking the reportConf
		// TODO: Log Error
		jausMessageDestroy(message);
		return false;
	}

	// Has Subs?
	if(!systemTree->hasSubsystem(reportConf->source))
	{
		// TODO: Throw Exception. Log Error.
		reportConfigurationMessageDestroy(reportConf);
		jausMessageDestroy(message);
		return false;
	}

	// Replace Subsystem
	systemTree->replaceSubsystem(reportConf->source, reportConf->subsystem);

	JausSubsystem subs = systemTree->getSubsystem(reportConf->source);
	for(int i = 0; i < subs->nodes->elementCount; i++)
	{
		JausNode node = (JausNode) subs->nodes->elementData[i];

		if(!jausNodeHasIdentification(node))
		{
			JausAddress address = jausAddressCreate();
			if(!address)
			{
				// TODO: Throw Exception. Log Error.
				reportConfigurationMessageDestroy(reportConf);
				jausMessageDestroy(message);
				return false;
			}
			address->subsystem = reportConf->source->subsystem;
			address->node = reportConf->source->node;
			address->component = JAUS_NODE_MANAGER;
			address->instance = 1;

			sendQueryNodeIdentification(address);
			jausAddressDestroy(address);
		}

		for(int j = 0; j < node->components->elementCount; j++)
		{
			JausComponent cmpt = (JausComponent) node->components->elementData[j];
			
			if(!jausComponentHasIdentification(cmpt))
			{
				sendQueryComponentIdentification(cmpt->address);
			}

			if(!jausComponentHasServices(cmpt))
			{
				sendQueryComponentServices(cmpt->address);
			}
		} // End For(Components)
	} // End For(Nodes)

	jausSubsystemDestroy(subs);
	reportConfigurationMessageDestroy(reportConf);
	jausMessageDestroy(message);
	return true;
}

bool CommunicatorComponent::processReportServices(JausMessage message)
{
	ReportServicesMessage reportServices = NULL;

	reportServices = reportServicesMessageFromJausMessage(message);
	if(!reportServices)
	{
		// TODO: Log error. Throw Exception.
		jausMessageDestroy(message);
		return false;
	}

	if(systemTree->hasComponent(reportServices->source))
	{
		systemTree->setComponentServices(reportServices->source, reportServices->jausServices);
	}

	reportServicesMessageDestroy(reportServices);
	jausMessageDestroy(message);
	return true;
}

bool CommunicatorComponent::processReportHeartbeatPulse(JausMessage message)
{
	// This function follows the flowchart designed for NM 2.0 by D. Kent and T. Galluzzo
	if(message->source->subsystem == cmpt->address->subsystem)
	{
		// Should not receive my own heartbeats
		// TODO: Throw Exception. Log Error.
		jausMessageDestroy(message);
		return false;
	}

	// Has Subs?
	if(!systemTree->hasSubsystem(message->source))
	{
		// Add Subs
		systemTree->addSubsystem(message->source, NULL);
		
		// Query SubsId
		sendQuerySubsystemIdentification(message->source);
		jausMessageDestroy(message);
		return true;
	}

	// Update Subsystem Timestamp
	systemTree->updateSubsystemTimestamp(message->source);
	
	// Has SubsId?
	if(!systemTree->hasSubsystemIdentification(message->source))
	{
		// Query SubsId
		sendQuerySubsystemIdentification(message->source);
		jausMessageDestroy(message);
		return true;
	}

	// Has SubsConf?
	if(!systemTree->hasSubsystemConfiguration(message->source))
	{
		sendQuerySubsystemConfiguration(message->source, true);
		jausMessageDestroy(message);
		return true;
	}

	JausSubsystem subs = systemTree->getSubsystem(message->source);
	if(!subs)
	{
		// TODO: Throw Exception. Log Error.
		jausMessageDestroy(message);
		return false;
	}

	for(int i = 0; i < subs->nodes->elementCount; i++)
	{
		JausNode node = (JausNode) subs->nodes->elementData[i];

		if(!jausNodeHasIdentification(node))
		{
			JausAddress address = jausAddressCreate();
			if(!address)
			{
				// TODO: Throw Exception. Log Error.
				jausSubsystemDestroy(subs);
				jausMessageDestroy(message);
				return false;
			}
			address->subsystem = message->source->subsystem;
			address->node = node->id;
			address->component = JAUS_NODE_MANAGER;
			address->instance = 1;

			sendQueryNodeIdentification(address);
			jausAddressDestroy(address);
		}

		for(int j = 0; j < node->components->elementCount; j++)
		{
			JausComponent cmpt = (JausComponent) node->components->elementData[j];
			
			if(!jausComponentHasIdentification(cmpt))
			{
				sendQueryComponentIdentification(cmpt->address);
			}

			if(!jausComponentHasServices(cmpt))
			{
				sendQueryComponentServices(cmpt->address);
			}
		} // end For(Components)
	} // end For(Nodes)

	jausMessageDestroy(message);
	return true;
}

bool CommunicatorComponent::processCreateEvent(JausMessage message)
{
	// Only support Configuration Changed events
	CreateEventMessage createEvent = NULL;
	QueryConfigurationMessage queryConf = NULL;
	ConfirmEventRequestMessage confirmEventRequest = NULL;
	JausMessage txMessage = NULL;
	int nextEventId = -1;
	HASH_MAP <int, JausAddress>::iterator iterator;
	
	confirmEventRequest = confirmEventRequestMessageCreate();
	if(!confirmEventRequest)
	{
		//TODO: Log Error. Throw Exception
		return false;
	}
	jausAddressCopy(confirmEventRequest->destination, message->source);
	jausAddressCopy(confirmEventRequest->source, cmpt->address);
	
	createEvent = createEventMessageFromJausMessage(message);
	if(!createEvent)
	{
		//TODO: Log Error. Throw Exception
		confirmEventRequest->responseCode = INVALID_EVENT_RESPONSE;
		txMessage = confirmEventRequestMessageToJausMessage(confirmEventRequest);
		if(txMessage)
		{
			this->commMngr->receiveJausMessage(txMessage, this);
		}
		confirmEventRequestMessageDestroy(confirmEventRequest);
		return false;
	}

	if(createEvent->reportMessageCode != JAUS_REPORT_CONFIGURATION)
	{
		// Currently the NM only supports configuration changed events
		confirmEventRequest->responseCode = MESSAGE_UNSUPPORTED_RESPONSE;
		txMessage = confirmEventRequestMessageToJausMessage(confirmEventRequest);
		if(txMessage)
		{
			this->commMngr->receiveJausMessage(txMessage, this);
		}
		confirmEventRequestMessageDestroy(confirmEventRequest);
		return false;
	}
	confirmEventRequest->messageCode = JAUS_REPORT_CONFIGURATION;

	queryConf = queryConfigurationMessageFromJausMessage(createEvent->queryMessage);
	if(!queryConf)
	{
		// ERROR: Cannot unpack query message
		// TODO: Log Error. Throw Exception
		confirmEventRequest->responseCode = INVALID_EVENT_RESPONSE;
		txMessage = confirmEventRequestMessageToJausMessage(confirmEventRequest);
		if(txMessage)
		{
			this->commMngr->receiveJausMessage(txMessage, this);
		}
		confirmEventRequestMessageDestroy(confirmEventRequest);
		return false;
	}
	
	if(queryConf->queryField == JAUS_SUBSYSTEM_CONFIGURATION)
	{
		for(iterator = subsystemChangeList.begin(); iterator != subsystemChangeList.end(); iterator++)
		{
			if(jausAddressEqual(createEvent->source, iterator->second))
			{
				// Event already created
				confirmEventRequest->responseCode = SUCCESSFUL_RESPONSE;
				confirmEventRequest->eventId = iterator->first;
				break;
			}
		}

		nextEventId = getNextEventId();
		if(nextEventId >= 0)
		{
			confirmEventRequest->eventId = (JausByte) nextEventId;
			eventId[nextEventId] = true;
			subsystemChangeList[nextEventId] = createEvent->source;
			confirmEventRequest->responseCode = SUCCESSFUL_RESPONSE;
		}
		else
		{
			confirmEventRequest->responseCode = CONNECTION_REFUSED_RESPONSE;
			confirmEventRequest->eventId = 0;
		}
	}
	else
	{
		// TODO: Log Error. Throw Exception.
		// Invalid Query Type
		confirmEventRequest->responseCode = INVALID_EVENT_RESPONSE;
		txMessage = confirmEventRequestMessageToJausMessage(confirmEventRequest);
		if(txMessage)
		{
			this->commMngr->receiveJausMessage(txMessage, this);
		}
		confirmEventRequestMessageDestroy(confirmEventRequest);
		return false;
	}

	// Send response
	txMessage = confirmEventRequestMessageToJausMessage(confirmEventRequest);
	if(txMessage)
	{
		this->commMngr->receiveJausMessage(txMessage, this);
	}

	queryConfigurationMessageDestroy(queryConf);
	createEventMessageDestroy(createEvent);
	return true;
}

bool CommunicatorComponent::processCancelEvent(JausMessage message)
{
	CancelEventMessage cancelEvent = NULL;

	cancelEvent = cancelEventMessageFromJausMessage(message);
	if(!cancelEvent)
	{
		// Error unpacking message
		// TODO: Throw Exception. Log Error.
		return false;
	}

	if(cancelEvent->messageCode == JAUS_QUERY_CONFIGURATION)
	{
		if(eventId[cancelEvent->eventId])
		{
			eventId[cancelEvent->eventId] = false;

			if(subsystemChangeList.find(cancelEvent->eventId) != subsystemChangeList.end())
			{
				// Remove that element
				subsystemChangeList.erase(subsystemChangeList.find(cancelEvent->eventId));
			}
			else if(nodeChangeList.find(cancelEvent->eventId) != nodeChangeList.end())
			{
				// Remove that element
				nodeChangeList.erase(nodeChangeList.find(cancelEvent->eventId));
			}
		}
	}

	cancelEventMessageDestroy(cancelEvent);
	return true;
}

void CommunicatorComponent::sendNodeChangedEvents()
{
	ReportConfigurationMessage reportConf = NULL;
	JausMessage txMessage = NULL;	
	HASH_MAP <int, JausAddress>::iterator iterator;
	
	JausNode thisNode = systemTree->getNode(this->cmpt->address);
	if(!thisNode)
	{
		// TODO: Record an error. Throw Exception
		return;
	}

	reportConf = reportConfigurationMessageCreate();
	if(!reportConf)
	{
		// TODO: Record an error. Throw Exception
		jausNodeDestroy(thisNode);
		return;
	}
	jausArrayAdd(reportConf->subsystem->nodes, (void *)thisNode);

	txMessage = reportConfigurationMessageToJausMessage(reportConf);
	jausAddressCopy(txMessage->source, cmpt->address);

	// TODO: Go through nodeChangeList looking for dead addresses
	for(iterator = nodeChangeList.begin(); iterator != nodeChangeList.end(); iterator++)
	{
		jausAddressCopy(txMessage->destination, iterator->second);
		this->commMngr->receiveJausMessage(jausMessageClone(txMessage), this);
	}
	
	jausMessageDestroy(txMessage);
	reportConfigurationMessageDestroy(reportConf);
}

void CommunicatorComponent::sendSubsystemChangedEvents()
{
	ReportConfigurationMessage reportConf = NULL;
	JausMessage txMessage = NULL;
	EventMessage eventMessage = NULL;
	HASH_MAP <int, JausAddress>::iterator iterator;

	JausSubsystem thisSubs = systemTree->getSubsystem(this->cmpt->address);
	if(!thisSubs)
	{
		// TODO: Record an error. Throw Exception
		return;
	}

	reportConf = reportConfigurationMessageCreate();
	if(!reportConf)
	{
		// TODO: Record an error. Throw Exception
		jausSubsystemDestroy(thisSubs);
		return;
	}
	jausSubsystemDestroy(reportConf->subsystem);
	reportConf->subsystem = thisSubs;

	eventMessage = eventMessageCreate();
	if(!eventMessage)
	{
		// TODO: Record an error. Throw Exception
		reportConfigurationMessageDestroy(reportConf);
		return;
	}

	eventMessage->reportMessage = reportConfigurationMessageToJausMessage(reportConf);
	if(!eventMessage->reportMessage)
	{
		// TODO: Record an error. Throw Exception
		reportConfigurationMessageDestroy(reportConf);
		eventMessageDestroy(eventMessage);
		return;
	}
	jausAddressCopy(eventMessage->source, cmpt->address);

	// TODO: check subsystemChangeList for dead addresses
	for(iterator = subsystemChangeList.begin(); iterator != subsystemChangeList.end(); iterator++)
	{
		eventMessage->eventId = iterator->first;
		jausAddressCopy(eventMessage->destination, iterator->second);
		txMessage = eventMessageToJausMessage(eventMessage);
		this->commMngr->receiveJausMessage(jausMessageClone(txMessage), this);
	}

	jausMessageDestroy(txMessage);
	reportConfigurationMessageDestroy(reportConf);
}

void CommunicatorComponent::generateHeartbeats()
{
	static double nextSendTime = getTimeSeconds();
	ReportHeartbeatPulseMessage heartbeat;
	JausMessage subsHeartbeat;
	
	if(getTimeSeconds() >= nextSendTime)
	{
		heartbeat = reportHeartbeatPulseMessageCreate();
		if(!heartbeat)
		{
			// Error constructing message
			// TODO: Log Error.
			return;
		}
		jausAddressCopy(heartbeat->source, cmpt->address);

		subsHeartbeat = reportHeartbeatPulseMessageToJausMessage(heartbeat);
		if(!subsHeartbeat)
		{
			// Error constructing message
			// TODO: Log Error.
			reportHeartbeatPulseMessageDestroy(heartbeat);
			return;
		}

		// Send Heartbeat to other node managers on this subsystem
		subsHeartbeat->destination->subsystem = JAUS_BROADCAST_SUBSYSTEM_ID;
		subsHeartbeat->destination->node = JAUS_BROADCAST_NODE_ID;
		subsHeartbeat->destination->component = JAUS_NODE_MANAGER_COMPONENT;
		subsHeartbeat->destination->instance = 1;
		this->commMngr->receiveJausMessage(subsHeartbeat, this);

		nextSendTime = getTimeSeconds() + 1.0;
		reportHeartbeatPulseMessageDestroy(heartbeat);
	}
}

bool CommunicatorComponent::sendQueryNodeIdentification(JausAddress address)
{
	QueryIdentificationMessage queryId = NULL;
	JausMessage txMessage = NULL;

	// TODO: Check timeout and request limit
	if( systemTree->hasNode(address) && 
		!systemTree->hasNodeIdentification(address))
	{
		// Create query message
		queryId = queryIdentificationMessageCreate();
		if(!queryId)
		{
			// Constructor Failed
			return false;
		}
		
		queryId->queryField = JAUS_QUERY_FIELD_NODE_IDENTITY;
		txMessage = queryIdentificationMessageToJausMessage(queryId);
		if(!txMessage)
		{
			// ToJausMessage Failed
			queryIdentificationMessageDestroy(queryId);
			return false;
		}

		jausAddressCopy(txMessage->destination, address);
		jausAddressCopy(txMessage->source, cmpt->address);
		this->commMngr->receiveJausMessage(txMessage, this);
		queryIdentificationMessageDestroy(queryId);
		return true;
	}
	return false;
}

bool CommunicatorComponent::sendQuerySubsystemIdentification(JausAddress address)
{
	QueryIdentificationMessage queryId = NULL;
	JausMessage txMessage = NULL;

	// TODO: Check timeout and request limit
	if( systemTree->hasSubsystem(address) && 
		!systemTree->hasSubsystemIdentification(address))
	{
		// Create query message
		queryId = queryIdentificationMessageCreate();
		if(!queryId)
		{
			// Constructor Failed
			return false;
		}
		
		queryId->queryField = JAUS_QUERY_FIELD_SS_IDENTITY;
		txMessage = queryIdentificationMessageToJausMessage(queryId);
		if(!txMessage)
		{
			// ToJausMessage Failed
			queryIdentificationMessageDestroy(queryId);
			return false;
		}

		jausAddressCopy(txMessage->destination, address);
		jausAddressCopy(txMessage->source, cmpt->address);
		this->commMngr->receiveJausMessage(txMessage, this);
		queryIdentificationMessageDestroy(queryId);
		return true;
	}
	return false;
}

bool CommunicatorComponent::sendQueryComponentIdentification(JausAddress address)
{
	QueryIdentificationMessage queryId = NULL;
	JausMessage txMessage = NULL;

	// TODO: Check timeout and request limit
	if(systemTree->hasComponent(address) &&
		!systemTree->hasComponentIdentification(address))
	{
		// Create query message
		queryId = queryIdentificationMessageCreate();
		if(!queryId)
		{
			// Constructor Failed
			return false;
		}
		
		queryId->queryField = JAUS_QUERY_FIELD_COMPONENT_IDENTITY;
		txMessage = queryIdentificationMessageToJausMessage(queryId);
		if(!txMessage)
		{
			// ToJausMessage Failed
			queryIdentificationMessageDestroy(queryId);
			return false;
		}

		jausAddressCopy(txMessage->destination, address);
		jausAddressCopy(txMessage->source, cmpt->address);
		this->commMngr->receiveJausMessage(txMessage, this);
		queryIdentificationMessageDestroy(queryId);
		return true;
	}
	return false;
}

bool CommunicatorComponent::processCreateServiceConnection(JausMessage message)
{
	// Not implemented right now
	return true;
}

bool CommunicatorComponent::processActivateServiceConnection(JausMessage message)
{
	// Not Implemented right now
	return true;
}

bool CommunicatorComponent::processSuspendServiceConnection(JausMessage message)
{
	// Not Implemented right now
	return true;
}

bool CommunicatorComponent::processTerminateServiceConnection(JausMessage message)
{
	// Not Implemented right now
	return true;
}

bool CommunicatorComponent::processRequestComponentControl(JausMessage message)
{
	RequestComponentControlMessage requestComponentControl = NULL;
	RejectComponentControlMessage rejectComponentControl = NULL;
	ConfirmComponentControlMessage confirmComponentControl = NULL;
	JausMessage txMessage = NULL;

	requestComponentControl = requestComponentControlMessageFromJausMessage(message);
	if(!requestComponentControl)
	{
		// Error unpacking message
		// TODO: Log Error. Throw Exception
		return false;
	}

	if(cmpt->controller.active)
	{
		if(requestComponentControl->authorityCode > cmpt->controller.authority) // Test for higher authority
		{	
			// Terminate control of current component
			rejectComponentControl = rejectComponentControlMessageCreate();
			jausAddressCopy(rejectComponentControl->source, cmpt->address);
			jausAddressCopy(rejectComponentControl->destination, cmpt->controller.address);
			txMessage = rejectComponentControlMessageToJausMessage(rejectComponentControl); 
			if(txMessage)
			{
				this->commMngr->receiveJausMessage(txMessage, this);
			}
			
			// Accept control of new component
			confirmComponentControl = confirmComponentControlMessageCreate();
			jausAddressCopy(confirmComponentControl->source, cmpt->address);
			jausAddressCopy(confirmComponentControl->destination, message->source);
			confirmComponentControl->responseCode = JAUS_CONTROL_ACCEPTED;
			txMessage = confirmComponentControlMessageToJausMessage(confirmComponentControl); 
			if(txMessage)
			{
				this->commMngr->receiveJausMessage(txMessage, this);
			}
			
			// Update cmpt controller information
			jausAddressCopy(cmpt->controller.address, message->source);
			cmpt->controller.authority = requestComponentControl->authorityCode;
		
			rejectComponentControlMessageDestroy(rejectComponentControl);
			confirmComponentControlMessageDestroy(confirmComponentControl);						
		}	
		else
		{
			if(!jausAddressEqual(message->source, cmpt->controller.address))
			{
				rejectComponentControl = rejectComponentControlMessageCreate();
				jausAddressCopy(rejectComponentControl->source, cmpt->address);
				jausAddressCopy(rejectComponentControl->destination, message->source);
				txMessage = rejectComponentControlMessageToJausMessage(rejectComponentControl); 
				if(txMessage)
				{
					this->commMngr->receiveJausMessage(txMessage, this);
				}

				rejectComponentControlMessageDestroy(rejectComponentControl);
			}
			else
			{
				// Reaccept control of new component
				confirmComponentControl = confirmComponentControlMessageCreate();
				jausAddressCopy(confirmComponentControl->source, cmpt->address);
				jausAddressCopy(confirmComponentControl->destination, message->source);
				confirmComponentControl->responseCode = JAUS_CONTROL_ACCEPTED;
				txMessage = confirmComponentControlMessageToJausMessage(confirmComponentControl); 
				if(txMessage)
				{
					this->commMngr->receiveJausMessage(txMessage, this);
				}
				
				confirmComponentControlMessageDestroy(confirmComponentControl);						
			}
		}
	}					
	else // Not currently under component control, so give control
	{
		confirmComponentControl = confirmComponentControlMessageCreate();
		jausAddressCopy(confirmComponentControl->source, cmpt->address);
		jausAddressCopy(confirmComponentControl->destination, message->source);
		confirmComponentControl->responseCode = JAUS_CONTROL_ACCEPTED;
		txMessage = confirmComponentControlMessageToJausMessage(confirmComponentControl); 
		if(txMessage)
		{
			this->commMngr->receiveJausMessage(txMessage, this);
		}

		jausAddressCopy(cmpt->controller.address, message->source);
		cmpt->controller.authority = requestComponentControl->authorityCode;
		cmpt->controller.active = JAUS_TRUE;

		confirmComponentControlMessageDestroy(confirmComponentControl);						
	}

	requestComponentControlMessageDestroy(requestComponentControl);
	return true;
}

bool CommunicatorComponent::processQueryComponentAuthority(JausMessage message)
{
	ReportComponentAuthorityMessage report = NULL;
	JausMessage txMessage = NULL;


	report = reportComponentAuthorityMessageCreate();
	if(!report)
	{
		// TODO: Throw Exception. Log Error.
		return false;
	}

	jausAddressCopy(report->source, cmpt->address);
	jausAddressCopy(report->destination, message->source);
	report->authorityCode = cmpt->authority;
	
	txMessage = reportComponentAuthorityMessageToJausMessage(report);	
	if(txMessage)
	{
		this->commMngr->receiveJausMessage(txMessage, this);
	}

	reportComponentAuthorityMessageDestroy(report);
	return true;
}

bool CommunicatorComponent::processQueryComponentStatus(JausMessage message)
{
	ReportComponentStatusMessage reportComponentStatus = NULL;
	JausMessage txMessage = NULL;


	reportComponentStatus = reportComponentStatusMessageCreate();
	jausAddressCopy(reportComponentStatus->source, cmpt->address);
	jausAddressCopy(reportComponentStatus->destination, message->source);
	reportComponentStatus->primaryStatusCode = cmpt->state;
	
	txMessage = reportComponentStatusMessageToJausMessage(reportComponentStatus);
	if(txMessage)
	{
		this->commMngr->receiveJausMessage(txMessage, this);
	}

	reportComponentStatusMessageDestroy(reportComponentStatus);
	return true;
}

bool CommunicatorComponent::processQueryHeartbeatPulse(JausMessage message)
{

	JausMessage txMessage = NULL;
	ReportHeartbeatPulseMessage reportHeartbeat = NULL;

	reportHeartbeat = reportHeartbeatPulseMessageCreate();
	if(!reportHeartbeat)
	{
		// TODO: Log Error. Throw Exception.
		return false;
	}

	jausAddressCopy(reportHeartbeat->source, cmpt->address);
	jausAddressCopy(reportHeartbeat->destination, message->source);
	txMessage = reportHeartbeatPulseMessageToJausMessage(reportHeartbeat);
	if(txMessage)
	{
		this->commMngr->receiveJausMessage(txMessage, this);
	}
	return true;
}

bool CommunicatorComponent::processQueryConfiguration(JausMessage message)
{
	QueryConfigurationMessage queryConf = NULL;
	ReportConfigurationMessage reportConf = NULL;
	JausMessage txMessage = NULL;
	JausNode node = NULL;

	queryConf = queryConfigurationMessageFromJausMessage(message);
	if(!queryConf)
	{
		// TODO: Log Error. Throw Exception.
		// Error unpacking message	
		return false;
	}
	
	switch(queryConf->queryField)
	{
		case JAUS_SUBSYSTEM_CONFIGURATION:
			// Subsystem Configuration requests should go to the Communicator!
			// This is included for backwards compatibility and other implementation support
			reportConf = reportConfigurationMessageCreate();
			if(!reportConf)
			{
				// TODO: Log Error. Throw Exception
				queryConfigurationMessageDestroy(queryConf);
				return false;
			}
			
			// Remove the subsystem created by the constructor
			jausSubsystemDestroy(reportConf->subsystem);

			// This call to the systemTree returns a copy, so safe to set this pointer to it
			reportConf->subsystem = systemTree->getSubsystem(this->cmpt->address->subsystem);
			if(reportConf->subsystem)
			{
				txMessage = reportConfigurationMessageToJausMessage(reportConf);
				jausAddressCopy(txMessage->source, cmpt->address);
				jausAddressCopy(txMessage->destination, queryConf->source);
				if(txMessage)
				{
					this->commMngr->receiveJausMessage(txMessage, this);
				}
			}

			reportConfigurationMessageDestroy(reportConf);
			queryConfigurationMessageDestroy(queryConf);
			return true;

		case JAUS_NODE_CONFIGURATION:
			// Node Configuration requests should go to the Node Manager!
			// This is included for backwards compatibility and other implementation support
			reportConf = reportConfigurationMessageCreate();
			if(!reportConf)
			{
				// TODO: Log Error. Throw Exception
				queryConfigurationMessageDestroy(queryConf);
				return false;
			}
			
			// This call to the systemTree returns a copy, so safe to set this pointer to it
			node = systemTree->getNode(this->cmpt->address->subsystem, this->cmpt->address->node);
			if(node)
			{
				jausArrayAdd(reportConf->subsystem->nodes, node);
			}

			txMessage = reportConfigurationMessageToJausMessage(reportConf);
			jausAddressCopy(txMessage->source, cmpt->address);
			jausAddressCopy(txMessage->destination, queryConf->source);
			if(txMessage)
			{
				this->commMngr->receiveJausMessage(txMessage, this);
			}

			reportConfigurationMessageDestroy(reportConf);
			queryConfigurationMessageDestroy(queryConf);
			return true;

		default:
			// TODO: Log Error. Throw Exception.
			// Unknown query type
			queryConfigurationMessageDestroy(queryConf);
			return false;
	}
}

bool CommunicatorComponent::processQueryIdentification(JausMessage message)
{
	QueryIdentificationMessage queryId = NULL;
	ReportIdentificationMessage reportId = NULL;
	JausMessage txMessage = NULL;
	char *identification = NULL;

	queryId = queryIdentificationMessageFromJausMessage(message);
	if(!queryId)
	{
		// TODO: Log Error. Throw Exception.
		// Error unpacking message	
		return false;
	}
	
	switch(queryId->queryField)
	{
		case JAUS_QUERY_FIELD_SS_IDENTITY:
			reportId = reportIdentificationMessageCreate();
			if(!reportId)
			{
				// TODO: Log Error. Throw Exception
				queryIdentificationMessageDestroy(queryId);
				return false;
			}

			identification = systemTree->getSubsystemIdentification(cmpt->address);
			if(strlen(identification) < JAUS_IDENTIFICATION_LENGTH_BYTES)
			{
				sprintf(reportId->identification, "%s", identification);
			}
			else
			{
				memcpy(reportId->identification, identification, JAUS_IDENTIFICATION_LENGTH_BYTES-1);
				reportId->identification[JAUS_IDENTIFICATION_LENGTH_BYTES-1] = 0;
			}

			reportId->queryType = JAUS_QUERY_FIELD_SS_IDENTITY;
			txMessage = reportIdentificationMessageToJausMessage(reportId);
			jausAddressCopy(txMessage->source, cmpt->address);
			jausAddressCopy(txMessage->destination, queryId->source);
			if(txMessage)
			{
				this->commMngr->receiveJausMessage(txMessage, this);
			}

			reportIdentificationMessageDestroy(reportId);
			queryIdentificationMessageDestroy(queryId);
			return true;

		case JAUS_QUERY_FIELD_NODE_IDENTITY:
			// Node Identification requests should go to the NM!
			// This is included for backwards compatibility and other implementation support
			reportId = reportIdentificationMessageCreate();
			if(!reportId)
			{
				// TODO: Log Error. Throw Exception
				queryIdentificationMessageDestroy(queryId);
				return false;
			}
			
			identification = systemTree->getNodeIdentification(cmpt->address);
			if(strlen(identification) < JAUS_IDENTIFICATION_LENGTH_BYTES)
			{
				sprintf(reportId->identification, "%s", identification);
			}
			else
			{
				memcpy(reportId->identification, identification, JAUS_IDENTIFICATION_LENGTH_BYTES-1);
				reportId->identification[JAUS_IDENTIFICATION_LENGTH_BYTES-1] = 0;
			}

			reportId->queryType = JAUS_QUERY_FIELD_NODE_IDENTITY;
			txMessage = reportIdentificationMessageToJausMessage(reportId);
			jausAddressCopy(txMessage->source, cmpt->address);
			jausAddressCopy(txMessage->destination, queryId->source);
			if(txMessage)
			{
				this->commMngr->receiveJausMessage(txMessage, this);
			}

			reportIdentificationMessageDestroy(reportId);
			queryIdentificationMessageDestroy(queryId);
			return true;

		case JAUS_QUERY_FIELD_COMPONENT_IDENTITY:
			reportId = reportIdentificationMessageCreate();
			if(!reportId)
			{
				// TODO: Log Error. Throw Exception
				queryIdentificationMessageDestroy(queryId);
				return false;
			}
			
			identification = cmpt->identification;
			if(strlen(identification) < JAUS_IDENTIFICATION_LENGTH_BYTES)
			{
				sprintf(reportId->identification, "%s", identification);
			}
			else
			{
				memcpy(reportId->identification, identification, JAUS_IDENTIFICATION_LENGTH_BYTES-1);
				reportId->identification[JAUS_IDENTIFICATION_LENGTH_BYTES-1] = 0;
			}

			reportId->queryType = JAUS_QUERY_FIELD_COMPONENT_IDENTITY;
			txMessage = reportIdentificationMessageToJausMessage(reportId);
			jausAddressCopy(txMessage->source, cmpt->address);
			jausAddressCopy(txMessage->destination, queryId->source);
			if(txMessage)
			{
				this->commMngr->receiveJausMessage(txMessage, this);
			}

			reportIdentificationMessageDestroy(reportId);
			queryIdentificationMessageDestroy(queryId);
			return true;

		default:
			queryIdentificationMessageDestroy(queryId);
			return false;
	}
}

bool CommunicatorComponent::processQueryServices(JausMessage message)
{
	QueryServicesMessage queryServices = NULL;
	ReportServicesMessage reportServices = NULL;
	JausMessage txMessage = NULL;

	queryServices = queryServicesMessageFromJausMessage(message);
	if(!queryServices)
	{
		// TODO: Log Error. Throw Exception.
		return false;
	}

	// Respond with our services
	reportServices = reportServicesMessageCreate();
	if(!reportServices)
	{
		// TODO: Log Error. Throw Exception.
		queryServicesMessageDestroy(queryServices);
		return false;
	}

	jausAddressCopy(reportServices->destination, message->source);
	jausAddressCopy(reportServices->source, cmpt->address);
	jausServicesDestroy(reportServices->jausServices);
	reportServices->jausServices = jausServicesClone(cmpt->services);

	txMessage = reportServicesMessageToJausMessage(reportServices);
	if(txMessage)
	{
		this->commMngr->receiveJausMessage(txMessage, this);
	}

	reportServicesMessageDestroy(reportServices);
	queryServicesMessageDestroy(queryServices);
	return true;
}

bool CommunicatorComponent::processConfirmEvent(JausMessage message)
{
	ConfirmEventRequestMessage confirm = NULL;
	
	confirm = confirmEventRequestMessageFromJausMessage(message);
	if(!confirm)
	{
		jausMessageDestroy(message);
		return false;
	}

	if(	confirm->source->node == this->cmpt->address->node &&
		confirm->source->component == JAUS_NODE_MANAGER_COMPONENT &&
		confirm->messageCode == JAUS_REPORT_CONFIGURATION &&
		confirm->responseCode == SUCCESSFUL_RESPONSE)
	{
		this->nodeManagerSubsystemEventConfirmed = true;
	}


	jausMessageDestroy(message);
	return true;
}

bool CommunicatorComponent::processEvent(JausMessage message)
{
	EventMessage eventMessage;

	eventMessage = eventMessageFromJausMessage(message);
	if(!eventMessage)
	{
		// Error unpacking the eventMessage
		ErrorEvent *e = new ErrorEvent(ErrorEvent::Memory, __FUNCTION__, __LINE__, "Cannot unpack EventMessage!");
		this->eventHandler->handleEvent(e);
		jausMessageDestroy(message);
		return false;
	}

	processMessage(jausMessageClone(eventMessage->reportMessage));
	eventMessageDestroy(eventMessage);
	return true;
}

bool CommunicatorComponent::sendQueryComponentServices(JausAddress address)
{
	QueryServicesMessage query = NULL;
	JausMessage txMessage = NULL;

	// TODO: Check timeout and request limit
	if( systemTree->hasComponent(address) &&
		!systemTree->hasComponentServices(address))
	{
		// Create query message
		query = queryServicesMessageCreate();
		if(!query)
		{
			// Constructor Failed
			return false;
		}
		
		txMessage = queryServicesMessageToJausMessage(query);
		if(!txMessage)
		{
			// ToJausMessage Failed
			queryServicesMessageDestroy(query);
			return false;
		}

		jausAddressCopy(txMessage->destination, address);
		jausAddressCopy(txMessage->source, cmpt->address);
		this->commMngr->receiveJausMessage(txMessage, this);
		queryServicesMessageDestroy(query);
		return true;
	}
	return false;
}
bool CommunicatorComponent::sendQueryNodeConfiguration(JausAddress address, bool createEvent)
{
	QueryConfigurationMessage query = NULL;
	JausMessage txMessage = NULL;
	CreateEventMessage createEventMsg = NULL;

	// TODO: Check timeout and request limit
	if( systemTree->hasNode(address) &&
		!systemTree->hasNodeConfiguration(address))
	{
		// Create query message
		query = queryConfigurationMessageCreate();
		if(!query)
		{
			// Constructor Failed
			return false;
		}
		query->queryField = JAUS_NODE_CONFIGURATION;

		txMessage = queryConfigurationMessageToJausMessage(query);
		if(!txMessage)
		{
			// ToJausMessage Failed
			queryConfigurationMessageDestroy(query);
			return false;
		}

		jausAddressCopy(txMessage->destination, address);
		jausAddressCopy(txMessage->source, cmpt->address);
		this->commMngr->receiveJausMessage(txMessage, this);
		
		if(createEvent)
		{
			createEventMsg = createEventMessageCreate();
			if(!createEventMsg)
			{
				queryConfigurationMessageDestroy(query);
				return false;
			}
			
			// Setup Create Event PV
			createEventMsg->presenceVector = 0;
			jausByteSetBit(&createEventMsg->presenceVector, CREATE_EVENT_PV_QUERY_MESSAGE_BIT);

			createEventMsg->reportMessageCode = jausMessageGetComplimentaryCommandCode(query->commandCode);
			createEventMsg->eventType = EVENT_EVERY_CHANGE_TYPE;
			createEventMsg->queryMessage = queryConfigurationMessageToJausMessage(query);
			if(!createEventMsg->queryMessage)
			{
				// Problem with queryConfigurationMessageToJausMessage
				createEventMessageDestroy(createEventMsg);
				queryConfigurationMessageDestroy(query);
				return false;
			}
			
			txMessage = createEventMessageToJausMessage(createEventMsg);
			if(!txMessage)
			{
				// Problem with createEventMsgMessageToJausMessage
				createEventMessageDestroy(createEventMsg);
				queryConfigurationMessageDestroy(query);
				return false;
			}

			jausAddressCopy(txMessage->destination, address);
			jausAddressCopy(txMessage->source, cmpt->address);
			this->commMngr->receiveJausMessage(txMessage, this);
		}

		queryConfigurationMessageDestroy(query);
		return true;
	}
	return false;
}

bool CommunicatorComponent::sendQuerySubsystemConfiguration(JausAddress address, bool createEvent)
{
	QueryConfigurationMessage query = NULL;
	JausMessage txMessage = NULL;
	CreateEventMessage createEventMsg = NULL;

	// TODO: Check timeout and request limit
	if( systemTree->hasSubsystem(address) &&
		!systemTree->hasSubsystemConfiguration(address))
	{
		// Create query message
		query = queryConfigurationMessageCreate();
		if(!query)
		{
			// Constructor Failed
			return false;
		}
		query->queryField = JAUS_SUBSYSTEM_CONFIGURATION;

		txMessage = queryConfigurationMessageToJausMessage(query);
		if(!txMessage)
		{
			// ToJausMessage Failed
			queryConfigurationMessageDestroy(query);
			return false;
		}

		jausAddressCopy(txMessage->destination, address);
		jausAddressCopy(txMessage->source, cmpt->address);
		this->commMngr->receiveJausMessage(txMessage, this);
		jausMessageDestroy(txMessage); // Send Query Node Configuration

		if(createEvent)
		{
			createEventMsg = createEventMessageCreate();
			if(!createEventMsg)
			{
				queryConfigurationMessageDestroy(query);
				return false;
			}

			// Setup Create Event PV
			createEventMsg->presenceVector = 0;
			jausByteSetBit(&createEventMsg->presenceVector, CREATE_EVENT_PV_QUERY_MESSAGE_BIT);
			
			createEventMsg->reportMessageCode = jausMessageGetComplimentaryCommandCode(query->commandCode);
			createEventMsg->eventType = EVENT_EVERY_CHANGE_TYPE;
			createEventMsg->queryMessage = queryConfigurationMessageToJausMessage(query);
			if(!createEventMsg->queryMessage)
			{
				// Problem with queryConfigurationMessageToJausMessage
				createEventMessageDestroy(createEventMsg);
				queryConfigurationMessageDestroy(query);
				return false;
			}
			
			txMessage = createEventMessageToJausMessage(createEventMsg);
			if(!txMessage)
			{
				// Problem with createEventMsgMessageToJausMessage
				createEventMessageDestroy(createEventMsg);
				queryConfigurationMessageDestroy(query);
				return false;
			}

			jausAddressCopy(txMessage->destination, address);
			jausAddressCopy(txMessage->source, cmpt->address);
			this->commMngr->receiveJausMessage(txMessage, this);
		}

		queryConfigurationMessageDestroy(query);
		return true;
	}
	return false;
}

int CommunicatorComponent::getNextEventId()
{
	int i;
	for(i = 0; i < MAXIMUM_EVENT_ID; i++)
	{
		if(eventId[i] == false)
		{
			return i;
		}
	}
	return -1;
}



