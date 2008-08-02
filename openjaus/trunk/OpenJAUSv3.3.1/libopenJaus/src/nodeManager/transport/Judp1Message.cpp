#include "nodeManager/transport/JudpMessage.h"
#include "nodeManager/transport/Judp1Message.h"

Judp1Message::Judp1Message()
{
	hcHeaderNumber = 0;
	hcLength = 0;
	hcFlags = 0;
	messageLength = 0;
	message = NULL;
	
	index = 0;
	buffer = NULL;
	bufferSizeBytes = 0;
}
	
Judp1Message::~Judp1Message(void)
{
	
}

int Judp1Message::getHcHeaderNumber(void)
{
	return hcHeaderNumber;
}

bool Judp1Message::setHcHeaderNumber(int hcHeaderNumber)
{
	return true;
}

int Judp1Message::getHcLength(void)
{
	return hcLength;
}

bool Judp1Message::setHcLength(int hcLength)
{
	return true;	
}


int Judp1Message::getHcFlags(void)
{
	return hcFlags;	
}

bool Judp1Message::setHcFlags(int hcFlags)
{
	
	return true;
}


int Judp1Message::getMessageLength(void)
{
	return messageLength;	
}

bool Judp1Message::setMessageLength(int messageLength)
{
	
	return true;
}


JausMessage Judp1Message::getJausMessage(void)
{
	return NULL;
}

bool Judp1Message::setJausMessage(JausMessage message)
{
	
	return true;
}


int Judp1Message::toBuffer(unsigned char *buffer, int bufferSizeBytes)
{
	return 0;
}

int Judp1Message::fromBuffer(unsigned char *buffer, int bufferSizeBytes)
{
	return 0;
}

int Judp1Message::getSizeBytes(void)
{
	return 0;
}
