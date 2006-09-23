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
package openjaus.libjaus.message;

import openjaus.libjaus.JausAddress;

/**
 * 
 * @author Tom Galluzzo & Danny Kent
 * @version 0.1
 *
 * This class will encapsulate all the work we have to do in serializing and deserializing
 * a Jaus Message.  It should also help in creating a new one so that the messages that
 * we have to generate in the Node Manager doesn't take to much work.
 */

// TODO: Need to set Header Properties in sub-classes 

public class JausMessage
{
	// The following are constants defined for the header properties in Jaus 
	public static final String UDP_HEADER = "JAUS01.0";
	public static final int UDP_HEADER_SIZE_BYTES = 8;

	public static final int HEADER_SIZE_BYTES = 16;

	public static final int LOW_PRIORITY =		0;
	public static final int DEFAULT_PRIORITY =	6;
	public static final int HIGH_PRIORITY =		11;
	
	public static final int ACK_NAK_NOT_REQUIRED =	0;
	public static final int ACK_NAK_REQUIRED =		1;
	public static final int NEGATIVE_ACKNOWLEDGE =	2;
	public static final int ACKNOWLEDGE =			3;
	
	public static final int ACK =	ACKNOWLEDGE;
	public static final int NAK =	NEGATIVE_ACKNOWLEDGE;

	public static final boolean SERVICE_CONNECTION_MESSAGE =		true;
	public static final boolean NOT_SERVICE_CONNECTION_MESSAGE =	false;

	public static final boolean EXPERIMENTAL_MESSAGE =		true;
	public static final boolean NOT_EXPERIMENTAL_MESSAGE =	false;

	public static final int VERSION_2_0 =	0;
	public static final int VERSION_2_1 =	0;
	public static final int VERSION_3_0 =	1;
	public static final int VERSION_3_1 =	1;
	public static final int VERSION_3_2 =	2;

	public static final int MAX_DATA_SIZE	=	4080;

	public static final int SINGLE_DATA_PACKET =		0;
	public static final int FIRST_DATA_PACKET =			1;
	public static final int NORMAL_DATA_PACKET =		2;
	public static final int RETRANSMITTED_DATA_PACKET =	4;
	public static final int LAST_DATA_PACKET =			8;

	public static final int MAX_SEQUENCE_NUMBER =	65535;

	public static final int DATA_FLAG_BIT_POSITION = 12;
	public static final int DATA_SIZE_BIT_POSITION = 0;
	
	public static final int VERSION_BIT_POSITION = 8;
	public static final int USER_DEFINED_FLAG_BIT_POSITION = 7;
	public static final int SERVICE_CONNECTION_FLAG_BIT_POSITION = 6;
	public static final int ACK_NAK_BIT_POSITION = 4;
	public static final int PRIORITY_BIT_POSITION = 0;	
	
