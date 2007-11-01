#include "JausUdpInterface.h"
#include "JausSubsystemCommunicationManager.h"
#include "JausNodeCommunicationManager.h"
#include "JausComponentCommunicationManager.h"

JausUdpInterface::JausUdpInterface(FileLoader *configData, JausCommunicationManager *commMngr)
{
	// Determine the type of our commMngr
	if(dynamic_cast<JausSubsystemCommunicationManager  *>(commMngr))
	{
		this->type = SUBSYSTEM_INTERFACE;
	}
	else if(dynamic_cast<JausNodeCommunicationManager *>(commMngr))
	{
		this->type = NODE_INTERFACE;
	}
	else if(dynamic_cast<JausComponentCommunicationManager *>(commMngr))
	{
		this->type = COMPONENT_INTERFACE;
	}
	else
	{
		this->type = UNKNOWN_INTERFACE;
	}
}

JausUdpInterface::~JausUdpInterface(void)
{
	// DO Something
}


InetAddress JausUdpInterface::getInetAddress(void)
{
	return this->socket->address;
}

bool JausUdpInterface::routeMessage(JausMessage message)
{
	// Todo route this packet to the proper output
	return true;
}

void JausUdpInterface::run()
{
	// Do Something
}

void JausUdpInterface::queueEmpty()
{
	// Do Something
}

void JausUdpInterface::queueFull()
{
	// Do Something
}

void JausUdpInterface::queueNewItem()
{
	// Do Something
}

std::string JausUdpInterface::toString()
{
	return "";
}

bool JausUdpInterface::sendDatagramPacket(DatagramPacket dgPacket)
{
	return true;
}

DatagramPacket JausUdpInterface::recvDatagramPacket()
{
	DatagramPacket recv = NULL;
	multicastSocketReceive(this->socket, recv);
	
	//TODO: Check for errors

	return recv;
}

void JausUdpInterface::openSocket(void)
{
	// Do Something
}

void JausUdpInterface::closeSocket(void)
{
	// Do Something
}

