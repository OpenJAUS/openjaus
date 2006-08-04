//File Name: ReportHeartbeatPulseMessage.java
//
// Written By: Tom Galluzzo (galluzzo@gmail.com)
//
// Version: 3.2  
//
// Date: 07/04/06
//

package jaus.message.inform;
import jaus.message.*;

public class ReportHeartbeatPulseMessage extends JausMessage
{
	private static final int COMMAND_CODE = REPORT_HEARTBEAT_PULSE;
	private static final int MAX_DATA_SIZE_BYTES = 0;
    
	public ReportHeartbeatPulseMessage()
	{
		super();
	}
	
	public ReportHeartbeatPulseMessage(byte[] buffer)
	{
		super(buffer, 0);
	}
	
	public ReportHeartbeatPulseMessage(byte[] buffer, int index)
	{
	    super(buffer, index);
	}

	public ReportHeartbeatPulseMessage(JausMessage jausMessage)
	{
	    super(jausMessage);
	}
	
	public void setCommandCode(int commandCode)
	{
	    this.commandCode = COMMAND_CODE;
	}
}