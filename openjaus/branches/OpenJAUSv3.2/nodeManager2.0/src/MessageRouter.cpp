#include "MessageRouter.h"
#include "JausSubsystemCommunicationManager.h"
#include "JausNodeCommunicationManager.h"
#include "JausComponentCommunicationManager.h"

MessageRouter::MessageRouter(FileLoader *configData, JausSubsystemCommunicationManager *subsComms, JausNodeCommunicationManager *nodeComms, JausComponentCommunicationManager *cmptComms, SystemTree *sysTree)
{
	this->cmptComms = cmptComms;
	this->nodeComms = nodeComms;
	this->subsComms = subsComms;
	this->systemTree = sysTree;

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
}

MessageRouter::~MessageRouter(void){}

bool MessageRouter::routeSubsystemSourceMessage(JausMessage message)
{
	// This complies with the MessageRouter Subsystem Source Table v2.0
	if(!message)
	{
		// TODO: Log Error. Throw exception. Invalid message object.
		return false;
	}

	if(message->source->subsystem == mySubsystemId)
	{
		// ERROR: Message from this subsystem has entered the subsystemSource method
		// TODO: Log Error. Throw Exception!
		jausMessageDestroy(message);
		return false;
	}

	if( message->destination->subsystem != mySubsystemId && 
		message->destination->subsystem != JAUS_BROADCAST_SUBSYSTEM_ID)
	{
		// ERROR: Message not for this Subsystem has entered the subsystemSource method
		// TODO: Log Error. Throw Exception!
		jausMessageDestroy(message);
		return false;
	}

	if(message->destination->node == JAUS_BROADCAST_NODE_ID)
	{
		// Have to clone the JausMessage b/c I am sending it in two directions
		nodeComms->sendJausMessage(jausMessageDuplicate(message));
		cmptComms->sendJausMessage(message);
		return true;
	}
	else if(message->destination->node == myNodeId)
	{
		cmptComms->sendJausMessage(message);
		return true;
	}
	else
	{
		nodeComms->sendJausMessage(message);
		return true;
	}
	return true;
}

bool MessageRouter::routeNodeSourceMessage(JausMessage message)
{
	// This complies with the MessageRouter Node Source Table v2.0
	if(!message)
	{
		// TODO: Log Error. Throw exception. Invalid message object.
		return false;
	}

	if(message->source->subsystem == mySubsystemId)
	{
		if(message->source->node == myNodeId)
		{
			// ERROR: Message from a local component has entered through the nodeSource method
			// TODO: Log Error. Throw exception.
			jausMessageDestroy(message);
			return false;
		}
		else
		{
			if(message->destination->subsystem == JAUS_BROADCAST_SUBSYSTEM_ID)
			{
				if(	message->destination->node == JAUS_BROADCAST_NODE_ID ||
					message->destination->node == myNodeId)
				{
					// Send to both subsComms & cmptComms
					// Duplicate on one of them
					subsComms->sendJausMessage(jausMessageDuplicate(message));
					cmptComms->sendJausMessage(message);
					return true;
				}
				else
				{
					subsComms->sendJausMessage(message);
					return true;
				}
			}
			else if(message->destination->subsystem == mySubsystemId)
			{
				if(message->destination->node == myNodeId)
				{
					// ERROR: Message for another node on this subsystem recv'd through NodeComms
					// TODO: Log Error. Throw Exception.
					jausMessageDestroy(message);
					return false;
				}
				else
				{
					cmptComms->sendJausMessage(message);
					return true;
				}
			}
			else
			{
				subsComms->sendJausMessage(message);
				return true;
			}
		}
	}
	else //message->source->subsystem != mySubsystemId
	{
		if(	message->destination->subsystem == JAUS_BROADCAST_SUBSYSTEM_ID ||
			message->destination->subsystem == mySubsystemId)
		{
			if(	message->destination->node == JAUS_BROADCAST_NODE_ID ||
				message->destination->node == myNodeId)
			{
				cmptComms->sendJausMessage(message);
				return true;
			}
			else
			{
				// ERROR: Message not for this Node recv'd through nodeComms
				// TODO: Log Error. Throw Exception.
				jausMessageDestroy(message);
				return false;
			}
		}
		else
		{
			// ERROR: Message not for this Subs recv'd through nodeComms
			// TODO: Log Error. Throw Exception.
			jausMessageDestroy(message);
			return false;
		}
	}
}

