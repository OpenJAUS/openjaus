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
// File Name: MessageRouter.java
//
// Written By: Tom Galluzzo (galluzzo AT gmail DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: 

package openjaus.nodemanager;

import openjaus.libjaus.*;
import openjaus.libjaus.message.*;
import java.net.*;
import java.util.Enumeration;
import org.apache.log4j.Logger;

public class MessageRouter extends Thread
{
	
	/** Logger that knows our class name */
	static private final Logger log = Logger.getLogger(MessageRouter.class);

	/** Keeps tracks of number of threads of this type */
	static private final Counter counter = new Counter("OJMessageRouter");


	DataRepository dataRepository;
	Queue nodeSendQueue;
	Queue nodeReceiveQueue;
	DatagramSocket componentSocket;
	Queue componentReceiveQueue;
	SubsystemTable subsystemTable;
	Monitor monitor;
	CoreMessageHandler coreMessageHandler;
	JausSubsystem thisSubsystem;
	JausNode thisNode;
	JausComponent thisComponent;
	JausAddress thisAddress;
	InetAddress nodeIpAddress;
	InetAddress componentSideIpAddress;
	int nodePort;
	
	public MessageRouter(	Queue nodeSendQueue, Queue nodeReceiveQueue, DatagramSocket componentSocket, Queue componentReceiveQueue, 
	        				SubsystemTable subsystemTable, Monitor monitor, CoreMessageHandler coreMessageHandler)
	{
		this.setName(counter.nextName());
//		messageBlock = 0;
//		messageCount = 0;
		dataRepository = NodeManager.getDataRepository();
//		dataRepository.put("MessageRouter Message Count", new Long(messageCount));
//		dataRepository.put("MessageRouter Message Block", new Integer(messageBlock));
		
		this.nodeSendQueue = nodeSendQueue;
		this.nodeReceiveQueue = nodeReceiveQueue;
		this.componentSocket = componentSocket;
		this.componentReceiveQueue = componentReceiveQueue;
		this.subsystemTable = subsystemTable;
		this.monitor = monitor;
		this.coreMessageHandler = coreMessageHandler;

		thisComponent = NodeManager.getComponent();
		thisNode = thisComponent.getNode();
		thisSubsystem = thisNode.getSubsystem();
		thisAddress = thisComponent.getAddress();

		nodeIpAddress = NodeManager.getNodeSideIpAddress();		
		componentSideIpAddress = NodeManager.getComponentSideIpAddress();
		nodePort = NodeManager.getNodePort();
	}

	// NOTE: This complies with Node Side Routing Table v0.2 (see NodeManager Design docs)
	private void routeNodeSideMessage(JausMessage message, InetAddress sourceIP, int sourcePort)
	{
		JausAddress destination = message.getDestination();
		JausAddress source = message.getSource();

		if(source.getSubsystem() == thisAddress.getSubsystem() && source.getNode() == thisAddress.getNode())
		{
			// turns out this should not be a warning, it happens all the time, as 
			// we hear our own multicasts
			//log.warn("Message from a local component has entered Node Manager from Node side queue");
		}
		else
		{
			if (destination.getSubsystem() == JausAddress.BROADCAST_SUBSYSTEM || destination.getSubsystem() == thisAddress.getSubsystem())
			{
				if (destination.getNode() == JausAddress.BROADCAST_NODE || destination.getNode() == thisAddress.getNode())
				{
					routeToLocalComponents(message, sourceIP, sourcePort);
				}
				else
				{
					log.warn("destination node is not this node");
					
				}
			}
			else
			{
				log.warn("destination subsystem is not this subsystem");
				
			}
		}
	}// routeNodeSideMessage

