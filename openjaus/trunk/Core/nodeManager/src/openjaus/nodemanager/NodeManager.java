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
// File Name: NodeManager.java
//
// Written By: Tom Galluzzo (galluzzo AT gmail DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: The NodeManager class contains the main method and is responsible for user I/O, spawning and connecting the essential
//				Node Manager objects and running all threads.
package openjaus.nodemanager;

import openjaus.libjaus.*;
import java.util.*;
import java.io.*;
import java.net.*;

import org.apache.log4j.Logger;

public class NodeManager
{
	/** Logger that knows our class name */
	static private final Logger log = Logger.getLogger(NodeManager.class);


	// JAUS and State machine related variables
	private static JausSubsystem subsystem;
	private static JausNode node;
	private static JausComponent component;
	private static JausAddress address;

	private static int multicastTimeToLive = 5;	
	private static int heartBeatPeriodMilliSec = 1000;
	private static boolean running = true;
	
	private static Properties properties;

	private static int nodePort;
	private static int componentMessagePort;
	private static int componentInterfacePort;

	private static DataRepository dataRepository;
	private static FileLogger fileLogger;
		
	private static InetAddress subsIpAddress;
	private static InetAddress nodeIpAddress;
	private static InetAddress componentIpAddress;
	private static InetAddress subsGroupAddress;
	private static InetAddress nodeGroupAddress;
	
	private static MulticastSocket nodeSocket;
	private static MulticastSocket subsSocket;	
	private static DatagramSocket componentSocket;
	
	private static ComponentInterface componentInterface;

	private static Monitor nodeSendMonitor;
	private static Monitor subsSendMonitor;
	private static Monitor messageRouterMonitor;
	
	private static Queue nodeSendQueue;
	private static Queue nodeReceiveQueue;
	
	private static SendThread nodeSendThread;
	private static ReceiveThread nodeReceiveThread;

	private static Queue subsSendQueue;

	private static SendThread subsSendThread;
	private static ReceiveThread subsReceiveThread;

	private static Queue componentReceiveQueue;
	private static ReceiveThread componentReceiveThread;

	private static SubsystemTable subsystemTable;

	private static CoreMessageHandler coreMessageHandler;

	private static MessageRouter messageRouter;
	
	private static HeartBeat heartBeat;
	
