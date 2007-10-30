#include "JausComponentCommunicationManager.h"
#include "NodeManagerComponent.h"

JausComponentCommunicationManager::JausComponentCommunicationManager(FileLoader *configData, MessageRouter *msgRouter, SystemTree *systemTree)
{
	this->msgRouter = msgRouter;
	this->systemTree = systemTree;
	this->configData = configData;
	this->nodeManagerCmpt = new NodeManagerComponent(this->configData, this);
	this->communicatorCmpt = new CommunicatorComponent(this->configData, this);
}

JausComponentCommunicationManager::~JausComponentCommunicationManager(void)
{
	delete this->nodeManagerCmpt;
}

void JausComponentCommunicationManager::routeJausMessage(JausTransportPacket *jtPacket)
{
	// TODO: Implement this method
}

NodeManagerComponent *JausComponentCommunicationManager::getNodeManagerComponent(void)
{
	return this->nodeManagerCmpt;
}

