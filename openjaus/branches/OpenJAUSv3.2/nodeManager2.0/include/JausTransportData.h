#ifndef JAUS_TRANSPORT_DATA
#define JAUS_TRANSPORT_DATA

#include <string>

typedef void *TransportData;

class JausTransportInterface;

class JausTransportData
{
private:
	JausTransportInterface *transport;
	TransportData data;

public:
	JausTransportData(void);
	JausTransportData(JausTransportInterface *transport, TransportData data);
	~JausTransportData(void);

	void setInterface(JausTransportInterface *transport);
	JausTransportInterface *getInterface();
	void setData(TransportData data);
	TransportData getData(void);
};

#endif

