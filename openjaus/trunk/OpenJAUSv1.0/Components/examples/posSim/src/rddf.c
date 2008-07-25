/*****************************************************************************
 *  Copyright (c) 2006, University of Florida.
 *  All rights reserved.
 *  
 *  This file is part of OpenJAUS.  OpenJAUS is distributed under the BSD 
 *  license.  See the LICENSE file for details.
 * 
 *  Redistribution and use in source and binary forms, with or without 
 *  modification, are permitted provided that the following conditions 
 *  are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer in the documentation and/or other materials provided
 *       with the distribution.
 *     * Neither the name of the University of Florida nor the names of its 
 *       contributors may be used to endorse or promote products derived from 
 *       this software without specific prior written permission.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
 *   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
 *   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR 
 *   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
 *   OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, 
 *   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY 
 *   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 ****************************************************************************/
 // File:		rddf.c 
// Version:		1.0
// Written by:	Danny Kent (jaus AT dannykent DOT com)
// Date:		08/05/06
// Description:	Reads a RDDF file (comma seperated) and stores the data into a structure
#include <stdlib.h>
#include <string.h>

#include <cimar.h>
#include "rddf.h"
#include "gpos.h"
#include "vss.h"
#include "posConstants.h"

// Controls the speed of the simulation
#define SPEED_FACTOR (double)0.75

// How far from a waypoint before "popping"
#define WAYPOINT_DISTANCE (double)0.5

static RddfWaypoint *waypoint = NULL;
static long numWaypoints = 0;
static long currentWaypoint = -1;
static int rddfDataValidity = FALSE;
static double rddfWaypointDistance = 0.0;

long rddfGetNextWaypointIndex()
{
	return currentWaypoint + 1;
}

double rddfGetDistanceNextWaypoint(void)
{
	return rddfWaypointDistance;
}

int rddfUpdatePosition(double lat, double lon)
{
	rddfWaypointDistance = greatCircleDistance(lat*DEG_TO_RAD, lon*DEG_TO_RAD, waypoint[currentWaypoint+1].latitudeDeg*DEG_TO_RAD, waypoint[currentWaypoint+1].longitudeDeg*DEG_TO_RAD);

	if(rddfWaypointDistance <= WAYPOINT_DISTANCE)
	{
		if(currentWaypoint < numWaypoints - 1)
		{
			currentWaypoint++;
		}
		else
			currentWaypoint = 1;
	}
	return 0;
}

RddfWaypoint *rddfGetCurrentWaypoint()
{
	if(currentWaypoint >= 0)
		return &waypoint[currentWaypoint];
	else return NULL;
}

double rddfGetCurrentHeadingRad(double latDeg, double lonDeg)
{
	double heading = 0;
	heading = greatCircleCourse(latDeg*DEG_TO_RAD, lonDeg*DEG_TO_RAD, waypoint[currentWaypoint+1].latitudeDeg*DEG_TO_RAD, waypoint[currentWaypoint+1].longitudeDeg*DEG_TO_RAD);
	return heading;
}

double rddfGetCurrentSpeedMph()
{
	double speed = 0;
	
	if(currentWaypoint < numWaypoints - 1 && currentWaypoint >= 0)
		speed = (waypoint[currentWaypoint].speedMph) * SPEED_FACTOR;
	else 
		speed = 0.0;
		
	return speed;
}

int rddfReleaseMemory()
{
	if(rddfDataValidity == TRUE)
	{
		free(waypoint);
		waypoint = NULL;
		rddfDataValidity = FALSE;
		return 0;
	}
	else return RDDF_DATA_NOT_VALID;
}

int rddfReadData(char *fName)
{
	FILE *filePointer = NULL;
	char fileName[100] = {0};
	char buff[120] = {0};
	
	cDebug(7, "Opening File %s\n", fName);
	
	if(rddfDataValidity == FALSE)
	{
		// Try local dir first
		sprintf(fileName,"./%s", fName);
		if( (filePointer = fopen(fileName, "r")) == NULL)
		{
			// Try local ./config and ../config
			sprintf(fileName,"./config/%s", fName);
			if( (filePointer = fopen(fileName, "r")) == NULL)
			{
				sprintf(fileName,"../config/%s", fName);
				if( (filePointer = fopen(fileName, "r")) == NULL)
				{
					cError("rddf: Cannot find and open the RDDF file.", fName);
					return RDDF_FILE_OPEN_ERROR;
				}
			}
		}
		
		cDebug(7, "Opening File %s\n", fileName);		
		
		srand((unsigned int) getTimeSeconds());
			
		//read in strings until no data leftu
		//WP Number, Lat, Lon, Lat Bounds(ft), Speed(mph), ####, ####, ####
		while(fgets(buff, sizeof(buff), filePointer)!= NULL)
		{
			if(waypoint == NULL) waypoint = (RddfWaypoint *)malloc(sizeof(RddfWaypoint));
			else waypoint = (RddfWaypoint *)realloc(waypoint, (numWaypoints+1) * sizeof(RddfWaypoint));
		
			strtok(buff, ","); //WP_NUMBER	
			waypoint[numWaypoints].latitudeDeg = atof(strtok(NULL, ",")); // Latitude (Deg)
			waypoint[numWaypoints].longitudeDeg = atof(strtok(NULL, ",")); // Longitude (Deg)
			waypoint[numWaypoints].lateralBoundsFt = atof(strtok(NULL, ",")); // Lat Bounds
			waypoint[numWaypoints].speedMph = atof(strtok(NULL, ",")); // speed (MPH)
			
			if(waypoint[numWaypoints].speedMph > 100)
			{
				waypoint[numWaypoints].speedMph = (rand() % 30) + 4;
			}
	
			numWaypoints++;
		}

		//No More Data
		fclose(filePointer);
		currentWaypoint = 0;
	
		rddfDataValidity = TRUE;
		
		return 0;
	}
	else
		return RDDF_DATA_ALREADY_INITIALIZED;
}

int rddfGetDataValidity(void)
{
	return rddfDataValidity;
}
