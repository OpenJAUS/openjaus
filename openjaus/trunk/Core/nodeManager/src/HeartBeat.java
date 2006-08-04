// File Name: HeartBeat.java
//
// Written By: Tom Galluzzo (galluzzo AT gmail DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This class runs a thread that generates a JAUS Heartbeat message, which keeps the NodeManager active and
//				Informs other NodeManagers and JAUS entities of this NodeManager's existence.

import jaus.*;
import jaus.message.inform.*;
import java.net.*;

class HeartBeat extends Thread
{
	static long beatCount  = 0;
	long beatPerioidMilliSec;
	Queue nodeSendQueue;
	Queue componentReceiveQueue;
	SubsystemTable subsystemTable;
	JausAddress thisAddress;
	JausComponent thisComponent;
	JausNode thisNode;
	MulticastSocket subsystemSocket;
	InetAddress nodeGroupAddress;
	InetAddress subsGroupAddress;
	InetAddress ipAddress;
	DataRepository dataRepository;
	int nodePort;
	
	public HeartBeat(long beatPerioidMilliSec, Queue outputQueue, Queue componentQueue, SubsystemTable subsystemTable)
	{
	    this.beatPerioidMilliSec = beatPerioidMilliSec;
		this.nodeSendQueue = outputQueue;
		this.subsystemTable = subsystemTable;
		this.componentReceiveQueue = componentQueue;
		thisComponent = NodeManager.getComponent();
		thisAddress = thisComponent.getAddress();
		thisNode = thisComponent.getNode();
		
		subsystemSocket = NodeManager.getSubsystemSocket();
		nodeGroupAddress = NodeManager.getNodeGroupAddress();
		subsGroupAddress = NodeManager.getSubsystemGroupAddress();
		ipAddress = NodeManager.getNodeSideIpAddress();
		nodePort = NodeManager.getNodePort();

		dataRepository = NodeManager.getDataRepository();
		dataRepository.put("Heartbeat Count", new Long(beatCount));
	}

	public void run()
	{
	    try
	    {
	        ReportHeartbeatPulseMessage heartBeatMessage = new ReportHeartbeatPulseMessage();
			heartBeatMessage.setSource(thisAddress);
			
			heartBeatMessage.getDestination().setSubsystem(thisAddress.getSubsystem());
			heartBeatMessage.getDestination().setNode(JausAddress.BROADCAST_NODE);
			heartBeatMessage.getDestination().setComponent(JausAddress.NODE_MANAGER_COMPONENT);
			heartBeatMessage.getDestination().setInstance(thisAddress.getInstance());
			byte[] buffer = new byte[heartBeatMessage.udpSize()];
			heartBeatMessage.toJausUdpBuffer(buffer);
			DatagramPacket packet = new DatagramPacket(buffer, buffer.length, nodeGroupAddress, nodePort);

			heartBeatMessage.getDestination().setSubsystem(thisAddress.getSubsystem());
			heartBeatMessage.getDestination().setNode(thisAddress.getNode());
			heartBeatMessage.getDestination().setComponent(JausAddress.BROADCAST_COMPONENT);
			heartBeatMessage.getDestination().setInstance(JausAddress.BROADCAST_INSTANCE);
			buffer = new byte[heartBeatMessage.size()];
			heartBeatMessage.toJausBuffer(buffer);
			DatagramPacket cmptPacket = new DatagramPacket(buffer, buffer.length, thisNode.getIpAddress(), thisComponent.getPort());

			if(subsystemSocket != null)
			{
				heartBeatMessage.getDestination().setSubsystem(JausAddress.BROADCAST_SUBSYSTEM);
				heartBeatMessage.getDestination().setNode(JausAddress.BROADCAST_NODE);
				heartBeatMessage.getDestination().setComponent(JausAddress.NODE_MANAGER_COMPONENT);
				heartBeatMessage.getDestination().setInstance(thisAddress.getInstance());
				buffer = new byte[heartBeatMessage.udpSize()];
				heartBeatMessage.toJausUdpBuffer(buffer);
				DatagramPacket subsPacket = new DatagramPacket(buffer, buffer.length, subsGroupAddress, nodePort);

				while(NodeManager.isRunning())
				{
					nodeSendQueue.push(packet);
					componentReceiveQueue.push(cmptPacket);
					subsystemSocket.send(subsPacket);
					subsystemTable.refresh();
					dataRepository.put("Heartbeat Count", new Long(++beatCount));
					sleep(beatPerioidMilliSec);
				}

			}
			else
			{
				while(NodeManager.isRunning())
				{
					nodeSendQueue.push(packet);
					componentReceiveQueue.push(cmptPacket);
					subsystemTable.refresh();
					dataRepository.put("Heartbeat Count", new Long(++beatCount));
					sleep(beatPerioidMilliSec);
				}				
			}
		    System.out.println("Heartbeat: Shutting down");			
	    }
	    catch(Exception e)
	    {
			NodeManager.getDataRepository().put("HeartBeat Exception", e);
	        System.out.println("HeartBeat: " + e);//Print and as usual ignore errors
	        
	    }
	}
	
	public long getBeatCount()
	{
		return beatCount;
	}
	
}
