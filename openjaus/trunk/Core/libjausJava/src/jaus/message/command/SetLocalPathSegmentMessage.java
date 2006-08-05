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
//File Name: SetLocalPathSegmentMessage.java
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

public class SetLocalPathSegmentMessage extends JausMessage
{
	private static final int COMMAND_CODE = SET_LOCAL_PATH_SEGMENT;
	private static final int MAX_DATA_SIZE_BYTES = 29;

	public static final int POINT_1_ELEVATION_BIT = 0;
	public static final int POINT_2_ELEVATION_BIT = 1;
	
	//Message Fields
	JausBytePresenceVector vector;
	JausUnsignedShort pathSegmentNumber; 
	JausInteger point1X; //scaled int
	JausInteger point1Y; //scaled int
	JausInteger point1Z; //scaled int
	JausInteger point2X; //scaled int
	JausInteger point2Y; //scaled int
	JausInteger point2Z; //scaled int
	JausUnsignedShort weightingFactor;
	
	public SetLocalPathSegmentMessage()
	{
		super();
		data = new byte[MAX_DATA_SIZE_BYTES];
		vector = new JausBytePresenceVector();
		pathSegmentNumber = new JausUnsignedShort((short)0);
		point1X = new JausInteger(0);
		point1Y = new JausInteger(0);
		point1Z = new JausInteger(0);
		point2X = new JausInteger(0);
		point2Y = new JausInteger(0);
		point2Z = new JausInteger(0);
		weightingFactor = new JausUnsignedShort((short)0);		
	}
	
	public SetLocalPathSegmentMessage(byte[] buffer)
	{
	    setFromJausBuffer(buffer, 0);
	}
	
	public SetLocalPathSegmentMessage(byte[] buffer, int index)
	{
	    setFromJausBuffer(buffer, index);
	}

