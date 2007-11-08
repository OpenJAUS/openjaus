#include "NodeManager.h"

#if defined(WIN32)
	#include <windows.h>
	#define CLEAR_COMMAND "cls"
#elif defined(__linux) || defined(linux) || defined(__linux__)
	#include <unistd.h>
	#define CLEAR_COMMAND "clear"
#endif

void printHelpMenu();
void parseUserInput(char input);

static NodeManager *nm;

class MyHandler : public EventHandler
{
	void handleEvent(NodeManagerEvent *e)
	{
		SystemTreeEvent *treeEvent;

		switch(e->getType())
		{
			case NodeManagerEvent::SystemTreeEvent:
				treeEvent = (SystemTreeEvent *)e;
				printf("%s\n", treeEvent->toString().c_str());
				delete e;
				break;

			default:
				delete e;
				break;
		}
	}
};




#if defined(WIN32)
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
	MyHandler *handler = new MyHandler();

	nm = new NodeManager(configData);
	nm->registerEventHandler(handler);

	printHelpMenu();

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
						parseUserInput(inputEvents[i].Event.KeyEvent.uChar.AsciiChar);
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

int main(int argc, char *args)
{
	FileLoader *configData = new FileLoader("nodeManager.conf");
	
	NodeManager *nm = new NodeManager(configData);
	printf("%s", nm->systemTreeToString().c_str());

	while(1)
	{
		usleep((unsigned int)(1*1e6));
	}

	return 0;
}
#endif

void parseUserInput(char input)
{
	switch(input)
	{
		case 'T':
			printf("\n\n%s", nm->systemTreeToDetailedString().c_str());
			break;

		case 't':
			printf("\n\n%s", nm->systemTreeToString().c_str());
			break;
		
		case 'c':
		case 'C':
			system(CLEAR_COMMAND);
			break;

		case '?':
			printHelpMenu();
	
		default:
			break;
	}

}

void printHelpMenu()
{
	printf("\n\nOpenJAUS Node Manager Help\n");
	printf("   t - Print System Tree\n");
	printf("   T - Print Detailed System Tree\n");
	printf("   c - Clear console window\n");
	printf("   ? - This Help Menu\n");
	printf(" ESC - Exit Node Manager\n");
}
