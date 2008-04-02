#ifndef COMMUNICATOR_COMPONENT_H
#define COMMUNICATOR_COMPONENT_H

#if defined(WIN32)
	#include <hash_map>
	#define HASH_MAP stdext::hash_map
#elif defined(__GNUC__)
	#include <ext/hash_map>
	#define HASH_MAP __gnu_cxx::hash_map
#else
	#error "Hash Map undefined in SystemTable.h."
#endif
#include "LocalComponent.h"

#define MAXIMUM_EVENT_ID	255
#define COMMUNICATOR_RATE_HZ 10

class SystemTree;
class JausComponentCommunicationManager;

class CommunicatorComponent : public LocalComponent
{
public:
	CommunicatorComponent(FileLoader *configData, EventHandler *handler, JausComponentCommunicationManager *cmptComms);
	~CommunicatorComponent(void);

	bool processMessage(JausMessage message);
	std::string toString();

private:
	bool processReportIdentification(JausMessage message);
	bool processReportConfiguration(JausMessage message);
	bool processReportServices(JausMessage message);
	bool processReportHeartbeatPulse(JausMessage message);
	bool processCreateEvent(JausMessage message);
	bool processCancelEvent(JausMessage message);
	bool processCreateServiceConnection(JausMessage message);
	bool processActivateServiceConnection(JausMessage message);
	bool processSuspendServiceConnection(JausMessage message);
	bool processTerminateServiceConnection(JausMessage message);
	bool processRequestComponentControl(JausMessage message);
	bool processQueryComponentAuthority(JausMessage message);
	bool processQueryComponentStatus(JausMessage message);
	bool processQueryHeartbeatPulse(JausMessage message);
	bool processQueryConfiguration(JausMessage message);
	bool processQueryIdentification(JausMessage message);
	bool processQueryServices(JausMessage message);
	bool processConfirmEvent(JausMessage message);

	void sendNodeChangedEvents();
	void sendSubsystemChangedEvents();
	void generateHeartbeats();
	
	bool sendQueryNodeIdentification(JausAddress address);
	bool sendQuerySubsystemIdentification(JausAddress address);
	bool sendQueryComponentIdentification(JausAddress address);
	
	bool sendQueryNodeConfiguration(JausAddress address, bool createEvent);
	bool sendQuerySubsystemConfiguration(JausAddress address, bool createEvent);
	bool sendQueryComponentServices(JausAddress address);

	void startupState();
	void intializeState();
	void standbyState();
	void readyState();
	void emergencyState();
	void failureState();
	void shutdownState();
	void allState();

	int getNextEventId();

	HASH_MAP <int, JausAddress> nodeChangeList;
	HASH_MAP <int, JausAddress> subsystemChangeList;
	bool eventId[255];
	SystemTree *systemTree;
};

#endif
