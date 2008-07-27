#include "nodeManager/transport/JudpMessage.h"
#include "nodeManager/transport/Judp1Message.h"
#include "nodeManager/transport/Judp2Message.h"

Judp2Message::Judp2Message(unsigned char *buffer)
{
	this->buffer = buffer;
	this->index = 0;
}

Judp2Message::~Judp2Message(void)
{

}

JausAddress Judp2Message::getSourceAddress(void)
{
	return NULL;
}

JausAddress Judp2Message::getDestinationAddress(void)
{
	return NULL;
}

int Judp2Message::getMessageType(void)
{
	return JUDP_TRANSPORT_TYPE;	// TODO: Placeholder. This needs to be determined from data 
}

char* Judp2Message::getPayloadBuffer(void)
{
	return NULL;
}

JausMessage Judp2Message::toJausMessage(void)
{
	return NULL;
}
