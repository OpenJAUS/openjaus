#include "NodeManagerComponent.h"
#include "JausComponentCommunicationManager.h"
#include "SystemTree.h"
#include "jaus.h"
#include "timeLib.h"

NodeManagerComponent::NodeManagerComponent(FileLoader *configData, JausComponentCommunicationManager *cmptComms)
{
	int subsystemId, nodeId;

	if(configData == NULL)
	{
		// OK, don't do this. This is bad.
		// TODO: Throw an exception? Log an error.
		return;
	}

	if(cmptComms == NULL)
	{
		// OK, don't do this. This is bad.
		// TODO: Throw an exception? Log an error.
		return;
	}

	this->type = COMPONENT_INTERFACE;
	this->commMngr = cmptComms;
	this->configData = configData;
	this->name = "NodeManager";
	this->cmptRateHz = NM_RATE_HZ;
	this->cmpt->identification = (char *)this->name.c_str();
	this->systemTree = cmptComms->getSystemTree();
	for(int i = 0; i < MAXIMUM_EVENT_ID; i++)
	{
		eventId[i] = false;
	}

	// Register ourselves on our queue
	this->queue.registerMonitor(this);

	// NOTE: These two values should exist in the properties file and should be checked 
	// in the NodeManager class prior to constructing this object
	subsystemId = configData->GetConfigDataInt("JAUS", "Subsystem Id = ");
	if(subsystemId < 1 || subsystemId > 254)
	{
		// Invalid ID
		// TODO: Throw an exception? Log an error.
		return;
	}

	nodeId = configData->GetConfigDataInt("JAUS", "Node Id = ");
	if(nodeId < 1 || nodeId > 254)
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
	this->cmpt->address->component = JAUS_NODE_MANAGER;
	this->cmpt->address->instance = 1;

	if(!this->commMngr->getSystemTree()->addComponent(this->cmpt->address, this->cmpt))
	{
		// TODO: Log Error, we can't add a node manager with instance 1
	}
	this->setupThread();
	this->startupState();
}

NodeManagerComponent::~NodeManagerComponent(void){}

bool NodeManagerComponent::processMessage(JausTransportPacket *jtPacket)
{
	// First, let double check this is for me!
	if(!jausAddressEqual(jtPacket->getJausMessage()->destination, cmpt->address))
	{
		// Whoa... this is wrong
		// TODO: Throw exception? Log an Error.
		delete jtPacket;
		return false;
	}

	// TODO: Let's add our hack here for making every message look like a heartbeat!

	switch(jtPacket->getJausMessage()->commandCode)
	{
		case JAUS_SET_COMPONENT_AUTHORITY:
		case JAUS_SHUTDOWN:
		case JAUS_STANDBY:
		case JAUS_RESUME:
		case JAUS_RESET:
		case JAUS_SET_EMERGENCY:
		case JAUS_CLEAR_EMERGENCY:
			// These messages are ignored!
			break;
		
		case JAUS_CREATE_SERVICE_CONNECTION:
			processCreateServiceConnection(jtPacket);
			break;

		case JAUS_ACTIVATE_SERVICE_CONNECTION:
			processActivateServiceConnection(jtPacket);
			break;

		case JAUS_SUSPEND_SERVICE_CONNECTION:
			processSuspendServiceConnection(jtPacket);
			break;

		case JAUS_TERMINATE_SERVICE_CONNECTION:
			processTerminateServiceConnection(jtPacket);
			break;

		case JAUS_REQUEST_COMPONENT_CONTROL:
			processRequestComponentControl(jtPacket);
			break;

		case JAUS_QUERY_COMPONENT_AUTHORITY:
			processQueryComponentAuthority(jtPacket);
			break;

		case JAUS_QUERY_COMPONENT_STATUS:
			processQueryComponentStatus(jtPacket);
			break;

		case JAUS_QUERY_HEARTBEAT_PULSE:
			processQueryHeartbeatPulse(jtPacket);
			break;

		case JAUS_REPORT_HEARTBEAT_PULSE:
			processReportHeartbeatPulse(jtPacket);
			break;

		case JAUS_QUERY_CONFIGURATION:
			processQueryConfiguration(jtPacket);
			break;

		case JAUS_QUERY_IDENTIFICATION:
			processQueryIdentification(jtPacket);
			break;

		case JAUS_QUERY_SERVICES:
			processQueryServices(jtPacket);
			break;

		case JAUS_REPORT_CONFIGURATION:
			processReportConfiguration(jtPacket);
			break;

		case JAUS_REPORT_IDENTIFICATION:
			processReportIdentification(jtPacket);
			break;

		case JAUS_REPORT_SERVICES:
			processReportServices(jtPacket);
			break;

		case JAUS_CANCEL_EVENT:
			processCancelEvent(jtPacket);
			break;

		case JAUS_CONFIRM_EVENT:
			processConfirmEvent(jtPacket);
			break;

		case JAUS_CREATE_EVENT:
			processCreateEvent(jtPacket);
			break;

		default:
			// Unhandled message received by node manager component
			delete jtPacket;
			return false;
	}
	
	delete jtPacket;
	return true;
}

