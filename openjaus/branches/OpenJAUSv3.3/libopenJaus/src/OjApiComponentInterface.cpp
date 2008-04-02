#include "OjApiComponentInterface.h"
#include "JausComponentCommunicationManager.h"
#include "NodeManagerComponent.h"
#include "jaus.h"

OjApiComponentInterface::OjApiComponentInterface(FileLoader *configData, EventHandler *handler, JausComponentCommunicationManager *cmptComms)
{
	this->type = COMPONENT_INTERFACE;
	this->eventHandler = handler;
	this->commMngr = cmptComms;
	this->name = OJ_API_NAME;
	
	this->configData = configData;

	// Setup our pThread
	this->setupThread();
}

OjApiComponentInterface::~OjApiComponentInterface(void){}

bool OjApiComponentInterface::routeMessage(JausMessage message)
{
	// Retrieve the transportData object from the list
	OjApiComponentTransportData transportData = NULL; //transportDataList[jausAddressHash(jtPacket->getJausMessage()->destination)].getData();

	// Send it off to the callback function
	if(transportData && transportData->messageParser)
	{
		transportData->messageParser(message);
		return true;
	}
	else 
	{
		return false;
	}
}

JausAddress OjApiComponentInterface::checkIn(int cmptId, void messageParser(JausMessage))
{
	NodeManagerComponent *nm = ((JausComponentCommunicationManager *)(this->commMngr))->getNodeManagerComponent();
	JausAddress cmptAddress = nm->checkInLocalComponent(cmptId);

	if(jausAddressIsValid(cmptAddress))
	{
		// Add this to my transport list
		OjApiComponentTransportData transportData = (OjApiComponentTransportData) calloc(1, sizeof(OjApiComponentTransportDataStruct));
		if(!transportData)
		{
			// Failed
			return NULL;
		}
		transportData->messageParser = messageParser;

		transportMap[jausAddressHash(cmptAddress)] = transportData;
		return cmptAddress;
	}
	else
	{
		return NULL;
	}
}

void OjApiComponentInterface::checkout(JausAddress address)
{
	NodeManagerComponent *nm = ((JausComponentCommunicationManager *)(this->commMngr))->getNodeManagerComponent();
	nm->checkOutLocalComponent(address);

	transportMap[jausAddressHash(address)] = NULL;
}

bool OjApiComponentInterface::verifyAddress(JausAddress address)
{
	return this->commMngr->getSystemTree()->hasComponent(address);
}

JausAddress OjApiComponentInterface::lookupJausEntities(JausAddress addressPattern)
{
	return this->commMngr->getSystemTree()->lookUpAddress(addressPattern);
}

JausAddress OjApiComponentInterface::lookupService(int commandCode, int serviceType)
{
	return this->commMngr->getSystemTree()->lookUpServiceInSystem(commandCode, serviceType);
}

bool OjApiComponentInterface::sendJausMessage(JausMessage txMessage)
{
	this->commMngr->receiveJausMessage(txMessage, this);
	return true;
}

std::string OjApiComponentInterface::toString()
{
	return this->name;
}

void OjApiComponentInterface::run()
{
	// Lock our mutex
	pthread_mutex_lock(&threadMutex);

	// There is no system-level queue to check in this thread (i.e. UDP Buffer or Serial buffer)
	// We will just sleep for long lengths of time waiting on a wakeThread call
	while(this->running)
	{
		pthread_cond_wait(&threadConditional, &threadMutex);
		
		// Check the send queue
		while(!this->queue.isEmpty())
		{
			// Pop a packet off the queue and send it off
			routeMessage(queue.pop());
		}
	}
	pthread_mutex_unlock(&threadMutex);
}

