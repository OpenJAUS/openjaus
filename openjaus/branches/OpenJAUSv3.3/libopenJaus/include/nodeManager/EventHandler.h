#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include "nodeManager/events/NodeManagerEvent.h"

#if defined(__GNUC__)
	#define __FUNCTION__ __PRETTY_FUNCTION__
#endif

class EventHandler
{
public:
	virtual void handleEvent(NodeManagerEvent *e) = 0;
	virtual ~EventHandler() {};
};

#endif
