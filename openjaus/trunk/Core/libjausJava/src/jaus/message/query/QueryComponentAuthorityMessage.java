//File Name: QueryComponentAuthorityMessage.java
//
// Written By: Tom Galluzzo (galluzzo@gmail.com)
//
// Version: 3.2  
//
// Date: 07/04/06
//

package jaus.message.query;
import jaus.message.*;

public class QueryComponentAuthorityMessage extends JausMessage
{    
	private static final int COMMAND_CODE = QUERY_COMPONENT_AUTHORITY;
	private static final int MAX_DATA_SIZE_BYTES = 0;
    
	public QueryComponentAuthorityMessage()
	{
		super();
	}
	
	public QueryComponentAuthorityMessage(byte[] buffer)
	{
		super(buffer, 0);
	}
	
	public QueryComponentAuthorityMessage(byte[] buffer, int index)
	{
	    super(buffer, index);
	}

	public QueryComponentAuthorityMessage(JausMessage jausMessage)
	{
	    super(jausMessage);
	}
	
	public void setCommandCode(int commandCode)
	{
	    this.commandCode = COMMAND_CODE;
	}	
	
}