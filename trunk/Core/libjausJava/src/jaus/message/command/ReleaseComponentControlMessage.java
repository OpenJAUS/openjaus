//File Name: ReleaseComponentControlMessage.java
//
// Written By: Tom Galluzzo (galluzzo@gmail.com)
//
// Version: 3.2  
//
// Date: 07/04/06
//

package jaus.message.command;
import jaus.message.*;

public class ReleaseComponentControlMessage extends JausMessage
{    
	private static final int COMMAND_CODE = RELEASE_COMPONENT_CONTROL;
	private static final int MAX_DATA_SIZE_BYTES = 0;
   
	public ReleaseComponentControlMessage()
	{
		super();
	}
	
	public ReleaseComponentControlMessage(byte[] buffer)
	{
		super(buffer, 0);
	}
	
	public ReleaseComponentControlMessage(byte[] buffer, int index)
	{
	    super(buffer, index);
	}

	public ReleaseComponentControlMessage(JausMessage jausMessage)
	{
	    super(jausMessage);
	}
	
	public void setCommandCode(int commandCode)
	{
	    this.commandCode = COMMAND_CODE;
	}	
	
}