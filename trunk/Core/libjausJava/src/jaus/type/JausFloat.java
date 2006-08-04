//File Name: JausFloat.java
//
// Written By: Danny Kent (jaus@dannykent.com)
//
// Version: 3.2
//
// Date: 07/04/06
//
// This file contains the Jaus Float data type and its associated methods. 
// JausFloat is used to convert between the JAVA float primitive and the JAUS defined type
//
// A Jaus Float is defined as a IEEE 32 bit floating point number

package jaus.type;

public class JausFloat
{
	public static final int SIZE_BYTES = 4;
	private float value;

	public JausFloat()
	{
		value = 0;
	}

	public JausFloat(float value)
	{
		this.value = value;
	}

	public JausFloat(byte[] byteArray)
	{
		value = fromJausBuffer(byteArray, 0);
	}
	
	public JausFloat(byte[] byteArray, int index)
	{
		value = fromJausBuffer(byteArray, index);
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
	
	public float getValue()
	{
		return this.value;
	}
	
	public void setValue(float value)
	{
		this.value = value;
	}
	
	public int size()
	{
		return SIZE_BYTES;
	}

	public static float fromJausBuffer(byte[] byteArray)
	{
		return fromJausBuffer(byteArray, 0);
	}
	
	public static float fromJausBuffer(byte[] byteArray, int index)
	{
		int tempValue = 0;
		int arrayUpperBounds = byteArray.length-index;
		
		// NOTE: Should not get an input array not equal in size to a Float
		//       If this occurs, the higher order bytes will be left as zeros 
		for(int i = 0; i < SIZE_BYTES && i < arrayUpperBounds; i++)
		{
			tempValue += ((byteArray[index+i] & 0xFF) << i*8); // 8 bits per byte
		}

		return Float.intBitsToFloat(tempValue);
	}
	
	public static boolean toJausBuffer(float value, byte[] byteArray)
	{
		return toJausBuffer(value, byteArray, 0);
	}
	
	public static boolean toJausBuffer(float value, byte[] byteArray, int index)
	{
		if(byteArray.length < index + SIZE_BYTES)
			return false; //not enough size

		int newValue = Float.floatToIntBits(value); 
		for(int i=0; i < SIZE_BYTES; i++)
		{
			byteArray[index+i] = (byte) ((newValue >>> i*8) & 0xFF); // 8 bits per byte
		}
		return true;
	}

	public String toString()
	{
		return Float.toString(this.value);
	}
	
	public String toHexString()
	{
		int val = Float.floatToIntBits(value);
		String temp = "";
		temp = Integer.toHexString(val).toUpperCase();
		for(int i=temp.length(); i < (SIZE_BYTES*2); i++)
		{
			temp = "0"+temp;
		}
		return temp;
	}
}
