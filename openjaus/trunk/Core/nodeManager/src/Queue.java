// File Name: Queue.java
//
// Written By: Tom Galluzzo (galluzzo AT gmail DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: The queue class maintians a linked list of objects and implements the push and pop methods

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