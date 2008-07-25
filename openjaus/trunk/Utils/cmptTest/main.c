#include <jaus.h>
#include <openJaus.h>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>

void myReadyState(OjCmpt myCmpt)
{
	printf("Ready State\n");
}

void myHeartbeatCallback(OjCmpt myCmpt, JausMessage hbMsg)
{
	printf("Hearbeat from: %d.%d.%d.%d\n", hbMsg->source->subsystem,
	hbMsg->source->node,
	hbMsg->source->component,
	hbMsg->source->instance);

	ojCmptDefaultMessageProcessor(myCmpt, hbMsg);
}

void myGposCallback(OjCmpt myCmpt, JausMessage gposMsg)
{
	printf("Gpos from: %d.%d.%d.%d\n", gposMsg->source->subsystem,
			gposMsg->source->node,
			gposMsg->source->component,
			gposMsg->source->instance);

	jausMessageDestroy(gposMsg);
}

int main(void)
{
	int running = TRUE;
	int gposSc = -1;
	OjCmpt cmpt;
	struct termios newTermio;
	struct termios storedTermio;
	char choice[8] = {0};
	int count = 0;
	JausAddress address;
	
	cmpt = ojCmptCreate("Test Component", 100, 0.5);

	// Add Services
	ojCmptAddService(cmpt, JAUS_GLOBAL_WAYPOINT_DRIVER); 
	// add each supported waypoint driver input message 
	ojCmptAddServiceInputMessage(cmpt, JAUS_GLOBAL_WAYPOINT_DRIVER, JAUS_SET_TRAVEL_SPEED, NO_PRESENCE_VECTOR);
	ojCmptAddServiceInputMessage(cmpt, JAUS_GLOBAL_WAYPOINT_DRIVER, JAUS_SET_GLOBAL_WAYPOINT, NO_PRESENCE_VECTOR);//actually, there is a PV and it's equal to zero
	ojCmptAddServiceInputMessage(cmpt, JAUS_GLOBAL_WAYPOINT_DRIVER, JAUS_QUERY_WAYPOINT_COUNT, NO_PRESENCE_VECTOR);
	ojCmptAddServiceInputMessage(cmpt, JAUS_GLOBAL_WAYPOINT_DRIVER, JAUS_QUERY_GLOBAL_WAYPOINT, NO_PRESENCE_VECTOR);
	// add each supported waypoint driver output message
	ojCmptAddServiceOutputMessage(cmpt, JAUS_GLOBAL_WAYPOINT_DRIVER, JAUS_REPORT_WAYPOINT_COUNT, NO_PRESENCE_VECTOR);
	ojCmptAddServiceOutputMessage(cmpt, JAUS_GLOBAL_WAYPOINT_DRIVER, JAUS_REPORT_GLOBAL_WAYPOINT, NO_PRESENCE_VECTOR);

	ojCmptSetState(cmpt, JAUS_READY_STATE);
	ojCmptSetStateCallback(cmpt, JAUS_READY_STATE, myReadyState);

	ojCmptSetMessageCallback(cmpt, JAUS_REPORT_GLOBAL_POSE, myGposCallback);
	ojCmptSetMessageCallback(cmpt, JAUS_REPORT_HEARTBEAT_PULSE, myHeartbeatCallback);

	if(ojCmptRun(cmpt))
	{
		printf("Failed to open node manager\n");
		return 0;
	}

	
	
	// Disable canonical mode, and set buffer size to 0 byte(s)
	{
		tcgetattr(0,&storedTermio);
		memcpy(&newTermio,&storedTermio,sizeof(struct termios));
		newTermio.c_lflag &= (~ICANON);
		newTermio.c_lflag &= (~ECHO);
		newTermio.c_cc[VTIME] = 0;
		newTermio.c_cc[VMIN] = 1;
		tcsetattr(0,TCSANOW,&newTermio);
	}
	while(running)
	{
		bzero(choice, 8);
		count = read(0, &choice, 8);

		if(count == 1)
		{
			switch(choice[0])
			{
				case 27: // ESC
					running = FALSE;
					break;

				case 'e': 
					address = jausAddressCreate();
					address->component = JAUS_GLOBAL_POSE_SENSOR;
					gposSc = ojCmptEstablishSc(cmpt, JAUS_REPORT_GLOBAL_POSE, 0xFF, address, 3.0, 2.0, 0);
					jausAddressDestroy(address);
					break;
			
				case 't': 
					ojCmptTerminateSc(cmpt, gposSc);
					break;
					
				default:
					printf("Unrecognized Command\n");
					break;
			}
		}
		else
		{
			printf("Unrecognized Command\n");
		}
	}

	ojCmptDestroy(cmpt);

	tcsetattr(0, TCSANOW, &storedTermio);

	return 0;
}
