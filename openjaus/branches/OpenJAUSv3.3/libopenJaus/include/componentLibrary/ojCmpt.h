#ifndef OJ_CMPT_H
#define OJ_CMPT_H

#include <jaus.h>

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE 1
#endif

#define OJ_CMPT_MAX_STATE_COUNT			32
#define OJ_CMPT_MAX_INCOMING_SC_COUNT	128
#define OJ_CMPT_MIN_FREQUENCY_HZ		0.1
#define OJ_CMPT_MAX_FREQUENCY_HZ		1000.0
#define OJ_CMPT_DEFAULT_FREQUENCY_HZ	1.0
	
typedef struct OjCmptStruct *OjCmpt;

JAUS_EXPORT OjCmpt ojCmptCreate(char *name, JausByte id, double frequency);
JAUS_EXPORT void ojCmptDestroy(OjCmpt ojCmpt);
JAUS_EXPORT int ojCmptRun(OjCmpt ojCmpt);

JAUS_EXPORT void ojCmptSetFrequencyHz(OjCmpt ojCmpt, double stateFrequencyHz);
JAUS_EXPORT void ojCmptSetState(OjCmpt ojCmpt, int state);

JAUS_EXPORT int ojCmptSetStateCallback(OjCmpt ojCmpt, int state, void (*stateCallbackFunction)(OjCmpt));			// Calls method from stateHandler
JAUS_EXPORT int ojCmptSetMainCallback(OjCmpt ojCmpt, void (*mainCallbackFunction)(OjCmpt));							// Calls method from stateHandler
JAUS_EXPORT void ojCmptSetMessageCallback(OjCmpt ojCmpt, unsigned short commandCode, void (*messageFunction)(OjCmpt, JausMessage));	// Calls method from messageHandler
JAUS_EXPORT void ojCmptSetMessageProcessorCallback(OjCmpt ojCmpt, void (*processMessageFunction)(OjCmpt, JausMessage));	// Calls method from messageHandler
JAUS_EXPORT void ojCmptSetUserData(OjCmpt ojCmpt, void *data);
JAUS_EXPORT void ojCmptSetAuthority(OjCmpt ojCmpt, JausByte authority);

JAUS_EXPORT int ojCmptSendMessage(OjCmpt ojCmpt, JausMessage message);

// Accessors
JAUS_EXPORT JausByte ojCmptGetAuthority(OjCmpt ojCmpt);
JAUS_EXPORT JausAddress ojCmptGetAddress(OjCmpt ojCmpt);
JAUS_EXPORT JausAddress ojCmptGetControllerAddress(OjCmpt ojCmpt);
JAUS_EXPORT JausBoolean ojCmptHasController(OjCmpt ojCmpt);
JAUS_EXPORT int ojCmptGetState(OjCmpt ojCmpt);
JAUS_EXPORT void ojCmptDefaultMessageProcessor(OjCmpt ojCmpt, JausMessage message);
JAUS_EXPORT char* ojCmptGetName(OjCmpt ojCmpt);
JAUS_EXPORT void *ojCmptGetUserData(OjCmpt ojCmpt);
JAUS_EXPORT double ojCmptGetRateHz(OjCmpt ojCmpt);

// Services
JAUS_EXPORT JausBoolean ojCmptAddService(OjCmpt ojCmpt, JausUnsignedShort serviceType);
JAUS_EXPORT JausBoolean ojCmptAddServiceInputMessage(OjCmpt ojCmpt, JausUnsignedShort serviceType, JausUnsignedShort commandCode, JausUnsignedInteger presenceVector);
JAUS_EXPORT JausBoolean ojCmptAddServiceOutputMessage(OjCmpt ojCmpt, JausUnsignedShort serviceType, JausUnsignedShort commandCode, JausUnsignedInteger presenceVector);

// Incomming Service Connections
JAUS_EXPORT int ojCmptEstablishSc(OjCmpt ojCmpt, JausUnsignedShort cCode, JausUnsignedInteger pv, JausAddress address, double rateHz, double timeoutSec, int qSize);
JAUS_EXPORT int ojCmptTerminateSc(OjCmpt ojCmpt, int scIndex);
JAUS_EXPORT JausBoolean ojCmptIsIncomingScActive(OjCmpt ojCmpt, int scIndex);
// OjCmpt add receive SC method

// Outgoing Service Connections
JAUS_EXPORT void ojCmptAddSupportedSc(OjCmpt ojCmpt, unsigned short commandCode);		// Add service connection support for this message
JAUS_EXPORT void ojCmptRemoveSupportedSc(OjCmpt ojCmpt, unsigned short commandCode);	// Removes service connection support for this message
JAUS_EXPORT ServiceConnection ojCmptGetScSendList(OjCmpt ojCmpt, unsigned short commandCode);
JAUS_EXPORT void ojCmptDestroySendList(ServiceConnection scList);
JAUS_EXPORT JausBoolean ojCmptIsOutgoingScActive(OjCmpt ojCmpt, unsigned short commandCode);
	
// System Discovery
JAUS_EXPORT int ojCmptLookupAddress(OjCmpt ojCmpt, JausAddress address);


#ifdef __cplusplus
}
#endif

#endif // OJ_CMPT_H

