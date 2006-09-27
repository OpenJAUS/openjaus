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
// File Name: SendThread.java
//
// Written By: Tom Galluzzo (galluzzo AT gmail DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This thread is responsible for poping packets off of a Queue and sending them on a UDP socket

package openjaus.nodemanager;
import java.net.*;

import org.apache.log4j.Logger;

public class SendThread extends Thread
{
	/** Logger that knows our class name */
	static private final Logger log = Logger.getLogger(SendThread.class);

	static private final Counter counter = new Counter("OJSendThread");

	static long sendCount = 0;
	MulticastSocket sendSocket;
	MulticastSocket subsSocket;
	Queue queue;
	Monitor monitor;
	DataRepository dataRepository;

	public SendThread(MulticastSocket sendSocket, Queue queue, Monitor monitor)
	{
		this.setName(counter.nextName());
		this.sendSocket = sendSocket;
		this.queue = queue;
		this.monitor = monitor;
		dataRepository = NodeManager.getDataRepository();
		dataRepository.put("Messages Sent Count", new Long(sendCount));
	}
	
	public void run()
	{
		log.info("SendThread starting");
		while(NodeManager.isRunning())
		{
			try
			{
				if(queue.isEmpty())
				{
					monitor.waitForSignal(1000);
				}
				
				if(!queue.isEmpty())
				{
					DatagramPacket packet = (DatagramPacket)queue.pop();
					if(log.isDebugEnabled())log.debug("Sending msg to: " + packet.getAddress());
					sendSocket.send(packet);
					dataRepository.put("Messages Sent Count", new Long(++sendCount));
				}
			}
			catch (Exception e)
			{
				dataRepository.put("SendThread Exception", e);
				log.warn("Could not send message", e);

			}
		}
	    log.warn("SendThread: Shutting down");			

	}
		
	public long getSendCount()
	{
		return sendCount;
	}
	
}
