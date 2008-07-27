#ifndef REQUEST_ADDRESS_MESSAGE
#define REQUEST_ADDRESS_MESSAGE

#include <jaus.h>

class RequestAddressMessage : JudpTransportMessage
{
public:
	RequestAddressMessage(JausAddress requestAddress);	
	~RequestAddressMessage(void);
	
	unsigned char* toBuffer(void);
	bool fromBuffer(unsigned char *);
	
	JausAddress getRequestAddress(void);
	
private:
	JausAddress requestAddress;
	
};

#endif
