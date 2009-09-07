/*****************************************************************************
 *  Copyright (c) 2008, University of Florida
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
// File Name: JausComponentCommunicationManager.h
//
// Written By: Danny Kent (jaus AT dannykent DOT com)
//
// Version: 3.3.0b
//
// Date: 08/07/08
//
// Description: 

#ifndef JAUS_CMPT_COMMS_MNGR_H
#define JAUS_CMPT_COMMS_MNGR_H

#include "JausCommunicationManager.h"
#include "SystemTree.h"
#include "NodeManagerComponent.h"
#include "CommunicatorComponent.h"

class OjUdpComponentInterface;

class JausComponentCommunicationManager : public JausCommunicationManager
{
public:
	JausComponentCommunicationManager(FileLoader *configData, MessageRouter *msgRouter, SystemTree *systemTree, EventHandler *handler);
	~JausComponentCommunicationManager(void);
	bool sendJausMessage(JausMessage message);
	bool receiveJausMessage(JausMessage message, JausTransportInterface *srcInf);
	bool startInterfaces(void);
	bool stopInterfaces(void);

	NodeManagerComponent *getNodeManagerComponent(void);
	
private:
	OjUdpComponentInterface *udpCmptInf;
	NodeManagerComponent *nodeManagerCmpt;
	CommunicatorComponent *communicatorCmpt;

	bool sendToComponentX(JausMessage message);
	bool sendToAllInterfaces(JausMessage message);
};

#endif
