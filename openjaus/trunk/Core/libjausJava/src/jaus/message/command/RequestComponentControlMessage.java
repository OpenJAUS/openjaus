//File Name: RequestComponentControlMessage.java
//
// Written By: Tom Galluzzo (galluzzo@gmail.com)
//
// Version: 3.2  
//
// Date: 07/04/06
//

package jaus.message.command;
import jaus.message.*;
import jaus.type.*;

public class RequestComponentControlMessage extends JausMessage
{
	private static final int COMMAND_CODE = REQUEST_COMPONENT_CONTROL;
	private static final int MAX_DATA_SIZE_BYTES = 1;

	//Message Fields
	JausByte authorityCode;
	
	public RequestComponentControlMessage()
	{
		super();
		data = new byte[MAX_DATA_SIZE_BYTES];
		authorityCode = new JausByte(0);
	}
	
	public RequestComponentControlMessage(byte[] buffer)
	{
	    setFromJausBuffer(buffer, 0);
	}
	
	public RequestComponentControlMessage(byte[] buffer, int index)
	{
	    setFromJausBuffer(buffer, index);
	}

	public RequestComponentControlMessage(JausMessage jausMessage)
	{
	    super(jausMessage);
	    authorityCode = new JausByte(data);
	}

	public void setCommandCode(int commandCode)
	{
	    this.commandCode = COMMAND_CODE;
	}	
	
	public boolean setAuthorityCode(int value)
	{
		if(value < 256 && value > -1)
		{
			authorityCode.setValue(value);
			return true;
		}
		else
			return false;
	}

	public JausByte getAuthorityCode()
	{
		return authorityCode;
	}
	
	// Takes a data UDP or regular JAUS buffer and unpacks it into the header data structure and the data attributes
	public boolean setFromJausBuffer(byte[] buffer, int index)
	{
		if(super.setFromJausBuffer(buffer, index))
		{
		    int dataIndex = 0;
		    authorityCode = new JausByte(data, dataIndex);
		    dataIndex += authorityCode.size();
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
			
			if(authorityCode.toJausBuffer(buffer, index))
			{
				index += authorityCode.size();
				return true;
			}
			else
			{
			    return false;				    
			}	        
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
			
			if(authorityCode.toJausBuffer(buffer, index))
			{
				index += authorityCode.size();
				return true;
			}
			else
			{
			    return false;				    
			}	        
	    }
	    else
	    {
	        return false;
	    }
	}
	
}