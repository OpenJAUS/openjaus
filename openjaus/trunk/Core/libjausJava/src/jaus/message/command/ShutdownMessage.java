//File Name: ShutdownMessage.java
//
// Written By: Tom Galluzzo (galluzzo@gmail.com)
//
// Version: 3.2  
//
// Date: 07/04/06
//

package jaus.message.command;
import jaus.message.*;

public class ShutdownMessage extends JausMessage
{    
	private static final int COMMAND_CODE = SHUTDOWN;
	private static final int MAX_DATA_SIZE_BYTES = 0;
   
	public ShutdownMessage()
	{
		super();
	}
	
	public ShutdownMessage(byte[] buffer)
	{
		super(buffer, 0);
	}
	
	public ShutdownMessage(byte[] buffer, int index)
	{
	    super(buffer, index);
	}

	public ShutdownMessage(JausMessage jausMessage)
	{
	    super(jausMessage);
	}
	
	public void setCommandCode(int commandCode)
	{
	    this.commandCode = COMMAND_CODE;
	}	
	
}