bool MessageRouter::routeComponentSourceMessage(JausMessage message)
{
	// This complies with the MessageRouter Component Source Table v2.0
	if(!message)
	{
		// TODO: Log Error. Throw exception. Invalid message object.
		return false;
	}

	if(message->source->subsystem != mySubsystemId)
	{
		// ERROR: Message with a different source subsystem has come in through cmptComms
		// TODO: Log Error. Throw Exception
		jausMessageDestroy(message);
		return false;
	}

	if(message->source->node != myNodeId)
	{
		// ERROR: Message with a different source node has come in through cmptComms
		// TODO: Log Error. Throw Exception
		jausMessageDestroy(message);
		return false;
	}

	if(message->destination->subsystem == mySubsystemId)
	{
		if(message->destination->node == myNodeId)
		{
			// ERROR: Message for this node has escaped the cmptComms! Should not happen!
			// TODO: Log Error. Throw Exception
			jausMessageDestroy(message);
			return false;
		}
		else
		{
			nodeComms->sendJausMessage(message);
			return true;
		}
	}
	else
	{
		sendToCommunicator(message);
		return true;
	}
}

bool MessageRouter::sendToCommunicator(JausMessage message)
{
	// This conforms to the routing table in MsgRouter Routing Tables SendToCommunicator v2.0
	if(!message)
	{
		// TODO: Log Error. Throw exception. Invalid message object.
		return false;
	}

	if(message->source->subsystem != mySubsystemId)
	{
		// ERROR: Messages not from mySubs should not go through this method!
		// TODO: Log Error. Throw Exception.
		jausMessageDestroy(message);
		return false;
	}

	if(message->destination->subsystem == mySubsystemId)
	{
		// ERROR: Messages for mySubs should not go through this method!
		// TODO: Log Error. Throw Exception.
		jausMessageDestroy(message);
		return false;
	}

	if(this->subsComms->isEnabled())
	{
		if(message->destination->subsystem == JAUS_BROADCAST_SUBSYSTEM_ID)
		{
			if(message->destination->node == myNodeId)
			{
				subsComms->sendJausMessage(message);
				return true;
			}
			else
			{
				// Send to both subsComms & nodeComms
				// Duplicate once
				subsComms->sendJausMessage(jausMessageDuplicate(message));
				nodeComms->sendJausMessage(message);
				return true;
			}
		}
		else
		{
			subsComms->sendJausMessage(message);
			return true;
		}
	}
	else
	{
		JausAddress communicatorAddress = systemTree->lookUpAddress(mySubsystemId, JAUS_ADDRESS_WILDCARD_OCTET, JAUS_COMMUNICATOR, JAUS_ADDRESS_WILDCARD_OCTET);
		if(!jausAddressIsValid(communicatorAddress) || 
			communicatorAddress->node == myNodeId || 
			myNodeId == JAUS_PRIMARY_NODE_MANAGER_NODE)
		{
			// We can't route this subsystem level message to a communicator or primary node
			// Either there is no communicator, we're it and our subsInf is turned off
			// Just destroy this message
			// TODO: Throw Exception? Log Error/Warning?
			jausMessageDestroy(message);
			return false;
		}
		else
		{
			nodeComms->sendJausMessage(message);
			return true;
		}
	}
}

bool MessageRouter::subsystemCommunicationEnabled()
{
	return this->subsComms->isEnabled();
}

bool MessageRouter::nodeCommunicationEnabled()
{
	return this->nodeComms->isEnabled();
}

bool MessageRouter::componentCommunicationEnabled()
{
	return this->cmptComms->isEnabled();
}


