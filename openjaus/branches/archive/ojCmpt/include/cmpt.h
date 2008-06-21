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
// File:		cmpt.h
//
// Version:		3.2
//
// Written by:	Tom Galluzzo (galluzzo AT gmail DOT com)
//
// Date:		08/04/06
//
// Description:	This file contains the skeleton C header file code for implementing the cmpt.c file

// How To Use This File:
// All comments labled "USER:" specify lines of code that the end user must change to implement thier individual component
// The end user must also change all functions and variables in this file begining with "cmpt"
// This substring must be changed to the component identifier acronym of the individual component, and
// this file should also be renamed likewise
// Ex: For a Primitive Driver component change all "cmpt" to "pd"
// Also Change all "CMPT" to your component acronym (ALL CAPS)

#ifndef CMPT_H
#define CMPT_H

#include <jaus.h>

#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE 1
#endif

#define CMPT_LOAD_CONFIGURATION_ERROR		-1
#define CMPT_NODE_MANAGER_OPEN_ERROR		-2
#define CMPT_STARTUP_BEFORE_SHUTDOWN_ERROR	-3
#define CMPT_THREAD_CREATE_ERROR			-4

#define CMPT_THREAD_TIMEOUT_SEC				1.0
#define CMPT_THREAD_DESIRED_RATE_HZ			50.0	// USER: Modify this rate as needed
// USER: Insert defines here
#define USER_COMPONENT_ID_NUMBER_HERE	254 // USER: Remove this define

// USER: All defines should start with "CMPT_", where your component acronym replaces "CMPT"

int cmptStartup(void);
int cmptShutdown(void);
JausState cmptGetState(void);
JausAddress cmptGetAddress(void);
double cmptGetUpdateRate(void);
// USER: Insert prototypes for added public function here

#endif // CMPT_H
