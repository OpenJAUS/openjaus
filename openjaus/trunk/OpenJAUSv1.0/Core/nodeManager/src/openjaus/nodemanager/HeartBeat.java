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
// File Name: HeartBeat.java
//
// Written By: Tom Galluzzo (galluzzo AT gmail DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This class runs a thread that generates a JAUS Heartbeat message, which keeps the NodeManager active and
//				Informs other NodeManagers and JAUS entities of this NodeManager's existence.

package openjaus.nodemanager;

import openjaus.libjaus.*;
import openjaus.libjaus.message.inform.*;
import java.net.*;
import org.apache.log4j.Logger;

class HeartBeat extends Thread
{
	/** Logger that knows our class name */
	static private final Logger log = Logger.getLogger(HeartBeat.class);

	/** Tracks number of threads of this type */
	static private final Counter counter = new Counter("OJHeartBeat");

	static long beatCount  = 0;
	long beatPerioidMilliSec;
	Queue nodeSendQueue;
	Queue componentReceiveQueue;
	SubsystemTable subsystemTable;
	JausAddress thisAddress;
	JausComponent thisComponent;
	JausNode thisNode;
	MulticastSocket subsystemSocket;
	InetAddress nodeGroupAddress;
	InetAddress subsGroupAddress;
	InetAddress ipAddress;
	DataRepository dataRepository;
	int nodePort;
	
	public HeartBeat(long beatPerioidMilliSec, Queue outputQueue, Queue componentQueue, SubsystemTable subsystemTable)
	{
		this.setName(counter.nextName());
	    this.beatPerioidMilliSec = beatPerioidMilliSec;
		this.nodeSendQueue = outputQueue;
		this.subsystemTable = subsystemTable;
		this.componentReceiveQueue = componentQueue;
		thisComponent = NodeManager.getComponent();
		thisAddress = thisComponent.getAddress();
		thisNode = thisComponent.getNode();
		
		subsystemSocket = NodeManager.getSubsystemSocket();
		nodeGroupAddress = NodeManager.getNodeGroupAddress();
		subsGroupAddress = NodeManager.getSubsystemGroupAddress();
		ipAddress = NodeManager.getNodeSideIpAddress();
		nodePort = NodeManager.getNodePort();

		dataRepository = NodeManager.getDataRepository();
		dataRepository.put("Heartbeat Count", new Long(beatCount));
		if(log.isDebugEnabled())log.debug("Heartbeat Count:"+ beatCount);
	}

	public void run()
	{
	    try
	    {
	    	if(log.isDebugEnabled())log.debug("Heartbeat starting");
	        ReportHeartbeatPulseMessage heartBeatMessage = new ReportHeartbeatPulseMessage();
			heartBeatMessage.setSource(thisAddress);
			
			heartBeatMessage.getDestination().setSubsystem(thisAddress.getSubsystem());
			heartBeatMessage.getDestination().setNode(JausAddress.BROADCAST_NODE);
			heartBeatMessage.getDestination().setComponent(JausAddress.NODE_MANAGER_COMPONENT);
			heartBeatMessage.getDestination().setInstance(thisAddress.getInstance());
			byte[] buffer = new byte[heartBeatMessage.udpSize()];
			heartBeatMessage.toJausUdpBuffer(buffer);
			DatagramPacket packet = new DatagramPacket(buffer, buffer.length, nodeGroupAddress, nodePort);

			heartBeatMessage.getDestination().setSubsystem(thisAddress.getSubsystem());
			heartBeatMessage.getDestination().setNode(thisAddress.getNode());
			heartBeatMessage.getDestination().setComponent(JausAddress.BROADCAST_COMPONENT);
			heartBeatMessage.getDestination().setInstance(JausAddress.BROADCAST_INSTANCE);
			buffer = new byte[heartBeatMessage.size()];
			heartBeatMessage.toJausBuffer(buffer);
			DatagramPacket cmptPacket = new DatagramPacket(buffer, buffer.length, thisNode.getIpAddress(), thisComponent.getPort());

			if(subsystemSocket != null)
			{
				heartBeatMessage.getDestination().setSubsystem(JausAddress.BROADCAST_SUBSYSTEM);
				heartBeatMessage.getDestination().setNode(JausAddress.BROADCAST_NODE);
				heartBeatMessage.getDestination().setComponent(JausAddress.NODE_MANAGER_COMPONENT);
				heartBeatMessage.getDestination().setInstance(thisAddress.getInstance());
				buffer = new byte[heartBeatMessage.udpSize()];
				heartBeatMessage.toJausUdpBuffer(buffer);
				DatagramPacket subsPacket = new DatagramPacket(buffer, buffer.length, subsGroupAddress, nodePort);

				while(NodeManager.isRunning())
				{
					nodeSendQueue.push(packet);
					componentReceiveQueue.push(cmptPacket);
					subsystemSocket.send(subsPacket);
					subsystemTable.refresh();
					dataRepository.put("Heartbeat Count", new Long(++beatCount));
					sleep(beatPerioidMilliSec);
				}

			}
			else
			{
				while(NodeManager.isRunning())
				{
					nodeSendQueue.push(packet);
					componentReceiveQueue.push(cmptPacket);
					subsystemTable.refresh();
					dataRepository.put("Heartbeat Count", new Long(++beatCount));
					sleep(beatPerioidMilliSec);
				}				
			}
		    log.info("Heartbeat: Shutting down");			
	    }
	    catch(Exception e)
	    {
			NodeManager.getDataRepository().put("HeartBeat Exception", e);
	        log.warn("HeartBeat exception",e);
	        
	    }
	}
	
	public long getBeatCount()
	{
		return beatCount;
	}
	
}