std::string NodeManagerComponent::toString()
{
	return "Communicator Component";
}

JausAddress NodeManagerComponent::checkInLocalComponent(int cmptId, JausTransportData *data)
{
	JausComponent cmpt = jausComponentCreate();
	if(!cmpt) return NULL;
	
	// Setup query address
	cmpt->address->subsystem = this->cmpt->address->subsystem;
	cmpt->address->node = this->cmpt->address->subsystem;
	cmpt->address->component = cmptId;
	cmpt->address->instance = 0;

	// Query SystemTree for next valid instance ID
	cmpt->address->instance = this->getCommunicationManager()->getSystemTree()->getNextInstanceId(cmpt->address);
	
	// Check returned value
	if(cmpt->address->instance == JAUS_INVALID_INSTANCE_ID)
	{
		jausComponentDestroy(cmpt);
		return NULL;
	}
	else
	{
		if(this->commMngr->getSystemTree()->addComponent(this->cmpt->address, this->cmpt))
		{
			JausAddress address = jausAddressClone(cmpt->address);
			jausComponentDestroy(cmpt);
			
			sendNodeChangedEvents();
			return address;
		}
		else
		{
			jausComponentDestroy(cmpt);
			return NULL;
		}
	}
}

void NodeManagerComponent::checkOutLocalComponent(JausAddress address)
{
	//sendNodeChangedEvents();
}

void NodeManagerComponent::startupState()
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

	service = jausServiceCreate(JAUS_NODE_MANAGER);
	if(!service) return;
	jausServiceAddInputCommand(service, JAUS_QUERY_CONFIGURATION, NO_PRESENCE_VECTOR);
	jausServiceAddInputCommand(service, JAUS_QUERY_IDENTIFICATION, NO_PRESENCE_VECTOR);
	jausServiceAddInputCommand(service, JAUS_QUERY_SERVICES, NO_PRESENCE_VECTOR);
	jausServiceAddInputCommand(service, JAUS_REPORT_CONFIGURATION, NO_PRESENCE_VECTOR);
	jausServiceAddInputCommand(service, JAUS_REPORT_IDENTIFICATION, NO_PRESENCE_VECTOR);
	jausServiceAddInputCommand(service, JAUS_REPORT_SERVICES, NO_PRESENCE_VECTOR);
	jausServiceAddInputCommand(service, JAUS_CANCEL_EVENT, NO_PRESENCE_VECTOR);
	jausServiceAddInputCommand(service, JAUS_CONFIRM_EVENT, NO_PRESENCE_VECTOR);
	jausServiceAddInputCommand(service, JAUS_CREATE_EVENT, NO_PRESENCE_VECTOR);

	jausServiceAddOutputCommand(service, JAUS_QUERY_CONFIGURATION, NO_PRESENCE_VECTOR);
	jausServiceAddOutputCommand(service, JAUS_QUERY_IDENTIFICATION, NO_PRESENCE_VECTOR);
	jausServiceAddOutputCommand(service, JAUS_QUERY_SERVICES, NO_PRESENCE_VECTOR);
	jausServiceAddOutputCommand(service, JAUS_REPORT_CONFIGURATION, NO_PRESENCE_VECTOR);
	jausServiceAddOutputCommand(service, JAUS_REPORT_IDENTIFICATION, NO_PRESENCE_VECTOR);
	jausServiceAddOutputCommand(service, JAUS_REPORT_SERVICES, NO_PRESENCE_VECTOR);
	jausServiceAddOutputCommand(service, JAUS_CANCEL_EVENT, NO_PRESENCE_VECTOR);
	jausServiceAddOutputCommand(service, JAUS_CONFIRM_EVENT, NO_PRESENCE_VECTOR);
	jausServiceAddOutputCommand(service, JAUS_CREATE_EVENT, NO_PRESENCE_VECTOR);

	// Add Node Manager Service
	jausServiceAddService(cmpt->services, service);
}

void NodeManagerComponent::intializeState()
{
	// Nothing to do
	this->cmpt->state = JAUS_READY_STATE;
}

void NodeManagerComponent::standbyState()
{
	// Nothing to do
}

void NodeManagerComponent::readyState()
{
	// Nothing to do
}