	// NOTE: This complies with Component Side Routing Table v0.1 (see NodeManager Design docs)
	private void routeComponentSideMessage(JausMessage message, InetAddress sourceIp, int sourcePort)
	{
		JausAddress destination = message.getDestination();
		JausAddress source = message.getSource();

		//System.out.println("Routing msg from: " + source + " to: " + destination);
		
		if(source.getSubsystem() == thisAddress.getSubsystem() && source.getNode() == thisAddress.getNode())
		{
			if(destination.getSubsystem() == JausAddress.BROADCAST_SUBSYSTEM)
			{
				if(destination.getNode() == JausAddress.BROADCAST_NODE)
				{
					// send to all nodes and all local components
					sendToEveryone(message);
					routeToLocalComponents(message, sourceIp, sourcePort);
				}
				else
				{
					sendToAllNodesX(message);
					if (destination.getNode() == thisAddress.getNode())
					{
						routeToLocalComponents(message, sourceIp, sourcePort);
					}
				}
			}
			else if(destination.getSubsystem() == thisAddress.getSubsystem())
			{
				if(destination.getNode() == JausAddress.BROADCAST_NODE)
				{
					// send to all local nodes and all local components
					sendToEveryoneOnSubsystem(message);
					routeToLocalComponents(message, sourceIp, sourcePort);
				}
				else if(destination.getNode() == thisAddress.getNode())
				{
					routeToLocalComponents(message, sourceIp, sourcePort);
				}
				else
				{
					// send to this local node
					sendToNode(message, destination.getSubsystem(), destination.getNode());
				}
			}
			else
			{	
				if (destination.getNode() == JausAddress.BROADCAST_NODE)
				{
					// send to all nodes on that subsystem
					sendToEveryoneOnSubsystem(message);
				}
				else
				{
					// send to that node on that subsystem
					//System.out.println("SendtoNode: " + destination);
					sendToNode(message, destination.getSubsystem(), destination.getNode());
				}
			}
		}
		else
		{
			log.warn("Component-side messages can only come from components on its own node");
			
		}
	}

	private void sendToEveryone(JausMessage message)
	{
		// get all nodes
		Enumeration subsystems = subsystemTable.getSubsystems();
		Enumeration nodes = null;
		JausSubsystem ss = null;
		JausNode node = null;
		while (subsystems.hasMoreElements())
		{
			ss = (JausSubsystem)subsystems.nextElement();
			nodes = ss.elements();
			while (nodes.hasMoreElements())
			{
				node = (JausNode)nodes.nextElement();
				sendToNode(message, ss.getId(), node.getId());
			}
		}
	}

	private void sendToEveryoneOnSubsystem(JausMessage message)
	{
		int subsystemID = message.getDestination().getSubsystem();
		JausSubsystem ss = subsystemTable.getSubsystem(subsystemID);
		Enumeration nodes = ss.elements();
		JausNode node = null;
		
		while (nodes.hasMoreElements())
		{
			node = (JausNode)nodes.nextElement();
			sendToNode(message, subsystemID, node.getId());
		}
	}

	private void sendToAllNodesX(JausMessage message)
	{
		// send to all nodes of number "node" on all subsystems
		int nodeID = message.getDestination().getNode();
		Enumeration subsystems = subsystemTable.getSubsystems();
		JausSubsystem ss = null;
		JausNode node = null;
		while (subsystems.hasMoreElements()) {
			ss = (JausSubsystem)subsystems.nextElement();
			node = ss.getNode(nodeID);
			if (node != null)
			{
				sendToNode(message, ss.getId(), nodeID);
			}
		}
	}

	// this method used to be called sendToDestinationNode

