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

import java.util.*;
import openjaus.libjaus.message.*;

public class JausService
{
	public static final int CORE_MESSAGE_SUPPORT =	0;
	public static final int NO_PRESENCE_VECTOR = 	0;
	public static final int INPUT_COMMAND = 	0;
	public static final int OUTPUT_COMMAND = 	1;

	public static final int SYSTEM_COMMANDER = 40;
	public static final int SUBSYSTEM_COMMANDER = 32;
	public static final int COMMUNICATOR = 35;
	public static final int GLOBAL_POSE_SENSOR = 38;
	public static final int LOCAL_POSE_SENSOR = 41;
	public static final int VELOCITY_STATE_SENSOR = 42;
	public static final int PRIMITIVE_DRIVER = 33;
	public static final int REFLEXIVE_DRIVER = 43;
	public static final int GLOBAL_VECTOR_DRIVER = 34;
	public static final int LOCAL_VECTOR_DRIVER = 44;
	public static final int GLOBAL_WAYPOINT_DRIVER = 45;
	public static final int LOCAL_WAYPOINT_DRIVER = 46;
	public static final int GLOBAL_PATH_SEGMENT_DRIVER = 47;
	public static final int LOCAL_PATH_SEGMENT_DRIVER = 48;
	public static final int PRIMATIVE_MANIPULATOR = 49;
	public static final int MANIPULATOR_JOINT_POSITION_SENSOR = 51;
	public static final int MANIPULATOR_JOINT_VELOCITY_SENSOR = 52;
	public static final int MANIPULATOR_JOINT_FORCE_TORQUE_SENSOR = 53;
	public static final int MANIPULATOR_JOINT_POSITIONS_DRIVER = 54;
	public static final int MANIPULATOR_END_EFFECTOR_DRIVER = 55;
	public static final int MANIPULATOR_JOINT_VELOCITIES_DRIVER = 56;
	public static final int MANIPULATOR_END_EFFECTOR_VELOCITY_STATE_DRIVER = 57;
	public static final int MANIPULATOR_JOINT_MOVE_DRIVER = 58;
	public static final int MANIPULATOR_END_EFFECTOR_DISCRETE_POSE_DRIVER = 59;
	public static final int VISUAL_SENSOR = 37;
	public static final int RANGE_SENSOR = 50;
	
	
	int type;				// Enumeration, same as Component ID from RA 3.2
	Vector inputJausCommands;			// Dynamic Array of input messages 
	Vector outputJausCommands;			// Dynamic Array of output messages	

	public JausService()
	{
		type = 0;
		inputJausCommands = new Vector();
		outputJausCommands = new Vector();
	}
	
	public JausService(int type)
	{
		this();
		this.type = type;
	}
	