void NodeManagerComponent::emergencyState()
{
	// Nothing to do
}

void NodeManagerComponent::failureState()
{
	// Nothing to do
}

void NodeManagerComponent::shutdownState()
{
	// Nothing to do
}

void NodeManagerComponent::allState()
{
	generateHeartbeats();
	// TODO: Create SystemTree refresh trigger at some rate
	// TODO: Check for serviceConnections
}

bool NodeManagerComponent::processReportConfiguration(JausTransportPacket *jtPacket)
{
	// This function follows the flowchart designed for NM 2.0 by D. Kent and T. Galluzzo
	ReportConfigurationMessage reportConf = NULL;

	reportConf = reportConfigurationMessageFromJausMessage(jtPacket->getJausMessage());
	if(!reportConf)
	{
		// Error unpacking the reportConf
		// TODO: Log Error
		delete jtPacket;
		return false;
	}

	// Has Subs?
	if(!systemTree->hasSubsystem(reportConf->source))
	{
		// TODO: Throw Exception. Log Error.
		reportConfigurationMessageDestroy(reportConf);
		delete jtPacket;
		return false;
	}

	// My Subs?
	if(!reportConf->source->subsystem == this->cmpt->address->subsystem)
	{
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
					delete jtPacket;
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
		delete jtPacket;
		return true;
	} // End !MySubs?
	
	if(!systemTree->hasNode(reportConf->source))
	{
		// Report Conf from unknown node! This is an unsolicited report
		// TODO: Throw Exception? Log error?
		reportConfigurationMessageDestroy(reportConf);
		delete jtPacket;
		return true;
	}

	// This is a node-level report
	// Should only have 1 node attached!
	if(reportConf->subsystem->nodes->elementCount > 1)
	{
		// TODO: Log Error? Throw Exception?
	}

	JausNode node = (JausNode) reportConf->subsystem->nodes->elementData[0];
	
	// Replace Node
	systemTree->replaceNode(reportConf->source, node);

	for(int i = 0; i < node->components->elementCount; i++)
	{
		JausComponent cmpt = (JausComponent) node->components->elementData[i];
		
		if(!jausComponentHasIdentification(cmpt))
		{
			sendQueryComponentIdentification(cmpt->address);
		}

		if(!jausComponentHasServices(cmpt))
		{
			sendQueryComponentServices(cmpt->address);
		}
	}

	// Send subs changed events
	sendSubsystemChangedEvents();
	
	reportConfigurationMessageDestroy(reportConf);
	delete jtPacket;
	return true;
}


bool NodeManagerComponent::processReportIdentification(JausTransportPacket *jtPacket)
{
	// This function follows the flowchart designed for NM 2.0 by D. Kent and T. Galluzzo
	ReportIdentificationMessage reportId = NULL;
	
	reportId = reportIdentificationMessageFromJausMessage(jtPacket->getJausMessage());
	if(!reportId)
	{
		// Error unpacking the reportId msg
		// TODO: Log Error. Throw Exception?
		delete jtPacket;
		return false;
	}

	switch(reportId->queryType)
	{
		case JAUS_QUERY_FIELD_SYSTEM_IDENTITY:
			// We don't care about this (actually we never ask for this, so this shouldn't happen)
			reportIdentificationMessageDestroy(reportId);
			delete jtPacket;
			return true;

		case JAUS_QUERY_FIELD_SS_IDENTITY:
			// Has Subs?
			if(!systemTree->hasSubsystem(reportId->source))
			{
				// Report ID from unknown Subsystem
				// TODO: Log Error. Throw Exception
				reportIdentificationMessageDestroy(reportId);
				delete jtPacket;
				return false;
			}

			// Add Identification
			systemTree->setSubsystemIdentification(reportId->source, reportId->identification);
			
			// Query Subs Conf & Setup event
			sendQuerySubsystemConfiguration(reportId->source, true);
			reportIdentificationMessageDestroy(reportId);
			delete jtPacket;
			return true;
			
		case JAUS_QUERY_FIELD_NODE_IDENTITY:
			// Has Node?
			if(!systemTree->hasNode(reportId->source))
			{
				// Report ID from unknown Node
				// TODO: Log Error. Throw Exception
				reportIdentificationMessageDestroy(reportId);
				delete jtPacket;
				return false;
			}

			// Add Identification
			systemTree->setNodeIdentification(reportId->source, reportId->identification);
			
			// Query Subs Conf & Setup event
			sendQueryNodeConfiguration(reportId->source, true);
			reportIdentificationMessageDestroy(reportId);
			delete jtPacket;
			return true;

		case JAUS_QUERY_FIELD_COMPONENT_IDENTITY:
			// Has Cmpt?
			if(!systemTree->hasComponent(reportId->source))
			{
				// Report ID from unknown Component
				// TODO: Log Error. Throw Exception
				reportIdentificationMessageDestroy(reportId);
				delete jtPacket;
				return false;
			}

			// Add Identification
			systemTree->setComponentIdentification(reportId->source, reportId->identification);
			reportIdentificationMessageDestroy(reportId);
			delete jtPacket;
			return true;

		default:
			// TODO: Log Error. Throw Exception.
			reportIdentificationMessageDestroy(reportId);
			delete jtPacket;
			return true;
	}

	reportIdentificationMessageDestroy(reportId);
	delete jtPacket;
	return true;
}

