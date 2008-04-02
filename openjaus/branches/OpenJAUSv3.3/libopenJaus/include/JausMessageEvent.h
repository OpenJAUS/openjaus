#ifndef JAUS_MESSAGE_EVENT_H
#define JAUS_MESSAGE_EVENT_H

#include <string>
#include "NodeManagerEvent.h"
#include "JausTransportInterface.h"

class JausMessageEvent : public NodeManagerEvent
{
public:
	JausMessageEvent(JausMessage message, JausTransportInterface *transport, unsigned char direction);
	~JausMessageEvent();

	std::string toString();
	JausMessage getJausMessage();
	JausTransportInterface *getJausTransportInterface();
	unsigned char getMessageDirection();

	enum{Inbound, Outbound};

private:
	unsigned char direction;
	JausMessage message;
	JausTransportInterface *transport;
};

#endif
