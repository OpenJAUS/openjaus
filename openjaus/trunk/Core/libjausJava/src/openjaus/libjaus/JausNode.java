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
import java.net.*;

public class JausNode
{
	public static final long TIMEOUT_MILLISEC = 5000;
	//TODO: Check the RefreshTimeout Hack for AFRL compliance
	public static final long REFRESH_TIMEOUT_MILLISEC = 3600000;
	
	String identification;
	int id;
	InetAddress ipAddress;
	int port;
	JausSubsystem subsystem;
	long timestamp;
	long refreshTimestamp;
	Vector components = new Vector();
	boolean nodeConfiguration;
	
	public JausNode()
	{
		super();
		subsystem = new JausSubsystem();
		identification = null;
		id = 0;
		timestamp = System.currentTimeMillis();
		refreshTimestamp = System.currentTimeMillis();
		this.nodeConfiguration = false;
	}

	public JausNode(String identification)
	{
		super();
		subsystem = new JausSubsystem();
		this.identification = identification;
		id = 0;
		timestamp = System.currentTimeMillis();
		this.nodeConfiguration = false;
	}

	public JausNode(int id)
	{
		super();
		subsystem = new JausSubsystem();
		identification = null;
		if(id > 0 && id < 255 ) this.id = id;
		else id = 0;
		timestamp = System.currentTimeMillis();
		this.nodeConfiguration = false;
	}

	// IMPORTANT TODO: GET RID OF THIS CONSTRUCTOR!!!
	public JausNode(int id, InetAddress ipAddress)
	{
		this(id, ipAddress, 3794);
	}

	public JausNode(int id, InetAddress ipAddress, int port)
	{
		super();
		subsystem = new JausSubsystem();
		identification = null;
		if(id > 0 && id < 255 ) this.id = id;
		else id = 0;
		this.ipAddress = ipAddress;
		this.port = port;
		timestamp = System.currentTimeMillis();
		this.nodeConfiguration = false;
	}
	public void addComponent(JausComponent component){
		components.add(component);
	}
	
	public int componentCount(){
		return components.size();
		
	}
	/** All of the components in this Node */
	public Enumeration componentEnumeration(){
		return components.elements();
		
	}
	/** Return index of a component in the internal data structure */
	public int indexOfComponent(JausComponent comp){
		return components.indexOf(comp);
	}
	/** Returns component based on its index in the internal data structure (NOT the
	 * JAUS Id!)
	 * @param index
	 * @return
	 */
	public JausComponent getComponentByIndex(int index){
		return (JausComponent) components.get(index);
	}
	
	public void removeComponent(JausComponent comp){
		components.remove(comp);
		
	}
	/** does this node contain this component? */
	public boolean containsComponent(JausComponent component){
		return components.contains(component);
	}
	/** Gets component based on its JAUS Id */
	public JausComponent getComponent(int id) {
		JausComponent component = null;
		int len = components.size();
		for (int i=0; i<len; i++) {
			component = (JausComponent)components.get(i);
			if (component.getAddress().getComponent() == id)
				return component;
		}
		return null;
	}

	public String getIdentification()
	{
		return identification;
	}
	
	public void setIdentification(String identification)
	{
		this.identification = identification;
	}

	public void setPort(int port) {
		this.port = port;
	}

	public int getPort() {
		return port;
	}
	
	public int getId()
	{
		return id;
	}
	
	public void setConfiguration(boolean value)
	{
		this.nodeConfiguration = value;
	}

	public boolean hasConfiguration()
	{
		return this.nodeConfiguration;
	}

	public void setId(int id)
	{
		if(id > 0 && id < 255 )
			this.id = id;
	}

	public InetAddress getIpAddress()
	{
		return ipAddress;
	}
	
	public void setIpAddress(InetAddress ipAddress)
	{
		this.ipAddress = ipAddress;
	}

	public void setSubsystem(JausSubsystem subsystem)
	{
		this.subsystem = subsystem;
	}
	
	public JausSubsystem getSubsystem()
	{
		return subsystem;
	}

	public void updateRefreshTimestamp()
	{
		refreshTimestamp = System.currentTimeMillis();
	}
	
	public void updateTimestamp()
	{
		timestamp = System.currentTimeMillis();
	}
	
	public boolean refreshHasTimedOut()
	{
		return (System.currentTimeMillis() - REFRESH_TIMEOUT_MILLISEC) > refreshTimestamp ? true : false;
	}
	
	public boolean hasTimedOut()
	{
		return (System.currentTimeMillis() - TIMEOUT_MILLISEC) > timestamp ? true : false;
	}
	
	public String toString()
	{
		if(identification == null)
		{
			return "JausNode" + "-" + id + " (IP: " + ipAddress.getHostAddress() + " : " + port + ")";
		}
		else
		{
			return identification + "-" + id + " (IP: " + ipAddress.getHostAddress() + " : " + port + ")";
		}
	}
	
	public int hashCode()
	{
		return (subsystem.getId() << 24) + (id << 16);
	}
	
	public boolean equals(Object comparisionObject)
	{
		return hashCode() == ((JausNode)comparisionObject).hashCode();
	}
}
