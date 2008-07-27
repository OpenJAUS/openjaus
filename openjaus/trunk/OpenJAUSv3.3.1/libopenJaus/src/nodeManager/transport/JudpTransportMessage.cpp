#include "nodeManager/transport/JudpTransportMessage.h"

JudpTransportMessage::JudpTransportMessage(void)
{
}

JudpTransportMessage::JudpTransportMessage(unsigned char *buffer, unsigned int bufferSizeBytes)
{
	this->buffer = buffer;
	this->index = 0;
	this->bufferSizeBytes = bufferSizeBytes;
}

JudpTransportMessage::~JudpTransportMessage(void)
{
}
	
unsigned int JudpTransportMessage::toBuffer(void)
{
	int index = 0;

	if(bufferSizeBytes >= this->getSizeBytes())
	{
		// Pack Message Fields to Buffer		
		if(!jausByteToBuffer(version, buffer+index, bufferSizeBytes-index)) return 0;
		index += JAUS_BYTE_SIZE_BYTES;

		if(!jausUnsignedShortToBuffer(commandCode, buffer+index, bufferSizeBytes-index)) return 0;
		index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
	}

	return index;
}

unsigned int JudpTransportMessage::getSizeBytes(void)
{
	return 3;
}
