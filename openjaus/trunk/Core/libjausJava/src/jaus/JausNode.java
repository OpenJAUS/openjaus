package jaus;

import java.util.*;
import java.net.*;

public class JausNode extends Vector
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
	
	public JausNode()
	{
		super();
		subsystem = new JausSubsystem();
		identification = null;
		id = 0;
		timestamp = System.currentTimeMillis();
		refreshTimestamp = System.currentTimeMillis();
	}

	public JausNode(String identification)
	{
		super();
		subsystem = new JausSubsystem();
		this.identification = identification;
		id = 0;
		timestamp = System.currentTimeMillis();
	}

	public JausNode(int id)
	{
		super();
		subsystem = new JausSubsystem();
		identification = null;
		if(id > 0 && id < 255 ) this.id = id;
		else id = 0;
		timestamp = System.currentTimeMillis();
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
	}

	public JausComponent getComponent(int id) {
		JausComponent component = null;
		int len = size();
		for (int i=0; i<len; i++) {
			component = (JausComponent)get(i);
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
