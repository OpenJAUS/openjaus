#ifndef ACCEPT_REQUEST_MESSAGE
#define ACCEPT_REQUEST_MESSAGE

#include <jaus.h>

class AcceptRequestMessage : JudpTransportMessage
{
public:
	AcceptRequestMessage(JausByte offeredId, JausUnsignedShort leaseTimeMin);	
	~AcceptRequestMessage(void);
	
	unsigned char* toBuffer(void);
	bool fromBuffer(unsigned char *);
	
	JausByte getOfferedId(void);
	JausUnsignedShort getLeaseTime(void);
	
private:
	JausByte offeredId;
	JausUnsignedShort leaseTimeMin;	
};

#endif
