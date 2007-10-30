#include "JausTransportData.h"
#include "JausTransportInterface.h"

JausTransportData::JausTransportData(void)
{
	this->data = NULL;
}

JausTransportData::~JausTransportData(void)
{
	if(this->data)
	{
		// TODO: Find a way to fix this Memory Leak
	}
}

JausTransportData::JausTransportData(JausTransportInterface *transport, TransportData data)
{
	this->data = data;
	this->transport = transport;
}

void JausTransportData::setInterface(JausTransportInterface *transport)
{
	this->transport = transport;
}

TransportData JausTransportData::getData()
{
	return this->data;
}

JausTransportInterface *JausTransportData::getInterface()
{
	return this->transport;
}

// Warning: This method could leak memory, if this->data is not NULL need to free it
void JausTransportData::setData(TransportData data)
{
	this->data = data;
}

