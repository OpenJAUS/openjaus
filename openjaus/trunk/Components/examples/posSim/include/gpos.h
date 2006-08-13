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
 #ifndef GPOS_H
#define GPOS_H

#include <cimar/jaus.h>

#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE 1
#endif

#define GPOS_LOAD_CONFIGURATION_ERROR		-1
#define GPOS_NODE_MANAGER_OPEN_ERROR		-2
#define GPOS_STARTUP_BEFORE_SHUTDOWN_ERROR	-3
#define GPOS_THREAD_CREATE_ERROR			-4

#define GPOS_THREAD_TIMEOUT_SEC				1.0

#define GPOS_MAX_SC_COUNT					32
#define GPOS_THREAD_DESIRED_RATE_HZ			40.0
// All defines should start with "GPOS_", where your component acronym replaces "GPOS"

int gposStartup(void);
int gposShutdown(void);
JausState gposGetState(void);
JausAddress gposGetAddress(void);
double gposGetUpdateRate(void);

// USER: Insert prototypes for added public function here
double gposGetLatitude(void);
double gposGetLongitude(void);
double gposGetYaw(void);
JausBoolean gposGetScActive(void);
int gposSetLatitude(double lat);
int gposSetLongitude(double lon);
int gposSetHeading(double heading);

#endif // GPOS_H
