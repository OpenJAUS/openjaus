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
// File Name: Queue.java
//
// Written By: Tom Galluzzo (galluzzo AT gmail DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: The queue class maintians a linked list of objects and implements the push and pop methods

package openjaus.nodemanager;

import java.util.*;

public class Queue extends LinkedList
{
	String name;
	Monitor monitor;
	DataRepository dataRepository;
	long maxSize;

	int bufferIndex; // Circular buffer index
	long sizeBuffer[]; // Circular size buffer
	final int BUFFER_SIZE = 1000;
	double averageSize;

	public Queue(String name, Monitor monitor)
	{
		super();
		this.name = name;
		this.monitor = monitor;
		dataRepository = NodeManager.getDataRepository();
		
		bufferIndex = 0;
		sizeBuffer = new long[BUFFER_SIZE];
		averageSize = size();

		dataRepository.put(new String(name + " Average Size"), new Double(averageSize));
		maxSize = size();
		dataRepository.put(new String(name + " Max Size"), new Long(maxSize));
	}

	public synchronized void push(Object object)
	{
		addLast(object);

		averageSize -= (double)sizeBuffer[bufferIndex] / (double)BUFFER_SIZE;
		sizeBuffer[bufferIndex] = size();
		averageSize += (double)sizeBuffer[bufferIndex] / (double)BUFFER_SIZE;
		bufferIndex = (bufferIndex + 1) % BUFFER_SIZE;
		
		dataRepository.put(new String(name + " Average Size"), new Double(averageSize));
		if(size() > maxSize)
		{
			maxSize = size();
			dataRepository.put(new String(name + " Max Size"), new Long(maxSize));
		}
		monitor.signal(); // Signal waiting threads to continue
	}

	public synchronized Object pop()
	{
		Object object = removeFirst();

		averageSize -= (double)sizeBuffer[bufferIndex] / (double)BUFFER_SIZE;
		sizeBuffer[bufferIndex] = size();
		averageSize += (double)sizeBuffer[bufferIndex] / (double)BUFFER_SIZE;
		bufferIndex = (bufferIndex + 1) % BUFFER_SIZE;
		
		dataRepository.put(new String(name + " Average Size"), new Double(averageSize));

		return object;
	}
	
}