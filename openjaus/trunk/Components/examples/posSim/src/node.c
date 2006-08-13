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
 // File:		node.c 
// Version:		1.0
// Written by:	Danny Kent (jaus AT dannykent DOT com)
// Date:		08/05/06
// Description:	This file contains the skeleton C code for implementing a JAUS node in a Linux environment

#include <unistd.h>
#include <cimar.h>
#include "gpos.h"
#include "vss.h"
#include "node.h"

int nodeStartup(void)
{
	// USER: Rename gpos to your individual component
	if(gposStartup())
	{
		cError("node: gposStartup failed\n");
		nodeShutdown();
		
		return NODE_GPOS_STARTUP_FAILED;	
	}
	usleep(10000);
	
	if(vssStartup())
	{
		cError("node: vssStartup failed\n");
		nodeShutdown();
		
		return NODE_VSS_STARTUP_FAILED;	
	}
	usleep(10000);

	return 0;
}

int nodeShutdown(void)
{
	gposShutdown();
	vssShutdown();
	
	return 0;
}

const char *nodeGetName(void)
{
	static const char *nodeName = NODE_NAME_STRING;
	
	return nodeName;	
}
