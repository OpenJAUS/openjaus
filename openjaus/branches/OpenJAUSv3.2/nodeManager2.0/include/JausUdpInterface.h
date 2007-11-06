#ifndef JAUS_UDP_INTERFACE_H
#define JAUS_UDP_INTERFACE_H

#ifdef WIN32
	#include <errno.h>
	#include <hash_map>
	#define HASH_MAP stdext::hash_map
#elif defined(__GNUC__)
	#include <ext/hash_map>
	#define HASH_MAP __gnu_cxx::hash_map
#endif

#include "JausTransportInterface.h"
#include "multicastSocket.h"
#include "inetAddress.h"
#include "datagramPacket.h"
#include "FileLoader.h"

#define JAUS_UDP_NAME	"JAUS UDP Interface"
#define SOCKET_TIMEOUT_SEC		0.5
#define JAUS_UDP_DATA_PORT	3794

extern "C" void *UdpRecvThread(void *);

// Transport Data Structure
typedef struct
{
	unsigned int addressValue;
	unsigned short port;
}UdpTransportData;

class JausUdpInterface : public JausTransportInterface
{
public:
	JausUdpInterface(FileLoader *configData, JausCommunicationManager *commMngr);
	~JausUdpInterface(void);

	InetAddress getInetAddress(void);

	bool routeMessage(JausMessage message);

	std::string toString();
	void run();
	void recvThreadRun();

private:
	MulticastSocket socket;
	void openSocket(void);
	void closeSocket(void);

	bool multicast;
	InetAddress ipAddress;
	InetAddress multicastGroup;
	unsigned short portNumber;

	int recvThreadId;
	pthread_t recvThread;
	pthread_attr_t recvThreadAttr;

	void sendJausMessage(UdpTransportData data, JausMessage message);
	void setupRecvThread();

	HASH_MAP <int, UdpTransportData> addressMap;
	UdpTransportData multicastData;
};

#endif
