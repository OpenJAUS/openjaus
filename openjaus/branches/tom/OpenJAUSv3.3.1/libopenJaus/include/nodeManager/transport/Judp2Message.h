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

#ifndef JUDP2_MESSAGE
#define JUDP2_MESSAGE

#include <jaus.h>
#include "nodeManager/transport/Transportable.h"

#define JUDP2_JAUS_MESSAGE_TYPE		1
#define JUDP2_TRANSPORT_TYPE		2


class Judp2Message : public Transportable 
{
public:
	Judp2Message();
	~Judp2Message(void);

	int getMessageType(void);
	bool setMessageType(int messageType);

	int getHcFlags(void);
	bool setHcFlags(int hcFlags);

	int getDataSize(void);
	bool setDataSize(int dataSize);

	int getHcHeaderNumber(void);
	bool setHcHeaderNumber(int hcHeaderNumber);
	
	int getHcLength(void);
	bool setHcLength(int hcLength);

	int getPriority(void);
	bool setPriority(int priority);

	int getAckNak(void);
	bool setAckNak(int ackNak);

	int getDataFlags(void);
	bool setDataFlags(int dataFlags);

	int getDestinationId(void);
	bool setDestinationId(int destinationId);

	int getSourceId(void);
	bool setSourceId(int sourceId);

	Transportable *getPayload(void);
	bool setPayload(Transportable *payload);
	
	int getSequenceNumber(void);
	bool setSequenceNumber(int sequenceNumber);

	int toBuffer(unsigned char *buffer, int bufferSizeBytes);
	int fromBuffer(unsigned char *buffer, int bufferSizeBytes);
	int getSizeBytes(void); 	
	
private:
	int messageType;
	int hcFlags;
	int dataSize;
	int hcNumber;
	int hcLength;
	int priority;
	int ackNak;
	int dataFlags;
	int destinationId;
	int sourceId;
	Transportable *payload;
	int sequenceNumber;
	
	int index;
	unsigned char *buffer;
	unsigned int bufferSizeBytes;
};

#endif
