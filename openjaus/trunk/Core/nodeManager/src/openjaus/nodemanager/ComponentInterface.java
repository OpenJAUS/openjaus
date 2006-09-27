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
// File Name: ComponentInterface.java
//
// Written By: Tom Galluzzo (galluzzo AT gmail DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This class handles the NodeManager's side of the component to node manager interface 
// 				It responds to and processes all component requests.  

package openjaus.nodemanager;

import openjaus.libjaus.*;
import java.net.*;
import org.apache.log4j.Logger;

public class ComponentInterface extends Thread
{
	/** Logger that knows our class name */
	static private final Logger log = Logger.getLogger(ComponentInterface.class);
	
	/** Tracks number of threads of this type */
	static private final Counter counter = new Counter("OJComponent");

	public static final int MINIMUM_VALID_COMPONENT_PORT = 1024; // This is a common minimum user reserved port value
	JausAddress thisAddress;
	InetAddress ipAddress;
	int componentInterfacePort;
	DatagramSocket socket;
	SubsystemTable subsystemTable;

	public ComponentInterface(int componentInterfacePort, SubsystemTable subsystemTable)
	{
		this.setName(counter.nextName());
		thisAddress = NodeManager.getComponent().getAddress();
		ipAddress = NodeManager.getComponentSideIpAddress();
	    this.componentInterfacePort = componentInterfacePort;
	    this.subsystemTable = subsystemTable;
		try
		{
			
		    socket = new DatagramSocket(this.componentInterfacePort, ipAddress);
		    socket.setSoTimeout(1000);
		    if(log.isDebugEnabled()){log.debug("Socket created, port:" + this.componentInterfacePort + " ip:" + ipAddress);}
		}
		catch(Exception e)
		{
			NodeManager.getDataRepository().put("ComponentInterface Exception", e);
		    log.warn("Exception creating DatagramSocket", e);
		}
	}
	
