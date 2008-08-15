#include "nodeManager/transport/JudpMessage.h"
#include "nodeManager/transport/Judp1Message.h"
#include "nodeManager/transport/Judp2Message.h"

Judp2Message::Judp2Message()
{
}

Judp2Message::~Judp2Message(void)
{

}

int Judp2Message::getMessageType(void)
{
	return 2;
}

int Judp2Message::toBuffer(unsigned char *buffer, int bufferSizeBytes)
{
	return 0;
	
}

int Judp2Message::fromBuffer(unsigned char *buffer, int bufferSizeBytes)
{
	return 0;
	
}

int Judp2Message::getSizeBytes(void)
{
	return 0;
}
