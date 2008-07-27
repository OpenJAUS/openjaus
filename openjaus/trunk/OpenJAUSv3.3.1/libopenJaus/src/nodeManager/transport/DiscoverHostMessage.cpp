#include <jaus.h>
#include "nodeManager/transport/DiscoverHostMessage.h"

DiscoverHostMessage::DiscoverHostMessage(unsigned char *buffer, unsigned int bufferSizeBytes)
{
	this->buffer = buffer;
	this->index = 0;
	this->bufferSizeBytes = bufferSizeBytes;
	this->proposedAddress = jausAddressCreate();
}

DiscoverHostMessage::~DiscoverHostMessage(void)
{
	jausAddressDestroy(this->proposedAddress);
}

unsigned int DiscoverHostMessage::toBuffer(void)
{
	int index = 0;

	if(bufferSizeBytes >= this->getSizeBytes())
	{
		// Pack Message Fields to Buffer		
		index += dynamic_cast<JudpTransportMessage *>(this)->toBuffer();

		if(!jausByteToBuffer(proposedAddress->subsystem, buffer+index, bufferSizeBytes-index)) return 0;
		index += JAUS_BYTE_SIZE_BYTES;

		if(!jausByteToBuffer(proposedAddress->node, buffer+index, bufferSizeBytes-index)) return 0;
		index += JAUS_BYTE_SIZE_BYTES;

		if(!jausByteToBuffer(proposedAddress->component, buffer+index, bufferSizeBytes-index)) return 0;
		index += JAUS_BYTE_SIZE_BYTES;

		if(!jausByteToBuffer(proposedAddress->instance, buffer+index, bufferSizeBytes-index)) return 0;
		index += JAUS_BYTE_SIZE_BYTES;
	}

	return index;
}

unsigned int DiscoverHostMessage::getSizeBytes(void)
{
	return dynamic_cast<JudpTransportMessage *>(this)->getSizeBytes() + 4;
}
