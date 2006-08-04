//File Name: RejectComponentControlMessage.java
//
// Written By: Tom Galluzzo (galluzzo@gmail.com)
//
// Version: 3.2  
//
// Date: 07/04/06
//

package jaus.message.command;
import jaus.message.*;

public class RejectComponentControlMessage extends JausMessage
{    
	private static final int COMMAND_CODE = REJECT_COMPONENT_CONTROL;
	private static final int MAX_DATA_SIZE_BYTES = 0;
   
	public RejectComponentControlMessage()
	{
		super();
	}
	
	public RejectComponentControlMessage(byte[] buffer)
	{
		super(buffer, 0);
	}
	
	public RejectComponentControlMessage(byte[] buffer, int index)
	{
	    super(buffer, index);
	}

	public RejectComponentControlMessage(JausMessage jausMessage)
	{
	    super(jausMessage);
	}
	
	public void setCommandCode(int commandCode)
	{
	    this.commandCode = COMMAND_CODE;
	}	
	
}