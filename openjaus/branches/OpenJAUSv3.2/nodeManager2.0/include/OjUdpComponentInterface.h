#ifndef OJ_UDP_COMPONENT_INTERFACE_H
#define OJ_UDP_COMPONENT_INTERFACE_H

#include "JausTransportInterface.h"
#include "datagramSocket.h"

// Transport Data Structure
typedef struct
{
	// Address is not needed because it can only be the loopback
	int destPort;

}OjUdpComponentTransportDataStruct;

typedef OjUdpComponentTransportDataStruct *OjUdpComponentTransportData;

class OjUdpComponentInterface : public JausTransportInterface
{
public:
	OjUdpComponentInterface(void);
	~OjUdpComponentInterface(void);

	unsigned int getPort(void);
	bool processMessage(JausTransportPacket jtPacket);

	void queueEmpty();
	void queueFull();
	void queueNewItem();
	std::string toString();

private:
	DatagramSocket socket;
	bool sendDatagramPacket(DatagramPacket dgPacket);
	DatagramPacket recvDatagramPacket(void);
	void openSocket(void);
	void closeSocket(void);
	void run();

	bool processOjNodemanagerInterfaceMessage(char *buffer);
};

#endif
