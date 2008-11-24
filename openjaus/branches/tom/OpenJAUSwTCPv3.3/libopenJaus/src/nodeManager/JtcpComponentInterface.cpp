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
// File Name: JtcpInterface.cpp
//
// Written By: Danny Kent (jaus AT dannykent DOT com) 
//
// Version: 3.3.0a
//
// Date: 08/07/08
//
// Description: Defines the standard JAUS UDP interface on port 3792. Is compliant with the 
// 				ETG/OPC style of UDP header

#include "nodeManager/JtcpComponentInterface.h"
#include "nodeManager/JausSubsystemCommunicationManager.h"
#include "nodeManager/JausNodeCommunicationManager.h"
#include "nodeManager/JausComponentCommunicationManager.h"
#include "nodeManager/events/ErrorEvent.h"
#include "nodeManager/events/JausMessageEvent.h"

JtcpInterface::JtcpInterface(FileLoader *configData, EventHandler *handler, JausCommunicationManager *commMngr)
{
	this->commMngr = commMngr;
	this->eventHandler = handler;
	this->name = JTCP_NAME;
	this->configData = configData;
	
	// Setup our UDP Socket
	if(!this->openSocket())
	{
		throw "JtcpInterface: Could not open socket\n";
	}
}

bool JtcpInterface::startInterface(void)
{
	// Set our thread running flag
	this->running = true;

	// Setup our pThread
	this->startThread();

	// Setup our receiveThread
	this->startRecvThread();

	return true;
}

bool JtcpInterface::stopInterface(void)
{
	this->running = false;
	
	// Stop our pThread
	this->stopThread();

	// Stop our receiveThread
	this->stopRecvThread();

	return true;
}

JtcpInterface::~JtcpInterface(void)
{
	if(running)
	{
		this->stopInterface();
	}
	this->closeSocket();

	// TODO: Check our threadIds to see if they terminated properly
}

InetAddress JtcpInterface::getInetAddress(void)
{
	return this->socket->address;
}

bool JtcpInterface::processMessage(JausMessage message)
{
	// if cmpt == BROADCAST || inst == BROADCAST send unicast to all components
	if( message->destination->component == JAUS_BROADCAST_COMPONENT_ID || message->destination->instance == JAUS_BROADCAST_INSTANCE_ID )
	{
		// Unicast to all known subsystems
		HASH_MAP<int, JtcpTransportData>::iterator iter;
		for(iter = addressMap.begin(); iter != addressMap.end(); iter++)
		{
			sendJausMessage(iter->second, message);
		}
		jausMessageDestroy(message);
		return true;
	}
	else
	{
		// Unicast
		if(addressMap.find(jausAddressHash(message->destination)) != addressMap.end())
		{
			sendJausMessage(addressMap.find(jausAddressHash(message->destination))->second, message);
			jausMessageDestroy(message);
			return true;
		}
		else
		{
			// Don't know how to send this message
			jausMessageDestroy(message);
			return false;
		}
	}
}

void JtcpInterface::run()
{
	// Lock our mutex
	pthread_mutex_lock(&threadMutex);

	while(this->running)
	{
		pthread_cond_wait(&threadConditional, &threadMutex);
		
		while(!this->queue.isEmpty())
		{
			// Pop a packet off the queue and send it off
			processMessage(queue.pop());
		}
	}
	pthread_mutex_unlock(&threadMutex);
}

std::string JtcpInterface::toString()
{
	char ret[256] = {0};
	char buf[80] = {0};
	if(this->socket)
	{
		inetAddressToBuffer(this->socket->address, buf, 80);
		sprintf(ret, "%s %s:%d", JTCP_NAME, buf, this->socket->port);
		return ret;
	}
	else
	{
		sprintf(ret, "%s Invalid.", JTCP_NAME);
		return ret;
	}
}

