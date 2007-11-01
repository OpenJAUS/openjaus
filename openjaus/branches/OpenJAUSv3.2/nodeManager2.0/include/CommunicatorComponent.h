#ifndef COMMUNICATOR_COMPONENT_H
#define COMMUNICATOR_COMPONENT_H

#include "LocalComponent.h"
class JausComponentCommunicationManager;

class CommunicatorComponent : public LocalComponent
{
public:
	CommunicatorComponent(FileLoader *configData, JausComponentCommunicationManager *cmptComms);
	~CommunicatorComponent(void);

	bool processMessage(JausMessage message);
	std::string toString();

private:
	bool processReportIdentification(JausMessage message);
	bool processReportConfiguration(JausMessage message);
	bool processReportServices(JausMessage message);
	bool processReportHeartbeat(JausMessage message);
	bool processCreateEvent(JausMessage message);
	bool processCancelEvent(JausMessage message);

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
