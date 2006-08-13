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
 #ifndef RDDF_H
#define RDDF_H

#define RDDF_FILE_OPEN_ERROR			-1
#define RDDF_END_OF_FILE 				-2
#define RDDF_UNKNOWN_ERROR				-3
#define RDDF_OUT_OF_DATA				-4
#define RDDF_DATA_ALREADY_INITIALIZED	-5
#define RDDF_DATA_NOT_VALID				-6

typedef struct
{
	double latitudeDeg;
	double longitudeDeg;
	double lateralBoundsFt;
	double speedMph;
} RddfWaypoint;

int rddfReadData(char *);
int rddfReleaseMemory(void);
double rddfGetCurrentSpeedMph();
double rddfGetCurrentHeadingRad(double latDeg, double lonDeg);
RddfWaypoint *rddfGetCurrentWaypoint();
int rddfUpdatePosition(double lat, double lon);
double rddfGetDistanceNextWaypoint(void);
long rddfGetNextWaypointIndex();
int rddfGetDataValidity(void);

#endif

