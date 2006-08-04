//File Name: QueryWaypointCountMessage.java
//
// Written By: Danny Kent (jaus@dannykent.com)
//
// Version: 3.2  
//
// Date: 07/04/06
//

package jaus.message.query;
import jaus.message.*;

public class QueryWaypointCountMessage extends JausMessage
{    
	private static final int COMMAND_CODE = QUERY_WAYPOINT_COUNT;
	private static final int MAX_DATA_SIZE_BYTES = 0;
    
	public QueryWaypointCountMessage()
	{
		super();
	}
	
	public QueryWaypointCountMessage(byte[] buffer)
	{
		super(buffer, 0);
	}
	
	public QueryWaypointCountMessage(byte[] buffer, int index)
	{
	    super(buffer, index);
	}

	public QueryWaypointCountMessage(JausMessage jausMessage)
	{
	    super(jausMessage);
	}
	
	public void setCommandCode(int commandCode)
	{
	    this.commandCode = COMMAND_CODE;
	}	
	
}