	// Jaus Command Class Messages
	public static final int SET_COMPONENT_AUTHORITY				= 0x0001;
	public static final int SHUTDOWN							= 0x0002;
	public static final int STANDBY								= 0x0003;
	public static final int RESUME								= 0x0004;
	public static final int RESET								= 0x0005;
	public static final int SET_EMERGENCY						= 0x0006;
	public static final int CLEAR_EMERGENCY						= 0x0007;
	public static final int CREATE_SERVICE_CONNECTION			= 0x0008;
	public static final int CONFIRM_SERVICE_CONNECTION			= 0x0009;
	public static final int ACTIVATE_SERVICE_CONNECTION			= 0x000A;
	public static final int SUSPEND_SERVICE_CONNECTION			= 0x000B;
	public static final int TERMINATE_SERVICE_CONNECTION		= 0x000C;
	public static final int REQUEST_COMPONENT_CONTROL			= 0x000D;
	public static final int RELEASE_COMPONENT_CONTROL			= 0x000E;
	public static final int CONFIRM_COMPONENT_CONTROL			= 0x000F;
	public static final int REJECT_COMPONENT_CONTROL			= 0x0010;
	public static final int SET_TIME							= 0x0011;
	public static final int SET_DATA_LINK_STATUS				= 0x0200;
	public static final int SET_DATA_LINK_SELECT				= 0x0201;
	public static final int SET_WRENCH_EFFORT					= 0x0405;
	public static final int SET_DISCRETE_DEVICES				= 0x0406;
	public static final int SET_GLOBAL_VECTOR					= 0x0407;
	public static final int SET_LOCAL_VECTOR					= 0x0408;
	public static final int SET_TRAVEL_SPEED					= 0x040A;
	public static final int SET_GLOBAL_WAYPOINT					= 0x040C;
	public static final int SET_LOCAL_WAYPOINT					= 0x040D;
	public static final int SET_GLOBAL_PATH_SEGMENT				= 0x040F;
	public static final int SET_LOCAL_PATH_SEGMENT				= 0x0410;
	public static final int SET_JOINT_EFFORTS					= 0x0601;
	public static final int SET_JOINT_POSITIONS					= 0x0602;
	public static final int SET_JOINT_VELOCITIES				= 0x0603;
	public static final int SET_TOOL_POINT						= 0x0604;
	public static final int SET_END_EFFECTOR_POSE				= 0x0605;
	public static final int SET_END_EFFECTOR_VELOCITY_STATE		= 0x0606;
	public static final int SET_JOINT_MOTION					= 0x0607;
	public static final int SET_END_EFFECTOR_PATH_MOTION		= 0x0608;
	public static final int SET_CAMERA_POSE						= 0x0801;
	public static final int SELECT_CAMERA						= 0x0802;
	public static final int SET_CAMERA_CAPABILITIES				= 0x0805;
	public static final int SET_CAMERA_FORMAT_OPTIONS			= 0x0806;

//	 Jaus Query Class Messages
	public static final int QUERY_COMPONENT_AUTHORITY			= 0x2001;
	public static final int QUERY_COMPONENT_STATUS				= 0x2002;
	public static final int QUERY_TIME							= 0x2011;
	public static final int QUERY_DATA_LINK_STATUS				= 0x2200;
	public static final int QUERY_SELECTED_DATA_LINK_STATUS		= 0x2201;
	public static final int QUERY_HEARTBEAT_PULSE				= 0x2202;
	public static final int QUERY_PLATFORM_SPECIFICATIONS		= 0x2400;
	public static final int QUERY_PLATFORM_OPERATIONAL_DATA		= 0x2401;
	public static final int QUERY_GLOBAL_POSE					= 0x2402;
	public static final int QUERY_LOCAL_POSE					= 0x2403;
	public static final int QUERY_VELOCITY_STATE				= 0x2404;
	public static final int QUERY_WRENCH_EFFORT					= 0x2405;
	public static final int QUERY_DISCRETE_DEVICES				= 0x2406;
	public static final int QUERY_GLOBAL_VECTOR					= 0x2407;
	public static final int QUERY_LOCAL_VECTOR					= 0x2408;
	public static final int QUERY_TRAVEL_SPEED					= 0x240A;
	public static final int QUERY_WAYPOINT_COUNT				= 0x240B;
	public static final int QUERY_GLOBAL_WAYPOINT				= 0x240C;
	public static final int QUERY_LOCAL_WAYPOINT				= 0x240D;
	public static final int QUERY_PATH_SEGMENT_COUNT			= 0x240E;
	public static final int QUERY_GLOBAL_PATH_SEGMENT			= 0x240F;
	public static final int QUERY_LOCAL_PATH_SEGMENT			= 0x2410;
	public static final int QUERY_MANIPULATOR_SPECIFICATIONS	= 0x2600;
	public static final int QUERY_JOINT_EFFORTS					= 0x2601;
	public static final int QUERY_JOINT_POSITIONS				= 0x2602;
	public static final int QUERY_JOINT_VELOCITIES				= 0x2603;
	public static final int QUERY_TOOL_POINT					= 0x2604;
	public static final int QUERY_JOINT_FORCE_TORQUES			= 0x2605;
	public static final int QUERY_CAMERA_POSE					= 0x2800;
	public static final int QUERY_CAMERA_COUNT					= 0x2801;
	public static final int QUERY_RELATIVE_OBJECT_POSITION		= 0x2802;
	public static final int QUERY_SELECTED_CAMERA				= 0x2804;
	public static final int QUERY_CAMERA_CAPABILITIES			= 0x2805;
	public static final int QUERY_CAMERA_FORMAT_OPTIONS			= 0x2806;
	public static final int QUERY_IMAGE							= 0x2807;

//	 Jaus Inform Class Messages
	public static final int REPORT_COMPONENT_AUTHORITY			= 0x4001;
	public static final int REPORT_COMPONENT_STATUS				= 0x4002;
	public static final int REPORT_TIME							= 0x4011;
	public static final int REPORT_DATA_LINK_STATUS				= 0x4200;
	public static final int REPORT_SELECTED_DATA_LINK_STATUS	= 0x4201;
	public static final int REPORT_HEARTBEAT_PULSE				= 0x4202;
	public static final int REPORT_PLATFORM_SPECIFICATIONS		= 0x4400;
	public static final int REPORT_PLATFORM_OPERATIONAL_DATA	= 0x4401;
	public static final int REPORT_GLOBAL_POSE					= 0x4402;
	public static final int REPORT_LOCAL_POSE					= 0x4403;
	public static final int REPORT_VELOCITY_STATE				= 0x4404;
	public static final int REPORT_WRENCH_EFFORT				= 0x4405;
	public static final int REPORT_DISCRETE_DEVICES				= 0x4406;
	public static final int REPORT_GLOBAL_VECTOR				= 0x4407;
	public static final int REPORT_LOCAL_VECTOR					= 0x4408;
	public static final int REPORT_TRAVEL_SPEED					= 0x440A;
	public static final int REPORT_WAYPOINT_COUNT				= 0x440B;
	public static final int REPORT_GLOBAL_WAYPOINT				= 0x440C;
	public static final int REPORT_LOCAL_WAYPOINT				= 0x440D;
	public static final int REPORT_PATH_SEGMENT_COUNT			= 0x440E;
	public static final int REPORT_GLOBAL_PATH_SEGMENT			= 0x440F;
	public static final int REPORT_LOCAL_PATH_SEGMENT			= 0x4410;
	public static final int REPORT_MANIPULATOR_SPECIFICATIONS	= 0x4600;
	public static final int REPORT_JOINT_EFFORTS				= 0x4601;
	public static final int REPORT_JOINT_POSITIONS				= 0x4602;
	public static final int REPORT_JOINT_VELOCITIES				= 0x4603;
	public static final int REPORT_TOOL_POINT					= 0x4604;
	public static final int REPORT_JOINT_FORCE_TORQUES			= 0x4605;
	public static final int REPORT_CAMERA_POSE					= 0x4800;
	public static final int REPORT_CAMERA_COUNT					= 0x4801;
	public static final int REPORT_RELATIVE_OBJECT_POSITION		= 0x4802;
	public static final int REPORT_SELECTED_CAMERA				= 0x4804;
	public static final int REPORT_CAMERA_CAPABILITIES			= 0x4805;
	public static final int REPORT_CAMERA_FORMAT_OPTIONS		= 0x4806;
	public static final int REPORT_IMAGE						= 0x4807;

