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
// File Name: CoreMessageHandler.java
//
// Written By: Tom Galluzzo (galluzzo AT gmail DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: The CoreMessageHandler class processes all messages which are destined for this NodeManager Instance.

import java.net.*;
import java.util.*;
import jaus.*;
import jaus.type.*;
import jaus.message.*;
import jaus.message.command.*;
import jaus.message.experimental.*;
import jaus.message.inform.*;

public class CoreMessageHandler
{
    SubsystemTable subsystemTable;
	Queue outputQueue;
	Queue nodeSendQueue;
	JausSubsystem thisSubsystem;
	JausNode thisNode;
	JausComponent thisComponent;
	byte[] buffer;
	DatagramPacket packet;

	QueryIdentificationMessage queryIdMsg;
	ReportIdentificationMessage reportIdMsg;
	QueryConfigurationMessage queryConfMsg;
	ReportConfigurationMessage reportConfMsg;
	ConfigurationChangedEventSetupMessage confChangeSetupMsg;
	ReportComponentAuthorityMessage reportAuthorityMsg;
	ReportComponentStatusMessage componentStatusMsg;
	CreateEventMessage createEventMsg;
	QueryServicesMessage queryServicesMsg;
	ReportServicesMessage reportServicesMsg;
	
	public CoreMessageHandler(Queue outputQueue, Queue nodeSendQueue, SubsystemTable subsystemTable)
    {
	    this.subsystemTable = subsystemTable;
        this.outputQueue = outputQueue;
        this.nodeSendQueue = nodeSendQueue;
        
       	thisComponent = NodeManager.getComponent();
        thisNode = thisComponent.getNode();
        thisSubsystem = thisNode.getSubsystem();
    }
    
