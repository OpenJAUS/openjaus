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
package openjaus.libjaus;

import openjaus.libjaus.message.*;

public class JausCommand
{
	private int commandCode;
	private long presenceVector;			 

	public JausCommand()
	{
		commandCode = 0;
		presenceVector = 0;
	}
	
	public JausCommand( int commandCode, long presenceVector)
	{
		this.commandCode = commandCode;
		this.presenceVector = presenceVector;
	}

	public int getCommandCode()
	{
		return commandCode;
	}
	
	public long getPresenceVector()
	{
		return presenceVector;
	}
	
	public int hashCode()
	{
		return commandCode;
	}
	
	public boolean equals(Object comparisionCommand)
	{
		return (this.commandCode == ((JausCommand)comparisionCommand).getCommandCode() &&
				this.presenceVector == ((JausCommand)comparisionCommand).getPresenceVector() ) ;
	}	
	
	public String toString()
	{
		return ""+JausCommand.commandCodeString(this.commandCode);
	}
	
	public static String commandCodeString(int commandCode)
	{
		switch(commandCode)
		{
			case JausMessage.SET_COMPONENT_AUTHORITY:
				return "SET_COMPONENT_AUTHORITY";
			case JausMessage.SHUTDOWN:
				return "SHUTDOWN";
			case JausMessage.STANDBY:
				return "STANDBY";
			case JausMessage.RESUME:
				return "RESUME";
			case JausMessage.RESET:
				return "RESET";
			case JausMessage.SET_EMERGENCY:
				return "SET_EMERGENCY";
			case JausMessage.CLEAR_EMERGENCY:
				return "CLEAR_EMERGENCY";
			case JausMessage.CREATE_SERVICE_CONNECTION:
				return "CREATE_SERVICE_CONNECTION";
			case JausMessage.CONFIRM_SERVICE_CONNECTION:
				return "CONFIRM_SERVICE_CONNECTION";
			case JausMessage.ACTIVATE_SERVICE_CONNECTION:
				return "ACTIVATE_SERVICE_CONNECTION";
			case JausMessage.SUSPEND_SERVICE_CONNECTION:
				return "SUSPEND_SERVICE_CONNECTION";
			case JausMessage.TERMINATE_SERVICE_CONNECTION:
				return "TERMINATE_SERVICE_CONNECTION";
			case JausMessage.REQUEST_COMPONENT_CONTROL:
				return "REQUEST_COMPONENT_CONTROL";
			case JausMessage.RELEASE_COMPONENT_CONTROL:
				return "RELEASE_COMPONENT_CONTROL";
			case JausMessage.CONFIRM_COMPONENT_CONTROL:
				return "CONFIRM_COMPONENT_CONTROL";
			case JausMessage.REJECT_COMPONENT_CONTROL:
				return "REJECT_COMPONENT_CONTROL";
			case JausMessage.SET_TIME:
				return "SET_TIME";
			case JausMessage.SET_DATA_LINK_STATUS:
				return "SET_DATA_LINK_STATUS";
			case JausMessage.SET_DATA_LINK_SELECT:
				return "SET_DATA_LINK_SELECT";
			case JausMessage.SET_WRENCH_EFFORT:
				return "SET_WRENCH_EFFORT";
			case JausMessage.SET_DISCRETE_DEVICES:
				return "SET_DISCRETE_DEVICES";
			case JausMessage.SET_GLOBAL_VECTOR:
				return "SET_GLOBAL_VECTOR";
			case JausMessage.SET_LOCAL_VECTOR:
				return "SET_LOCAL_VECTOR";
			case JausMessage.SET_TRAVEL_SPEED:
				return "SET_TRAVEL_SPEED";
			case JausMessage.SET_GLOBAL_WAYPOINT:
				return "SET_GLOBAL_WAYPOINT";
			case JausMessage.SET_LOCAL_WAYPOINT:
				return "SET_LOCAL_WAYPOINT";
			case JausMessage.SET_GLOBAL_PATH_SEGMENT:
				return "SET_GLOBAL_PATH_SEGMENT";
			case JausMessage.SET_LOCAL_PATH_SEGMENT:
				return "SET_LOCAL_PATH_SEGMENT";
			case JausMessage.SET_JOINT_EFFORTS:
				return "SET_JOINT_EFFORTS";
			case JausMessage.SET_JOINT_POSITIONS:
				return "SET_JOINT_POSITIONS";
			case JausMessage.SET_JOINT_VELOCITIES:
				return "SET_JOINT_VELOCITIES";
			case JausMessage.SET_TOOL_POINT:
				return "SET_TOOL_POINT";
			case JausMessage.SET_END_EFFECTOR_POSE:
				return "SET_END_EFFECTOR_POSE";
			case JausMessage.SET_END_EFFECTOR_VELOCITY_STATE:
				return "SET_END_EFFECTOR_VELOCITY_STATE";
			case JausMessage.SET_JOINT_MOTION:
				return "SET_JOINT_MOTION";
			case JausMessage.SET_END_EFFECTOR_PATH_MOTION:
				return "SET_END_EFFECTOR_PATH_MOTION";
			case JausMessage.SET_CAMERA_POSE:
				return "SET_CAMERA_POSE";
			case JausMessage.SELECT_CAMERA:
				return "SELECT_CAMERA";
			case JausMessage.SET_CAMERA_CAPABILITIES:
				return "SET_CAMERA_CAPABILITIES";
			case JausMessage.SET_CAMERA_FORMAT_OPTIONS:
				return "SET_CAMERA_FORMAT_OPTIONS";
			case JausMessage.QUERY_COMPONENT_AUTHORITY:
				return "QUERY_COMPONENT_AUTHORITY";
			case JausMessage.QUERY_COMPONENT_STATUS:
				return "QUERY_COMPONENT_STATUS";
			case JausMessage.QUERY_TIME:
				return "QUERY_TIME";
			case JausMessage.QUERY_DATA_LINK_STATUS:
				return "QUERY_DATA_LINK_STATUS";
			case JausMessage.QUERY_SELECTED_DATA_LINK_STATUS:
				return "QUERY_SELECTED_DATA_LINK_STATUS";
			case JausMessage.QUERY_HEARTBEAT_PULSE:
				return "QUERY_HEARTBEAT_PULSE";
			case JausMessage.QUERY_PLATFORM_SPECIFICATIONS:
				return "QUERY_PLATFORM_SPECIFICATIONS";
			case JausMessage.QUERY_PLATFORM_OPERATIONAL_DATA:
				return "QUERY_PLATFORM_OPERATIONAL_DATA";
			case JausMessage.QUERY_GLOBAL_POSE:
				return "QUERY_GLOBAL_POSE";
			case JausMessage.QUERY_LOCAL_POSE:
				return "QUERY_LOCAL_POSE";
			case JausMessage.QUERY_VELOCITY_STATE:
				return "QUERY_VELOCITY_STATE";
			case JausMessage.QUERY_WRENCH_EFFORT:
				return "QUERY_WRENCH_EFFORT";
			case JausMessage.QUERY_DISCRETE_DEVICES:
				return "QUERY_DISCRETE_DEVICES";
			case JausMessage.QUERY_GLOBAL_VECTOR:
				return "QUERY_GLOBAL_VECTOR";
			case JausMessage.QUERY_LOCAL_VECTOR:
				return "QUERY_LOCAL_VECTOR";
			case JausMessage.QUERY_TRAVEL_SPEED:
				return "QUERY_TRAVEL_SPEED";
			case JausMessage.QUERY_WAYPOINT_COUNT:
				return "QUERY_WAYPOINT_COUNT";
			case JausMessage.QUERY_GLOBAL_WAYPOINT:
				return "QUERY_GLOBAL_WAYPOINT";
			case JausMessage.QUERY_LOCAL_WAYPOINT:
				return "QUERY_LOCAL_WAYPOINT";
			case JausMessage.QUERY_PATH_SEGMENT_COUNT:
				return "QUERY_PATH_SEGMENT_COUNT";
			case JausMessage.QUERY_GLOBAL_PATH_SEGMENT:
				return "QUERY_GLOBAL_PATH_SEGMENT";
			case JausMessage.QUERY_LOCAL_PATH_SEGMENT:
				return "QUERY_LOCAL_PATH_SEGMENT";
			case JausMessage.QUERY_MANIPULATOR_SPECIFICATIONS:
				return "QUERY_MANIPULATOR_SPECIFICATIONS";
			case JausMessage.QUERY_JOINT_EFFORTS:
				return "QUERY_JOINT_EFFORTS";
			case JausMessage.QUERY_JOINT_POSITIONS:
				return "QUERY_JOINT_POSITIONS";
			case JausMessage.QUERY_JOINT_VELOCITIES:
				return "QUERY_JOINT_VELOCITIES";
			case JausMessage.QUERY_TOOL_POINT:
				return "QUERY_TOOL_POINT";
			case JausMessage.QUERY_JOINT_FORCE_TORQUES:
				return "QUERY_JOINT_FORCE_TORQUES";
			case JausMessage.QUERY_CAMERA_POSE:
				return "QUERY_CAMERA_POSE";
			case JausMessage.QUERY_CAMERA_COUNT:
				return "QUERY_CAMERA_COUNT";
			case JausMessage.QUERY_RELATIVE_OBJECT_POSITION:
				return "QUERY_RELATIVE_OBJECT_POSITION";
			case JausMessage.QUERY_SELECTED_CAMERA:
				return "QUERY_SELECTED_CAMERA";
			case JausMessage.QUERY_CAMERA_CAPABILITIES:
				return "QUERY_CAMERA_CAPABILITIES";
			case JausMessage.QUERY_CAMERA_FORMAT_OPTIONS:
				return "QUERY_CAMERA_FORMAT_OPTIONS";
			case JausMessage.QUERY_IMAGE:
				return "QUERY_IMAGE";
			case JausMessage.REPORT_COMPONENT_AUTHORITY:
				return "REPORT_COMPONENT_AUTHORITY";
			case JausMessage.REPORT_COMPONENT_STATUS:
				return "REPORT_COMPONENT_STATUS";
			case JausMessage.REPORT_TIME:
				return "REPORT_TIME";
			case JausMessage.REPORT_DATA_LINK_STATUS:
				return "REPORT_DATA_LINK_STATUS";
			case JausMessage.REPORT_SELECTED_DATA_LINK_STATUS:
				return "REPORT_SELECTED_DATA_LINK_STATUS";
			case JausMessage.REPORT_HEARTBEAT_PULSE:
				return "REPORT_HEARTBEAT_PULSE";
			case JausMessage.REPORT_PLATFORM_SPECIFICATIONS:
				return "REPORT_PLATFORM_SPECIFICATIONS";
			case JausMessage.REPORT_PLATFORM_OPERATIONAL_DATA:
				return "REPORT_PLATFORM_OPERATIONAL_DATA";
			case JausMessage.REPORT_GLOBAL_POSE:
				return "REPORT_GLOBAL_POSE";
			case JausMessage.REPORT_LOCAL_POSE:
				return "REPORT_LOCAL_POSE";
			case JausMessage.REPORT_VELOCITY_STATE:
				return "REPORT_VELOCITY_STATE";
			case JausMessage.REPORT_WRENCH_EFFORT:
				return "REPORT_WRENCH_EFFORT";
			case JausMessage.REPORT_DISCRETE_DEVICES:
				return "REPORT_DISCRETE_DEVICES";
			case JausMessage.REPORT_GLOBAL_VECTOR:
				return "REPORT_GLOBAL_VECTOR";
			case JausMessage.REPORT_LOCAL_VECTOR:
				return "REPORT_LOCAL_VECTOR";
			case JausMessage.REPORT_TRAVEL_SPEED:
				return "REPORT_TRAVEL_SPEED";
			case JausMessage.REPORT_WAYPOINT_COUNT:
				return "REPORT_WAYPOINT_COUNT";
			case JausMessage.REPORT_GLOBAL_WAYPOINT:
				return "REPORT_GLOBAL_WAYPOINT";
			case JausMessage.REPORT_LOCAL_WAYPOINT:
				return "REPORT_LOCAL_WAYPOINT";
			case JausMessage.REPORT_PATH_SEGMENT_COUNT:
				return "REPORT_PATH_SEGMENT_COUNT";
			case JausMessage.REPORT_GLOBAL_PATH_SEGMENT:
				return "REPORT_GLOBAL_PATH_SEGMENT";
			case JausMessage.REPORT_LOCAL_PATH_SEGMENT:
				return "REPORT_LOCAL_PATH_SEGMENT";
			case JausMessage.REPORT_MANIPULATOR_SPECIFICATIONS:
				return "REPORT_MANIPULATOR_SPECIFICATIONS";
			case JausMessage.REPORT_JOINT_EFFORTS:
				return "REPORT_JOINT_EFFORTS";
			case JausMessage.REPORT_JOINT_POSITIONS:
				return "REPORT_JOINT_POSITIONS";
			case JausMessage.REPORT_JOINT_VELOCITIES:
				return "REPORT_JOINT_VELOCITIES";
			case JausMessage.REPORT_TOOL_POINT:
				return "REPORT_TOOL_POINT";
			case JausMessage.REPORT_JOINT_FORCE_TORQUES:
				return "REPORT_JOINT_FORCE_TORQUES";
			case JausMessage.REPORT_CAMERA_POSE:
				return "REPORT_CAMERA_POSE";
			case JausMessage.REPORT_CAMERA_COUNT:
				return "REPORT_CAMERA_COUNT";
			case JausMessage.REPORT_RELATIVE_OBJECT_POSITION:
				return "REPORT_RELATIVE_OBJECT_POSITION";
			case JausMessage.REPORT_SELECTED_CAMERA:
				return "REPORT_SELECTED_CAMERA";
			case JausMessage.REPORT_CAMERA_CAPABILITIES:
				return "REPORT_CAMERA_CAPABILITIES";
			case JausMessage.REPORT_CAMERA_FORMAT_OPTIONS:
				return "REPORT_CAMERA_FORMAT_OPTIONS";
			case JausMessage.REPORT_IMAGE:
				return "REPORT_IMAGE";
			case JausMessage.QUERY_IDENTIFICATION:
				return "QUERY_IDENTIFICATION";
			case JausMessage.REPORT_IDENTIFICATION:
				return "REPORT_IDENTIFICATION";
			case JausMessage.QUERY_CONFIGURATION:
				return "QUERY_CONFIGURATION";
			case JausMessage.REPORT_CONFIGURATION:
				return "REPORT_CONFIGURATION";
			case JausMessage.CONFIGURATION_CHANGED_EVENT_SETUP:
				return "CONFIGURATION_CHANGED_EVENT_SETUP";
			case JausMessage.CONFIGURATION_CHANGED_EVENT_NOTIFICATION:
				return "CONFIGURATION_CHANGED_EVENT_NOTIFICATION";
			case JausMessage.CREATE_EVENT:
				return "CREATE_EVENT";
			case JausMessage.CONFIRM_EVENT:
				return "CONFIRM_EVENT";
			case JausMessage.QUERY_SERVICES:
				return "QUERY_SERVICES";
			case JausMessage.REPORT_SERVICES:		
				return "REPORT_SERVICES";
			default:
				return "UNDEFINED JAUS MESSAGE: " + Integer.toHexString(commandCode).toUpperCase();
		}
	}
}