	// JAUS Known Experimental Messages
	public static final int QUERY_IDENTIFICATION 							= 0xD2A4;
	public static final int REPORT_IDENTIFICATION 							= 0xD4A5;
	public static final int QUERY_CONFIGURATION 							= 0xD2A6;
	public static final int REPORT_CONFIGURATION 							= 0xD4A6;
	public static final int CONFIGURATION_CHANGED_EVENT_SETUP 				= 0xD6A8;
	public static final int CONFIGURATION_CHANGED_EVENT_NOTIFICATION 		= 0xD8A8;
	public static final int CREATE_EVENT 									= 0xF0A1;
	public static final int CONFIRM_EVENT 									= 0xF009;
	public static final int QUERY_SERVICES 									= 0xD2A7;
	public static final int REPORT_SERVICES 								= 0xD4A7;
	
	protected static final int FIRST_DATA_BYTE_POSITION = HEADER_SIZE_BYTES;
	
	//JausMessage Properties
	protected int properties;
	protected int commandCode;
	protected JausAddress destination;
	protected JausAddress source;
	protected int dataControl;
	protected int sequenceNumber;
	protected byte[] data;
	
	// Default Constructor
	public JausMessage()
	{
		setPriority(DEFAULT_PRIORITY);
		setAckNak(ACK_NAK_NOT_REQUIRED);
		setServiceConnectionFlag(NOT_SERVICE_CONNECTION_MESSAGE);
		setUserDefinedFlag(NOT_EXPERIMENTAL_MESSAGE);
		setVersion(VERSION_3_2);
		
		setCommandCode(0);
		destination = new JausAddress();
		source = new JausAddress();		

		setDataFlag(SINGLE_DATA_PACKET);
		setDataSize(0);
		
		setSequenceNumber(0);

		data = new byte[0];
	}
	
