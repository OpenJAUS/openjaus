#ifndef JUDP_TRANSPORT_MESSAGE
#define JUDP_TRANSPORT_MESSAGE

#include <jaus.h>

class JudpTransportMessage : JudpTransportMessage
{
public:
	JudpTransportMessage(JausByte version, JausUnsignedShort commandCode);	
	~JudpTransportMessage(void);
	
	unsigned char* toBuffer(void);
	bool fromBuffer(unsigned char *);
	
	JausByte getVersion(void);
	JausUnsignedShort getCommandCode(void);
	
private:
	JausByte version;
	JausUnsignedShort commandCode;
	
};

#endif
