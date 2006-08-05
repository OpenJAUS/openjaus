/*****************************************************************************
 *  Copyright (c) 2006, University of Florida.
 *  All rights reserved.
 *  
 *  This file is part of OpenJAUS.  OpenJAUS is distributed under the BSD 
 *  license.  See the LICENSE file for details.
 * 
 *  Redistribution and use in source and binary forms, with or without 
 *  modification, are permitted provided that the following conditions 
 *  are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer in the documentation and/or other materials provided
 *       with the distribution.
 *     * Neither the name of the University of Florida nor the names of its 
 *       contributors may be used to endorse or promote products derived from 
 *       this software without specific prior written permission.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
 *   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
 *   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR 
 *   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
 *   OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, 
 *   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY 
 *   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 ****************************************************************************/
//File Name: SetLocalWaypointMessage.java
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

public class SetLocalWaypointMessage extends JausMessage
{
	private static final int COMMAND_CODE = SET_LOCAL_WAYPOINT;
	private static final int MAX_DATA_SIZE_BYTES = 21;

	public static final int Z_BIT = 0;
	public static final int ROLL_BIT = 1;
	public static final int PITCH_BIT = 2;
	public static final int YAW_BIT = 3;
	
	//Message Fields
	JausBytePresenceVector vector;
	JausUnsignedShort waypointNumber; 
	JausInteger X; //scaled int
	JausInteger Y; //scaled int
	JausInteger Z; //scaled int
	JausShort roll; //scaled int
	JausShort pitch; //scaled int
	JausShort yaw; //scaled int
	
	public SetLocalWaypointMessage()
	{
		super();
		data = new byte[MAX_DATA_SIZE_BYTES];
		vector = new JausBytePresenceVector();
		waypointNumber = new JausUnsignedShort((short)0);
		X = new JausInteger(0);
		Y = new JausInteger(0);
		Z = new JausInteger(0);
		roll = new JausShort((short)0);
		pitch = new JausShort((short)0);
		yaw = new JausShort((short)0);
	}
	
	public SetLocalWaypointMessage(byte[] buffer)
	{
	    setFromJausBuffer(buffer, 0);
	}
	
	public SetLocalWaypointMessage(byte[] buffer, int index)
	{
	    setFromJausBuffer(buffer, index);
	}

	public SetLocalWaypointMessage(JausMessage jausMessage)
	{
	    super(jausMessage);
		int dataIndex = 0;
		vector = new JausBytePresenceVector(data, dataIndex) ;
		dataIndex += vector.size();
		waypointNumber = new JausUnsignedShort(data, dataIndex) ;
		dataIndex += waypointNumber.size();
		X = new JausInteger(data, dataIndex) ;
		dataIndex += X.size();
		Y = new JausInteger(data, dataIndex) ;
		dataIndex += Y.size();
		if (vector.isBitSet(Z_BIT))
		{
			Z = new JausInteger(data, dataIndex) ;
		}
		dataIndex += Z.size();
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
		if (vector.isBitSet(YAW_BIT))
		{
			yaw = new JausShort(data, dataIndex) ;
		}
		dataIndex += yaw.size();
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
	
	public boolean setWaypointNumber(int value)
	{
		if(value < JausUnsignedShort.MAX_VALUE + 1 && value > JausUnsignedShort.MIN_VALUE - 1)
		{
			waypointNumber.setValue(value);
			return true;
		}
		else
			return false;			
	}
	public boolean setLatitude(double value)
	{
		if(value < JausInteger.MAX_VALUE + 1 && value > JausInteger.MIN_VALUE - 1)
		{
			X.setFromDouble(value, -100000.0,100000.0);
			return true;
		}
		else
			return false;			
	}
	public boolean setLongitude(double value)
	{
		if(value < JausInteger.MAX_VALUE + 1 && value > JausInteger.MIN_VALUE - 1)
		{
			Y.setFromDouble(value, -100000.0,100000.0);
			return true;
		}
		else
			return false;			
	}
	public boolean setElevation(double value)
	{
		if(value < JausInteger.MAX_VALUE + 1 && value > JausInteger.MIN_VALUE - 1)
		{
			Z.setFromDouble(value, -10000.0,35000.0);
			return true;
		}
		else
			return false;			
	}
	public boolean setYaw(double value)
	{
		if(value < JausShort.MAX_VALUE + 1 && value > JausShort.MIN_VALUE - 1)
		{
			yaw.setFromDouble(value, -Math.PI,Math.PI);
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
	public int getWaypointNumber() 
	{
		return waypointNumber.getValue();
	}
	public double getLatitude()
	{
		return X.scaleToDouble(-100000.0,100000.0);
	}
	public double getLongitude()
	{
		return Y.scaleToDouble(-100000.0,100000.0);
	}
	public double getElevation()
	{
		return Z.scaleToDouble(-10000.0,35000.0);
	}
	public double getYaw()
	{
		return yaw.scaleToDouble(-Math.PI,Math.PI);
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
			waypointNumber = new JausUnsignedShort(data, dataIndex) ;
			dataIndex += waypointNumber.size();
			X = new JausInteger(data, dataIndex) ;
			dataIndex += X.size();
			Y = new JausInteger(data, dataIndex) ;
			dataIndex += Y.size();
			if (vector.isBitSet(Z_BIT))
			{
				Z = new JausInteger(data, dataIndex) ;
			}
			dataIndex += Z.size();
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
			if (vector.isBitSet(YAW_BIT))
			{
				yaw = new JausShort(data, dataIndex) ;
			}
			dataIndex += yaw.size();
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
			if(waypointNumber.toJausBuffer(buffer, index))
			{
				index += waypointNumber.size();
			}
			else
			{
		    return false;
			}
			if(X.toJausBuffer(buffer, index))
			{
				index += X.size();
			}
			else
			{
		    return false;
			}
			if(Y.toJausBuffer(buffer, index))
			{
				index += Y.size();
			}
			else
			{
		    return false;
			}
			if(vector.isBitSet(Z_BIT))
			{
				if(Z.toJausBuffer(buffer, index))
				{
					index += Z.size();
				}
				else
				{
			    return false;
				}
			}			
			if(vector.isBitSet(YAW_BIT))
			{
				if(yaw.toJausBuffer(buffer, index))
				{
					index += yaw.size();
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
			if(waypointNumber.toJausBuffer(buffer, index))
			{
				index += waypointNumber.size();
			}
			else
			{
		    return false;
			}
			if(X.toJausBuffer(buffer, index))
			{
				index += X.size();
			}
			else
			{
		    return false;
			}
			if(Y.toJausBuffer(buffer, index))
			{
				index += Y.size();
			}
			else
			{
		    return false;
			}
			if(vector.isBitSet(Z_BIT))
			{
				if(Z.toJausBuffer(buffer, index))
				{
					index += Z.size();
				}
				else
				{
			    return false;
				}
			}			
			if(vector.isBitSet(YAW_BIT))
			{
				if(yaw.toJausBuffer(buffer, index))
				{
					index += yaw.size();
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