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
// File Name: timeLib.c
//
// Written by: Tom Galluzzo (galluzzo AT gmail DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description:	CIMAR timing library header file


#ifdef WIN32
	#include <windows.h>
#else
//	#define HAVE_GETTIMEOFDAY
//	#include "config.h"
	#include <sys/time.h>
//	#endif
//	#ifdef HAVE_TIME_H
		#include <time.h>
//	#endif
#endif

#include "timeLib.h"

#ifdef WIN32

static char init = 0;

double getTimeSeconds(void)
{
	TIMECAPS timerInfo;

	if(!init)
	{
		timeGetDevCaps(&timerInfo, sizeof(TIMECAPS));
		timeBeginPeriod(timerInfo.wPeriodMin);
	}

	return (double) (timeGetTime() / 1000.0);
}
#else
double getTimeSeconds(void)
{
#ifdef HAVE_GETTIMEOFDAY
      static struct timeval time;
      
      gettimeofday(&time, NULL);
      
      return (double)time.tv_sec + (double)time.tv_usec/1.0e6;
#elif defined(HAVE_CLOCK_GETTIME)
      static struct timespec time;
      
      clock_gettime(CLOCK_REALTIME, &time);
      
      return (double)time.tv_sec + (double)time.tv_nsec/1.0e9;
#endif
}
#endif
