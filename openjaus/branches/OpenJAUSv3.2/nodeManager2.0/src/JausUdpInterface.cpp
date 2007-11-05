#include "JausUdpInterface.h"
#include "JausSubsystemCommunicationManager.h"
#include "JausNodeCommunicationManager.h"
#include "JausComponentCommunicationManager.h"

JausUdpInterface::JausUdpInterface(FileLoader *configData, JausCommunicationManager *commMngr)
{
	this->commMngr = commMngr;
	this->name = JAUS_UDP_NAME;
	this->configData = configData;
	this->multicast = false;

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

	// Setup our receiveThread
	this->setupRecvThread();
}

JausUdpInterface::~JausUdpInterface(void)
{
	if(running)
	{
		this->stopThread();
	}
	this->closeSocket();

	// TODO: Check our threadIds to see if they terminated properly
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
			// if subs==BROADCAST send multicast


			break;

		case NODE_INTERFACE:
			// if node==BROADCAST send multicast
			break;

		case COMPONENT_INTERFACE:
			// if cmpt == BROADCAST || inst == BROADCAST send unicast to all components
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
	char ret[256] = {0};
	char buf[80] = {0};
	inetAddressToString(this->socket->address, buf);
	sprintf(ret, "%s %s:%d", JAUS_UDP_NAME, buf, this->socket->port);
	return ret;
}

void JausUdpInterface::openSocket(void)
{
	switch(this->type)
	{
		case SUBSYSTEM_INTERFACE:
			// Read Subsystem UDP Parameters
			this->portNumber = this->configData->GetConfigDataInt("Subsystem_Communications", "JAUS_UDP_Port");
			this->ipAddress = inetAddressGetByString((char *)this->configData->GetConfigDataString("Subsystem_Communications", "JAUS_UDP_IP").c_str());
			if(this->ipAddress == NULL)
			{
				this->ipAddress = inetAddressCreate();
				this->ipAddress->value = INADDR_ANY;
			}

			// Create Subsystem Socket
			this->socket = multicastSocketCreate(JAUS_DATA_PORT, ipAddress);
			if(!this->socket)
			{
				// Error creating our socket
				return;
			}

			// Setup Multicast
			if(this->configData->GetConfigDataBool("Subsystem_Communications", "JAUS_UDP_Multicast"))
			{
				this->multicastGroup  = inetAddressGetByString((char *)this->configData->GetConfigDataString("Subsystem_Communications", "JAUS_UDP_Multicast_Group").c_str());
				multicastSocketJoinGroup(this->socket, this->multicastGroup);
			}

			// Setup TTL
			multicastSocketSetTTL(this->socket, this->configData->GetConfigDataInt("Subsystem_Communications", "JAUS_UDP_TTL"));

			// Setup Timeout
			multicastSocketSetTimeout(this->socket, this->configData->GetConfigDataInt("Subsystem_Communications", "JAUS_UDP_Timeout_Sec"));

			// Setup Loopback
			multicastSocketSetLoopback(this->socket, LOOPBACK_DISABLED);
			break;

		case NODE_INTERFACE:
			// Setup Node Configuration
			this->portNumber = this->configData->GetConfigDataInt("Node_Communications", "JAUS_UDP_Port");
			this->ipAddress = inetAddressGetByString((char *)this->configData->GetConfigDataString("Node_Communications", "JAUS_UDP_IP").c_str());
			if(this->ipAddress == NULL)
			{
				this->ipAddress = inetAddressCreate();
				this->ipAddress->value = INADDR_ANY;
			}

			// Create Node Socket
			this->socket = multicastSocketCreate(JAUS_DATA_PORT, ipAddress);
			if(!this->socket)
			{
				// Error creating our socket
				return;
			}

			// Setup Multicast
			if(this->configData->GetConfigDataBool("Node_Communications", "JAUS_UDP_Multicast"))
			{
				this->multicastGroup  = inetAddressGetByString((char *)this->configData->GetConfigDataString("Node_Communications", "JAUS_UDP_Multicast_Group").c_str());
				multicastSocketJoinGroup(this->socket, this->multicastGroup);
			}

			// Setup Timeout
			multicastSocketSetTimeout(this->socket, this->configData->GetConfigDataInt("Node_Communications", "JAUS_UDP_Timeout_Sec"));

			// Setup Loopback
			multicastSocketSetLoopback(this->socket, LOOPBACK_DISABLED);
			break;

		case COMPONENT_INTERFACE:
			// Read Component Configuration
			this->portNumber = this->configData->GetConfigDataInt("Component_Communications", "JAUS_UDP_Port");
			this->ipAddress = inetAddressGetByString((char *)this->configData->GetConfigDataString("Component_Communications", "JAUS_UDP_IP").c_str());
			if(this->ipAddress == NULL)
			{
				this->ipAddress = inetAddressCreate();
				this->ipAddress->value = INADDR_ANY;
			}

			// Create Component Socket
			this->socket = multicastSocketCreate(JAUS_DATA_PORT, ipAddress);
			if(!this->socket)
			{
				// Error creating our socket
				return;
			}

			// Setup Multicast
			if(this->configData->GetConfigDataBool("Component_Communications", "JAUS_UDP_Multicast"))
			{
				this->multicastGroup  = inetAddressGetByString((char *)this->configData->GetConfigDataString("Component_Communications", "JAUS_UDP_Multicast_Group").c_str());
				multicastSocketJoinGroup(this->socket, this->multicastGroup);
			}

			// Setup Timeout
			multicastSocketSetTimeout(this->socket, this->configData->GetConfigDataInt("Component_Communications", "JAUS_UDP_Timeout_Sec"));

			// Setup Loopback
			multicastSocketSetLoopback(this->socket, LOOPBACK_DISABLED);
			break;

		default:
			// Unknown type
			break;
	}
}

