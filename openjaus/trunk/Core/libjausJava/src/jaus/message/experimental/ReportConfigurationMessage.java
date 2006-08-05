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
/**
 * @author Danny Kent (jaus@dannykent.com)
 * @version 0.1
 * @date: 02/14/05
 */

package jaus.message.experimental;

import java.util.*;
import jaus.*;
import jaus.message.*;
import jaus.type.*;

public class ReportConfigurationMessage extends JausMessage
{
	private static final int REPORT_CONFIGURATION = 0xD4A6;
	private static final int COMMAND_CODE = REPORT_CONFIGURATION;
	
	//TODO: Need Dynamic way to set data size
	private static final int MAX_DATA_SIZE_BYTES = 4080;
	
	private static final int INDENTIFICATION_STRING_SIZE_BYTES = 80;

	//Message Fields
	JausSubsystem subsystemConfiguration;

	public ReportConfigurationMessage()
	{
		super();
		setUserDefinedFlag(EXPERIMENTAL_MESSAGE);
		
		data = new byte[MAX_DATA_SIZE_BYTES];

		//initialize data fields
		subsystemConfiguration = new JausSubsystem();
	}

	public ReportConfigurationMessage(byte[] buffer)
	{
	    setFromJausBuffer(buffer, 0);
	}

	public ReportConfigurationMessage(byte[] buffer, int index)
	{
	    setFromJausBuffer(buffer, index);
	}

	public ReportConfigurationMessage(JausMessage jausMessage)
	{
		super(jausMessage);
		processFromDataBuffer();
	}
	
	public void setCommandCode(int commandCode)
	{
	    this.commandCode = COMMAND_CODE;
	}	
	
	public boolean setSubsystemConfiguration(JausSubsystem subsystemConfiguration)
	{
		this.subsystemConfiguration = subsystemConfiguration;
		return true;
	}

	public JausSubsystem getSubsystemConfiguration()
	{
		return subsystemConfiguration;
	}
	
	// Takes a data UDP or regular JAUS buffer and unpacks it into the header data structure and the data attributes
	public boolean setFromJausBuffer(byte[] buffer, int index)
	{
    	if(super.setFromJausBuffer(buffer, index))
		{
			processFromDataBuffer();
			return true;
		}
		else
		{
		    return false;
		}
	}
	
	// Takes the header and data byte array and packs them into a data buffer
	// This method needs to be overridden for all subclasses of JausMessage to reflect the correct pack routine
	public boolean toJausBuffer(byte[] buffer, int index)
	{
//		if(super.toJausBuffer(buffer, index))
//	    {
//			index += HEADER_SIZE_BYTES;
//			processToJausBuffer(buffer, index);
//						
//			return true;
//	    }
//	    else return false;
		int dataSize = processToJausBuffer(data, 0);
		
		byte[] tempData = new byte[dataSize];
		System.arraycopy(data, 0, tempData, 0, dataSize);
		data = tempData;
		
		return super.toJausBuffer(buffer, index);
	}

	// Overloaded method to accept a buffer and pack this message into its UDP form
	public boolean toJausUdpBuffer(byte[] buffer, int index)
	{
	    if(super.toJausUdpBuffer(buffer, index))
	    {
	    	index += HEADER_SIZE_BYTES + UDP_HEADER_SIZE_BYTES;
			processToJausBuffer(buffer, index);
			return true;
	    }
	    else return false;
	}

	private int processToJausBuffer(byte[] buffer, int index)
	{		
		int originalIndex = index;
		
		// Set Node Count Field
		JausByte.toJausBuffer(subsystemConfiguration.size(), buffer, index); index++;
	    
	    Enumeration subsystemElements = subsystemConfiguration.elements();
	    while(subsystemElements.hasMoreElements())
	    {
	        JausNode node = (JausNode)subsystemElements.nextElement();
		    // Set node Id field
	        JausByte.toJausBuffer(node.getId(), buffer, index); index++;
		    // Set component count field
	        JausByte.toJausBuffer(node.size(), buffer, index); index++;
	        
		    Enumeration nodeElements = node.elements();
		    while(nodeElements.hasMoreElements())
		    {
		        JausComponent component = (JausComponent)nodeElements.nextElement();
			    // Set component Id field
		        JausByte.toJausBuffer(component.getAddress().getComponent(), buffer, index); index++;
			    // Set component Instance field
		        JausByte.toJausBuffer(component.getAddress().getInstance(), buffer, index); index++;			    
		    }
	    }
	    return (index - originalIndex);
    }
	
	private int processFromDataBuffer()
	{
    	/*
		System.out.println("Unpacking from: ");
	    for(int i=0; i<30; i++)
	    {
	    	System.out.print(" " + data[i]);
	    }
    	System.out.println();
    	*/

    	int index = 0;
		
		int subsystemId = source.getSubsystem();
		subsystemConfiguration = new JausSubsystem(subsystemId);

		//Read number of nodes
		int nodeCount = JausByte.fromJausBuffer(data, index);
		index += JausByte.SIZE_BYTES;

		if(nodeCount < 1) nodeCount = 1; //TODO: Check Jaus Compliance
		
		for(int i = 0; i < nodeCount; i++)
		{
			//Reads next byte from buffer which is node ID
			int nodeId = JausByte.fromJausBuffer(data, index);
			index += JausByte.SIZE_BYTES;
			
			//Create node and add to table
			JausNode tempNode = new JausNode(nodeId);
			tempNode.setSubsystem(subsystemConfiguration);
			subsystemConfiguration.add(tempNode);
			
			//read number of components on this node
			int compCount = JausByte.fromJausBuffer(data, index);
			index += JausByte.SIZE_BYTES;
			
			for(int j = 0; j < compCount; j++)
			{
				//read component ID
				int compId = JausByte.fromJausBuffer(data, index);
				index += JausByte.SIZE_BYTES;
				
				//read instance ID
				int instId = JausByte.fromJausBuffer(data, index);
				index += JausByte.SIZE_BYTES;
				
				//set-up the JausAddress of the component
				JausAddress address = new JausAddress(subsystemId, nodeId, compId, instId);

				//create component and add to table
				JausComponent tempComp = new JausComponent(address);
				tempComp.setNode(tempNode);
				tempNode.add(tempComp);
			}
		}
		return index;
	}	
}