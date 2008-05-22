#include <jaus.h>
#include <openJaus.h>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>

static double sendTimeSec[1000] = {0};
static double pingTimeSec[1000] = {0};

void echoReadyState(OjCmpt myCmpt)
{
}

void echoMsgCallback(OjCmpt myCmpt, JausMessage msg)
{
	//char addrString[128] = {0};
	JausAddress address = NULL;
	JausMessage newMsg = NULL;
	
	//jausAddressToString(msg->source, addrString);
	//printf("Recved %s from: %s\n", jausMessageCommandCodeString(msg), addrString);

	if(	msg->commandCode != JAUS_REPORT_HEARTBEAT_PULSE &&
		msg->commandCode != JAUS_QUERY_IDENTIFICATION &&
		msg->commandCode != JAUS_QUERY_SERVICES )
	{
		address = jausAddressCreate();
		newMsg = jausMessageClone(msg);
		
		jausAddressCopy(address, newMsg->source);
		jausAddressCopy(newMsg->source, newMsg->destination);
		jausAddressCopy(newMsg->destination, address);
		
		//printf("Echoing %s\n", jausMessageCommandCodeString(msg));
		ojCmptSendMessage(myCmpt, newMsg);
		
		jausAddressDestroy(address);
		jausMessageDestroy(newMsg);
	}
			
	
	ojCmptDefaultMessageProcessor(myCmpt, msg);
}

void testReadyState(OjCmpt myCmpt)
{
	static int i = 0;
	double time = ojGetTimeSec();
	JausMessage msg;
	ReportComponentStatusMessage status = reportComponentStatusMessageCreate();
	
	status->source->subsystem = 1;
	status->source->node = 1;
	status->source->component = 89;
	status->source->instance = 1;
	status->destination->subsystem = 1;
	status->destination->node = 1;
	status->destination->component = 88;
	status->destination->instance = 1;
	status->sequenceNumber = (unsigned short)i;
	 
	msg = reportComponentStatusMessageToJausMessage(status);
	if(i<1000)	sendTimeSec[i] = time;
	//printf("Sending Status\n");
	ojCmptSendMessage(myCmpt, msg);
	
	jausMessageDestroy(msg);
	reportComponentStatusMessageDestroy(status);	
	
	i++;
}

void testMsgCallback(OjCmpt myCmpt, JausMessage msg)
{
	double time = ojGetTimeSec();
	int i = msg->sequenceNumber;
	
	if(msg->commandCode == JAUS_REPORT_COMPONENT_STATUS)
	{ 
		//printf("Recieved status\n");
		if(i < 1000) pingTimeSec[i] = time - sendTimeSec[i];
		else
		{
			printf("Finished collecting\n");
		}
	}
		
	ojCmptDefaultMessageProcessor(myCmpt, msg);
}

int main(void)
{
	bool running = true;
	OjCmpt echoCmpt;
	OjCmpt testCmpt;
	struct termios newTermio;
	struct termios storedTermio;
	char choice[8] = {0};
	int count = 0;
	FILE *fout = fopen("dt.txt", "w");
	
	// Disable canonical mode, and set buffer size to 0 byte(s)
	tcgetattr(0,&storedTermio);
	memcpy(&newTermio,&storedTermio,sizeof(struct termios));	
	newTermio.c_lflag &= (~ICANON);
	newTermio.c_lflag &= (~ECHO);
	newTermio.c_cc[VTIME] = 0;
	newTermio.c_cc[VMIN] = 1;
	tcsetattr(0,TCSANOW,&newTermio);
	
	echoCmpt = ojCmptCreate("Echo Component", 88, 1.0);
	ojCmptSetState(echoCmpt, JAUS_READY_STATE);
	ojCmptSetStateCallback(echoCmpt, JAUS_READY_STATE, echoReadyState);
	ojCmptSetMessageProcessorCallback(echoCmpt, echoMsgCallback);
	ojCmptRun(echoCmpt);

	testCmpt = ojCmptCreate("Test Component", 89, 10.0);
	ojCmptSetState(testCmpt, JAUS_READY_STATE);
	ojCmptSetStateCallback(testCmpt, JAUS_READY_STATE, testReadyState);
	ojCmptSetMessageProcessorCallback(testCmpt, testMsgCallback);
	ojCmptRun(testCmpt);

	while(running)
	{
		bzero(choice, 8);
		count = read(0, &choice, 8);
		//printf("%d %d %d %d %d %d %d %d %d\n", count, choice[0], choice[1], choice[2], choice[3], choice[4], choice[5], choice[6], choice[7]);
		if(count == 1 && choice[0] == 27) // ESC
		{
			running = false;
		}
	}

	
	ojCmptDestroy(echoCmpt);
	ojCmptDestroy(testCmpt);

	for(count = 0; count<1000; count++)
	{
		fprintf(fout, "%lf\n", pingTimeSec[count]);
	}

	fclose(fout);
	
	tcsetattr(0, TCSANOW, &storedTermio);

	return 0;
}
