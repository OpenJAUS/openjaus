//File Name: QueryTravelSpeedMessage.java
//
// Written By: Danny Kent (jaus@dannykent.com)
//
// Version: 3.2  
//
// Date: 07/04/06
//

package jaus.message.query;
import jaus.message.*;

public class QueryTravelSpeedMessage extends JausMessage
{    
	private static final int COMMAND_CODE = QUERY_TRAVEL_SPEED;
	private static final int MAX_DATA_SIZE_BYTES = 0;
    
	public QueryTravelSpeedMessage()
	{
		super();
	}
	
	public QueryTravelSpeedMessage(byte[] buffer)
	{
		super(buffer, 0);
	}
	
	public QueryTravelSpeedMessage(byte[] buffer, int index)
	{
	    super(buffer, index);
	}

	public QueryTravelSpeedMessage(JausMessage jausMessage)
	{
	    super(jausMessage);
	}
	
	public void setCommandCode(int commandCode)
	{
	    this.commandCode = COMMAND_CODE;
	}	
	
}