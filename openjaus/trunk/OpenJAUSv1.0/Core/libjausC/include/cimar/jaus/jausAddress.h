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
// File Name: jausAddress.h
//
// Written By: Danny Kent (jaus AT dannykent DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines the basic JausAddress of each component

#ifndef JAUS_ADDRESS_H
#define JAUS_ADDRESS_H

#include "cimar/jaus.h"

#define JAUS_INVALID_INSTANCE 		0
#define JAUS_INVALID_COMPONENT 		0
#define JAUS_INVALID_NODE 			0
#define JAUS_INVALID_SUBSYSTEM 		0

#define JAUS_BROADCAST 				255
#define JAUS_BROADCAST_INSTANCE 	255
#define JAUS_BROADCAST_COMPONENT 	255
#define JAUS_BROADCAST_NODE 		255
#define JAUS_BROADCAST_SUBSYSTEM 	255

#define JAUS_NODE_MANAGER_COMPONENT 	1
#define JAUS_PRIMARY_NODE_MANAGER_NODE 	1

typedef union
{
	struct
	{
		JausByte instance;
		JausByte component;
		JausByte node;
		JausByte subsystem;
	};
	JausUnsignedInteger id;
}JausAddressStruct;

typedef JausAddressStruct *JausAddress;

JausAddress jausAddressCreate(void);
void jausAddressDestroy(JausAddress);

int jausAddressToString(JausAddress, char *);

#endif // JAUS_ADDRESS_H
