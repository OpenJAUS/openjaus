#ifndef JAUS_UDP_INTERFACE_H
#define JAUS_UDP_INTERFACE_H

#include "JausTransportInterface.h"
#include "multicastSocket.h"
#include "inetAddress.h"
#include "datagramPacket.h"
#include "FileLoader.h"

// Transport Data Structure
typedef struct
{
	InetAddress destAddress;
}UdpTransportDataStruct;

typedef UdpTransportDataStruct *UdpTransportData;

class JausUdpInterface : public JausTransportInterface
{
public:
	JausUdpInterface(FileLoader *configData, JausCommunicationManager *commMngr);
	~JausUdpInterface(void);

	InetAddress getInetAddress(void);

	bool routeMessage(JausMessage message);

	void queueEmpty();
	void queueFull();
	void queueNewItem();
	std::string toString();
	void run();

private:
	MulticastSocket socket;
	bool sendDatagramPacket(DatagramPacket dgPacket);
	DatagramPacket recvDatagramPacket();
	void openSocket(void);
	void closeSocket(void);
};

#endif
