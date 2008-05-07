// File:		vehicle.c 
// Version:		0.4
// Written by:	Tom Galluzzo (galluzzt@ufl.edu)
// Date:		07/22/2005

#include <stdlib.h>	
#include <string.h>	
#include <math.h>

#include "vehicle.h"

#if defined (WIN32)
	#define SLEEP_MS(x) Sleep(x)
#elif defined(__linux) || defined(linux) || defined(__linux__) || defined(__APPLE__)
	#define SLEEP_MS(x) usleep(x*1000)
#endif

#define K_MINIMUM_THRESHOLD				0.001
#define SPEED_MINIMUM_THRESHOLD			0.001

VehicleState vehicleStateCreate(void)
{
	VehicleState state;
	
	state = (VehicleState)malloc( sizeof(struct VehicleState) );
	if(state == NULL)
	{
		return NULL;
	}
	
	memset(state, 0, sizeof(struct VehicleState) );
	
	return state;
}

void vehicleStateDestroy( VehicleState state)
{
	free(state);
}

void vehicleModelTimeStep( VehicleState state, double dTime)
{
	float kAve = state->phiEffort;
	float dPhi = state->desiredPhiEffort - state->phiEffort;
	double dMaxPhi = VEHICLE_MAX_PHI_RATE_EFFORT_PER_SEC * dTime;
	double dDistM = state->speedMps * dTime;
	float dYawRad;
	
	if(dPhi > 0)
	{
		state->phiEffort += dPhi > dMaxPhi? dMaxPhi : dPhi;
	}
	else
	{
		state->phiEffort += dPhi < -dMaxPhi? -dMaxPhi : dPhi;
	}
	
	kAve += state->phiEffort;
	kAve /= 2.0f;
	kAve *= VEHICLE_CURVATURE_PER_EFFORT;
	
	dYawRad = dDistM * kAve;
	
	if(kAve < K_MINIMUM_THRESHOLD && kAve > -K_MINIMUM_THRESHOLD)
	{
		// Project straight line
		state->xM += sin(state->yawRad) * dDistM; 
		state->yM += cos(state->yawRad) * dDistM; 
	}
	else
	{
		// Project path along curve
		state->xM += (cos(state->yawRad)*(1.0 - cos(dYawRad)) + sin(state->yawRad)*sin(dYawRad)) / kAve; 
		state->yM += (cos(state->yawRad)*sin(dYawRad) - sin(state->yawRad)*(1.0 - cos(dYawRad))) / kAve; 
	}
	
	state->yawRad += dYawRad;
}

void vehicleModelDistStep( VehicleState state, double dDistM)
{
	float kAve;
	float dYawRad;
	
	if(state->speedMps > SPEED_MINIMUM_THRESHOLD)
	{
		vehicleModelTimeStep( state, dDistM / state->speedMps);
	}
	else
	{
		kAve = state->phiEffort;
		state->phiEffort = state->desiredPhiEffort;
		kAve += state->phiEffort;
		kAve /= 2.0f;
		kAve *= VEHICLE_CURVATURE_PER_EFFORT;

		dYawRad = dDistM * kAve;

		if(kAve < K_MINIMUM_THRESHOLD && kAve > -K_MINIMUM_THRESHOLD)
		{
			// Project straight line
			state->xM += sin(state->yawRad) * dDistM; 
			state->yM += cos(state->yawRad) * dDistM; 
		}
		else
		{
			// Project path along curve
			state->xM += (cos(state->yawRad)*(1.0 - cos(dYawRad)) + sin(state->yawRad)*sin(dYawRad)) / kAve; 
			state->yM += (cos(state->yawRad)*sin(dYawRad) - sin(state->yawRad)*(1.0 - cos(dYawRad))) / kAve; 
		}
		
		state->yawRad += dYawRad;
	}
}
