#include <windows.h>
#include "NodeManager.h"

int main(int argc, char *args)
{
	FileLoader *configData = new FileLoader("nodeManager.conf");
	
	printf("Subs Id: %d\n", configData->GetConfigDataInt("JAUS", "SubsystemId"));
	
	NodeManager *nm = new NodeManager(configData);
	printf("%s", nm->getSystemTable().c_str());

	while(1)
	{
		Sleep(1000);
	}

	return 0;
}