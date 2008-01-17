#ifndef OJ_UDP_COMPONENT_INTERFACE_H
#define OJ_UDP_COMPONENT_INTERFACE_H

#if defined(WIN32)
	#include <hash_map>
	#define HASH_MAP stdext::hash_map
#elif defined(__GNUC__)
	#include <ext/hash_map>
	#define HASH_MAP __gnu_cxx::hash_map
#else
	#error "Hash Map undefined in SystemTable.h."
#endif

#include "JausTransportInterface.h"
#include "JausComponentCommunicationManager.h"
#include "SystemTree.h"
#include "NodeManagerComponent.h"
#include "datagramSocket.h"

#define OJ_UDP_INTERFACE_MESSAGE_SIZE_BYTES	8

class OjUdpComponentInterface : public JausTransportInterface
{
public:
	OjUdpComponentInterface(FileLoader *configData, EventHandler *handler, JausComponentCommunicationManager *commMngr);
	~OjUdpComponentInterface(void);

	unsigned int getPort(void);
	bool routeMessage(JausMessage message);
	std::string toString();

private:
	NodeManagerComponent *nodeManager;
	SystemTree *systemTree;
	DatagramSocket socket;
	InetAddress ipAddress;
	unsigned short portNumber;
	HASH_MAP<int, unsigned short> portMap;

	bool sendDatagramPacket(DatagramPacket dgPacket);
	void openSocket(void);
	void closeSocket(void);
	void run();

	bool processOjNodemanagerInterfaceMessage(char *buffer);

	// Message type codes
	enum
	{
		CHECK_IN								= 0x01,
		REPORT_ADDRESS							= 0x02,
		CHECK_OUT								= 0x03,
		VERIFY_ADDRESS							= 0x04,
		ADDRESS_VERIFIED						= 0x05,
		GET_COMPONENT_ADDRESS_LIST				= 0x06,
		COMPONENT_ADDRESS_LIST_RESPONSE			= 0x07,
		LOOKUP_ADDRESS							= 0x08,
		LOOKUP_ADDRESS_RESPONSE					= 0x09,
		LOOKUP_SERVICE_ADDRESS					= 0x0A,
		LOOKUP_SERVICE_ADDRESS_RESPONSE			= 0x0B,
		LOOKUP_SERVICE_ADDRESS_LIST				= 0x0C,
		LOOKUP_SERVICE_ADDRESS_LIST_RESPONSE	= 0x0D 
	};
};

#endif