	public void addCoreServices()
	{		
		// add each supported core input message 
		this.addInputCommand(JausMessage.SET_COMPONENT_AUTHORITY, NO_PRESENCE_VECTOR);
		this.addInputCommand(JausMessage.SHUTDOWN, NO_PRESENCE_VECTOR);
		this.addInputCommand(JausMessage.STANDBY, NO_PRESENCE_VECTOR);
		this.addInputCommand(JausMessage.RESUME, NO_PRESENCE_VECTOR);
		this.addInputCommand(JausMessage.RESET, NO_PRESENCE_VECTOR);
		this.addInputCommand(JausMessage.SET_EMERGENCY, NO_PRESENCE_VECTOR);
		this.addInputCommand(JausMessage.CLEAR_EMERGENCY, NO_PRESENCE_VECTOR);
		this.addInputCommand(JausMessage.CREATE_SERVICE_CONNECTION, NO_PRESENCE_VECTOR);
		this.addInputCommand(JausMessage.CONFIRM_SERVICE_CONNECTION, NO_PRESENCE_VECTOR);
		this.addInputCommand(JausMessage.ACTIVATE_SERVICE_CONNECTION, NO_PRESENCE_VECTOR);
		this.addInputCommand(JausMessage.SUSPEND_SERVICE_CONNECTION, NO_PRESENCE_VECTOR);
		this.addInputCommand(JausMessage.TERMINATE_SERVICE_CONNECTION, NO_PRESENCE_VECTOR);
		this.addInputCommand(JausMessage.REQUEST_COMPONENT_CONTROL, NO_PRESENCE_VECTOR);
		this.addInputCommand(JausMessage.RELEASE_COMPONENT_CONTROL, NO_PRESENCE_VECTOR);
		this.addInputCommand(JausMessage.CONFIRM_COMPONENT_CONTROL, NO_PRESENCE_VECTOR);
		this.addInputCommand(JausMessage.REJECT_COMPONENT_CONTROL, NO_PRESENCE_VECTOR);
		this.addInputCommand(JausMessage.QUERY_COMPONENT_AUTHORITY, NO_PRESENCE_VECTOR);
		this.addInputCommand(JausMessage.QUERY_COMPONENT_STATUS, NO_PRESENCE_VECTOR);
		this.addInputCommand(JausMessage.REPORT_COMPONENT_AUTHORITY, NO_PRESENCE_VECTOR);
		this.addInputCommand(JausMessage.REPORT_COMPONENT_STATUS, NO_PRESENCE_VECTOR);
		
		// add each supported this output message
		this.addOutputCommand(JausMessage.CREATE_SERVICE_CONNECTION, NO_PRESENCE_VECTOR);
		this.addOutputCommand(JausMessage.CONFIRM_SERVICE_CONNECTION, NO_PRESENCE_VECTOR);
		this.addOutputCommand(JausMessage.TERMINATE_SERVICE_CONNECTION, NO_PRESENCE_VECTOR);
		this.addOutputCommand(JausMessage.CONFIRM_COMPONENT_CONTROL, NO_PRESENCE_VECTOR);
		this.addOutputCommand(JausMessage.REJECT_COMPONENT_CONTROL, NO_PRESENCE_VECTOR);
		this.addOutputCommand(JausMessage.REPORT_COMPONENT_AUTHORITY, NO_PRESENCE_VECTOR);
		this.addOutputCommand(JausMessage.REPORT_COMPONENT_STATUS, NO_PRESENCE_VECTOR);
		
		// experimental messages handled by default
		this.addInputCommand(JausMessage.QUERY_IDENTIFICATION, NO_PRESENCE_VECTOR);
		this.addOutputCommand(JausMessage.QUERY_IDENTIFICATION, NO_PRESENCE_VECTOR);
		this.addInputCommand(JausMessage.REPORT_IDENTIFICATION, NO_PRESENCE_VECTOR);
		this.addOutputCommand(JausMessage.REPORT_IDENTIFICATION, NO_PRESENCE_VECTOR);
		this.addInputCommand(JausMessage.REPORT_CONFIGURATION, NO_PRESENCE_VECTOR);
		this.addOutputCommand(JausMessage.REPORT_CONFIGURATION, NO_PRESENCE_VECTOR);
		this.addInputCommand(JausMessage.QUERY_CONFIGURATION, NO_PRESENCE_VECTOR);
		this.addOutputCommand(JausMessage.QUERY_CONFIGURATION, NO_PRESENCE_VECTOR);
		this.addInputCommand(JausMessage.CONFIGURATION_CHANGED_EVENT_SETUP, NO_PRESENCE_VECTOR);
		this.addOutputCommand(JausMessage.CONFIGURATION_CHANGED_EVENT_SETUP, NO_PRESENCE_VECTOR);
		this.addInputCommand(JausMessage.CONFIGURATION_CHANGED_EVENT_NOTIFICATION, NO_PRESENCE_VECTOR);
		this.addOutputCommand(JausMessage.CONFIGURATION_CHANGED_EVENT_NOTIFICATION, NO_PRESENCE_VECTOR);
		this.addInputCommand(JausMessage.CREATE_EVENT, 0xF);
		this.addOutputCommand(JausMessage.CREATE_EVENT, 0xF);
		this.addInputCommand(JausMessage.CONFIRM_EVENT, NO_PRESENCE_VECTOR);
		this.addOutputCommand(JausMessage.CONFIRM_EVENT, NO_PRESENCE_VECTOR);

	}
	
	public void addInputCommand(int commandCode, long presenceVector)
	{
		JausCommand command = new JausCommand(commandCode, presenceVector);
		inputJausCommands.add(command);
	}

