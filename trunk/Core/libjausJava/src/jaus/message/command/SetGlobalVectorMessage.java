//File Name: SetGlobalVectorMessage.java
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

public class SetGlobalVectorMessage extends JausMessage
{
	private static final int COMMAND_CODE = SET_GLOBAL_VECTOR;
	private static final int MAX_DATA_SIZE_BYTES = 13;

	public static final int SPEED_BIT = 0;
	public static final int ALTITUDE_BIT = 1;
	public static final int HEADING_BIT = 2;
	public static final int ROLL_BIT = 3;
	public static final int PITCH_BIT = 4;
	
	//Message Fields
	JausBytePresenceVector vector;
	JausUnsignedShort speed; //scaled int
	JausInteger altitude; //scaled int
	JausShort heading; //scaled int
	JausShort roll; //scaled int
	JausShort pitch; //scaled int
	
	public SetGlobalVectorMessage()
	{
		super();
		data = new byte[MAX_DATA_SIZE_BYTES];
		vector = new JausBytePresenceVector();
		speed = new JausUnsignedShort((short)0);
		altitude = new JausInteger((short)0);
		heading = new JausShort((short)0);
		roll = new JausShort((short)0);
		pitch = new JausShort((short)0);
	}
	
	public SetGlobalVectorMessage(byte[] buffer)
	{
	    setFromJausBuffer(buffer, 0);
	}
	
	public SetGlobalVectorMessage(byte[] buffer, int index)
	{
	    setFromJausBuffer(buffer, index);
	}

