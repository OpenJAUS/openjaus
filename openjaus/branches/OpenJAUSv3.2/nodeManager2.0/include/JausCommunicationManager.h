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
#include "JausTransportPacket.h"
#include "JausQueueMonitor.h"
#include "JausTransportInterface.h"
#include "FileLoader.h"
#include "MessageRouter.h"
#include "SystemTree.h"

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
	virtual void routeJausMessage(JausTransportPacket *jtPacket);
	MessageRouter *getMessageRouter();

protected:
	int jausAddressHash(JausAddress address);

	MessageRouter *msgRouter;
	std::vector <JausTransportInterface> interfaces;
	HASH_MAP<int, JausTransportData *> transportDataList;
	FileLoader *configData;
	SystemTree *systemTree;
	bool enabled;
};

#endif
