//File Name: SetGlobalPathSegmentMessage.java
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

public class SetGlobalPathSegmentMessage extends JausMessage
{
	private static final int COMMAND_CODE = SET_GLOBAL_PATH_SEGMENT;
	private static final int MAX_DATA_SIZE_BYTES = 29;

	public static final int POINT_1_ELEVATION_BIT = 0;
	public static final int POINT_2_ELEVATION_BIT = 1;
	
	//Message Fields
	JausBytePresenceVector vector;
	JausUnsignedShort pathSegmentNumber; 
	JausInteger point1Latitude; //scaled int
	JausInteger point1Longitude; //scaled int
	JausInteger point1Elevation; //scaled int
	JausInteger point2Latitude; //scaled int
	JausInteger point2Longitude; //scaled int
	JausInteger point2Elevation; //scaled int
	JausUnsignedShort weightingFactor;
	
	public SetGlobalPathSegmentMessage()
	{
		super();
		data = new byte[MAX_DATA_SIZE_BYTES];
		vector = new JausBytePresenceVector();
		pathSegmentNumber = new JausUnsignedShort((short)0);
		point1Latitude = new JausInteger(0);
		point1Longitude = new JausInteger(0);
		point1Elevation = new JausInteger(0);
		point2Latitude = new JausInteger(0);
		point2Longitude = new JausInteger(0);
		point2Elevation = new JausInteger(0);
		weightingFactor = new JausUnsignedShort((short)0);		
	}
	
	public SetGlobalPathSegmentMessage(byte[] buffer)
	{
	    setFromJausBuffer(buffer, 0);
	}
	
	public SetGlobalPathSegmentMessage(byte[] buffer, int index)
	{
	    setFromJausBuffer(buffer, index);
	}