	public SetLocalPathSegmentMessage(JausMessage jausMessage)
	{
	    super(jausMessage);
		int dataIndex = 0;
		vector = new JausBytePresenceVector(data, dataIndex) ;
		dataIndex += vector.size();
		pathSegmentNumber = new JausUnsignedShort(data, dataIndex) ;
		dataIndex += pathSegmentNumber.size();
		point1X = new JausInteger(data, dataIndex) ;
		dataIndex += point1X.size();
		point1Y = new JausInteger(data, dataIndex) ;
		dataIndex += point1Y.size();
		if (vector.isBitSet(POINT_1_ELEVATION_BIT))
		{
			point1Z = new JausInteger(data, dataIndex) ;
		}
		dataIndex += point1Z.size();
		point2X = new JausInteger(data, dataIndex) ;
		dataIndex += point2X.size();
		point2Y = new JausInteger(data, dataIndex) ;
		dataIndex += point2Y.size();
		if (vector.isBitSet(POINT_2_ELEVATION_BIT))
		{
			point2Z = new JausInteger(data, dataIndex) ;
		}
		dataIndex += point2Z.size();
		weightingFactor = new JausUnsignedShort(data, dataIndex) ;
		dataIndex += weightingFactor.size();		
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
			pathSegmentNumber.setValue(value);
			return true;
		}
		else
			return false;			
	}
	public boolean setPoint1Latitude(double value)
	{
		if(value < JausInteger.MAX_VALUE + 1 && value > JausInteger.MIN_VALUE - 1)
		{
			point1X.setFromDouble(value, -100000.0,100000.0);
			return true;
		}
		else
			return false;			
	}
	public boolean setPoint1Longitude(double value)
	{
		if(value < JausInteger.MAX_VALUE + 1 && value > JausInteger.MIN_VALUE - 1)
		{
			point1Y.setFromDouble(value, -100000.0,100000.0);
			return true;
		}
		else
			return false;			
	}
	public boolean setPoint1Elevation(double value)
	{
		if(value < JausInteger.MAX_VALUE + 1 && value > JausInteger.MIN_VALUE - 1)
		{
			point1Z.setFromDouble(value, -10000.0,35000.0);
			return true;
		}
		else
			return false;			
	}
	public boolean setPoint2Latitude(double value)
	{
		if(value < JausInteger.MAX_VALUE + 1 && value > JausInteger.MIN_VALUE - 1)
		{
			point2X.setFromDouble(value, -100000.0,100000.0);
			return true;
		}
		else
			return false;			
	}
	public boolean setPoint2Longitude(double value)
	{
		if(value < JausInteger.MAX_VALUE + 1 && value > JausInteger.MIN_VALUE - 1)
		{
			point2Y.setFromDouble(value, -100000.0,100000.0);
			return true;
		}
		else
			return false;			
	}
	public boolean setPoint2Elevation(double value)
	{
		if(value < JausInteger.MAX_VALUE + 1 && value > JausInteger.MIN_VALUE - 1)
		{
			point2Z.setFromDouble(value, -10000.0,35000.0);
			return true;
		}
		else
			return false;			
	}
	public boolean setWeightingFactor(int value)
	{
		if(value < JausUnsignedShort.MAX_VALUE + 1 && value > JausUnsignedShort.MIN_VALUE - 1)
		{
			weightingFactor.setValue(value);
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
		return pathSegmentNumber.getValue();
	}
	public double getPoint1Latitude()
	{
		return point1X.scaleToDouble(-100000.0,100000.0);
	}
	public double getPoint1Longitude()
	{
		return point1Y.scaleToDouble(-100000.0,100000.0);
	}
	public double getPoint1Elevation()
	{
		return point1Z.scaleToDouble(-10000.0,35000.0);
	}
	public double getPoint2Latitude()
	{
		return point2X.scaleToDouble(-100000.0,100000.0);
	}
	public double getPoint2Longitude()
	{
		return point2Y.scaleToDouble(-100000.0,100000.0);
	}
	public double getPoint2Elevation()
	{
		return point2Z.scaleToDouble(-10000.0,35000.0);
	}
	public int getWeightingFactor() 
	{
		return weightingFactor.getValue();	
	}
	
	// Takes a data UDP or regular JAUS buffer and unpacks it into the header data structure and the data attributes
	public boolean setFromJausBuffer(byte[] buffer, int index)
	{
		if(super.setFromJausBuffer(buffer, index))
		{
			int dataIndex = 0;
			vector = new JausBytePresenceVector(data, dataIndex) ;
			dataIndex += vector.size();
			pathSegmentNumber = new JausUnsignedShort(data, dataIndex) ;
			dataIndex += pathSegmentNumber.size();
			point1X = new JausInteger(data, dataIndex) ;
			dataIndex += point1X.size();
			point1Y = new JausInteger(data, dataIndex) ;
			dataIndex += point1Y.size();
			if (vector.isBitSet(POINT_1_ELEVATION_BIT))
			{
				point1Z = new JausInteger(data, dataIndex) ;
			}
			dataIndex += point1Z.size();
			point2X = new JausInteger(data, dataIndex) ;
			dataIndex += point2X.size();
			point2Y = new JausInteger(data, dataIndex) ;
			dataIndex += point2Y.size();
			if (vector.isBitSet(POINT_2_ELEVATION_BIT))
			{
				point2Z = new JausInteger(data, dataIndex) ;
			}
			dataIndex += point2Z.size();
			weightingFactor = new JausUnsignedShort(data, dataIndex) ;
			dataIndex += weightingFactor.size();	
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
			if(pathSegmentNumber.toJausBuffer(buffer, index))
			{
				index += pathSegmentNumber.size();
			}
			else
			{
		    return false;
			}
			if(point1X.toJausBuffer(buffer, index))
			{
				index += point1X.size();
			}
			else
			{
		    return false;
			}
			if(point1Y.toJausBuffer(buffer, index))
			{
				index += point1Y.size();
			}
			else
			{
		    return false;
			}
			if(vector.isBitSet(POINT_1_ELEVATION_BIT))
			{
				if(point1Z.toJausBuffer(buffer, index))
				{
					index += point1Z.size();
				}
				else
				{
			    return false;
				}
			}			
			if(point2X.toJausBuffer(buffer, index))
			{
				index += point2X.size();
			}
			else
			{
		    return false;
			}
			if(point2Y.toJausBuffer(buffer, index))
			{
				index += point2Y.size();
			}
			else
			{
		    return false;
			}
			if(vector.isBitSet(POINT_2_ELEVATION_BIT))
			{
				if(point2Z.toJausBuffer(buffer, index))
				{
					index += point2Z.size();
				}
				else
				{
			    return false;
				}
			}		
			if(weightingFactor.toJausBuffer(buffer, index))
			{
				index += weightingFactor.size();
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
			
			if(vector.getPresenceVector().toJausBuffer(buffer, index))
			{
				index += vector.size();
			}
			else
			{
			    return false;				    
			}					    
			if(pathSegmentNumber.toJausBuffer(buffer, index))
			{
				index += pathSegmentNumber.size();
			}
			else
			{
		    return false;
			}
			if(point1X.toJausBuffer(buffer, index))
			{
				index += point1X.size();
			}
			else
			{
		    return false;
			}
			if(point1Y.toJausBuffer(buffer, index))
			{
				index += point1Y.size();
			}
			else
			{
		    return false;
			}
			if(vector.isBitSet(POINT_1_ELEVATION_BIT))
			{
				if(point1Z.toJausBuffer(buffer, index))
				{
					index += point1Z.size();
				}
				else
				{
			    return false;
				}
			}			
			if(point2X.toJausBuffer(buffer, index))
			{
				index += point2X.size();
			}
			else
			{
		    return false;
			}
			if(point2Y.toJausBuffer(buffer, index))
			{
				index += point2Y.size();
			}
			else
			{
		    return false;
			}
			if(vector.isBitSet(POINT_2_ELEVATION_BIT))
			{
				if(point2Z.toJausBuffer(buffer, index))
				{
					index += point2Z.size();
				}
				else
				{
			    return false;
				}
			}		
			if(weightingFactor.toJausBuffer(buffer, index))
			{
				index += weightingFactor.size();
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