	private void sendToNode(JausMessage message, int subsystem, int node)
	{
		// Send message off to a specific local node
		InetAddress destIpAddress;// = subsystemTable.lookUpIpAddress(subsystem, node);
		Integer destPort;

		try
		{
			if(subsystem == thisSubsystem.getId())
			{
				destIpAddress = subsystemTable.lookUpIpAddress(subsystem, node);
			}
			else
			{
				destIpAddress = InetAddress.getByName("192.168.128." + subsystem);
			}
		}
		catch(Exception e)
		{
			dataRepository.put("MessageRouter Exception", e);
			log.warn("MessageRouter exception" , e);
			return;
		}

		if(node == JausAddress.PRIMARY_NODE_MANAGER_NODE) // HACK: Needed at OPC experiment for other peoples bad node mananagers
		{
			destPort = new Integer(3794);
		}
		else
		{
			if(subsystem == thisSubsystem.getId())
			{
				destPort = new Integer(3794);
			}
			else
			{
				destPort = new Integer(10000 + node);
			}
		}
		
		//System.out.println("Msg router: sending msg to subs: (" + subsystem + ", " + destIpAddress + ") Node: (" + node + ", " + destPort + ")");
		
		if(destIpAddress != null && destPort != null)
		{
			byte[] buffer = new byte[message.udpSize()];
			message.toJausUdpBuffer(buffer);
			DatagramPacket packet = new DatagramPacket(buffer, buffer.length, destIpAddress, destPort.intValue());
			nodeSendQueue.push(packet);		    
		}
		else
		{
			log.warn("Null port or address");

		}
	}

	private void routeToLocalComponents(JausMessage message, InetAddress sourceIp, int sourcePort)
	{
		int destComponent = message.getDestination().getComponent();
		int destInstance = message.getDestination().getInstance();
		
		if(destComponent == JausAddress.BROADCAST_COMPONENT)
		{
			if(destInstance == JausAddress.BROADCAST_INSTANCE)
			{
				// Send to all instances of all components on this node
	    		byte[] buffer = new byte[message.size()];
	    		message.toJausBuffer(buffer);
				Enumeration nodeElements = thisNode.elements();
		        while(nodeElements.hasMoreElements())
		        {
		            JausComponent component = (JausComponent)nodeElements.nextElement();
		    		DatagramPacket packet = new DatagramPacket(buffer, buffer.length, componentSideIpAddress, component.getPort());
		    		try
					{
		    			componentSocket.send(packet);
					}
					catch (Exception e)
					{
						dataRepository.put("MessageRouter Exception", e);
						log.warn("Exception sending to componentSocket", e);
					}
		    	}

				coreMessageHandler.process(message, sourceIp, sourcePort);
			}
			else
			{	
				// Send to the specific instances of all components on this node
				boolean foundAnInstance = false;
	    		byte[] buffer = new byte[message.size()];
	    		message.toJausBuffer(buffer);
				Enumeration nodeElements = thisNode.elements();
		        while(nodeElements.hasMoreElements())
		        {
		            JausComponent component = (JausComponent)nodeElements.nextElement();
		    		if(component.getAddress().getInstance() == destInstance)
		    		{
						foundAnInstance = true;
						
						if(component.equals(thisComponent))
						{
				        	coreMessageHandler.process(message, sourceIp, sourcePort);							
						}
						else
						{
			    			DatagramPacket packet = new DatagramPacket(buffer, buffer.length, componentSideIpAddress, component.getPort());
			    			try
							{
			    				componentSocket.send(packet);
							}
							catch (Exception e)
							{
								dataRepository.put("MessageRouter Exception", e);
								log.warn("Exception sending to componentSocket", e);
							}
						}
		    		}
		    	}

		        if(!foundAnInstance)
		        {
			        log.warn("Could not find instance");
		        }
			}
		}
		else if(destComponent == thisAddress.getComponent())
		{
			if(destInstance == JausAddress.BROADCAST_INSTANCE || destInstance == thisAddress.getInstance())
			{
				coreMessageHandler.process(message, sourceIp, sourcePort);
			}
			else
			{
				log.warn("destination was not this, or a broadcast");
				
			}
		}
		else
		{	
			if(destInstance == JausAddress.BROADCAST_INSTANCE)
			{
				// Send to all instances of the component on this node
				boolean foundAnInstance = false;
	    		byte[] buffer = new byte[message.size()];
	    		message.toJausBuffer(buffer);
				Enumeration nodeElements = thisNode.elements();
		        while(nodeElements.hasMoreElements())
		        {
		            JausComponent component = (JausComponent)nodeElements.nextElement();
		    		if(component.getAddress().getComponent() == destComponent)
		    		{
		    			foundAnInstance = true;
		    			DatagramPacket packet = new DatagramPacket(buffer, buffer.length, componentSideIpAddress, component.getPort());
		    			try
						{
		    				componentSocket.send(packet);
						}
						catch (Exception e)
						{
							dataRepository.put("MessageRouter Exception", e);
							log.warn("MessageRouter could not send", e);
						}
		    		}
		    	}
		        if(!foundAnInstance)
		        {
					log.warn("Could not find instance");
		        }
			}
			else
			{
				// Send to the specific instance of the specific component on this node
				JausComponent component = new JausComponent(message.getDestination());
				component.setNode(thisNode); // Set parent node
		        if(thisNode.contains(component))
		        {
					byte[] buffer = new byte[message.size()];
		    		message.toJausBuffer(buffer);
		            int componentPort = ((JausComponent)thisNode.get(thisNode.indexOf(component))).getPort();
		            DatagramPacket packet = new DatagramPacket(buffer, buffer.length, componentSideIpAddress, componentPort);
	    			try
					{
	    				componentSocket.send(packet);
					}
					catch (Exception e)
					{
						dataRepository.put("MessageRouter Exception", e);
						log.warn("MessageRouter exception sending to componentSocket" , e);
					}
		    	}
		        else
		        {
		        	log.warn("Component does not exist on this Node");
					
		        }
			}
		}
	}
	
