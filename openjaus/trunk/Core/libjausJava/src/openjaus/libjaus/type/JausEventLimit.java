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
//File Name: JausEventLimit.java
//
// Written By: Tom Galluzzo
//
// Version: 3.2
//
// Date: 07/04/06
//
package openjaus.libjaus.type;

public class JausEventLimit
{	
	private static final int UNDEFINED_TYPE			= -1;
	private static final int BYTE_TYPE				= 0;
	private static final int SHORT_TYPE				= 1;
	private static final int INTEGER_TYPE			= 2;
	private static final int LONG_TYPE				= 3;
	private static final int UNSIGNED_SHORT_TYPE	= 4;
	private static final int UNSIGNED_INTEGER_TYPE	= 5;
	private static final int UNSIGNED_LONG_TYPE		= 6;
	private static final int FLOAT_TYPE				= 7;
	private static final int DOUBLE_TYPE			= 8;
	private static final int RGB_TYPE				= 9;
	
	private JausByte byteValue;
	private JausShort shortValue;
	private JausInteger integerValue;
	private JausLong longValue;
	private JausUnsignedShort unsignedShortValue;
	private JausUnsignedInteger unsignedIntegerValue;
	private JausFloat floatValue;
	private JausDouble doubleValue;
	
	private int dataType;
	
	public JausEventLimit()
	{
		dataType = -1;
	}

	public JausEventLimit(byte[] byteArray, int dataType)
	{
		setFromJausBuffer(byteArray, 0, dataType);
	}	
	
	public JausEventLimit(byte[] byteArray, int index, int dataType)
	{
		setFromJausBuffer(byteArray, index, dataType);
	}
	
	public boolean setDataType(int dataType)
	{
		if(dataType > -1 && dataType < 9)
		{
			this.dataType = dataType;
			
			switch(dataType)
			{
				case BYTE_TYPE:
					byteValue = new JausByte();
					break;
					
				case SHORT_TYPE:
					shortValue = new JausShort();
					break;
					
				case INTEGER_TYPE:
					integerValue = new JausInteger();
					break;
									
				case LONG_TYPE:
					longValue = new JausLong();
					break;
					
				case UNSIGNED_SHORT_TYPE:
					unsignedShortValue = new JausUnsignedShort();
					break;
					
				case UNSIGNED_INTEGER_TYPE:
					unsignedIntegerValue = new JausUnsignedInteger();
					break;
					
				case FLOAT_TYPE:
					floatValue = new JausFloat();
					break;
					
				case DOUBLE_TYPE:
					doubleValue = new JausDouble();
					break;
					
				default:
					return false;
			}
			
			return true;
		}
		else
		{
			return false;
		}
	}

	public int getDataType()
	{
		return dataType;
	}

	public JausByte getByteValue()
	{
		return byteValue;
	}
	
	public JausShort getShortValue()
	{
		return shortValue;
	}
	
	public JausInteger getIntegerValue()
	{
		return integerValue;
	}
	
	public JausLong getLongValue()
	{
		return longValue;
	}
	
	public JausUnsignedShort getUnsignedShortValue()
	{
		return unsignedShortValue;
	}
	
	public JausUnsignedInteger getUnsignedIntegerValue()
	{
		return unsignedIntegerValue;
	}
	
	public JausFloat getFloatValue()
	{
		return floatValue;
	}
	
	public JausDouble getDoubleValue()
	{
		return doubleValue;
	}	

	public int size()
	{
		switch(dataType)
		{
			case BYTE_TYPE:
				return byteValue.size();
				
			case SHORT_TYPE:
				return shortValue.size();
				
			case INTEGER_TYPE:
				return integerValue.size();
								
			case LONG_TYPE:
				return longValue.size();
				
			case UNSIGNED_SHORT_TYPE:
				return unsignedShortValue.size();
				
			case UNSIGNED_INTEGER_TYPE:
				return unsignedIntegerValue.size();
				
			case FLOAT_TYPE:
				return floatValue.size();
				
			case DOUBLE_TYPE:
				return doubleValue.size();
				
			default:
				return 0;
		}
	}
	
	public boolean toJausBuffer(byte[] byteArray)
	{
		return toJausBuffer(this, byteArray, 0);
	}
	
	public boolean toJausBuffer(byte[] byteArray, int index)
	{
		return toJausBuffer(this, byteArray, index);
	}		
	
