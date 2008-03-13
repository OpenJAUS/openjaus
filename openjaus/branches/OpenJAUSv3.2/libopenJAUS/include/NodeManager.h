#ifndef NODEMANAGER_H
#define NODEMANAGER_H

#include <list>
#include "MessageRouter.h"
#include "SystemTree.h"
#include "FileLoader.h"
#include "EventHandler.h"
#include "NodeManagerEvent.h"
#include "SystemTreeEvent.h"
#include "ErrorEvent.h"
#include "JausMessageEvent.h"
#include "jaus.h"

#define	OJ_NODE_MANAGER_VERSION	"3.2.0"

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

