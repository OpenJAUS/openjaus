#ifndef NM_EVENT_H
#define NM_EVENT_H

#include <string>

#ifdef WIN32
	#define EXPORT	__declspec(dllexport)
#else
	#define EXPORT
#endif

class NodeManagerEvent
{
	
public:
	EXPORT enum {SystemTreeEvent, ErrorEvent, TransportEvent, JausMessageEvent};
	EXPORT unsigned int getType();
	EXPORT virtual std::string toString();
	EXPORT virtual ~NodeManagerEvent() = 0;

protected:
	unsigned int type;

};

#endif

