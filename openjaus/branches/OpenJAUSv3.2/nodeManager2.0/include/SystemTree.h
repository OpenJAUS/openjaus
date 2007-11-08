#ifndef SYSTEM_TREE_H
#define SYSTEM_TREE_H

#include "FileLoader.h"
#include "EventHandler.h"
#include "jaus.h"

class SystemTree
{
public:
	SystemTree(FileLoader *configData, EventHandler *handler);
	~SystemTree(void);

	bool updateComponentTimestamp(JausAddress address);
	bool updateNodeTimestamp(JausAddress address);
	bool updateSubsystemTimestamp(JausAddress address);

	bool setComponentServices(JausAddress address, JausArray inputServices);

	bool setSubsystemIdentification(JausAddress address, char *identification);
	bool setNodeIdentification(JausAddress address, char *identification);
	bool setComponentIdentification(JausAddress address, char *identification);

	char *getSubsystemIdentification(JausSubsystem subsystem);
	char *getSubsystemIdentification(JausAddress address);
	char *getSubsystemIdentification(int subsId);

	char *getNodeIdentification(JausNode node);
	char *getNodeIdentification(JausAddress address);
	char *getNodeIdentification(int subsId, int nodeId);

	bool hasComponent(JausComponent cmpt);
	bool hasComponent(JausAddress address);
	bool hasComponent(int subsystemId, int nodeId, int componentId, int instanceId);

	bool hasNode(JausNode node);
	bool hasNode(JausAddress address);
	bool hasNode(int subsId, int nodeId);

	bool hasSubsystem(JausSubsystem subsystem);
	bool hasSubsystem(JausAddress address);
	bool hasSubsystem(int subsId);

	bool hasSubsystemIdentification(JausSubsystem subsystem);
	bool hasSubsystemIdentification(JausAddress address);
	bool hasSubsystemIdentification(int subsId);

	bool hasSubsystemConfiguration(JausSubsystem subsystem);
	bool hasSubsystemConfiguration(JausAddress address);
	bool hasSubsystemConfiguration(int subsId);

	bool hasNodeIdentification(JausNode node);
	bool hasNodeIdentification(JausAddress address);
	bool hasNodeIdentification(int subsId, int nodeId);

	bool hasNodeConfiguration(JausNode node);
	bool hasNodeConfiguration(JausAddress address);
	bool hasNodeConfiguration(int subsId, int nodeId);

	bool hasComponentIdentification(JausComponent cmpt);
	bool hasComponentIdentification(JausAddress address);
	bool hasComponentIdentification(int subsystemId, int nodeId, int componentId, int instanceId);

	bool hasComponentServices(JausComponent cmpt);
	bool hasComponentServices(JausAddress address);
	bool hasComponentServices(int subsystemId, int nodeId, int componentId, int instanceId);

	JausSubsystem *getSystem(void);

	JausSubsystem getSubsystem(JausSubsystem subsystem);
	JausSubsystem getSubsystem(JausAddress address);
	JausSubsystem getSubsystem(int subsId);

	JausNode getNode(JausNode node);
	JausNode getNode(JausAddress address);
	JausNode getNode(int subsId, int nodeId);

	JausComponent getComponent(JausComponent cmpt);
	JausComponent getComponent(JausAddress address);
	JausComponent getComponent(int subsystemId, int nodeId, int componentId, int instanceId);

	bool addSubsystem(JausSubsystem subs);
	bool addSubsystem(JausAddress address, JausSubsystem subs);
	bool addSubsystem(int subsId, JausSubsystem subs);

	bool addNode(JausNode node);
	bool addNode(JausAddress address, JausNode node);
	bool addNode(int subsId, int nodeId, JausNode node);

	bool addComponent(JausComponent cmpt);
	bool addComponent(JausAddress address, JausComponent cmpt);
	bool addComponent(int subsystemId, int nodeId, int componentId, int instanceId, JausComponent cmpt);

	bool removeSubsystem(JausSubsystem subsystem);
	bool removeSubsystem(JausAddress address);
	bool removeSubsystem(int subsId);

	bool removeNode(JausNode node);
	bool removeNode(JausAddress address);
	bool removeNode(int subsId, int nodeId);
	
	bool removeComponent(JausComponent cmpt);
	bool removeComponent(JausAddress address);
	bool removeComponent(int subsystemId, int nodeId, int componentId, int instanceId);

	bool replaceSubsystem(JausAddress address, JausSubsystem newSubs);
	bool replaceSubsystem(int subsystemId, JausSubsystem newSubs);

	bool replaceNode(JausAddress address, JausNode newNode);
	bool replaceNode(int subsystemId, int nodeId, JausNode newNode);
	bool replaceComponent(JausAddress address, JausComponent newCmpt);

	JausAddress lookUpAddress(JausAddress address);
	JausAddress lookUpAddress(int lookupSubs, int lookupNode, int lookupCmpt, int lookupInst);
	
	JausAddress lookUpServiceInNode(int nodeId, int commandCode, int serviceType);
	JausAddress lookUpServiceInNode(JausNode node, int commandCode, int serviceType);
	JausAddress lookUpServiceInSubsystem(int subsId, int nodeId, int commandCode, int serviceType);
	JausAddress lookUpServiceInSubsystem(JausSubsystem subs, int commandCode, int serviceType);
	JausAddress lookUpServiceInSystem(int commandCode, int serviceType);

	unsigned char getNextInstanceId(JausAddress address);

	std::string toString();
	std::string toDetailedString();
	void refresh();

private:
	FileLoader *configData;
	EventHandler *eventHandler;
	JausSubsystem system[255];
	int subsystemCount;
	int mySubsystemId;
	int myNodeId;

	JausNode findNode(JausNode node);
	JausNode findNode(JausAddress address);
	JausNode findNode(int subsId, int nodeId);

	JausComponent findComponent(JausComponent cmpt);
	JausComponent findComponent(JausAddress address);
	JausComponent findComponent(int subsId, int nodeId, int cmptId, int instId);

};

#endif
