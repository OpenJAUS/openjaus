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
import openjaus.libjaus.message.*;
import  openjaus.libjaus.type.*;

public class ReportIdentificationMessage extends JausMessage
{
	private static final int REPORT_IDENTIFICATION = 0xD4A5;
	private static final int COMMAND_CODE = REPORT_IDENTIFICATION;
	private static final int MAX_DATA_SIZE_BYTES = 84;
	
	private static final int INDENTIFICATION_STRING_SIZE_BYTES = 80;

	public static final int SYSTEM_IDENTIFICATION 		= 1;
	public static final int SUBSYSTEM_IDENTIFICATION 	= 2;
	public static final int NODE_IDENTIFICATION 		= 3;
	public static final int COMPONENT_IDENTIFICATION 	= 4;
	
	//Message Fields
	JausByte queryType;
	JausByte authority;
	JausUnsignedShort type;
	String identification;
	
	public ReportIdentificationMessage()
	{
		super();
		setUserDefinedFlag(EXPERIMENTAL_MESSAGE);

		data = new byte[MAX_DATA_SIZE_BYTES];

		queryType = new JausByte(0);
		authority = new JausByte(0);
		type = new JausUnsignedShort(0);
		identification = "";
	}

	public ReportIdentificationMessage(byte[] buffer)
	{
	    setFromJausBuffer(buffer, 0);
	}

	public ReportIdentificationMessage(byte[] buffer, int index)
	{
	    setFromJausBuffer(buffer, index);
	}

	public ReportIdentificationMessage(JausMessage jausMessage)
	{
	    super(jausMessage);
		int dataIndex = 0;
		
		queryType = new JausByte(data, dataIndex);
		dataIndex += queryType.size();
		
		authority = new JausByte(data, dataIndex);
		dataIndex += authority.size();

		type = new JausUnsignedShort(data, dataIndex);
		dataIndex += type.size();
		
		if(data.length - 4 > 3 && data.length - 4 <= 80)
		{
			identification = new String(data, dataIndex, data.length - 4);
		}
		else
		{
			identification = new String("Null");			
		}
	}

	public void setCommandCode(int commandCode)
	{
	    this.commandCode = COMMAND_CODE;
	}	
	
	public boolean setQueryType(int value)
	{
		if(value < 5 && value > 0)
		{
			queryType.setValue(value);
			return true;
		}
		else
		{
			return false;
		}
	}

	public boolean setAuthority(int value)
	{
		if(value < 256 && value > -1)
		{
			authority.setValue(value);
			return true;
		}
		else
			return false;
	}

	public boolean setType(int value)
	{
		if(value < JausUnsignedShort.MAX_VALUE + 1 && value > JausUnsignedShort.MIN_VALUE - 1)
		{
			type.setValue(value);
			return true;
		}
		else
			return false;
	}
	
	public void setIdentification(String identification)
	{
	    this.identification = identification;
	}
	
	public JausByte getQueryType()
	{
		return queryType;
	}

	public JausByte getAuthority()
	{
		return authority;
	}
	
	public JausUnsignedShort getType()
	{
		return type;
	}
	
	public String getIdentification()
	{
		return identification;
	}
	
	// Takes a data UDP or regular JAUS buffer and unpacks it into the header data structure and the data attributes
	public boolean setFromJausBuffer(byte[] buffer, int index)
	{
		if(super.setFromJausBuffer(buffer, index))
		{
		    int dataIndex = 0;
		    
		    queryType = new JausByte(data, dataIndex);
			dataIndex += queryType.size();

			authority = new JausByte(data, dataIndex);
			dataIndex += authority.size();
			
			type = new JausUnsignedShort(data, dataIndex);
			dataIndex += type.size();
			identification = new String(data, dataIndex, INDENTIFICATION_STRING_SIZE_BYTES);
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
			
			if(queryType.toJausBuffer(buffer, index))
			{
				index += queryType.size();
			}
			else return false;

			if(authority.toJausBuffer(buffer, index))
			{
				index += authority.size();
			}
			else return false;
			
			if(type.toJausBuffer(buffer, index))
			{
				index += type.size();
			}
			else return false;
			
			byte[] tempBuffer = identification.getBytes();
			if(buffer.length >= tempBuffer.length + index)
			{
				System.arraycopy(tempBuffer, 0, buffer, index, tempBuffer.length);
				
				for(index = index + tempBuffer.length; index < buffer.length; index++)
				{
				    buffer[index] = 0;
				}
			}
			else return false;
			
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
			
			if(queryType.toJausBuffer(buffer, index))
			{
				index += queryType.size();
			}
			else return false;

			if(authority.toJausBuffer(buffer, index))
			{
				index += authority.size();
			}
			else return false;
			
			if(type.toJausBuffer(buffer, index))
			{
				index += type.size();
			}
			else return false;
			
			byte[] tempBuffer = identification.getBytes();
			if(buffer.length >= tempBuffer.length + index)
			{
				System.arraycopy(tempBuffer, 0, buffer, index, tempBuffer.length);
			}
			else return false;			
			
			return true;
	    }
	    else
	    {
	        return false;
	    }
	}
	
}
