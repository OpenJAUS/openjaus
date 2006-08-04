// File Name: ReceiveThread.java
//
// Written By: Tom Galluzzo (galluzzo AT gmail DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This thread is responsible for reading packets off of a UDP socket and placing them on a Queue

import java.net.*;
import jaus.message.*;

public class ReceiveThread extends Thread
{
	static long receiveCount = 0;
    DatagramSocket socket;
	Queue queue;
	InetAddress nodeIpAddress;
	int nodePort;
	DataRepository dataRepository;
	
	public ReceiveThread(DatagramSocket socket, Queue queue)
	{
		this.socket = socket;
		this.queue = queue;
		this.nodeIpAddress = NodeManager.getNodeSideIpAddress();
		this.nodePort = NodeManager.getNodePort();
		dataRepository = NodeManager.getDataRepository();
		dataRepository.put("Messages Received Count", new Long(receiveCount));
		
		try
		{
		    socket.setSoTimeout(1000);
		}
		catch(Exception e)
		{
			dataRepository.put("ReceiveThread Exception", e);
			System.out.println(e);
		}
	}
	
	public void run()
	{
		try
		{
		    // Initialize the datagram packet with a pre-sized array (Packets with more data will be truncated)
			int maxJausRecvSize = JausMessage.MAX_DATA_SIZE; 
			maxJausRecvSize += JausMessage.HEADER_SIZE_BYTES;
			maxJausRecvSize += JausMessage.UDP_HEADER_SIZE_BYTES;

			while(NodeManager.isRunning())
			{
				DatagramPacket packet = new DatagramPacket(new byte[maxJausRecvSize], maxJausRecvSize);
				try
				{
					socket.receive(packet);
				}
				catch(SocketTimeoutException e)
				{
					continue;
				}
				dataRepository.put("Messages Received Count", new Long(++receiveCount));
				
				//System.out.println("ReceiveThread: " + this + ", from: " + packet.getAddress());
				
				// If the packet is from another socket then push it on the node Receive Queue
				// Otherwise ignore it because Datagram and Multicast packets are not allowed to loop
				// on this socket. This prevents infinite message loops in the NodeManager

				if(!packet.getAddress().equals(nodeIpAddress))
				{
					queue.push(packet);
				}
				else if(packet.getPort() != nodePort)   
				{
					queue.push(packet);				
				}
				    
			}
		    System.out.println("ReceiveThread: Shutting down");			

		}
		catch (Exception e)
		{
			dataRepository.put("ReceiveThread Exception", e);
			System.out.println(e);
		}
	}
	
	public long getReceiveCount()
	{
		return receiveCount;
	}
	
}
