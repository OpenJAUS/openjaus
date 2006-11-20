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
// File Name: SubsystemTable.java
//
// Written By: Tom Galluzzo (galluzzo AT gmail DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: The SubsystemTable class manages all of the JAUS system and subsystem information
// 				such as addresses, ipaddresses, port numbers.
package openjaus.nodemanager;

import openjaus.libjaus.*;
import openjaus.libjaus.message.*;
import openjaus.libjaus.message.experimental.*;
import openjaus.libjaus.message.inform.*;

import java.util.*;
import java.net.*;
import java.text.*;

import org.apache.log4j.Logger;

public class SubsystemTable
{
	/** Logger that knows our class name */
	static private final Logger log = Logger.getLogger(SubsystemTable.class);

	Queue outputQueue;
	Vector table; // Vector of JausSubsystems
	Vector nodeConfChangedNotifyList;
	Vector subsystemConfChangedNotifyList;
	Vector nodeReportConfEventList;
	Vector subsystemReportConfEventList;
	JausSubsystem thisSubsystem;
	JausNode thisNode;
	JausComponent thisComponent;
	int lookupComponentId = 0;
	int lookupCommandCode = 0;
	int lookupServiceCommandType = 0;
	int lookupSubsystemIndex = 0;
	int lookupNodeIndex = 0;
	int lookupComponentIndex = 0;
	int refreshCountSec = 0;
	public static final int REFRESH_TIMEOUT_SEC = 60;
	
	boolean instanceIdAvailable[][];
	
    public SubsystemTable(Queue outputQueue)
    {
    	this.outputQueue = outputQueue;
    	table = new Vector();
    	nodeConfChangedNotifyList = new Vector();
    	subsystemConfChangedNotifyList = new Vector();
    	nodeReportConfEventList = new Vector();
    	subsystemReportConfEventList = new Vector();

    	instanceIdAvailable = new boolean[255][255];
		for(int componentId=1; componentId<255; componentId++)
		{
			for(int instanceId=1; instanceId<255; instanceId++)
			{
				instanceIdAvailable[componentId][instanceId] = true;
			}
		}
		
    	thisComponent = NodeManager.getComponent();
        thisNode = thisComponent.getNode();
        thisSubsystem = thisNode.getSubsystem();
       
		instanceIdAvailable[thisComponent.getAddress().getComponent()][thisComponent.getAddress().getInstance()] = false;
		table.add(thisSubsystem);
		log.info("SubsystemTable: Added Component: " + thisSubsystem + " : " + thisNode + " : " + thisComponent);
    }
    
    public void processHeartbeat(JausMessage message, InetAddress ipAddress, int port)
    {
		//System.out.println("SubsystemTable: HB From " + message.getSource() + " " + ipAddress + " " + port);
		JausSubsystem sourceSubsystem = new JausSubsystem(message.getSource().getSubsystem());

		JausNode sourceNode = new JausNode(message.getSource().getNode(), ipAddress, port);
		sourceNode.setSubsystem(sourceSubsystem); // Set parent subsystem
		
		JausComponent sourceComponent = new JausComponent(message.getSource(), 0, port);
		sourceComponent.setNode(sourceNode); // Set parent node
		
		sourceNode.addComponent(sourceComponent);
		sourceSubsystem.addNode(sourceNode);
		
		if(table.contains(sourceSubsystem))
		{
			JausSubsystem subsystem = (JausSubsystem)table.get(table.indexOf(sourceSubsystem));
			subsystem.updateTimestamp();

			if(subsystem.containsNode(sourceNode))
			{
				JausNode node = (JausNode)subsystem.getNodeByIndex(subsystem.indexOfNode(sourceNode));
				node.updateTimestamp();

				if(node.containsComponent(sourceComponent))
				{
					JausComponent component = (JausComponent)node.getComponentByIndex(node.indexOfComponent(sourceComponent));
					component.updateTimestamp();    					    
				}
				else
				{
					// TODO: Only add remote components (might not need this whole block)
				    sourceComponent.setNode(node);
					node.addComponent(sourceComponent);
					log.info("SubsystemTable: Added Component: " + subsystem + " : " + node + " : " + sourceComponent);    					    
					if(node.equals(thisNode))
					{
						sendNodeChangedEvents();
						sendNodeChangedNotifications();
						sendSubsystemChangedEvents();
						sendSubsystemChangedNotifications();
					}
				}
			}
			else
			{
			    sourceNode.setSubsystem(subsystem);
				subsystem.addNode(sourceNode);
				log.info("SubsystemTable: Added Component: " + subsystem + " : " + sourceNode + " : " + sourceComponent);
			}
		}
		else
		{
			table.add(sourceSubsystem);
			log.info("SubsystemTable: Added Component: " + sourceSubsystem + " : " + sourceNode + " : " + sourceComponent);
		}
    }
    
