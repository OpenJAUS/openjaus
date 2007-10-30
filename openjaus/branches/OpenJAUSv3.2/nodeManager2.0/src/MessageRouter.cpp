#include "MessageRouter.h"
#include "JausSubsystemCommunicationManager.h"
#include "JausNodeCommunicationManager.h"
#include "JausComponentCommunicationManager.h"

MessageRouter::MessageRouter(FileLoader *configData, JausSubsystemCommunicationManager *subsComms, JausNodeCommunicationManager *nodeComms, JausComponentCommunicationManager *cmptComms)
{
	this->cmptComms = cmptComms;
	this->nodeComms = nodeComms;
	this->subsComms = subsComms;

	this->configData = configData;
}

MessageRouter::~MessageRouter(void){}

bool MessageRouter::routeSubsystemSourceMessage(JausTransportPacket packet)
{
	// TODO: Fill in routing table
	return true;
}

bool MessageRouter::routeNodeSourceMessage(JausTransportPacket packet)
{
	// TODO: Fill in routing table
	return true;
}

bool MessageRouter::routeComponentSourceMessage(JausTransportPacket packet)
{
	// TODO: Fill in routing table
	return true;
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


