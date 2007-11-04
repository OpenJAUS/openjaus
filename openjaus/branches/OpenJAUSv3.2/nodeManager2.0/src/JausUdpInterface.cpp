#include "JausUdpInterface.h"
#include "JausSubsystemCommunicationManager.h"
#include "JausNodeCommunicationManager.h"
#include "JausComponentCommunicationManager.h"

JausUdpInterface::JausUdpInterface(FileLoader *configData, JausCommunicationManager *commMngr)
{
	this->commMngr = commMngr;
	this->name = JAUS_UDP_NAME;
	this->configData = configData;

	// Determine the type of our commMngr
	if(dynamic_cast<JausSubsystemCommunicationManager  *>(this->commMngr))
	{
		this->type = SUBSYSTEM_INTERFACE;
	}
	else if(dynamic_cast<JausNodeCommunicationManager *>(this->commMngr))
	{
		this->type = NODE_INTERFACE;
	}
	else if(dynamic_cast<JausComponentCommunicationManager *>(this->commMngr))
	{
		this->type = COMPONENT_INTERFACE;
	}
	else
	{
		this->type = UNKNOWN_INTERFACE;
	}

	// Setup our UDP Socket
	this->openSocket();

	// Setup our pThread
	this->setupThread();
}

JausUdpInterface::~JausUdpInterface(void)
{
	if(running)
	{
		this->stopThread();
	}
	this->closeSocket();
}

InetAddress JausUdpInterface::getInetAddress(void)
{
	return this->socket->address;
}

bool JausUdpInterface::routeMessage(JausMessage message)
{
	switch(this->type)
	{
		case SUBSYSTEM_INTERFACE:
			// if subs==BROADCAST send to all subsystems != mySubsId
			break;

		case NODE_INTERFACE:
			// if node==BROADCAST send to all subsystems != mySubsId
			break;

		case COMPONENT_INTERFACE:
			break;

		default:
			// Unknown type
			// No routing behavior
			jausMessageDestroy(message);
	}
	return true;
}

void JausUdpInterface::run()
{
	// Lock our mutex
	pthread_mutex_lock(&threadMutex);

	while(this->running)
	{
		pthread_cond_wait(&threadConditional, &threadMutex);

		while(!this->queue.isEmpty())
		{
			// Pop a packet off the queue and send it off
			routeMessage(queue.pop());
		}
	}
	pthread_mutex_unlock(&threadMutex);
}

std::string JausUdpInterface::toString()
{
	return JAUS_UDP_NAME;
}

bool JausUdpInterface::sendDatagramPacket(DatagramPacket dgPacket)
{
	multicastSocketSend(socket, dgPacket);
	return true;
}

DatagramPacket JausUdpInterface::recvDatagramPacket()
{
	DatagramPacket packet = NULL;
	JausMessage message = NULL;

	if(multicastSocketReceive(this->socket, packet) > 0)
	{
		message = jausMessageCreate();		
		if(jausMessageFromBuffer(message, packet->buffer, packet->bufferSizeBytes))
		{

			// Add to transportMap
			switch(this->type)
			{
				case SUBSYSTEM_INTERFACE:
					// TODO: add subsId to transportMap
					break;

				case NODE_INTERFACE:
					// TODO: add nodeId to transportMap
					break;

				case COMPONENT_INTERFACE:
					// TODO: add jausAddress to transportMap
					break;

				default:
					// Unknown type
					break;
			}
		}
	}
	return packet;
}

void JausUdpInterface::openSocket(void)
{
	this->socket = multicastSocketCreate(JAUS_DATA_PORT);
}

void JausUdpInterface::closeSocket(void)
{
	// Do Something
}