	public void process(JausMessage message, InetAddress sourceIp, int sourcePort)
	{
		switch(message.getCommandCode()) // Switch the processing algorithm according to the JAUS message type
		{
			case JausMessage.SET_COMPONENT_AUTHORITY: 
				SetComponentAuthorityMessage setAuthorityMsg = new SetComponentAuthorityMessage(message);
				thisComponent.setAuthority(setAuthorityMsg.getAuthorityCode().getValue());
				break;
				
			case JausMessage.SHUTDOWN:
				ShutdownMessage shutdownMsg = new ShutdownMessage(message);
				thisComponent.getState().setValue(JausState.SHUTDOWN);
				break;
				
			case JausMessage.STANDBY:
				StandbyMessage standbyMsg = new StandbyMessage(message);
				thisComponent.getState().setValue(JausState.STANDBY);
				break;
				
			case JausMessage.RESUME:
				if(thisComponent.getState().getValue() == JausState.STANDBY)
				{
					ResumeMessage resumeMsg = new ResumeMessage(message);
					thisComponent.getState().setValue(JausState.STANDBY);					
				}
				break;
				
			case JausMessage.RESET:
			    // TODO: switch to init, clear queues, and clear subsystem table?
				break;
				
			case JausMessage.SET_EMERGENCY:
				SetEmergencyMessage emergencyMsg = new SetEmergencyMessage(message);
				thisComponent.getState().setValue(JausState.EMERGENCY);
				break;
				
			case JausMessage.CLEAR_EMERGENCY:
				ClearEmergencyMessage clearEmergenceMsg = new ClearEmergencyMessage(message);
				thisComponent.getState().setValue(JausState.STANDBY);
				break;
				
			case JausMessage.REQUEST_COMPONENT_CONTROL:
				RejectComponentControlMessage rejectControl = new RejectComponentControlMessage();
				rejectControl.setDestination(message.getSource());
				rejectControl.setSource(thisComponent.getAddress());
				buffer = new byte[rejectControl.size()];
				rejectControl.toJausBuffer(buffer);
				packet = new DatagramPacket(buffer, buffer.length, thisNode.getIpAddress(), thisComponent.getPort());
			    outputQueue.push(packet);
				break;
				
			case JausMessage.RELEASE_COMPONENT_CONTROL:
			    // Ignore this message
				// TODO: Maybe log this
				break;
				
			case JausMessage.CONFIRM_COMPONENT_CONTROL:
			    // Ignore this message
				// TODO: Maybe log this
				break;
				
			case JausMessage.REJECT_COMPONENT_CONTROL:
			    // Ignore this message
				// TODO: Maybe log this
				break;
				
			case JausMessage.QUERY_COMPONENT_AUTHORITY:
				reportAuthorityMsg = new ReportComponentAuthorityMessage();
				reportAuthorityMsg.setDestination(message.getSource());
				reportAuthorityMsg.setSource(thisComponent.getAddress());
				reportAuthorityMsg.setAuthorityCode(thisComponent.getAuthority());
				buffer = new byte[reportAuthorityMsg.size()];
				reportAuthorityMsg.toJausBuffer(buffer);
				packet = new DatagramPacket(buffer, buffer.length, thisNode.getIpAddress(), thisComponent.getPort());
				outputQueue.push(packet);
				break;
				
			case JausMessage.QUERY_COMPONENT_STATUS:
				componentStatusMsg = new ReportComponentStatusMessage();
				componentStatusMsg.setDestination(message.getSource());
				componentStatusMsg.setSource(thisComponent.getAddress());
				componentStatusMsg.setPrimaryStatusCode(thisComponent.getState().getValue());
				componentStatusMsg.setSecondaryStatusCode(0);
				buffer = new byte[componentStatusMsg.size()];
				componentStatusMsg.toJausBuffer(buffer);
				packet = new DatagramPacket(buffer, buffer.length, thisNode.getIpAddress(), thisComponent.getPort());
				outputQueue.push(packet);
				break;
				
			case JausMessage.REPORT_COMPONENT_AUTHORITY:
				reportAuthorityMsg = new ReportComponentAuthorityMessage();
				subsystemTable.processComponentAuthority(reportAuthorityMsg, sourceIp, sourcePort);
			    break;
				
			case JausMessage.REPORT_COMPONENT_STATUS:
				ReportComponentStatusMessage componentStatusMsg = new ReportComponentStatusMessage();
				subsystemTable.processComponentStatus(componentStatusMsg, sourceIp, sourcePort);
				break;
			
			case JausMessage.REPORT_HEARTBEAT_PULSE:
				//System.out.println("Got Report HB Pulse from " + message.getSource() + " to " + message.getDestination());
				subsystemTable.processHeartbeat(message, sourceIp, sourcePort);

				if(message.getSource().getSubsystem() == thisComponent.getAddress().getSubsystem())
				{
					if(message.getSource().getNode() == thisComponent.getAddress().getNode())
					{
			        	JausComponent component = new JausComponent(message.getSource());
			        	component.setNode(new JausNode(message.getSource().getNode()));
			        	component.getNode().setSubsystem(new JausSubsystem(message.getSource().getSubsystem()));
			        	if(subsystemTable.hasComponentIdentification(component))
			        	{
			        		return;
			        	}
			        	else
			        	{
							queryIdMsg = new QueryIdentificationMessage();
							queryIdMsg.setQueryType(QueryIdentificationMessage.COMPONENT_IDENTIFICATION);
			        	}
			        	
			        	// If this is from something on our node, we need to query its services
						//System.out.println("CMH: Querying Services of: " + message.getSource().getComponent() + " : " + message.getSource());						    
						queryServicesMsg = new QueryServicesMessage();
						queryServicesMsg.setDestination(message.getSource());
						queryServicesMsg.setSource(thisComponent.getAddress());
						
						buffer = new byte[queryServicesMsg.size()];
						queryServicesMsg.toJausBuffer(buffer);
						packet = new DatagramPacket(buffer, buffer.length, thisNode.getIpAddress(), thisComponent.getPort());
					    outputQueue.push(packet);			        	
					}
					else
					{
			        	JausNode sourceNode = new JausNode(message.getSource().getNode());
			        	sourceNode.setSubsystem(new JausSubsystem(message.getSource().getSubsystem()));
			        	if(subsystemTable.hasNodeIdentification(sourceNode))
			        	{
			        		return;
			        	}
			        	else
			        	{
							queryIdMsg = new QueryIdentificationMessage();
							queryIdMsg.setQueryType(QueryIdentificationMessage.NODE_IDENTIFICATION);	        	    			        		
			        	}
					}	
				}
				else
				{
					// Heartbeat fowarding
		        	if(thisNode.getId() == JausAddress.PRIMARY_NODE_MANAGER_NODE)
		        	{
						//System.out.println("Forwarding HB");
						Enumeration nodes = thisSubsystem.elements();
						JausNode node = null;
						message.getDestination().setSubsystem(thisSubsystem.getId());
						message.getDestination().setComponent(JausComponent.NODE_MANAGER);
						while(nodes.hasMoreElements())
						{
							node = (JausNode)nodes.nextElement();
							if(node.getId() != thisNode.getId())
							{
								message.getDestination().setNode(node.getId());
								//System.out.println("Forwarding HB to: " + message.getDestination());
								buffer = new byte[message.udpSize()];
								message.toJausUdpBuffer(buffer);
								try
								{
									InetAddress destIpAddress = InetAddress.getByName("192.168." + thisSubsystem.getId() + "." + node.getId());
									packet = new DatagramPacket(buffer, buffer.length, destIpAddress, thisComponent.getPort());
									nodeSendQueue.push(packet);
								}
								catch(Exception e)
								{
									System.out.println("MessageRouter: " + e);
									e.printStackTrace(); // now we'll know where it's coming from
									return;
								}
							}
						}	
		        	}		        	

		        	JausSubsystem subsystem = new JausSubsystem(message.getSource().getSubsystem());
		        	if(subsystemTable.hasSubsystemIdentification(subsystem))
		        	{
		        		return;
		        	}
		        	else
		        	{
						queryIdMsg = new QueryIdentificationMessage();
						queryIdMsg.setQueryType(QueryIdentificationMessage.SUBSYSTEM_IDENTIFICATION);
		        	}

				}
											
				queryIdMsg.setDestination(message.getSource());
				queryIdMsg.setSource(thisComponent.getAddress());
				
				buffer = new byte[queryIdMsg.size()];
			    queryIdMsg.toJausBuffer(buffer);
				packet = new DatagramPacket(buffer, buffer.length, thisNode.getIpAddress(), thisComponent.getPort());
			    outputQueue.push(packet);

			    break;
			
			case JausMessage.QUERY_IDENTIFICATION:
				//System.out.println("CMH: Got subs query id from: " + message.getSource());
				queryIdMsg = new QueryIdentificationMessage(message);

				reportIdMsg = new ReportIdentificationMessage();
				reportIdMsg.setDestination(message.getSource());
				reportIdMsg.setSource(thisComponent.getAddress());
				reportIdMsg.setAuthority(thisComponent.getAuthority());
				reportIdMsg.setType(0);
				
				switch(queryIdMsg.getQueryType().getValue())
				{
					case QueryIdentificationMessage.SUBSYSTEM_IDENTIFICATION:
						reportIdMsg.setQueryType(ReportIdentificationMessage.SUBSYSTEM_IDENTIFICATION);
						reportIdMsg.setIdentification(thisSubsystem.getIdentification());
						break;
						
					case QueryIdentificationMessage.NODE_IDENTIFICATION:
						reportIdMsg.setQueryType(ReportIdentificationMessage.NODE_IDENTIFICATION);
						reportIdMsg.setIdentification(thisNode.getIdentification());
						break;
					
					case QueryIdentificationMessage.COMPONENT_IDENTIFICATION:
						reportIdMsg.setQueryType(ReportIdentificationMessage.COMPONENT_IDENTIFICATION);
						reportIdMsg.setIdentification(thisComponent.getIdentification());
						break;
					
					default:
						// TODO: Log as error
						return;
				}

				byte[] buffer = new byte[reportIdMsg.size()];
				reportIdMsg.toJausBuffer(buffer);
				packet = new DatagramPacket(buffer, buffer.length, thisNode.getIpAddress(), thisComponent.getPort());
			    outputQueue.push(packet);
			    break;
			
			case JausMessage.REPORT_IDENTIFICATION:
				//System.out.println("CMH: Got Report Id From: " + message.getSource() + " size: " + message.size());
			
			    reportIdMsg = new ReportIdentificationMessage(message);
				subsystemTable.processReportIdentification(reportIdMsg, sourceIp, sourcePort);
				
				queryConfMsg = new QueryConfigurationMessage();
				queryConfMsg.setDestination(message.getSource());
				queryConfMsg.setSource(thisComponent.getAddress());
				
			    switch(reportIdMsg.getQueryType().getValue())
			    {
					case ReportIdentificationMessage.SUBSYSTEM_IDENTIFICATION:
			        	queryConfMsg.setQueryField(QueryConfigurationMessage.SUBSYSTEM_CONFIGURATION);		        	    
						break;
						
					case ReportIdentificationMessage.NODE_IDENTIFICATION:
						//System.out.println("CMH: Got Report Node Id From: " + message.getSource() + " size: " + message.size());
						if(message.getSource().getSubsystem() == thisComponent.getAddress().getSubsystem())
						{
							queryConfMsg.setQueryField(QueryConfigurationMessage.NODE_CONFIGURATION);		        	    
						}
						else
						{
							return;
						}
						break;

					case ReportIdentificationMessage.COMPONENT_IDENTIFICATION:
						// We don't query the configuration of a component, we query its services
						return;

					default:
			        	// TODO: Log as error
			        	return;
			    }

				createEventMsg = new CreateEventMessage();
				createEventMsg.setDestination(message.getSource());
				createEventMsg.setSource(thisComponent.getAddress());
			    createEventMsg.setMessageCode(JausMessage.QUERY_CONFIGURATION);
			    createEventMsg.setEventType(CreateEventMessage.EVERY_CHANGE);
			    createEventMsg.setQueryMessage(queryConfMsg);

				buffer = new byte[queryConfMsg.size()];
				queryConfMsg.toJausBuffer(buffer);
				packet = new DatagramPacket(buffer, buffer.length, thisNode.getIpAddress(), thisComponent.getPort());
			    outputQueue.push(packet);

				buffer = new byte[createEventMsg.size()];
				createEventMsg.toJausBuffer(buffer);
				packet = new DatagramPacket(buffer, buffer.length, thisNode.getIpAddress(), thisComponent.getPort());
			    outputQueue.push(packet);			    
			    break;

			case JausMessage.QUERY_CONFIGURATION:
				queryConfMsg = new QueryConfigurationMessage(message);

				reportConfMsg = new ReportConfigurationMessage();
				reportConfMsg.setDestination(message.getSource());
				reportConfMsg.setSource(thisComponent.getAddress());
				
				switch(queryConfMsg.getQueryField().getValue())
				{
					case QueryConfigurationMessage.SUBSYSTEM_CONFIGURATION:
						reportConfMsg.setSubsystemConfiguration(thisSubsystem);
						break;
						
					case QueryConfigurationMessage.NODE_CONFIGURATION:
						// Create a new JausSubsystem object and add just this node to it
						// This will allow us to send just the components on this node
						JausSubsystem subsystem = new JausSubsystem(thisSubsystem.getId());
						subsystem.add(thisNode);
						reportConfMsg.setSubsystemConfiguration(subsystem);
						break;

					default: 
						// TODO: Log as error
						return;
				}

				buffer = new byte[reportConfMsg.size()];
				reportConfMsg.toJausBuffer(buffer);
				packet = new DatagramPacket(buffer, buffer.length, thisNode.getIpAddress(), thisComponent.getPort());
			    outputQueue.push(packet);
			    break;

			case JausMessage.REPORT_CONFIGURATION:
				//System.out.println("CMH: Got Report Conf From: " + message.getSource());
				
				// Process new configuration in table
				reportConfMsg = new ReportConfigurationMessage(message);
			    subsystemTable.processReportConfiguration(reportConfMsg, sourceIp, sourcePort);
			   
			    // Check to see if there are any unidentified component and query their respective identification
		    	JausSubsystem reportSubsystem = reportConfMsg.getSubsystemConfiguration();		    	
		    	Enumeration subsystemEnum = reportSubsystem.elements();
				while(subsystemEnum.hasMoreElements())
				{
					JausNode reportNode = (JausNode)subsystemEnum.nextElement();
					if(!subsystemTable.hasNodeIdentification(reportNode))
					{
						queryIdMsg = new QueryIdentificationMessage();
						queryIdMsg.setQueryType(QueryIdentificationMessage.NODE_IDENTIFICATION);		        	    			        		
						queryIdMsg.getDestination().setSubsystem(reportSubsystem.getId());
						queryIdMsg.getDestination().setNode(reportNode.getId());
						queryIdMsg.getDestination().setComponent(JausComponent.NODE_MANAGER);
						queryIdMsg.getDestination().setInstance(JausAddress.PRIMARY_INSTANCE);
						queryIdMsg.setSource(thisComponent.getAddress());
						//System.out.println("CMH: Querying ID of: " + reportNode + " : " + queryIdMsg.getDestination());							
						
						buffer = new byte[queryIdMsg.size()];
					    queryIdMsg.toJausBuffer(buffer);
						packet = new DatagramPacket(buffer, buffer.length, thisNode.getIpAddress(), thisComponent.getPort());
					    outputQueue.push(packet);
					}
				
					Enumeration nodeEnum = reportNode.elements();
					while(nodeEnum.hasMoreElements())
					{
						JausComponent reportComponent = (JausComponent)nodeEnum.nextElement();
						if(!subsystemTable.hasComponentIdentification(reportComponent))
						{
							//System.out.println("CMH: Querying ID of: " + reportComponent + " : " + reportComponent.getAddress());							
							queryIdMsg = new QueryIdentificationMessage();
							queryIdMsg.setQueryType(QueryIdentificationMessage.COMPONENT_IDENTIFICATION);		        	    			        		
							queryIdMsg.setDestination(reportComponent.getAddress());
							queryIdMsg.setSource(thisComponent.getAddress());
							
							buffer = new byte[queryIdMsg.size()];
						    queryIdMsg.toJausBuffer(buffer);
							packet = new DatagramPacket(buffer, buffer.length, thisNode.getIpAddress(), thisComponent.getPort());
						    outputQueue.push(packet);
						}

						//System.out.println("CMH: Querying Services of: " + message.getSource().getComponent() + " : " + message.getSource());						    
						queryServicesMsg = new QueryServicesMessage();
						queryServicesMsg.setDestination(reportComponent.getAddress());
						queryServicesMsg.setSource(thisComponent.getAddress());
						
						buffer = new byte[queryServicesMsg.size()];
						queryServicesMsg.toJausBuffer(buffer);
						packet = new DatagramPacket(buffer, buffer.length, thisNode.getIpAddress(), thisComponent.getPort());
					    outputQueue.push(packet);
						
					}
				}
				break;

			case JausMessage.CREATE_EVENT:
				createEventMsg = new CreateEventMessage(message);

				ConfirmEventMessage confirmEventMsg = new ConfirmEventMessage();
				confirmEventMsg.setDestination(createEventMsg.getSource());
				confirmEventMsg.setSource(thisComponent.getAddress());
				confirmEventMsg.setMessageCode(JausMessage.REPORT_CONFIGURATION);
				
				if(subsystemTable.processCreateEvent(createEventMsg, sourceIp, sourcePort))
				{
					confirmEventMsg.setResponseCode(0); // Successful
				}
				else
				{
					confirmEventMsg.setResponseCode(6); // Message Not Supported
				}
				
				buffer = new byte[confirmEventMsg.size()];
				confirmEventMsg.toJausBuffer(buffer);
				packet = new DatagramPacket(buffer, buffer.length, thisNode.getIpAddress(), thisComponent.getPort());
			    outputQueue.push(packet);
			    break;

			case JausMessage.CONFIGURATION_CHANGED_EVENT_SETUP:
				confChangeSetupMsg = new ConfigurationChangedEventSetupMessage(message);
				subsystemTable.processConfChangeSetup(confChangeSetupMsg, sourceIp, sourcePort);
			    break;
			    
			case JausMessage.CONFIRM_EVENT:
				
			    break;

			case JausMessage.REPORT_SERVICES:
				//System.out.println("CMH: Got Report Services From: " + message.getSource());
				// Process services into table
				reportServicesMsg = new ReportServicesMessage(message);
			    subsystemTable.processReportServices(reportServicesMsg, sourceIp, sourcePort);
			    break;

			case JausMessage.QUERY_SERVICES: // Query Services Command Code				
				//System.out.println("Query Services from " + message.getSource());

				// Respond with our services
				reportServicesMsg = new ReportServicesMessage();

				reportServicesMsg.setDestination(message.getSource());
				reportServicesMsg.setSource(thisComponent.getAddress());
				reportServicesMsg.setServices(thisComponent.getServices());

				buffer = new byte[reportServicesMsg.size()];
				reportServicesMsg.toJausBuffer(buffer);
				packet = new DatagramPacket(buffer, buffer.length, thisNode.getIpAddress(), thisComponent.getPort());
			    outputQueue.push(packet);
			    break;

			default:
			    // TODO: Log as error or warning
				break;
			
		}// switch
	}// process
	
}// Class