	public void run()
	{
		while(NodeManager.isRunning())
		{
			try
			{
				//wait on event signal
				if(nodeReceiveQueue.isEmpty() && componentReceiveQueue.isEmpty()) monitor.waitForSignal(1000);

				if(nodeReceiveQueue.size() > 0)
				{
				    DatagramPacket packet = (DatagramPacket)nodeReceiveQueue.pop();
				    JausMessage message = new JausMessage(packet.getData());
//					if(message.getCommandCode() == 0xD1D0)
//					{
//						messageCount = 0;
//					}
//					else if(message.getCommandCode() == 0xD1D2)
//					{
//						messageBlock++;
//						dataRepository.put("MessageRouter Message Block", new Integer(messageBlock));
//						dataRepository.put("MessageRouter Message Count", new Long(messageCount));
//						System.out.println("MessageRouter Message Block: " + messageBlock + " Count = " + messageCount);
//					}
//					else
//					{
//						messageCount++;
//					}
				    dataRepository.put("MessageRouter Current Message", message);
//				     if(log.isDebugEnabled())log.debug("Current Node Side Message command code:"+ message.getCommandCode());
					routeNodeSideMessage(message, packet.getAddress(), packet.getPort());
				}

				if(componentReceiveQueue.size() > 0)
				{
				    DatagramPacket packet = (DatagramPacket)componentReceiveQueue.pop();
				    JausMessage message = new JausMessage(packet.getData());
//					if(message.getCommandCode() == 0xD1D0)
//					{
//						messageCount = 0;
//					}
//					else if(message.getCommandCode() == 0xD1D2)
//					{
//						messageBlock++;
//						dataRepository.put("MessageRouter Message Block", new Integer(messageBlock));
//						dataRepository.put("MessageRouter Message Count", new Long(messageCount));
//						System.out.println("MessageRouter Message Block: " + messageBlock + " Count = " + messageCount);
//					}
//					else
//					{
//						messageCount++;
//					}
					dataRepository.put("MessageRouter Current Message", message);
//				    if(log.isDebugEnabled())log.debug("Current Component Side Message command code:"+ message.getCommandCode());

					routeComponentSideMessage(message,  packet.getAddress(), packet.getPort());
				}
			}
			catch(Exception e)
			{
				dataRepository.put("MessageRouter Exception", e);
				log.warn("MessageRouter exception" , e);
				
			}
		}
	    log.info("Shutting down");			

	}	
}
