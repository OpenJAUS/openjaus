#ifndef JAUS_COMMUNICATION_MANAGER
#define JAUS_COMMUNICATION_MANAGER

#ifdef WIN32
	#include <errno.h>
	#include <hash_map>
	#define HASH_MAP stdext::hash_map
#elif defined(__GNUC__)
	#include <ext/hash_map>
	#define HASH_MAP __gnu_cxx::hash_map
#endif

#include <vector>
#include "JausTransportInterface.h"
#include "utils/FileLoader.h"
#include "MessageRouter.h"
#include "SystemTree.h"
#include "EventHandler.h"

class JausCommunicationManager
{
public:
	JausCommunicationManager(void);
	virtual ~JausCommunicationManager(void);
	
	unsigned long getInterfaceCount(void);
	JausTransportInterface *getJausInterface(unsigned long index);
	JausTransportInterface *getJausInterface(std::string interfaceName);
	bool interfaceExists(std::string interfaceName);
	void enable(void);
	void disable(void);
	bool isEnabled(void);
	SystemTree *getSystemTree();
	virtual bool sendJausMessage(JausMessage message);
	virtual bool receiveJausMessage(JausMessage message, JausTransportInterface *jtInterface);
	MessageRouter *getMessageRouter();

protected:
	MessageRouter *msgRouter;
	std::vector <JausTransportInterface *> interfaces;
	HASH_MAP<int, JausTransportInterface *> interfaceMap;
	FileLoader *configData;
	SystemTree *systemTree;
	EventHandler *handler;
	int mySubsystemId;
	int myNodeId;
	bool enabled;
};

#endif
