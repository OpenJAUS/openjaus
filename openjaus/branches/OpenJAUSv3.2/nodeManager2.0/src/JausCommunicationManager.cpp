#include "JausCommunicationManager.h"
#include "JausTransportInterface.h"


JausCommunicationManager::JausCommunicationManager(void) {}

JausCommunicationManager::~JausCommunicationManager(void) {}

unsigned long JausCommunicationManager::getInterfaceCount(void)
{
	return (unsigned long) this->interfaces.size();
}

JausTransportInterface *JausCommunicationManager::getJausInterface(unsigned long index)
{
	if(index < this->interfaces.size())
	{
		return this->interfaces.at(index);
	}
	else
	{
		return NULL;
	}
}

JausTransportInterface *JausCommunicationManager::getJausInterface(std::string interfaceName)
{
	for(unsigned long i = 0; i < this->interfaces.size(); i++)
	{
		if(this->interfaces.at(i)->getName() == interfaceName)
		{
			return this->interfaces.at(i);
		}
	}
	return NULL;
}

bool JausCommunicationManager::interfaceExists(std::string interfaceName)
{
	for(unsigned long i = 0; i < this->interfaces.size(); i++)
	{
		if(this->interfaces.at(i)->getName() == interfaceName)
		{
			return true;
		}
	}
	return false;
}

void JausCommunicationManager::enable(void)
{
	enabled = true;
}

void JausCommunicationManager::disable(void)
{
	enabled = false;
}

bool JausCommunicationManager::isEnabled(void)
{
	return enabled;
}

SystemTree *JausCommunicationManager::getSystemTree()
{
	return this->systemTree;
}

bool JausCommunicationManager::sendJausMessage(JausMessage message)
{
	// Does nothing
	// TODO: Throw an error
	return false;
}

bool JausCommunicationManager::receiveJausMessage(JausMessage message, JausTransportInterface *srcInf)
{
	// Does nothing
	// TODO: Throw an error
	return false;
}

MessageRouter *JausCommunicationManager::getMessageRouter()
{
	return this->msgRouter;
}


