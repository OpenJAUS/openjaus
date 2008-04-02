#ifndef OJ_CMPT_H
#define OJ_CMPT_H

#include <jaus.h>

#define OJ_CMPT_MAX_STATE_COUNT			32
#define OJ_CMPT_MIN_FREQUENCY_HZ		0.1
#define OJ_CMPT_MAX_FREQUENCY_HZ		1000.0
#define OJ_CMPT_DEFAULT_FREQUENCY_HZ	1.0

typedef struct OjCmpt *OjCmpt;

JAUS_EXPORT OjCmpt ojCmptCreate(char *name, JausByte id, double frequency);
JAUS_EXPORT void ojCmptDestroy(OjCmpt ojCmpt);

JAUS_EXPORT void ojCmptSetFrequencyHz(OjCmpt ojCmpt, double stateFrequencyHz);
JAUS_EXPORT void ojCmptSetState(OjCmpt ojCmpt, int state);

JAUS_EXPORT int ojCmptSetStateCallback(OjCmpt ojCmpt, int state, void (*stateCallbackFunction)(OjCmpt));			// Calls method from stateHandler
JAUS_EXPORT int ojCmptSetMainCallback(OjCmpt ojCmpt, void (*mainCallbackFunction)(OjCmpt));							// Calls method from stateHandler
JAUS_EXPORT void ojCmptSetMessageCallback(OjCmpt ojCmpt, unsigned short commandCode, void (*messageFunction)(OjCmpt, JausMessage));	// Calls method from messageHandler
JAUS_EXPORT void ojCmptSetMessageProcessorCallback(OjCmpt ojCmpt, void (*processMessageFunction)(OjCmpt, JausMessage));	// Calls method from messageHandler

JAUS_EXPORT void ojCmptSendMessage(OjCmpt ojCmpt, JausMessage message);

JAUS_EXPORT char* ojCmptGetName(OjCmpt ojCmpt);
JAUS_EXPORT JausAddress ojCmptGetAddress(OjCmpt ojCmpt);

JAUS_EXPORT int ojCmptGetState(OjCmpt ojCmpt);

JAUS_EXPORT double ojCmptGetRateHz(OjCmpt ojCmpt);
JAUS_EXPORT void ojCmptDefaultMessageProcessor(OjCmpt ojCmpt, JausMessage message);

void addService(JausService service);
//	int addServiceCommand(ServiceCommandType direction, JausUnsignedShort id, JausUnsignedShort commandCode, JausIntegerPresenceVector presenceVector);


void establishServiceConnection(ServiceConnection cmptSc);


void addScMessage(unsigned short commandCode);		// Add service connection support for this message
void removeScMessage(unsigned short commandCode);	// Removes service connection support for this message

int scIsActive(unsigned short commandCode);
ServiceConnection getScSendList(unsigned short commandCode);

#endif // OJ_CMPT_H

