/**
 * @author Tom Galluzzo (galluzzo@gmail.com)
 * @version 0.1
 * @date: 02/14/05
 */

package jaus.message.experimental;
import jaus.message.*;
import jaus.type.*;

public class ConfirmEventMessage extends JausMessage
{
	private static final int COMMAND_CODE = CONFIRM_EVENT;
	private static final int MAX_DATA_SIZE_BYTES = 7;

	public static final int CONFIRMED_UPDATE_RATE_BIT = 0;
	
	//Message Fields
	JausBytePresenceVector presenceVector;	// 1: Presence Vector
	JausUnsignedShort messageCode;			// 2: Command Code of message sent in case of event occurance
	JausByte eventId;						// 3: Event Id
	JausUnsignedShort confirmedUpdateRate;			// 4: For Periodic Events, Scaled UnsignedShort (0, 1092)
	JausByte responseCode;					// 5: Enumeration of Response Types (see above)

	public ConfirmEventMessage()
	{
		super();
		setUserDefinedFlag(EXPERIMENTAL_MESSAGE);

		data = new byte[MAX_DATA_SIZE_BYTES];

		presenceVector = new JausBytePresenceVector();	// 1: Presence Vector
		messageCode = new JausUnsignedShort(0);			// 2: Command Code of the resulting query
		eventId = new JausByte(0);
		confirmedUpdateRate = new JausUnsignedShort(0);	
		responseCode = new JausByte(0);
	}
	
	public ConfirmEventMessage(byte[] buffer)
	{
	    setFromJausBuffer(buffer, 0);
	}
	
	public ConfirmEventMessage(byte[] buffer, int index)
	{
	    setFromJausBuffer(buffer, index);
	}

	public ConfirmEventMessage(JausMessage jausMessage)
	{
		super(jausMessage);
		int dataIndex = 0;

		presenceVector = new JausBytePresenceVector(data, dataIndex) ;
		dataIndex += presenceVector.size();
		
		messageCode = new JausUnsignedShort(data, dataIndex);
		dataIndex += messageCode.size();
		
		eventId = new JausByte(data, dataIndex);
		dataIndex += eventId.size();
		
		if(presenceVector.isBitSet(CONFIRMED_UPDATE_RATE_BIT))
		{
			confirmedUpdateRate = new JausUnsignedShort(data, dataIndex);
			dataIndex += confirmedUpdateRate.size();
		}

		responseCode = new JausByte(data, dataIndex);
		dataIndex += responseCode.size();
	}

	public void setMessageCode(int messageCode)
	{
		this.messageCode = new JausUnsignedShort(messageCode);
	}
	
	public void setResponseCode(int code)
	{
		this.responseCode = new JausByte(code);
	}
	
	public void setCommandCode(int commandCode)
	{
	    this.commandCode = COMMAND_CODE;
	}	

	public boolean setPresenceVectorBit(int bit)
	{
		return presenceVector.setBit(bit);
	}
	
	public boolean clearPresenceVectorBit(int bit)
	{
		return presenceVector.clearBit(bit);
	}
	
	// Takes a data UDP or regular JAUS buffer and unpacks it into the header data structure and the data attributes
	public boolean setFromJausBuffer(byte[] buffer, int index)
	{
		if(super.setFromJausBuffer(buffer, index))
		{
			int dataIndex = 0;

			presenceVector = new JausBytePresenceVector(data, dataIndex) ;
			dataIndex += presenceVector.size();
			
			messageCode = new JausUnsignedShort(data, dataIndex);
			dataIndex += messageCode.size();
			
			eventId = new JausByte(data, dataIndex);
			dataIndex += eventId.size();
			
			if(presenceVector.isBitSet(CONFIRMED_UPDATE_RATE_BIT))
			{
				confirmedUpdateRate = new JausUnsignedShort(data, dataIndex);
				dataIndex += confirmedUpdateRate.size();
			}

			responseCode = new JausByte(data, dataIndex);
			dataIndex += responseCode.size();

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

			if(presenceVector.getPresenceVector().toJausBuffer(buffer, index))
			{
				index += presenceVector.size();
			}
			else
			{
				return false;
			}

			if(messageCode.toJausBuffer(buffer, index))
			{
				index += messageCode.size();
			}
			else
			{
				return false;
			}

			if(eventId.toJausBuffer(buffer, index))
			{
				index += eventId.size();
			}
			else
			{
				return false;
			}

			if(presenceVector.isBitSet(CONFIRMED_UPDATE_RATE_BIT))
			{
				if(confirmedUpdateRate.toJausBuffer(buffer, index))
				{
					index += confirmedUpdateRate.size();
				}
				else
				{
					return false;
				}
			}			

			if(responseCode.toJausBuffer(buffer, index))
			{
				index += responseCode.size();
			}
			else
			{
				return false;
			}
		
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

			if(presenceVector.getPresenceVector().toJausBuffer(buffer, index))
			{
				index += presenceVector.size();
			}
			else
			{
				return false;
			}

			if(messageCode.toJausBuffer(buffer, index))
			{
				index += messageCode.size();
			}
			else
			{
				return false;
			}

			if(eventId.toJausBuffer(buffer, index))
			{
				index += eventId.size();
			}
			else
			{
				return false;
			}

			if(presenceVector.isBitSet(CONFIRMED_UPDATE_RATE_BIT))
			{
				if(confirmedUpdateRate.toJausBuffer(buffer, index))
				{
					index += confirmedUpdateRate.size();
				}
				else
				{
					return false;
				}
			}			

			if(responseCode.toJausBuffer(buffer, index))
			{
				index += responseCode.size();
			}
			else
			{
				return false;
			}
			
			return true;
	    }
	    else
	    {
	        return false;
	    }
	}

}