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
//File Name: CreateServiceConnectionMessage.java
//
// Written By: Bob Touchton (btouch@comcast.net)
//
// Version: 3.2  
//
// Date: 07/04/06
//

package jaus.message.command;
import jaus.message.*;
import jaus.type.*;

public class CreateServiceConnectionMessage extends JausMessage
{
	private static final int COMMAND_CODE = CREATE_SERVICE_CONNECTION;
	private static final int MAX_DATA_SIZE_BYTES = 8;

	//Message Fields
	JausUnsignedShort serviceConnectionCommandCode;
	JausUnsignedShort requestedPeriodicUpdateRateHertz; //scaled int
	JausUnsignedInteger serviceConnectionPresenceVector;
	
	public CreateServiceConnectionMessage()
	{
		super();
		data = new byte[MAX_DATA_SIZE_BYTES];
		serviceConnectionCommandCode = new JausUnsignedShort(0);
		requestedPeriodicUpdateRateHertz = new JausUnsignedShort(0);
		serviceConnectionPresenceVector = new JausUnsignedInteger(0);
	}
	
	public CreateServiceConnectionMessage(byte[] buffer)
	{
	    setFromJausBuffer(buffer, 0);
	}
	
	public CreateServiceConnectionMessage(byte[] buffer, int index)
	{
	    setFromJausBuffer(buffer, index);
	}

	public CreateServiceConnectionMessage(JausMessage jausMessage)
	{
	    super(jausMessage);
		int dataIndex = 0;
		serviceConnectionCommandCode = new JausUnsignedShort(data, dataIndex);
		dataIndex += serviceConnectionCommandCode.size();
		requestedPeriodicUpdateRateHertz = new JausUnsignedShort(data, dataIndex);
		dataIndex += requestedPeriodicUpdateRateHertz.size();
		serviceConnectionPresenceVector = new JausUnsignedInteger(data, dataIndex);
	}

	public void setCommandCode(int commandCode)
	{
	    this.commandCode = COMMAND_CODE;
	}	
	
	public boolean setServiceConnectionCommandCode(int value)
	{
		if(value < JausUnsignedShort.MAX_VALUE + 1 && value > JausUnsignedShort.MIN_VALUE - 1)
		{
			serviceConnectionCommandCode.setValue(value);
			return true;
		}
		else
			return false;	
	}
	
	
	public boolean setRequestedPeriodicUpdateRate(double value)
	{
		requestedPeriodicUpdateRateHertz.setFromDouble(value, 0.0, 1092.0);
		return true;
	}
	
	public boolean setServiceConnectionPresenceVector(int value)
	{
		if(value < JausUnsignedInteger.MAX_VALUE + 1 && value > JausUnsignedInteger.MIN_VALUE - 1)
		{
			serviceConnectionPresenceVector.setValue(value);
			return true;
		}
		else
			return false;				
	}

	public JausUnsignedShort getServiceConnectionCommandCode()
	{
		return serviceConnectionCommandCode;
	}
	
	public double getRequestedPeriodicUpdateRate()
	{
		return requestedPeriodicUpdateRateHertz.scaleToDouble(0.0, 1092.0);
	}

	public JausUnsignedInteger getServiceConnectionPresenceVector()
	{
		return serviceConnectionPresenceVector;
	}
	
	// Takes a data UDP or regular JAUS buffer and unpacks it into the header data structure and the data attributes
	public boolean setFromJausBuffer(byte[] buffer, int index)
	{
		if(super.setFromJausBuffer(buffer, index))
		{
			int dataIndex = 0;
			serviceConnectionCommandCode = new JausUnsignedShort(data, dataIndex);
			dataIndex += serviceConnectionCommandCode.size();
			requestedPeriodicUpdateRateHertz = new JausUnsignedShort(data, dataIndex);
			dataIndex += requestedPeriodicUpdateRateHertz.size();
			serviceConnectionPresenceVector = new JausUnsignedInteger(data, dataIndex);
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
	    if(super.toJausBuffer(buffer, index))
	    {
			index += HEADER_SIZE_BYTES;
			
			if(serviceConnectionCommandCode.toJausBuffer(buffer, index))
			{
				index += serviceConnectionCommandCode.size();
			}
			else
			{
			    return false;				    
			}					    
   			if(requestedPeriodicUpdateRateHertz.toJausBuffer(buffer, index))
			{
				index += requestedPeriodicUpdateRateHertz.size();
			}
			else
			{
			    return false;				    
			}	        
			if(serviceConnectionPresenceVector.toJausBuffer(buffer, index))
			{
				index += serviceConnectionPresenceVector.size();
			}
			else
			{
			    return false;				    
			}	  
			return true;
	    }
	    else
	    {
	        return false;
	    }
	}

	// Overloaded method to accept a buffer and pack this message into its UDP form
	public boolean toJausUdpBuffer(byte[] buffer, int index)
	{
	    if(super.toJausUdpBuffer(buffer, index))
	    {
	    	index += HEADER_SIZE_BYTES + UDP_HEADER_SIZE_BYTES;
			
			if(serviceConnectionCommandCode.toJausBuffer(buffer, index))
			{
				index += serviceConnectionCommandCode.size();
			}
			else
			{
			    return false;				    
			}					    
			if(requestedPeriodicUpdateRateHertz.toJausBuffer(buffer, index))
			{
				index += requestedPeriodicUpdateRateHertz.size();
			}
			else
			{
			    return false;				    
			}	        
			if(serviceConnectionPresenceVector.toJausBuffer(buffer, index))
			{
				index += serviceConnectionPresenceVector.size();
			}
			else
			{
			    return false;				    
			}	  
			return true;
	    }
	    else
	    {
	        return false;
	    }
	}
	
	
}