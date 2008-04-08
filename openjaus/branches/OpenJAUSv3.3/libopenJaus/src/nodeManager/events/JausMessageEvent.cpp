#include "nodeManager/events/JausMessageEvent.h"

JausMessageEvent::JausMessageEvent(JausMessage message, JausTransportInterface *transport, unsigned char direction)
{
	this->type = NodeManagerEvent::JausMessageEvent;
	this->message = message;
	this->transport = transport;
	this->direction = direction;
}

JausMessageEvent::~JausMessageEvent()
{
	if(message != NULL)
	{
		jausMessageDestroy(message);
	}
}

std::string JausMessageEvent::toString()
{
	char buf[1024] = {0};
	char addressString[80] = {0};

	if(direction == JausMessageEvent::Inbound)
	{
		sprintf(buf, "RECEIVED:");
	}

	if(direction == JausMessageEvent::Outbound)
	{
		sprintf(buf, "SENDING:");
	}

	jausAddressToString(this->message->source, addressString);
	sprintf(buf, "%s %s from %s", buf, jausMessageCommandCodeString(this->message), addressString);
	jausAddressToString(this->message->destination, addressString);
	sprintf(buf, "%s to %s on interface: %s", buf, addressString, this->transport->toString().c_str());

	return buf;
}

JausMessage JausMessageEvent::getJausMessage()
{
	return this->message;
}

JausTransportInterface *JausMessageEvent::getJausTransportInterface()
{
	return this->transport;
}

unsigned char JausMessageEvent::getMessageDirection()
{
	return this->direction;
}

