#include "JausComponentCommunicationManager.h"
#include "NodeManagerComponent.h"
#include "CommunicatorComponent.h"
#include "JausUdpInterface.h"
#include "OjApiComponentInterface.h"
#include "OjUdpComponentInterface.h"

JausComponentCommunicationManager::JausComponentCommunicationManager(FileLoader *configData, MessageRouter *msgRouter, SystemTree *systemTree, EventHandler *handler)
{
	this->enabled = true;
	this->msgRouter = msgRouter;
	this->systemTree = systemTree;
	this->configData = configData;
	this->handler = handler;
	this->interfaces.empty();
	this->interfaceMap.empty();

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
		printf("Opening Component Interface:\t");
		JausUdpInterface *udpInterface = new JausUdpInterface(configData, this->handler, this);
		printf("[DONE: %s]\n", udpInterface->toString().c_str());
		this->interfaces.push_back(udpInterface);
	}

	if(configData->GetConfigDataBool("Component_Communications", "OpenJAUS_API"))
	{
		printf("Opening Component Interface:\t");
		OjApiComponentInterface *apiCmptInf = new OjApiComponentInterface(configData, this->handler, this);
		printf("[DONE: %s]\n", apiCmptInf->toString().c_str());
		this->interfaces.push_back(apiCmptInf);
	}

	if(configData->GetConfigDataBool("Component_Communications", "OpenJAUS_UDP"))
	{
		printf("Opening Component Interface:\t");
		OjUdpComponentInterface *udpCmptInf = new OjUdpComponentInterface(configData, this->handler, this);
		printf("[DONE: %s]\n", udpCmptInf->toString().c_str());
		this->interfaces.push_back(udpCmptInf);
	}

	// Start Local Components
	this->nodeManagerCmpt = new NodeManagerComponent(this->configData, this->handler, this);
	this->interfaces.push_back(nodeManagerCmpt);
	this->communicatorCmpt = new CommunicatorComponent(this->configData, this->handler, this);
	this->interfaces.push_back(communicatorCmpt);

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
	if( message->destination->subsystem != mySubsystemId &&
		message->destination->subsystem != JAUS_BROADCAST_SUBSYSTEM_ID )
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

	//char buf[80] = {0};
	//jausAddressToString(message->source, buf);
	//printf("CmptMngr: Process %s from %s", jausMessageCommandCodeString(message), buf);
	//jausAddressToString(message->destination, buf);
	//printf(" to %s\n", buf);

	// Add this source to our interface table
	interfaceMap[jausAddressHash(message->source)] = srcInf;

	if(message->destination->subsystem == mySubsystemId)
	{
		if(message->destination->node == myNodeId)
		{
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
			// Send to MsgRouter
			msgRouter->routeComponentSourceMessage(jausMessageClone(message));
			
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
		msgRouter->routeComponentSourceMessage(jausMessageClone(message));

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
	HASH_MAP<int, JausTransportInterface *>::iterator iter;

	if(!message)
	{
		// Error: Invalid message
		// TODO: Log Error. Throw Exception
		return false;
	}

	if(	message->destination->subsystem == JAUS_BROADCAST_SUBSYSTEM_ID ||
		message->destination->node == JAUS_BROADCAST_NODE_ID)
	{
		// This is ensure that the jausAddressHash works incase either the Subs or Node IDs are BROADCAST
		// Assume if we have gotten here this message is actually for our Subs & Node
		JausAddress lookupAddress = jausAddressClone(message->destination);
		lookupAddress->subsystem = mySubsystemId;
		lookupAddress->node = myNodeId;

		iter = interfaceMap.find(jausAddressHash(lookupAddress));
		jausAddressDestroy(lookupAddress);
	}
	else
	{
		iter = interfaceMap.find(jausAddressHash(message->destination));
	}
	
	if(iter != interfaceMap.end())
	{
		iter->second->queueJausMessage(message);
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
	HASH_MAP<int, JausTransportInterface *>::iterator iter;

	if(!message)
	{
		// Error: Invalid message
		// TODO: Log Error. Throw Exception
		return false;
	}

	for(iter = interfaceMap.begin(); iter != interfaceMap.end(); iter++)
	{
		if(iter->second != NULL)
		{
			iter->second->queueJausMessage(jausMessageClone(message));
		}
	}
	
	jausMessageDestroy(message);
	return true;
}

