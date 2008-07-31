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
// File Name: JudpInterface.h
//
// Written By: Danny Kent (jaus AT dannykent DOT com)
//
// Version: 3.3.0
//
// Date: 07/09/08
//
// Description: This file lists the functions associated with a UDP Jaus 
//              Transport interface. This interface confirms to the JUDP 
//              interface (with header compression) described in SAE 
//				document AS5669.

#ifndef JUDP1_MESSAGE
#define JUDP1_MESSAGE

#include <jaus.h>
#include "nodeManager/transport/Transportable.h"

class Judp1Message : public Transportable 
{
public:
	Judp1Message();
	~Judp1Message(void);

	int getHcHeaderNumber(void);
	bool setHcHeaderNumber(int hcHeaderNumber);
	
	int getHcLength(void);
	bool setHcLength(int hcLength);

	int getHcFlags(void);
	bool setHcFlags(int hcFlags);

	int getMessageLength(void);
	bool setMessageLength(int messageLength);
	
	JausMessage getJausMessage(void);
	bool setJausMessage(JausMessage message);

private:
	int hcHeaderNumber;
	int hcLength;
	int hcFlags;
	int messageLength;
	JausMessage message;
	int index;
	unsigned char *buffer;
	unsigned int bufferSizeBytes;
};

#endif