	public static boolean toJausBuffer(JausEventLimit limit, byte[] byteArray)
	{
		return toJausBuffer(limit, byteArray, 0);
	}
	
	public static boolean toJausBuffer(JausEventLimit limit, byte[] byteArray, int index)
	{
		switch(limit.getDataType())
		{
			case BYTE_TYPE:
				return limit.getByteValue().toJausBuffer(byteArray, index);
				
			case SHORT_TYPE:
				return limit.getShortValue().toJausBuffer(byteArray, index);
				
			case INTEGER_TYPE:
				return limit.getIntegerValue().toJausBuffer(byteArray, index);
								
			case LONG_TYPE:
				return limit.getLongValue().toJausBuffer(byteArray,index);
				
			case UNSIGNED_SHORT_TYPE:
				return limit.getUnsignedShortValue().toJausBuffer(byteArray,index);
				
			case UNSIGNED_INTEGER_TYPE:
				return limit.getUnsignedIntegerValue().toJausBuffer(byteArray,index);
				
			case FLOAT_TYPE:
				return limit.getFloatValue().toJausBuffer(byteArray,index);
				
			case DOUBLE_TYPE:
				return limit.getDoubleValue().toJausBuffer(byteArray,index);
				
			default:
				return false;
		}
	}

	public boolean setFromJausBuffer(byte[] byteArray, int dataType)
	{
		return setFromJausBuffer(byteArray, 0, dataType);
	}

	public boolean setFromJausBuffer(byte[] byteArray, int index, int dataType)
	{
		if(setDataType(dataType))
		{
			switch(dataType)
			{
				case BYTE_TYPE:
					return byteValue.setFromJausBuffer(byteArray, index);
					
				case SHORT_TYPE:
					return shortValue.setFromJausBuffer(byteArray, index);
					
				case INTEGER_TYPE:
					return integerValue.setFromJausBuffer(byteArray, index);
									
				case LONG_TYPE:
					return longValue.setFromJausBuffer(byteArray,index);
					
				case UNSIGNED_SHORT_TYPE:
					return unsignedShortValue.setFromJausBuffer(byteArray,index);
					
				case UNSIGNED_INTEGER_TYPE:
					return unsignedIntegerValue.setFromJausBuffer(byteArray,index);
					
				case FLOAT_TYPE:
					return floatValue.setFromJausBuffer(byteArray,index);
					
				case DOUBLE_TYPE:
					return doubleValue.setFromJausBuffer(byteArray,index);
					
				default:
					return false;
			}
		
		}
		else
		{
			return false;
		}
	}
	
	public static JausEventLimit fromJausBuffer(byte[] byteArray, int dataType)
	{
		return fromJausBuffer(byteArray, 0, dataType);
	}
	
	public static JausEventLimit fromJausBuffer(byte[] byteArray, int index, int dataType)
	{
		JausEventLimit limit = new JausEventLimit();
		
		if(limit.setFromJausBuffer(byteArray, index, dataType))
		{
			return limit;
		}
		else
		{
			return null;
		}
	}

	public String toHexString()
	{
		switch(dataType)
		{
			case BYTE_TYPE:
				return byteValue.toHexString();
				
			case SHORT_TYPE:
				return shortValue.toHexString();
				
			case INTEGER_TYPE:
				return integerValue.toHexString();
								
			case LONG_TYPE:
				return longValue.toHexString();
				
			case UNSIGNED_SHORT_TYPE:
				return unsignedShortValue.toHexString();
				
			case UNSIGNED_INTEGER_TYPE:
				return unsignedIntegerValue.toHexString();
				
			case FLOAT_TYPE:
				return floatValue.toHexString();
				
			case DOUBLE_TYPE:
				return doubleValue.toHexString();
				
			default:
				return null;
		}
	}
		
	public String toString()
	{
		switch(dataType)
		{
			case BYTE_TYPE:
				return byteValue.toString();
				
			case SHORT_TYPE:
				return shortValue.toString();
				
			case INTEGER_TYPE:
				return integerValue.toString();
								
			case LONG_TYPE:
				return longValue.toString();
				
			case UNSIGNED_SHORT_TYPE:
				return unsignedShortValue.toString();
				
			case UNSIGNED_INTEGER_TYPE:
				return unsignedIntegerValue.toString();
				
			case FLOAT_TYPE:
				return floatValue.toString();
				
			case DOUBLE_TYPE:
				return doubleValue.toString();
				
			default:
				return null;
		}
	}
}
