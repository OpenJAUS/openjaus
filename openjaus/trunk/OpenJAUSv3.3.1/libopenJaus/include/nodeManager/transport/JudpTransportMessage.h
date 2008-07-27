#ifndef JUDP_TRANSPORT_MESSAGE
#define JUDP_TRANSPORT_MESSAGE

#include <jaus.h>

class JudpTransportMessage
{
public:
	JudpTransportMessage(void);
	JudpTransportMessage(unsigned char *buffer, unsigned int bufferSizeBytes);
	
	~JudpTransportMessage(void);
	
	unsigned int toBuffer(void);
	
	unsigned int getSizeBytes(void);
	
	JausByte getVersion(void);
	
	JausUnsignedShort getCommandCode(void);
	
protected:
	JausByte version;
	JausUnsignedShort commandCode;
	unsigned char *buffer;
	int index;
	unsigned int bufferSizeBytes;
};

#endif
