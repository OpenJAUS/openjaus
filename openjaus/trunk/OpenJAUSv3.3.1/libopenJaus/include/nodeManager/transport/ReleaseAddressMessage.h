#ifndef RELEASE_ADDRESS_MESSAGE
#define RELEASE_ADDRESS_MESSAGE

#include <jaus.h>

class ReleaseAddressMessage : JudpTransportMessage
{
public:
	ReleaseAddressMessage(JausAddress requestAddress);	
	~ReleaseAddressMessage(void);
	
	unsigned char* toBuffer(void);
	bool fromBuffer(unsigned char *);
	
	JausAddress getReleaseAddress(void);
	
private:
	JausAddress requestAddress;
	
};

#endif
