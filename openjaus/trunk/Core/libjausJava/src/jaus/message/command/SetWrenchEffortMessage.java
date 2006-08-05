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
//File Name: SetWrenchMessage.java
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

public class SetWrenchEffortMessage extends JausMessage
{
	private static final int COMMAND_CODE = SET_WRENCH_EFFORT;
	private static final int MAX_DATA_SIZE_BYTES = 20;

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
	JausShort propulsiveLinearEffortX; //scaled int
	JausShort propulsiveLinearEffortY; //scaled int
	JausShort propulsiveLinearEffortZ; //scaled int
	JausShort propulsiveRotationalEffortX; //scaled int
	JausShort propulsiveRotationalEffortY; //scaled int
	JausShort propulsiveRotationalEffortZ; //scaled int
	JausByte resistiveLinearEffortX; //scaled int
	JausByte resistiveLinearEffortY; //scaled int
	JausByte resistiveLinearEffortZ; //scaled int
	JausByte resistiveRotationalEffortX; //scaled int
	JausByte resistiveRotationalEffortY; //scaled int
	JausByte resistiveRotationalEffortZ; //scaled int
	
	public SetWrenchEffortMessage()
	{
		super();
		data = new byte[MAX_DATA_SIZE_BYTES];
		vector = new JausShortPresenceVector();
		propulsiveLinearEffortX = new JausShort((short)0);
		propulsiveLinearEffortY = new JausShort((short)0);
		propulsiveLinearEffortZ = new JausShort((short)0);
		propulsiveRotationalEffortX = new JausShort((short)0);
		propulsiveRotationalEffortY = new JausShort((short)0);
		propulsiveRotationalEffortZ = new JausShort((short)0);
		resistiveLinearEffortX = new JausByte(0);
		resistiveLinearEffortY = new JausByte(0);
		resistiveLinearEffortZ = new JausByte(0);
		resistiveRotationalEffortX = new JausByte(0);
		resistiveRotationalEffortY = new JausByte(0);
		resistiveRotationalEffortZ = new JausByte(0);
	}
	
	public SetWrenchEffortMessage(byte[] buffer)
	{
	    setFromJausBuffer(buffer, 0);
	}
	
	public SetWrenchEffortMessage(byte[] buffer, int index)
	{
	    setFromJausBuffer(buffer, index);
	}

