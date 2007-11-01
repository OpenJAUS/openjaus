#ifndef OJ_API_INTERFACE_H
#define OJ_API_INTERFACE_H

#include "JausTransportInterface.h"
#include "NodeManagerComponent.h"

#define OJ_API_NAME "OpenJAUS API Component Interface"

// Transport Data Structure
typedef struct
{
	void (*messageParser)(JausMessage);
}OjApiComponentTransportDataStruct;

typedef OjApiComponentTransportDataStruct *OjApiComponentTransportData;

class OjApiComponentInterface : public JausTransportInterface
{
public:
	OjApiComponentInterface(FileLoader *configData, JausComponentCommunicationManager *cmptMngr);
	~OjApiComponentInterface(void);

	bool routeMessage(JausMessage message);
	JausAddress checkIn(int cmptId, void messageParser(JausMessage));
	void checkout(JausAddress address);
	bool verifyAddress(JausAddress addressPattern);
	JausAddress lookupJausEntities(JausAddress addressPattern);
	JausAddress lookupService(int commandCode, int serviceType);
	bool sendJausMessage(JausMessage txMessage);

	void queueEmpty();
	void queueFull();
	void queueNewItem();
	std::string toString();

	void run();
};

#endif
