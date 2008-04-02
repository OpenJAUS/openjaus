#include <stdio.h>
//#include "properties.h"
#include "pd.h"
#include "simulator.h"
#include "vehicleSim.h"
#include "gpos.h"
#include "vss.h"
#include "wd.h"

#if defined (WIN32)
	#define SLEEP_MS(x) Sleep(x)
#elif defined(__linux) || defined(linux) || defined(__linux__)
	#define SLEEP_MS(x) usleep(x*1000)
#endif

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
	
	if(gposStartup())
	{
		//cError("node: gposStartup failed\n");
		simulatorShutdown();
		
		return SIMULATOR_STARTUP_FAILED;	
	}

	if(vssStartup())
	{
		//cError("node: vssStartup failed\n");
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
	vssShutdown();
	gposShutdown();
	pdShutdown();
	vehicleSimShutdown();
	
	return 0;
}

const char *simulatorGetName(void)
{
	static const char *simulatorName = SIMULATOR_NAME_STRING;
	
	return simulatorName;	
}
