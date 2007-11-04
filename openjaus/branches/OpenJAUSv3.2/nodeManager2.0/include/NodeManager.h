#ifndef NODEMANAGER_H
#define NODEMANAGER_H

#include "MessageRouter.h"
#include "SystemTree.h"
#include "FileLoader.h"
#include "jaus.h"

class NodeManager
{
public:
	NodeManager(FileLoader *configData);
	~NodeManager(void);

	std::string getSystemTable();

private:
	FileLoader *configData;

	MessageRouter *msgRouter;
	SystemTree *systemTree;
	
	JausNode node;
	JausSubsystem subsystem;
};

#endif

