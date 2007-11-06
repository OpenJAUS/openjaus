#if defined(WIN32)
	#include <windows.h>
	#define SLEEP_SEC(x) Sleep((DWORD)x*1e3)
#elif defined(__linux) || defined(linux) || defined(__linux__)
	#include <unistd.h>
	#define SLEEP_SEC(x) usleep((unsigned int)(x*1e6))
#endif

#include "NodeManager.h"

int main(int argc, char *args)
{
	FileLoader *configData = new FileLoader("nodeManager.conf");
	
	NodeManager *nm = new NodeManager(configData);
	printf("%s", nm->getSystemTable().c_str());

	while(1)
	{
		SLEEP_SEC(1);
	}

	return 0;
}