bool NodeManagerComponent::processReportServices(JausTransportPacket *jtPacket)
{
	ReportServicesMessage reportServices = NULL;

	reportServices = reportServicesMessageFromJausMessage(jtPacket->getJausMessage());
	if(!reportServices)
	{
		// TODO: Log error. Throw Exception.
		delete jtPacket;
		return false;
	}

	if(systemTree->hasComponent(reportServices->source))
	{
		systemTree->setComponentServices(reportServices->source, reportServices->jausServices);
	}

	reportServicesMessageDestroy(reportServices);
	delete jtPacket;
	return true;
}

bool NodeManagerComponent::processReportHeartbeatPulse(JausTransportPacket *jtPacket)
{
	// This function follows the flowchart designed for NM 2.0 by D. Kent and T. Galluzzo
	JausMessage message = jtPacket->getJausMessage();

	// Has Subs?
	if(!systemTree->hasSubsystem(message->source))
	{
		// Add Subs
		systemTree->addSubsystem(message->source, NULL);
		
		// Query SubsId
		sendQuerySubsystemIdentification(message->source);
		delete jtPacket;
		return true;
	}

	// Update Subsystem Timestamp
	systemTree->updateSubsystemTimestamp(message->source);
	
	// Has SubsId?
	if(!systemTree->hasSubsystemIdentification(message->source))
	{
		// Query SubsId
		sendQuerySubsystemIdentification(message->source);
		delete jtPacket;
		return true;
	}

	// My Subs?
	if(message->source->subsystem != this->cmpt->address->subsystem)
	{
		// Has SubsConf?
		if(!systemTree->hasSubsystemConfiguration(message->source))
		{
			sendQuerySubsystemConfiguration(message->source, true);
			delete jtPacket;
			return true;
		}

		JausSubsystem subs = systemTree->getSubsystem(message->source);
		if(!subs)
		{
			// TODO: Throw Exception. Log Error.
			delete jtPacket;
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
					delete jtPacket;
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

		delete jtPacket;
		return true;
	} // End !MySubs

	// Has Node?
	if(!systemTree->hasNode(message->source))
	{
		// Add Node
		systemTree->addNode(message->source, NULL);

		// Query NodeID
		// Setup Query Address
		JausAddress address = jausAddressCreate();
		if(!address)
		{
			// TODO: Throw Exception. Log Error.
			delete jtPacket;
			return false;
		}
		address->subsystem = message->source->subsystem;
		address->node = message->source->node;
		address->component = JAUS_NODE_MANAGER;
		address->instance = 1;

		// Query Node ID
		sendQueryNodeIdentification(address);
		jausAddressDestroy(address);
		delete jtPacket;
		return true;
	}

	// Update Node Timestamp
	systemTree->updateNodeTimestamp(message->source);

	// Has NodeId?
	if(!systemTree->hasNodeIdentification(message->source))
	{
		// Query NodeID
		// Setup Query Address
		JausAddress address = jausAddressCreate();
		if(!address)
		{
			// TODO: Throw Exception. Log Error.
			delete jtPacket;
			return false;
		}
		address->subsystem = message->source->subsystem;
		address->node = message->source->node;
		address->component = JAUS_NODE_MANAGER;
		address->instance = 1;

		// Query Node ID
		sendQueryNodeIdentification(address);
		jausAddressDestroy(address);
		delete jtPacket;
		return true;
	}

	// My Node?
	if(message->source->node != this->cmpt->address->node)
	{
		// Has NodeConf?
		if(!systemTree->hasNodeConfiguration(message->source))
		{
			// Query NodeConf
			JausAddress address = jausAddressCreate();
			if(!address)
			{
				// TODO: Throw Exception. Log Error.
				delete jtPacket;
				return false;
			}
			address->subsystem = message->source->subsystem;
			address->node = message->source->node;
			address->component = JAUS_NODE_MANAGER;
			address->instance = 1;

			sendQueryNodeConfiguration(address, true);
			jausAddressDestroy(address);
			delete jtPacket;
			return true;
		}
		else
		{
			JausNode node = systemTree->getNode(message->source);
			
			// Check for component ID and Services
			for(int i = 0; i < node->components->elementCount; i++)
			{
				JausComponent cmpt = (JausComponent) node->components->elementData[i];
				if(!jausComponentHasIdentification(cmpt))
				{
					sendQueryComponentIdentification(cmpt->address);
				}

				if(!jausComponentHasServices(cmpt))
				{
					sendQueryComponentServices(cmpt->address);
				}
			}

			delete jtPacket;
			return false;
		} 
	}// End !MyNode

	// Has Component?
	if(!systemTree->hasComponent(message->source))
	{
		// Add Component
		systemTree->addComponent(message->source, NULL);
	}
	else
	{
		// Update Component Timestamp
		systemTree->updateComponentTimestamp(message->source);
	}

	if(!systemTree->hasComponentIdentification(message->source))
	{
		sendQueryComponentIdentification(message->source);
	}

	if(!systemTree->hasComponentServices(message->source))
	{
		sendQueryComponentServices(message->source);
	}

	delete jtPacket;
	return true;
}

bool NodeManagerComponent::processCreateEvent(JausTransportPacket *jtPacket)
{
	// Only support Configuration Changed events
	CreateEventMessage createEvent = NULL;
	QueryConfigurationMessage queryConf = NULL;
	ConfirmEventMessage confirmEvent = NULL;
	JausMessage txMessage = NULL;
	HASH_MAP <int, JausAddress>::iterator iterator;
	
	confirmEvent = confirmEventMessageCreate();
	if(!confirmEvent)
	{
		//TODO: Log Error. Throw Exception
		return false;
	}
	jausAddressCopy(confirmEvent->destination, jtPacket->getJausMessage()->source);
	jausAddressCopy(confirmEvent->source, cmpt->address);
	
	createEvent = createEventMessageFromJausMessage(jtPacket->getJausMessage());
	if(!createEvent)
	{
		//TODO: Log Error. Throw Exception
		confirmEvent->responseCode = INVALID_EVENT_RESPONSE;
		txMessage = confirmEventMessageToJausMessage(confirmEvent);
		if(txMessage)
		{
			this->commMngr->routeJausMessage(new JausTransportPacket(txMessage, this, NULL));
		}
		confirmEventMessageDestroy(confirmEvent);
		return false;
	}

	if(createEvent->messageCode != JAUS_QUERY_CONFIGURATION)
	{
		// Currently the NM only supports configuration changed events
		confirmEvent->responseCode = MESSAGE_UNSUPPORTED_RESPONSE;
		txMessage = confirmEventMessageToJausMessage(confirmEvent);
		if(txMessage)
		{
			this->commMngr->routeJausMessage(new JausTransportPacket(txMessage, this, NULL));
		}
		confirmEventMessageDestroy(confirmEvent);
		return false;
	}
	confirmEvent->messageCode = JAUS_REPORT_CONFIGURATION;

	queryConf = queryConfigurationMessageFromJausMessage(createEvent->queryMessage);
	if(!queryConf)
	{
		// ERROR: Cannot unpack query message
		// TODO: Log Error. Throw Exception
		confirmEvent->responseCode = INVALID_EVENT_RESPONSE;
		txMessage = confirmEventMessageToJausMessage(confirmEvent);
		if(txMessage)
		{
			this->commMngr->routeJausMessage(new JausTransportPacket(txMessage, this, NULL));
		}
		confirmEventMessageDestroy(confirmEvent);
		return false;
	}
	
	switch(queryConf->queryField)
	{
		case JAUS_SUBSYSTEM_CONFIGURATION:
			for(iterator = subsystemChangeList.begin(); iterator != subsystemChangeList.end(); iterator++)
			{
				if(jausAddressEqual(createEvent->source, iterator->second))
				{
					// Event already created
					confirmEvent->responseCode = SUCCESSFUL_RESPONSE;
					confirmEvent->eventId = iterator->first;
					break;
				}
			}

			confirmEvent->eventId = getNextEventId();
			if(confirmEvent->eventId >= 0)
			{
				eventId[confirmEvent->eventId] = true;
				subsystemChangeList[confirmEvent->eventId] = createEvent->source;
				confirmEvent->responseCode = SUCCESSFUL_RESPONSE;
			}
			else
			{
				confirmEvent->responseCode = CONNECTION_REFUSED_RESPONSE;
				confirmEvent->eventId = 0;
			}
			break;
		
		case JAUS_NODE_CONFIGURATION:
			for(iterator = nodeChangeList.begin(); iterator != nodeChangeList.end(); iterator++)
			{
				if(jausAddressEqual(createEvent->source, iterator->second))
				{
					// Event already created
					confirmEvent->responseCode = SUCCESSFUL_RESPONSE;
					confirmEvent->eventId = iterator->first;
					break;
				}
			}

			confirmEvent->eventId = getNextEventId();
			if(confirmEvent->eventId >= 0)
			{
				eventId[confirmEvent->eventId] = true;
				nodeChangeList[confirmEvent->eventId] = createEvent->source;
				confirmEvent->responseCode = SUCCESSFUL_RESPONSE;
			}
			else
			{
				confirmEvent->responseCode = CONNECTION_REFUSED_RESPONSE;
				confirmEvent->eventId = 0;
			}
			break;

		default:
			// TODO: Log Error. Throw Exception.
			// Unknown Query Type
			confirmEvent->responseCode = INVALID_EVENT_RESPONSE;
			txMessage = confirmEventMessageToJausMessage(confirmEvent);
			if(txMessage)
			{
				this->commMngr->routeJausMessage(new JausTransportPacket(txMessage, this, NULL));
			}
			confirmEventMessageDestroy(confirmEvent);
			return false;
	}

	// Send response
	txMessage = confirmEventMessageToJausMessage(confirmEvent);
	if(txMessage)
	{
		this->commMngr->routeJausMessage(new JausTransportPacket(txMessage, this, NULL));
	}

	queryConfigurationMessageDestroy(queryConf);
	createEventMessageDestroy(createEvent);
	return true;
}

bool NodeManagerComponent::processCancelEvent(JausTransportPacket *jtPacket)
{
	CancelEventMessage cancelEvent = NULL;

	cancelEvent = cancelEventMessageFromJausMessage(jtPacket->getJausMessage());
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

bool NodeManagerComponent::processCreateServiceConnection(JausTransportPacket *jtPacket)
{
	// Not implemented right now
	return true;
}

bool NodeManagerComponent::processActivateServiceConnection(JausTransportPacket *jtPacket)
{
	// Not Implemented right now
	return true;
}

bool NodeManagerComponent::processSuspendServiceConnection(JausTransportPacket *jtPacket)
{
	// Not Implemented right now
	return true;
}

bool NodeManagerComponent::processTerminateServiceConnection(JausTransportPacket *jtPacket)
{
	// Not Implemented right now
	return true;
}

bool NodeManagerComponent::processRequestComponentControl(JausTransportPacket *jtPacket)
{
	RequestComponentControlMessage requestComponentControl = NULL;
	RejectComponentControlMessage rejectComponentControl = NULL;
	ConfirmComponentControlMessage confirmComponentControl = NULL;
	JausMessage txMessage = NULL;

	JausMessage message = jtPacket->getJausMessage();

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
				this->commMngr->routeJausMessage(new JausTransportPacket(txMessage, this, NULL));
			}
			
			// Accept control of new component
			confirmComponentControl = confirmComponentControlMessageCreate();
			jausAddressCopy(confirmComponentControl->source, cmpt->address);
			jausAddressCopy(confirmComponentControl->destination, message->source);
			confirmComponentControl->responseCode = JAUS_RESPONSE_CODE_CONTROL_ACCEPTED;
			txMessage = confirmComponentControlMessageToJausMessage(confirmComponentControl); 
			if(txMessage)
			{
				this->commMngr->routeJausMessage(new JausTransportPacket(txMessage, this, NULL));
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
					this->commMngr->routeJausMessage(new JausTransportPacket(txMessage, this, NULL));
				}

				rejectComponentControlMessageDestroy(rejectComponentControl);
			}
			else
			{
				// Reaccept control of new component
				confirmComponentControl = confirmComponentControlMessageCreate();
				jausAddressCopy(confirmComponentControl->source, cmpt->address);
				jausAddressCopy(confirmComponentControl->destination, message->source);
				confirmComponentControl->responseCode = JAUS_RESPONSE_CODE_CONTROL_ACCEPTED;
				txMessage = confirmComponentControlMessageToJausMessage(confirmComponentControl); 
				if(txMessage)
				{
					this->commMngr->routeJausMessage(new JausTransportPacket(txMessage, this, NULL));
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
		confirmComponentControl->responseCode = JAUS_RESPONSE_CODE_CONTROL_ACCEPTED;
		txMessage = confirmComponentControlMessageToJausMessage(confirmComponentControl); 
		if(txMessage)
		{
			this->commMngr->routeJausMessage(new JausTransportPacket(txMessage, this, NULL));
		}

		jausAddressCopy(cmpt->controller.address, message->source);
		cmpt->controller.authority = requestComponentControl->authorityCode;
		cmpt->controller.active = JAUS_TRUE;

		confirmComponentControlMessageDestroy(confirmComponentControl);						
	}

	requestComponentControlMessageDestroy(requestComponentControl);
	return true;
}

bool NodeManagerComponent::processQueryComponentAuthority(JausTransportPacket *jtPacket)
{
	ReportComponentAuthorityMessage report = NULL;
	JausMessage txMessage = NULL;
	JausMessage message = jtPacket->getJausMessage();

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
		this->commMngr->routeJausMessage(new JausTransportPacket(txMessage, this, NULL));
	}

	reportComponentAuthorityMessageDestroy(report);
	return true;
}

