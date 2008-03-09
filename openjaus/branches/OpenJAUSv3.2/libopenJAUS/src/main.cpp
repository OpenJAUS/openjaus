#include "NodeManager.h"

#if defined(WIN32)
	#include <windows.h>
	#define CLEAR_COMMAND "cls"
#elif defined(__linux) || defined(linux) || defined(__linux__)
	#include <unistd.h>
	#include <termios.h>
	#define CLEAR_COMMAND "clear"
#endif

void printHelpMenu();
void parseUserInput(char input);

static NodeManager *nm;

class MyHandler : public EventHandler
{
	~MyHandler()
	{

	}
	void handleEvent(NodeManagerEvent *e)
	{
		SystemTreeEvent *treeEvent;
		ErrorEvent *errorEvent;
		JausMessageEvent *messageEvent;

		switch(e->getType())
		{
			case NodeManagerEvent::SystemTreeEvent:
				treeEvent = (SystemTreeEvent *)e;
				printf("%s\n", treeEvent->toString().c_str());
				delete e;
				break;

			case NodeManagerEvent::ErrorEvent:
				errorEvent = (ErrorEvent *)e;
				printf("%s\n", errorEvent->toString().c_str());
				delete e;
				break;

			case NodeManagerEvent::JausMessageEvent:
				messageEvent = (JausMessageEvent *)e;
				// TODO: Make this useful somehow
				// If you turn this on, the system gets spam-y this is just a test of the message event
				//printf("%s\n", messageEvent->toString().c_str());
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

	printf("\nOpenJAUS Node Manager Version %s (%s)\n\n", OJ_NODE_MANAGER_VERSION, __DATE__); 

	// Setup the console window's input handle
	handleStdin = GetStdHandle(STD_INPUT_HANDLE); 

	MyHandler *handler = new MyHandler();
	FileLoader *configData = new FileLoader("nodeManager.conf");

	nm = new NodeManager(configData, handler);

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
	struct termios newTermio;
	struct termios storedTermio;
	bool running = true;
	char choice[8] = {0};
	int count = 0;
	
	tcgetattr(0,&storedTermio);
	memcpy(&newTermio,&storedTermio,sizeof(struct termios));
	
	// Disable canonical mode, and set buffer size to 0 byte(s)
	newTermio.c_lflag &= (~ICANON);
	newTermio.c_lflag &= (~ECHO);
	newTermio.c_cc[VTIME] = 0;
	newTermio.c_cc[VMIN] = 0;
	tcsetattr(0,TCSANOW,&newTermio);

	printf("\nOpenJAUS Node Manager Version %s (%s)\n\n", OJ_NODE_MANAGER_VERSION, __DATE__); 

	FileLoader *configData = new FileLoader("nodeManager.conf");
	MyHandler *handler = new MyHandler();

	nm = new NodeManager(configData, handler);
	printHelpMenu();
	
	while(running)
	{
		bzero(choice, 8);
		count = read(0, &choice, 8);// = getchar();
		//printf("%d %d %d %d %d %d %d %d %d\n", count, choice[0], choice[1], choice[2], choice[3], choice[4], choice[5], choice[6], choice[7]);
		if(count == 1 && choice[0] == 27) // ESC
		{
			running = false;
		}
		else if(count == 1)
		{
			parseUserInput(choice[0]);
		}
		usleep((unsigned int)(0.2*1e6));
	}

	tcsetattr(0, TCSANOW, &storedTermio);
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
