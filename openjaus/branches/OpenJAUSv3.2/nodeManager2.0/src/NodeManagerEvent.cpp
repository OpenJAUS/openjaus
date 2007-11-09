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

