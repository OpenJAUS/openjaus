#include "SystemTreeEvent.h"

SystemTreeEvent::SystemTreeEvent(unsigned int type)
{
	this->type = NodeManagerEvent::SystemTreeEvent;
	this->subType = type;
	this->subs = NULL;
	this->node = NULL;
	this->cmpt = NULL;
}

SystemTreeEvent::SystemTreeEvent(unsigned int type, JausSubsystem subs)
{
	this->type = NodeManagerEvent::SystemTreeEvent;
	this->subType = type;
	this->subs = jausSubsystemClone(subs);
	this->node = NULL;
	this->cmpt = NULL;
}


SystemTreeEvent::SystemTreeEvent(unsigned int type, JausNode node)
{
	this->type = NodeManagerEvent::SystemTreeEvent;
	this->subType = type;
	this->subs = NULL;
	this->node = jausNodeClone(node);
	this->cmpt = NULL;
}

SystemTreeEvent::SystemTreeEvent(unsigned int type, JausComponent cmpt)
{
	this->type = NodeManagerEvent::SystemTreeEvent;
	this->subType = type;
	this->subs = NULL;
	this->node = NULL;
	this->cmpt = jausComponentClone(cmpt);
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

	switch(this->subType)
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
			jausNodeToString(this->node, buf);
			output += "Node ADDED: ";
			output += buf;
			return output;

		case SystemTreeEvent::NodeRemoved:
			jausNodeToString(this->node, buf);
			output += "Node REMOVED: ";
			output += buf;
			return output;
		
		case SystemTreeEvent::NodeTimeout:
			jausNodeToString(this->node, buf);
			output += "Node TIMEOUT: ";
			output += buf;
			return output;

		case SystemTreeEvent::ComponentAdded:
			jausComponentToString(this->cmpt, buf);
			output += "Component ADDED: ";
			output += buf;
			return output;

		case SystemTreeEvent::ComponentRemoved:
			jausComponentToString(this->cmpt, buf);
			output += "Component REMOVED: ";
			output += buf;
			return output;

		case SystemTreeEvent::ComponentTimeout:
			jausComponentToString(this->cmpt, buf);
			output += "Component TIMEOUT: ";
			output += buf;
			return output;
	
		default:
			output = "Unknown Subsystem Event";
			return output;
	}
}