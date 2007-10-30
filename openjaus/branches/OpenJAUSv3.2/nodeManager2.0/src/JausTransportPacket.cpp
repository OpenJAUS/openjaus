#include "JausTransportPacket.h"

JausTransportPacket::JausTransportPacket(void)
{
	this->message = NULL;
	this->data = new JausTransportData();
}

JausTransportPacket::~JausTransportPacket(void)
{
	if(this->message)
	{
		jausMessageDestroy(this->message);
		this->message = NULL;
	}
	delete this->data;
}

JausTransportPacket::JausTransportPacket(JausMessage message, JausTransportInterface *transport, TransportData data)
{
	this->message = message;
	this->data = new JausTransportData(transport, data);
}

void JausTransportPacket::setJausMessage(JausMessage message)
{
	if(this->message)
	{
		jausMessageDestroy(this->message);
	}
	this->message = message;
}

JausMessage JausTransportPacket::getJausMessage(void)
{
	return this->message;
}

void JausTransportPacket::setTransportInterface(JausTransportInterface *transport)
{
	this->data->setInterface(transport);
}

JausTransportInterface *JausTransportPacket::getTransportInterface(void)
{
	return this->data->getInterface();
}

JausTransportData *JausTransportPacket::getJausTransportData(void)
{
	return this->data;
}

