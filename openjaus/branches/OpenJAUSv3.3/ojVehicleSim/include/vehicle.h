// File:		vehicle.h
// Version:		0.1
// Written by:	Bob Touchton (btouch@ufl.edu) and Tom Galluzzo (galluzzt@ufl.edu)
// Date:		07/22/2005

#ifndef VEHICLE_H
#define VEHICLE_H

#define VEHICLE_MAX_PHI_RATE_EFFORT_PER_SEC		60.0 // Tuned: 8/13/2005, Roberto and Tom
#define VEHICLE_CURVATURE_PER_EFFORT			0.0016f // Changed from 0.00078f per Tom 8/19/05 Tuned: 8/13/2005, Danny and Tom
#define VEHICLE_MAX_PHI_EFFORT					100.0

typedef struct VehicleState
{
	float xM;
	float yM;
	float yawRad;
	float speedMps;
	float desiredSpeedMps;
	float phiEffort;
	float desiredPhiEffort;	
}* VehicleState;

VehicleState vehicleStateCreate(void);
void vehicleStateDestroy(VehicleState);

void vehicleModelTimeStep(VehicleState, double);
void vehicleModelDistStep(VehicleState, double);

#endif // VEHICLE_H
