//File Name: SetLocalVectorMessage.java
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

public class SetLocalVectorMessage extends JausMessage
{
	private static final int COMMAND_CODE = SET_LOCAL_VECTOR;
	private static final int MAX_DATA_SIZE_BYTES = 6;

	//Message Fields
	JausInteger speed; //scaled int
	JausShort heading; //scaled int
	
	public SetLocalVectorMessage()
	{
		super();
		data = new byte[MAX_DATA_SIZE_BYTES];
		speed = new JausInteger(0);
		heading = new JausShort((short)0);
	}
	
	public SetLocalVectorMessage(byte[] buffer)
	{
	    setFromJausBuffer(buffer, 0);
	}
	
	public SetLocalVectorMessage(byte[] buffer, int index)
	{
	    setFromJausBuffer(buffer, index);
	}

	public SetLocalVectorMessage(JausMessage jausMessage)
	{
	    super(jausMessage);
		int dataIndex = 0;
		speed = new JausInteger(data, dataIndex);
		dataIndex += speed.size();
		heading = new JausShort(data, dataIndex);
	}

	public void setCommandCode(int commandCode)
	{
	    this.commandCode = COMMAND_CODE;
	}	
	
	public boolean setSpeed(int value)
	{
		speed.setFromDouble(value, 0.0, 10000.0);
		return true;
	}
	
	public boolean setHeading(int value) 
	{
		heading.setFromDouble((short)value, -Math.PI, Math.PI);
		return true;
	}

	public double getSpeed()
	{
		return speed.scaleToDouble(0.0, 10000.0);
	}
	
	public double getHeading()
	{
		return heading.scaleToDouble(-Math.PI, Math.PI);
	}

	// Takes a data UDP or regular JAUS buffer and unpacks it into the header data structure and the data attributes
	public boolean setFromJausBuffer(byte[] buffer, int index)
	{
		if(super.setFromJausBuffer(buffer, index))
		{
			int dataIndex = 0;
			speed = new JausInteger(data, dataIndex);
			dataIndex += speed.size();
			heading = new JausShort(data, dataIndex);
			dataIndex += heading.size();
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
			
			if(speed.toJausBuffer(buffer, index))
			{
				index += speed.size();
			}
			else
			{
			    return false;				    
			}					    
			if(heading.toJausBuffer(buffer, index))
			{
				index += heading.size();
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
			
			if(speed.toJausBuffer(buffer, index))
			{
				index += speed.size();
			}
			else
			{
			    return false;				    
			}					    
			if(heading.toJausBuffer(buffer, index))
			{
				index += heading.size();
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