#ifndef DISCOVER_HOST_MESSAGE
#define DISCOVER_HOST_MESSAGE

#include <jaus.h>

class DiscoverHostMessage : JudpTransportMessage
{
public:
	DiscoverHostMessage(JausAddress requestedAddress);	
	~DiscoverHostMessage(void);
	
	unsigned char* toBuffer(void);
	bool fromBuffer(unsigned char *);
	
	JausAddress getRequestedAddress(void);
	
private:
	JausAddress requestedAddress;
	
};

#endif
