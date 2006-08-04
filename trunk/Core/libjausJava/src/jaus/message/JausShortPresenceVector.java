// File Name: JausShortPresenceVector.java
//
// Written By: 	Bob Touchton (btouch@comcast.net)
//				Danny Kent (jaus@dannykent.com)
//
// Version: 3.2
//
// Date: 07/04/06
//
// This file defines the JAUS Presence Vector class and its associated methods.  
// JausPresenceVector is to be nested with JAUS message classes that contain a Presence
// Vector field and is used to test for the presence of absence of a field of interest
//
// A JAUS Presence Vector can be a byte, an unsigned short or an unsigned integer.
// 

package jaus.message;
import jaus.type.*;

public class JausShortPresenceVector
{
	private JausUnsignedShort presenceVector;

	public JausShortPresenceVector()
	{
		presenceVector = new JausUnsignedShort();
	}

	public JausShortPresenceVector(byte[] byteArray)
	{
		presenceVector = new JausUnsignedShort(byteArray);
	}

	public JausShortPresenceVector(byte[] byteArray, int index)
	{
		presenceVector = new JausUnsignedShort(byteArray, index);
	}

	public boolean isBitSet(int bit)
	{
		return((presenceVector.getValue() & (0x01 << bit)) > 0);
	}
	
	public boolean setBit(int bit)
	{
		if(presenceVector.size()*8 < bit)
			return false;
		else
		{
			presenceVector.setValue(presenceVector.getValue() | (0x01 << bit));
			return true;
		}
	}
	
	public boolean clearBit(int bit)
	{
		if(presenceVector.size()*8 < bit) // 8 bits per byte
			return false;
		else
		{
			presenceVector.setValue(presenceVector.getValue() & ~(0x01 << bit));
			return true;
		}	
	}
	
	public JausUnsignedShort getPresenceVector()
	{
		return presenceVector;
	}
	
	public void setPresenceVector(JausUnsignedShort value)
	{
		presenceVector = value;
	}

	public int size()
	{
		return presenceVector.size();
	}
}