    public void processReportIdentification(ReportIdentificationMessage message, InetAddress ipAddress, int port)
    {
		JausSubsystem sourceSubsystem = new JausSubsystem(message.getSource().getSubsystem());
		JausNode sourceNode = new JausNode(message.getSource().getNode(), ipAddress);
		sourceNode.setSubsystem(sourceSubsystem); // Set parent subsystem
		JausComponent sourceComponent = new JausComponent(message.getSource(), 0, port);
		sourceComponent.setNode(sourceNode); // Set parent node
		sourceNode.addComponent(sourceComponent);
		sourceSubsystem.addNode(sourceNode);

		if(table.contains(sourceSubsystem))
		{
			JausSubsystem subsystem = (JausSubsystem)table.get(table.indexOf(sourceSubsystem));

			if(subsystem.containsNode(sourceNode))
			{
				JausNode node = (JausNode)subsystem.getNodeByIndex(subsystem.indexOfNode(sourceNode));
				
				if(node.containsComponent(sourceComponent))
				{
					JausComponent component = (JausComponent)node.getComponentByIndex(node.indexOfComponent(sourceComponent));
					component.setAuthority(message.getAuthority().getValue());
					switch(message.getQueryType().getValue())
					{
						case ReportIdentificationMessage.SUBSYSTEM_IDENTIFICATION:
							subsystem.setIdentification(message.getIdentification());					
							break;
							
						case ReportIdentificationMessage.NODE_IDENTIFICATION:
							node.setIdentification(message.getIdentification());					
							break;
						
						case ReportIdentificationMessage.COMPONENT_IDENTIFICATION:
							component.setIdentification(message.getIdentification());					
							break;
						
						default:
							log.warn("Unknown message type:" + message.getQueryType().getValue() );
							return;
					}
				}
				else
				{
					log.warn("Component not in node:" + sourceComponent);
					
				}
			}
			else
			{
				log.warn("Node not in subsystem:" + sourceNode);
				
			}
		}
		else
		{
			log.warn("Subsystem does not exist: " + sourceSubsystem);

		}
    }

    public void processReportConfiguration(ReportConfigurationMessage message, InetAddress ipAddress, int port)
    {
    	JausSubsystem reportSubsystem = message.getSubsystemConfiguration();
		boolean subsystemChanged = false;
    	
    	Enumeration subsystemEnum = reportSubsystem.nodeEnumeration();
		while(subsystemEnum.hasMoreElements())
		{
			JausNode reportNode = (JausNode)subsystemEnum.nextElement();
			reportNode.setIpAddress(ipAddress);
			reportNode.setPort(port);
		
			Enumeration nodeEnum = reportNode.componentEnumeration();
			while(nodeEnum.hasMoreElements())
			{
				JausComponent reportComponent = (JausComponent)nodeEnum.nextElement();
				reportComponent.setPort(port);
			}
		}
		
    	if(table.contains(reportSubsystem))
		{
			JausSubsystem subsystem = (JausSubsystem)table.get(table.indexOf(reportSubsystem));
    		reportSubsystem.setIdentification(subsystem.getIdentification());

    		if(reportSubsystem.equals(thisSubsystem))
			{
				subsystemChanged = true;

	    		subsystemEnum = reportSubsystem.nodeEnumeration();
				while(subsystemEnum.hasMoreElements())
				{
					JausNode reportNode = (JausNode)subsystemEnum.nextElement();
					if(subsystem.containsNode(reportNode))
					{
						JausNode node = (JausNode)subsystem.getNodeByIndex(subsystem.indexOfNode(reportNode));
						reportNode.setIdentification(node.getIdentification()); // Copy identification
						reportNode.setIpAddress(node.getIpAddress()); // Copy identification
						reportNode.setPort(node.getPort()); // Copy identification
						
						Enumeration nodeEnum = reportNode.componentEnumeration();
						while(nodeEnum.hasMoreElements())
						{
							JausComponent reportComponent = (JausComponent)nodeEnum.nextElement();
							if(node.containsComponent(reportComponent))
							{
								JausComponent component = (JausComponent)node.getComponentByIndex(node.indexOfComponent(reportComponent));
								reportComponent.setIdentification(component.getIdentification());
								reportComponent.setPort(component.getPort());
								reportComponent.setServices(component.getServices());
							}
						}
						subsystem.removeNode(node);
						subsystem.addNode(reportNode);
					}
					else
					{
						subsystem.addNode(reportNode);
					}
				}
			}
			else
			{
	    		subsystemEnum = reportSubsystem.nodeEnumeration();
				while(subsystemEnum.hasMoreElements())
				{
					JausNode reportNode = (JausNode)subsystemEnum.nextElement();
					if(subsystem.containsNode(reportNode))
					{
						JausNode node = (JausNode)subsystem.getNodeByIndex(subsystem.indexOfNode(reportNode));
						reportNode.setIdentification(node.getIdentification()); // Copy identification
						reportNode.setIpAddress(node.getIpAddress()); // Copy identification
						reportNode.setPort(node.getPort()); // Copy identification
						
						Enumeration nodeEnum = reportNode.componentEnumeration();
						while(nodeEnum.hasMoreElements())
						{
							JausComponent reportComponent = (JausComponent)nodeEnum.nextElement();
							if(node.containsComponent(reportComponent))
							{
								JausComponent component = (JausComponent)node.getComponentByIndex(node.indexOfComponent(reportComponent));
								reportComponent.setIdentification(component.getIdentification());
								reportComponent.setPort(component.getPort());
								reportComponent.setServices(component.getServices());
							}
						}
					}
				}
				table.remove(subsystem);
	        	table.add(reportSubsystem);    										
			}
		}
    	else
    	{
        	table.add(reportSubsystem);    		
    	}

    	if(subsystemChanged)
    	{
			sendSubsystemChangedEvents();
			sendSubsystemChangedNotifications();
    	}
    }

    public void processReportServices(ReportServicesMessage message, InetAddress ipAddress, int port)
    {
		JausSubsystem sourceSubsystem = new JausSubsystem(message.getSource().getSubsystem());
		JausNode sourceNode = new JausNode(message.getSource().getNode(), ipAddress);
		sourceNode.setSubsystem(sourceSubsystem); // Set parent subsystem
		JausComponent sourceComponent = new JausComponent(message.getSource(), 0, port);
		sourceComponent.setNode(sourceNode); // Set parent node
		sourceNode.addComponent(sourceComponent);
		sourceSubsystem.addNode(sourceNode);

		if(table.contains(sourceSubsystem))
		{
			JausSubsystem subsystem = (JausSubsystem)table.get(table.indexOf(sourceSubsystem));

			if(subsystem.containsNode(sourceNode))
			{
				JausNode node = (JausNode)subsystem.getNodeByIndex(subsystem.indexOfNode(sourceNode));
				
				if(node.containsComponent(sourceComponent))
				{
					JausComponent component = (JausComponent)node.getComponentByIndex(node.indexOfComponent(sourceComponent));
					component.setServices(message.getServices());		
				}
				else
				{
					log.warn("Component not in node: " + sourceComponent);
				
				}
			}
			else
			{
				log.warn("Node not in subsystem:" + sourceNode);
			
			}
		}
		else
		{
			log.warn("Subsystem not in system: " + sourceSubsystem);

		}
    }
    
