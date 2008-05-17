#include <jaus.h>
#include <openJaus.h>
#include <windows.h>

void myReadyState(OjCmpt myCmpt)
{
}

void myHeartbeatCallback(OjCmpt myCmpt, JausMessage hbMsg)
{
	printf("Hearbeat from: %d.%d.%d.%d\n", hbMsg->source->subsystem,
		hbMsg->source->node,
		hbMsg->source->component,
		hbMsg->source->instance);

	ojCmptDefaultMessageProcessor(myCmpt, hbMsg);
}

void main(void)
{
	HANDLE handleStdin;
    INPUT_RECORD inputEvents[128];
	DWORD eventCount;
	int running = TRUE;
	int i = 0;
	OjCmpt cmpt;

	cmpt = ojCmptCreate("Test Component", 38, 1.0);

	ojCmptSetState(cmpt, JAUS_READY_STATE);
	ojCmptSetStateCallback(cmpt, JAUS_READY_STATE, myReadyState);

	ojCmptSetMessageCallback(cmpt, JAUS_REPORT_GLOBAL_POSE, myHeartbeatCallback);
	ojCmptSetMessageCallback(cmpt, JAUS_REPORT_HEARTBEAT_PULSE, myHeartbeatCallback);

	ojCmptRun(cmpt);

	// Setup the console window's input handle
	handleStdin = GetStdHandle(STD_INPUT_HANDLE); 
	while(running)
	{
		// See how many events are waiting for us, this prevents blocking if none
		GetNumberOfConsoleInputEvents(handleStdin, &eventCount);
		if(eventCount > 0)
		{
			ReadConsoleInput( handleStdin, inputEvents, 128, &eventCount);		// number of records read 
		}
 
	    // Parse console input events 
        for (i = 0; i < (int) eventCount; i++) 
        {
            switch(inputEvents[i].EventType) 
            { 
				case KEY_EVENT: // keyboard input 
					if(inputEvents[i].Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE)
					{
						running = FALSE;
					}
					break;
				
				default:
					break;
			}
		}

		ojSleepMsec(10);
	}

	ojCmptDestroy(cmpt);
}