	public static void main(String[] args)
	{
		// This allows us to change the TTL value
		// TTL > 1 is neccessary for VPN Experiments
		// Has a drawback that this won't work on IPv6 hardware (whatever that means!)
		System.setProperty("java.net.preferIPv4Stack", "true");		
		
		double lastLogTimeMilliSec = 0.0;		

		try
		{
			log.info("NodeManager starting");
			properties = new Properties();
			if(args.length > 0)
			{
				System.out.println("Opening Config file "+args[0]);
				properties.load(new FileInputStream(new File(args[0])));
			}
			else
			{
				System.out.println("Opening Config file ./nodeManager.conf");
				properties.load(new FileInputStream(new File("./", "nodeManager.conf")));
			}

			System.out.println(properties.getProperty("COMPONENT_IDENTIFICATION") + " Version: 3.2 (03/22/2006)");
			
			address = new JausAddress();
			address.setSubsystem(Integer.parseInt(properties.getProperty("SUBSYSTEM_ID").trim()));
			address.setNode(Integer.parseInt(properties.getProperty("NODE_ID").trim()));
			address.setComponent(JausComponent.NODE_MANAGER);
			address.setInstance(JausAddress.PRIMARY_INSTANCE);
			System.out.println("JAUS Address: " + address);

			dataRepository = new DataRepository();
		
			NetworkInterface subsInterface = NetworkInterface.getByName(properties.getProperty("SUBSYSTEM_SIDE_INTERFACE"));
			if(subsInterface != null)
			{
				log.info("Subsystem Side Interface: " + subsInterface.getName());				
				Enumeration e = subsInterface.getInetAddresses();
				if(e.hasMoreElements())
				{
					subsIpAddress = (InetAddress)e.nextElement();
					log.info("Subsystem IP Address: " + subsIpAddress);				
				}
			}

			NetworkInterface networkInterface = NetworkInterface.getByName(properties.getProperty("NETWORK_INTERFACE"));
			if(networkInterface  != null){
				log.info("NodeManager: Network Interface: " + networkInterface.getName());				
			}else{
				log.warn("Network interface was null");
				
			}
			
			Enumeration e = networkInterface.getInetAddresses();
			if(e.hasMoreElements())
			{
				nodeIpAddress = (InetAddress)e.nextElement();
				log.info("Node IP Address: " + nodeIpAddress);				
			}
			
			nodeGroupAddress = InetAddress.getByName(properties.getProperty("NODE_GROUP_ADDRESS").trim());
			log.info("Node Side Group Address: " + nodeGroupAddress);				
			
			nodePort = Integer.parseInt(properties.getProperty("NODE_PORT").trim());
			log.info("Node Port: " + nodePort);

			nodeSocket = new MulticastSocket(nodePort);
			nodeSocket.setNetworkInterface(networkInterface); // nodeSocket.setInterface(nodeIpAddress);
			nodeSocket.joinGroup(new InetSocketAddress(nodeGroupAddress, nodePort), networkInterface);
			nodeSocket.setTimeToLive(multicastTimeToLive);			
			
			log.info("Opened Node Side Multicast Socket: " + nodeSocket);				

			if(subsInterface != null)
			{
				subsGroupAddress = InetAddress.getByName(properties.getProperty("SUBSYSTEM_GROUP_ADDRESS").trim());
				log.info("Subsystem Side Group Address: " + subsGroupAddress);				
			
				subsSocket = new MulticastSocket(nodePort);
				subsSocket.setNetworkInterface(subsInterface); //subsSocket.setInterface(subsIpAddress);
				subsSocket.joinGroup(new InetSocketAddress(subsGroupAddress, nodePort), subsInterface);
				subsSocket.setTimeToLive(multicastTimeToLive);
				log.info("Opened Subsystem Side Multicast Socket: " + subsSocket);				
			}
			
			componentMessagePort = Integer.parseInt(properties.getProperty("COMPONENT_MESSAGE_PORT").trim());
			log.info("Component Message Port: " + componentMessagePort);
			
			componentIpAddress = InetAddress.getByName("localhost");
			componentSocket = new DatagramSocket(componentMessagePort, componentIpAddress);
			//System.out.println("NodeManager: Component Side Recv Buff Size: " + componentSocket.getReceiveBufferSize());				
			//System.out.println("NodeManager: Component Side Send Buff Size: " + componentSocket.getSendBufferSize());				
			log.info("Component Side InetAddress: " + componentSocket.getLocalAddress());				
			log.info("Opened Component Side Datagram Socket: " + componentSocket);				

			componentInterfacePort = Integer.parseInt(properties.getProperty("COMPONENT_INTERFACE_PORT").trim());
			log.info("Component Interface Port: " + componentInterfacePort);
			
			// Instantiate JAUS self subsystem, node and component
			subsystem = new JausSubsystem(address.getSubsystem());
			subsystem.setIdentification(properties.getProperty("SUBSYSTEM_IDENTIFICATION").trim());
			node = new JausNode(address.getNode(), nodeIpAddress, nodePort);
			node.setIdentification(properties.getProperty("NODE_IDENTIFICATION").trim());
			component = new JausComponent(address, 0, nodePort);
			component.setIdentification(properties.getProperty("COMPONENT_IDENTIFICATION").trim());
			node.setSubsystem(subsystem); // Set parent subsystem
	 		component.setNode(node); // Set parent node
	 		node.addComponent(component);
			subsystem.addNode(node);
			
			nodeSendMonitor = new Monitor();
			messageRouterMonitor = new Monitor();
						
			nodeSendQueue = new Queue("Node Send Queue", nodeSendMonitor);
			nodeReceiveQueue = new Queue("Node Receive Queue", messageRouterMonitor);

			if(subsSocket != null)
			{
				log.info("Creating subsystem side threads");
				subsSendMonitor = new Monitor();
				subsSendQueue = new Queue("Subsystem Send Queue", subsSendMonitor);
				subsSendThread = new SendThread(subsSocket, subsSendQueue, subsSendMonitor);
				subsReceiveThread = new ReceiveThread("Subsystem Receive Thread", subsSocket, nodeReceiveQueue);
			}

			nodeSendThread = new SendThread(nodeSocket, nodeSendQueue, nodeSendMonitor);
			nodeReceiveThread = new ReceiveThread("Node Receive Thread", nodeSocket, nodeReceiveQueue);
			
			componentReceiveQueue = new Queue("Component Receive Queue", messageRouterMonitor);
			componentReceiveThread = new ReceiveThread("Component Receive Thread", componentSocket, componentReceiveQueue);
			
			subsystemTable = new SubsystemTable(componentReceiveQueue);

			componentInterface = new ComponentInterface(componentInterfacePort, subsystemTable);
			
			coreMessageHandler = new CoreMessageHandler(componentReceiveQueue, nodeSendQueue, subsystemTable);
			
			messageRouter = new MessageRouter(nodeSendQueue, nodeReceiveQueue, componentSocket, componentReceiveQueue, subsystemTable, messageRouterMonitor, coreMessageHandler);
			
			heartBeat = new HeartBeat(heartBeatPeriodMilliSec, nodeSendQueue, componentReceiveQueue, subsystemTable);

			String logFileName = properties.getProperty("LOG_FILE");
			if (logFileName == null || logFileName.trim().equals("")) logFileName = "log/nodeManagerLog.csv";
			fileLogger = new FileLogger(dataRepository, logFileName);

			componentInterface.start();
			if(subsReceiveThread != null)
			{
				subsReceiveThread.start();
			}
			nodeSendThread.start();
			nodeReceiveThread.start();
			componentReceiveThread.start();
			messageRouter.start();
			heartBeat.start();

			byte[] inputBuffer = new byte[256];			
			int inputCount = 0;
			while(inputBuffer[0] != 27)
			{
				inputCount = System.in.read(inputBuffer);
				switch(inputBuffer[0])
				{
					case 't':
						System.out.print(subsystemTable.toString());
						break;

					case 'T':
						System.out.print(subsystemTable.toDetailedString());
						break;
						
					case 's':
						if(inputBuffer[1] == 's' && inputBuffer[2] == ' ')
						{
							int i;
							for(i = 3; i < inputBuffer.length; i++)
							{
								if(inputBuffer[i] == '\n')
								{
									break;
								}
							}
							try
							{
								String intString = new String(inputBuffer, 3, i - 3);
								System.out.print(subsystemTable.subsystemToString(Integer.parseInt(intString)));
							}
							catch(Exception except)
							{
								System.out.println("NodeManager: Error! Incorrect Print Subsystem Syntax");
							}
						}
						break;
						
					case 'd':
						System.out.println("Data List...");
						Iterator dataEntries  = dataRepository.entrySet().iterator();
						while(dataEntries.hasNext())
						{
							System.out.println(""+((Map.Entry)dataEntries.next()).getKey());
						}
						break;
				}
			}
			System.out.println("NodeManager: Shutting Down");
			running = false;
		}
		catch(Exception e) 
		{
			log.warn("NodeManager exception in main loop", e);
			running = false;
		}

	}

	public static boolean isRunning()
	{
		return running;
	}

	public static DataRepository getDataRepository()
	{
		return dataRepository;
	}

	public static JausComponent getComponent()
	{
		return component;
	}
	
	public static InetAddress getNodeSideIpAddress()
	{
		return nodeIpAddress;
	}

	public static InetAddress getComponentSideIpAddress()
	{
		return componentIpAddress;
	}
	
	public static InetAddress getNodeGroupAddress()
	{
		return nodeGroupAddress;
	}

	public static InetAddress getSubsystemGroupAddress()
	{
		return subsGroupAddress;
	}

	public static InetAddress getSubsystemIpAddress()
	{
		return subsIpAddress;
	}
	
	public static MulticastSocket getSubsystemSocket()
	{
		return subsSocket;
	}
	
	public static int getNodePort()
	{
		return nodePort;
	}
}

