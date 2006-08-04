//File Name: QueryVelocityStateMessage.java
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

public class QueryVelocityStateMessage extends JausMessage
{    
	private static final int COMMAND_CODE = QUERY_VELOCITY_STATE;
	private static final int MAX_DATA_SIZE_BYTES = 2;
	
	public static final int VELOCITY_X_BIT = 0;
	public static final int VELOCITY_Y_BIT = 1;
	public static final int VELOCITY_Z_BIT = 2;
	public static final int VELOCITY_RMS_BIT = 3;
	public static final int ROLL_RATE_BIT = 4;
	public static final int PITCH_RATE_BIT = 5;
	public static final int YAW_RATE_BIT = 6;
	public static final int RATE_RMS_BIT = 7;
	public static final int TIME_STAMP_BIT = 8;
	// NOTE: The PV for this message says field 11 which isn't defined in the message
	
    //Message Fields
	JausShortPresenceVector vector;
		
	public QueryVelocityStateMessage()
	{
		super();
		vector = new JausShortPresenceVector(); 
	}
	
	public QueryVelocityStateMessage(byte[] buffer)
	{
		super(buffer, 0);
	}
	
	public QueryVelocityStateMessage(byte[] buffer, int index)
	{
	    super(buffer, index);
	}

	public QueryVelocityStateMessage(JausMessage jausMessage)
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