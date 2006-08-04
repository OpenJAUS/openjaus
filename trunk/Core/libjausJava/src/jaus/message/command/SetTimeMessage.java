//File Name: SetTimeMessage.java
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

public class SetTimeMessage extends JausMessage
{
	private static final int COMMAND_CODE = SET_TIME;
	private static final int MAX_DATA_SIZE_BYTES = 7;
	
	public static final int TIME_STAMP_BIT = 0;
	public static final int DATE_STAMP_BIT = 1;

	//Message Fields
	JausBytePresenceVector presenceVector;
	JausUnsignedInteger timeStamp;
	JausUnsignedShort dateStamp;
	
	public SetTimeMessage()
	{
		super();
		data = new byte[MAX_DATA_SIZE_BYTES];
		presenceVector = new JausBytePresenceVector();
		timeStamp = new JausUnsignedInteger(0) ;
		dateStamp = new JausUnsignedShort(0) ;
	}
	
	public SetTimeMessage(byte[] buffer)
	{
	    setFromJausBuffer(buffer, 0);
	}
	
	public SetTimeMessage(byte[] buffer, int index)
	{
	    setFromJausBuffer(buffer, index);
	}

	public SetTimeMessage(JausMessage jausMessage)
	{
	    super(jausMessage);
		int dataIndex = 0;
		presenceVector = new JausBytePresenceVector(data, dataIndex) ;
		dataIndex += presenceVector.size();
		if (presenceVector.isBitSet(TIME_STAMP_BIT))
		{
			timeStamp = new JausUnsignedInteger(data, dataIndex) ;
		}
		dataIndex += presenceVector.size();
		if (presenceVector.isBitSet(DATE_STAMP_BIT))
		{
			dateStamp = new JausUnsignedShort(data, dataIndex) ;
		}
	}

	public void setCommandCode(int commandCode)
	{
	    this.commandCode = COMMAND_CODE;
	}	
	
	public boolean setPresenceVectorBit(int bit)
	{
		return presenceVector.setBit(bit);
	}
	
	public boolean clearPresenceVectorBit(int bit)
	{
		return presenceVector.clearBit(bit);
	}
	
	public boolean setTimeStamp(int value)//TODO: needs to follow bit-wise interpretation
	{
		if(value < JausUnsignedInteger.MAX_VALUE + 1 && value > JausUnsignedInteger.MIN_VALUE - 1)
		{
			timeStamp.setValue(value);
			return true;
		}
		else
			return false;			
	}

	public boolean setDateStamp(int value)//TODO: needs to follow bit-wise interpretation
	{
		if(value < JausUnsignedShort.MAX_VALUE + 1 && value > JausUnsignedShort.MIN_VALUE - 1)
		{
			dateStamp.setValue(value);
			return true;
		}
		else
			return false;			
	}
	
	public JausByte getPresenceVector()
	{
		return presenceVector.getPresenceVector();
	}
	
	public JausUnsignedInteger getTimeStamp()//TODO: needs to follow bit-wise interpretation
	{
		return timeStamp;
	}

	public JausUnsignedShort getDateStamp()//TODO: needs to follow bit-wise interpretation
	{
		return dateStamp;
	}

	// Takes a data UDP or regular JAUS buffer and unpacks it into the header data structure and the data attributes
	public boolean setFromJausBuffer(byte[] buffer, int index)
	{
		if(super.setFromJausBuffer(buffer, index))
		{
			int dataIndex = 0;
			presenceVector = new JausBytePresenceVector(data, dataIndex);
			dataIndex += presenceVector.size();
			if (presenceVector.isBitSet(TIME_STAMP_BIT))
			{
				timeStamp = new JausUnsignedInteger(data, dataIndex) ;
			}
			dataIndex += presenceVector.size();
			if (presenceVector.isBitSet(DATE_STAMP_BIT))
			{
				dateStamp = new JausUnsignedShort(data, dataIndex) ;
			}
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
			
			if(presenceVector.getPresenceVector().toJausBuffer(buffer, index))
			{
				index += presenceVector.size();
			}
			else
			{
			    return false;				    
			}					    
			if(presenceVector.isBitSet(TIME_STAMP_BIT))
			{
				if(timeStamp.toJausBuffer(buffer, index))
				{
					index += timeStamp.size();
				}
				else
				{
			    return false;
				}
			}
			if(presenceVector.isBitSet(DATE_STAMP_BIT))
			{
				if(dateStamp.toJausBuffer(buffer, index))
				{
					index += dateStamp.size();
				}
				else
				{
				    return false;				    
				}
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
			
			if(presenceVector.getPresenceVector().toJausBuffer(buffer, index))
			{
				index += presenceVector.size();
			}
			else
			{
			    return false;				    
			}					    
			if(presenceVector.isBitSet(0))
			{
				if(timeStamp.toJausBuffer(buffer, index))
				{
					index += timeStamp.size();
				}
				else
				{
			    return false;
				}
			}
			if(presenceVector.isBitSet(1))
			{
				if(dateStamp.toJausBuffer(buffer, index))
				{
					index += dateStamp.size();
				}
				else
				{
				    return false;				    
				}
			}
			return true;
	    }
	    else
	    {
	        return false;
	    }
	}
	
	
}