    public void processConfChangeSetup(ConfigurationChangedEventSetupMessage message, InetAddress ipAddress, int port)
    {
    	if(message.getNotificationType().getValue()== 3) // Terminate notification
    	{
    		if(nodeConfChangedNotifyList.contains(message.getSource()))
    			nodeConfChangedNotifyList.remove(message.getSource());

    		if(subsystemConfChangedNotifyList.contains(message.getSource()))
    			subsystemConfChangedNotifyList.remove(message.getSource());
    	}
    	else
    	{
    		if(	message.getSource().getComponent() == JausComponent.NODE_MANAGER || 
    			message.getSource().getComponent() == JausComponent.COMMUNICATOR )
    		{
    			// Higher or equal level components will be interesed when the lower level changes
        		// so add them to the node changed list
    			if(!nodeConfChangedNotifyList.contains(message.getSource())) // If the source is not already registered
        			nodeConfChangedNotifyList.add(message.getSource()); // Add the source to the notify list		
    		}
    		else
    		{
    			// Lower level components will be interesed when the lower level changes or this subsystem changes
        		// so add them to the subsystem changed list
    			if(!subsystemConfChangedNotifyList.contains(message.getSource())) // If the source is not already registered
    				subsystemConfChangedNotifyList.add(message.getSource()); // Add the source to the notify list		
    		}
    	}
    }

    public boolean processCreateEvent(CreateEventMessage message, InetAddress ipAddress, int port)
    {
    	if(message.getMessageCode() != JausMessage.QUERY_CONFIGURATION)
    	{
    		return false;
    	}

    	QueryConfigurationMessage queryConfMsg = new QueryConfigurationMessage(message.getQueryMessage()); 	
		switch(queryConfMsg.getQueryField().getValue())
		{
			case QueryConfigurationMessage.SUBSYSTEM_CONFIGURATION:
				if(!subsystemReportConfEventList.contains(message.getSource())) // If the source is not already registered
				{
					subsystemReportConfEventList.add(message.getSource()); // Add the source to the notify list		
				}
				break;
				
			case QueryConfigurationMessage.NODE_CONFIGURATION:
				if(!nodeReportConfEventList.contains(message.getSource())) // If the source is not already registered
				{
					nodeReportConfEventList.add(message.getSource()); // Add the source to the notify list		
				}
				break;

			default: 
				log.warn("Unknown query field:" + queryConfMsg.getQueryField().getValue());
	
				return false;
		}
		return true;
    }

    public void processComponentAuthority(ReportComponentAuthorityMessage message, InetAddress ipAddress, int port)
    {
    	JausSubsystem sourceSubsystem = new JausSubsystem(message.getSource().getSubsystem());
		JausNode sourceNode = new JausNode(message.getSource().getNode(), ipAddress);
		JausComponent sourceComponent = new JausComponent(message.getSource(), 0, port);
		
		if(table.contains(sourceSubsystem))
		{
			JausSubsystem subsystem = (JausSubsystem)table.get(table.indexOf(sourceSubsystem));

			if(subsystem.containsNode(sourceNode))
			{
				JausNode node = (JausNode)subsystem.getNodeByIndex(subsystem.indexOfNode(sourceNode));
				
				if(node.containsComponent(sourceComponent))
				{
					JausComponent component = (JausComponent)node.getComponentByIndex(node.indexOfComponent(sourceComponent));
					component.setAuthority(message.getAuthorityCode().getValue());    					    
				}
				else
				{
					log.warn("Unknown source component: " + sourceComponent);

				}
			}
			else
			{
				log.warn("Unknown source Node: " + sourceNode);

			}
		}
		else
		{
			log.warn("Unknown subsystem:" + sourceSubsystem);
	
		}
    }

    public void processComponentStatus(ReportComponentStatusMessage message, InetAddress ipAddress, int port)
    {
    	JausSubsystem sourceSubsystem = new JausSubsystem(message.getSource().getSubsystem());
		JausNode sourceNode = new JausNode(message.getSource().getNode(), ipAddress);
		JausComponent sourceComponent = new JausComponent(message.getSource(), 0, port);
		
		if(table.contains(sourceSubsystem))
		{
			JausSubsystem subsystem = (JausSubsystem)table.get(table.indexOf(sourceSubsystem));

			if(subsystem.containsNode(sourceNode))
			{
				JausNode node = (JausNode)subsystem.getNodeByIndex(subsystem.indexOfNode(sourceNode));
				
				if(node.containsComponent(sourceComponent))
				{
					JausComponent component = (JausComponent)node.getComponentByIndex(node.indexOfComponent(sourceComponent));
					component.getState().setValue(message.getPrimaryStatusCode().getValue());    					    
				}
				else
				{
					log.warn("Unknown component:" + sourceComponent);

				}
			}
			else
			{
				log.warn("Unknown Node:" + sourceNode);
				
			}
		}
		else
		{
			log.warn("Unknown subsystem:" + sourceSubsystem);

		}
    }
	
