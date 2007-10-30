#ifndef MESSAGE_ROUTER_H
#define MESSAGE_ROUTER_H

#include "JausTransportPacket.h"
#include "FileLoader.h"
#include "jaus.h"

class JausSubsystemCommunicationManager;
class JausNodeCommunicationManager;
class JausComponentCommunicationManager;

class MessageRouter
{
public:
	MessageRouter(FileLoader *configData, JausSubsystemCommunicationManager *subsComms, JausNodeCommunicationManager *nodeComms, JausComponentCommunicationManager *cmptComms);
	~MessageRouter(void);
	bool routeSubsystemSourceMessage(JausTransportPacket packet);
	bool routeNodeSourceMessage(JausTransportPacket packet);
	bool routeComponentSourceMessage(JausTransportPacket packet);

	bool subsystemCommunicationEnabled();
	bool nodeCommunicationEnabled();
	bool componentCommunicationEnabled();

private:
	FileLoader *configData;
	JausSubsystemCommunicationManager *subsComms;
	JausNodeCommunicationManager *nodeComms;
	JausComponentCommunicationManager *cmptComms;
};

#endif
