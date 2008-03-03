#ifndef JAUS_NODE_COMMS_MNGR_H
#define JAUS_NODE_COMMS_MNGR_H

#include "JausCommunicationManager.h"

class JausNodeCommunicationManager : public JausCommunicationManager
{
public:
	JausNodeCommunicationManager(FileLoader *configData, MessageRouter *msgRouter, SystemTree *systemTree, EventHandler *handler);
	~JausNodeCommunicationManager(void);
	bool sendJausMessage(JausMessage message);
	bool receiveJausMessage(JausMessage message, JausTransportInterface *srcInf);

private:
	bool sendToSubsystemGateway(JausMessage message);
	bool sendToNodeX(JausMessage message);
	bool sendToAllInterfaces(JausMessage message);
};

#endif
