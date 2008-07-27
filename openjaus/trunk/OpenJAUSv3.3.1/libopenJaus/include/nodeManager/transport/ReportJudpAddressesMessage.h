#ifndef REPORT_JUDP_ADDRESSES_MESSAGE
#define REPORT_JUDP_ADDRESSES_MESSAGE

#include <jaus.h>

class ReportJudpAddressesMessage : JudpTransportMessage
{
public:
	ReportJudpAddressesMessage(void);	
	~ReportJudpAddressesMessage(void);
	
	unsigned char* toBuffer(void);
	bool fromBuffer(unsigned char *);

private:
	JausUnsignedShort addressCount;
	std::vector <JausAddress> jausAddresses;
	std::vector <unsigned int> udpAddresses;
};

#endif