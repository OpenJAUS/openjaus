#include <jaus.h>
#include "nodeManager/transport/Transportable.h"
#include "nodeManager/transport/Judp1Message.h"
#include "nodeManager/transport/Judp2Message.h"
#include "nodeManager/transport/JudpMessage.h"

JudpMessage::JudpMessage()
{
	version = JUDP_VERSION_UNDEFINED;
	messages.empty();
}

JudpMessage::~JudpMessage(void)
{
}

int JudpMessage::getVersion(void)
{
	return version;
}

Transportable *JudpMessage::popMessage(void)
{
	int index = messages.size();
	
	if(index)
	{
		Transportable *message = messages[index-1];
		messages.pop_back();
		return message;
	}
	else
	{
		return NULL;
	}
}

bool JudpMessage::pushMessage(Judp1Message *message)
{
	if(version == JUDP_VERSION_UNDEFINED || version == JUDP_VERSION_1_0)
	{
		version = JUDP_VERSION_1_0;
		this->messages.push_back(message);
		return true;
	}

	return false;
}

bool JudpMessage::pushMessage(Judp2Message *message)
{
	if(version == JUDP_VERSION_UNDEFINED || version == JUDP_VERSION_2_0)
	{
		version = JUDP_VERSION_2_0;
		this->messages.push_back(message);
		return true;
	}

	return false;
}

int JudpMessage::toBuffer(unsigned char *buffer, int bufferSizeBytes)
{
	int index = 0;

	if(bufferSizeBytes >= getSizeBytes())
	{
		buffer[index] = version;
		index++;
		
		std::vector<Transportable *>::iterator iterator;
		switch(version)
		{
			case JUDP_VERSION_1_0:
				for(iterator = messages.begin(); iterator != messages.end(); iterator++) 
				{
					index += ((Judp1Message *)*iterator)->toBuffer(buffer+index, bufferSizeBytes-index);
				}
				break;

			case JUDP_VERSION_2_0:
				for(iterator = messages.begin(); iterator != messages.end(); iterator++) 
				{
					index += ((Judp2Message *)*iterator)->toBuffer(buffer+index, bufferSizeBytes-index);
				}
				break;
				
			default:
				// TODO: Throw error
				break;
		}		

	}

	return index;
}

int JudpMessage::fromBuffer(unsigned char *buffer, int bufferSizeBytes)
{
	Transportable *message = NULL;
	int index = 0;
	int bytesUnpacked = 0;

	version = buffer[0];
	index = 1;
	
	while(index < bufferSizeBytes)
	{
		switch(version)
		{
			case JUDP_VERSION_1_0:
				message = new Judp1Message();
				bytesUnpacked = ((Judp1Message *)message)->fromBuffer(buffer + index, bufferSizeBytes - index);
				break;

			case JUDP_VERSION_2_0:
				message = new Judp2Message();
				bytesUnpacked = ((Judp2Message *)message)->fromBuffer(buffer + index, bufferSizeBytes - index);
				break;
				
			default:
				bytesUnpacked = 0;
				break;
		}		

		if(!bytesUnpacked)
		{
			if(message)
			{
				delete message;
			}
			break;
		}

		this->messages.push_back(message);
		index += bytesUnpacked;
	}
	
	return index;
}
	
int JudpMessage::getSizeBytes(void)
{
	int sizeBytes = 1;

	std::vector<Transportable *>::iterator iterator;
	for(iterator = messages.begin(); iterator != messages.end(); iterator++) 
	{
		sizeBytes += (*iterator)->getSizeBytes();
	}

	return sizeBytes;
}


