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
// File:		exCmpt.h
// Version:		0.4 alpha
// Written by:	Tom Galluzzo (galluzzt@ufl.edu)
// Date:		07/01/2005
// Description:	This file contains the skeleton C header file code for implementing the exCmpt.c file

#ifndef EX_CMPT_H
#define EX_CMPT_H

#include <cimar/jaus.h>

#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE 1
#endif

#define EX_CMPT_LOAD_CONFIGURATION_ERROR		-1
#define EX_CMPT_NODE_MANAGER_OPEN_ERROR		-2
#define EX_CMPT_STARTUP_BEFORE_SHUTDOWN_ERROR	-3
#define EX_CMPT_THREAD_CREATE_ERROR			-4

#define EX_CMPT_THREAD_TIMEOUT_SEC				1.0
#define EX_CMPT_THREAD_DESIRED_RATE_HZ			20.0	// USER: Modify this rate as needed
// USER: Insert defines here
#define EX_COMPONENT_ID					6

// USER: All defines should start with "EX_CMPT_", where your component acronym replaces "EX_CMPT"

int exCmptStartup(void);
int exCmptShutdown(void);
JausState exCmptGetState(void);
JausAddress exCmptGetAddress(void);
double exCmptGetUpdateRate(void);
// USER: Insert prototypes for added public function here
JausBoolean exCmptGetVssScStatus(void);
ReportVelocityStateMessage exCmptGetVss(void);

#endif // EX_CMPT_H
