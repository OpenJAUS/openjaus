#ifndef NODEMANAGER_H
#define NODEMANAGER_H

#include "MessageRouter.h"
#include "SystemTree.h"
#include "JausSubsystemCommunicationManager.h"
#include "JausNodeCommunicationManager.h"
#include "JausComponentCommunicationManager.h"
#include "FileLoader.h"

class NodeManager
{
public:
	NodeManager(FileLoader *configData);
	~NodeManager(void);

private:
	FileLoader *configData;

	MessageRouter *msgRouter;
	SystemTree *SystemTree;
	
	JausSubsystemCommunicationManager *subsComms;
	JausNodeCommunicationManager *nodeComms;
	JausComponentCommunicationManager *cmptComms;
};

#endif

