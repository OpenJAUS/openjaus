#include "JausNodeCommunicationManager.h"
#include "JausUdpInterface.h"

JausNodeCommunicationManager::JausNodeCommunicationManager(FileLoader *configData, MessageRouter *msgRouter, SystemTree *systemTree)
{
	this->systemTree = systemTree;
	this->msgRouter = msgRouter;
	this->configData = configData;

	// NOTE: These two values should exist in the properties file and should be checked 
	// in the NodeManager class prior to constructing this object
	mySubsystemId = configData->GetConfigDataInt("JAUS", "Subsystem Id = ");
	if(mySubsystemId < JAUS_MINIMUM_SUBSYSTEM_ID || mySubsystemId > JAUS_MAXIMUM_SUBSYSTEM_ID)
	{
		// Invalid ID
		// TODO: Throw an exception? Log an error.
		mySubsystemId = JAUS_INVALID_SUBSYSTEM_ID;
		return;
	}

	myNodeId = configData->GetConfigDataInt("JAUS", "Node Id = ");
	if(myNodeId < JAUS_MINIMUM_NODE_ID || myNodeId > JAUS_MAXIMUM_NODE_ID)
	{
		// Invalid ID
		// TODO: Throw an exception? Log an error.
		myNodeId= JAUS_INVALID_NODE_ID;
		return;
	}

	// Start subsystem interface(s)
	if(configData->GetConfigDataBool("Node Communications", "UDP"))
	{
		JausUdpInterface *udpInterface = new JausUdpInterface(configData, this);
		this->interfaces.push_back(udpInterface);
	}

	if( configData->GetConfigDataBool("Node Communications", "Enabled") &&
		this->interfaces.size() > 0)
	{
		this->enabled = true;
	}
}


JausNodeCommunicationManager::~JausNodeCommunicationManager(void)
{
	std::vector<JausTransportInterface *>::iterator iterator;
	for(iterator = interfaces.begin(); iterator != interfaces.end(); iterator++) 
	{
		delete *iterator;
	}
}

bool JausNodeCommunicationManager::sendJausMessage(JausMessage message)
{
	// This conforms to the NodeCommMngr Routing Table's MsgRouter Source Table v2.0
	if(!message)
	{
		// Error: Invalid message
		// TODO: Log Error. Throw Exception
		return false;
	}
	
	if(message->source->subsystem != mySubsystemId)
	{
		if( message->destination->subsystem == JAUS_BROADCAST_SUBSYSTEM_ID ||
			message->destination->subsystem == mySubsystemId)
		{
			
		}
		else
		{
			// ERROR: Message received from MsgRouter that is not from this subs and not for this subs!
			// TODO: Log Error. Throw Exception.
			jausMessageDestroy(message);
			return false;
		}
	}
	else // message->source->subsystem == mySubsystemId
	{
		if(message->source->node != myNodeId)
		{
			// ERROR: Message received from MsgRouter that has address of another node on this system
			// TODO: Log Error. Throw Exception.
			jausMessageDestroy(message);
			return false;
		}
		else
		{
			// Special behavior in here to handle routing of messages to the communicator / primary nodemngr
		}
	}
}

bool JausNodeCommunicationManager::receiveJausMessage(JausMessage message, JausTransportInterface *srcInf)
{
	// TODO: Implement this method
	return false;
}

