#include "nodeManager/transport/JudpMessage.h"
#include "nodeManager/transport/Judp1Message.h"

Judp1Message::Judp1Message(unsigned char *buffer)
{
	this->buffer = buffer;
	this->index = 0;
}

Judp1Message::~Judp1Message(void)
{

}

JausAddress Judp1Message::getSourceAddress(void)
{
	return NULL;
}

JausAddress Judp1Message::getDestinationAddress(void)
{
	return NULL;
}

int Judp1Message::getMessageType(void)
{
	return JUDP_JAUS_MESSAGE_TYPE;	// Only JAUS message type supported by JUDP 1.0 
}

char* Judp1Message::getPayloadBuffer(void)
{
	return NULL;
}

JausMessage Judp1Message::toJausMessage(void)
{
	return NULL;
}
