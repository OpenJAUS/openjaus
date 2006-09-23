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
//File Name: SetDiscreteDevicesMessage.java
//
// Written By: Bob Touchton (btouch@comcast.net)
//
// Version: 3.2  
//
// Date: 07/04/06
//

package openjaus.libjaus.message.command;
import openjaus.libjaus.message.*;
import openjaus.libjaus.type.*;

public class SetDiscreteDevicesMessage extends JausMessage
{
	private static final int COMMAND_CODE = SET_DISCRETE_DEVICES;
	private static final int MAX_DATA_SIZE_BYTES = 5;

	public static final int MAIN_PROPULSION_BIT = 0;
	public static final int PARKING_BRAKE_HORN_BIT = 1;
	public static final int GEAR_BIT = 2;
	public static final int TRANSFER_CASE_BIT = 3;

	//Message Fields
	JausBytePresenceVector vector;
	JausByte mainPropulsion; //TODO: implement bit-wise interpretation
	JausByte parkingBrakeHorn; //TODO: implement bit-wise interpretation
	JausByte gear; //TODO: implement bit-wise interpretation
	JausByte transferCase; //TODO: implement bit-wise interpretation
	
	public SetDiscreteDevicesMessage()
	{
		super();
		data = new byte[MAX_DATA_SIZE_BYTES];
		vector = new JausBytePresenceVector();
		mainPropulsion = new JausByte(0);
		parkingBrakeHorn = new JausByte(0);
		gear = new JausByte(0);
		transferCase = new JausByte(0);
	}
	
	public SetDiscreteDevicesMessage(byte[] buffer)
	{
	    setFromJausBuffer(buffer, 0);
	}
	
	public SetDiscreteDevicesMessage(byte[] buffer, int index)
	{
	    setFromJausBuffer(buffer, index);
	}

	public SetDiscreteDevicesMessage(JausMessage jausMessage)
	{
	    super(jausMessage);
		int dataIndex = 0;
		vector = new JausBytePresenceVector(data, dataIndex) ;
		dataIndex += vector.size();
		if (vector.isBitSet(MAIN_PROPULSION_BIT))
		{
			mainPropulsion = new JausByte(data, dataIndex) ;
		}
		dataIndex += mainPropulsion.size();
		if (vector.isBitSet(PARKING_BRAKE_HORN_BIT))
		{
			parkingBrakeHorn = new JausByte(data, dataIndex) ;
		}
		dataIndex += parkingBrakeHorn.size();
		if (vector.isBitSet(GEAR_BIT))
		{
			gear = new JausByte(data, dataIndex) ;
		}
		dataIndex += gear.size();
		if (vector.isBitSet(TRANSFER_CASE_BIT))
		{
			transferCase = new JausByte(data, dataIndex) ;
		}
		dataIndex += transferCase.size();
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
	
	public boolean setMainPropulsion(int value)
	{
		if(value < JausByte.MAX_VALUE + 1 && value > JausByte.MIN_VALUE - 1)
		{
			mainPropulsion.setValue(value);
			return true;
		}
		else
			return false;			
	}
	public boolean setParkingBrakeHorn(int value)
	{
		if(value < JausByte.MAX_VALUE + 1 && value > JausByte.MIN_VALUE - 1)
		{
			parkingBrakeHorn.setValue(value);
			return true;
		}
		else
			return false;			
	}
	public boolean setGear(int value)
	{
		if(value < JausByte.MAX_VALUE + 1 && value > JausByte.MIN_VALUE - 1)
		{
			gear.setValue(value);
			return true;
		}
		else
			return false;			
	}
	public boolean setTransferCase(int value)
	{
		if(value < JausByte.MAX_VALUE + 1 && value > JausByte.MIN_VALUE - 1)
		{
			transferCase.setValue(value);
			return true;
		}
		else
			return false;			
	}
	
	public JausByte getPresenceVector()
	{
		return vector.getPresenceVector();
	}	
	public int getMainPropulsion()
	{
		return mainPropulsion.getValue();
	}
	public int getParkingBrakeHorn()
	{
		return parkingBrakeHorn.getValue();
	}
	public int getGear()
	{
		return gear.getValue();
	}
	public int getTransferCase()
	{
		return transferCase.getValue();
	}
	
	// Takes a data UDP or regular JAUS buffer and unpacks it into the header data structure and the data attributes
	public boolean setFromJausBuffer(byte[] buffer, int index)
	{
		if(super.setFromJausBuffer(buffer, index))
		{
			int dataIndex = 0;
			vector = new JausBytePresenceVector(data, dataIndex) ;
			dataIndex += vector.size();
			if (vector.isBitSet(MAIN_PROPULSION_BIT))
			{
				mainPropulsion = new JausByte(data, dataIndex) ;
			}
			dataIndex += mainPropulsion.size();
			if (vector.isBitSet(PARKING_BRAKE_HORN_BIT))
			{
				parkingBrakeHorn = new JausByte(data, dataIndex) ;
			}
			dataIndex += parkingBrakeHorn.size();
			if (vector.isBitSet(GEAR_BIT))
			{
				gear = new JausByte(data, dataIndex) ;
			}
			dataIndex += gear.size();
			if (vector.isBitSet(TRANSFER_CASE_BIT))
			{
				transferCase = new JausByte(data, dataIndex) ;
			}
			dataIndex += transferCase.size();
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
			if(vector.isBitSet(MAIN_PROPULSION_BIT))
			{
				if(mainPropulsion.toJausBuffer(buffer, index))
				{
					index += mainPropulsion.size();
				}
				else
				{
			    return false;
				}
			}			
			if(vector.isBitSet(PARKING_BRAKE_HORN_BIT))
			{
				if(parkingBrakeHorn.toJausBuffer(buffer, index))
				{
					index += parkingBrakeHorn.size();
				}
				else
				{
			    return false;
				}
			}			
			if(vector.isBitSet(GEAR_BIT))
			{
				if(gear.toJausBuffer(buffer, index))
				{
					index += gear.size();
				}
				else
				{
			    return false;
				}
			}			
			if(vector.isBitSet(TRANSFER_CASE_BIT))
			{
				if(transferCase.toJausBuffer(buffer, index))
				{
					index += transferCase.size();
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
			if(vector.isBitSet(MAIN_PROPULSION_BIT))
			{
				if(mainPropulsion.toJausBuffer(buffer, index))
				{
					index += mainPropulsion.size();
				}
				else
				{
			    return false;
				}
			}			
			if(vector.isBitSet(PARKING_BRAKE_HORN_BIT))
			{
				if(parkingBrakeHorn.toJausBuffer(buffer, index))
				{
					index += parkingBrakeHorn.size();
				}
				else
				{
			    return false;
				}
			}			
			if(vector.isBitSet(GEAR_BIT))
			{
				if(gear.toJausBuffer(buffer, index))
				{
					index += gear.size();
				}
				else
				{
			    return false;
				}
			}			
			if(vector.isBitSet(TRANSFER_CASE_BIT))
			{
				if(transferCase.toJausBuffer(buffer, index))
				{
					index += transferCase.size();
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