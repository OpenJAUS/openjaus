#include "nodeManager/JausTransportInterface.h"
#include "nodeManager/JausCommunicationManager.h"

JausTransportInterface::JausTransportInterface(void){}

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

void JausTransportInterface::setupThread()
{
	int retVal;
	
	// TODO: Check for errors
	retVal = pthread_cond_init(&this->threadConditional, NULL);
	pthread_mutex_init(&this->threadMutex, NULL);
	pthread_attr_init(&this->threadAttributes);
	pthread_attr_setdetachstate(&this->threadAttributes, PTHREAD_CREATE_DETACHED);

	this->running = true;
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

bool JausTransportInterface::processMessage(JausMessage message)
{
	// Should never be used!
	// TODO: Throw exception. Log Error.

	// Force Segfault
	abort();

	return false;
}

void JausTransportInterface::queueJausMessage(JausMessage message)
{
	this->queue.push(message);
	wakeThread();
}

void JausTransportInterface::wakeThread()
{
	pthread_cond_signal(&this->threadConditional);
}

void JausTransportInterface::run()
{
	// Should never be used!
	printf("JausTransportInterface::run should never be used\n");
	
	// Force Segfault
	abort();
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