	public SetGlobalPathSegmentMessage(JausMessage jausMessage)
	{
	    super(jausMessage);
		int dataIndex = 0;
		vector = new JausBytePresenceVector(data, dataIndex) ;
		dataIndex += vector.size();
		pathSegmentNumber = new JausUnsignedShort(data, dataIndex) ;
		dataIndex += pathSegmentNumber.size();
		point1Latitude = new JausInteger(data, dataIndex) ;
		dataIndex += point1Latitude.size();
		point1Longitude = new JausInteger(data, dataIndex) ;
		dataIndex += point1Longitude.size();
		if (vector.isBitSet(POINT_1_ELEVATION_BIT))
		{
			point1Elevation = new JausInteger(data, dataIndex) ;
		}
		dataIndex += point1Elevation.size();
		point2Latitude = new JausInteger(data, dataIndex) ;
		dataIndex += point2Latitude.size();
		point2Longitude = new JausInteger(data, dataIndex) ;
		dataIndex += point2Longitude.size();
		if (vector.isBitSet(POINT_2_ELEVATION_BIT))
		{
			point2Elevation = new JausInteger(data, dataIndex) ;
		}
		dataIndex += point2Elevation.size();
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
			point1Latitude.setFromDouble(value, -90.0,90.0);
			return true;
		}
		else
			return false;			
	}
	public boolean setPoint1Longitude(double value)
	{
		if(value < JausInteger.MAX_VALUE + 1 && value > JausInteger.MIN_VALUE - 1)
		{
			point1Longitude.setFromDouble(value, -180.0,180.0);
			return true;
		}
		else
			return false;			
	}
	public boolean setPoint1Elevation(double value)
	{
		if(value < JausInteger.MAX_VALUE + 1 && value > JausInteger.MIN_VALUE - 1)
		{
			point1Elevation.setFromDouble(value, -10000.0,35000.0);
			return true;
		}
		else
			return false;			
	}
	public boolean setPoint2Latitude(double value)
	{
		if(value < JausInteger.MAX_VALUE + 1 && value > JausInteger.MIN_VALUE - 1)
		{
			point2Latitude.setFromDouble(value, -90.0,90.0);
			return true;
		}
		else
			return false;			
	}
	public boolean setPoint2Longitude(double value)
	{
		if(value < JausInteger.MAX_VALUE + 1 && value > JausInteger.MIN_VALUE - 1)
		{
			point2Longitude.setFromDouble(value, -180.0,180.0);
			return true;
		}
		else
			return false;			
	}
	public boolean setPoint2Elevation(double value)
	{
		if(value < JausInteger.MAX_VALUE + 1 && value > JausInteger.MIN_VALUE - 1)
		{
			point2Elevation.setFromDouble(value, -10000.0,35000.0);
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
		return point1Latitude.scaleToDouble(-90.0,90.0);
	}
	public double getPoint1Longitude()
	{
		return point1Longitude.scaleToDouble(-180.0,180.0);
	}
	public double getPoint1Elevation()
	{
		return point1Elevation.scaleToDouble(-10000.0,35000.0);
	}
	public double getPoint2Latitude()
	{
		return point2Latitude.scaleToDouble(-90.0,90.0);
	}
	public double getPoint2Longitude()
	{
		return point2Longitude.scaleToDouble(-180.0,180.0);
	}
	public double getPoint2Elevation()
	{
		return point2Elevation.scaleToDouble(-10000.0,35000.0);
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
			point1Latitude = new JausInteger(data, dataIndex) ;
			dataIndex += point1Latitude.size();
			point1Longitude = new JausInteger(data, dataIndex) ;
			dataIndex += point1Longitude.size();
			if (vector.isBitSet(POINT_1_ELEVATION_BIT))
			{
				point1Elevation = new JausInteger(data, dataIndex) ;
			}
			dataIndex += point1Elevation.size();
			point2Latitude = new JausInteger(data, dataIndex) ;
			dataIndex += point2Latitude.size();
			point2Longitude = new JausInteger(data, dataIndex) ;
			dataIndex += point2Longitude.size();
			if (vector.isBitSet(POINT_2_ELEVATION_BIT))
			{
				point2Elevation = new JausInteger(data, dataIndex) ;
			}
			dataIndex += point2Elevation.size();
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
			if(point1Latitude.toJausBuffer(buffer, index))
			{
				index += point1Latitude.size();
			}
			else
			{
		    return false;
			}
			if(point1Longitude.toJausBuffer(buffer, index))
			{
				index += point1Longitude.size();
			}
			else
			{
		    return false;
			}
			if(vector.isBitSet(POINT_1_ELEVATION_BIT))
			{
				if(point1Elevation.toJausBuffer(buffer, index))
				{
					index += point1Elevation.size();
				}
				else
				{
			    return false;
				}
			}			
			if(point2Latitude.toJausBuffer(buffer, index))
			{
				index += point2Latitude.size();
			}
			else
			{
		    return false;
			}
			if(point2Longitude.toJausBuffer(buffer, index))
			{
				index += point2Longitude.size();
			}
			else
			{
		    return false;
			}
			if(vector.isBitSet(POINT_2_ELEVATION_BIT))
			{
				if(point2Elevation.toJausBuffer(buffer, index))
				{
					index += point2Elevation.size();
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
			if(point1Latitude.toJausBuffer(buffer, index))
			{
				index += point1Latitude.size();
			}
			else
			{
		    return false;
			}
			if(point1Longitude.toJausBuffer(buffer, index))
			{
				index += point1Longitude.size();
			}
			else
			{
		    return false;
			}
			if(vector.isBitSet(POINT_1_ELEVATION_BIT))
			{
				if(point1Elevation.toJausBuffer(buffer, index))
				{
					index += point1Elevation.size();
				}
				else
				{
			    return false;
				}
			}			
			if(point2Latitude.toJausBuffer(buffer, index))
			{
				index += point2Latitude.size();
			}
			else
			{
		    return false;
			}
			if(point2Longitude.toJausBuffer(buffer, index))
			{
				index += point2Longitude.size();
			}
			else
			{
		    return false;
			}
			if(vector.isBitSet(POINT_2_ELEVATION_BIT))
			{
				if(point2Elevation.toJausBuffer(buffer, index))
				{
					index += point2Elevation.size();
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