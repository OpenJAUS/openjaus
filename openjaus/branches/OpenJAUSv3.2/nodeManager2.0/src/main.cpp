#include "NodeManager.h"

#if defined(WIN32)

#include <windows.h>
int main(int argc, char *args)
{
	// Console parameters
	HANDLE handleStdin;
    INPUT_RECORD inputEvents[128];
	DWORD eventCount;

	// Control parameter
	bool running = true;
	int i = 0;

	// Setup the console window's input handle
	handleStdin = GetStdHandle(STD_INPUT_HANDLE); 

	FileLoader *configData = new FileLoader("nodeManager.conf");
	
	NodeManager *nm = new NodeManager(configData);

	while(running)
	{
		// See how many events are waiting for us, this prevents blocking if none
		GetNumberOfConsoleInputEvents(handleStdin, &eventCount);
		
		if(eventCount > 0)
		{
			// Check for user input here
			ReadConsoleInput( 
					handleStdin,		// input buffer handle 
					inputEvents,		// buffer to read into 
					128,				// size of read buffer 
					&eventCount);		// number of records read 
		}
 
	    // Parse console input events 
        for (i = 0; i < (int) eventCount; i++) 
        {
            switch(inputEvents[i].EventType) 
            { 
				case KEY_EVENT: // keyboard input 
					if(inputEvents[i].Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE)
					{
						running = false;
					}
					else if(inputEvents[i].Event.KeyEvent.bKeyDown)
					{
						switch(inputEvents[i].Event.KeyEvent.wVirtualKeyCode)
						{
							case 't':
							case 'T':
								printf("%s", nm->getSystemTable().c_str());
								break;
							
							case 'c':
							case 'C':
								system("cls");
								break;

							default:
								break;
						}
					}
					break;
				
				default:
					break;
			}
		}

		Sleep((DWORD)(0.2*1e3));
	}
	return 0;
}
#elif defined(__linux) || defined(linux) || defined(__linux__)

#include <unistd.h>

int main(int argc, char *args)
{
	FileLoader *configData = new FileLoader("nodeManager.conf");
	
	NodeManager *nm = new NodeManager(configData);
	printf("%s", nm->getSystemTable().c_str());

	while(1)
	{
		usleep((unsigned int)(1*1e6));
	}

	return 0;
}
#endif

