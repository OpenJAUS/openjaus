#ifndef QUERY_JUDP_ADDRESSES_MESSAGE
#define QUERY_JUDP_ADDRESSES_MESSAGE

#include <jaus.h>

class QueryJudpAddressesMessage : JudpTransportMessage
{
public:
	QueryJudpAddressesMessage(void);	
	~QueryJudpAddressesMessage(void);
	
	unsigned char* toBuffer(void);
	bool fromBuffer(unsigned char *);
	
};

#endif
