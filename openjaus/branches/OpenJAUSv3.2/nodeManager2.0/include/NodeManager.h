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
#include "jaus.h"

class NodeManager : public EventHandler
{
public:
	NodeManager(FileLoader *configData);
	~NodeManager(void);

	std::string systemTreeToString();
	std::string systemTreeToDetailedString();

	bool registerEventHandler(EventHandler *handler);

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

