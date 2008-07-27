#ifndef REQUEST_ADDRESS_MESSAGE
#define REQUEST_ADDRESS_MESSAGE

#include <jaus.h>

class RequestedAddressMessage : JudpTransportMessage
{
public:
	RequestedAddressMessage(JausByte requestedId);	
	~RequestedAddressMessage(void);
	
	unsigned char* toBuffer(void);
	bool fromBuffer(unsigned char *);
	
	JausByte getRequestedId(void);
	
private:
	JausByte requestedId;
	
};

#endif
