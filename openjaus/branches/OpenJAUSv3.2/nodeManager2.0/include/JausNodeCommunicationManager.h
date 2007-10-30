#ifndef JAUS_NODE_COMMS_MNGR_H
#define JAUS_NODE_COMMS_MNGR_H

#include "JausCommunicationManager.h"

class JausNodeCommunicationManager : public JausCommunicationManager
{
public:
	JausNodeCommunicationManager(void);
	~JausNodeCommunicationManager(void);
	void routeJausMessage(JausTransportPacket *jtPacket);
};

#endif
