#include "NodeManagerEvent.h"

unsigned int NodeManagerEvent::getType()
{
	return this->type;
}

std::string NodeManagerEvent::toString()
{
	switch(this->type)
	{
		case NodeManagerEvent::SystemTreeEvent:
			return "Subsystem Event";
		
		case NodeManagerEvent::ErrorEvent:
			return "Error Event";
		
		case NodeManagerEvent::TransportEvent:
			return "Transport Event";

		default:
			return "Unknown Event";
	}
}

SystemTreeEvent::SystemTreeEvent(unsigned int type)
{
	this->eventType = type;
	subs = NULL;
	node = NULL;
	cmpt = NULL;
}

SystemTreeEvent::SystemTreeEvent(unsigned int type, JausSubsystem subs)
{
	this->eventType = type;
	subs = jausSubsystemClone(subs);
	node = NULL;
	cmpt = NULL;
}


SystemTreeEvent::SystemTreeEvent(unsigned int type, JausNode node)
{
	this->eventType = type;
	subs = NULL;
	node = jausNodeClone(node);
	cmpt = NULL;
}

SystemTreeEvent::SystemTreeEvent(unsigned int type, JausComponent cmpt)
{
	this->eventType = type;
	subs = NULL;
	node = NULL;
	cmpt = jausComponentClone(cmpt);
}

SystemTreeEvent::~SystemTreeEvent()
{
	if(subs) jausSubsystemDestroy(subs);
	if(node) jausNodeDestroy(node);
	if(cmpt) jausComponentDestroy(cmpt);
}


std::string SystemTreeEvent::toString()
{
	std::string output = "";
	char buf[128] = {0};

	switch(this->eventType)
	{
		case SystemTreeEvent::SubsystemAdded:
			jausSubsystemToString(this->subs, buf);
			output += "Subsystem ADDED: ";
			output += buf;
			return output;

		case SystemTreeEvent::SubsystemRemoved:
			jausSubsystemToString(this->subs, buf);
			output += "Subsystem REMOVED: ";
			output += buf;
			return output;

		case SystemTreeEvent::SubsystemTimeout:
			jausSubsystemToString(this->subs, buf);
			output += "Subsystem TIMEOUT: ";
			output += buf;
			return output;

		case SystemTreeEvent::NodeAdded:
			return output;

		case SystemTreeEvent::NodeRemoved:
			return output;
		
		case SystemTreeEvent::NodeTimeout:
			return output;

		case SystemTreeEvent::ComponentAdded:
			return output;

		case SystemTreeEvent::ComponentRemoved:
			return output;

		case SystemTreeEvent::ComponentTimeout:
			return output;
	
		default:
			output = "Unknown Subsystem Event";
			return output;
	}
}