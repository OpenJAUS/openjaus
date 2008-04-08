#ifndef NODEMANAGER_H
#define NODEMANAGER_H

#include <list>
#include <jaus.h>
#include "MessageRouter.h"
#include "SystemTree.h"
#include "utils/FileLoader.h"
#include "EventHandler.h"
#include "events/NodeManagerEvent.h"
#include "events/SystemTreeEvent.h"
#include "events/ErrorEvent.h"
#include "events/JausMessageEvent.h"

#define	OJ_NODE_MANAGER_VERSION	"3.3.0"

class NodeManager : public EventHandler
{
public:
	JAUS_EXPORT NodeManager(FileLoader *configData, EventHandler *handler);
	JAUS_EXPORT ~NodeManager(void);

	JAUS_EXPORT std::string systemTreeToString();
	JAUS_EXPORT std::string systemTreeToDetailedString();

	JAUS_EXPORT bool registerEventHandler(EventHandler *handler);

private:
	FileLoader *configData;

	MessageRouter *msgRouter;
	SystemTree *systemTree;
	
	JausNode node;
	JausSubsystem subsystem;

	void handleEvent(NodeManagerEvent *e);
	std::list <EventHandler *> eventHandlers;
};

#endif

