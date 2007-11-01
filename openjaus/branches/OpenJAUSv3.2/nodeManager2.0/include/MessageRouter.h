#ifndef MESSAGE_ROUTER_H
#define MESSAGE_ROUTER_H

#include "SystemTree.h"
#include "JausTransportPacket.h"
#include "FileLoader.h"
#include "jaus.h"

class JausSubsystemCommunicationManager;
class JausNodeCommunicationManager;
class JausComponentCommunicationManager;

class MessageRouter
{
public:
	MessageRouter(FileLoader *configData, JausSubsystemCommunicationManager *subsComms, JausNodeCommunicationManager *nodeComms, JausComponentCommunicationManager *cmptComms, SystemTree *systemTree);
	~MessageRouter(void);
	bool routeSubsystemSourceMessage(JausMessage message);
	bool routeNodeSourceMessage(JausMessage message);
	bool routeComponentSourceMessage(JausMessage message);

	bool subsystemCommunicationEnabled();
	bool nodeCommunicationEnabled();
	bool componentCommunicationEnabled();

private:
	FileLoader *configData;
	JausSubsystemCommunicationManager *subsComms;
	JausNodeCommunicationManager *nodeComms;
	JausComponentCommunicationManager *cmptComms;
	SystemTree *systemTree;

	unsigned short mySubsystemId;
	unsigned short myNodeId;
	bool sendToCommunicator(JausMessage message);
};

#endif
