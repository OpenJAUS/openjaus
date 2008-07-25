
#ifndef SIMULATOR_H
#define SIMULATOR_H

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

#define SIMULATOR_NAME_STRING			"Vehicle Sim"

#define SIMULATOR_STARTUP_FAILED	-1

int simulatorStartup(void);
int simulatorShutdown(void);
const char *simulatorGetName(void);

#endif // SIMULATOR_H
