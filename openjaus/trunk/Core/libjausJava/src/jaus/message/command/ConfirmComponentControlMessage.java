//File Name: ConfirmComponentControlMessage.java
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

public class ConfirmComponentControlMessage extends JausMessage
{
	private static final int COMMAND_CODE = CONFIRM_COMPONENT_CONTROL;
	private static final int MAX_DATA_SIZE_BYTES = 1;

	//Message Fields
	JausByte responseCode;
	
	public ConfirmComponentControlMessage()
	{
		super();
		data = new byte[MAX_DATA_SIZE_BYTES];
		responseCode = new JausByte(0);
	}
	
	public ConfirmComponentControlMessage(byte[] buffer)
	{
	    setFromJausBuffer(buffer, 0);
	}
	
	public ConfirmComponentControlMessage(byte[] buffer, int index)
	{
	    setFromJausBuffer(buffer, index);
	}

	public ConfirmComponentControlMessage(JausMessage jausMessage)
	{
		super(jausMessage);
	    responseCode = new JausByte(data);
	}

	public void setCommandCode(int commandCode)
	{
	    this.commandCode = COMMAND_CODE;
	}	
	
	public boolean setResponseCode(int value)
	{
		if(value < 256 && value > -1)
		{
		    responseCode.setValue(value);
			return true;
		}
		else
			return false;
	}
	
	public JausByte getResponseCode()
	{
	    return responseCode;
	}
	
	// Takes a data UDP or regular JAUS buffer and unpacks it into the header data structure and the data attributes
	public boolean setFromJausBuffer(byte[] buffer, int index)
	{
		if(super.setFromJausBuffer(buffer, index))
		{
		    int dataIndex = 0;
		    responseCode = new JausByte(data, dataIndex);
		    dataIndex += responseCode.size();
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
			
			if(responseCode.toJausBuffer(buffer, index))
			{
				index += responseCode.size();
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
			
			if(responseCode.toJausBuffer(buffer, index))
			{
				index += responseCode.size();
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