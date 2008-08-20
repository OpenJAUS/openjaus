#include "nodeManager/transport/JudpMessage.h"
#include "nodeManager/transport/Judp1Message.h"
#include "nodeManager/transport/Judp2Message.h"

Judp2Message::Judp2Message()
{
	messageType = JUDP2_TRANSPORT_TYPE;
	hcFlags = 0;
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
	this->messageType = messageType;
	return true;
}

int Judp2Message::getHcFlags(void)
{
	return hcFlags;
}

bool Judp2Message::setHcFlags(int hcFlags)
{
	this->hcFlags = hcFlags;
	return true;
}

int Judp2Message::getDataSize(void)
{
	return getSizeBytes();
}

int Judp2Message::getHcNumber(void)
{
	return hcNumber;
}

bool Judp2Message::setHcNumber(int hcNumber)
{
	this->hcNumber = hcNumber;
	return true;
}

int Judp2Message::getHcLength(void)
{
	return hcLength;
}

bool Judp2Message::setHcLength(int hcLength)
{
	this->hcLength = hcLength;
	return true;
}

int Judp2Message::getPriority(void)
{
	return priority;
}

bool Judp2Message::setPriority(int priority)
{
	this->priority = priority;
	return true;
}

int Judp2Message::getBroadcast(void)
{
	return broadcast;
}

bool Judp2Message::setBroadcast(int broadcast)
{
	this->broadcast = broadcast;
	return true;
}

int Judp2Message::getAckNak(void)
{
	return ackNak;
}

bool Judp2Message::setAckNak(int ackNak)
{
	this->ackNak = ackNak;
	return true;
}

int Judp2Message::getDataFlags(void)
{
	return dataFlags;
}

bool Judp2Message::setDataFlags(int dataFlags)
{
	this->dataFlags = dataFlags;
	return true;
}

int Judp2Message::getDestinationId(void)
{
	return destinationId;
}

bool Judp2Message::setDestinationId(int destinationId)
{
	this->destinationId = destinationId;
	return true;
}

int Judp2Message::getSourceId(void)
{
	return sourceId;
}

bool Judp2Message::setSourceId(int sourceId)
{
	this->sourceId = sourceId;
	return true;
}

Transportable* Judp2Message::getPayload(void)
{
	return payload;
}

bool Judp2Message::setPayload(Transportable *payload)
{
	this->payload = payload;
	return true;
}

int Judp2Message::getSequenceNumber(void)
{
	return sequenceNumber;
}

bool Judp2Message::setSequenceNumber(int sequenceNumber)
{
	this->sequenceNumber = sequenceNumber;
	return true;
}

int Judp2Message::toBuffer(unsigned char *buffer, int bufferSizeBytes)
{
	int index = 0;
	int dataSize = getSizeBytes();

	if(bufferSizeBytes >= getSizeBytes())
	{
		buffer[index] = (unsigned char) messageType << 2;
		buffer[index++] += (unsigned char) (hcFlags & 0x3F);
		buffer[index++] = (unsigned char) (dataSize & 0xFF);
		buffer[index++] = (unsigned char) ((dataSize >> 8) & 0xFF);
		if(hcFlags != 0)
		{	
			buffer[index++] = hcNumber; 
			buffer[index++] = hcLength;
		}
		buffer[index++] = (priority << 6) | ((broadcast & 0x03) << 4) | ((ackNak & 0x03) << 2) | (dataFlags & 0x03);
		
		memcpy(buffer + index, &destinationId, 4);
		index += 4;
		
		memcpy(buffer + index, &sourceId, 4);
		index += 4;		
	
		index += payload->toBuffer(buffer + index, bufferSizeBytes - index);
		
		memcpy(buffer + index, &sequenceNumber, 2);
		index += 2;
	}

	return index;
}

int Judp2Message::fromBuffer(unsigned char *buffer, int bufferSizeBytes)
{
	int index = 0;
	int dataSize = 0;
	
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
	index += 2;
	
	return index;
}

int Judp2Message::getSizeBytes(void)
{
	int index = 14;
	
	if(hcFlags != 0)
	{
		index += 2;
	}
	
	index += payload->getSizeBytes();
	
	return index;
}