    private void sendNodeChangedNotifications()
    {
    	ConfigurationChangedEventNotificationMessage confChangedEventMsg = new ConfigurationChangedEventNotificationMessage();
		confChangedEventMsg.setSource(thisComponent.getAddress());

		Enumeration notifications = nodeConfChangedNotifyList.elements();
    	while(notifications.hasMoreElements())
    	{
    		JausAddress destination = (JausAddress)notifications.nextElement();
    		confChangedEventMsg.setDestination(destination);
    		
    		byte[] buffer = new byte[confChangedEventMsg.size()];
    		confChangedEventMsg.toJausBuffer(buffer);
    		DatagramPacket packet = new DatagramPacket(buffer, buffer.length, thisNode.getIpAddress(), thisComponent.getPort());
    	    outputQueue.push(packet);
    	}
    	nodeConfChangedNotifyList.clear();
    }

    private void sendNodeChangedEvents()
    {
    	ReportConfigurationMessage reportConfMsg = new ReportConfigurationMessage();
		reportConfMsg.setSource(thisComponent.getAddress());
		
		// Create a new JausSubsystem object and add just this node to it
		// This will allow us to send just the components on this node
		JausSubsystem subsystem = new JausSubsystem(thisSubsystem.getId());
		subsystem.addNode(thisNode);
		reportConfMsg.setSubsystemConfiguration(subsystem);

		Enumeration notifications = nodeReportConfEventList.elements();
    	while(notifications.hasMoreElements())
    	{
    		JausAddress destination = (JausAddress)notifications.nextElement();
    		reportConfMsg.setDestination(destination);
    		
    		byte[] buffer = new byte[reportConfMsg.size()];
    		reportConfMsg.toJausBuffer(buffer);
    		DatagramPacket packet = new DatagramPacket(buffer, buffer.length, thisNode.getIpAddress(), thisComponent.getPort());
    	    outputQueue.push(packet);
    	}
    }
    
    private void sendSubsystemChangedNotifications()
    {
    	ConfigurationChangedEventNotificationMessage confChangedEventMsg = new ConfigurationChangedEventNotificationMessage();
		confChangedEventMsg.setSource(thisComponent.getAddress());

		Enumeration notifications = subsystemConfChangedNotifyList.elements();
    	while(notifications.hasMoreElements())
    	{
    		JausAddress destination = (JausAddress)notifications.nextElement();
    		confChangedEventMsg.setDestination(destination);
    		
    		byte[] buffer = new byte[confChangedEventMsg.size()];
    		confChangedEventMsg.toJausBuffer(buffer);
    		DatagramPacket packet = new DatagramPacket(buffer, buffer.length, thisNode.getIpAddress(), thisComponent.getPort());
    	    outputQueue.push(packet);
    	}
    	subsystemConfChangedNotifyList.clear();
    	
    }

    private void sendSubsystemChangedEvents()
    {
    	ReportConfigurationMessage reportConfMsg = new ReportConfigurationMessage();
		reportConfMsg.setSource(thisComponent.getAddress());
		
		reportConfMsg.setSubsystemConfiguration(thisSubsystem);

		Enumeration notifications = subsystemReportConfEventList.elements();
    	while(notifications.hasMoreElements())
    	{
    		JausAddress destination = (JausAddress)notifications.nextElement();
    		reportConfMsg.setDestination(destination);
    		
    		byte[] buffer = new byte[reportConfMsg.size()];
    		reportConfMsg.toJausBuffer(buffer);
    		DatagramPacket packet = new DatagramPacket(buffer, buffer.length, thisNode.getIpAddress(), thisComponent.getPort());
    	    outputQueue.push(packet);
    	}
    }
    
	public boolean isComponentInTable(JausComponent testComponent)
    {
		JausSubsystem sourceSubsystem = new JausSubsystem(testComponent.getAddress().getSubsystem());
		JausNode sourceNode = new JausNode(testComponent.getAddress().getNode(), null);
		sourceNode.setSubsystem(sourceSubsystem); // Set parent subsystem
		JausComponent sourceComponent = new JausComponent(testComponent.getAddress(), 0, 0);
		sourceComponent.setNode(sourceNode); // Set parent node
		sourceNode.addComponent(sourceComponent);
		sourceSubsystem.addNode(sourceNode);

		if(table.contains(sourceSubsystem))
		{
			JausSubsystem subsystem = (JausSubsystem)table.get(table.indexOf(sourceSubsystem));

			if(subsystem.containsNode(sourceNode))
			{
				JausNode node = (JausNode)subsystem.getNodeByIndex(subsystem.indexOfNode(sourceNode));
				
				if(node.containsComponent(sourceComponent))
				{
					return true;
				}
			}
		}
    	return false;
    }

    public boolean isComponentIdentificationInTable(JausComponent testComponent)
    {
		JausSubsystem sourceSubsystem = new JausSubsystem(testComponent.getAddress().getSubsystem());
		JausNode sourceNode = new JausNode(testComponent.getAddress().getNode(), null);
		sourceNode.setSubsystem(sourceSubsystem); // Set parent subsystem
		JausComponent sourceComponent = new JausComponent(testComponent.getAddress(), 0, 0);
		sourceComponent.setNode(sourceNode); // Set parent node
		sourceNode.addComponent(sourceComponent);
		sourceSubsystem.addNode(sourceNode);

		if(table.contains(sourceSubsystem))
		{
			JausSubsystem subsystem = (JausSubsystem)table.get(table.indexOf(sourceSubsystem));

			if(subsystem.containsNode(sourceNode))
			{
				JausNode node = (JausNode)subsystem.getNodeByIndex(subsystem.indexOfNode(sourceNode));
				
				if(node.containsComponent(sourceComponent))
				{
					JausComponent component = (JausComponent)node.getComponentByIndex(node.indexOfComponent(sourceComponent));
					if(component.getIdentification() != null)
						return true;
				}
			}
		}
    	return false;
    }