bool JtcpInterface::openSocket(void)
{
	double socketTimeoutSec = 0;
	unsigned char socketTTL = 0;

	// Read Component Configuration
	// Port Number
	this->portNumber = JTCP_DATA_PORT;

	// IP Address
	this->ipAddress = inetAddressGetLocalHost();
	if(this->ipAddress == NULL)
	{
		// Cannot open specified IP Address
		char errorString[128] = {0};
		sprintf(errorString, "Could not open default IP Address: %s", JTCP_DEFAULT_COMPONENT_IP.c_str());
		
		ErrorEvent *e = new ErrorEvent(ErrorEvent::Configuration, __FUNCTION__, __LINE__, errorString);
		this->eventHandler->handleEvent(e);
		return false;
	}

	// Timeout
	socketTimeoutSec = JTCP_DEFAULT_COMPONENT_TIMEOUT_SEC;

	// Header Compression
	// No header compression for Component Interfaces
	this->supportHeaderCompression = false;

	// Create Socket
	this->socket = streamServerCreate(this->portNumber, ipAddress);
	if(!this->socket)
	{
		// Error creating our socket
		char errorString[128] = {0};
		char buf[24] = {0};
		
		inetAddressToBuffer(this->ipAddress, buf, 24);
		sprintf(errorString, "Could not open socket: %s:%d", buf, this->portNumber);
		ErrorEvent *e = new ErrorEvent(ErrorEvent::Configuration, __FUNCTION__, __LINE__, errorString);
		this->eventHandler->handleEvent(e);
		
		inetAddressDestroy(this->ipAddress);
		return false;
	}
	else
	{
		this->ipAddress->value = socket->address->value;
		this->portNumber = socket->port;
	}
	inetAddressDestroy(this->ipAddress);

	// Setup Timeout
	streamServerSetTimeout(this->socket, socketTimeoutSec);

	return true;
}

void JtcpInterface::sendJausMessage(JtcpTransportData data, JausMessage message)
{
	StreamPacket packet = NULL;
	int result;

	// Sends a JAUS Message with no transport header
	packet = streamPacketCreate();
	packet->bufferSizeBytes = (int) jausMessageSize(message);
	packet->buffer = (unsigned char *) calloc(packet->bufferSizeBytes, 1);
	packet->port = data.port;
	packet->address->value = data.addressValue;

	if(jausMessageToBuffer(message, packet->buffer, packet->bufferSizeBytes))
	{
		result = streamServerSend(this->socket, packet);
	}

	free(packet->buffer);
	streamPacketDestroy(packet);
}

void JtcpInterface::closeSocket(void)
{
	streamServerDestroy(this->socket);
}

void JtcpInterface::startRecvThread()
{
	pthread_attr_init(&this->recvThreadAttr);
	pthread_attr_setdetachstate(&this->recvThreadAttr, PTHREAD_CREATE_JOINABLE);
	this->recvThreadId = pthread_create(&this->recvThread, &this->recvThreadAttr, JtcpRecvThread, this);
	pthread_attr_destroy(&this->recvThreadAttr);
}

void JtcpInterface::stopRecvThread()
{
	pthread_join(this->recvThread, NULL);
}

void JtcpInterface::recvThreadRun()
{
	StreamPacket packet;
	JausMessage rxMessage;
	JtcpTransportData data;
	int index = 0;
	long bytesRecv = 0;

	packet = streamPacketCreate();
	packet->bufferSizeBytes = JTCP_MAX_PACKET_SIZE;
	packet->buffer = (unsigned char *) calloc(packet->bufferSizeBytes, 1);
	
	while(this->running)
	{
		index = 0;
		bytesRecv = streamServerReceive(this->socket, packet);
		
		if(bytesRecv > 0)
		{
			rxMessage = jausMessageCreate();
			if(!jausMessageFromBuffer(rxMessage, packet->buffer, packet->bufferSizeBytes))
			{
				// Error receiving message
				jausMessageDestroy(rxMessage);
				continue;
			}

			// Add to transportMap
			data.addressValue = packet->address->value;
			data.port = packet->port;
			this->addressMap[jausAddressHash(rxMessage->source)] = data;

			// Received message Event	
			JausMessage tempMessage = jausMessageClone(rxMessage);
			JausMessageEvent *e = new JausMessageEvent(tempMessage, this, JausMessageEvent::Inbound);
			this->eventHandler->handleEvent(e);

			// Send to Communications manager
			this->commMngr->receiveJausMessage(rxMessage, this);
		}
	}

	free(packet->buffer);
	streamPacketDestroy(packet);
}

void *JtcpRecvThread(void *obj)
{
	JtcpInterface *jtcpInterface = (JtcpInterface *)obj;
	jtcpInterface->recvThreadRun();
	return NULL;
}
