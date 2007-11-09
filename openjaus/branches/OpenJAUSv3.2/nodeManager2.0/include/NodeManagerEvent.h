#ifndef NM_EVENT_H
#define NM_EVENT_H

#include <string>

class NodeManagerEvent
{
public:
	enum {SystemTreeEvent, ErrorEvent, TransportEvent};
	unsigned int getType();
	virtual std::string toString();

protected:
	unsigned int type;

};


#endif
