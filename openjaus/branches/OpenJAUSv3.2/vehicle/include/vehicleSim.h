#ifndef VEHICLE_SIM_H
#define VEHICLE_SIM_H

#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE 1
#endif

#define VEHICLE_SIM_LOAD_CONFIGURATION_ERROR	-1
#define VEHICLE_SIM_MALLOC_ERROR				-2
#define VEHICLE_SIM_THREAD_CREATE_ERROR			-4

#define VEHICLE_SIM_THREAD_TIMEOUT_SEC			1.0

#define VEHICLE_SIM_UNDEFINED_STATE		-1
#define VEHICLE_SIM_UNKNOWN_STATE		-1
#define VEHICLE_SIM_INVALID_STATE		-1
#define VEHICLE_SIM_MANUAL_STATE		0
#define VEHICLE_SIM_HOMING_STATE		1
#define VEHICLE_SIM_READY_STATE			2
#define VEHICLE_SIM_SHUTDOWN_STATE		3

#define VEHICLE_SIM_RUN		0
#define VEHICLE_SIM_PAUSE	1

#define VEHICLE_SIM_AUTO_STATE	1

int vehicleSimStartup(void);
int vehicleSimShutdown(void);

double vehicleSimGetUpdateRate(void);
int vehicleSimGetState(void);

PointLla vehicleSimGetPositionLla(void);
double vehicleSimGetX(void);
double vehicleSimGetY(void);
double vehicleSimGetH(void);
double vehicleSimGetSpeed(void);

double vehicleSimGetRotateEffort(void);

int vehicleSimGetRunPause(void);
void vehicleSimToggleRunPause(void);
void vehicleSimSetCommand(double, double, double);
double vehicleSimGetLinearEffortX(void);
double vehicleSimGetResistiveEffortX(void);
double vehicleSimGetRotationalEffort(void);

#endif // VEHICLE_SIM_H
