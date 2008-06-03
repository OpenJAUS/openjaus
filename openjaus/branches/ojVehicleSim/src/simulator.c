#include <stdio.h>
#include <openJaus.h>
//#include "properties.h"
#include "pd.h"
#include "simulator.h"
#include "vehicleSim.h"
#include "wd.h"

int simulatorStartup(void)
{
	if(vehicleSimStartup())
	{
		//cError("node: vehicleSimStartup failed\n");
		simulatorShutdown();
		
		return SIMULATOR_STARTUP_FAILED;	
	}

	if(pdStartup())
	{
		printf("node: pdStartup failed\n");
		//cError("node: pdStartup failed\n");
		simulatorShutdown();
		
		return SIMULATOR_STARTUP_FAILED;	
	}
	
	if(wdStartup())
	{
		//cError("node: wdStartup failed\n");
		simulatorShutdown();
		
		return SIMULATOR_STARTUP_FAILED;	
	}

	return 0;
}

int simulatorShutdown(void)
{
	wdShutdown();	
	pdShutdown();
	vehicleSimShutdown();
	
	return 0;
}

const char *simulatorGetName(void)
{
	static const char *simulatorName = SIMULATOR_NAME_STRING;
	
	return simulatorName;	
}
