#include <jaus.h>
#include <nodeManagerInterface.h>
#include "ojCmpt.h"

typedef	struct 
{
	void (*function)(OjCmpt, JausMessage);
	unsigned short commandCode;
}MessageCallback;				// An array to hold the pointers to the message callback functions

struct OjCmpt
{
	double frequencyHz;		// Desired frequency of the component 
	double rateHz;		// Actual running frequency of the component 

	JausComponent jaus;				// A pointer to the JausComponent structure found in the OpenJAUS libjaus library.

	pthread_t thread;			// Pointer to the pthread that is running the component thread

	void (*stateCallback[OJ_CMPT_MAX_STATE_COUNT])(OjCmpt);	// An array to hold the pointers to the callback functions
	void (*mainCallback)(OjCmpt);					
	void (*processMessageCallback)(OjCmpt, JausMessage);			
	
	MessageCallback *messageCallback;				// An array to hold the pointers to the message callback functions
	int messageCallbackCount;

	int state;
	int run;

	NodeManagerInterface nmi;	
};

void* ojCmptThread(void *threadData);

OjCmpt ojCmptCreate(char *name, JausByte id, double stateFrequencyHz)
{
	OjCmpt ojCmpt;
	int i;

	ojCmpt = (OjCmpt)malloc(sizeof(struct OjCmpt));

	ojCmpt->jaus = jausComponentCreate();
	ojCmpt->jaus->identification = (char *)calloc(strlen(name) + 1, 1);
	strcpy(ojCmpt->jaus->identification, name);
	ojCmpt->jaus->address->component = id;
	ojCmptSetState(ojCmpt, JAUS_UNDEFINED_STATE);
	ojCmptSetFrequencyHz(ojCmpt, stateFrequencyHz);

	for(i=0; i<OJ_CMPT_MAX_STATE_COUNT; i++)
	{
		ojCmpt->stateCallback[i] = NULL;
	}
	ojCmpt->mainCallback = NULL;
	ojCmpt->processMessageCallback = NULL;
	ojCmpt->messageCallback = NULL;
	ojCmpt->messageCallbackCount = 0;
	
	ojCmpt->run = FALSE;

	if (!jausServiceAddCoreServices(ojCmpt->jaus->services))	// Add core services
	{
		free(ojCmpt->jaus->identification);
		jausComponentDestroy(ojCmpt->jaus);
		free(ojCmpt);
		return NULL;
	}

	ojCmpt->nmi = NULL;

	return ojCmpt;
}

int ojCmptRun(OjCmpt ojCmpt)
{
	pthread_attr_t attr;	// Thread attributed for the component threads spawned in this function

	ojCmpt->nmi = nodeManagerOpen(ojCmpt->jaus);
	if(ojCmpt->nmi == NULL)
	{
		free(ojCmpt->jaus->identification);
		jausComponentDestroy(ojCmpt->jaus);
		free(ojCmpt);
		return -1; 
	}

	ojCmpt->run = TRUE;

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	if(pthread_create(&ojCmpt->thread, &attr, ojCmptThread, (void*)ojCmpt) != 0)
	{
		nodeManagerClose(ojCmpt->nmi); // Close Node Manager Connection
		free(ojCmpt->jaus->identification);
		jausComponentDestroy(ojCmpt->jaus);
		free(ojCmpt);
		pthread_attr_destroy(&attr);
		return -2;
	}
	pthread_attr_destroy(&attr);

	return 0;
}

void ojCmptDestroy(OjCmpt ojCmpt)
{
	ojCmpt->run = FALSE;

	ojSleepMsec((int)(2000.0 / ojCmpt->frequencyHz));

	pthread_cancel(ojCmpt->thread);

	if(ojCmpt->messageCallback)
	{
		free(ojCmpt->messageCallback);
	}

	nodeManagerClose(ojCmpt->nmi); // Close Node Manager Connection
	free(ojCmpt->jaus->identification);
	jausComponentDestroy(ojCmpt->jaus);
	free(ojCmpt);	
};

void ojCmptSetFrequencyHz(OjCmpt ojCmpt, double stateFrequencyHz)
{
	if(stateFrequencyHz > OJ_CMPT_MIN_FREQUENCY_HZ && stateFrequencyHz < OJ_CMPT_MAX_FREQUENCY_HZ)
	{
		ojCmpt->frequencyHz = stateFrequencyHz;
	}
	else
	{
		ojCmpt->frequencyHz = OJ_CMPT_DEFAULT_FREQUENCY_HZ;
	}
}

void ojCmptSetState(OjCmpt ojCmpt, int state)
{
	if(state < 0 || state > OJ_CMPT_MAX_STATE_COUNT)
	{
		ojCmpt->state = JAUS_UNDEFINED_STATE;
		ojCmpt->jaus->state = JAUS_UNDEFINED_STATE;
	}
	else
	{
		ojCmpt->state = state;
		if(state > JAUS_EMERGENCY_STATE)
		{
			ojCmpt->jaus->state = JAUS_UNDEFINED_STATE;
		}
		else
		{
			ojCmpt->jaus->state = state;
		}
	}
}

int ojCmptSetStateCallback(OjCmpt ojCmpt, int state, void (*stateCallbackFunction)(OjCmpt))			// Calls method from stateHandler
{
	if(state < 0 || state > OJ_CMPT_MAX_STATE_COUNT)
	{
		return -1;
	}
	else
	{
		ojCmpt->stateCallback[state] = stateCallbackFunction;
		return 0;
	}
}

