//File Name: ActivateServiceConnectionMessage.java
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

public class ActivateServiceConnectionMessage extends JausMessage
{
	private static final int COMMAND_CODE = ACTIVATE_SERVICE_CONNECTION;
	private static final int MAX_DATA_SIZE_BYTES = 3;

	//Message Fields
	JausUnsignedShort serviceConnectionCommandCode;
	JausByte instanceId;
	
	public ActivateServiceConnectionMessage()
	{
		super();
		data = new byte[MAX_DATA_SIZE_BYTES];
		serviceConnectionCommandCode = new JausUnsignedShort(0);
		instanceId = new JausByte(0);
	}
	
	public ActivateServiceConnectionMessage(byte[] buffer)
	{
	    setFromJausBuffer(buffer, 0);
	}
	
	public ActivateServiceConnectionMessage(byte[] buffer, int index)
	{
	    setFromJausBuffer(buffer, index);
	}

	public ActivateServiceConnectionMessage(JausMessage jausMessage)
	{
	    super(jausMessage);
		int dataIndex = 0;
		serviceConnectionCommandCode = new JausUnsignedShort(data, dataIndex);
		dataIndex += serviceConnectionCommandCode.size();
		instanceId = new JausByte(data, dataIndex);
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
	
	public boolean setInstanceId(int value)
	{
		if(value < JausByte.MAX_VALUE + 1 && value > JausByte.MIN_VALUE - 1)
		{
			instanceId.setValue(value);
			return true;
		}
		else
			return false;			
	}

	public JausUnsignedShort getServiceConnectionCommandCode()
	{
		return serviceConnectionCommandCode;
	}
	
	public JausByte getInstanceId()
	{
		return instanceId;
	}

	// Takes a data UDP or regular JAUS buffer and unpacks it into the header data structure and the data attributes
	public boolean setFromJausBuffer(byte[] buffer, int index)
	{
		if(super.setFromJausBuffer(buffer, index))
		{
			int dataIndex = 0;
			serviceConnectionCommandCode = new JausUnsignedShort(data, dataIndex);
			dataIndex += serviceConnectionCommandCode.size();
			instanceId = new JausByte(data, dataIndex);
			dataIndex += instanceId.size();
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
			if(instanceId.toJausBuffer(buffer, index))
			{
				index += instanceId.size();
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
			if(instanceId.toJausBuffer(buffer, index))
			{
				index += instanceId.size();
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