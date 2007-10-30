#ifndef JAUS_CMPT_COMMS_MNGR_H
#define JAUS_CMPT_COMMS_MNGR_H

#include "JausCommunicationManager.h"
#include "SystemTree.h"
#include "NodeManagerComponent.h"
#include "CommunicatorComponent.h"

class JausComponentCommunicationManager : public JausCommunicationManager
{
public:
	JausComponentCommunicationManager(FileLoader *configData, MessageRouter *msgRouter, SystemTree *systemTree);
	~JausComponentCommunicationManager(void);
	void routeJausMessage(JausTransportPacket *jtPacket);

	NodeManagerComponent *getNodeManagerComponent(void);
	
private:
	NodeManagerComponent *nodeManagerCmpt;
	CommunicatorComponent *communicatorCmpt;
};

#endif