void ojCmptSetMessageCallback(OjCmpt ojCmpt, unsigned short commandCode, void (*messageFunction)(OjCmpt, JausMessage))	// Calls method from messageHandler
{
	int i;

	for(i=0; i<ojCmpt->messageCallbackCount; i++)
	{
		if(ojCmpt->messageCallback[i].commandCode == commandCode)
		{
			ojCmpt->messageCallback[i].function = messageFunction;
			return;
		}
	}

	if(ojCmpt->messageCallback)
	{
		ojCmpt->messageCallbackCount++;
		ojCmpt->messageCallback = (MessageCallback *)realloc(ojCmpt->messageCallback, ojCmpt->messageCallbackCount * sizeof(MessageCallback));
	}
	else
	{
		ojCmpt->messageCallbackCount = 1;
		ojCmpt->messageCallback = (MessageCallback *)malloc(sizeof(MessageCallback));
	}

	ojCmpt->messageCallback[ojCmpt->messageCallbackCount - 1].commandCode = commandCode;
	ojCmpt->messageCallback[ojCmpt->messageCallbackCount - 1].function = messageFunction;
}

void ojCmptSetMessageProcessorCallback(OjCmpt ojCmpt, void (*processMessageFunction)(OjCmpt, JausMessage))	// Calls method from messageHandler
{
	ojCmpt->processMessageCallback = processMessageFunction;
}

double ojCmptGetRateHz(OjCmpt ojCmpt)
{
	return ojCmpt->rateHz;
}


void* ojCmptThread(void *threadData)
{
	OjCmpt ojCmpt;
	JausMessage rxMessage;
	double time, prevTime, nextExcecuteTime = 0.0;
	int i;

	time = ojGetTimeSec();

	// Get handle to OpenJausComponent that was created 
	ojCmpt = (OjCmpt)threadData;
	
	while(ojCmpt->run) // Execute state machine code while not in the SHUTDOWN state
	{
		do
		{
			if(nodeManagerReceive(ojCmpt->nmi, &rxMessage))
			{
				for(i=0; i<ojCmpt->messageCallbackCount; i++)
				{
					if(ojCmpt->messageCallback[i].commandCode == rxMessage->commandCode && ojCmpt->messageCallback[i].function)
					{
						ojCmpt->messageCallback[i].function(ojCmpt, rxMessage);
						i = -1;
						break;
					}
				}
				
				if(i == ojCmpt->messageCallbackCount)
				{
					if(ojCmpt->processMessageCallback)
					{
						ojCmpt->processMessageCallback(ojCmpt, rxMessage);
					}
					else
					{
						defaultJausMessageProcessor(rxMessage, ojCmpt->nmi, ojCmpt->jaus);
					}
				}
			}
			else 
			{
				if(ojGetTimeSec() > nextExcecuteTime)
				{
					break;
				}
				else
				{
					ojSleepMsec(1);
				}
			}
		}while(ojGetTimeSec() < nextExcecuteTime);

		prevTime = time;
		time = ojGetTimeSec();
		ojCmpt->rateHz = 1.0/(time-prevTime); // Compute the update rate of this thread

		if(ojCmpt->mainCallback)
		{
			ojCmpt->mainCallback(ojCmpt);
		}

		if(ojCmpt->state != JAUS_UNDEFINED_STATE && ojCmpt->stateCallback[ojCmpt->state])
		{
			ojCmpt->stateCallback[ojCmpt->state](ojCmpt);
		}

		nextExcecuteTime = 2.0 * time + 1.0/ojCmpt->frequencyHz - ojGetTimeSec();
	}	

	return NULL;
}



char* ojCmptGetName(OjCmpt ojCmpt)
{
	char *name;

	name = (char *)malloc(strlen(ojCmpt->jaus->identification)+1);
	strcpy(name, ojCmpt->jaus->identification);

	return name;
}

JausAddress ojCmptGetAddress(OjCmpt ojCmpt)
{
	return jausAddressClone(ojCmpt->jaus->address);
}

void ojCmptDefaultMessageProcessor(OjCmpt ojCmpt, JausMessage message)
{
	defaultJausMessageProcessor(message, ojCmpt->nmi, ojCmpt->jaus);
}

int ojCmptGetState(OjCmpt ojCmpt)
{
	return ojCmpt->state;
}

//int OpenJausComponent::sendMessage(OjCmpt JausMessage message)
//{
//	return nodeManagerSend(ojCmpt->nmi, message);
//}

//void OpenJausComponent::addService(JausService service)
//{
//	jausServiceAddService(this->cmpt->services, service);
//}
//
//
////bool OpenJausComponent::addServiceCommand(ServiceCommandType direction, JausUnsignedShort id, JausUnsignedShort commandCode, JausUnsignedInteger presenceVector)
////{
////	JausService service;
////	
////	// Find the service from the id
////	for (int i = 0; i < this->cmpt->services->elementCount; i++)
////	{
////		if (services->)
////	}
////}
//
//
//void OpenJausComponent::establishServiceConnection(ServiceConnection cmptSc)
//{
//	messageHandler.establishServiceConnection(cmptSc);
//}
//
//
//void OpenJausComponent::addScMessage(unsigned short commandCode)
//{
//	messageHandler.addScMessage(commandCode);
//}
//
//
//void OpenJausComponent::removeScMessage(unsigned short commandCode)
//{
//	messageHandler.removeScMessage(commandCode);
//}
//
//
//bool OpenJausComponent::scIsActive(unsigned short commandCode)
//{
//	return messageHandler.scIsActive(commandCode);
//}
//
//
//ServiceConnection OpenJausComponent::getScSendList(unsigned short commandCode)
//{
//	return messageHandler.getScSendList(commandCode);
//}
