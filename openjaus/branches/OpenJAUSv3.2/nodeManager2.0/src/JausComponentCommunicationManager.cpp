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

bool JausComponentCommunicationManager::sendJausMessage(JausMessage message)
{
	// TODO: Implement this method
	return false;
}

bool JausComponentCommunicationManager::receiveJausMessage(JausMessage message, JausTransportInterface *srcInf)
{
	// TODO: Implement this method
	return false;
}

NodeManagerComponent *JausComponentCommunicationManager::getNodeManagerComponent(void)
{
	return this->nodeManagerCmpt;
}

