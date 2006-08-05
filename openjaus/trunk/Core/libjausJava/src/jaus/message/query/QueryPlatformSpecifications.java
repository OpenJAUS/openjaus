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
//File Name: QueryPlatformSpecifications.java
//
// Written By: Danny Kent (jaus@dannykent.com)
//
// Version: 3.2  
//
// Date: 07/04/06
//

package jaus.message.query;
import jaus.message.*;
import jaus.type.JausUnsignedInteger;

public class QueryPlatformSpecifications extends JausMessage
{    
	private static final int COMMAND_CODE = QUERY_PLATFORM_SPECIFICATIONS;
	private static final int MAX_DATA_SIZE_BYTES = 4;
	
	public static final int MOBILITY_PLATFORM_NAME_BIT = 0;
	public static final int FRONT_BIT = 1;
	public static final int BACK_BIT = 2;
	public static final int RIGHT_BIT = 3;
	public static final int LEFT_BIT = 4;
	public static final int TOP_BIT = 5;
	public static final int BOTTOM_BIT = 6;
	public static final int X_CG_BIT = 7;
	public static final int Y_CG_BIT = 8;
	public static final int Z_CG_BIT = 9;
	public static final int TURNING_RADIUS_BIT = 10;
	public static final int WHEEL_BASE_BIT = 11;
	public static final int TRACK_WIDTH_BIT = 12;
	public static final int STATIC_PITCH_OVER_BIT = 13;
	public static final int STATIC_ROLL_OVER_BIT = 14;
	public static final int MAX_VELOCITY_X_BIT = 15;
	public static final int MAX_VELOCITY_Y_BIT = 16;
	public static final int MAX_VELOCITY_Z_BIT = 17;
	public static final int MAX_ROLL_RATE_BIT = 18;
	public static final int MAX_PITCH_RATE_BIT = 19;
	public static final int MAX_YAW_RATE_BIT = 20;
	
    //Message Fields
	JausIntegerPresenceVector vector;
		
	public QueryPlatformSpecifications()
	{
		super();
		vector = new JausIntegerPresenceVector(); 
	}
	
	public QueryPlatformSpecifications(byte[] buffer)
	{
		super(buffer, 0);
	}
	
	public QueryPlatformSpecifications(byte[] buffer, int index)
	{
	    super(buffer, index);
	}

	public QueryPlatformSpecifications(JausMessage jausMessage)
	{
	    super(jausMessage);
	    vector = new JausIntegerPresenceVector(data);
	}
	
	public boolean setPresenceVectorBit(int bit)
	{
		return vector.setBit(bit);
	}
	
	public boolean clearPresenceVectorBit(int bit)
	{
		return vector.clearBit(bit);
	}
	
	public JausUnsignedInteger getPresenceVector()
	{
		return vector.getPresenceVector();
	}
	
	// Takes a data UDP or regular JAUS buffer and unpacks it into the header data structure and the data attributes
	public boolean setFromJausBuffer(byte[] buffer, int index)
	{
		if(super.setFromJausBuffer(buffer, index))
		{
			vector.setPresenceVector(new JausUnsignedInteger(data));
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