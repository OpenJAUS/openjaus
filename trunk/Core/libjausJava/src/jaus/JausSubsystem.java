package jaus;
import java.util.*;

public class JausSubsystem extends Vector
{
	public static final long TIMEOUT_MILLISEC = 5000;
	
	String identification;
	int id;
	long timestamp;
	
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

	public JausNode getNode(int id) {
		JausNode node = null;
		int len = size();
		for (int i=0; i<len; i++) {
			node = (JausNode)get(i);
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