    public boolean hasSubsystemIdentification(JausSubsystem testSubsystem)
    {
		if(table.contains(testSubsystem))
		{
			JausSubsystem subsystem = (JausSubsystem)table.get(table.indexOf(testSubsystem));

			if(subsystem.getIdentification() != null)
			{
				return true;
			}
		}
    	return false;
    }
    
    public boolean hasNodeIdentification(JausNode testNode)
    {
    	JausSubsystem testSubsystem = testNode.getSubsystem();

    	if(table.contains(testSubsystem))
		{
			JausSubsystem subsystem = (JausSubsystem)table.get(table.indexOf(testSubsystem));

			if(subsystem.containsNode(testNode))
			{
				JausNode node = (JausNode)subsystem.getNodeByIndex(subsystem.indexOfNode(testNode));
				if(node.getIdentification() != null)
				{
					return true;
				}
			}
		}
    	return false;
    }

    public boolean hasComponentIdentification(JausComponent testComponent)
    {
    	JausNode testNode = testComponent.getNode();
    	JausSubsystem testSubsystem = testNode.getSubsystem();
    	
		if(table.contains(testSubsystem))
		{
			JausSubsystem subsystem = (JausSubsystem)table.get(table.indexOf(testSubsystem));

			if(subsystem.containsNode(testNode))
			{
				JausNode node = (JausNode)subsystem.getNodeByIndex(subsystem.indexOfNode(testNode));

				if(node.containsComponent(testComponent))
				{
					JausComponent component = (JausComponent)node.getComponentByIndex(node.indexOfComponent(testComponent));
					if(component.getIdentification() != null)
					{
						return true;
					}
				}
			}
		}
		
    	return false;
    }

    public boolean lookUpAddressInNode(JausNode node, JausAddress lookupAddress)
    {
		for(int componentIndex = 0; componentIndex < node.componentCount(); componentIndex++)
		{
			JausComponent component = (JausComponent)node.getComponentByIndex(componentIndex); 

			if(lookupAddress.getComponent() == 0)
			{
				if(lookupAddress.getInstance() == 0)
				{
					lookupAddress.setId(component.getAddress().getId());
					return true;
				}
				else
				{
					if(lookupAddress.getInstance() == component.getAddress().getInstance())
					{
						lookupAddress.setId(component.getAddress().getId());
						return true;						
					}
				}
			}
			else
			{
				if(lookupAddress.getComponent() == component.getAddress().getComponent())
				{
					if(lookupAddress.getInstance() == 0)
					{
						lookupAddress.setId(component.getAddress().getId());
						return true;
					}
					else
					{
						if(lookupAddress.getInstance() == component.getAddress().getInstance())
						{
							lookupAddress.setId(component.getAddress().getId());
							return true;						
						}
					}					
				}				
			}
		}
		return false;
    }

    public boolean lookUpAddressInSubsystem(JausSubsystem subsystem, JausAddress lookupAddress)
    {
		if(lookupAddress.getNode() == 0)
		{
			for(int nodeIndex = 0; nodeIndex < subsystem.nodeCount(); nodeIndex++)
			{
				if(lookUpAddressInNode((JausNode)subsystem.getNodeByIndex(nodeIndex), lookupAddress))
				{
					return true;
				}
			}
		}
		else
		{
			JausNode testNode = new JausNode(lookupAddress.getNode());
			if(subsystem.containsNode(testNode))
			{
				if(lookUpAddressInNode((JausNode)subsystem.getNodeByIndex(subsystem.indexOfNode(testNode)), lookupAddress))
				{
					return true;
				}
			}
		}
		return false;
    }
    
	public boolean lookUpAddressInSystem(JausAddress lookupAddress)
	{
		if(lookupAddress.getSubsystem() == 0)
		{
			for(int subsystemIndex = 0; subsystemIndex < table.size(); subsystemIndex++)
			{
				if(lookUpAddressInSubsystem((JausSubsystem)table.get(subsystemIndex), lookupAddress))
				{
					return true;
				}
			}
		}
		else
		{
			JausSubsystem testSubsystem = new JausSubsystem(lookupAddress.getSubsystem());
			if(table.contains(testSubsystem))
			{
				if(lookUpAddressInSubsystem((JausSubsystem)table.get(table.indexOf(testSubsystem)), lookupAddress))
				{
					return true;
				}
			}
		}
		return false;
	}

    public boolean lookUpServiceAddressInNode(JausNode node, JausAddress lookupAddress, int commandCode, int serviceCommandType)
    {
		for(int componentIndex = 0; componentIndex < node.componentCount(); componentIndex++)
		{
			JausComponent component = (JausComponent)node.getComponentByIndex(componentIndex); 

			if(lookupAddress.getComponent() == 0)
			{
				if(lookupAddress.getInstance() == 0)
				{
					if(component.serviceCommandExists(commandCode, serviceCommandType))
					{
						lookupAddress.setId(component.getAddress().getId());
						return true;
					}
				}
				else
				{
					if(lookupAddress.getInstance() == component.getAddress().getInstance())
					{
						if(component.serviceCommandExists(commandCode, serviceCommandType))
						{
							lookupAddress.setId(component.getAddress().getId());
							return true;
						}
					}
				}
			}
			else
			{
				if(lookupAddress.getComponent() == component.getAddress().getComponent())
				{
					if(lookupAddress.getInstance() == 0)
					{
						if(component.serviceCommandExists(commandCode, serviceCommandType))
						{
							lookupAddress.setId(component.getAddress().getId());
							return true;
						}
					}
					else
					{
						if(lookupAddress.getInstance() == component.getAddress().getInstance())
						{
							if(component.serviceCommandExists(commandCode, serviceCommandType))
							{
								lookupAddress.setId(component.getAddress().getId());
								return true;						
							}
						}
					}					
				}				
			}
		}
		return false;
    }

