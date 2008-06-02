/*****************************************************************************
 *  Copyright (c) 2008, OpenJAUS.com
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
// File Name: JausUdpInterface.h
//
// Written By: Danny Kent (jaus AT dannykent DOT com)
//
// Version: 3.3 BETA
//
// Date: 04/15/08
//
// Description: 

#ifndef JAUS_UDP_INTERFACE_H
#define JAUS_UDP_INTERFACE_H

#ifdef WIN32
	#include <errno.h>
	#include <hash_map>
	#define HASH_MAP stdext::hash_map
#elif defined(__GNUC__)
	#include <ext/hash_map>
	#define HASH_MAP __gnu_cxx::hash_map
#endif

#include "JausTransportInterface.h"
#include "utils/multicastSocket.h"
#include "utils/inetAddress.h"
#include "utils/datagramPacket.h"
#include "utils/FileLoader.h"

#define JAUS_UDP_NAME					"JAUS UDP Interface"
#define SOCKET_TIMEOUT_SEC				0.5
#define JAUS_UDP_DATA_PORT				3794
#define JAUS_OPC_UDP_HEADER				"JAUS01.0"
#define JAUS_OPC_UDP_HEADER_SIZE_BYTES	8 

extern "C" void *UdpRecvThread(void *);

// Transport Data Structure
typedef struct
{
	unsigned int addressValue;
	unsigned short port;
}UdpTransportData;

class JausUdpInterface : public JausTransportInterface
{
public:
	JausUdpInterface(FileLoader *configData, EventHandler *handler, JausCommunicationManager *commMngr);
	~JausUdpInterface(void);

	InetAddress getInetAddress(void);

	bool processMessage(JausMessage message);

	bool startInterface();
	bool stopInterface();
	std::string toString();
	void run();
	void recvThreadRun();

private:
	MulticastSocket socket;
	bool openSocket(void);
	void closeSocket(void);

	bool multicast;
	InetAddress ipAddress;
	InetAddress multicastGroup;
	unsigned short portNumber;

	int recvThreadId;
	pthread_t recvThread;
	pthread_attr_t recvThreadAttr;

	void sendJausMessage(UdpTransportData data, JausMessage message);
	void startRecvThread();
	void stopRecvThread();

	HASH_MAP <int, UdpTransportData> addressMap;
	bool subsystemGatewayDiscovered;
	UdpTransportData subsystemGatewayData;
	UdpTransportData multicastData;
};

#endif