void JausUdpInterface::closeSocket(void)
{
	multicastSocketDestroy(this->socket);
}

void JausUdpInterface::setupRecvThread()
{
	pthread_attr_init(&this->recvThreadAttr);
	pthread_attr_setdetachstate(&this->recvThreadAttr, PTHREAD_CREATE_DETACHED);

	this->recvThreadId = pthread_create(&this->recvThread, &this->recvThreadAttr, UdpRecvThread, this);
}

void JausUdpInterface::recvThreadRun()
{
	DatagramPacket packet;
	JausMessage rxMessage;
	UdpTransportData data;

	packet = datagramPacketCreate();
	packet->bufferSizeBytes = JAUS_HEADER_SIZE_BYTES + JAUS_MAX_DATA_SIZE_BYTES;
	packet->buffer = (unsigned char *) calloc(packet->bufferSizeBytes, 1);
	
	while(this->running)
	{
		if(multicastSocketReceive(this->socket, packet) > 0)
		{
			rxMessage = jausMessageCreate();
			if(jausMessageFromBuffer(rxMessage, packet->buffer, packet->bufferSizeBytes))
			{
				// Add to transportMap
				switch(this->type)
				{
					case SUBSYSTEM_INTERFACE:
						data.addressValue = packet->address->value;
						data.port = packet->port;
						this->addressMap[rxMessage->source->subsystem] = data;
						break;

					case NODE_INTERFACE:
						data.addressValue = packet->address->value;
						data.port = packet->port;
						this->addressMap[rxMessage->source->node] = data;
						break;

					case COMPONENT_INTERFACE:
						data.addressValue = packet->address->value;
						data.port = packet->port;
						this->addressMap[jausAddressHash(rxMessage->source)] = data;
						break;

					default:
						// Unknown type
						break;
				}

				this->commMngr->receiveJausMessage(rxMessage, this);
			}
			else
			{
				jausMessageDestroy(rxMessage);
			}
		}
	}
}

void *UdpRecvThread(void *obj)
{
	JausUdpInterface *udpInterface = (JausUdpInterface *)obj;
	udpInterface->recvThreadRun();
	return NULL;
}
