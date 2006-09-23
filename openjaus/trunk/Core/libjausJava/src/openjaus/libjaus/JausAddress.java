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

public class JausAddress
{
	public static final int SUBSYSTEM_BIT_POSITION = 24;
	public static final int NODE_BIT_POSITION = 16;
	public static final int COMPONENT_BIT_POSITION = 8;
	public static final int INSTANCE_BIT_POSITION = 0;

	public static final int INVALID_INSTANCE = 0;
	public static final int INVALID_COMPONENT = 0;
	public static final int INVALID_NODE = 0;
	public static final int INVALID_SUBSYSTEM = 0;

	public static final int BROADCAST = 255;
	public static final int BROADCAST_INSTANCE = 255;
	public static final int BROADCAST_COMPONENT = 255;
	public static final int BROADCAST_NODE = 255;
	public static final int BROADCAST_SUBSYSTEM = 255;

	public static final int NODE_MANAGER_COMPONENT = 1;
	public static final int PRIMARY_NODE_MANAGER_NODE = 1;
	public static final int PRIMARY_INSTANCE = 1;

	int id;

	public JausAddress()
	{
		id = 0;
	}

	public JausAddress(int id)
	{
		this.id = id;
	}

	public JausAddress(JausAddress address)
	{
		id = address.getId();
	}
	
	public JausAddress(int subsystem, int node, int component, int instance)
	{
		setSubsystem(subsystem);
		setNode(node);
		setComponent(component);
		setInstance(instance);
	}

	public int getId()
	{
		return id;
	}

	public int getSubsystem()
	{
		return id >>> SUBSYSTEM_BIT_POSITION;
	}

	public int getNode()
	{
		return (id >>> NODE_BIT_POSITION) & 0xFF;
	}

	public int getComponent()
	{
		return (id >>> COMPONENT_BIT_POSITION) & 0xFF;
	}

	public int getInstance()
	{
		return id & 0xFF;
	}

	public void setId(int id)
	{
		this.id = id;
	}

	public void setSubsystem(int subsystem)
	{
		if(subsystem > 0 && subsystem < 256)
		{
			id = (subsystem << SUBSYSTEM_BIT_POSITION) | (id & 0x00FFFFFF);
		}
	}
	
	public void setNode(int node)
	{
		if(node > 0 && node < 256)
		{
			id = (node << NODE_BIT_POSITION) | (id & 0xFF00FFFF);
		}
	}

	public void setComponent(int component)
	{
		if(component > 0 && component < 256)
		{
			id = (component << COMPONENT_BIT_POSITION) | (id & 0xFFFF00FF);
		}
	}

	public void setInstance(int instance)
	{
		if(instance > 0 && instance < 256)
		{
			id = instance | (id & 0xFFFFFF00);
		}
	}
	
	public String toString()
	{
		return "" + getSubsystem() + "." + getNode() + "." + getComponent() + "." + getInstance();
	}

	public int hashCode()
	{
		return id;
	}
	
	public boolean equals(Object comparisionAddress)
	{
		return id == ((JausAddress)comparisionAddress).getId();
	}
}
