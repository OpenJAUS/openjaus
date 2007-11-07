#include "NodeManager.h"

NodeManager::NodeManager(FileLoader *configData)
{
	// Create our systemTable
	this->systemTree = new SystemTree(configData);

	// Create this subsystem
	this->subsystem = jausSubsystemCreate();
	if(!subsystem)
	{
		//TODO: Log Error. Throw Exception.
		return;
	}
	
	// Setup this subsystem
	int	subsystemId = configData->GetConfigDataInt("JAUS", "SubsystemId");
	if(subsystemId < JAUS_MINIMUM_SUBSYSTEM_ID || subsystemId > JAUS_MAXIMUM_SUBSYSTEM_ID)
	{
		// Invalid ID
		// TODO: Throw an exception? Log an error.
		return;
	}
	this->subsystem->id = subsystemId;
	
	this->subsystem->identification = (char *) malloc(strlen(configData->GetConfigDataString("JAUS", "Subsystem_Identification").c_str())+1);
	sprintf(this->subsystem->identification, configData->GetConfigDataString("JAUS", "Subsystem_Identification").c_str());
	
	// Create this node
	this->node = jausNodeCreate();
	if(!node)
	{
		//TODO: Log Error. Throw Exception.
		return;
	}

	// Setup this node
	int nodeId = configData->GetConfigDataInt("JAUS", "NodeId");
	if(nodeId < JAUS_MINIMUM_NODE_ID || nodeId > JAUS_MAXIMUM_NODE_ID)
	{
		// Invalid ID
		// TODO: Throw an exception? Log an error.
		return;
	}
	this->node->id = nodeId;
	this->node->identification = (char *) malloc(strlen(configData->GetConfigDataString("JAUS", "Node_Identification").c_str())+1);
	sprintf(this->node->identification, configData->GetConfigDataString("JAUS", "Node_Identification").c_str());
	jausArrayAdd(this->subsystem->nodes, this->node);

	// TODO: Check our config file parameters

	// Add this subsystem
	this->systemTree->addSubsystem(subsystem);

	// Create our MsgRouter
	this->msgRouter = new MessageRouter(configData, systemTree);
}

NodeManager::~NodeManager(void)
{
	delete msgRouter;
	delete systemTree;
}

std::string NodeManager::systemTableToString()
{
	return systemTree->toString();
}

std::string NodeManager::systemTableToDetailedString()
{
	return systemTree->toDetailedString();
}
