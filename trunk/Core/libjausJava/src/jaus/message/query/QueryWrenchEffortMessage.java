//File Name: QueryWrenchEffortMessage.java
//
// Written By: Danny Kent (jaus@dannykent.com)
//
// Version: 3.2  
//
// Date: 07/04/06
//

package jaus.message.query;
import jaus.message.*;
import jaus.type.JausUnsignedShort;

public class QueryWrenchEffortMessage extends JausMessage
{    
	private static final int COMMAND_CODE = QUERY_WRENCH_EFFORT;
	private static final int MAX_DATA_SIZE_BYTES = 2;
	
	public static final int PROPULSIVE_LINEAR_EFFORT_X_BIT = 0;
	public static final int PROPULSIVE_LINEAR_EFFORT_Y_BIT = 1;
	public static final int PROPULSIVE_LINEAR_EFFORT_Z_BIT = 2;
	public static final int PROPULSIVE_ROTATIONAL_EFFORT_X_BIT = 3;
	public static final int PROPULSIVE_ROTATIONAL_EFFORT_Y_BIT = 4;
	public static final int PROPULSIVE_ROTATIONAL_EFFORT_Z_BIT = 5;
	public static final int RESISTIVE_LINEAR_EFFORT_X_BIT = 6;
	public static final int RESISTIVE_LINEAR_EFFORT_Y_BIT = 7;
	public static final int RESISTIVE_LINEAR_EFFORT_Z_BIT = 8;
	public static final int RESISTIVE_ROTATIONAL_EFFORT_X_BIT = 9;
	public static final int RESISTIVE_ROTATIONAL_EFFORT_Y_BIT = 10;
	public static final int RESISTIVE_ROTATIONAL_EFFORT_Z_BIT = 11;
	
    //Message Fields
	JausShortPresenceVector vector;
		
	public QueryWrenchEffortMessage()
	{
		super();
		vector = new JausShortPresenceVector(); 
	}
	
	public QueryWrenchEffortMessage(byte[] buffer)
	{
		super(buffer, 0);
	}
	
	public QueryWrenchEffortMessage(byte[] buffer, int index)
	{
	    super(buffer, index);
	}

	public QueryWrenchEffortMessage(JausMessage jausMessage)
	{
	    super(jausMessage);
	    vector = new JausShortPresenceVector(data);
	}
	
	public boolean setPresenceVectorBit(int bit)
	{
		return vector.setBit(bit);
	}
	
	public boolean clearPresenceVectorBit(int bit)
	{
		return vector.clearBit(bit);
	}
	
	public JausUnsignedShort getPresenceVector()
	{
		return vector.getPresenceVector();
	}
	
	// Takes a data UDP or regular JAUS buffer and unpacks it into the header data structure and the data attributes
	public boolean setFromJausBuffer(byte[] buffer, int index)
	{
		if(super.setFromJausBuffer(buffer, index))
		{
			vector.setPresenceVector(new JausUnsignedShort(data));
			return true;
		}
		else
			return false;
	}
	
	//TODO: Ask Tom about these messages, something doesn't seem right, but I might just be tired
	// Takes the header and data byte array and packs them into a data buffer
	// This method needs to be overridden for all subclasses of JausMessage to reflect the correct pack routine
	public boolean toJausBuffer(byte[] buffer, int index)
	{
	    if(super.toJausBuffer(buffer, index))
	    {
	    	index += HEADER_SIZE_BYTES;
	    	
	    	if(vector.getPresenceVector().toJausBuffer(buffer, index))
	    	{
	    		index += vector.size();
	    	}
	    	else return false;
	    	
	    	return true;
	    }
	    else
	    	return false;
	}
	
	// Overloaded method to accept a buffer and pack this message into its UDP form
	public boolean toJausUdpBuffer(byte[] buffer, int index)
	{
	    if(super.toJausUdpBuffer(buffer, index))
	    {
	    	index += HEADER_SIZE_BYTES + UDP_HEADER_SIZE_BYTES;
			
	    	if(vector.getPresenceVector().toJausBuffer(buffer, index))
	    	{
	    		index += vector.size();
	    	}
	    	else return false;
	    	
	    	return true;
	    }
	    else
	    	return false;
			
	}
}