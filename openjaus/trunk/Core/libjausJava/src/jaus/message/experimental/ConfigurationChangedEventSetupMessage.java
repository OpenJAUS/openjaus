/**
 * @author Danny Kent (jaus@dannykent.com)
 * @version 0.1
 * @date: 02/14/05
 */

package jaus.message.experimental;
import jaus.message.*;
import jaus.type.*;

public class ConfigurationChangedEventSetupMessage extends JausMessage
{
	private static final int CONFIGURATION_CHANGED_EVENT_SETUP = 0xD6A8;
	private static final int COMMAND_CODE = CONFIGURATION_CHANGED_EVENT_SETUP;
	private static final int MAX_DATA_SIZE_BYTES = 1;

	//Message Fields
	JausByte notificationType;
	
	public ConfigurationChangedEventSetupMessage()
	{
		super();
		setUserDefinedFlag(EXPERIMENTAL_MESSAGE);

		data = new byte[MAX_DATA_SIZE_BYTES];

		notificationType = new JausByte(0);
	}

	public ConfigurationChangedEventSetupMessage(byte[] buffer)
	{
	    setFromJausBuffer(buffer, 0);
	}

	public ConfigurationChangedEventSetupMessage(byte[] buffer, int index)
	{
	    setFromJausBuffer(buffer, index);
	}

	public ConfigurationChangedEventSetupMessage(JausMessage jausMessage)
	{
	    super(jausMessage);
		int dataIndex = 0;
		notificationType = new JausByte(data, dataIndex);
	}

	public void setCommandCode(int commandCode)
	{
	    this.commandCode = COMMAND_CODE;
	}	
	
	public boolean setNotificationType(int value)
	{
		if(value < 256 && value > -1)
		{
			notificationType.setValue(value);
			return true;
		}
		else
			return false;
	}

	public JausByte getNotificationType()
	{
		return notificationType;
	}

	// Takes a data UDP or regular JAUS buffer and unpacks it into the header data structure and the data attributes
	public boolean setFromJausBuffer(byte[] buffer, int index)
	{
		if(super.setFromJausBuffer(buffer, index))
		{
		    int dataIndex = 0;
		    notificationType = new JausByte(data, dataIndex);
		    return true;
		}
		else
		{
		    return false;
		}
	}
	
	// Takes the header and data byte array and packs them into a data buffer
	// This method needs to be overridden for all subclasses of JausMessage to reflect the correct pack routine
	public boolean toJausBuffer(byte[] buffer, int index)
	{
	    if(super.toJausBuffer(buffer, index))
	    {
			index += HEADER_SIZE_BYTES;
			
			if(notificationType.toJausBuffer(buffer, index))
			{
				index += notificationType.size();
			}
			else return false;
			
			return true;
	    }
	    else
	    {
	        return false;
	    }
	}

	// Overloaded method to accept a buffer and pack this message into its UDP form
	public boolean toJausUdpBuffer(byte[] buffer, int index)
	{
	    if(super.toJausUdpBuffer(buffer, index))
	    {
	    	index += HEADER_SIZE_BYTES + UDP_HEADER_SIZE_BYTES;
			
			if(notificationType.toJausBuffer(buffer, index))
			{
				index += notificationType.size();
			}
			else return false;
			
			return true;
	    }
	    else
	    {
	        return false;
	    }
	}
	
}