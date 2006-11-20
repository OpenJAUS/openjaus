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

public class JausSubsystem 
{
	public static final long TIMEOUT_MILLISEC = 5000;
	
	String identification;
	int id;
	long timestamp;
	/** Vector of Nodes within this subsystem */
	Vector jausNodes = new Vector();
	
	public JausSubsystem()
	{
		super();
		identification = null;
		id = 0;
		timestamp = System.currentTimeMillis();
	}

	public JausSubsystem(String identification)
	{
		super();
		this.identification = identification;
		id = 0;
		timestamp = System.currentTimeMillis();
	}

	public JausSubsystem(int id)
	{
		super();
		identification = null;
		if(id > 0 && id < 255 ) this.id = id;
		else id = 0;
		timestamp = System.currentTimeMillis();
	}

	/** Returns number of Nodes in this Subsystem */
	public int nodeCount(){
		return jausNodes.size();
	}
	
	/** Returns enumeration of all nodes in this subsystem */
	public Enumeration nodeEnumeration(){
		return jausNodes.elements();
	}
	/** Add a node to the end of the list */
	public void addNode(JausNode newNode){
		jausNodes.add(newNode);
	}
	
	public boolean containsNode(JausNode compNode){
		return jausNodes.contains(compNode);
	}
	public int indexOfNode(JausNode compNode){
		return jausNodes.indexOf(compNode);
	}
	/** Returns a node based on it's index in the list.  This is NOT the same as NodeId,
	 * but is instead just the order it got added to this particular JausSubsystem object.
	 * @param index
	 * @return
	 */
	public JausNode getNodeByIndex(int index){
		return (JausNode) jausNodes.get(index);
	}
	
	public void removeNode(JausNode removeNode){
		jausNodes.remove(removeNode);
	}
	/** Returns a JausNode based on it's ID */
	public JausNode getNode(int id) {
		JausNode node = null;
		int len = jausNodes.size();
		for (int i=0; i<len; i++) {
			node = (JausNode)jausNodes.get(i);
			if (node.getId() == id)
				return node;
		}
		return null;
	}
	
	public void updateTimestamp()
	{
		timestamp = System.currentTimeMillis();
	}
	
	public boolean hasTimedOut()
	{
		return (System.currentTimeMillis() - TIMEOUT_MILLISEC) > timestamp ? true : false;
	}
	
	public String getIdentification()
	{
		return identification;
	}
	
	public void setIdentification(String identification)
	{
		this.identification = identification;
	}
	
	public int getId()
	{
		return id;
	}
	
	public void setId(int id)
	{
		if(id > -1 && id < 255 )
			this.id = id;
	}

	public String toString()
	{
		if(identification == null)
			return "JausSubsystem" + "-" + id;
		else
			return identification + "-" + id;			
	}
	
	public int hashCode()
	{
		return id << 24;
	}
	
	public boolean equals(Object comparisionObject)
	{
		return hashCode() == ((JausSubsystem)comparisionObject).hashCode();
	}
}