    public boolean lookUpServiceAddressInSubsystem(JausSubsystem subsystem, JausAddress lookupAddress, int commandCode, int serviceCommandType)
    {
		if(lookupAddress.getNode() == 0)
		{
			for(int nodeIndex = 0; nodeIndex < subsystem.nodeCount(); nodeIndex++)
			{
				if(lookUpServiceAddressInNode((JausNode)subsystem.getNodeByIndex(nodeIndex), lookupAddress, commandCode, serviceCommandType))
				{
					return true;
				}
			}
		}
		else
		{
			JausNode testNode = new JausNode(lookupAddress.getNode());
			if(subsystem.containsNode(testNode))
			{
				if(lookUpServiceAddressInNode((JausNode)subsystem.getNodeByIndex(subsystem.indexOfNode(testNode)), lookupAddress, commandCode, serviceCommandType))
				{
					return true;
				}
			}
		}
		return false;
    }
    
	public boolean lookUpServiceAddressInSystem(JausAddress lookupAddress, int commandCode, int serviceCommandType)
	{
		if(lookupAddress.getSubsystem() == 0)
		{
			for(int subsystemIndex = 0; subsystemIndex < table.size(); subsystemIndex++)
			{
				if(lookUpServiceAddressInSubsystem((JausSubsystem)table.get(subsystemIndex), lookupAddress, commandCode, serviceCommandType))
				{
					return true;
				}
			}
		}
		else
		{
			JausSubsystem testSubsystem = new JausSubsystem(lookupAddress.getSubsystem());
			if(table.contains(testSubsystem))
			{
				if(lookUpServiceAddressInSubsystem((JausSubsystem)table.get(table.indexOf(testSubsystem)), lookupAddress, commandCode, serviceCommandType))
				{
					return true;
				}
			}
		}
		return false;
	}
	
    public InetAddress lookUpIpAddress(int subsystemID, int nodeID)
	{
		if (subsystemID == thisSubsystem.getId())
		{
			return lookUpLocalIpAddress(nodeID);
		}
		else
		{
			JausSubsystem ss = getSubsystem(subsystemID);
			if (ss != null)
			{
				JausNode node = ss.getNode(nodeID);
				if (node != null)
				{
					return node.getIpAddress();
				}
				else
				{
					log.warn("lookUpIpAddress: no such Node:" + nodeID);
					
				}
			} 
			else
			{
				log.warn("lookUpIpAddress: no such Subsystem:" + subsystemID);
		
			}
		}
		return null;
	}

	public Integer lookUpPort(int subsystemID, int nodeID)
	{
		JausSubsystem ss = getSubsystem(subsystemID);
		if(ss != null)
		{
			JausNode node = ss.getNode(nodeID);
			if(node != null)
			{
				return new Integer(node.getPort());
			}
			else
			{
				log.warn("lookUpPort: no such Node:" + nodeID);
				
			}
		} 
		else
		{
			log.warn("lookUpPort: no such Subsystem:" + subsystemID);
			
		}
		return null;
	}
	
	public JausAddress getComponentAddress(int componentId)
	{
		if(componentId == 0)
		{
			if(lookupComponentId == 0)
			{
				log.warn("getComponentAddress Called Uninitialized");	
				return null;
			}
		}
		else
		{
			lookupComponentId = componentId;
			lookupSubsystemIndex = 0;
			lookupNodeIndex = 0;
			lookupComponentIndex = 0;			
		}
		
		while(lookupSubsystemIndex < table.size() )
		{
			JausSubsystem subsystem = (JausSubsystem) table.get(lookupSubsystemIndex);
				
			while(lookupNodeIndex < subsystem.nodeCount())
			{
				JausNode node = (JausNode) subsystem.getNodeByIndex(lookupNodeIndex);
				
				while(lookupComponentIndex < node.componentCount())
				{
					JausComponent component = (JausComponent) node.getComponentByIndex(lookupComponentIndex);
					lookupComponentIndex++;

					if(component.getAddress().getComponent() == lookupComponentId)
					{
						return component.getAddress();
					}
				}
				lookupComponentIndex = 0;
				lookupNodeIndex++;
			}			
			lookupNodeIndex = 0;
			lookupSubsystemIndex++;
		}
		
		lookupComponentId = 0;

		return null;
	}

