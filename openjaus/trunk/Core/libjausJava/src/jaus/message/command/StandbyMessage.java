//File Name: StandbyMessage.java
//
// Written By: Tom Galluzzo (galluzzo@gmail.com)
//
// Version: 3.2  
//
// Date: 07/04/06
//

package jaus.message.command;
import jaus.message.*;

public class StandbyMessage extends JausMessage
{    
	private static final int COMMAND_CODE = STANDBY;
	private static final int MAX_DATA_SIZE_BYTES = 0;
    
	public StandbyMessage()
	{
		super();
	}
	
	public StandbyMessage(byte[] buffer)
	{
		super(buffer, 0);
	}
	
	public StandbyMessage(byte[] buffer, int index)
	{
	    super(buffer, index);
	}

	public StandbyMessage(JausMessage jausMessage)
	{
	    super(jausMessage);
	}
	
	public void setCommandCode(int commandCode)
	{
	    this.commandCode = COMMAND_CODE;
	}	
	
}