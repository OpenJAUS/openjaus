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

package openjaus.libjaus.message.experimental;

import java.util.*;
import openjaus.libjaus.*;
import openjaus.libjaus.message.*;
import openjaus.libjaus.type.*;

public class ReportServicesMessage extends JausMessage
{
	private static final int REPORT_SERVICES = 0xD4A7;
	private static final int COMMAND_CODE = REPORT_SERVICES;
	
	//TODO: Need Dynamic way to set data size
	private static final int MAX_DATA_SIZE_BYTES = 512;
	
	//Message Fields
	Vector services;

	public ReportServicesMessage()
	{
		super();
		setUserDefinedFlag(EXPERIMENTAL_MESSAGE);
		
		data = new byte[MAX_DATA_SIZE_BYTES];

		//initialize data fields
		services = new Vector();
	}

	public ReportServicesMessage(byte[] buffer)
	{
	    setFromJausBuffer(buffer, 0);
		setUserDefinedFlag(EXPERIMENTAL_MESSAGE);
	}

	public ReportServicesMessage(byte[] buffer, int index)
	{
	    setFromJausBuffer(buffer, index);
		setUserDefinedFlag(EXPERIMENTAL_MESSAGE);
	}

	public ReportServicesMessage(JausMessage jausMessage)
	{
		super(jausMessage);
		setUserDefinedFlag(EXPERIMENTAL_MESSAGE);
		processFromDataBuffer();
	}
	
	public void setCommandCode(int commandCode)
	{
	    this.commandCode = COMMAND_CODE;
	}	
	
	public boolean setServices(Vector services)
	{
		this.services = services;
		return true;
	}

	public Vector getServices()
	{
		return services;
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
		int originalIndex = index;
		
	    if(super.toJausBuffer(buffer, index))
	    {
			index += HEADER_SIZE_BYTES;
			processToJausBuffer(buffer, index);
			
			return true;
	    }
	    else return false;
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

	private void processToJausBuffer(byte[] buffer, int index)
	{
		// Service Count
		JausByte.toJausBuffer(services.size(), buffer, index); index++;
		
		Enumeration servicesEnum = services.elements();
		while(servicesEnum.hasMoreElements())
		{
			JausService service = (JausService)servicesEnum.nextElement();
			
			// Service Type
			JausUnsignedShort.toJausBuffer(service.getType(), buffer, index); 
			index += JausUnsignedShort.SIZE_BYTES;
			
			// Input Command Count
			JausByte.toJausBuffer(service.getInputCommands().size(), buffer, index); index++;
			
			Enumeration inputCommands = service.getInputCommands().elements();
			while(inputCommands.hasMoreElements())
			{
				JausCommand command = (JausCommand)inputCommands.nextElement();
				
				// Pack Command Code
				JausUnsignedShort.toJausBuffer(command.getCommandCode(), buffer, index); 
				index += JausUnsignedShort.SIZE_BYTES;
								
				// Pack PV
				JausUnsignedInteger.toJausBuffer(command.getPresenceVector(), buffer, index); 
				index += JausUnsignedInteger.SIZE_BYTES;
			}
			
			// Output Command Count
			JausByte.toJausBuffer(service.getOutputCommands().size(), buffer, index); index++;
			
			Enumeration outputCommands = service.getOutputCommands().elements();
			while(outputCommands.hasMoreElements())
			{
				JausCommand command = (JausCommand)outputCommands.nextElement();
				
				// Pack Command Code
				JausUnsignedShort.toJausBuffer(command.getCommandCode(), buffer, index); 
				index += JausUnsignedShort.SIZE_BYTES;
								
				// Pack PV
				JausUnsignedInteger.toJausBuffer(command.getPresenceVector(), buffer, index); 
				index += JausUnsignedInteger.SIZE_BYTES;
			}
		}
    }
	
	private int processFromDataBuffer()
	{
		int index = 0;
	
		services = new Vector();

		// Read number of services
		int servicesCount = JausByte.fromJausBuffer(data, index);
		index += JausByte.SIZE_BYTES;

		for(int i = 0; i < servicesCount; i++)
		{
			int serviceType = JausUnsignedShort.fromJausBuffer(data, index);
			index += JausUnsignedShort.SIZE_BYTES;
			
			JausService service = new JausService(serviceType);
			services.add(service);
			
			int inputCommandCount = JausByte.fromJausBuffer(data, index);
			index += JausByte.SIZE_BYTES;
			
			for(int j = 0; j < inputCommandCount; j++)
			{
				int commandCode = JausUnsignedShort.fromJausBuffer(data, index);
				index += JausUnsignedShort.SIZE_BYTES;
				
				long presenceVector = JausUnsignedInteger.fromJausBuffer(data, index);
				index += JausUnsignedInteger.SIZE_BYTES;
				
				service.addInputCommand(commandCode, presenceVector);
			}

			int outputCommandCount = JausByte.fromJausBuffer(data, index);
			index += JausByte.SIZE_BYTES;

			for(int j = 0; j < outputCommandCount; j++)
			{
				int commandCode = JausUnsignedShort.fromJausBuffer(data, index);
				index += JausUnsignedShort.SIZE_BYTES;
				
				long presenceVector = JausUnsignedInteger.fromJausBuffer(data, index);
				index += JausUnsignedInteger.SIZE_BYTES;
				
				service.addOutputCommand(commandCode, presenceVector);
			}
		}		
		return index;
	}	
}