	public JausAddress lookupServiceAddressList(JausAddress lookupAddress, int commandCode, int serviceCommandType)
	{
		if(commandCode == 0)
		{
			if(lookupCommandCode == 0)
			{
				log.warn("SubsystemTable: Error: lookupServiceAddressList Called Uninitialized");	
				return null;
			}
		}
		else
		{
			lookupCommandCode = commandCode;
			lookupServiceCommandType = serviceCommandType;
			lookupSubsystemIndex = 0;
			lookupNodeIndex = 0;
			lookupComponentIndex = 0;			
		}
		
		while(lookupSubsystemIndex < table.size() )
		{
			JausSubsystem subsystem = (JausSubsystem) table.get(lookupSubsystemIndex);
			
			if(lookupAddress.getSubsystem() != 0 && lookupAddress.getSubsystem() != subsystem.getId())
			{
				lookupNodeIndex = 0;
				lookupSubsystemIndex++;
				continue;
			}
			
			while(lookupNodeIndex < subsystem.nodeCount())
			{
				JausNode node = (JausNode) subsystem.getNodeByIndex(lookupNodeIndex);

				if(lookupAddress.getNode() != 0 && lookupAddress.getNode() != node.getId())
				{
					lookupComponentIndex = 0;
					lookupNodeIndex++;
					continue;
				}
				
				while(lookupComponentIndex < node.componentCount())
				{
					JausComponent component = (JausComponent) node.getComponentByIndex(lookupComponentIndex);
					if(lookupAddress.getComponent() != 0 && lookupAddress.getComponent() != component.getAddress().getComponent())
					{
						lookupComponentIndex++;					
						continue;
					}
					if(lookupAddress.getInstance() != 0 && lookupAddress.getInstance() != component.getAddress().getInstance())
					{
						lookupComponentIndex++;					
						continue;
					}

					if(component.serviceCommandExists(lookupCommandCode, lookupServiceCommandType))
					{
						lookupComponentIndex++;					
						return component.getAddress();
					}
					else
					{
						lookupComponentIndex++;								
					}
				}
				lookupComponentIndex = 0;
				lookupNodeIndex++;
			}			
			lookupNodeIndex = 0;
			lookupSubsystemIndex++;
		}
		
		lookupCommandCode = 0;
		lookupServiceCommandType = 0;

		return null;
	}
	
	
	public JausSubsystem getSubsystem(int id)
	{
		JausSubsystem subsystem = null;
		int len = table.size();
		for(int i=0; i<len; i++)
		{
			subsystem = (JausSubsystem)table.get(i);
			if (subsystem.getId() == id)
			{
				return subsystem;
			}
		}
		return null;
	}
	
    public InetAddress lookUpLocalIpAddress(int nodeId)
    {
		JausNode node = thisSubsystem.getNode(nodeId);
		if (node != null)
			return node.getIpAddress();
		else
			log.warn("lookUpLocalIpAddress: no such node:" + nodeId);
		
		return null;
    }

	public Enumeration getSubsystems()
	{
		return table.elements();
	}
	
    public int checkInLocalComponent(int componentId, int port)
    {
		// Install the component in table only if component with same port # is not allready in table
   		Enumeration nodeElements = thisNode.componentEnumeration();
   		while(nodeElements.hasMoreElements())
   		{
   			JausComponent component = (JausComponent)nodeElements.nextElement();
   			if(component.getPort() == port)
   			{
   		    	return JausAddress.INVALID_INSTANCE; // TODO: change to ERROR_PORT_ALLREADY_IN_TABLE
   			}
   		}
    	
   		// Find an available instance id and then add component
    	for(int i = 0; i < 255; i++)
    	{
    		if(instanceIdAvailable[componentId][i])
    		{
    			instanceIdAvailable[componentId][i] = false;
    			JausAddress componentAddress = new JausAddress(thisComponent.getAddress());
    			componentAddress.setInstance(i);
    			componentAddress.setComponent(componentId);
    			JausComponent sourceComponent = new JausComponent(componentAddress, 0, port);
    			sourceComponent.setNode(thisNode); // Set parent node
				thisNode.addComponent(sourceComponent);
				log.info("Added Component: " + thisSubsystem + " : " + thisNode + " : " + sourceComponent);

				sendNodeChangedEvents();
				sendNodeChangedNotifications();
				sendSubsystemChangedEvents();
				sendSubsystemChangedNotifications();

				return i;
    		}
    	}
    	
    	return JausAddress.INVALID_INSTANCE; // TODO: change to ERROR_NO_FREE_INSTANCE
    }
    
    public boolean checkOutLocalComponent(JausAddress address)
    {
		Enumeration nodeElements = thisNode.componentEnumeration();
		while(nodeElements.hasMoreElements())
		{
			JausComponent component = (JausComponent)nodeElements.nextElement();
			if(component.getAddress().equals(address))
			{
				System.out.println("SubsystemTable: Removing Component: " + component);
				thisNode.removeComponent(component);
				instanceIdAvailable[address.getComponent()][address.getInstance()] = true;
	    		if(subsystemConfChangedNotifyList.contains(component.getAddress())) // If the component is already registered
	    		{
	    			subsystemConfChangedNotifyList.remove(component.getAddress()); // Remove the component from the notify list		
	    		}
				sendNodeChangedEvents();
				sendNodeChangedNotifications();
				sendSubsystemChangedEvents();
				sendSubsystemChangedNotifications();
				return true;
			}
		}
    	
    	return false;
    }

    public String toString()
    {
    	String result  = new String("SubsystemTable: Subsystem Table Display: ");
    	
    	Date date = new Date();
    	SimpleDateFormat formatter = new SimpleDateFormat("MM/dd/yyyy - hh:mm:ss", new Locale("en","US"));
    	result += formatter.format(date) + "\n";
    	
    	Enumeration tableElements = table.elements();
    	while(tableElements.hasMoreElements())
    	{
    		JausSubsystem subsystem = (JausSubsystem)tableElements.nextElement();
    		result += "SubsystemTable:\t" + subsystem + "\n";
    		
    		Enumeration subsystemElements = subsystem.nodeEnumeration();
    		while(subsystemElements.hasMoreElements())
    		{
    			JausNode node = (JausNode)subsystemElements.nextElement();
    			result += "SubsystemTable:\t\t" + node + "\n";
    			
    			Enumeration nodeElements = node.componentEnumeration();
    			while(nodeElements.hasMoreElements())
    			{
    				JausComponent component = (JausComponent)nodeElements.nextElement();
    				result += "SubsystemTable:\t\t\t" + component + "\n";
    				
    				Enumeration componentServices = component.getServices().elements();
        			while(componentServices.hasMoreElements())
        			{
        				JausService service = (JausService)componentServices.nextElement();
        				result += "SubsystemTable:\t\t\t\t" + service + "\n";
        			}
    			}
    			
    		}
    	}
 
    	return result; 
    }

