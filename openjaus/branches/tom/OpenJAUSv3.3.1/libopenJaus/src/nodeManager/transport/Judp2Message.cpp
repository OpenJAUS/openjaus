#include "nodeManager/transport/JudpMessage.h"
#include "nodeManager/transport/Judp1Message.h"
#include "nodeManager/transport/Judp2Message.h"

Judp2Message::Judp2Message()
{
	messageType = JUDP2_TRANSPORT_TYPE;
	hcFlags = 0;
	dataSize = 14;
	hcNumber = 0;
	hcLength = 0;
	priority = 1;
	broadcast = 0;
	ackNak = 0;
	dataFlags = 0;
	destinationId = 0;
	sourceId = 0;
	payload = NULL;
	sequenceNumber = 0;
	
	payloadBuffer = NULL;

}

Judp2Message::~Judp2Message(void)
{

}

int Judp2Message::getMessageType(void)
{
	return messageType;
}

bool Judp2Message::setMessageType(int messageType)
{
	return true;
}

int Judp2Message::getHcFlags(void)
{
	return hcFlags;
}

bool Judp2Message::setHcFlags(int hcFlags)
{
	return true;
}

int Judp2Message::getDataSize(void)
{
	return dataSize;
}

bool Judp2Message::setDataSize(int dataSize)
{
	return true;
}

int Judp2Message::getHcNumber(void)
{
	return hcNumber;
}

bool Judp2Message::setHcNumber(int hcNumber)
{
	return true;
}

int Judp2Message::getHcLength(void)
{
	return hcLength;
}

bool Judp2Message::setHcLength(int hcLength)
{
	return true;
}

int Judp2Message::getPriority(void)
{
	return priority;
}

bool Judp2Message::setPriority(int priority)
{
	return true;
}

int Judp2Message::getBroadcast(void)
{
	return broadcast;
}

bool Judp2Message::setBroadcast(int priority)
{
	return true;
}

int Judp2Message::getAckNak(void)
{
	return ackNak;
}

bool Judp2Message::setAckNak(int ackNak)
{
	return true;
}

int Judp2Message::getDataFlags(void)
{
	return dataFlags;
}

bool Judp2Message::setDataFlags(int dataFlags)
{
	return true;
}

int Judp2Message::getDestinationId(void)
{
	return destinationId;
}

bool Judp2Message::setDestinationId(int destinationId)
{
	return true;
}

int Judp2Message::getSourceId(void)
{
	return sourceId;
}

bool Judp2Message::setSourceId(int sourceId)
{
	return true;
}

Transportable* Judp2Message::getPayload(void)
{
	return payload;
}

bool Judp2Message::setPayload(Transportable *payload)
{
	return true;
}

int Judp2Message::getSequenceNumber(void)
{
	return sequenceNumber;
}

bool Judp2Message::setSequenceNumber(int sequenceNumber)
{
	return true;
}

int Judp2Message::toBuffer(unsigned char *buffer, int bufferSizeBytes)
{
	return 0;
	
}

int Judp2Message::fromBuffer(unsigned char *buffer, int bufferSizeBytes)
{
	int index = 0;
	
	messageType = buffer[index] >> 2;
	hcFlags = (buffer[index++] & 0x03);
	dataSize =  buffer[index+1] << 8 + buffer[index];
	index += 2;
	if(hcFlags != 0)
	{	
		hcNumber = buffer[index++];
		hcLength = buffer[index++];
	}
	
	priority = buffer[index] >> 6;
	broadcast = (buffer[index] >> 4) & 0x03;
	ackNak = (buffer[index] >> 2) & 0x03;
	dataFlags =	buffer[index++] & 0x03;
	
	memcpy(&destinationId, buffer + index, 4);
	index += 4;
	
	memcpy(&sourceId, buffer + index, 4);
	index += 4;	

	payloadBuffer = buffer + index;
	
	index = dataSize - 2;
	
	memcpy(&sequenceNumber, buffer + index, 2);
	index += 4;
	
	return index;
}

int Judp2Message::getSizeBytes(void)
{
	return dataSize;
}
