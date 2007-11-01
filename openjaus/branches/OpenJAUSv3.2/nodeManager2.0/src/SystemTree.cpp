#include "SystemTree.h"
#include "timeLib.h"

SystemTree::SystemTree(FileLoader *configData)
{
	this->configData = configData;
	subsystemCount = 0;
}

SystemTree::~SystemTree(void)
{
}

bool SystemTree::updateComponentTimestamp(JausAddress address)
{
	JausComponent cmpt = findComponent(address);
	if(cmpt)
	{
		jausComponentUpdateTimestamp(cmpt);
		return true;
	}
	else
	{
		return false;
	}
}

bool SystemTree::updateNodeTimestamp(JausAddress address)
{
	JausNode node = findNode(address);
	if(node)
	{
		jausNodeUpdateTimestamp(node);
		return true;
	}
	else
	{
		return false;
	}
}

bool SystemTree::updateSubsystemTimestamp(JausAddress address)
{
	JausSubsystem subs = system[address->subsystem];
	if(subs)
	{
		jausSubsystemUpdateTimestamp(subs);
		return true;
	}
	else
	{
		return false;
	}
}

unsigned char SystemTree::getNextInstanceId(JausAddress address)
{
	bool instanceAvailable[255] = {true};
	int i = 0;
	
	// Get this node
	JausNode node = findNode(address->subsystem, address->node);
	if(node)
	{
		// We'll go through all the attached components and check for matches
		for(i=0; i < node->components->elementCount; i++)
		{
			JausComponent cmpt = (JausComponent) node->components->elementData[i];
		
			// if this is the same cmpt Id, we'll mark that instance as used
			if(cmpt->address->component == address->component)
			{
				instanceAvailable[cmpt->address->instance] = false;
			}
		}

		// Find the lowest value instance that is available
		i = JAUS_MINIMUM_INSTANCE_ID;
		while(i <= JAUS_MAXIMUM_INSTANCE_ID)
		{
			if(instanceAvailable[i])
			{
				return i;
			}
		}
		return JAUS_INVALID_INSTANCE_ID;
	}
	return JAUS_INVALID_INSTANCE_ID;
}

bool SystemTree::hasComponent(JausComponent cmpt)
{
	JausAddress address = cmpt->address;
	return hasComponent(address->subsystem, address->node, address->component, address->instance);
}

bool SystemTree::hasComponent(JausAddress address)
{
	return hasComponent(address->subsystem, address->node, address->component, address->instance);
}

