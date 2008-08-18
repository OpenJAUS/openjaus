#include "nodeManager/transport/JudpMessage.h"
#include "nodeManager/transport/Judp1Message.h"

Judp1Message::Judp1Message()
{
	hcHeaderNumber = 0;
	hcLength = 0;
	hcFlags = JUDP1_MESSAGE_HC_NO_COMPRESSION;
	messageLength = 0;
	header = NULL;
	jausData = NULL;
	message = NULL;
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
	this->hcHeaderNumber = hcHeaderNumber; 
	return true;
}

int Judp1Message::getHcLength(void)
{
	return hcLength;
}

bool Judp1Message::setHcLength(int hcLength)
{
	this->hcLength = hcLength;
	return true;	
}

int Judp1Message::getHcFlags(void)
{
	return hcFlags;	
}

bool Judp1Message::setHcFlags(int hcFlags)
{
	this->hcFlags = hcFlags;
	return true;
}

int Judp1Message::getMessageLength(void)
{
	return messageLength;	
}

bool Judp1Message::setMessageLength(int messageLength)
{
	this->messageLength = messageLength;
	return true;
}

unsigned char * Judp1Message::getHeader(void)
{
	return header;	
}

bool Judp1Message::setHeader(unsigned char *header)
{
	this->messageLength = messageLength;
	return true;
}

JausMessage Judp1Message::getJausMessage(void)
{
	unsigned char *fullBuffer = NULL;
	
	switch(hcFlags)
	{
		case JUDP1_MESSAGE_HC_COMPRESSION_ACKNOWLEDGE:
			return 0;
			
		case JUDP1_MESSAGE_HC_COMPRESSED_MESSAGE:
			if(header && jausData)
			{
				fullBuffer = (unsigned char *)malloc(hcLength + messageLength);
				memcpy(fullBuffer, header, hcLength);
				memcpy(fullBuffer + hcLength, jausData, messageLength);
				jausMessageFromBuffer(message, fullBuffer, hcLength + messageLength);
				free(fullBuffer);
			}
			break;
			
		default:
			break;
	}

	return message;
}

bool Judp1Message::setJausMessage(JausMessage message)
{
	this->message = message;
	return true;
}

int Judp1Message::toBuffer(unsigned char *buffer, int bufferSizeBytes)
{
	int index = 0;

	if(bufferSizeBytes >= getSizeBytes())
	{
		buffer[index++] = (unsigned char) (hcHeaderNumber);
		buffer[index++] = (unsigned char) (((hcLength & 0x3F) << 6) | (hcFlags & 0x03));
		// NOTE: The messageLength member is BIG ENDIAN, this is different for other JAUS messages
		buffer[index++] = (unsigned char) ((messageLength & 0xFF00) >> 8);
		buffer[index++] = (unsigned char) (messageLength & 0xFF);
		
		index += jausMessageToBuffer(message, buffer + index, bufferSizeBytes - index);
	}

	return index;
}

int Judp1Message::fromBuffer(unsigned char *buffer, int bufferSizeBytes)
{
	int index = 0;
	
	hcHeaderNumber = buffer[index++];
	hcLength = (buffer[index] >> 2) & 0x3F;
	hcFlags = (buffer[index++] & 0x03);
	messageLength =  buffer[index++] << 8;
	messageLength += buffer[index++];

	switch(hcFlags)
	{
		case JUDP1_MESSAGE_HC_NO_COMPRESSION:
			message = jausMessageCreate();
			jausMessageFromBuffer(message, buffer+index, bufferSizeBytes-index);
			index += jausMessageSize(message);
			break;
			
		case JUDP1_MESSAGE_HC_ENGAGE_COMPRESSION:
			message = jausMessageCreate();
			jausMessageFromBuffer(message, buffer+index, bufferSizeBytes-index);
			index += jausMessageSize(message);
			break;
			
		case JUDP1_MESSAGE_HC_COMPRESSION_ACKNOWLEDGE:
			return 0;
			
		case JUDP1_MESSAGE_HC_COMPRESSED_MESSAGE:
			jausData = buffer + index;
			index += messageLength;
			break;
		
		default:
//			e = new ErrorEvent(ErrorEvent::Message, __FUNCTION__, __LINE__, "Unknown Header Compression Flag!");
//			this->eventHandler->handleEvent(e);
			return 0;
	}
	
	return index;
}

int Judp1Message::getSizeBytes(void)
{
	return 4 + jausMessageSize(message);
}
