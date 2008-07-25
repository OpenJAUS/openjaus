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
 *       contributors may be used to endorse or promote products depdrived from 
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
// File:		wd.h
//
// Version:		1.0
//
// Written by:	Danny Kent (jaus AT dannykent DOT com)
//
// Date:		08/24/06
//
// Description:	This file contains the skeleton C header file code for implementing the wd.c file

#ifndef WD_H
#define WD_H

#include <cimar/jaus.h>
#include "vehicle.h"

#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE 1
#endif

#define WD_LOAD_CONFIGURATION_ERROR		-1
#define WD_NODE_MANAGER_OPEN_ERROR		-2
#define WD_STARTUP_BEFORE_SHUTDOWN_ERROR	-3
#define WD_THREAD_CREATE_ERROR			-4

#define WD_THREAD_TIMEOUT_SEC				1.0
#define WD_THREAD_DESIRED_RATE_HZ			50.0	// USER: Modify this rate as needed
// USER: Insert defines here

// USER: All defines should start with "WD_", where your component acronym replaces "WD"

int wdStartup(void);
int wdShutdown(void);
JausState wdGetState(void);
JausAddress wdGetAddress(void);
JausAddress wdGetControllerAddress(void);

double wdGetUpdateRate(void);
// USER: Insert prototypes for added public function here
ReportWrenchEffortMessage wdGetReportedWrench(void);
SetWrenchEffortMessage wdGetCommandedWrench(void);
ReportVelocityStateMessage wdGetVss(void);
ReportGlobalPoseMessage wdGetGpos(void);
SetTravelSpeedMessage wdGetTravelSpeed(void);
SetGlobalWaypointMessage wdGetGlobalWaypoint(void);

JausState wdGetPdState(void);
JausBoolean wdGetPdWrenchScStatus(void);
JausBoolean wdGetPdStatusScStatus(void);
JausBoolean wdGetVssScStatus(void);
JausBoolean wdGetGposScStatus(void);
JausBoolean wdGetInControlStatus(void);
VehicleState wdGetDesiredVehicleState(void);
double wdGetWaypointDistanceM(void);
int wdGetActiveWaypoint(void);
int wdGetWaypointCount(void);
void wdToggleRequestControl(void);
JausBoolean wdGetRequestControl(void);
void wdCreateWaypoint(void);
void wdSetSpeed(void);

#endif // WD_H
