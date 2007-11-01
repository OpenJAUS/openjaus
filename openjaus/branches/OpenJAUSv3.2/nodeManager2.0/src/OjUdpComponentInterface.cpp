#include "OjUdpComponentInterface.h"

OjUdpComponentInterface::OjUdpComponentInterface(void){}

OjUdpComponentInterface::~OjUdpComponentInterface(void){}

unsigned int OjUdpComponentInterface::getPort(void)
{
	return this->socket->port;
}

bool OjUdpComponentInterface::routeMessage(JausMessage message){ return true;}
void OjUdpComponentInterface::queueEmpty() {}
void OjUdpComponentInterface::queueFull() {}

void OjUdpComponentInterface::queueNewItem()
{

}

bool OjUdpComponentInterface::sendDatagramPacket(DatagramPacket dgPacket)
{
	return true;
}

DatagramPacket OjUdpComponentInterface::recvDatagramPacket(void)
{
	DatagramPacket dgPacket = NULL;
	int bytesReceived = 0;

	// Receive packet from socket
	bytesReceived = datagramSocketReceive(socket, dgPacket);

	return dgPacket;
}

void OjUdpComponentInterface::openSocket(void)
{

}

void OjUdpComponentInterface::closeSocket(void)
{

}

void OjUdpComponentInterface::run()
{
}

bool OjUdpComponentInterface::processOjNodemanagerInterfaceMessage(char *buffer)
{
	return true;
}

std::string OjUdpComponentInterface::toString()
{
	// Do something
	return "OpenJAUS Udp Component Interface";
}