    public String toDetailedString()
    {
    	String result  = new String("SubsystemTable: Subsystem Table Display: ");
    	
    	Date date = new Date();
    	SimpleDateFormat formatter = new SimpleDateFormat("MM/dd/yyyy - hh:mm:ss", new Locale("en","US"));
    	result += formatter.format(date) + "\n";
    	
    	Enumeration tableElements = table.elements();
    	while(tableElements.hasMoreElements())
    	{
    		JausSubsystem subsystem = (JausSubsystem)tableElements.nextElement();
    		result += "SubsystemTable:\t" + subsystem + "\n";
    		
    		Enumeration subsystemElements = subsystem.nodeEnumeration();
    		while(subsystemElements.hasMoreElements())
    		{
    			JausNode node = (JausNode)subsystemElements.nextElement();
    			result += "SubsystemTable:\t\t" + node + "\n";
    			
    			Enumeration nodeElements = node.componentEnumeration();
    			while(nodeElements.hasMoreElements())
    			{
    				JausComponent component = (JausComponent)nodeElements.nextElement();
    				result += "SubsystemTable:\t\t\t" + component + "\n";
    				
    				Enumeration componentServices = component.getServices().elements();
        			while(componentServices.hasMoreElements())
        			{
        				JausService service = (JausService)componentServices.nextElement();
        				result += "SubsystemTable:\t\t\t\t" + service + "\n";

        				Enumeration inputCommands = service.getInputCommands().elements();
            			while(inputCommands.hasMoreElements())
            			{
            				JausCommand inputCommand = (JausCommand)inputCommands.nextElement();
            				result += "SubsystemTable:\t\t\t\t\tInput: " + inputCommand + "\n";
            			}
            			
        				result += "SubsystemTable:\n";

        				Enumeration outputCommands = service.getOutputCommands().elements();
            			while(outputCommands.hasMoreElements())
            			{
            				JausCommand outputCommand = (JausCommand)outputCommands.nextElement();
            				result += "SubsystemTable:\t\t\t\t\tOutput: " + outputCommand + "\n";
            			}
        			}
    			}
    			
    		}
    	}
 
    	return result; 
    }

    public String subsystemToString(int subsystemId)
    {
    	JausSubsystem subsystem =  getSubsystem(subsystemId);
    	if(subsystem == null)
    	{
    		return "SubsystemTable: Error! Subsystem " + subsystemId + " Not Found In Table\n";
    	}
    	
    	String result  = new String("SubsystemTable: Subsystem Table Display: ");
    	
    	Date date = new Date();
    	SimpleDateFormat formatter = new SimpleDateFormat("MM/dd/yyyy - hh:mm:ss", new Locale("en","US"));
    	result += formatter.format(date) + "\n";
    	
		result += "SubsystemTable:\t" + subsystem + "\n";
		
		Enumeration subsystemElements = subsystem.nodeEnumeration();
		while(subsystemElements.hasMoreElements())
		{
			JausNode node = (JausNode)subsystemElements.nextElement();
			result += "SubsystemTable:\t\t" + node + "\n";
			
			Enumeration nodeElements = node.componentEnumeration();
			while(nodeElements.hasMoreElements())
			{
				JausComponent component = (JausComponent)nodeElements.nextElement();
				result += "SubsystemTable:\t\t\t" + component + "\n";
				
				Enumeration componentServices = component.getServices().elements();
    			while(componentServices.hasMoreElements())
    			{
    				JausService service = (JausService)componentServices.nextElement();
    				result += "SubsystemTable:\t\t\t\t" + service + "\n";
    			}
			}
			
		}
 
    	return result; 
    }    
    
	public void refresh()
	{
		boolean nodeConfChanged = false;
		boolean subsystemConfChanged = false;
		
		//check table freshnesh info and time things out that need it
		Enumeration tableElements = table.elements();
		while(tableElements.hasMoreElements())
		{
			JausSubsystem subsystem = (JausSubsystem)tableElements.nextElement();
			if(subsystem.hasTimedOut())
			{
				log.info("SubsystemTable: Timeout Occured: Removing Subsystem: " + subsystem);
				table.remove(subsystem);
			}
			else if(subsystem.getId() == thisComponent.getAddress().getSubsystem()) // Only remove nodes from this subsystem
			{	
				Enumeration subsystemElements = subsystem.nodeEnumeration();
				while(subsystemElements.hasMoreElements())
				{
					JausNode node = (JausNode)subsystemElements.nextElement();
					if(node.hasTimedOut())
					{
						log.info("SubsystemTable: Timeout Occured: Removing Node: " + node);
						subsystem.removeNode(node);
						subsystemConfChanged = true;
					}
					else if(node.getId() == thisComponent.getAddress().getNode()) // Only remove components from this node
					{
						Enumeration nodeElements = node.componentEnumeration();
						while(nodeElements.hasMoreElements())
						{
							JausComponent component = (JausComponent)nodeElements.nextElement();
							if(component.hasTimedOut())
							{
								log.info("SubsystemTable: Timeout Occured: Removing Component: " + component);
								node.removeComponent(component);
								instanceIdAvailable[component.getAddress().getComponent()][component.getAddress().getInstance()] = true;
								nodeConfChanged = true;
								subsystemConfChanged = true;
							}
						}
					} // if(node equals this node)
				} // while(subsystem has more elements)
			} // if(subsystem has timed out)
		} // while(table has more elements)
		
		if(refreshCountSec++ >= REFRESH_TIMEOUT_SEC)
		{
			refreshCountSec = 0;
			//nodeConfChanged = true;
		}
		
		if(nodeConfChanged)
		{
			sendNodeChangedEvents();
			sendNodeChangedNotifications();
		}
		if(subsystemConfChanged)
		{
			sendSubsystemChangedEvents();
			sendSubsystemChangedNotifications();
		}
	} // refresh()
}