	public synchronized void run()
	{
		log.debug("ComponentInterface run()");
		InterfaceMessage replyMessage;
		JausAddress address;
		DatagramPacket outPacket;
		byte[] replyBuffer;
		
		try
		{
			while(NodeManager.isRunning())
			{
			    byte[] inBuffer = new byte[8];
			    DatagramPacket packet = new DatagramPacket(inBuffer, inBuffer.length);
				try
				{
					socket.receive(packet);
				}
				catch(SocketTimeoutException e)
				{
					continue;
				}
				
				InterfaceMessage inMessage = new InterfaceMessage(packet.getData());
				
				switch(inMessage.getCommand())
				{
					case InterfaceMessage.NODE_MANAGER_CHECK_OUT:
						address = new JausAddress();
						address.setInstance(inMessage.getData()[0] & 0xff);
						address.setComponent(inMessage.getData()[1] & 0xff);
						address.setNode(inMessage.getData()[2] & 0xff);
						address.setSubsystem(inMessage.getData()[3] & 0xff);
						if(subsystemTable.checkOutLocalComponent(address))
						{
							// TODO: Send back success reply
						}	
						else
						{
							// TODO: Send back failure reply
						}
						break;
						
					case InterfaceMessage.NODE_MANAGER_CHECK_IN:
					    // System.out.println("ComponentInterface: Received Query JAUS address command from: " + JausComponent.getName(componentId));
					    int componentId = inMessage.getData()[0] & 0xff;
						if(componentId == JausAddress.INVALID_COMPONENT || componentId == JausAddress.BROADCAST_COMPONENT)
						{
						    log.warn("Error: Component attempted to check in with an invalid component ID: " + componentId);
							// TODO: Send back checkin error reply (invalid component number)
						    break;
						}

						int componentMessagePort = (inMessage.getData()[1] & 0xFF) + ((inMessage.getData()[2] & 0xFF) << 8);
						if(componentMessagePort < MINIMUM_VALID_COMPONENT_PORT || packet.getPort() < MINIMUM_VALID_COMPONENT_PORT)
						{
						    log.warn("Error: Component attempted to check in with an invalid port number (" + packet.getPort() + ")");
							// TODO: Send back checkin error reply (invalid port number)
							break;
						}
						
						int instanceId = subsystemTable.checkInLocalComponent(componentId, componentMessagePort);
						if(instanceId == JausAddress.INVALID_INSTANCE)
						{
						    log.warn("Error: Component attempted to check in with an invalid instance number");
							// TODO: Send back checkin error reply (no available instance)							
							break;
						}
						
						replyMessage = new InterfaceMessage();
						replyMessage.setCommand(InterfaceMessage.REPORT_JAUS_ADDRESS);
						replyMessage.getData()[0] = (byte)(instanceId & 0xff);
						replyMessage.getData()[1] = (byte)(componentId & 0xff);
						replyMessage.getData()[2] = (byte)(thisAddress.getNode() & 0xff);
						replyMessage.getData()[3] = (byte)(thisAddress.getSubsystem() & 0xff);
						
				    	replyBuffer = new byte[8];
						replyMessage.pack(replyBuffer);
					    outPacket = new DatagramPacket(replyBuffer, replyBuffer.length, packet.getAddress(), packet.getPort());
					    socket.send(outPacket);
					    break;
					    
					case InterfaceMessage.NODE_MANAGER_VERIFY_ADDRESS:
						address = new JausAddress();
						address.setInstance(inMessage.getData()[0] & 0xff);
						address.setComponent(inMessage.getData()[1] & 0xff);
						address.setNode(inMessage.getData()[2] & 0xff);
						address.setSubsystem(inMessage.getData()[3] & 0xff);						
						JausComponent component = new JausComponent(address, 0, 0);

						int response = 0;
						if(subsystemTable.isComponentInTable(component))
						{
							response = 1;
						}
						if(log.isDebugEnabled())log.debug("Checked address: " + address + " returning: " + response);
						
						replyMessage = new InterfaceMessage();
						replyMessage.setCommand(InterfaceMessage.NODE_MANAGER_ADDRESS_VERIFIED);
						replyMessage.getData()[0] = (byte)(response & 0xff);
						
				    	replyBuffer = new byte[8];
						replyMessage.pack(replyBuffer);
					    outPacket = new DatagramPacket(replyBuffer, replyBuffer.length, packet.getAddress(), packet.getPort());
					    socket.send(outPacket);
					    break;

					case InterfaceMessage.NODE_MANAGER_GET_COMPONENT_ADDRESS_LIST:
						componentId  = inMessage.getData()[0];
					
						if(log.isDebugEnabled())log.debug("Get address for component ID: " + componentId);
						address = subsystemTable.getComponentAddress(componentId);

						replyMessage = new InterfaceMessage();
						replyMessage.setCommand(InterfaceMessage.NODE_MANAGER_COMPONENT_ADDRESS_LIST_RESPONSE);
						
						if(address == null)
						{
							replyMessage.getData()[0] = (byte)(0 & 0xff);
							replyMessage.getData()[1] = (byte)(0 & 0xff);
							replyMessage.getData()[2] = (byte)(0 & 0xff);
							replyMessage.getData()[3] = (byte)(0 & 0xff);
							if(log.isDebugEnabled())log.debug("Get address for component ID: " + componentId + " returning: 0.0.0.0");
						}
						else	
						{
							replyMessage.getData()[0] = (byte)(address.getInstance() & 0xff);
							replyMessage.getData()[1] = (byte)(address.getComponent() & 0xff);
							replyMessage.getData()[2] = (byte)(address.getNode() & 0xff);
							replyMessage.getData()[3] = (byte)(address.getSubsystem() & 0xff);							
							if(log.isDebugEnabled())log.debug("Get address for component ID: " + componentId + " returning: " + address);
						}
						
				    	replyBuffer = new byte[8];
						replyMessage.pack(replyBuffer);
					    outPacket = new DatagramPacket(replyBuffer, replyBuffer.length, packet.getAddress(), packet.getPort());
					    socket.send(outPacket);
					    break;

					case InterfaceMessage.NODE_MANAGER_LOOKUP_ADDRESS:
						address = new JausAddress();
						address.setInstance(inMessage.getData()[0] & 0xff);
						address.setComponent(inMessage.getData()[1] & 0xff);
						address.setNode(inMessage.getData()[2] & 0xff);
						address.setSubsystem(inMessage.getData()[3] & 0xff);						
						if(log.isDebugEnabled())log.debug("Looking Up Address: " + address);

						replyMessage = new InterfaceMessage();
						replyMessage.setCommand(InterfaceMessage.NODE_MANAGER_LOOKUP_ADDRESS_RESPONSE);
						
						if(subsystemTable.lookUpAddressInSystem(address))
						{
							replyMessage.getData()[4] = (byte)1;
							if(log.isDebugEnabled())log.debug("Lookup Address Found: " + address);
						}
						else
						{
							replyMessage.getData()[4] = (byte)0;							
							if(log.isDebugEnabled())log.debug("Lookup Address NOT Found: " + address);
						}
						
						replyMessage.getData()[0] = (byte)(address.getInstance() & 0xff);
						replyMessage.getData()[1] = (byte)(address.getComponent() & 0xff);
						replyMessage.getData()[2] = (byte)(address.getNode() & 0xff);
						replyMessage.getData()[3] = (byte)(address.getSubsystem() & 0xff);							
						
				    	replyBuffer = new byte[8];
						replyMessage.pack(replyBuffer);
					    outPacket = new DatagramPacket(replyBuffer, replyBuffer.length, packet.getAddress(), packet.getPort());
					    socket.send(outPacket);
					    break;

					case InterfaceMessage.NODE_MANAGER_LOOKUP_SERVICE_ADDRESS:
						address = new JausAddress();
						address.setInstance(inMessage.getData()[0] & 0xff);
						address.setComponent(inMessage.getData()[1] & 0xff);
						address.setNode(inMessage.getData()[2] & 0xff);
						address.setSubsystem(inMessage.getData()[3] & 0xff);			
						
						int commandCode = (inMessage.getData()[4] & 0xFF) + ((inMessage.getData()[5] & 0xFF) << 8);
						
						int serviceCommandType = (inMessage.getData()[6] & 0xFF);
						if(log.isDebugEnabled())log.debug("Looking Up Address: " + address);

						replyMessage = new InterfaceMessage();
						replyMessage.setCommand(InterfaceMessage.NODE_MANAGER_LOOKUP_SERVICE_ADDRESS_RESPONSE);
						
						if(subsystemTable.lookUpServiceAddressInSystem(address, commandCode, serviceCommandType))
						{
							replyMessage.getData()[4] = (byte)1;
							if(log.isDebugEnabled())log.debug("Lookup Address Found: " + address);
						}
						else
						{
							replyMessage.getData()[4] = (byte)0;							
							if(log.isDebugEnabled())log.debug("Lookup Address NOT Found: " + address);
						}
						
						replyMessage.getData()[0] = (byte)(address.getInstance() & 0xff);
						replyMessage.getData()[1] = (byte)(address.getComponent() & 0xff);
						replyMessage.getData()[2] = (byte)(address.getNode() & 0xff);
						replyMessage.getData()[3] = (byte)(address.getSubsystem() & 0xff);							
						
				    	replyBuffer = new byte[8];
						replyMessage.pack(replyBuffer);
					    outPacket = new DatagramPacket(replyBuffer, replyBuffer.length, packet.getAddress(), packet.getPort());
					    socket.send(outPacket);
					    break;

					case InterfaceMessage.NODE_MANAGER_LOOKUP_SERVICE_ADDRESS_LIST:
						address = new JausAddress();
						address.setInstance(inMessage.getData()[0] & 0xff);
						address.setComponent(inMessage.getData()[1] & 0xff);
						address.setNode(inMessage.getData()[2] & 0xff);
						address.setSubsystem(inMessage.getData()[3] & 0xff);			
						
						commandCode = (inMessage.getData()[4] & 0xFF) + ((inMessage.getData()[5] & 0xFF) << 8);
						serviceCommandType = (inMessage.getData()[6] & 0xFF);
		
						//System.out.println("CmptInterface: Get address for component ID: " + componentId);
						address = subsystemTable.lookupServiceAddressList(address, commandCode, serviceCommandType);

						replyMessage = new InterfaceMessage();
						replyMessage.setCommand(InterfaceMessage.NODE_MANAGER_LOOKUP_SERVICE_ADDRESS_LIST_RESPONSE);
						
						if(address == null)
						{
							replyMessage.getData()[0] = (byte)(0 & 0xff);
							replyMessage.getData()[1] = (byte)(0 & 0xff);
							replyMessage.getData()[2] = (byte)(0 & 0xff);
							replyMessage.getData()[3] = (byte)(0 & 0xff);
							replyMessage.getData()[4] = (byte)0;
							//System.out.println("CmptInterface: Get address for component ID: " + componentId + " returning: 0.0.0.0");
						}
						else	
						{
							replyMessage.getData()[0] = (byte)(address.getInstance() & 0xff);
							replyMessage.getData()[1] = (byte)(address.getComponent() & 0xff);
							replyMessage.getData()[2] = (byte)(address.getNode() & 0xff);
							replyMessage.getData()[3] = (byte)(address.getSubsystem() & 0xff);							
							replyMessage.getData()[4] = (byte)1;
							//System.out.println("CmptInterface: Get address for component ID: " + componentId + " returning: " + address);
						}
						
				    	replyBuffer = new byte[8];
						replyMessage.pack(replyBuffer);
					    outPacket = new DatagramPacket(replyBuffer, replyBuffer.length, packet.getAddress(), packet.getPort());
					    socket.send(outPacket);
					    break;
					    
					default:
					    log.info("Received unknown message command");
						break;
				}
			}
		    log.warn("Shutting down");
		}
		catch (Exception e)
		{
			NodeManager.getDataRepository().put("ComponentInterface Exception", e);
			log.warn("Exception",e);
			
		}
	}
	
