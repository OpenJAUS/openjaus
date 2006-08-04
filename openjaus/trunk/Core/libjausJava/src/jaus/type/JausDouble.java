//File Name: JausDouble.java
//
// Written By: Danny Kent (jaus@dannykent.com)
//
// Version: 3.2
//
// Date: 07/04/06
//
// This file contains the Jaus Double data type and its associated methods. 
// JausDouble is used to convert between the JAVA double primitive and the JAUS defined type
//
// A Jaus Double is defined as a IEEE 32 bit floating point number

package jaus.type;

public class JausDouble
{
	public static final int SIZE_BYTES = 8;
	private double value;

	public JausDouble()
	{
		value = 0;
	}

	public JausDouble(double value)
	{
		this.value = value;
	}

	public JausDouble(byte[] byteArray)
	{
		value = fromJausBuffer(byteArray, 0);
	}
	
	public JausDouble(byte[] byteArray, int index)
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
	
	public double getValue()
	{
		return value;
	}
	
	public void setValue(double value)
	{
		this.value = value;
	}

	public int size()
	{
		return SIZE_BYTES;
	}

	public static double fromJausBuffer(byte[] byteArray)
	{
		return fromJausBuffer(byteArray, 0);
	}
	
	public static double fromJausBuffer(byte[] byteArray, int index)
	{
		long tempValue = 0;
		int arrayUpperBound = byteArray.length-index;
		
		// NOTE: Should not get an input array not equal in size to a Double
		//       If this occurs, the higher order bytes will be left as zeros 
		for(int i = 0; i < SIZE_BYTES && i < arrayUpperBound; i++)
		{
			tempValue += ((byteArray[index+i] & 0xFF) << i*8); // 8 bits per byte
		}
		
		return Double.longBitsToDouble(tempValue);
	}
	
	public static boolean toJausBuffer(double value, byte[] byteArray)
	{
		return toJausBuffer(value, byteArray, 0);
	}
	
	public static boolean toJausBuffer(double value, byte[] byteArray, int index)
	{
		if(byteArray.length < index + SIZE_BYTES)
			return false; //not enough size

		long newValue = Double.doubleToLongBits(value); 
		for(int i=0; i < SIZE_BYTES; i++)
		{
			byteArray[index+i] = (byte) ((newValue >>> i*8) & 0xFF); // 8 bits per byte
		}
		return true;
	}

	public String toString()
	{
		return Double.toString(this.value);
	}
	
	public String toHexString()
	{
		long val = Double.doubleToLongBits(value);
		String temp = "";
		temp = Long.toHexString(val).toUpperCase();
		for(int i=temp.length(); i < (SIZE_BYTES*2); i++)
		{
			temp = "0"+temp;
		}
		return temp;
	}
}