bool NodeManagerComponent::processQueryComponentStatus(JausTransportPacket *jtPacket)
{
	ReportComponentStatusMessage reportComponentStatus = NULL;
	JausMessage txMessage = NULL;
	JausMessage message = jtPacket->getJausMessage();

	reportComponentStatus = reportComponentStatusMessageCreate();
	jausAddressCopy(reportComponentStatus->source, cmpt->address);
	jausAddressCopy(reportComponentStatus->destination, message->source);
	reportComponentStatus->primaryStatusCode = cmpt->state;
	
	txMessage = reportComponentStatusMessageToJausMessage(reportComponentStatus);	
	if(txMessage)
	{
		this->commMngr->routeJausMessage(new JausTransportPacket(txMessage, this, NULL));
	}

	reportComponentStatusMessageDestroy(reportComponentStatus);
	return true;
}

bool NodeManagerComponent::processQueryHeartbeatPulse(JausTransportPacket *jtPacket)
{
	JausMessage message = jtPacket->getJausMessage();
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
		this->commMngr->routeJausMessage(new JausTransportPacket(txMessage, this, NULL));
	}
	return true;
}

bool NodeManagerComponent::processQueryConfiguration(JausTransportPacket *jtPacket)
{
	QueryConfigurationMessage queryConf = NULL;
	ReportConfigurationMessage reportCong = NULL;
	JausMessage txMessage = NULL;

	queryConf = queryConfigurationMessageFromJausMessage(jtPacket->getJausMessage());
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
			// This hack will fix bad implementation from other systems
			if(this->commMngr->getMessageRouter()->subsystemCommunicationEnabled() &&
				//systemTable->)
			{
				queryConf->destination->component = JAUS_COMMUNICATOR;
				queryConf->destination->instance = JAUS_MINIMUM_INSTANCE;
				txMessage = queryConfigurationMessageToJausMessage(queryConf);
				if(txMessage)
				{
					this->commMngr->routeJausMessage(new JausTransportPacket(txMessage, this, NULL));	
				}
			}
			else
			{
				// This NM is not connected to the subsystem network, 
				// therefore no one should be asking us for subsystem configuration
				// TODO: Log Error. Throw Exception.
			}
			break;

		case JAUS_NODE_CONFIGURATION:
			break;

		case JAUS_COMPONENT_CONFIGURATION:
			break;
		
		case JAUS_INSTANCE_CONFIGURATION:
		case JAUS_SYSTEM_CONFIGURATION:
			// TODO: Log Warning.
			// Unhandled/Unknown requests
			break;

		default:
			// TODO: Log Error. Throw Exception.
			// Unknown query type
			break;
	}

	queryConfigurationMessageDestroy(queryConf);
	return true;
}