	public class InterfaceMessage
	{
	    public static final int NODE_MANAGER_CHECK_IN								= 0x01;
	    public static final int REPORT_JAUS_ADDRESS									= 0x02;
	    public static final int NODE_MANAGER_CHECK_OUT								= 0x03;
	    public static final int NODE_MANAGER_VERIFY_ADDRESS							= 0x04;
	    public static final int NODE_MANAGER_ADDRESS_VERIFIED						= 0x05;
	    public static final int NODE_MANAGER_GET_COMPONENT_ADDRESS_LIST				= 0x06;
	    public static final int NODE_MANAGER_COMPONENT_ADDRESS_LIST_RESPONSE		= 0x07;
	    public static final int NODE_MANAGER_LOOKUP_ADDRESS							= 0x08;
	    public static final int NODE_MANAGER_LOOKUP_ADDRESS_RESPONSE				= 0x09;
	    public static final int NODE_MANAGER_LOOKUP_SERVICE_ADDRESS					= 0x0A;
	    public static final int NODE_MANAGER_LOOKUP_SERVICE_ADDRESS_RESPONSE		= 0x0B;
	    public static final int NODE_MANAGER_LOOKUP_SERVICE_ADDRESS_LIST			= 0x0C;
	    public static final int NODE_MANAGER_LOOKUP_SERVICE_ADDRESS_LIST_RESPONSE	= 0x0D;
	    
	    int command;
	    byte[] data;
	    
	    public InterfaceMessage()
	    {
	        command = 0;
	        data = new byte[7];
	    }

	    public InterfaceMessage(byte[] buffer)
	    {
	        data = new byte[7];
	        unpack(buffer);
	    }
	    
	    public int getCommand()
	    {
	        return command;
	    }
	    
	    public void setCommand(int command)
	    {
	        if(command > 0 && command < 256)
	            this.command = command;
	    }

	    public byte[] getData()
	    {
	        return data;
	    }
	    
	    public void unpack(byte[] buffer)
	    {
	        command = buffer[0] & 0xFF;
	        System.arraycopy(buffer, 1, data, 0, 7);
	    }

	    public void pack(byte[] buffer)
	    {
	       buffer[0] = (byte)(command & 0xFF);
	       System.arraycopy(data, 0, buffer, 1, 7);
	    }
	    
	}
	
}
