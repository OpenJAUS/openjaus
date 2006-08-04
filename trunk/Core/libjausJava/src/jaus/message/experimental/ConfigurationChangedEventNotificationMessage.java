/**
 * @author Danny Kent (jaus@dannykent.com)
 * @version 0.1
 * @date: 02/14/05
 */

package jaus.message.experimental;
import jaus.message.*;

public class ConfigurationChangedEventNotificationMessage extends JausMessage
{
	private static final int CONFIGURATION_CHANGED_EVENT_NOTIFICATION = 0xD8A8;
	private static final int COMMAND_CODE = CONFIGURATION_CHANGED_EVENT_NOTIFICATION;
	private static final int MAX_DATA_SIZE_BYTES = 0;

	public ConfigurationChangedEventNotificationMessage()
	{
		super();
		setUserDefinedFlag(EXPERIMENTAL_MESSAGE);

		data = new byte[MAX_DATA_SIZE_BYTES];
	}

	public ConfigurationChangedEventNotificationMessage(byte[] buffer)
	{
	    setFromJausBuffer(buffer, 0);
	}

	public ConfigurationChangedEventNotificationMessage(byte[] buffer, int index)
	{
	    setFromJausBuffer(buffer, index);
	}

	public ConfigurationChangedEventNotificationMessage(JausMessage jausMessage)
	{
	    super(jausMessage);
	}

	public void setCommandCode(int commandCode)
	{
	    this.commandCode = COMMAND_CODE;
	}	
	
	// Takes a data UDP or regular JAUS buffer and unpacks it into the header data structure and the data attributes
	public boolean setFromJausBuffer(byte[] buffer, int index)
	{
		return super.setFromJausBuffer(buffer, index);
	}
	
	// Takes the header and data byte array and packs them into a data buffer
	// This method needs to be overridden for all subclasses of JausMessage to reflect the correct pack routine
	public boolean toJausBuffer(byte[] buffer, int index)
	{
	    return super.toJausBuffer(buffer, index);
	}

	// Overloaded method to accept a buffer and pack this message into its UDP form
	public boolean toJausUdpBuffer(byte[] buffer, int index)
	{
	    return super.toJausUdpBuffer(buffer, index);
	}
	
}