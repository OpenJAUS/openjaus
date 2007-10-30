#ifndef JAUS_TRANSPORT_PACKET
#define JAUS_TRANSPORT_PACKET

#include "JausTransportData.h"
#include "jaus.h"

class JausTransportPacket
{
public:
	JausTransportPacket(void);
	~JausTransportPacket(void);
	JausTransportPacket(JausMessage message, JausTransportInterface *transport, TransportData data);

	void setJausMessage(JausMessage message);
	JausMessage getJausMessage(void);
	void setTransportInterface(JausTransportInterface *transport);
	JausTransportInterface *getTransportInterface(void);
	JausTransportData *getJausTransportData(void);

private:
	JausMessage message;
	JausTransportData *data;
};

#endif

