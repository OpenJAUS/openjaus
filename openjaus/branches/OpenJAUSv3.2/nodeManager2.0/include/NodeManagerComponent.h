#ifndef NODE_MANAGER_COMPONENT_H
#define NODE_MANAGER_COMPONENT_H

#include "LocalComponent.h"
#include "JausTransportData.h"

#if defined(WIN32)
	#include <hash_map>
	#define HASH_MAP stdext::hash_map
#elif defined(__GNUC__)
	#include <ext/hash_map>
	#define HASH_MAP __gnu_cxx::hash_map
#else
	#error "Hash Map undefined in SystemTable.h."
#endif

class JausComponentCommunicationManager;
class SystemTree;

#define NM_RATE_HZ	20
#define MAXIMUM_EVENT_ID	255

class NodeManagerComponent : public LocalComponent
{
public:
	NodeManagerComponent(FileLoader *configData, JausComponentCommunicationManager *cmptComms);
	~NodeManagerComponent(void);

	bool processMessage(JausTransportPacket *jtPacket);
	std::string toString();

	JausAddress checkInLocalComponent(int cmptId, JausTransportData *data);
	void checkOutLocalComponent(JausAddress address);

private:
	bool processReportIdentification(JausTransportPacket *jtPacket);
	bool processReportConfiguration(JausTransportPacket *jtPacket);
	bool processReportServices(JausTransportPacket *jtPacket);
	bool processReportHeartbeatPulse(JausTransportPacket *jtPacket);
	bool processCreateEvent(JausTransportPacket *jtPacket);
	bool processCancelEvent(JausTransportPacket *jtPacket);
	bool processCreateServiceConnection(JausTransportPacket *jtPacket);
	bool processActivateServiceConnection(JausTransportPacket *jtPacket);
	bool processSuspendServiceConnection(JausTransportPacket *jtPacket);
	bool processTerminateServiceConnection(JausTransportPacket *jtPacket);
	bool processRequestComponentControl(JausTransportPacket *jtPacket);
	bool processQueryComponentAuthority(JausTransportPacket *jtPacket);
	bool processQueryComponentStatus(JausTransportPacket *jtPacket);
	bool processQueryHeartbeatPulse(JausTransportPacket *jtPacket);
	bool processQueryConfiguration(JausTransportPacket *jtPacket);
	bool processQueryIdentification(JausTransportPacket *jtPacket);
	bool processQueryServices(JausTransportPacket *jtPacket);
	bool processConfirmEvent(JausTransportPacket *jtPacket);

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