bool NodeManagerComponent::processQueryIdentification(JausTransportPacket *jtPacket)
{
	return true;
}

bool NodeManagerComponent::processQueryServices(JausTransportPacket *jtPacket)
{
	return true;
}

bool NodeManagerComponent::processConfirmEvent(JausTransportPacket *jtPacket)
{
	return true;
}

void NodeManagerComponent::sendNodeChangedEvents()
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
		this->commMngr->routeJausMessage(new JausTransportPacket(jausMessageDuplicate(txMessage), this, NULL));
	}
	
	jausMessageDestroy(txMessage);
	reportConfigurationMessageDestroy(reportConf);
}

void NodeManagerComponent::sendSubsystemChangedEvents()
{
	ReportConfigurationMessage reportConf = NULL;
	JausMessage txMessage = NULL;	
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

	txMessage = reportConfigurationMessageToJausMessage(reportConf);
	jausAddressCopy(txMessage->source, cmpt->address);

	// TODO: check subsystemChangeList for dead addresses
	for(iterator = subsystemChangeList.begin(); iterator != subsystemChangeList.end(); iterator++)
	{
		jausAddressCopy(txMessage->destination, iterator->second);
		this->commMngr->routeJausMessage(new JausTransportPacket(jausMessageDuplicate(txMessage), this, NULL));
	}

	jausMessageDestroy(txMessage);
	reportConfigurationMessageDestroy(reportConf);
}

