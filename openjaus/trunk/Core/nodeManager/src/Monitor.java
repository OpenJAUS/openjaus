// File Name: Monitor.java
//
// Written By: Tom Galluzzo (galluzzo AT gmail DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: The monitor class provides a common object for queues and message threads to maintain a common wait lock.
//				This class is probably redundant, since the queues alone could probably manage a common wait lock, but
//				it has been implemented in this version as an easy solution.

public class Monitor
{
	public synchronized void waitForSignal()
	{
		try
		{
			wait();
		}
		catch (Exception e)
		{
			System.out.println("Monitor: " + e);
		}

	}

	public synchronized void waitForSignal(long timeout)
	{
		try
		{
			wait(timeout);
		}
		catch (Exception e)
		{
			System.out.println("Monitor: " + e);
		}

	}

	public synchronized void signal()
	{
		notifyAll();
	}
}