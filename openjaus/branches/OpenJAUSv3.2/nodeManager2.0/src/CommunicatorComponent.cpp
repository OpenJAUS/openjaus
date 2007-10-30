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

bool CommunicatorComponent::processMessage(JausTransportPacket jtPacket)
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

bool CommunicatorComponent::processReportIdentification(JausTransportPacket jtPacket)
{
	return true;
}

bool CommunicatorComponent::processReportConfiguration(JausTransportPacket jtPacket)
{

	return true;
}

bool CommunicatorComponent::processReportServices(JausTransportPacket jtPacket)
{

	return true;
}

bool CommunicatorComponent::processReportHeartbeat(JausTransportPacket jtPacket)
{

	return true;
}

bool CommunicatorComponent::processCreateEvent(JausTransportPacket jtPacket)
{

	return true;
}

bool CommunicatorComponent::processCancelEvent(JausTransportPacket jtPacket)
{

	return true;
}
