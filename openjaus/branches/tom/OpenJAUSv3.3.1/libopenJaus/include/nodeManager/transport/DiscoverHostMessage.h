#ifndef DISCOVER_HOST_MESSAGE
#define DISCOVER_HOST_MESSAGE

#include <jaus.h>
#include "JudpTransportMessage.h"

class DiscoverHostMessage : public JudpTransportMessage
{
public:
	DiscoverHostMessage(unsigned char *buffer, unsigned int bufferSizeBytes);	
	~DiscoverHostMessage(void);
	
	unsigned int toBuffer(void);
	
	unsigned int getSizeBytes(void);
	
	void setProposedAddress(JausAddress proposedAddress);
	JausAddress getProposedAddress(void);
	
private:
	JausAddress proposedAddress;
	
};

#endif