	// Crates a JausMessage object from the given buffer
	public JausMessage(byte[] buffer, int index)
	{
    	destination = new JausAddress();
		source = new JausAddress();		
		setFromJausBuffer(buffer, index);			

    /*	System.out.print("JausMessage unpacking : " + source + " : " + Integer.toHexString(commandCode) + " : " + buffer.length + " > ");
	    for(int i=0; i<32 && i<data.length; i++)
	    {
	    	System.out.print(" " + (data[i] & 0xFF));
	    }
    	System.out.println();
    */
		
	}
	
	//	Overloaded constructor to accept no index input, assumes 0
	public JausMessage(byte[] buffer)
	{
		this(buffer, 0);
	}

	public JausMessage(JausMessage jausMessage)
	{
	    setProperties(jausMessage.getProperties());
	    setCommandCode(jausMessage.getCommandCode());
	    setDestination(jausMessage.getDestination());
	    setSource(jausMessage.getSource());
	    setDataControl(jausMessage.getDataControl());
	    setSequenceNumber(jausMessage.getSequenceNumber());
	    data = new byte[jausMessage.getData().length];
	    System.arraycopy(jausMessage.getData(), 0, data, 0, data.length);
	}

	public int udpSize()
	{
		//this will be the total number of bytes
		return UDP_HEADER_SIZE_BYTES + HEADER_SIZE_BYTES + data.length;
	}
	
	public int size()
	{
		//this will be the total number of bytes
		//basically the length of the header + Datalength
		return HEADER_SIZE_BYTES + data.length;
	}

	public void setProperties(int properties)
	{
		this.properties = properties;
	}

	public int getProperties()
	{
		return properties;
	}
	
	public int getPriority()
	{
		return (properties >>> PRIORITY_BIT_POSITION) & 0x0F;
	}
	
	public void setPriority(int priority)
	{
		if(priority > -1 && priority < 16)
		{
			properties = (priority << PRIORITY_BIT_POSITION) | (properties & 0xFFFFFFF0);
		}
	}
	
	public int getAckNak()
	{
		return (properties >>> ACK_NAK_BIT_POSITION) & 0x03;
	}
	
	public void setAckNak(int ackNak)
	{
		if(ackNak > -1 && ackNak < 4)
		{
			properties = (ackNak << ACK_NAK_BIT_POSITION) | (properties & 0xFFFFFFCF);
		}
	}

	public boolean getServiceConnectionFlag()
	{
		return (properties & 0x40) > 0;
	}
	
	public void setServiceConnectionFlag(boolean serviceConnectionFlag)
	{
		if(serviceConnectionFlag)
		{
			properties = properties | 0x40;
		}
		else
		{
			properties = properties & 0xFFFFFFBF;
		}
	}
	
	public boolean getUserDefinedFlag()
	{
		return (properties & 0x80) > 0;
	}
	
