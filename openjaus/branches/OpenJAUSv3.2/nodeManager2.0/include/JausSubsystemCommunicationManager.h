#ifndef JAUS_SUBS_COMMS_MNGR_H
#define JAUS_SUBS_COMMS_MNGR_H

#include "JausCommunicationManager.h"

class JausSubsystemCommunicationManager : public JausCommunicationManager
{
public:
	JausSubsystemCommunicationManager(FileLoader *configData, MessageRouter *msgRouter, SystemTree *systemTree);
	~JausSubsystemCommunicationManager(void);
	bool sendJausMessage(JausMessage message);
	bool receiveJausMessage(JausMessage message, JausTransportInterface *srcInf);

private:
	bool sendToSubsystemX(JausMessage message);
	bool sendToAllInterfaces(JausMessage message);
};

#endif
