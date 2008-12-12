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
// File Name: JtcpInterface.h
//
// Written By: Danny Kent (jaus AT dannykent DOT com)
//
// Version: 3.3.0a
//
// Date: 08/07/08
//
// Description: This file lists the functions associated with a UDP Jaus 
//              Transport interface. This interface confirms to the JTCP 
//              interface (with header compression) described in SAE 
//				document AS5669.

#ifndef JTCP_INTERFACE_H
#define JTCP_INTERFACE_H

#ifdef WIN32
	#include <errno.h>
	#include <hash_map>
	#define HASH_MAP stdext::hash_map
#elif defined(__GNUC__)
	#include <ext/hash_map>
	#define HASH_MAP __gnu_cxx::hash_map
#endif

#include "JausTransportInterface.h"
#include "utils/inetAddress.h"
#include "utils/streamServer.h"
#include "utils/streamPacket.h"
#include "utils/FileLoader.h"

#define JTCP_NAME								"JTCP Component Interface"
#define JTCP_DATA_PORT							3794 // per AS5669 v1.0 and IANA assignment
#define JTCP_PER_PACKET_HEADER_SIZE_BYTES		1
#define JTCP_PER_MESSAGE_HEADER_SIZE_BYTES		4
#define JTCP_VERSION_NUMBER						2 // per AS5669 v1.0
#define JTCP_MAX_PACKET_SIZE					4096 // per AS5669 v1.0

// Header Compression Flag Values
#define JTCP_HC_NO_COMPRESSION			0
#define JTCP_HC_ENGAGE_COMPRESSION		1
#define JTCP_HC_COMPRESSION_ACKNOWLEDGE	2 // Note: This value has multiple interpretations, depending on the message length field
#define JTCP_HC_COMPRESSED_MESSAGE		3

// Default Configuration Values
// Component UDP Interface Default Values
#define JTCP_DEFAULT_COMPONENT_TIMEOUT_SEC			1.0f
#define JTCP_DEFAULT_COMPONENT_HEADER_COMPRESSION	false

static const std::string JTCP_DEFAULT_COMPONENT_IP = "127.0.0.1"; // Per OpenJAUS Node Manager Interface document

extern "C" void *JtcpRecvThread(void *);

// Transport Data Structure
typedef struct
{
	unsigned int addressValue;
	unsigned short port;
}JtcpTransportData;

typedef struct
{
	unsigned char headerNumber;
	unsigned char length;
	unsigned char flags;
	unsigned short messageLength;
}JtcpHeaderCompressionData;

class JtcpInterface : public JausTransportInterface
{
public:
	JtcpInterface(FileLoader *configData, EventHandler *handler, JausCommunicationManager *commMngr);
	~JtcpInterface(void);

	InetAddress getInetAddress(void);

	bool processMessage(JausMessage message);

	bool startInterface();
	bool stopInterface();
	std::string toString();
	void run();
	void recvThreadRun();

private:
	StreamServer socket;
	bool openSocket(void);
	void closeSocket(void);

	InetAddress ipAddress;
	unsigned short portNumber;
	bool supportHeaderCompression;

	int recvThreadId;
	pthread_t recvThread;
	pthread_attr_t recvThreadAttr;

	void sendJausMessage(JtcpTransportData data, JausMessage message);
	void startRecvThread();
	void stopRecvThread();

	unsigned int headerCompressionDataToBuffer(JtcpHeaderCompressionData *hcData, unsigned char *buffer, unsigned int bufferSizeBytes);
	unsigned int headerCompressionDataFromBuffer(JtcpHeaderCompressionData *hcData, unsigned char *buffer, unsigned int bufferSizeBytes);
	void sendUncompressedMessage(JtcpTransportData data, JausMessage message);
	void sendCompressedMessage(JtcpTransportData data, JausMessage message);
	bool receiveUncompressedMessage(JausMessage rxMessage, unsigned char *buffer, unsigned int bufferSizeBytes);
	bool receiveCompressedMessage(JausMessage rxMessage, JtcpHeaderCompressionData *hcData, unsigned char *buffer, unsigned int bufferSizeBytes);


	HASH_MAP <int, JtcpTransportData> addressMap;
};

#endif