	public void setUserDefinedFlag(boolean userDefinedFlag)
	{
		if(userDefinedFlag)
		{
			properties = properties | 0x80;
		}
		else
		{
			properties = properties & 0xFFFFFF7F;
		}
	}
	
	public int getVersion()
	{
		return (properties >>> VERSION_BIT_POSITION) & 0x3F;
	}
	
	public void setVersion(int version)
	{
		if(version > -1 && version < 0x4F)
		{
			properties = (version << VERSION_BIT_POSITION) | (properties & 0xFFFFC0FF);
		}
	}
	
	public void setCommandCode(int commandCode)
	{
		this.commandCode = commandCode;
	}

	public int getCommandCode()
	{
		return commandCode;
	}

	public JausAddress getSource()
	{
		return source;
	}

	public void setSource(JausAddress source)
	{
		this.source = source;
	}

	public JausAddress getDestination()
	{
		return destination;
	}

	public void setDestination(JausAddress destination)
	{
		this.destination = destination;
	}

	public void setDataControl(int dataControl)
	{
		this.dataControl = dataControl;
	}

	public int getDataControl()
	{
		return dataControl;
	}

	public void setDataSize(int dataSize)
	{
		if(dataSize > -1 && dataSize <= MAX_DATA_SIZE)
		{
			dataControl = (dataSize << DATA_SIZE_BIT_POSITION) | (dataControl & 0xFFFFF000);
		}
	}

	public int getDataSize()
	{
		return (dataControl >>> DATA_SIZE_BIT_POSITION) & 0x0FFF;
	}
	
	public int getDataFlag()
	{
		return (dataControl >>> DATA_FLAG_BIT_POSITION) & 0x0F;
	}

	public void setDataFlag(int dataFlag)
	{
		if(dataFlag > -1 && dataFlag < 16)
		{
			dataControl = (dataFlag << DATA_FLAG_BIT_POSITION) | (dataControl & 0xFFFF0FFF);
		}
	}

	public int getSequenceNumber()
	{
		return sequenceNumber;
	}

	public void setSequenceNumber(int sequenceNumber)
	{
		this.sequenceNumber = sequenceNumber;
	}

	public byte[] getData()
	{
		return data;
	}
	
	public void setData(byte[] data)
	{
		this.data = data;
	}
	
	// First checks for a proper UDP header and then takes the remaning
	// data buffer and unpacks it into the header data structure and the data byte array
	// This method needs to be overridden for all subclasses of JausMessage to reflect the correct unpack routine
	public boolean setFromJausBuffer(byte[] buffer, int index)
	{
		String headerString = new String(buffer, index, UDP_HEADER_SIZE_BYTES); 
		if(headerString.equals(UDP_HEADER))
		{ 
		    index += UDP_HEADER_SIZE_BYTES;
		}

		if(setHeaderFromJausBuffer(buffer, index))
		{		
		    index += HEADER_SIZE_BYTES;
		    data = new byte[getDataSize()];
			System.arraycopy(buffer, index, data, 0, getDataSize());
			return true;
		}
		else 
		{
		    return false;
		}
	
	}

	// Overloaded method to accept no index input, assumes 0	
	public boolean setFromJausBuffer(byte[] buffer)
	{
		return setFromJausBuffer(buffer, 0);
	}
	
	// Takes the header and data byte array and packs them into a data buffer
	// This method needs to be overridden for all subclasses of JausMessage to reflect the correct pack routine
	public boolean toJausBuffer(byte[] buffer, int index)
	{
		if(buffer.length < (index + HEADER_SIZE_BYTES + data.length))
			return false; //improper size	
		else
		{	
			if(headerToJausBuffer(buffer, index))
			{
				index += HEADER_SIZE_BYTES;
				
			/*	System.out.print("Data Buffer > ");
			    for(int i=0; i<32 && i<data.length; i++)
			    {
			    	System.out.print(" " + (data[i] & 0xFF));
			    }
		    	System.out.println();
			*/	
				System.arraycopy(data, 0, buffer, index, data.length);
				return true;
			}
			else
				return false; //headerToJausBuffer failed
		}
	}
	
