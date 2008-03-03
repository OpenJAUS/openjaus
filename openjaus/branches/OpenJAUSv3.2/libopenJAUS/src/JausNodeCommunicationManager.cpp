#include "JausNodeCommunicationManager.h"
#include "JausUdpInterface.h"

JausNodeCommunicationManager::JausNodeCommunicationManager(FileLoader *configData, MessageRouter *msgRouter, SystemTree *systemTree, EventHandler *handler)
{
	this->handler = handler;
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
	if(configData->GetConfigDataBool("Node_Communications", "JAUS_UDP"))
	{
		printf("Opening Node Interface:\t\t");
		JausUdpInterface *udpInterface = new JausUdpInterface(configData, handler, this);
		printf("[DONE: %s]\n", udpInterface->toString().c_str());
		this->interfaces.push_back(udpInterface);
	}

	if( configData->GetConfigDataBool("Node_Communications", "Enabled") &&
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
	if(!this->enabled)
	{
		// This Communication Manager is turned off
		// Destroy this message
		jausMessageDestroy(message);
		return false;
	}

	// This conforms to the NodeCommMngr Routing Table's MsgRouter Source Table v2.0
	if(!message)
	{
		// Error: Invalid message
		// TODO: Log Error. Throw Exception
		return false;
	}

	//char buf[80] = {0};
	//jausAddressToString(message->source, buf);
	//printf("NCommMngr: Process %s from %s", jausMessageCommandCodeString(message), buf);
	//jausAddressToString(message->destination, buf);
	//printf(" to %s\n", buf);

	if(message->source->subsystem != mySubsystemId)
	{
		if( message->destination->subsystem == JAUS_BROADCAST_SUBSYSTEM_ID ||
			message->destination->subsystem == mySubsystemId)
		{
			if(message->destination->node == JAUS_BROADCAST_NODE_ID)
			{
				// Send to all other nodes on this subs
				return sendToAllInterfaces(message);
			}
			else if(message->destination->node != myNodeId)
			{
				// Route to Node X
				return sendToNodeX(message);
			}
			else
			{
				// ERROR: Message received from MsgRouter that is not from this subs is for this node!
				// TODO: Log Error. Throw Exception.
				jausMessageDestroy(message);
				return false;
			}
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
			if( message->destination->subsystem != mySubsystemId &&
				message->destination->subsystem != JAUS_BROADCAST_SUBSYSTEM_ID)
			{
					return sendToSubsystemGateway(message);
			}
			else if(message->destination->subsystem == JAUS_BROADCAST_SUBSYSTEM_ID)
			{
				if(message->destination->node == JAUS_BROADCAST_SUBSYSTEM_ID)
				{
					// Send to all other nodes
					return sendToAllInterfaces(message);
				}
				else if(message->destination->node == myNodeId)
				{
					return sendToSubsystemGateway(message);
				}
				else //message->destination->node == X
				{
					// Route to node X
					sendToNodeX(jausMessageClone(message));

					// PREVENT DUPLICATION!
					// If Node X is not the Communicator Node or the Primary node, sendToSubsystemGateway
					JausAddress commAddress = systemTree->lookUpAddress(mySubsystemId, JAUS_ADDRESS_WILDCARD_OCTET, JAUS_COMMUNICATOR, JAUS_ADDRESS_WILDCARD_OCTET);
					if(commAddress && commAddress->node != message->destination->node && message->destination->node != JAUS_PRIMARY_NODE_MANAGER_NODE)
					{
						sendToSubsystemGateway(jausMessageClone(message));
					}
					
					jausMessageDestroy(message);
					return true;
				}
			}
			else //message->destination->subsystem == mySubsystemId
			{
				if(message->destination->node == myNodeId)
				{
					// ERROR: Msg recv'd which is for this node!
					// TODO: Log Error. Throw Exception.
					jausMessageDestroy(message);
					return false;
				}
				else if(message->destination->node == JAUS_BROADCAST_NODE_ID)
				{
					// Send to all other nodes
					return sendToAllInterfaces(message);
				}
				else 
				{
					// Route to Node X
					return sendToNodeX(message);
				}
			}
		}
	}
}

bool JausNodeCommunicationManager::receiveJausMessage(JausMessage message, JausTransportInterface *srcInf)
{
	if(!this->enabled)
	{
		// This Communication Manager is turned off
		// Destroy this message
		jausMessageDestroy(message);
		return false;
	}

	// This conforms to the NodeCommMngr Routing Table's MsgRouter Source Table v2.0
	if(!message)
	{
		// Error: Invalid message
		// TODO: Log Error. Throw Exception
		return false;
	}

	// Check for errors
	if(message->source->subsystem == mySubsystemId)
	{
		if(message->source->node == myNodeId)
		{
			// Error: Msg recv'd from this node through NodeInf, invalid!
			// TODO: Log Error. Throw Exception
			jausMessageDestroy(message);
			return false;
		}
		else
		{
			// Put Interface data on the map
			interfaceMap[message->source->node] = srcInf;

			if(message->destination->node != myNodeId && message->destination->node != JAUS_BROADCAST_NODE_ID)
			{
				// ERROR: Message not for this node recv'd from another node
				// TODO: Log Error. Throw Exception
				jausMessageDestroy(message);
				return false;
			}
			else
			{
				msgRouter->routeNodeSourceMessage(message);
				return true;
			}
		}
	}
	else //message->source->subsystem != mySubsystemId
	{
		if(	message->destination->subsystem == JAUS_BROADCAST_SUBSYSTEM_ID ||
			message->destination->subsystem == mySubsystemId)
		{
			if(message->destination->node == myNodeId)
			{
				// ERROR: Message not for this node recv'd from another node
				// TODO: Log Error. Throw Exception
				jausMessageDestroy(message);
				return false;
			}
			else
			{
				msgRouter->routeNodeSourceMessage(message);
				return true;
			}
		}
		else // message->destination->subsystem == X
		{
			// ERROR: Message not for this subsystem and not from this subsystem recv'd from another node
			// TODO: Log Error. Throw Exception
			jausMessageDestroy(message);
			return false;
		}
	}
}

bool JausNodeCommunicationManager::sendToSubsystemGateway(JausMessage message)
{
	if(!message)
	{
		// Error: Invalid message
		// TODO: Log Error. Throw Exception
		return false;
	}

	if(msgRouter->subsystemCommunicationEnabled())
	{
		// ERROR: This should have gone out to the SubsCommMngr
		// TODO: Log Error. Throw Exception.
		jausMessageDestroy(message);
		return false;
	}

	// Find the Communicator's Address
	JausAddress commAddress = systemTree->lookUpAddress(mySubsystemId, JAUS_ADDRESS_WILDCARD_OCTET, JAUS_COMMUNICATOR, JAUS_ADDRESS_WILDCARD_OCTET);
	if(commAddress)
	{
		// Send to the Communicator's Node
		JausTransportInterface *jtInf = interfaceMap[commAddress->node];
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
	else if(myNodeId != JAUS_PRIMARY_NODE_MANAGER_NODE)
	{
		// Send to the Primary Node Manager (note this is mainly for backwards compatibility)
		JausTransportInterface *jtInf = interfaceMap[commAddress->node];
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
	else
	{
		// No known communicator
		// This is the Primary Node
		// And I don't have an active SubsCommMngr
		jausMessageDestroy(message);
		return false;
	}
}

bool JausNodeCommunicationManager::sendToNodeX(JausMessage message)
{
	if(!message)
	{
		// Error: Invalid message
		// TODO: Log Error. Throw Exception
		return false;
	}

	JausTransportInterface *jtInf = interfaceMap[message->destination->node];
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

bool JausNodeCommunicationManager::sendToAllInterfaces(JausMessage message)
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
