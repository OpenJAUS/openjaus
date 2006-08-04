//File Name: SetEmergencyMessage.java
//
// Written By: Danny Kent (jaus@dannykent.com)
//
// Version: 3.2  
//
// Date: 07/04/06
//

package jaus.message.command;
import jaus.message.*;
import jaus.type.*;

public class SetEmergencyMessage extends JausMessage
{
	private static final int COMMAND_CODE = SET_EMERGENCY;
	private static final int MAX_DATA_SIZE_BYTES = 2;

	//Message Fields
	JausUnsignedShort emergencyCode;
	
	public SetEmergencyMessage()
	{
		super();
		data = new byte[MAX_DATA_SIZE_BYTES];
		emergencyCode = new JausUnsignedShort(0);
	}
	
	public SetEmergencyMessage(byte[] buffer)
	{
	    setFromJausBuffer(buffer, 0);
	}
	
	public SetEmergencyMessage(byte[] buffer, int index)
	{
	    setFromJausBuffer(buffer, index);
	}

	public SetEmergencyMessage(JausMessage jausMessage)
	{
	    super(jausMessage);
	    emergencyCode = new JausUnsignedShort(data);
	}

	public void setCommandCode(int commandCode)
	{
	    this.commandCode = COMMAND_CODE;
	}	
	
	public boolean setEmergencyCode(int value)
	{
	    emergencyCode.setValue(value);
		return true;
	}

	public JausUnsignedShort getEmergencyCode()
	{
		return emergencyCode;
	}

	// Takes a data UDP or regular JAUS buffer and unpacks it into the header data structure and the data attributes
	public boolean setFromJausBuffer(byte[] buffer, int index)
	{
		if(super.setFromJausBuffer(buffer, index))
		{
		    int dataIndex = 0;
		    emergencyCode = new JausUnsignedShort(data, dataIndex);
		    dataIndex += emergencyCode.size();
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
			
			if(emergencyCode.toJausBuffer(buffer, index))
			{
				index += emergencyCode.size();
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
			
			if(emergencyCode.toJausBuffer(buffer, index))
			{
				index += emergencyCode.size();
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