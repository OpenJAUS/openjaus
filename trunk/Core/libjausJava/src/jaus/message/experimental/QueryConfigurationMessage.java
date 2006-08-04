/**
 * @author Danny Kent (jaus@dannykent.com)
 * @version 0.1
 * @date: 02/14/05
 */

package jaus.message.experimental;
import jaus.message.*;
import jaus.type.*;

public class QueryConfigurationMessage extends JausMessage
{
	private static final int QUERY_CONFIGURATION = 0xD2A6;
	private static final int COMMAND_CODE = QUERY_CONFIGURATION;
	private static final int MAX_DATA_SIZE_BYTES = 1;

	public static final int SUBSYSTEM_CONFIGURATION 	= 2;
	public static final int NODE_CONFIGURATION	 		= 3;

	//Message Fields
	JausByte queryField;
	
	public QueryConfigurationMessage()
	{
		super();
		setUserDefinedFlag(EXPERIMENTAL_MESSAGE);

		data = new byte[MAX_DATA_SIZE_BYTES];

		queryField = new JausByte(0);
	}

	public QueryConfigurationMessage(byte[] buffer)
	{
	    setFromJausBuffer(buffer, 0);
	}

	public QueryConfigurationMessage(byte[] buffer, int index)
	{
	    setFromJausBuffer(buffer, index);
	}

	public QueryConfigurationMessage(JausMessage jausMessage)
	{
	    super(jausMessage);
		int dataIndex = 0;
		queryField = new JausByte(data, dataIndex);
	}

	public void setCommandCode(int commandCode)
	{
	    this.commandCode = COMMAND_CODE;
	}	
	
	public boolean setQueryField(int value)
	{
		if(value < 4 && value > 1)
		{
			queryField.setValue(value);
			return true;
		}
		else
			return false;
	}

	public JausByte getQueryField()
	{
		return queryField;
	}

	// Takes a data UDP or regular JAUS buffer and unpacks it into the header data structure and the data attributes
	public boolean setFromJausBuffer(byte[] buffer, int index)
	{
		if(super.setFromJausBuffer(buffer, index))
		{
		    int dataIndex = 0;
		    queryField = new JausByte(data, dataIndex);
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
			
			if(queryField.toJausBuffer(buffer, index))
			{
				index += queryField.size();
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
			
			if(queryField.toJausBuffer(buffer, index))
			{
				index += queryField.size();
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