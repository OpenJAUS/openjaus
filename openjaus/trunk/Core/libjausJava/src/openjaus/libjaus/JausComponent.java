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

public class JausComponent
{
	public static final int STATE_UNDEFINED	=	-1;
	public static final int STATE_UNKNOWN =		-1;
	public static final int STATE_INVALID = 	-1;

	public static final int STATE_INITIALIZE =	0;
	public static final int STATE_READY =		1;
	public static final int STATE_STANDBY =		2;
	public static final int STATE_SHUTDOWN =	3;
	public static final int STATE_FAILURE =		4;
	public static final int STATE_EMERGENCY =	5;
	
	public static final int NODE_MANAGER = 1;
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

	public static final long TIMEOUT_MILLISEC = 3000;
	
	String identification;
	JausAddress address;
	JausState state;	
	JausComponent controller;
	JausNode node; // Parent node
	Vector services; // JausServices Vector
	int authority;
	boolean controllerActive;
	int port;
	long timestamp;
	boolean servicesInformation;
	
	public JausComponent()
	{
		identification = null;
		address = new JausAddress();
		state = new JausState();
		controller = null;
		node = null;
		services = new Vector();
		JausService service = new JausService();
		service.addCoreServices();
		services.add(service);
		this.servicesInformation = false;
		
		authority = 0;
		controllerActive = false;
		port = -1;
		timestamp = System.currentTimeMillis();
	}

	public JausComponent(String identification)
	{
		this.identification = identification;
		address = new JausAddress();
		state = new JausState();
		controller = null;
		node = null;
		services = new Vector();
		JausService service = new JausService();
		service.addCoreServices();
		services.add(service);
		this.servicesInformation = false;

		authority = 0;
		controllerActive = false;
		port = -1;
		timestamp = System.currentTimeMillis();
	}

	public JausComponent(JausAddress address)
	{
		identification = null;
		this.address = address;
		state = new JausState();
		controller = null;
		node = null;
		services = new Vector();
		JausService service = new JausService();
		service.addCoreServices();
		services.add(service);
		this.servicesInformation = false;

		authority = 0;
		controllerActive = false;
		port = -1;
		timestamp = System.currentTimeMillis();
	}
	
	public JausComponent(JausAddress address, int authority)
	{
		identification = null;
		this.address = address;
		state = new JausState();
		controller = null;
		node = null;
		services = new Vector();
		JausService service = new JausService();
		service.addCoreServices();
		services.add(service);
		this.servicesInformation = false;

		this.authority = authority;
		controllerActive = false;
		port = -1;
		timestamp = System.currentTimeMillis();
	}
	
	public JausComponent(JausAddress address, int authority, int port)
	{
		identification = null;
		this.address = address;
		state = new JausState();
		controller = null;
		node = null;
		services = new Vector();
		JausService service = new JausService();
		service.addCoreServices();
		services.add(service);
		this.servicesInformation = false;

		this.authority = authority;
		controllerActive = false;
		this.port = port;
		timestamp = System.currentTimeMillis();
	}

	public boolean getServicesInformation()
	{
        return this.servicesInformation;
	}
	
	public void setServicesInformation(boolean value)
	{
		this.servicesInformation = value;
	}

	public String getIdentification()
	{
        return identification;
	}
	
	public void setIdentification(String identification)
	{
		this.identification = identification;
	}
	
	public static String getType(int componentId)
	{
		switch(componentId)
		{	
			case NODE_MANAGER:
					return "NodeManager";
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
					if(componentId > NODE_MANAGER && componentId < SUBSYSTEM_COMMANDER)
					{
						return "Experimental";						
					}
					return "Undefined";												
		}
	}
	
	public Vector getServices()
	{
		return services;
	}
	
	public void setServices(Vector services)
	{
		this.services = services;
	}
	
	public boolean serviceCommandExists(int commandCode, int serviceType)
	{
		Enumeration servicesEnum = services.elements();
		while(servicesEnum.hasMoreElements())
		{
			JausService jausService = (JausService)servicesEnum.nextElement();
			
			if(serviceType == JausService.INPUT_COMMAND)
			{
				Enumeration commandEnum = jausService.getInputCommands().elements();
				while(commandEnum.hasMoreElements())
				{
					JausCommand command = (JausCommand)commandEnum.nextElement();
					if(command.getCommandCode() == commandCode) return true;
				}				
			}
			else if(serviceType == JausService.OUTPUT_COMMAND)
			{
				Enumeration commandEnum = jausService.getOutputCommands().elements();
				while(commandEnum.hasMoreElements())
				{
					JausCommand command = (JausCommand)commandEnum.nextElement();
					if(command.getCommandCode() == commandCode) return true;
				}
			}
		}
		return false;
	}
	
	public String getType()
	{
	    return getType(address.getComponent());
	}
	
	public JausAddress getAddress()
	{
		return address;
	}
	
	public void setAddress(JausAddress address)
	{
		this.address = address;
	}

	public JausState getState()
	{
		return state;
	}
	
	public void setState(JausState state)
	{
		this.state = state;
	}

	public JausComponent getController()
	{
		return controller;
	}
	
	public void setController(JausComponent controller)
	{
		this.controller = controller;
	}
	
	public JausNode getNode()
	{
		return node;
	}
	
	public void setNode(JausNode node)
	{
		this.node = node;
	}

	public int getAuthority()
	{
		return authority;
	}
	
	public void setAuthority(int authority)
	{
		this.authority = authority;
	}

	public boolean isControllerActive()
	{
	    return controllerActive;
	}
	
	public int getPort()
	{
		return port;
	}
	
	public void setPort(int port)
	{
		this.port = port;
	}

	public void updateTimestamp()
	{
		timestamp = System.currentTimeMillis();
	}
	
	public boolean hasTimedOut()
	{
		return (System.currentTimeMillis() - TIMEOUT_MILLISEC) > timestamp ? true : false;
	}

	public String toString()
	{
		if(identification == null)
			return getType() + "-" + address.getComponent() + "." + address.getInstance() + " (Port: " + port + ")" + " Service Info: " + servicesInformation;
		else
			return getIdentification() + " (" + getType() + ")-" + address.getComponent() + "." + address.getInstance() + " (Port: " + port + ")" + " Service Info: " + servicesInformation;			
	}

	public int hashCode()
	{
		return address.hashCode();
	}
	
	public boolean equals(Object comparisionComponent)
	{
		return hashCode() == ((JausComponent)comparisionComponent).hashCode();
	}
}
