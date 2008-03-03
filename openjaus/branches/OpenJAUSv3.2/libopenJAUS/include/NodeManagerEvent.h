#ifndef NM_EVENT_H
#define NM_EVENT_H

#include <string>

class NodeManagerEvent
{
public:
	enum {SystemTreeEvent, ErrorEvent, TransportEvent};
	unsigned int getType();
	virtual std::string toString();
	virtual ~NodeManagerEvent() = 0;

protected:
	unsigned int type;

};

#endif