void NodeManagerComponent::generateHeartbeats()
{
	static double nextSendTime = getTimeSeconds();
	ReportHeartbeatPulseMessage heartbeat;
	JausMessage nodeHeartbeat;
	JausMessage cmptHeartbeat;
	
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

		nodeHeartbeat = reportHeartbeatPulseMessageToJausMessage(heartbeat);
		if(!nodeHeartbeat)
		{
			// Error constructing message
			// TODO: Log Error.
			reportHeartbeatPulseMessageDestroy(heartbeat);
			return;
		}

		cmptHeartbeat = reportHeartbeatPulseMessageToJausMessage(heartbeat);
		if(!cmptHeartbeat)
		{
			// Error constructing message
			// TODO: Log Error.
			jausMessageDestroy(nodeHeartbeat);
			reportHeartbeatPulseMessageDestroy(heartbeat);
			return;
		}

		// Send Heartbeat to other node managers on this subsystem
		nodeHeartbeat->destination->subsystem = cmpt->address->subsystem;
		nodeHeartbeat->destination->node = JAUS_BROADCAST_NODE_ID;
		nodeHeartbeat->destination->component = JAUS_NODE_MANAGER_COMPONENT;
		nodeHeartbeat->destination->instance = 1;
		this->commMngr->routeJausMessage(new JausTransportPacket(nodeHeartbeat, this, NULL));

		// Send Heartbeat to components on this node
		cmptHeartbeat->destination->subsystem = cmpt->address->subsystem;
		cmptHeartbeat->destination->node = cmpt->address->node;
		cmptHeartbeat->destination->component = JAUS_BROADCAST_COMPONENT_ID;
		cmptHeartbeat->destination->instance = JAUS_BROADCAST_INSTANCE_ID;
		this->commMngr->routeJausMessage(new JausTransportPacket(cmptHeartbeat, this, NULL));

		nextSendTime = getTimeSeconds() + 1.0;
		reportHeartbeatPulseMessageDestroy(heartbeat);
	}
}

