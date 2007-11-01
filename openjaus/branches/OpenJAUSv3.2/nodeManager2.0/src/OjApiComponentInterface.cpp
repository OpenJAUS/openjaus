#include "OjApiComponentInterface.h"
#include "JausComponentCommunicationManager.h"
#include "NodeManagerComponent.h"
#include "jaus.h"

OjApiComponentInterface::OjApiComponentInterface(FileLoader *configData, JausComponentCommunicationManager *cmptComms)
{
	this->type = COMPONENT_INTERFACE;
	this->commMngr = cmptComms;
	this->name = OJ_API_NAME;
	
	this->configData = configData;

	// Register ourselves on our queue
	this->queue.registerMonitor(this);

	// Setup our pThread
	this->setupThread();
}

OjApiComponentInterface::~OjApiComponentInterface(void){}

bool OjApiComponentInterface::processMessage(JausTransportPacket *jtPacket)
{
	// Retrieve the transportData object from the list
	OjApiComponentTransportData transportData = NULL; //transportDataList[jausAddressHash(jtPacket->getJausMessage()->destination)].getData();

	// Send it off to the callback function
	if(transportData && transportData->messageParser)
	{
		transportData->messageParser(jtPacket->getJausMessage());
		return true;
	}
	else 
	{
		return false;
	}
}

JausAddress OjApiComponentInterface::checkIn(int cmptId, void messageParser(JausMessage))
{
	JausTransportData *data = new JausTransportData();

	// Create the TransportData structure and populate it
	OjApiComponentTransportData transportData;
	transportData = (OjApiComponentTransportData) malloc(sizeof(OjApiComponentTransportDataStruct));
	if(!transportData)
	{
		return NULL;
	}
	transportData->messageParser = messageParser;
	
	// Setup the JausTransportData object
	data->setInterface(this);
	data->setData((TransportData) transportData);
	
	// Check-in through the Node Manager
	return ((JausComponentCommunicationManager *)(this->commMngr))->getNodeManagerComponent()->checkInLocalComponent(cmptId, data);
}

void OjApiComponentInterface::checkout(JausAddress address)
{
	NodeManagerComponent *nm = ((JausComponentCommunicationManager *)(this->commMngr))->getNodeManagerComponent();
	nm->checkOutLocalComponent(address);
}

bool OjApiComponentInterface::verifyAddress(JausAddress address)
{
	return this->commMngr->getSystemTree()->hasComponent(address);
}

JausAddress OjApiComponentInterface::lookupJausEntities(JausAddress addressPattern)
{
	//return this->commMngr->getSystemTree()->lookUpAddressInSystem(addressPattern);
	return NULL;
}

JausAddress OjApiComponentInterface::lookupService(int commandCode, int serviceType)
{
	return this->commMngr->getSystemTree()->lookUpServiceInSystem(commandCode, serviceType);
}

bool OjApiComponentInterface::sendJausMessage(JausMessage txMessage)
{
	//this->commMngr->routeJausMessage(new JausTransportPacket(txMessage, this, this->commMngr->getSystemTree()->getTransportData(txMessage->source)->getData()));
	return true;
}

void OjApiComponentInterface::queueEmpty() {}
void OjApiComponentInterface::queueFull() {}

void OjApiComponentInterface::queueNewItem()
{
	// Wake up our pThread
	wakeThread();
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
			processMessage(queue.pop());
		}
	}
	pthread_mutex_unlock(&threadMutex);
}

