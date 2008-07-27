#ifndef DISCOVER_HOST_MESSAGE
#define DISCOVER_HOST_MESSAGE

#include <jaus.h>

class DiscoverHostMessage : JudpTransportMessage
{
public:
	~DiscoverHostMessage(JausByte requestedId);	
	~DiscoverHostMessage(void);
	
	unsigned char* toBuffer(void);
	bool fromBuffer(unsigned char *);
	
	JausByte getRequestedId(void);
	
private:
	JausByte requestedId;
	
};

#endif
