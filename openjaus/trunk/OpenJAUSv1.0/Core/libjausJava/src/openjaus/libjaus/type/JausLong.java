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
//File Name: JausLong.java
//
// Written By: Danny Kent (jaus@dannykent.com)
//
// Version: 3.2
//
// Date: 07/04/06
//
// This file contains the Jaus Long data type and its associated methods. 
// JausLong is used to convert between the JAVA long primitive and the JAUS defined type
// 
//A Jaus Long is defined as a 64 bit signed integer

package openjaus.libjaus.type;

public class JausLong
{
	private static final double RANGE = 18446744073709551614.0; // NOTE: This range is incorrect, but is as defined by Jaus
	public static final long MAX_VALUE = 9223372036854775807L;
	public static final long MIN_VALUE = -9223372036854775807L;
	public static final int SIZE_BYTES = 8;
	private long value;

	public JausLong()
	{
		value = 0;
	}

	public JausLong(long value)
	{
		this.value = value;
	}

	public JausLong(byte[] byteArray)
	{
		value = fromJausBuffer(byteArray, 0);
	}
	
	public JausLong(byte[] byteArray, int index)
	{
		value = fromJausBuffer(byteArray, index);
	}

	public long getValue()
	{
		return value;
	}

	public void setValue(long value)
	{
		this.value = value;
	}
	
	public boolean toJausBuffer(byte[] byteArray)
	{
		return toJausBuffer(this.value, byteArray, 0);
	}
	
	public boolean toJausBuffer(byte[] byteArray, int index)
	{
		return toJausBuffer(this.value, byteArray, index);
	}

	public boolean setFromJausBuffer(byte[] byteArray)
	{
		return setFromJausBuffer(byteArray, 0);
	}
	
	public boolean setFromJausBuffer(byte[] byteArray, int index)
	{
		if(byteArray.length - index < SIZE_BYTES)
			return false;
		else
		{
			value = fromJausBuffer(byteArray, index);
			return true;
		}
	}	
		
	public int size()
	{
		return SIZE_BYTES;
	}

	// Takes the input double and the scale range and stores the coresponding scaled integer in value
	// This is to support Jaus Scaled Integers
	// Real_Value = Integer_Value*Scale_Factor + Bias
	public double scaleToDouble(double min, double max)
	{
		//BUG: What to do when max < min
		//limit value between min and max Integer values
		if(value > MAX_VALUE) value = MAX_VALUE;
		if(value < MIN_VALUE) value = MIN_VALUE;
		
		double scaleFactor = (max-min)/RANGE; //NOTE: Possible Bug with Range
		double bias = (max+min)/2.0; 
	    
		return value*scaleFactor + bias;
	}
	
	// Takes the value inside the object and returns it as a double in the range
	// This is to support Jaus Scaled Integers
	// Integer_Value = Round((Real_Value - Bias)/Scale_Factor)
	public void setFromDouble(double value, double min, double max)
	{
		//BUG: What to do when max < min
		double scaleFactor = (max-min)/RANGE; //NOTE: Possible Bug with Range
		double bias = (max+min)/2.0;
		
		// limit real number between min and max
		if(value < min) value = min;
		if(value > max) value = max;
		
		
		// calculate rounded integer value
		this.value = (long) Math.round((value - bias)/scaleFactor);
	}
	
	public static boolean toJausBuffer(long value, byte[] byteArray)
	{
		return toJausBuffer(value, byteArray, 0);
	}
	
	public static boolean toJausBuffer(long value, byte[] byteArray, int index)
	{
		if(byteArray.length < index + SIZE_BYTES)
			return false; //not enough size
		
		for(int i=0; i < SIZE_BYTES; i++)
		{
			byteArray[index+i] = (byte) ((value >>> i*8) & 0xFF); // 8 bits per byte
		}
		return true;
	}

	public static long fromJausBuffer(byte[] byteArray)
	{
		return fromJausBuffer(byteArray, 0);
	}
	
	public static long fromJausBuffer(byte[] byteArray, int index)
	{
		long tempValue = 0;
		int arrayUpperBounds = byteArray.length-index;
		
		for(int i = 0; i < SIZE_BYTES && i < arrayUpperBounds; i++)
		{
			tempValue += ((byteArray[index+i] & 0xFF) << i*8); // 8 bits per byte
		}
		
		return tempValue;
	}

	public String toString()
	{
		return Long.toString(this.value);
	}
	
	public String toHexString()
	{
		String temp = "";
		temp = Long.toHexString(value).toUpperCase();
		for(int i=temp.length(); i < (SIZE_BYTES*2); i++)
		{
			temp = "0"+temp;
		}
		return temp;
	}
	
}
