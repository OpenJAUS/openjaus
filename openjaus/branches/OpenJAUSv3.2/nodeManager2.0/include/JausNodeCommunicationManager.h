#ifndef JAUS_NODE_COMMS_MNGR_H
#define JAUS_NODE_COMMS_MNGR_H

#include "JausCommunicationManager.h"

class JausNodeCommunicationManager : public JausCommunicationManager
{
public:
	JausNodeCommunicationManager(FileLoader *configData, MessageRouter *msgRouter, SystemTree *systemTree);
	~JausNodeCommunicationManager(void);
	bool sendJausMessage(JausMessage message);
	bool receiveJausMessage(JausMessage message, JausTransportInterface *srcInf);

private:
	bool sendToSubsystemGateway(JausMessage message);
};

#endif