bool NodeManagerComponent::sendQueryNodeIdentification(JausAddress address)
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
		this->commMngr->routeJausMessage(new JausTransportPacket(txMessage, this, NULL));
		queryIdentificationMessageDestroy(queryId);
		return true;
	}
	return false;
}

bool NodeManagerComponent::sendQuerySubsystemIdentification(JausAddress address)
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
		this->commMngr->routeJausMessage(new JausTransportPacket(txMessage, this, NULL));
		queryIdentificationMessageDestroy(queryId);
		return true;
	}
	return false;
}

bool NodeManagerComponent::sendQueryComponentIdentification(JausAddress address)
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
		this->commMngr->routeJausMessage(new JausTransportPacket(txMessage, this, NULL));
		queryIdentificationMessageDestroy(queryId);
		return true;
	}
	return false;
}

bool NodeManagerComponent::sendQueryComponentServices(JausAddress address)
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
		this->commMngr->routeJausMessage(new JausTransportPacket(txMessage, this, NULL));
		queryServicesMessageDestroy(query);
		return true;
	}
	return false;
}
bool NodeManagerComponent::sendQueryNodeConfiguration(JausAddress address, bool createEvent)
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
		this->commMngr->routeJausMessage(new JausTransportPacket(txMessage, this, NULL));
		
		if(createEvent)
		{
			createEventMsg = createEventMessageCreate();
			if(!createEventMsg)
			{
				queryConfigurationMessageDestroy(query);
				return false;
			}
			
			createEventMsg->messageCode = query->commandCode;
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
			this->commMngr->routeJausMessage(new JausTransportPacket(txMessage, this, NULL));
		}

		queryConfigurationMessageDestroy(query);
		return true;
	}
	return false;
}

bool NodeManagerComponent::sendQuerySubsystemConfiguration(JausAddress address, bool createEvent)
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
		this->commMngr->routeJausMessage(new JausTransportPacket(txMessage, this, NULL));
		jausMessageDestroy(txMessage); // Send Query Node Configuration

		if(createEvent)
		{
			createEventMsg = createEventMessageCreate();
			if(!createEventMsg)
			{
				queryConfigurationMessageDestroy(query);
				return false;
			}
			
			createEventMsg->messageCode = query->commandCode;
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
			this->commMngr->routeJausMessage(new JausTransportPacket(txMessage, this, NULL));
		}

		queryConfigurationMessageDestroy(query);
		return true;
	}
	return false;
}

int NodeManagerComponent::getNextEventId()
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


