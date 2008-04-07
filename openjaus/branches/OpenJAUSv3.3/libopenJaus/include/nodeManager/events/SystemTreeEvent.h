#ifndef SYSTEM_TREE_EVENT_H
#define SYSTEM_TREE_EVENT_H

#include <string>
#include "NodeManagerEvent.h"
#include "jaus.h"

class SystemTreeEvent : public NodeManagerEvent
{
public:
	SystemTreeEvent(unsigned int type);
	SystemTreeEvent(unsigned int type, JausSubsystem subs);
	SystemTreeEvent(unsigned int type, JausNode node);
	SystemTreeEvent(unsigned int type, JausComponent cmpt);
	~SystemTreeEvent();

	std::string toString();
	JausComponent getComponent();
	JausNode getNode();
	JausSubsystem getSubsystem();
	
	enum {	SubsystemAdded, SubsystemRemoved, SubsystemTimeout, 
			NodeAdded, NodeRemoved, NodeTimeout,
			ComponentAdded, ComponentRemoved, ComponentTimeout};

private:
	unsigned int subType;
	JausSubsystem subs;
	JausNode node;
	JausComponent cmpt;
};

#endif
