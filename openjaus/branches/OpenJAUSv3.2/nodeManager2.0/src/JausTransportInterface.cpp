#include "JausTransportInterface.h"
#include "JausCommunicationManager.h"

JausTransportInterface::JausTransportInterface(void) {}

JausTransportInterface::~JausTransportInterface(void) {}

std::string JausTransportInterface::getName()
{
	return this->name;
}

JausCommunicationManager *JausTransportInterface::getCommunicationManager()
{
	return this->commMngr;
}

void JausTransportInterface::setCommunicationManager(JausCommunicationManager *commMngr)
{
	this->commMngr = commMngr;
}

bool JausTransportInterface::isRunning()
{
	return this->running;
}

void JausTransportInterface::stopThread()
{
	this->running = false;
	wakeThread();
}

void JausTransportInterface::wakeThread()
{
	pthread_cond_signal(&threadConditional);
}

void JausTransportInterface::setupThread()
{
	pthread_cond_init(&threadConditional, NULL);
	pthread_mutex_init(&threadMutex, NULL);
	pthread_attr_init(&this->threadAttributes);
	pthread_attr_setdetachstate(&this->threadAttributes, PTHREAD_CREATE_DETACHED);

	this->pThreadId = pthread_create(&this->pThread, &this->threadAttributes, ThreadRun, this);
}

JausTransportType JausTransportInterface::getType(void)
{
	return this->type;
}

unsigned long JausTransportInterface::queueSize()
{
	return this->queue.size();
}

bool JausTransportInterface::routeMessage(JausMessage message)
{
	// Should never be used!
	// TODO: Throw exception. Log Error.
	return false;
}

void JausTransportInterface::queueJausMessage(JausMessage message)
{
	this->queue.push(message);
	
	if(pthread_mutex_trylock(&threadMutex) != EBUSY)
	{
		wakeThread();
	}
}

void JausTransportInterface::run()
{
	// Should never be used!
}

std::string JausTransportInterface::toString()
{
	return "I should never be called!";
}

void *ThreadRun(void *obj)
{
	JausTransportInterface *jtInterface = (JausTransportInterface *)obj;
	jtInterface->run();
	return NULL;
}



