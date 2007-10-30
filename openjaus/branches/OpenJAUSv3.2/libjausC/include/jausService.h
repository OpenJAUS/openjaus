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
// File Name: jausService.h
//
// Written By: Bob Touchton (btouch AT comcast DOT net), inspired by Danny Kent (jaus AT dannykent DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// This file defines the attributes of a ReportServicesMessage support functions

#ifndef JAUS_SERVICE_H
#define JAUS_SERVICE_H

#include "jaus.h"

#define CORE_MESSAGE_SUPPORT	0
#define NO_PRESENCE_VECTOR 		0
#define JAUS_SERVICE_INPUT_COMMAND 0
#define JAUS_SERVICE_OUTPUT_COMMAND 1

// ************************************************************************************************************************************
//			Report Services Support
// ************************************************************************************************************************************

struct JausCommandStruct
{
	JausUnsignedShort commandCode;		
	JausIntegerPresenceVector presenceVector;
	
	struct JausCommandStruct *next;			
};

typedef struct JausCommandStruct *JausCommand;

struct JausServiceStruct
{
	JausUnsignedShort type;				// Enumeration, same as Component ID from RA 3.2
	JausCommand inputCommandList;		// List of input messages 
	JausByte	inputCommandCount;
	JausCommand outputCommandList;		// List of output messages
	JausByte	outputCommandCount;
	
	struct JausServiceStruct *next;
};

typedef struct JausServiceStruct *JausService;

// Services JausArray Constructor
JausArray jausServicesCreate(void);

// Services JausArray Destructor
void jausServicesDestroy(JausArray jausServices);

// Services Duplication
JausArray jausServicesDuplicate(JausArray sourceServices);

// Service Constructor
JausService jausServiceCreate(JausUnsignedShort type);

// Command Constructor
JausCommand jausCommandCreate(void);

// Service Destructor
void jausServiceDestroy(JausService service);

// Command Destructor
void jausCommandDestroy(JausCommand command);

// ************************************************************************************************************************************
//			Report Services End User Functions
// ************************************************************************************************************************************

JausBoolean jausServiceAddCoreServices(JausArray jausServices);

JausService jausServiceCreateService(JausUnsignedShort serviceType);

JausBoolean jausServiceAddInputCommand(JausService service, JausUnsignedShort commandCode, JausIntegerPresenceVector presenceVector);

JausBoolean jausServiceAddOutputCommand(JausService service, JausUnsignedShort commandCode, JausIntegerPresenceVector presenceVector);

JausBoolean jausServiceAddService(JausArray jausServices, JausService service);

JausService jausServiceRetrieveService(JausArray jausServices, JausUnsignedShort serviceType);

#endif

