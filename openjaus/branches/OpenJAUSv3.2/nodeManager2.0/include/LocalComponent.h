#ifndef LOCAL_COMPONENT_H
#define LOCAL_COMPONENT_H

#include "JausTransportInterface.h"
#include "jaus.h"

class LocalComponent : public JausTransportInterface
{
protected:
	JausComponent cmpt;
	double cmptRateHz;
	virtual void startupState() = 0;
	virtual void intializeState() = 0;
	virtual void standbyState() = 0;
	virtual void readyState() = 0;
	virtual void emergencyState() = 0;
	virtual void failureState() = 0;
	virtual void shutdownState() = 0;
	virtual void allState() = 0;

	void queueEmpty();
	void queueFull();
	void queueNewItem();

public:
	void run();

};

#endif
