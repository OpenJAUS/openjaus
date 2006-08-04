/**
 * @author Tom Galluzzo (galluzzo@gmail.com)
 * @version 0.3
 * @date: 03/24/06
 */

package jaus.message.experimental;
import jaus.message.*;
import jaus.type.*;

public class QueryServicesMessage extends JausMessage
{
	private static final int QUERY_SERVICES = 0xD2A7;
	private static final int COMMAND_CODE = QUERY_SERVICES;
	private static final int MAX_DATA_SIZE_BYTES = 0;

	//Message Fields
	
	public QueryServicesMessage()
	{
		super();
		setUserDefinedFlag(EXPERIMENTAL_MESSAGE);
	}

	public QueryServicesMessage(byte[] buffer)
	{
		super(buffer, 0);
		setUserDefinedFlag(EXPERIMENTAL_MESSAGE);
	}

	public QueryServicesMessage(byte[] buffer, int index)
	{
		super(buffer, index);
		setUserDefinedFlag(EXPERIMENTAL_MESSAGE);
	}

	public QueryServicesMessage(JausMessage jausMessage)
	{
	    super(jausMessage);
		setUserDefinedFlag(EXPERIMENTAL_MESSAGE);
	}

	public void setCommandCode(int commandCode)
	{
	    this.commandCode = COMMAND_CODE;
	}	

}