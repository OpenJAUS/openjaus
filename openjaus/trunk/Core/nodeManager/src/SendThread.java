// File Name: SendThread.java
//
// Written By: Tom Galluzzo (galluzzo AT gmail DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This thread is responsible for poping packets off of a Queue and sending them on a UDP socket

import java.net.*;

public class SendThread extends Thread
{
	static long sendCount = 0;
	MulticastSocket sendSocket;
	MulticastSocket subsSocket;
	Queue queue;
	Monitor monitor;
	DataRepository dataRepository;

	public SendThread(MulticastSocket sendSocket, Queue queue, Monitor monitor)
	{
		this.sendSocket = sendSocket;
		this.queue = queue;
		this.monitor = monitor;
		dataRepository = NodeManager.getDataRepository();
		dataRepository.put("Messages Sent Count", new Long(sendCount));
	}
	
	public void run()
	{
		while(NodeManager.isRunning())
		{
			try
			{
				if(queue.isEmpty())
				{
					monitor.waitForSignal(1000);
				}
				
				if(!queue.isEmpty())
				{
					DatagramPacket packet = (DatagramPacket)queue.pop();
					//System.out.println("Sending msg to: " + packet.getAddress());
					sendSocket.send(packet);
					dataRepository.put("Messages Sent Count", new Long(++sendCount));
				}
			}
			catch (Exception e)
			{
				dataRepository.put("SendThread Exception", e);
				System.out.println("SendThread: " + e);
				e.printStackTrace();
			}
		}
	    System.out.println("SendThread: Shutting down");			

	}
		
	public long getSendCount()
	{
		return sendCount;
	}
	
}
