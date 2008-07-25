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
 * @author Tom Galluzzo (galluzzo@gmail.com)
 * @version 0.1
 * @date: 02/14/05
 */

package openjaus.libjaus.message.inform;
import openjaus.libjaus.message.*;
import openjaus.libjaus.type.*;

public class ReportComponentStatusMessage extends JausMessage
{
	private static final int COMMAND_CODE = REPORT_COMPONENT_STATUS;
	private static final int MAX_DATA_SIZE_BYTES = 5;

	//Message Fields
	JausByte primaryStatusCode;
	JausUnsignedInteger secondaryStatusCode;

	public ReportComponentStatusMessage()
	{
		super();

		data = new byte[MAX_DATA_SIZE_BYTES];

		primaryStatusCode = new JausByte(0);
		secondaryStatusCode = new JausUnsignedInteger(0);
	}
	
	public ReportComponentStatusMessage(byte[] buffer)
	{
	    setFromJausBuffer(buffer, 0);
	}
	
	public ReportComponentStatusMessage(byte[] buffer, int index)
	{
	    setFromJausBuffer(buffer, index);
	}

	public ReportComponentStatusMessage(JausMessage jausMessage)
	{
		super(jausMessage);
		int dataIndex = 0;
		primaryStatusCode = new JausByte(data, dataIndex);
		dataIndex += primaryStatusCode.size();
		secondaryStatusCode = new JausUnsignedInteger(data, dataIndex);
	}

	public void setCommandCode(int commandCode)
	{
	    this.commandCode = COMMAND_CODE;
	}	
	
	public boolean setPrimaryStatusCode(int value)
	{
		if(value < 256 && value > -1)
		{
			primaryStatusCode.setValue(value);
			return true;
		}
		else
			return false;
	}

	public boolean setSecondaryStatusCode(long value)
	{
		if(value < 256 && value > -1) // TODO: Fix range for JAUS compliance
		{
		    secondaryStatusCode.setValue(value);
			return true;
		}
		else
			return false;
	}

	public JausByte getPrimaryStatusCode()
	{
		return primaryStatusCode;
	}

	public JausUnsignedInteger getSecondaryStatusCode()
	{
		return secondaryStatusCode;
	}
	
	// Takes a data UDP or regular JAUS buffer and unpacks it into the header data structure and the data attributes
	public boolean setFromJausBuffer(byte[] buffer, int index)
	{
		if(super.setFromJausBuffer(buffer, index))
		{
		    int dataIndex = 0;
		    primaryStatusCode = new JausByte(data, dataIndex);
		    dataIndex += primaryStatusCode.size();
			secondaryStatusCode = new JausUnsignedInteger(data, dataIndex);
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
			
			if(primaryStatusCode.toJausBuffer(buffer, index))
			{
				index += primaryStatusCode.size();
			}
			else return false;
			
			if(secondaryStatusCode.toJausBuffer(buffer, index))
			{
				index += secondaryStatusCode.size();
			} else return false;				          
			
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
			
			if(primaryStatusCode.toJausBuffer(buffer, index))
			{
				index += primaryStatusCode.size();
			}
			else return false;
			
			if(secondaryStatusCode.toJausBuffer(buffer, index))
			{
				index += secondaryStatusCode.size();
			} else return false;				          
			
			return true;
	    }
	    else
	    {
	        return false;
	    }
	}
	
}