	public void addOutputCommand(int commandCode, long presenceVector)
	{
		JausCommand command = new JausCommand(commandCode, presenceVector);
		outputJausCommands.add(command);
	}
	
	public Vector getInputCommands()
	{
		return inputJausCommands;
	}

	public Vector getOutputCommands()
	{
		return outputJausCommands;
	}
	
	public int getType()
	{
		return type;
	}

	public static String getTypeString(int type)
	{
		switch(type)
		{	
			case CORE_MESSAGE_SUPPORT:
					return "Core Message Support";
			case SYSTEM_COMMANDER:
					return "SystemCommander";
			case SUBSYSTEM_COMMANDER:
					return "SubsystemCommander";
			case COMMUNICATOR:
					return "Communicator";
			case GLOBAL_POSE_SENSOR:
					return "GlobalPoseSensor";
			case LOCAL_POSE_SENSOR:
					return "LocalPosSensor";
			case VELOCITY_STATE_SENSOR:
					return "VelocityStateSensor";
			case PRIMITIVE_DRIVER:
					return "PrimitiveDriver";
			case REFLEXIVE_DRIVER:
					return "ReflexiveDriver";
			case GLOBAL_VECTOR_DRIVER:
					return "GlobalVectorDriver";
			case LOCAL_VECTOR_DRIVER:
					return "LocalVectorDriver";
			case GLOBAL_WAYPOINT_DRIVER:
					return "GlobalWaypointDriver";
			case LOCAL_WAYPOINT_DRIVER:
					return "LocalWaypointDriver";
			case GLOBAL_PATH_SEGMENT_DRIVER:
					return "GlobalPathSegmentDriver";
			case LOCAL_PATH_SEGMENT_DRIVER:
					return "LocalPathSegmentDriver";
			case PRIMATIVE_MANIPULATOR:
					return "PrimativeManipulator";
			case MANIPULATOR_JOINT_POSITION_SENSOR:
					return "ManipulatorJointPositionSensor";
			case MANIPULATOR_JOINT_VELOCITY_SENSOR:
					return "ManipulatorJointVelocitySensor";
			case MANIPULATOR_JOINT_FORCE_TORQUE_SENSOR:
					return "ManipulatorJointForce/TorqueSensor";
			case MANIPULATOR_JOINT_POSITIONS_DRIVER:
					return "ManipulatorJointPositionsDriver";
			case MANIPULATOR_END_EFFECTOR_DRIVER:
					return "ManipulatorEndEffectorDriver";
			case MANIPULATOR_JOINT_VELOCITIES_DRIVER:
					return "ManipulatorJointVelocitiesDriver";
			case MANIPULATOR_END_EFFECTOR_VELOCITY_STATE_DRIVER:
					return "ManipulatorEndEffectorVelocityStateDriver";
			case MANIPULATOR_JOINT_MOVE_DRIVER:
					return "ManipulatorJointMoveDriver";
			case MANIPULATOR_END_EFFECTOR_DISCRETE_POSE_DRIVER:
					return "ManipulatorEndEffectorDiscretePoseDriver";
			case VISUAL_SENSOR:
					return "VisualSensor";
			case RANGE_SENSOR:
					return "RangeSensor";
			default:
					return "Unknown";												
		}
	}

	public String getTypeString()
	{
		return getTypeString(getType());
	}
	
	public int hashCode()
	{
		return type;
	}
	
	public boolean equals(Object comparisonService)
	{
		JausService input = (JausService)comparisonService;
		
		if(type != input.getType()) return false;
		
		if(inputJausCommands.size() != input.getInputCommands().size()) return false;
		for(int i = 0; i < inputJausCommands.size(); i++)
		{
			if(inputJausCommands.elementAt(i) != input.getInputCommands().elementAt(i)) return false;
		}

		if(outputJausCommands.size() != input.getOutputCommands().size()) return false;
		for(int i = 0; i < outputJausCommands.size(); i++)
		{
			if(outputJausCommands.elementAt(i) != input.getOutputCommands().elementAt(i)) return false;
		}

		return true;
	}
	
	public String toString()
	{
		return "Service: " + getTypeString() + ", Type: " + getType();
	}
}