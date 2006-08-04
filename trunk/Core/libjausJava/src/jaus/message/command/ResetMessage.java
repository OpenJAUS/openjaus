//File Name: ResetMessage.java
//
// Written By: Tom Galluzzo (galluzzo@gmail.com)
//
// Version: 3.2  
//
// Date: 07/04/06
//

package jaus.message.command;
import jaus.message.*;

public class ResetMessage extends JausMessage
{    
	private static final int COMMAND_CODE = RESET;
	private static final int MAX_DATA_SIZE_BYTES = 0;
    
	public ResetMessage()
	{
		super();
	}
	
	public ResetMessage(byte[] buffer)
	{
		super(buffer, 0);
	}
	
	public ResetMessage(byte[] buffer, int index)
	{
	    super(buffer, index);
	}

	public ResetMessage(JausMessage jausMessage)
	{
	    super(jausMessage);
	}
	
	public void setCommandCode(int commandCode)
	{
	    this.commandCode = COMMAND_CODE;
	}	
	
}