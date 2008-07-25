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
// File Name: pointGg.c
//
// Written By: Danny Kent (jaus AT dannykent DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines the functions of a global grid point

#include <malloc.h>
#include "cimar.h"

PointGg pointGgCreate(void)
{
	PointGg pointGg;
	
	pointGg = (PointGg)malloc(sizeof(PointGgStruct));
	
	if(pointGg)
	{
		pointGg->row = 0;
		pointGg->column = 0;
		
		return pointGg;
	}
	else
		return NULL;
}

void pointGgDestroy(PointGg pointGg)
{
	free(pointGg);
}

PointLla globalGridToLla(PointGg pointGg, double gridResolution)
{
	PointUtm pointUtm = pointUtmCreate();
	PointLla pointLla = pointLlaCreate();
	if(pointUtm && pointLla)
	{	
		// Use the grid Resolution and the global position to calculate the UTM Values
		pointUtm->xMeters = (pointGg->column * gridResolution) + gridResolution/2;
		pointUtm->yMeters = (pointGg->row * gridResolution) + gridResolution/2;

		// Check if UTM Library is initialized
		if(!utmInitCheck()) 
		{
			pointUtmDestroy(pointUtm);
			pointLlaDestroy(pointLla);
			return NULL;
		}

		pointLla = pointUtmToPointLla(pointUtm);

		//Destroy the UTM Point
		pointUtmDestroy(pointUtm);		

		return pointLla;
	}
	else
	{
		if(pointUtm) pointUtmDestroy(pointUtm);
		if(pointLla) pointLlaDestroy(pointLla);
		return NULL;
	}
}

PointGg llaToGlobalGrid(PointLla pointLla, double gridResolution)
{
	PointGg pointGg = pointGgCreate();
	PointUtm pointUtm;

	if(pointGg)
	{	
		// Check values
		if(pointLla->longitudeRadians > CIMAR_PI || pointLla->longitudeRadians < -CIMAR_PI ||
		   pointLla->latitudeRadians > CIMAR_HALF_PI || pointLla->latitudeRadians < -CIMAR_HALF_PI )
		{
			cError("smartSensor: Improper pointLLA value. Check Radians.\n");
			cError("smartSensor: pointLLA Latitude (rad): %0.9f   Longiude (rad): %0.9f\n", pointLla->latitudeRadians, pointLla->longitudeRadians);

			pointGgDestroy(pointGg);

			return NULL;
		}
	
		// Check if UTM Library is initialized
		if(utmInitCheck())
		{
			//if UTM Library is initialized, check the UTM Zone
			if(!utmZoneCheck(pointLla))
			{
				// UTM Zone is different, re-init
				if(utmConversionInit(pointLla))
				{
					// Failed
					pointGgDestroy(pointGg);
					return NULL;
				}
			}
		}
		else
		{
			// UTM Library is not initialized, initialize it now
			if(utmConversionInit(pointLla))
			{
				// FailedpointLlaToPointUtm
				pointGgDestroy(pointGg);
				return NULL;
			}
		}
		
		// Convert to UTM space
		pointUtm = pointLlaToPointUtm(pointLla);
		
		// Use the grid Resolution and the UTM value to determine the global position
		pointGg->row = (unsigned int) (pointUtm->yMeters / gridResolution);
		pointGg->column = (unsigned int) (pointUtm->xMeters / gridResolution);
		
		// Destroy PointUtm, no longer needed
		pointUtmDestroy(pointUtm);
		return pointGg;
	}
	else
	{
		pointGgDestroy(pointGg);
		return NULL;
	}
}

PointGg utmToGlobalGrid(PointUtm pointUtm, double gridResolution)
{
	PointGg pointGg = pointGgCreate();
	
	if(pointGg)
	{
		// Use the grid Resolution and the UTM value to determine the global position
		pointGg->row = (unsigned int) (pointUtm->yMeters / gridResolution);
		pointGg->column = (unsigned int) (pointUtm->xMeters / gridResolution);
	
		return pointGg;
	}
	else
		return NULL;
}

PointUtm globalGridToUtm(PointGg pointGg, double gridResolution)
{
	PointUtm pointUtm = pointUtmCreate();
	if(pointUtm)
	{	
		// Use the grid Resolution and the global position to calculate the UTM Values
		pointUtm->xMeters = (pointGg->column * gridResolution) + gridResolution/2;
		pointUtm->yMeters = (pointGg->row * gridResolution) + gridResolution/2;
		
		return pointUtm;
	}
	else
		return NULL;
}

