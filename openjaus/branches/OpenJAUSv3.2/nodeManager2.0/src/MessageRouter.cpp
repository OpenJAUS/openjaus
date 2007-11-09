#include "MessageRouter.h"
#include "JausSubsystemCommunicationManager.h"
#include "JausNodeCommunicationManager.h"
#include "JausComponentCommunicationManager.h"
#include "ErrorEvent.h"

MessageRouter::MessageRouter(FileLoader *configData, SystemTree *sysTree, EventHandler *handler)
{
	this->systemTree = sysTree;
	this->configData = configData;
	this->eventHandler = handler;

	this->cmptComms = new JausComponentCommunicationManager(configData, this, systemTree);
	this->nodeComms = new JausNodeCommunicationManager(configData, this, systemTree);
	this->subsComms = new JausSubsystemCommunicationManager(configData, this, systemTree);

	// NOTE: These two values should exist in the properties file and should be checked 
	// in the NodeManager class prior to constructing this object
	mySubsystemId = configData->GetConfigDataInt("JAUS", "SubsystemId");
	if(mySubsystemId < JAUS_MINIMUM_SUBSYSTEM_ID || mySubsystemId > JAUS_MAXIMUM_SUBSYSTEM_ID)
	{
		// Invalid ID
		ErrorEvent *e = new ErrorEvent(ErrorEvent::Configuration, __FILE__, __FUNCTION__, __LINE__, "Invalid Subsystem Id");
		this->eventHandler->handleEvent(e);
		mySubsystemId = JAUS_INVALID_SUBSYSTEM_ID;
		return;
	}

	myNodeId = configData->GetConfigDataInt("JAUS", "NodeId");
	if(myNodeId < JAUS_MINIMUM_NODE_ID || myNodeId > JAUS_MAXIMUM_NODE_ID)
	{
		// Invalid ID
		ErrorEvent *e = new ErrorEvent(ErrorEvent::Configuration, __FILE__, __FUNCTION__, __LINE__, "Invalid Node Id");
		this->eventHandler->handleEvent(e);
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
		ErrorEvent *e = new ErrorEvent(ErrorEvent::NullPointer, __FILE__, __FUNCTION__, __LINE__, "Invalid JausMessage");
		this->eventHandler->handleEvent(e);
		return false;
	}

	if(message->source->subsystem == mySubsystemId)
	{
		// ERROR: Message from this subsystem has entered the subsystemSource method
		ErrorEvent *e = new ErrorEvent(ErrorEvent::Routing, __FILE__, __FUNCTION__, __LINE__, "Message from this Subsystem has entered the SubsystemSource method.");
		this->eventHandler->handleEvent(e);

		jausMessageDestroy(message);
		return false;
	}

	if( message->destination->subsystem != mySubsystemId && 
		message->destination->subsystem != JAUS_BROADCAST_SUBSYSTEM_ID)
	{
		// ERROR: Message not for this Subsystem has entered the subsystemSource method
		ErrorEvent *e = new ErrorEvent(ErrorEvent::Routing, __FILE__, __FUNCTION__, __LINE__, "Message not for this Subsystem has entered the SubsystemSource method.");
		this->eventHandler->handleEvent(e);
		jausMessageDestroy(message);
		return false;
	}

	if(message->destination->node == JAUS_BROADCAST_NODE_ID)
	{
		// Have to clone the JausMessage b/c I am sending it in two directions
		nodeComms->sendJausMessage(jausMessageClone(message));
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
		ErrorEvent *e = new ErrorEvent(ErrorEvent::NullPointer, __FILE__, __FUNCTION__, __LINE__, "Invalid JausMessage");
		this->eventHandler->handleEvent(e);
		return false;
	}

	if(message->source->subsystem == mySubsystemId)
	{
		if(message->source->node == myNodeId)
		{
			// ERROR: Message from a local component has entered through the nodeSource method
			ErrorEvent *e = new ErrorEvent(ErrorEvent::Routing, __FILE__, __FUNCTION__, __LINE__, "Message from a local component has entered through the NodeSource method");
			this->eventHandler->handleEvent(e);
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
					// Clone on one of them
					subsComms->sendJausMessage(jausMessageClone(message));
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
				if( message->destination->node != myNodeId &&
					message->destination->node != JAUS_BROADCAST_NODE_ID)
				{
					// ERROR: Message for another node on this subsystem recv'd through NodeComms
					ErrorEvent *e = new ErrorEvent(ErrorEvent::Routing, __FILE__, __FUNCTION__, __LINE__, "Message for another Node on this Subsystem recv'd through NodeComms");
					this->eventHandler->handleEvent(e);
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
				ErrorEvent *e = new ErrorEvent(ErrorEvent::Routing, __FILE__, __FUNCTION__, __LINE__, "Message not for this Node recv'd through NodeComms");
				this->eventHandler->handleEvent(e);
				jausMessageDestroy(message);
				return false;
			}
		}
		else
		{
			// ERROR: Message not for this Subs recv'd through nodeComms
			ErrorEvent *e = new ErrorEvent(ErrorEvent::Routing, __FILE__, __FUNCTION__, __LINE__, "Message not for this Subs recv'd through NodeComms");
			this->eventHandler->handleEvent(e);
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
		ErrorEvent *e = new ErrorEvent(ErrorEvent::NullPointer, __FILE__, __FUNCTION__, __LINE__, "Invalid JausMessage");
		this->eventHandler->handleEvent(e);
		return false;
	}

	//char buf[80] = {0};
	//printf("routeCmptMsg=> ");
	//jausAddressToString(message->source, buf);
	//printf("Routing %s from %s", jausMessageCommandCodeString(message), buf);
	//jausAddressToString(message->destination, buf);
	//printf(" to %s\n", buf);

	if(message->source->subsystem != mySubsystemId)
	{
		// ERROR: Message with a different source subsystem has come in through cmptComms
		ErrorEvent *e = new ErrorEvent(ErrorEvent::Routing, __FILE__, __FUNCTION__, __LINE__, "Message with a different source subsystem has come in through cmptComms");
		this->eventHandler->handleEvent(e);
		jausMessageDestroy(message);
		return false;
	}

	if(message->source->node != myNodeId)
	{
		// ERROR: Message with a different source node has come in through cmptComms
		ErrorEvent *e = new ErrorEvent(ErrorEvent::Routing, __FILE__, __FUNCTION__, __LINE__, "Message with a different source node has come in through cmptComms");
		this->eventHandler->handleEvent(e);
		jausMessageDestroy(message);
		return false;
	}

	if(message->destination->subsystem == mySubsystemId)
	{
		if(message->destination->node == myNodeId)
		{
			// ERROR: Message for this node has escaped the cmptComms! Should not happen!
			ErrorEvent *e = new ErrorEvent(ErrorEvent::Routing, __FILE__, __FUNCTION__, __LINE__, "Message for this node has escaped cmptComms");
			this->eventHandler->handleEvent(e);
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
		ErrorEvent *e = new ErrorEvent(ErrorEvent::NullPointer, __FILE__, __FUNCTION__, __LINE__, "Invalid JausMessage");
		this->eventHandler->handleEvent(e);
		return false;
	}

	if(message->source->subsystem != mySubsystemId)
	{
		// ERROR: Messages not from mySubs should not go through this method!
		ErrorEvent *e = new ErrorEvent(ErrorEvent::Routing, __FILE__, __FUNCTION__, __LINE__, "Messages not from mySubs should not go through this method!");
		this->eventHandler->handleEvent(e);
		jausMessageDestroy(message);
		return false;
	}

	if(message->destination->subsystem == mySubsystemId)
	{
		// ERROR: Messages for mySubs should not go through this method!
		ErrorEvent *e = new ErrorEvent(ErrorEvent::Routing, __FILE__, __FUNCTION__, __LINE__, "Messages for mySubs should not go through this method!");
		this->eventHandler->handleEvent(e);
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
				// Clone once
				subsComms->sendJausMessage(jausMessageClone(message));
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
			ErrorEvent *e = new ErrorEvent(ErrorEvent::Routing, __FILE__, __FUNCTION__, __LINE__, "Either there is no communicator, we're it and our subsInf is turned off");
			this->eventHandler->handleEvent(e);
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


