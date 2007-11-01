#include "CommunicatorComponent.h"
#include "JausComponentCommunicationManager.h"
#include "jaus.h"

CommunicatorComponent::CommunicatorComponent(FileLoader *configData, JausComponentCommunicationManager *cmptComms)
{
	this->type = COMPONENT_INTERFACE;
	
	this->commMngr = cmptComms;
	this->configData = configData;

	this->name = "Communicator Component";
	this->cmpt = jausComponentCreate();
	if(!this->cmpt)
	{
		return;
	}

	this->queue = JausTransportQueue();
}

CommunicatorComponent::~CommunicatorComponent(void)
{
}

bool CommunicatorComponent::processMessage(JausMessage message)
{
	return true;
}

std::string CommunicatorComponent::toString()
{
	return "Communicator Component";
}

void CommunicatorComponent::startupState()
{

}

void CommunicatorComponent::intializeState()
{

}

void CommunicatorComponent::standbyState()
{

}

void CommunicatorComponent::readyState()
{

}

void CommunicatorComponent::emergencyState()
{

}

void CommunicatorComponent::failureState()
{

}

void CommunicatorComponent::shutdownState()
{

}

void CommunicatorComponent::allState()
{

}

bool CommunicatorComponent::processReportIdentification(JausMessage message)
{
	return true;
}

bool CommunicatorComponent::processReportConfiguration(JausMessage message)
{

	return true;
}

bool CommunicatorComponent::processReportServices(JausMessage message)
{

	return true;
}

bool CommunicatorComponent::processReportHeartbeat(JausMessage message)
{

	return true;
}

bool CommunicatorComponent::processCreateEvent(JausMessage message)
{

	return true;
}

bool CommunicatorComponent::processCancelEvent(JausMessage message)
{

	return true;
}
