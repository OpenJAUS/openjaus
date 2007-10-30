#ifndef JAUS_SUBS_COMMS_MNGR_H
#define JAUS_SUBS_COMMS_MNGR_H

#include "JausCommunicationManager.h"

class JausSubsystemCommunicationManager : public JausCommunicationManager
{
public:
	JausSubsystemCommunicationManager(void);
	~JausSubsystemCommunicationManager(void);
	void routeJausMessage(JausTransportPacket *jtPacket);
};

#endif