bool SystemTree::hasComponent(int subsystemId, int nodeId, int componentId, int instanceId)
{
	JausComponent cmpt = findComponent(subsystemId, nodeId, componentId, instanceId);
	if(cmpt)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool SystemTree::hasNode(JausNode node)
{
	return hasNode(node->subsystem->id, node->id);
}

bool SystemTree::hasNode(JausAddress address)
{
	return hasNode(address->subsystem, address->node);
}

bool SystemTree::hasNode(int subsystemId, int nodeId)
{
	JausNode node = findNode(subsystemId, nodeId);
	if(node)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool SystemTree::hasSubsystem(JausSubsystem subsystem)
{
	return hasSubsystem(subsystem->id);
}

bool SystemTree::hasSubsystem(JausAddress address)
{
	return hasSubsystem(address->subsystem);
}

bool SystemTree::hasSubsystem(int subsystemId)
{
	if(system[subsystemId])
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool SystemTree::hasSubsystemConfiguration(JausSubsystem subsystem)
{
	return hasSubsystemConfiguration(subsystem->id);
}

// TODO: Move this to JausSubsystem
bool SystemTree::hasSubsystemConfiguration(JausAddress address)
{
	return hasSubsystemConfiguration(address->subsystem);
}

bool SystemTree::hasSubsystemConfiguration(int subsId)
{
	if(system[subsId])
	{
		// TODO: Check for config info
		return true;
	}
	else
	{
		return false;
	}
}

bool SystemTree::hasSubsystemIdentification(JausSubsystem subsystem)
{
	return hasSubsystemIdentification(subsystem->id);
}

bool SystemTree::hasSubsystemIdentification(JausAddress address)
{
	return hasSubsystemIdentification(address->subsystem);
}

bool SystemTree::hasSubsystemIdentification(int subsId)
{
	JausSubsystem subs = system[subsId];
	if(subs && subs->identification)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool SystemTree::hasNodeIdentification(JausNode node)
{
	return hasNodeIdentification(node->subsystem->id, node->id);
}

bool SystemTree::hasNodeIdentification(JausAddress address)
{
	return hasNodeIdentification(address->subsystem, address->node);
}

bool SystemTree::hasNodeIdentification(int subsystemId, int nodeId)
{
	JausNode node = findNode(subsystemId, nodeId);
	if(node && node->identification)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool SystemTree::hasNodeConfiguration(JausAddress address)
{
	return true;
}

bool SystemTree::hasComponentIdentification(JausAddress address)
{
	return hasComponentIdentification(address->subsystem, address->node, address->component, address->instance);
}

bool SystemTree::hasComponentIdentification(int subsystemId, int nodeId, int componentId, int instanceId)
{
	JausComponent cmpt = findComponent(subsystemId, nodeId, componentId, instanceId);
	if(cmpt && cmpt->identification)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool SystemTree::hasComponentServices(JausAddress address)
{
	return hasComponentServices(address->subsystem, address->node, address->component, address->instance);
}

bool SystemTree::hasComponentServices(int subsystemId, int nodeId, int componentId, int instanceId)
{
	JausComponent cmpt = findComponent(subsystemId, nodeId, componentId, instanceId);
	if(cmpt && cmpt->services->elementCount > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//JausAddress SystemTree::lookUpAddressInNode(JausNode node, JausAddress address);
//JausAddress SystemTree::lookUpAddressInSubsystem(JausSubsystem subs, JausAddress address);
//JausAddress SystemTree::lookUpAddressInSystem(JausAddress address);
//JausAddress SystemTree::lookUpServiceInNode(JausNode node, int commandCode, int serviceType);
//JausAddress SystemTree::lookUpServiceInSubsystem(JausSubsystem subs, int commandCode, int serviceType);

JausAddress SystemTree::lookUpServiceInSystem(int commandCode, int serviceType)
{
	JausAddress list = NULL;
	JausAddress cur = list;
	int i;

	if(serviceType != JAUS_SERVICE_INPUT_COMMAND && serviceType != JAUS_SERVICE_OUTPUT_COMMAND)
	{
		return NULL;
	}

	for(i = 1; i < 254; i++)
	{
		JausSubsystem subs = system[i];
		if(!subs)
		{
			continue;
		}

		for(int i = 0; i < subs->nodes->elementCount; i++)
		{
			JausNode node = (JausNode) subs->nodes->elementData[i];

			for(int j = 0; j < node->components->elementCount; j++)
			{
				JausComponent cmpt = (JausComponent) node->components->elementData[j];
				for(int k = 0; cmpt->services->elementCount; k++)
				{
					JausService service = (JausService) cmpt->services->elementData[i];
					JausCommand command = NULL;
					switch(serviceType)
					{
						case JAUS_SERVICE_INPUT_COMMAND:
							command = service->inputCommandList;
							break;
						
						case JAUS_SERVICE_OUTPUT_COMMAND:
							command = service->outputCommandList;
							break;
						
						default:
							// ERROR: Unknown service type
							// SHOULD NEVER GET HERE, CHECKED ABOVE
							return list;
					}

					while(command)
					{
						if(command->commandCode == commandCode)
						{
							// YAY... we found a matching commandCode
							// Add this component's address to our list
							JausAddress address = jausAddressClone(cmpt->address);
							address->next = NULL;
							
							if(list == NULL)
							{
								list = address;
								cur = list->next;
							}
							else
							{
								cur->next = address;
								cur = cur->next;
							}

							// This is a cheat to skip the rest of the commands
							// since a command should not repeat
							command = NULL;
						}
						else
						{
							command = command->next;
						}
					}
				}
			}
		}
	}

	return list;

}

JausSubsystem *SystemTree::getSystem(void)
{
	if(subsystemCount == 0)
	{
		return NULL;
	}

	JausSubsystem *systemClone = (JausSubsystem *)malloc(subsystemCount*sizeof(JausSubsystem));
	int systemCloneIndex = 0;
	
	for(int i = 1; i < 255; i++)
	{
		if(system[i])
		{
			systemClone[systemCloneIndex] = jausSubsystemClone(system[i]);
			systemCloneIndex++;
		}
	}
	return systemClone;
}

JausSubsystem SystemTree::getSubsystem(JausSubsystem subsystem)
{
	return getSubsystem(subsystem->id);
}

JausSubsystem SystemTree::getSubsystem(JausAddress address)
{
	return getSubsystem(address->subsystem);
}

JausSubsystem SystemTree::getSubsystem(int subsystemId)
{
	JausSubsystem subs = system[subsystemId];
	if(subs)
	{
		return jausSubsystemClone(subs);
	}
	return NULL;
}

JausNode SystemTree::getNode(JausNode node)
{
	return getNode(node->subsystem->id, node->id);
}

JausNode SystemTree::getNode(JausAddress address)
{
	return getNode(address->subsystem, address->node);
}

JausNode SystemTree::getNode(int subsystemId, int nodeId)
{
	JausNode node = findNode(subsystemId, nodeId);
	if(node)
	{
		return jausNodeClone(node);
	}
	return NULL;
}

JausComponent SystemTree::getComponent(JausComponent cmpt)
{
	return getComponent(cmpt->address->subsystem, cmpt->address->node, cmpt->address->component, cmpt->address->instance);
}

JausComponent SystemTree::getComponent(JausAddress address)
{
	return getComponent(address->subsystem, address->node, address->component, address->instance);
}

JausComponent SystemTree::getComponent(int subsystemId, int nodeId, int componentId, int instanceId)
{
	JausComponent cmpt = findComponent(subsystemId, nodeId, componentId, instanceId);
	if(cmpt)
	{
		return jausComponentClone(cmpt);
	}
	return NULL;
}

JausNode SystemTree::findNode(JausNode node)
{
	return findNode(node->subsystem->id, node->id);
}

JausNode SystemTree::findNode(JausAddress address)
{
	return findNode(address->subsystem, address->node);
}

JausNode SystemTree::findNode(int subsId, int nodeId)
{
	JausSubsystem subs = system[subsId];
	if(subs)
	{
		for(int i = 0; i < subs->nodes->elementCount; i++)
		{
			JausNode node = (JausNode)subs->nodes->elementData[i];
			if(node->id == nodeId)
			{
				return node;
			}
		}
	}
	return NULL;
}

JausComponent SystemTree::findComponent(JausComponent cmpt)
{
	return findComponent(cmpt->address->subsystem, cmpt->address->node, cmpt->address->component, cmpt->address->instance);
}

JausComponent SystemTree::findComponent(JausAddress address)
{
	return findComponent(address->subsystem, address->node, address->component, address->instance);
}

JausComponent SystemTree::findComponent(int subsId, int nodeId, int cmptId, int instId)
{
	JausSubsystem subs = system[subsId];
	if(subs)
	{
		for(int i = 0; i < subs->nodes->elementCount; i++)
		{
			JausNode node = (JausNode)subs->nodes->elementData[i];
			if(node->id == nodeId)
			{
				for(int i = 0; i < node->components->elementCount; i++)
				{
					JausComponent cmpt = (JausComponent)node->components->elementData[i];
					if(	cmpt->address->component == cmptId && cmpt->address->instance == instId )
					{
						return cmpt;
					}
				}
				return NULL;
			}
		}
	}
	return NULL;
}


bool SystemTree::addComponent(JausComponent cmpt)
{
	return addComponent(cmpt->address->subsystem, cmpt->address->node, cmpt->address->component, cmpt->address->instance, cmpt);
}

bool SystemTree::addComponent(JausAddress address, JausComponent cmpt)
{
	return addComponent(address->subsystem, address->node, address->component, address->instance, cmpt);
}

bool SystemTree::addComponent(int subsystemId, int nodeId, int componentId, int instanceId, JausComponent cmpt)
{
	if(!this->hasComponent(subsystemId, nodeId, componentId, instanceId))
	{
		JausNode node = findNode(subsystemId, nodeId);
		if(node && componentId >= JAUS_MINIMUM_COMPONENT_ID && componentId <= JAUS_MAXIMUM_COMPONENT_ID
				&& instanceId >= JAUS_MINIMUM_INSTANCE_ID && instanceId <= JAUS_MAXIMUM_INSTANCE_ID)
		{
			// Add the component to the node
			if(cmpt)
			{
				cmpt = jausComponentClone(cmpt);
			}
			else
			{
				cmpt = jausComponentCreate();
				cmpt->address->instance = instanceId;
				cmpt->address->component = componentId;
				cmpt->address->node = nodeId;
				cmpt->address->subsystem = subsystemId;
			}
			cmpt->node = node;

			jausArrayAdd(node->components, cmpt);
			return true;
		}
	}

	return false;
}

bool SystemTree::addNode(JausNode node)
{
	return addNode(node->subsystem->id, node->id, node);
}

bool SystemTree::addNode(JausAddress address, JausNode node)
{
	return addNode(address->subsystem, address->node, node);
}

bool SystemTree::addNode(int subsystemId, int nodeId, JausNode node)
{
	if(!this->hasNode(subsystemId, nodeId))
	{
		JausSubsystem subs = system[subsystemId];
		if(subs && nodeId >= JAUS_MINIMUM_NODE_ID && nodeId <= JAUS_MAXIMUM_NODE_ID)
		{
			if(node)
			{
				node = jausNodeClone(node);
			}
			else
			{
				JausNode node = jausNodeCreate();
				node->id = nodeId;
			}

			node->subsystem = subs;
			
			jausArrayAdd(subs->nodes, node);
			return true;
		}
	}
	return false;
}

bool SystemTree::addSubsystem(JausSubsystem subs)
{
	return addSubsystem(subs->id, subs);
}

bool SystemTree::addSubsystem(JausAddress address, JausSubsystem subs)
{
	return addSubsystem(address->subsystem, subs);
}

bool SystemTree::addSubsystem(int subsystemId, JausSubsystem subs)
{
	if(!this->hasSubsystem(subsystemId))
	{
		// Test for valid ID
		if(subsystemId >= JAUS_MINIMUM_SUBSYSTEM_ID && subsystemId <= JAUS_MAXIMUM_SUBSYSTEM_ID)
		{
			if(subs)
			{
				subs = jausSubsystemClone(subs);
			}
			else
			{
				JausSubsystem subs = jausSubsystemCreate();
				subs->id = subsystemId;
			}
			
			this->system[subs->id] = subs;
			subsystemCount++;
			return true;
		}
	}
	return false;
}

bool SystemTree::removeNode(JausNode node)
{
	return removeNode(node->subsystem->id, node->id);
}

bool SystemTree::removeNode(JausAddress address)
{
	return removeNode(address->subsystem, address->node);
}

bool SystemTree::removeNode(int subsystemId, int nodeId)
{
	JausSubsystem subs = system[subsystemId];
	if(subs)
	{
		for(int i=0; i<subs->nodes->elementCount; i++)
		{
			JausNode node = (JausNode)subs->nodes->elementData[i];
			if(nodeId == node->id)
			{
				jausArrayRemoveAt(subs->nodes, i);
				jausNodeDestroy(node);
				return true;
			}
		}
	}
	return false;
}

bool SystemTree::removeSubsystem(JausSubsystem subs)
{
	return removeSubsystem(subs->id);
}

bool SystemTree::removeSubsystem(JausAddress address)
{
	return removeSubsystem(address->subsystem);
}

bool SystemTree::removeSubsystem(int subsystemId)
{
	JausSubsystem subs = system[subsystemId];
	if(subs)
	{
		system[subsystemId] = NULL;
		jausSubsystemDestroy(subs);
		subsystemCount--;
		return true;
	}
	return false;
}

bool SystemTree::removeComponent(JausComponent cmpt)
{
	return removeComponent(cmpt->address->subsystem, cmpt->address->node, cmpt->address->component, cmpt->address->instance);
}

bool SystemTree::removeComponent(JausAddress address)
{
	return removeComponent(address->subsystem, address->node, address->component, address->instance);
}

bool SystemTree::removeComponent(int subsystemId, int nodeId, int componentId, int instanceId)
{
	JausNode node = findNode(subsystemId, nodeId);
	if(node)
	{
		for(int i = 0; i < node->components->elementCount; i++)
		{
			JausComponent cmpt = (JausComponent) node->components->elementData[i];
			if(cmpt->address->component == componentId && cmpt->address->instance == instanceId)
			{
				jausArrayRemoveAt(node->components, i);
				jausComponentDestroy(cmpt);
				return true;
			}
		}
	}	
	return false;
}

bool SystemTree::replaceSubsystem(JausAddress address, JausSubsystem newSubs)
{
	return true;
}

bool SystemTree::replaceNode(JausAddress address, JausNode newNode)
{
	return replaceNode(address->subsystem, address->node, newNode);
}

bool SystemTree::replaceNode(int subsystemId, int nodeId, JausNode newNode)
{
	JausNode currentNode = findNode(subsystemId, nodeId);
	if(!currentNode)
	{
		// No node to replace, so add the newNode
		addNode(subsystemId, nodeId, newNode);
		return true;
	}

	JausNode cloneNode = jausNodeCreate();
	if(!cloneNode)
	{
		return false;
	}
	cloneNode->id = currentNode->id;
	cloneNode->identification = (char *) realloc(cloneNode->identification, strlen(currentNode->identification)+1);
	sprintf(cloneNode->identification, "%s", currentNode->identification);
	cloneNode->subsystem = currentNode->subsystem;
	
	for(int i = 0; i < newNode->components->elementCount; i++)
	{
		JausComponent newCmpt = (JausComponent)newNode->components->elementData[i];
		JausComponent addCmpt = findComponent(newCmpt);
		if(addCmpt)
		{
			addCmpt = jausComponentClone(addCmpt);
		}
		else
		{
			addCmpt = jausComponentCreate();
			addCmpt->address->subsystem = subsystemId;
			addCmpt->address->node = nodeId;
			addCmpt->address->component = newCmpt->address->component;
			addCmpt->address->instance = newCmpt->address->instance;
		}
		addCmpt->node = cloneNode;
		jausArrayAdd(cloneNode->components, addCmpt);
	}
	removeNode(subsystemId, nodeId);
	cloneNode->subsystem = system[subsystemId];
	jausArrayAdd(system[subsystemId]->nodes, cloneNode);
	return true;
}

//bool SystemTree::replaceComponent(JausAddress address, JausComponent newCmpt)
//{
//	JausComponent oldCmpt = findComponent(address->subsystem, address->node, address->component, address->instense);
//	if(oldCmpt)
//	{
//		// Ok, this component already exists in the table
//		// Copy data over from the old component to this new one
//	}
//	else
//	{
//		// This component isn't in the table! No need to replace, we'll just put a copy in there
//		addComponent(jausComponentClone(newCmpt));
//		return true;
//	}
//}

bool SystemTree::setSubsystemIdentification(JausAddress address, char *identification)
{
	JausSubsystem subs = system[address->subsystem];
	if(subs)
	{
		subs->identification = (char *) realloc(subs->identification, strlen(identification) + 1);
		if(subs->identification)
		{
			sprintf(subs->identification, "%s", identification);
			return true;
		}
	}
	return false;
}

bool SystemTree::setNodeIdentification(JausAddress address, char *identification)
{
	JausNode node = findNode(address);
	if(node)
	{
		node->identification = (char *) realloc(node->identification, strlen(identification) + 1);
		if(node->identification)
		{
			sprintf(node->identification, "%s", identification);
			return true;
		}
	}
	return false;
}

bool SystemTree::setComponentIdentification(JausAddress address, char *identification)
{
	JausComponent cmpt = findComponent(address);
	if(cmpt)
	{
		cmpt->identification = (char *) realloc(cmpt->identification, strlen(identification) + 1);
		if(cmpt->identification)
		{
			sprintf(cmpt->identification, "%s", identification);
			return true;
		}
	}
	return false;
}

bool SystemTree::setComponentServices(JausAddress address, JausArray inputServices)
{
	JausComponent cmpt = findComponent(address);
	if(cmpt)
	{
		// Remove current service set
		jausServicesDestroy(cmpt->services);
		cmpt->services = jausServicesDuplicate(inputServices);
		return true;
	}
	return false;
}

char *SystemTree::getSubsystemIdentification(JausSubsystem subsystem)
{
	return getSubsystemIdentification(subsystem->id);
}

char *SystemTree::getSubsystemIdentification(JausAddress address)
{
	return getSubsystemIdentification(address->subsystem);
}

char *SystemTree::getSubsystemIdentification(int subsId)
{
	JausSubsystem subs = system[subsId];
	if(subs)
	{
		return subs->identification;
	}
	else
	{
		return NULL;
	}
}

char *SystemTree::getNodeIdentification(JausNode node)
{
	return getNodeIdentification(node->subsystem->id, node->id);
}

char *SystemTree::getNodeIdentification(JausAddress address)
{
	return getNodeIdentification(address->subsystem, address->node);
}

char *SystemTree::getNodeIdentification(int subsId, int nodeId)
{
	JausNode node = findNode(subsId, nodeId);
	if(node)
	{
		return node->identification;
	}
	else
	{
		return NULL;
	}
}



//bool SystemTree::compareComponent(JausComponent component);
//bool SystemTree::compareNode(JausNode node);
//bool SystemTree::compareSubsystem(JausSubsystem subs);
//
//std::string SystemTree::toString();
//std::string SystemTree::toDetailedString();
//void SystemTree::refresh(JausAddress address);


