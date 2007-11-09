#ifndef JAUS_CMPT_COMMS_MNGR_H
#define JAUS_CMPT_COMMS_MNGR_H

#include "JausCommunicationManager.h"
#include "SystemTree.h"
#include "NodeManagerComponent.h"
#include "CommunicatorComponent.h"

class JausComponentCommunicationManager : public JausCommunicationManager
{
public:
	JausComponentCommunicationManager(FileLoader *configData, MessageRouter *msgRouter, SystemTree *systemTree, EventHandler *handler);
	~JausComponentCommunicationManager(void);
	bool sendJausMessage(JausMessage message);
	bool receiveJausMessage(JausMessage message, JausTransportInterface *srcInf);

	NodeManagerComponent *getNodeManagerComponent(void);
	
private:
	NodeManagerComponent *nodeManagerCmpt;
	CommunicatorComponent *communicatorCmpt;

	bool sendToComponentX(JausMessage message);
	bool sendToAllInterfaces(JausMessage message);
};

#endif
