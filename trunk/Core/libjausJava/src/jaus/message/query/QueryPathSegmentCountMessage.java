//File Name: QueryPathSegmentCountMessage.java
//
// Written By: Danny Kent (jaus@dannykent.com)
//
// Version: 3.2  
//
// Date: 07/04/06
//

package jaus.message.query;
import jaus.message.*;

public class QueryPathSegmentCountMessage extends JausMessage
{    
	private static final int COMMAND_CODE = QUERY_PATH_SEGMENT_COUNT;
	private static final int MAX_DATA_SIZE_BYTES = 0;
    
	public QueryPathSegmentCountMessage()
	{
		super();
	}
	
	public QueryPathSegmentCountMessage(byte[] buffer)
	{
		super(buffer, 0);
	}
	
	public QueryPathSegmentCountMessage(byte[] buffer, int index)
	{
	    super(buffer, index);
	}

	public QueryPathSegmentCountMessage(JausMessage jausMessage)
	{
	    super(jausMessage);
	}
	
	public void setCommandCode(int commandCode)
	{
	    this.commandCode = COMMAND_CODE;
	}	
	
}