#include "JausSubsystemCommunicationManager.h"
#include "JausUdpInterface.h"

JausSubsystemCommunicationManager::JausSubsystemCommunicationManager(FileLoader *configData, MessageRouter *msgRouter, SystemTree *systemTree)
{
	this->systemTree = systemTree;
	this->msgRouter = msgRouter;
	this->configData = configData;

	// NOTE: These two values should exist in the properties file and should be checked 
	// in the NodeManager class prior to constructing this object
	mySubsystemId = configData->GetConfigDataInt("JAUS", "SubsystemId");
	if(mySubsystemId < JAUS_MINIMUM_SUBSYSTEM_ID || mySubsystemId > JAUS_MAXIMUM_SUBSYSTEM_ID)
	{
		// Invalid ID
		// TODO: Throw an exception? Log an error.
		mySubsystemId = JAUS_INVALID_SUBSYSTEM_ID;
		return;
	}

	myNodeId = configData->GetConfigDataInt("JAUS", "NodeId");
	if(myNodeId < JAUS_MINIMUM_NODE_ID || myNodeId > JAUS_MAXIMUM_NODE_ID)
	{
		// Invalid ID
		// TODO: Throw an exception? Log an error.
		myNodeId= JAUS_INVALID_NODE_ID;
		return;
	}

	// Start subsystem interface(s)
	if(configData->GetConfigDataBool("Subsystem_Communications", "JAUS_UDP"))
	{
		printf("Opening Subsystem Interface:\t");
		JausUdpInterface *udpInterface = new JausUdpInterface(configData, this);
		printf("[DONE: %s]\n", udpInterface->toString().c_str());
		this->interfaces.push_back(udpInterface);
	}

	if( configData->GetConfigDataBool("Subsystem_Communications", "Enabled") &&
		this->interfaces.size() > 0)
	{
		this->enabled = true;
	}

}

JausSubsystemCommunicationManager::~JausSubsystemCommunicationManager(void)
{
	std::vector<JausTransportInterface *>::iterator iterator;
	for(iterator = interfaces.begin(); iterator != interfaces.end(); iterator++) 
	{
		delete *iterator;
	}
}

bool JausSubsystemCommunicationManager::sendJausMessage(JausMessage message)
{
	if(!this->enabled)
	{
		// This Communication Manager is turned off
		// Destroy this message
		jausMessageDestroy(message);
		return false;
	}

	// This conforms to the SubsCommMngr MsgRouter Source Routing Table v2.0
	if(!message)
	{
		// Error: Invalid message
		// TODO: Log Error. Throw Exception
		return false;
	}
	
	// Check for Errors
	if(message->source->subsystem != mySubsystemId)
	{
		// ERROR: Message from another Subs coming in from MsgRouter
		// TODO: Log Error. Throw Exception.
		jausMessageDestroy(message);
		return false;
	}

	if(message->destination->subsystem == mySubsystemId)
	{
		// ERROR: Message for this Subs coming in from MsgRouter
		// TODO: Log Error. Throw Exception.
		jausMessageDestroy(message);
		return false;
	}

	if(message->destination->subsystem == JAUS_BROADCAST_SUBSYSTEM_ID)
	{
		return sendToAllInterfaces(message);
	}
	else
	{
		return sendToSubsystemX(message);
	}
}

bool JausSubsystemCommunicationManager::receiveJausMessage(JausMessage message, JausTransportInterface *srcInf)
{
	if(!this->enabled)
	{
		// This Communication Manager is turned off
		// Destroy this message
		jausMessageDestroy(message);
		return false;
	}

	// This conforms to the SubsCommMngr MsgRouter Source Routing Table v2.0
	if(!message)
	{
		// Error: Invalid message
		// TODO: Log Error. Throw Exception
		return false;
	}

	if(!srcInf)
	{
		// Error: Invalid interface
		// TODO: Log Error. Throw Exception.
		jausMessageDestroy(message);
		return false;
	}

	if(message->source->subsystem == mySubsystemId)
	{
		// Error: Cannot receive messages for myself through a subsInterface!
		// TODO: Log Error. Throw Exception.
		jausMessageDestroy(message);
		return false;
	}

	// Ok, this is a valid source. Add/Update its interface on the map
	interfaceMap[message->source->subsystem] = srcInf;

	if(	message->destination->subsystem == mySubsystemId ||
		message->destination->subsystem == JAUS_BROADCAST_SUBSYSTEM_ID)
	{
		msgRouter->routeSubsystemSourceMessage(message);
		return true;
	}
	else
	{
		// Error: Somehow I received a message intended for another subsystem
		// TODO: Log Error. Throw Exception.
		jausMessageDestroy(message);
		return false;
	}
}

bool JausSubsystemCommunicationManager::sendToSubsystemX(JausMessage message)
{
	if(!message)
	{
		// Error: Invalid message
		// TODO: Log Error. Throw Exception
		return false;
	}

	// Route to subsystem X
	JausTransportInterface *jtInf = interfaceMap[message->destination->subsystem];
	if(jtInf)
	{
		jtInf->queueJausMessage(message);
		return true;
	}
	else
	{
		// I don't know how to send to Subsystem X
		jausMessageDestroy(message);
		return false;
	}
}

bool JausSubsystemCommunicationManager::sendToAllInterfaces(JausMessage message)
{
	std::vector <JausTransportInterface *>::iterator iter;

	if(!message)
	{
		// Error: Invalid message
		// TODO: Log Error. Throw Exception
		return false;
	}

	for(iter = interfaces.begin(); iter != interfaces.end(); iter++)
	{
		(*iter)->queueJausMessage(jausMessageClone(message));
	}
	jausMessageDestroy(message);
	return true;
}
