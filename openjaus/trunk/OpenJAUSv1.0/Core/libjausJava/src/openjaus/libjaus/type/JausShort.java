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
// File Name: JausShort.java
//
// Written By: Danny Kent (jaus@dannykent.com)
//
// Version: 3.2
//
// Date: 07/04/06
//
// This file contains the Jaus Short data type and its associated methods. 
// JausShort is used to convert between the JAVA short primitive and the JAUS defined type
//
// A Jaus Short is defined as a 16 bit signed integer

package openjaus.libjaus.type;

public class JausShort
{
	private static final double RANGE = 65534.0; // NOTE: This range is incorrect, but is as defined by Jaus
	public static final short MAX_VALUE = 32767;
	public static final short MIN_VALUE = -32768;
	
	public static final int SIZE_BYTES = 2;
	private short value;

	public JausShort()
	{
		value = 0;
	}

	public JausShort(short value)
	{
		this.value = value;
	}

	public JausShort(byte[] byteArray)
	{
		value = fromJausBuffer(byteArray, 0);
	}
	
	public JausShort(byte[] byteArray, int index)
	{
		value = fromJausBuffer(byteArray, index);
	}

	public short getValue()
	{
		return value;
	}
	
	public void setValue(short value)
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
		return 	setFromJausBuffer(byteArray, 0);
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
		
		double scaleFactor = (max-min)/RANGE;
		double bias = (max+min)/2.0; 
	    
		return value*scaleFactor + bias;
	}

	// Takes the input double and the scale range and stores the coresponding scaled integer in value
	// This is to support Jaus Scaled Integers
	// Integer_Value = Round((Real_Value � Bias)/Scale_Factor)
	public void setFromDouble(double value, double min, double max)
	{
		//BUG: What to do when max < min
		double scaleFactor = (max-min)/RANGE;
		double bias = (max+min)/2.0;
		
		// limit real number between min and max
		if(value < min) value = min;
		if(value > max) value = max;
				
		// calculate rounded integer value
		this.value = (short) Math.round((value - bias)/scaleFactor);
	}
	
	public static boolean toJausBuffer(short value, byte[] byteArray)
	{
		return toJausBuffer(value, byteArray, 0);
	}
	
	public static boolean toJausBuffer(short value, byte[] byteArray, int index)
	{
		if(byteArray.length < index + SIZE_BYTES)
			return false; //not enough size
		
		for(int i=0; i < SIZE_BYTES; i++)
		{
			byteArray[index+i] = (byte) ((value >>> i*8) & 0xFF); // 8 bits per byte
		}
		return true;
	}

	public static short fromJausBuffer(byte[] byteArray)
	{
		return fromJausBuffer(byteArray, 0);
	}
	
	public static short fromJausBuffer(byte[] byteArray, int index)
	{
		short tempValue = 0;
		int arrayUpperBounds = byteArray.length-index;
		
		// NOTE: Should not get an input array not equal in size to a Integer
		//       If this occurs, the higher order bytes will be left as zeros 
		for(int i = 0; i < SIZE_BYTES && i < arrayUpperBounds; i++)
		{
			tempValue += ((byteArray[index+i] & 0xFF) << i*8); // 8 bits per byte
		}
		
		return tempValue;
	}
	
	public String toHexString()
	{
		String temp = "";
		temp = Integer.toHexString(value).toUpperCase();
		for(int i=temp.length(); i < (SIZE_BYTES*2); i++)
		{
			temp = "0"+temp;
		}
		return temp;
	}
	
	public String toString()
	{
		return Short.toString(this.value);
	}
}