	public SetGlobalVectorMessage(JausMessage jausMessage)
	{
	    super(jausMessage);
		int dataIndex = 0;
		vector = new JausBytePresenceVector(data, dataIndex) ;
		dataIndex += vector.size();
		if (vector.isBitSet(SPEED_BIT))
		{
			speed = new JausUnsignedShort(data, dataIndex) ;
		}
		dataIndex += speed.size();
		if (vector.isBitSet(ALTITUDE_BIT))
		{
			altitude = new JausInteger(data, dataIndex) ;
		}
		dataIndex += altitude.size();
		if (vector.isBitSet(HEADING_BIT))
		{
			heading = new JausShort(data, dataIndex) ;
		}
		dataIndex += heading.size();
		if (vector.isBitSet(ROLL_BIT))
		{
			roll = new JausShort(data, dataIndex) ;
		}
		dataIndex += roll.size();
		if (vector.isBitSet(PITCH_BIT))
		{
			pitch = new JausShort(data, dataIndex) ;
		}
		dataIndex += pitch.size();
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
	
	public boolean setSpeed(double value)
	{
		if(value < JausUnsignedShort.MAX_VALUE + 1 && value > JausUnsignedShort.MIN_VALUE - 1)
		{
			speed.setFromDouble(value, 0.0,10000.0);
			return true;
		}
		else
			return false;			
	}
	public boolean setAltitude(double value)
	{
		if(value < JausInteger.MAX_VALUE + 1 && value > JausInteger.MIN_VALUE - 1)
		{
			altitude.setFromDouble(value, -10000.0,35000.0);
			return true;
		}
		else
			return false;			
	}
	public boolean setHeading(double value)
	{
		if(value < JausShort.MAX_VALUE + 1 && value > JausShort.MIN_VALUE - 1)
		{
			heading.setFromDouble(value, -Math.PI,Math.PI);
			return true;
		}
		else
			return false;			
	}
	public boolean setRoll(double value)
	{
		if(value < JausShort.MAX_VALUE + 1 && value > JausShort.MIN_VALUE - 1)
		{
			roll.setFromDouble(value, -Math.PI,Math.PI);
			return true;
		}
		else
			return false;			
	}
	public boolean setPitch(double value)
	{
		if(value < JausShort.MAX_VALUE + 1 && value > JausShort.MIN_VALUE - 1)
		{
			pitch.setFromDouble(value, -Math.PI,Math.PI);
			return true;
		}
		else
			return false;			
	}
	
	public JausByte getPresenceVector()
	{
		return vector.getPresenceVector();
	}	
	public double getSpeed()
	{
		return speed.scaleToDouble( 0.0,10000.0);
	}
	public double getAltitude()
	{
		return altitude.scaleToDouble(-10000.0,35000.0);
	}
	public double getHeading()
	{
		return heading.scaleToDouble(-Math.PI,Math.PI);
	}
	public double getRoll()
	{
		return roll.scaleToDouble(-Math.PI,Math.PI);
	}
	public double getPitch()
	{
		return pitch.scaleToDouble(-Math.PI,Math.PI);
	}
	
	// Takes a data UDP or regular JAUS buffer and unpacks it into the header data structure and the data attributes
	public boolean setFromJausBuffer(byte[] buffer, int index)
	{
		if(super.setFromJausBuffer(buffer, index))
		{
			int dataIndex = 0;
			vector = new JausBytePresenceVector(data, dataIndex) ;
			dataIndex += vector.size();
			if (vector.isBitSet(SPEED_BIT))
			{
				speed = new JausUnsignedShort(data, dataIndex) ;
			}
			dataIndex += speed.size();
			if (vector.isBitSet(ALTITUDE_BIT))
			{
				altitude = new JausInteger(data, dataIndex) ;
			}
			dataIndex += altitude.size();
			if (vector.isBitSet(HEADING_BIT))
			{
				heading = new JausShort(data, dataIndex) ;
			}
			dataIndex += heading.size();
			if (vector.isBitSet(ROLL_BIT))
			{
				roll = new JausShort(data, dataIndex) ;
			}
			dataIndex += roll.size();
			if (vector.isBitSet(PITCH_BIT))
			{
				pitch = new JausShort(data, dataIndex) ;
			}
			dataIndex += pitch.size();
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
			
			if(vector.getPresenceVector().toJausBuffer(buffer, index))
			{
				index += vector.size();
			}
			else
			{
			    return false;				    
			}					    
			if(vector.isBitSet(SPEED_BIT))
			{
				if(speed.toJausBuffer(buffer, index))
				{
					index += speed.size();
				}
				else
				{
			    return false;
				}
			}			
			if(vector.isBitSet(ALTITUDE_BIT))
			{
				if(altitude.toJausBuffer(buffer, index))
				{
					index += altitude.size();
				}
				else
				{
			    return false;
				}
			}			
			if(vector.isBitSet(HEADING_BIT))
			{
				if(heading.toJausBuffer(buffer, index))
				{
					index += heading.size();
				}
				else
				{
			    return false;
				}
			}			
			if(vector.isBitSet(ROLL_BIT))
			{
				if(roll.toJausBuffer(buffer, index))
				{
					index += roll.size();
				}
				else
				{
			    return false;
				}
			}			
			if(vector.isBitSet(PITCH_BIT))
			{
				if(pitch.toJausBuffer(buffer, index))
				{
					index += pitch.size();
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
			
			if(vector.getPresenceVector().toJausBuffer(buffer, index))
			{
				index += vector.size();
			}
			else
			{
			    return false;				    
			}					    
			if(vector.isBitSet(SPEED_BIT))
			{
				if(speed.toJausBuffer(buffer, index))
				{
					index += speed.size();
				}
				else
				{
			    return false;
				}
			}			
			if(vector.isBitSet(ALTITUDE_BIT))
			{
				if(altitude.toJausBuffer(buffer, index))
				{
					index += altitude.size();
				}
				else
				{
			    return false;
				}
			}			
			if(vector.isBitSet(HEADING_BIT))
			{
				if(heading.toJausBuffer(buffer, index))
				{
					index += heading.size();
				}
				else
				{
			    return false;
				}
			}			
			if(vector.isBitSet(ROLL_BIT))
			{
				if(roll.toJausBuffer(buffer, index))
				{
					index += roll.size();
				}
				else
				{
			    return false;
				}
			}			
			if(vector.isBitSet(PITCH_BIT))
			{
				if(pitch.toJausBuffer(buffer, index))
				{
					index += pitch.size();
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