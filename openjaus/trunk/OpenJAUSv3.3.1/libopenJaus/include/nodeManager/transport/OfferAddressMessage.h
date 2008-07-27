#ifndef OFFER_ADDRESS_MESSAGE
#define OFFER_ADDRESS_MESSAGE

#include <jaus.h>

class OfferAddressMessage : JudpTransportMessage
{
public:
	OfferAddressMessage(JausAddress offerAddress, JausUnsignedShort leaseTimeMin);	
	~OfferAddressMessage(void);
	
	unsigned char* toBuffer(void);
	bool fromBuffer(unsigned char *);
	
	JausAddress getOfferAddress(void);
	JausUnsignedShort getLeaseTime(void);
	
private:
	JausAddress offerAddress;
	JausUnsignedShort leaseTimeMin;	
};

#endif
