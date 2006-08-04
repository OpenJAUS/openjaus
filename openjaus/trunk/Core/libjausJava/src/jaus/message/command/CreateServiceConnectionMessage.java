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