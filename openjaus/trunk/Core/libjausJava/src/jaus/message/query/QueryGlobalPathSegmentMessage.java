//File Name: QueryGlobalPathSegmentMessage.java
//
// Written By: Danny Kent (jaus@dannykent.com)
//
// Version: 3.2  
//
// Date: 07/04/06
//

package jaus.message.query;
import jaus.message.*;
import jaus.type.*;

public class QueryGlobalPathSegmentMessage extends JausMessage
{
	private static final int COMMAND_CODE = QUERY_GLOBAL_PATH_SEGMENT;
	private static final int MAX_DATA_SIZE_BYTES = 3;

	public static final int POINT_1_ELEVATION_BIT = 0;
	public static final int POINT_2_ELEVATION_BIT = 1;
    
	//Message Fields
	JausBytePresenceVector vector;
	JausUnsignedShort pathSegmentNumber;
	
	public QueryGlobalPathSegmentMessage()
	{
		super();
		data = new byte[MAX_DATA_SIZE_BYTES];
		vector = new JausBytePresenceVector(); 
		pathSegmentNumber = new JausUnsignedShort();
	}
	
	public QueryGlobalPathSegmentMessage(byte[] buffer)
	{
	    setFromJausBuffer(buffer, 0);
	}
	
	public QueryGlobalPathSegmentMessage(byte[] buffer, int index)
	{
	    setFromJausBuffer(buffer, index);
	}

	public QueryGlobalPathSegmentMessage(JausMessage jausMessage)
	{
	    super(jausMessage);
	    int dataIndex = 0;
	    pathSegmentNumber = new JausUnsignedShort(data, dataIndex);
	    dataIndex += pathSegmentNumber.size();
	    vector = new JausBytePresenceVector(data, dataIndex);
	}

	public void setCommandCode(int commandCode)
	{
	    this.commandCode = COMMAND_CODE;
	}	
	
	public boolean setPresenceVectorBit(int bit)
	{
		return vector.setBit(bit);
	}
	
	public boolean clearPresenceVectorBit(int bit)
	{
		return vector.clearBit(bit);
	}
	
	public JausByte getPresenceVector()
	{
		return vector.getPresenceVector();
	}

	public boolean setPathSegmentNumber(int value)
	{
		if(value < JausUnsignedShort.MAX_VALUE + 1 && value > JausUnsignedShort.MIN_VALUE - 1)
		{
			pathSegmentNumber.setValue(value);
			return true;
		}
		else
			return false;
	}

	public JausUnsignedShort getPathSegmentNumber()
	{
		return pathSegmentNumber;
	}

	// Takes a data UDP or regular JAUS buffer and unpacks it into the header data structure and the data attributes
	public boolean setFromJausBuffer(byte[] buffer, int index)
	{
		if(super.setFromJausBuffer(buffer, index))
		{
		    int dataIndex = 0;
		    pathSegmentNumber = new JausUnsignedShort(data, dataIndex);
		    dataIndex += pathSegmentNumber.size();
		    vector.setPresenceVector(new JausByte(data, dataIndex));
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
			
			if(pathSegmentNumber.toJausBuffer(buffer, index))
			{
				index += pathSegmentNumber.size();
			}
			else return false;
			
			if(vector.getPresenceVector().toJausBuffer(buffer, index))
	    	{
	    		index += vector.size();
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
			
			if(pathSegmentNumber.toJausBuffer(buffer, index))
			{
				index += pathSegmentNumber.size();
			}
			else return false;
			
	    	if(vector.getPresenceVector().toJausBuffer(buffer, index))
	    	{
	    		index += vector.size();
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