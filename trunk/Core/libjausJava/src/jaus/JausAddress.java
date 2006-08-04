package jaus;

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
