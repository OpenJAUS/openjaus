#include "JausComponentCommunicationManager.h"
#include "NodeManagerComponent.h"
#include "CommunicatorComponent.h"
#include "JausUdpInterface.h"
#include "OjApiComponentInterface.h"
#include "OjUdpComponentInterface.h"

JausComponentCommunicationManager::JausComponentCommunicationManager(FileLoader *configData, MessageRouter *msgRouter, SystemTree *systemTree)
{
	this->msgRouter = msgRouter;
	this->systemTree = systemTree;
	this->configData = configData;
	this->nodeManagerCmpt = new NodeManagerComponent(this->configData, this);
	this->communicatorCmpt = new CommunicatorComponent(this->configData, this);
	this->enabled = true;

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

	// Start component interface(s)
	if(configData->GetConfigDataBool("Component_Communications", "JAUS_UDP"))
	{
		JausUdpInterface *udpInterface = new JausUdpInterface(configData, this);
		this->interfaces.push_back(udpInterface);
	}

	if(configData->GetConfigDataBool("Component_Communications", "OpenJAUS_API"))
	{
		OjApiComponentInterface *apiCmptInf = new OjApiComponentInterface(configData, this);
		this->interfaces.push_back(apiCmptInf);
	}

	if(configData->GetConfigDataBool("Component_Communications", "OpenJAUS_UDP"))
	{
		OjUdpComponentInterface *udpCmptInf = new OjUdpComponentInterface(configData, this);
		this->interfaces.push_back(udpCmptInf);
	}
}

JausComponentCommunicationManager::~JausComponentCommunicationManager(void)
{
	delete this->nodeManagerCmpt;
	delete this->communicatorCmpt;
}

bool JausComponentCommunicationManager::sendJausMessage(JausMessage message)
{
	// This conforms to the CmptCommMngr MsgRouter Source Routing Table v2.0
	if(!message)
	{
		// Error: Invalid message
		// TODO: Log Error. Throw Exception
		return false;
	}
	
	// Check for Errors
	if( message->source->subsystem != mySubsystemId &&
		message->source->subsystem != JAUS_BROADCAST_SUBSYSTEM_ID )
	{
		// ERROR: Message not for this subsystem has been routed from the MsgRouter
		// TODO: Log Error. Throw Exception.
		jausMessageDestroy(message);
		return false;
	}

	if(message->source->subsystem == mySubsystemId && message->source->node == myNodeId)
	{
		// ERROR: Message from this node has been routed from the MsgRouter
		// TODO: Log Error. Throw Exception.
		jausMessageDestroy(message);
		return false;
	}

	if( message->destination->subsystem == mySubsystemId ||
		message->destination->subsystem == JAUS_BROADCAST_SUBSYSTEM_ID)
	{
		if( message->destination->component == JAUS_BROADCAST_COMPONENT_ID ||
			message->destination->instance == JAUS_BROADCAST_INSTANCE_ID)
		{
			return sendToAllInterfaces(message);
		}
		else
		{
			return sendToComponentX(message);
		}
	}
	else
	{
		// ERROR: Message not for components on this node received
		// TODO: Log Error. Throw Exception.
		jausMessageDestroy(message);
		return false;
	}
}

bool JausComponentCommunicationManager::receiveJausMessage(JausMessage message, JausTransportInterface *srcInf)
{
	// This conforms to the CmptCommMngr MsgRouter Source Routing Table v2.0
	if(!message)
	{
		// Error: Invalid message
		// TODO: Log Error. Throw Exception
		return false;
	}
	
	if(message->source->subsystem != mySubsystemId)
	{
		// ERROR: Received a message from a component that is not from my subsystem!
		// TODO: Log Error. Throw Exception.
		jausMessageDestroy(message);
		return false;
	}

	if(message->source->node != myNodeId)
	{
		// ERROR: Received a message from a component that is not from my subsystem!
		// TODO: Log Error. Throw Exception.
		jausMessageDestroy(message);
		return false;
	}

	if(message->destination->subsystem == mySubsystemId)
	{
		if(message->destination->node == myNodeId)
		{
			if(message->destination->component == JAUS_BROADCAST_COMPONENT_ID)
			{
				return sendToComponentX(message);
			}
			else
			{
				return sendToAllInterfaces(message);
			}
		}
		else
		{
			msgRouter->routeComponentSourceMessage(jausMessageDuplicate(message));
			if(message->destination->component == JAUS_BROADCAST_COMPONENT_ID)
			{
				return sendToAllInterfaces(message);
			}
			else
			{
				return sendToComponentX(message);
			}
		}
	}
	else if(message->destination->subsystem == JAUS_BROADCAST_SUBSYSTEM_ID)
	{
		msgRouter->routeComponentSourceMessage(jausMessageDuplicate(message));

		if(message->destination->component == JAUS_BROADCAST_COMPONENT_ID)
		{
			return sendToAllInterfaces(message);
		}
		else
		{
			return sendToComponentX(message);
		}
	}
	else
	{
		msgRouter->routeComponentSourceMessage(message);
	}

	return false;
}

NodeManagerComponent *JausComponentCommunicationManager::getNodeManagerComponent(void)
{
	return this->nodeManagerCmpt;
}

bool JausComponentCommunicationManager::sendToComponentX(JausMessage message)
{
	if(!message)
	{
		// Error: Invalid message
		// TODO: Log Error. Throw Exception
		return false;
	}

	JausTransportInterface *jtInf = interfaceMap[jausAddressHash(message->destination)];
	if(jtInf)
	{
		jtInf->queueJausMessage(message);
		return true;
	}
	else
	{
		// I don't know how to send something to that node
		jausMessageDestroy(message);
		return false;
	}
}

bool JausComponentCommunicationManager::sendToAllInterfaces(JausMessage message)
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
		(*iter)->queueJausMessage(jausMessageDuplicate(message));
	}
	
	jausMessageDestroy(message);
	return true;
}