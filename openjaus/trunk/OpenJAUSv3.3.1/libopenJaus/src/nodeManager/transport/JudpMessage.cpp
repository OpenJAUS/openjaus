#include <jaus.h>
#include "nodeManager/transport/Transportable.h"
#include "nodeManager/transport/Judp1Message.h"
#include "nodeManager/transport/Judp2Message.h"
#include "nodeManager/transport/JudpMessage.h"

JudpMessage::JudpMessage()
{
	setVersion(JUDP_VERSION_UNDEFINED);
	judp1Message = new Judp1Message();
	//judp2Message = new Judp2Message();
	messages.empty();
}

JudpMessage::JudpMessage(int version)
{
	JudpMessage();
	setVersion(version);
}

JudpMessage::~JudpMessage(void)
{
}

int JudpMessage::getVersion(void)
{
	return version;
}

bool JudpMessage::setVersion(int version)
{
	this->version = version;
	return false;
}

Transportable *JudpMessage::popMessage(void)
{
	int messageIndex = 0;
	return messages[messageIndex];
}

bool JudpMessage::pushMessage(Transportable *message)
{
	this->messages.push_back(message);
	return true;
}

int JudpMessage::toBuffer(unsigned char *buffer, int bufferSizeBytes)
{
	return 0;
}

int JudpMessage::fromBuffer(unsigned char *buffer, int bufferSizeBytes)
{
	Transportable *message = NULL;
	int index = 0;
	int bytesUnpacked = 0;

	index = 1;
	
	while(index < bufferSizeBytes)
	{
		switch(version)
		{
			case JUDP_VERSION_1_0:
				message = new Judp1Message();
				bytesUnpacked = judp1Message->fromBuffer(buffer + index, bufferSizeBytes - index);
				break;

			case JUDP_VERSION_2_0:
				//message = new Judp2Message();
				bytesUnpacked = 0;//judp2Message->fromBuffer(buffer + index, bufferSizeBytes - index);
				break;
				
			default:
				// TODO: Throw error
				break;
		}		

		this->messages.push_back(message);
		index += bytesUnpacked;
		
		if(!bytesUnpacked)
		{
			break;
		}
	}
	
	return index;
}
	
int JudpMessage::getSizeBytes(void)
{
	//Transportable *message = NULL;
	int sizeBytes = 1;
//	int bytesUnpacked = 0;
//	
//	while(sizeBytes < bufferSizeBytes)
//	{
//		switch(version)
//		{
//			case JUDP_VERSION_1_0:
//				bytesUnpacked = judp1Message->getSizeBytes();
//				break;
//
//			case JUDP_VERSION_2_0:
//				bytesUnpacked = judp2Message->getSizeBytes();
//				break;
//				
//			default:
//				// TODO: Throw error
//				break;
//		}		
//
//		if(!bytesUnpacked)
//		{
//			break;
//		}
//
//		sizeBytes += bytesUnpacked;
//	}
//
	return sizeBytes;
}