	public SetWrenchEffortMessage(JausMessage jausMessage)
	{
	    super(jausMessage);
		int dataIndex = 0;
		vector = new JausShortPresenceVector(data, dataIndex) ;
		dataIndex += vector.size();
		if (vector.isBitSet(PROPULSIVE_LINEAR_EFFORT_X_BIT))
		{
			propulsiveLinearEffortX = new JausShort(data, dataIndex) ;
		}
		dataIndex += propulsiveLinearEffortX.size();
		if (vector.isBitSet(PROPULSIVE_LINEAR_EFFORT_Y_BIT))
		{
			propulsiveLinearEffortY = new JausShort(data, dataIndex) ;
		}
		dataIndex += propulsiveLinearEffortY.size();
		if (vector.isBitSet(PROPULSIVE_LINEAR_EFFORT_Z_BIT))
		{
			propulsiveLinearEffortZ = new JausShort(data, dataIndex) ;
		}
		dataIndex += propulsiveLinearEffortZ.size();
		if (vector.isBitSet(PROPULSIVE_ROTATIONAL_EFFORT_X_BIT))
		{
			propulsiveRotationalEffortX = new JausShort(data, dataIndex) ;
		}
		dataIndex += propulsiveRotationalEffortX.size();
		if (vector.isBitSet(PROPULSIVE_ROTATIONAL_EFFORT_Y_BIT))
		{
			propulsiveRotationalEffortY = new JausShort(data, dataIndex) ;
		}
		dataIndex += propulsiveRotationalEffortY.size();
		if (vector.isBitSet(PROPULSIVE_ROTATIONAL_EFFORT_Z_BIT))
		{
			propulsiveRotationalEffortZ = new JausShort(data, dataIndex) ;
		}
		dataIndex += propulsiveRotationalEffortZ.size();
		if (vector.isBitSet(RESISTIVE_LINEAR_EFFORT_X_BIT))
		{
			resistiveLinearEffortX = new JausByte(data, dataIndex) ;
		}
		dataIndex += resistiveLinearEffortX.size();
		if (vector.isBitSet(RESISTIVE_LINEAR_EFFORT_Y_BIT))
		{
			resistiveLinearEffortY = new JausByte(data, dataIndex) ;
		}
		dataIndex += resistiveLinearEffortY.size();
		if (vector.isBitSet(RESISTIVE_LINEAR_EFFORT_Z_BIT))
		{
			resistiveLinearEffortZ = new JausByte(data, dataIndex) ;
		}
		dataIndex += resistiveLinearEffortZ.size();
		if (vector.isBitSet(RESISTIVE_ROTATIONAL_EFFORT_X_BIT))
		{
			resistiveRotationalEffortX = new JausByte(data, dataIndex) ;
		}
		dataIndex += resistiveRotationalEffortX.size();
		if (vector.isBitSet(RESISTIVE_ROTATIONAL_EFFORT_Y_BIT))
		{
			resistiveRotationalEffortY = new JausByte(data, dataIndex) ;
		}
		dataIndex += resistiveRotationalEffortY.size();
		if (vector.isBitSet(RESISTIVE_ROTATIONAL_EFFORT_Z_BIT))
		{
			resistiveRotationalEffortZ = new JausByte(data, dataIndex) ;
		}
		dataIndex += resistiveRotationalEffortZ.size();
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
	
	public boolean setPropulsiveLinearEffortX(double value)
	{
		if(value < JausShort.MAX_VALUE + 1 && value > JausShort.MIN_VALUE - 1)
		{
			propulsiveLinearEffortX.setFromDouble(value, -100.0,100.0);
			return true;
		}
		else
			return false;			
	}
	public boolean setPropulsiveLinearEffortY(double value)
	{
		if(value < JausShort.MAX_VALUE + 1 && value > JausShort.MIN_VALUE - 1)
		{
			propulsiveLinearEffortY.setFromDouble(value, -100.0,100.0);
			return true;
		}
		else
			return false;			
	}
	public boolean setPropulsiveLinearEffortZ(double value)
	{
		if(value < JausShort.MAX_VALUE + 1 && value > JausShort.MIN_VALUE - 1)
		{
			propulsiveLinearEffortZ.setFromDouble(value, -100.0,100.0);
			return true;
		}
		else
			return false;			
	}
	public boolean setPropulsiveRotationalEffortX(double value)
	{
		if(value < JausShort.MAX_VALUE + 1 && value > JausShort.MIN_VALUE - 1)
		{
			propulsiveRotationalEffortX.setFromDouble(value, -100.0,100.0);
			return true;
		}
		else
			return false;			
	}
	public boolean setPropulsiveRotationalEffortY(double value)
	{
		if(value < JausShort.MAX_VALUE + 1 && value > JausShort.MIN_VALUE - 1)
		{
			propulsiveRotationalEffortY.setFromDouble(value, -100.0,100.0);
			return true;
		}
		else
			return false;			
	}
	public boolean setPropulsiveRotationalEffortZ(double value)
	{
		if(value < JausShort.MAX_VALUE + 1 && value > JausShort.MIN_VALUE - 1)
		{
			propulsiveRotationalEffortZ.setFromDouble(value, -100.0,100.0);
			return true;
		}
		else
			return false;			
	}
	public boolean setResistiveLinearEffortX(double value)
	{
		if(value < JausByte.MAX_VALUE + 1 && value > JausByte.MIN_VALUE - 1)
		{
			resistiveLinearEffortX.setFromDouble(value, 0.0,100.0);
			return true;
		}
		else
			return false;			
	}
	public boolean setResistiveLinearEffortY(double value)
	{
		if(value < JausByte.MAX_VALUE + 1 && value > JausByte.MIN_VALUE - 1)
		{
			resistiveLinearEffortY.setFromDouble(value, 0.0,100.0);
			return true;
		}
		else
			return false;			
	}
	public boolean setResistiveLinearEffortZ(double value)
	{
		if(value < JausByte.MAX_VALUE + 1 && value > JausByte.MIN_VALUE - 1)
		{
			resistiveLinearEffortZ.setFromDouble(value, 0.0,100.0);
			return true;
		}
		else
			return false;			
	}
	public boolean setResistiveRotationalEffortX(double value)
	{
		if(value < JausByte.MAX_VALUE + 1 && value > JausByte.MIN_VALUE - 1)
		{
			resistiveRotationalEffortX.setFromDouble(value, 0.0,100.0);
			return true;
		}
		else
			return false;			
	}
	public boolean setResistiveRotationalEffortY(double value)
	{
		if(value < JausByte.MAX_VALUE + 1 && value > JausByte.MIN_VALUE - 1)
		{
			resistiveRotationalEffortY.setFromDouble(value, 0.0,100.0);
			return true;
		}
		else
			return false;			
	}
	public boolean setResistiveRotationalEffortZ(double value)
	{
		if(value < JausByte.MAX_VALUE + 1 && value > JausByte.MIN_VALUE - 1)
		{
			resistiveRotationalEffortZ.setFromDouble(value, 0.0,100.0);
			return true;
		}
		else
			return false;			
	}
	
	public JausUnsignedShort getPresenceVector()
	{
		return vector.getPresenceVector();
	}	
	public double getPropulsiveLinearEffortX()
	{
		return propulsiveLinearEffortX.scaleToDouble(-100.0, 100.0);
	}
	public double getPropulsiveLinearEffortY()
	{
		return propulsiveLinearEffortY.scaleToDouble(-100.0, 100.0);
	}
	public double getPropulsiveLinearEffortZ()
	{
		return propulsiveLinearEffortZ.scaleToDouble(-100.0, 100.0);
	}
	public double getPropulsiveRotationalEffortX()
	{
		return propulsiveRotationalEffortX.scaleToDouble(-100.0, 100.0);
	}
	public double getPropulsiveRotationalEffortY()
	{
		return propulsiveRotationalEffortY.scaleToDouble(-100.0, 100.0);
	}
	public double getPropulsiveRotationalEffortZ()
	{
		return propulsiveRotationalEffortZ.scaleToDouble(-100.0, 100.0);
	}
	public double getResistiveLinearEffortX()
	{
		return resistiveLinearEffortX.scaleToDouble(0.0, 100.0);
	}
	public double getResistiveLinearEffortY()
	{
		return resistiveLinearEffortY.scaleToDouble(0.0, 100.0);
	}
	public double getResistiveLinearEffortZ()
	{
		return resistiveLinearEffortZ.scaleToDouble(0.0, 100.0);
	}
	public double getResistiveRotationalEffortX()
	{
		return resistiveRotationalEffortX.scaleToDouble(0.0, 100.0);
	}
	public double getResistiveRotationalEffortY()
	{
		return resistiveRotationalEffortY.scaleToDouble(0.0, 100.0);
	}
	public double getResistiveRotationalEffortZ()
	{
		return resistiveRotationalEffortZ.scaleToDouble(0.0, 100.0);
	}
	
	// Takes a data UDP or regular JAUS buffer and unpacks it into the header data structure and the data attributes
	public boolean setFromJausBuffer(byte[] buffer, int index)
	{
		if(super.setFromJausBuffer(buffer, index))
		{
			int dataIndex = 0;
			vector = new JausShortPresenceVector(data, dataIndex) ;
			dataIndex += vector.size();
			if (vector.isBitSet(PROPULSIVE_LINEAR_EFFORT_X_BIT))
			{
				propulsiveLinearEffortX = new JausShort(data, dataIndex) ;
			}
			dataIndex += propulsiveLinearEffortX.size();
			if (vector.isBitSet(PROPULSIVE_LINEAR_EFFORT_Y_BIT))
			{
				propulsiveLinearEffortY = new JausShort(data, dataIndex) ;
			}
			dataIndex += propulsiveLinearEffortY.size();
			if (vector.isBitSet(PROPULSIVE_LINEAR_EFFORT_Z_BIT))
			{
				propulsiveLinearEffortZ = new JausShort(data, dataIndex) ;
			}
			dataIndex += propulsiveLinearEffortZ.size();
			if (vector.isBitSet(PROPULSIVE_ROTATIONAL_EFFORT_X_BIT))
			{
				propulsiveRotationalEffortX = new JausShort(data, dataIndex) ;
			}
			dataIndex += propulsiveRotationalEffortX.size();
			if (vector.isBitSet(PROPULSIVE_ROTATIONAL_EFFORT_Y_BIT))
			{
				propulsiveRotationalEffortY = new JausShort(data, dataIndex) ;
			}
			dataIndex += propulsiveRotationalEffortY.size();
			if (vector.isBitSet(PROPULSIVE_ROTATIONAL_EFFORT_Z_BIT))
			{
				propulsiveRotationalEffortZ = new JausShort(data, dataIndex) ;
			}
			dataIndex += propulsiveRotationalEffortZ.size();
			if (vector.isBitSet(RESISTIVE_LINEAR_EFFORT_X_BIT))
			{
				resistiveLinearEffortX = new JausByte(data, dataIndex) ;
			}
			dataIndex += resistiveLinearEffortX.size();
			if (vector.isBitSet(RESISTIVE_LINEAR_EFFORT_Y_BIT))
			{
				resistiveLinearEffortY = new JausByte(data, dataIndex) ;
			}
			dataIndex += resistiveLinearEffortY.size();
			if (vector.isBitSet(RESISTIVE_LINEAR_EFFORT_Z_BIT))
			{
				resistiveLinearEffortZ = new JausByte(data, dataIndex) ;
			}
			dataIndex += resistiveLinearEffortZ.size();
			if (vector.isBitSet(RESISTIVE_ROTATIONAL_EFFORT_X_BIT))
			{
				resistiveRotationalEffortX = new JausByte(data, dataIndex) ;
			}
			dataIndex += resistiveRotationalEffortX.size();
			if (vector.isBitSet(RESISTIVE_ROTATIONAL_EFFORT_Y_BIT))
			{
				resistiveRotationalEffortY = new JausByte(data, dataIndex) ;
			}
			dataIndex += resistiveRotationalEffortY.size();
			if (vector.isBitSet(RESISTIVE_ROTATIONAL_EFFORT_Z_BIT))
			{
				resistiveRotationalEffortZ = new JausByte(data, dataIndex) ;
			}
			dataIndex += resistiveRotationalEffortZ.size();
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
			if(vector.isBitSet(PROPULSIVE_LINEAR_EFFORT_X_BIT))
			{
				if(propulsiveLinearEffortX.toJausBuffer(buffer, index))
				{
					index += propulsiveLinearEffortX.size();
				}
				else
				{
			    return false;
				}
			}			
			if(vector.isBitSet(PROPULSIVE_LINEAR_EFFORT_Y_BIT))
			{
				if(propulsiveLinearEffortY.toJausBuffer(buffer, index))
				{
					index += propulsiveLinearEffortY.size();
				}
				else
				{
			    return false;
				}
			}			
			if(vector.isBitSet(PROPULSIVE_LINEAR_EFFORT_Z_BIT))
			{
				if(propulsiveLinearEffortZ.toJausBuffer(buffer, index))
				{
					index += propulsiveLinearEffortZ.size();
				}
				else
				{
			    return false;
				}
			}			
			if(vector.isBitSet(PROPULSIVE_ROTATIONAL_EFFORT_X_BIT))
			{
				if(propulsiveRotationalEffortX.toJausBuffer(buffer, index))
				{
					index += propulsiveRotationalEffortX.size();
				}
				else
				{
			    return false;
				}
			}			
			if(vector.isBitSet(PROPULSIVE_ROTATIONAL_EFFORT_Y_BIT))
			{
				if(propulsiveRotationalEffortY.toJausBuffer(buffer, index))
				{
					index += propulsiveRotationalEffortY.size();
				}
				else
				{
			    return false;
				}
			}			
			if(vector.isBitSet(PROPULSIVE_ROTATIONAL_EFFORT_Z_BIT))
			{
				if(propulsiveRotationalEffortZ.toJausBuffer(buffer, index))
				{
					index += propulsiveRotationalEffortZ.size();
				}
				else
				{
			    return false;
				}
			}			
			if(vector.isBitSet(RESISTIVE_LINEAR_EFFORT_X_BIT))
			{
				if(resistiveLinearEffortX.toJausBuffer(buffer, index))
				{
					index += resistiveLinearEffortX.size();
				}
				else
				{
			    return false;
				}
			}			
			if(vector.isBitSet(RESISTIVE_LINEAR_EFFORT_Y_BIT))
			{
				if(resistiveLinearEffortY.toJausBuffer(buffer, index))
				{
					index += resistiveLinearEffortY.size();
				}
				else
				{
			    return false;
				}
			}			
			if(vector.isBitSet(RESISTIVE_LINEAR_EFFORT_Z_BIT))
			{
				if(resistiveLinearEffortZ.toJausBuffer(buffer, index))
				{
					index += resistiveLinearEffortZ.size();
				}
				else
				{
			    return false;
				}
			}			
			if(vector.isBitSet(RESISTIVE_ROTATIONAL_EFFORT_X_BIT))
			{
				if(resistiveRotationalEffortX.toJausBuffer(buffer, index))
				{
					index += resistiveRotationalEffortX.size();
				}
				else
				{
			    return false;
				}
			}			
			if(vector.isBitSet(RESISTIVE_ROTATIONAL_EFFORT_Y_BIT))
			{
				if(resistiveRotationalEffortY.toJausBuffer(buffer, index))
				{
					index += resistiveRotationalEffortY.size();
				}
				else
				{
			    return false;
				}
			}			
			if(vector.isBitSet(RESISTIVE_ROTATIONAL_EFFORT_Z_BIT))
			{
				if(resistiveRotationalEffortZ.toJausBuffer(buffer, index))
				{
					index += resistiveRotationalEffortZ.size();
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
			if(vector.isBitSet(PROPULSIVE_LINEAR_EFFORT_X_BIT))
			{
				if(propulsiveLinearEffortX.toJausBuffer(buffer, index))
				{
					index += propulsiveLinearEffortX.size();
				}
				else
				{
			    return false;
				}
			}			
			if(vector.isBitSet(PROPULSIVE_LINEAR_EFFORT_Y_BIT))
			{
				if(propulsiveLinearEffortY.toJausBuffer(buffer, index))
				{
					index += propulsiveLinearEffortY.size();
				}
				else
				{
			    return false;
				}
			}			
			if(vector.isBitSet(PROPULSIVE_LINEAR_EFFORT_Z_BIT))
			{
				if(propulsiveLinearEffortZ.toJausBuffer(buffer, index))
				{
					index += propulsiveLinearEffortZ.size();
				}
				else
				{
			    return false;
				}
			}			
			if(vector.isBitSet(PROPULSIVE_ROTATIONAL_EFFORT_X_BIT))
			{
				if(propulsiveRotationalEffortX.toJausBuffer(buffer, index))
				{
					index += propulsiveRotationalEffortX.size();
				}
				else
				{
			    return false;
				}
			}			
			if(vector.isBitSet(PROPULSIVE_ROTATIONAL_EFFORT_Y_BIT))
			{
				if(propulsiveRotationalEffortY.toJausBuffer(buffer, index))
				{
					index += propulsiveRotationalEffortY.size();
				}
				else
				{
			    return false;
				}
			}			
			if(vector.isBitSet(PROPULSIVE_ROTATIONAL_EFFORT_Z_BIT))
			{
				if(propulsiveRotationalEffortZ.toJausBuffer(buffer, index))
				{
					index += propulsiveRotationalEffortZ.size();
				}
				else
				{
			    return false;
				}
			}			
			if(vector.isBitSet(RESISTIVE_LINEAR_EFFORT_X_BIT))
			{
				if(resistiveLinearEffortX.toJausBuffer(buffer, index))
				{
					index += resistiveLinearEffortX.size();
				}
				else
				{
			    return false;
				}
			}			
			if(vector.isBitSet(RESISTIVE_LINEAR_EFFORT_Y_BIT))
			{
				if(resistiveLinearEffortY.toJausBuffer(buffer, index))
				{
					index += resistiveLinearEffortY.size();
				}
				else
				{
			    return false;
				}
			}			
			if(vector.isBitSet(RESISTIVE_LINEAR_EFFORT_Z_BIT))
			{
				if(resistiveLinearEffortZ.toJausBuffer(buffer, index))
				{
					index += resistiveLinearEffortZ.size();
				}
				else
				{
			    return false;
				}
			}			
			if(vector.isBitSet(RESISTIVE_ROTATIONAL_EFFORT_X_BIT))
			{
				if(resistiveRotationalEffortX.toJausBuffer(buffer, index))
				{
					index += resistiveRotationalEffortX.size();
				}
				else
				{
			    return false;
				}
			}			
			if(vector.isBitSet(RESISTIVE_ROTATIONAL_EFFORT_Y_BIT))
			{
				if(resistiveRotationalEffortY.toJausBuffer(buffer, index))
				{
					index += resistiveRotationalEffortY.size();
				}
				else
				{
			    return false;
				}
			}			
			if(vector.isBitSet(RESISTIVE_ROTATIONAL_EFFORT_Z_BIT))
			{
				if(resistiveRotationalEffortZ.toJausBuffer(buffer, index))
				{
					index += resistiveRotationalEffortZ.size();
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