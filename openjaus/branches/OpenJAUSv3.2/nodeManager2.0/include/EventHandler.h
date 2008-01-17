#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include "NodeManagerEvent.h"

class EventHandler
{
public:
	virtual void handleEvent(NodeManagerEvent *e) = 0;
	virtual ~EventHandler() {};
};

#endif

