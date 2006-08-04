//File Name: QueryGlobalWaypoint.java
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

public class QueryGlobalWaypoint extends JausMessage
{
	private static final int COMMAND_CODE = QUERY_GLOBAL_WAYPOINT;
	private static final int MAX_DATA_SIZE_BYTES = 2;

	//Message Fields
	JausUnsignedShort waypointNumber;
	
	public QueryGlobalWaypoint()
	{
		super();
		data = new byte[MAX_DATA_SIZE_BYTES];
		waypointNumber = new JausUnsignedShort();
	}
	
	public QueryGlobalWaypoint(byte[] buffer)
	{
	    setFromJausBuffer(buffer, 0);
	}
	
	public QueryGlobalWaypoint(byte[] buffer, int index)
	{
	    setFromJausBuffer(buffer, index);
	}

	public QueryGlobalWaypoint(JausMessage jausMessage)
	{
	    super(jausMessage);
	    waypointNumber = new JausUnsignedShort(data);
	}

	public void setCommandCode(int commandCode)
	{
	    this.commandCode = COMMAND_CODE;
	}	
	
	public boolean setWaypointNumber(int value)
	{
		if(value < JausUnsignedShort.MAX_VALUE + 1 && value > JausUnsignedShort.MIN_VALUE - 1)
		{
			waypointNumber.setValue(value);
		}
		else
			return false;
		
		return true;
	}

	public JausUnsignedShort getWaypointNumber()
	{
		return waypointNumber;
	}

	// Takes a data UDP or regular JAUS buffer and unpacks it into the header data structure and the data attributes
	public boolean setFromJausBuffer(byte[] buffer, int index)
	{
		if(super.setFromJausBuffer(buffer, index))
		{
		    int dataIndex = 0;
		    waypointNumber = new JausUnsignedShort(data, dataIndex);
		    dataIndex += waypointNumber.size();
		}
		else
		{
		    return false;
		}
		
		return true;
	}
	
	// Takes the header and data byte array and packs them into a data buffer
	// This method needs to be overridden for all subclasses of JausMessage to reflect the correct pack routine
	public boolean toJausBuffer(byte[] buffer, int index)
	{
	    if(super.toJausBuffer(buffer, index))
	    {
			index += HEADER_SIZE_BYTES;
			
			if(waypointNumber.toJausBuffer(buffer, index))
			{
				index += waypointNumber.size();
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
			
			if(waypointNumber.toJausBuffer(buffer, index))
			{
				index += waypointNumber.size();
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