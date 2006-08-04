#ifndef NODE_MANAGER_H
#define NODE_MANAGER_H

#include <cimar.h>
#include <cimar/jaus.h>
#include <pthread.h>
#include <string.h>

#ifdef __cplusplus
extern "C" 
{
#endif

#define SC_ERROR_SEQUENCE_NUMBERS_EQUAL 			-1
#define SC_ERROR_SEQUENCE_NUMBER_OUT_OF_SYNC 		-2
#define SC_ERROR_SERVICE_CONNECTION_QUEUE_EMPTY		-1
#define SC_ERROR_SERVICE_CONNECTION_DOES_NOT_EXIST	-2

#define SC_REFERENCE_TYPE		0
#define SC_EVENT_TYPE			1


typedef struct ServiceConnectionStruct
{
	double requestedUpdateRateHz;
	double confirmedUpdateRateHz;
	double lastSentTime;
	double timeoutSec;

	JausAddress address;
	JausIntegerPresenceVector presenceVector;
	JausUnsignedShort commandCode;
	JausUnsignedShort sequenceNumber;
	JausMessage queryMessage;
	JausByte serviceConnectionType;

	int instanceId;
	JausBoolean isActive;
	
	Queue queue;
	unsigned int queueSize;

	struct ServiceConnectionStruct *nextSc;
}ServiceConnectionStruct;

typedef ServiceConnectionStruct *ServiceConnection;

typedef struct SupportedScMessageStruct
{
	unsigned short commandCode;
	ServiceConnection scList;
	struct SupportedScMessageStruct *nextSupportedScMsg;
}SupportedScMessageStruct;

typedef SupportedScMessageStruct *SupportedScMessage;

typedef struct
{
	SupportedScMessage supportedScMsgList;
	ServiceConnection incommingSc;
	int supportedScMsgCount;
	int outgoingScCount;
	int incommingScCount;
}ServiceConnectionManagerStruct;

typedef ServiceConnectionManagerStruct *ServiceConnectionManager;

typedef struct JausAddressListStruct
{
	JausAddress address;
	struct JausAddressListStruct *nextAddress;
}JausAddressList;

typedef struct
{
	Vector messageLists;
}LargeMessageHandlerStruct;

typedef LargeMessageHandlerStruct *LargeMessageHandler;

typedef struct
{
	JausUnsignedShort commandCode;
	JausAddress source;
	Vector messages;
}LargeMessageListStruct;

typedef LargeMessageListStruct *LargeMessageList;

typedef struct
{
	DatagramSocket interfaceSocket;
	DatagramSocket messageSocket;
	
	pthread_t heartbeatThreadId;
	int heartbeatThreadRunning;
	pthread_t receiveThreadId;
	int receiveThreadRunning;
	
	InetAddress ipAddress;
	
	Queue receiveQueue;
	
	JausComponent cmpt;
	
	int isOpen;

	int heartbeatCount;
	int receiveCount;
	
	double timestamp;
	
	ServiceConnectionManager scm;
	LargeMessageHandler lmh;
}NodeManagerInterfaceStruct;

typedef NodeManagerInterfaceStruct *NodeManagerInterface;

NodeManagerInterface nodeManagerOpen(JausComponent);
int nodeManagerClose(NodeManagerInterface);
int nodeManagerReceive(NodeManagerInterface, JausMessage *);
int nodeManagerSend(NodeManagerInterface, JausMessage);
int nodeManagerSendSingleMessage(NodeManagerInterface, JausMessage);
JausAddressList *nodeManagerGetComponentAddressList(NodeManagerInterface, unsigned char);
void nodeManagerDestroyAddressList(JausAddressList *);
int nodeManagerVerifyAddress(NodeManagerInterface, JausAddress);
JausBoolean nodeManagerLookupAddress(NodeManagerInterface, JausAddress);
void nodeManagerSendCoreServiceConnections(NodeManagerInterface);
JausBoolean nodeManagerLookupServiceAddress(NodeManagerInterface, JausAddress, unsigned short, int);
JausAddressList* nodeManagerLookupServiceAddressList(NodeManagerInterface, JausAddress, unsigned short, int);

ServiceConnection serviceConnectionCreate(void);
void serviceConnectionDestroy(ServiceConnection sc);

ServiceConnectionManager scManagerCreate(void);
void scManagerDestroy(ServiceConnectionManager);

void scManagerProcessConfirmScMessage(NodeManagerInterface, ConfirmServiceConnectionMessage);
void scManagerProcessCreateScMessage(NodeManagerInterface, CreateServiceConnectionMessage);
void scManagerProcessActivateScMessage(NodeManagerInterface, ActivateServiceConnectionMessage);
void scManagerProcessSuspendScMessage(NodeManagerInterface, SuspendServiceConnectionMessage);
void scManagerProcessTerminateScMessage(NodeManagerInterface, TerminateServiceConnectionMessage);
void scManagerProcessUpdatedSubystem(NodeManagerInterface, JausSubsystem);
void scManagerProccessCreateEvent(NodeManagerInterface, CreateEventMessage);
void scManagerProcessConfirmEvent(NodeManagerInterface, ConfirmEventMessage);
void scManagerProcessCancelEvent(NodeManagerInterface, CancelEventMessage);
JausBoolean scManagerCreatePeriodicEvent(NodeManagerInterface, ServiceConnection);
JausBoolean scManagerCancelPeriodicEvent(NodeManagerInterface, ServiceConnection);

void scManagerAddSupportedMessage(NodeManagerInterface, unsigned short);
void scManagerRemoveSupportedMessage(NodeManagerInterface, unsigned short);
JausBoolean scManagerQueryActiveMessage(NodeManagerInterface, unsigned short);

ServiceConnection scManagerGetSendList(NodeManagerInterface, unsigned short);
void scManagerDestroySendList(ServiceConnection);

JausBoolean scManagerCreateServiceConnection(NodeManagerInterface nmi, ServiceConnection sc);
JausBoolean scManagerTerminateServiceConnection(NodeManagerInterface, ServiceConnection);
JausBoolean scManagerReceiveServiceConnection(NodeManagerInterface nmi, ServiceConnection requestSc, JausMessage *message);
void scManagerReceiveMessage(NodeManagerInterface, JausMessage);

void defaultJausMessageProcessor(JausMessage, NodeManagerInterface, JausComponent);

LargeMessageHandler lmHandlerCreate(void);
void lmHandlerDestroy(LargeMessageHandler);
LargeMessageList lmListCreate(void);
void lmListDestroy(LargeMessageList);
void lmHandlerReceiveLargeMessage(NodeManagerInterface, JausMessage);
int lmHandlerMessageListEqual(LargeMessageList, LargeMessageList);
LargeMessageList lmHandlerGetMessageList(LargeMessageHandler, JausMessage);
int lmHandlerLargeMessageCheck(JausMessage, JausMessage);
int lmHandlerSendLargeMessage(NodeManagerInterface, JausMessage);

#ifdef __cplusplus
}
#endif

#endif // NODE_MANAGER_INTERFACE_H
