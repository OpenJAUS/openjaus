#include "JausUdpInterface.h"

JausUdpInterface::JausUdpInterface(FileLoader *configData, JausCommunicationManager *commMngr)
{
	// Do something!
}

JausUdpInterface::~JausUdpInterface(void)
{
	// DO Something
}


InetAddress JausUdpInterface::getInetAddress(void)
{
	return this->socket->address;
}

bool JausUdpInterface::processMessage(JausTransportPacket jtPacket)
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

