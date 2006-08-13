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
 #ifndef VSS_H
#define VSS_H

#include <cimar/jaus.h>

#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE 1
#endif

#ifndef RDDF_MODE
#define RDDF_MODE 1
#endif
#ifndef DEFAULT_MODE
#define DEFAULT_MODE 2
#endif

#define VSS_LOAD_CONFIGURATION_ERROR		-1
#define VSS_NODE_MANAGER_OPEN_ERROR			-2
#define VSS_STARTUP_BEFORE_SHUTDOWN_ERROR	-3
#define VSS_THREAD_CREATE_ERROR				-4
#define VSS_CONFIG_FILE_OPEN_ERROR			-5
#define VSS_CONFIG_FILE_UNKNOWN_ERROR		-6
#define VSS_CONFIG_FILE_DATA_ERROR			-7

#define VSS_RUN_MODE						0
#define VSS_PAUSE_MODE						1

#define VSS_THREAD_TIMEOUT_SEC				1.0

#define VSS_MAX_SC_COUNT					32
#define VSS_THREAD_DESIRED_RATE_HZ			40.0
// All defines should start with "VSS_", where your component acronym replaces "VSS"

int vssStartup(void);
int vssShutdown(void);
JausState vssGetState(void);
JausAddress vssGetAddress(void);
double vssGetUpdateRate(void);

int vssGetScActive(void);
// USER: Insert prototypes for added public function here
double vssGetSpeed(void);
int vssSetMode(int mode);
int vssSetSpeedMph(double vel);
void vssSetRunPause(int rp);
int vssGetRunPause();
void vssToggleRunPause();

#endif // VSS_H