	// Overloaded method to accept no index input, assumes 0
	public boolean toJausBuffer(byte[] buffer)
	{
		return toJausBuffer(buffer, 0);
	}

	// Overloaded method to accept a buffer and pack this message into its UDP form
	public boolean toJausUdpBuffer(byte[] buffer, int index)
	{
		if(buffer.length < (index + UDP_HEADER_SIZE_BYTES + HEADER_SIZE_BYTES + data.length))
			return false; //improper size		
		else
		{	
			System.arraycopy(UDP_HEADER.getBytes(), 0, buffer, index, UDP_HEADER_SIZE_BYTES);
			return toJausBuffer(buffer, index + UDP_HEADER_SIZE_BYTES);
		}
	}
	
	// Overloaded method to accept a buffer and pack this message into its UDP form
	public boolean toJausUdpBuffer(byte[] buffer)
	{
		return toJausUdpBuffer(buffer, 0);
	}
	
	// This private method takes a buffer at the given index and unpacks it into the header properties and data fields
	// This method is called whenever a message is unpacked to pull the header properties
	protected boolean setHeaderFromJausBuffer(byte[] buffer, int index)
	{
		if(buffer.length < index + HEADER_SIZE_BYTES)
			return false;
		else
		{
			setProperties((buffer[index] & 0xFF) + ((buffer[index + 1] & 0xFF) << 8));
	
			setCommandCode((buffer[index + 2] & 0xFF) + ((buffer[index + 3] & 0xFF) << 8));
	
			destination.setInstance(buffer[index + 4] & 0xFF);
			destination.setComponent(buffer[index + 5] & 0xFF);
			destination.setNode(buffer[index + 6] & 0xFF);
			destination.setSubsystem(buffer[index + 7] & 0xFF);
	
			source.setInstance(buffer[index + 8] & 0xFF);
			source.setComponent(buffer[index + 9] & 0xFF);
			source.setNode(buffer[index + 10] & 0xFF);
			source.setSubsystem(buffer[index + 11] & 0xFF);
			
			setDataControl((buffer[index + 12] & 0xFF) + ((buffer[index + 13] & 0xFF) << 8));
	
			setSequenceNumber((buffer[index + 14] & 0xFF) + ((buffer[index + 15] & 0xFF) << 8));
			return true;
		}
	}

	// This private method packs the header properties and data fields into the provided buffer at the given index
	// This method is called whenever a message is packed to put the header properties
	protected boolean headerToJausBuffer(byte[] buffer, int index)
	{
		if(buffer.length < index + HEADER_SIZE_BYTES)
			return false;
		else
		{					
			buffer[index] = (byte)(properties & 0xFF);
			buffer[index + 1] = (byte)((properties & 0xFF00) >> 8);

			buffer[index + 2] = (byte)(commandCode & 0xFF);
			buffer[index + 3] = (byte)((commandCode & 0xFF00) >> 8);

			buffer[index + 4] = (byte)(destination.getInstance() & 0xFF);
			buffer[index + 5] = (byte)(destination.getComponent() & 0xFF);
			buffer[index + 6] = (byte)(destination.getNode() & 0xFF);
			buffer[index + 7] = (byte)(destination.getSubsystem() & 0xFF);

			buffer[index + 8] = (byte)(source.getInstance() & 0xFF);
			buffer[index + 9] = (byte)(source.getComponent() & 0xFF);
			buffer[index + 10] = (byte)(source.getNode() & 0xFF);
			buffer[index + 11] = (byte)(source.getSubsystem() & 0xFF);
			
			setDataSize(data.length);
			buffer[index + 12] = (byte)(dataControl & 0xFF);
			buffer[index + 13] = (byte)((dataControl & 0xFF00) >> 8);

			buffer[index + 14] = (byte)(sequenceNumber & 0xFF);
			buffer[index + 15] = (byte)((sequenceNumber & 0xFF00) >> 8);
			
			return true;
		}
	}
	
} //end Class JausHeader


