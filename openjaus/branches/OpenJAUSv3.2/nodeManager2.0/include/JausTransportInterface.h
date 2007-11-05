#ifndef JAUS_TRANSPORT_INTERFACE
#define JAUS_TRANSPORT_INTERFACE

#ifdef WIN32
	#include "pthread.h"	
#elif defined(__GNUC__)
	#include <pthread.h>
	#include <errno.h>
#endif

#include <string>
#include "JausTransportQueue.h"
#include "SystemTree.h"
#include "FileLoader.h"
#include "jaus.h"


typedef enum JausTransportType {UNKNOWN_INTERFACE, SUBSYSTEM_INTERFACE, NODE_INTERFACE, COMPONENT_INTERFACE};

class JausCommunicationManager;

extern "C" void *ThreadRun(void *);

class JausTransportInterface
{
public:
	JausTransportInterface(void);
	virtual ~JausTransportInterface(void);

	std::string getName();
	JausCommunicationManager *getCommunicationManager();
	void setCommunicationManager(JausCommunicationManager *commMngr);

	bool isRunning();
	void stopThread();

	JausTransportType getType(void);
	unsigned long queueSize();
	void queueJausMessage(JausMessage message);

	virtual bool processMessage(JausMessage message);
	virtual std::string toString();
	virtual void run();

protected:
	void setupThread();
	void wakeThread();

	std::string name;
	JausTransportType type;
	JausTransportQueue queue;
	bool running;
	JausCommunicationManager *commMngr;
	FileLoader *configData;
	int pThreadId;
	pthread_t pThread;
	pthread_attr_t threadAttributes;
	pthread_cond_t threadConditional;
	pthread_mutex_t threadMutex;
};

#endif
