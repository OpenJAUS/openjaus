#ifndef ACCEPT_REQUEST_MESSAGE
#define ACCEPT_REQUEST_MESSAGE

#include <jaus.h>

class AcceptRequestMessage : JudpTransportMessage
{
public:
	AcceptRequestMessage(JausAddress offeredAddress, JausUnsignedShort leaseTimeMin);	
	~AcceptRequestMessage(void);
	
	unsigned char* toBuffer(void);
	bool fromBuffer(unsigned char *);
	
	JausAddress getOfferedAddress(void);
	JausUnsignedShort getLeaseTime(void);
	
private:
	JausAddress offeredAddress;
	JausUnsignedShort leaseTimeMin;	
};

#endif
