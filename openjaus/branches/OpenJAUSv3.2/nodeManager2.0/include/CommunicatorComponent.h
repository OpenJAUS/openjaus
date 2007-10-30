#ifndef COMMUNICATOR_COMPONENT_H
#define COMMUNICATOR_COMPONENT_H

#include "LocalComponent.h"
class JausComponentCommunicationManager;

class CommunicatorComponent : public LocalComponent
{
public:
	CommunicatorComponent(FileLoader *configData, JausComponentCommunicationManager *cmptComms);
	~CommunicatorComponent(void);

	bool processMessage(JausTransportPacket jtPacket);
	std::string toString();

private:
	bool processReportIdentification(JausTransportPacket jtPacket);
	bool processReportConfiguration(JausTransportPacket jtPacket);
	bool processReportServices(JausTransportPacket jtPacket);
	bool processReportHeartbeat(JausTransportPacket jtPacket);
	bool processCreateEvent(JausTransportPacket jtPacket);
	bool processCancelEvent(JausTransportPacket jtPacket);

	void startupState();
	void intializeState();
	void standbyState();
	void readyState();
	void emergencyState();
	void failureState();
	void shutdownState();
	void allState();
};

#endif
