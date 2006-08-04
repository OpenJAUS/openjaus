/**
 * @author Tom Galluzzo (galluzzo@gmail.com)
 * @version 0.1
 * @date: 02/14/05
 */

package jaus.message.experimental;
import jaus.message.*;
import jaus.type.*;

public class CreateEventMessage extends JausMessage
{
	private static final int COMMAND_CODE = CREATE_EVENT;
	private static final int MAX_DATA_SIZE_BYTES = 4080;

	public static final int EVENT_BOUNDARY_BIT = 0;
	public static final int LIMIT_DATA_TYPE_BIT = 1;
	public static final int LIMIT_DATA_FIELD_BIT = 2;
	public static final int LOWER_LIMIT_BIT = 3;
	public static final int UPPER_LIMIT_BIT = 4;
	public static final int STATE_LIMIT_BIT = 5;
	public static final int REQUESTED_MINIMUM_RATE_BIT = 6;
	public static final int REQUESTED_UPDATE_RATE_BIT = 7;
	
	public static final int PERIODIC = 0;
	public static final int FIRST_CHANGE = 1;
	public static final int EVERY_CHANGE = 2;
	public static final int BOUNDARY_CHANGE = 3;
	public static final int PERIODIC_NO_REPLACEMENT = 4;
	
	//Message Fields
	JausBytePresenceVector presenceVector;	// 1: Presence Vector
	JausUnsignedShort messageCode;			// 2: Command Code of the resulting query
	JausByte eventType;						// 3: Enumeration of Event types
	JausByte eventBoundary;					// 4: Enumeration of Event Boundary Conditions
	JausByte limitDataType;					// 5: Enumeration of data types for fields 7 & 8
	JausByte limitDataField;				// 6: Field from Report for Limit Trigger
	JausEventLimit lowerLimit;				// 7: Lower Event Limit
	JausEventLimit upperLimit;				// 8: Upper Event Limit
	JausEventLimit stateLimit;				// 9: State Event Limit used for Equal Boundary
	JausUnsignedShort requestedMinimumRate;		// 10: For Periodic Events for unchanging value, Scaled UnsignedShort (0, 1092)
	JausUnsignedShort requestedUpdateRate;			// 11: For Periodic Events, Scaled UnsignedShort (0, 1092)
	JausMessage queryMessage;				// 12: Query Message (including header) to use for response

	public CreateEventMessage()
	{
		super();
		setUserDefinedFlag(EXPERIMENTAL_MESSAGE);

		data = new byte[MAX_DATA_SIZE_BYTES];

		presenceVector = new JausBytePresenceVector();	// 1: Presence Vector
		messageCode = new JausUnsignedShort(0);			// 2: Command Code of the resulting query
		eventType = new JausByte(0);						// 3: Enumeration of Event types
		eventBoundary = new JausByte(0);					// 4: Enumeration of Event Boundary Conditions
		limitDataType = new JausByte(0);					// 5: Enumeration of data types for fields 7 & 8
		limitDataField = new JausByte(0);				// 6: Field from Report for Limit Trigger
		lowerLimit = new JausEventLimit();				// 7: Lower Event Limit
		upperLimit = new JausEventLimit();				// 8: Upper Event Limit
		stateLimit = new JausEventLimit();				// 9: State Event Limit used for Equal Boundary
		requestedMinimumRate = new JausUnsignedShort(0);		// 10: For Periodic Events for unchanging value, Scaled UnsignedShort (0, 1092)
		requestedUpdateRate = new JausUnsignedShort(0);		// 11: For Periodic Events, Scaled UnsignedShort (0, 1092)
		queryMessage = new JausMessage();				// 12: Query Message (including header) to use for response
	}
	
	public CreateEventMessage(byte[] buffer)
	{
	    setFromJausBuffer(buffer, 0);
	}
	
	public CreateEventMessage(byte[] buffer, int index)
	{
	    setFromJausBuffer(buffer, index);
	}

	public CreateEventMessage(JausMessage jausMessage)
	{
		super(jausMessage);
		int dataIndex = 0;

		presenceVector = new JausBytePresenceVector(data, dataIndex) ;
		dataIndex += presenceVector.size();
		
		messageCode = new JausUnsignedShort(data, dataIndex);
		dataIndex += messageCode.size();
		
		eventType = new JausByte(data, dataIndex);
		dataIndex += eventType.size();
		
		if(presenceVector.isBitSet(EVENT_BOUNDARY_BIT))
		{
			eventBoundary = new JausByte(data, dataIndex);
			dataIndex += eventBoundary.size();
		}

		if(presenceVector.isBitSet(LIMIT_DATA_TYPE_BIT))
		{
			limitDataType = new JausByte(data, dataIndex);
			dataIndex += limitDataType.size();
		}
	
		if(presenceVector.isBitSet(LIMIT_DATA_FIELD_BIT))
		{
			limitDataField = new JausByte(data, dataIndex);
			dataIndex += limitDataField.size();
		}

		if(presenceVector.isBitSet(LOWER_LIMIT_BIT))
		{
			lowerLimit = new JausEventLimit(data, dataIndex, limitDataType.getValue());
			dataIndex += lowerLimit.size();
		}
	
		if(presenceVector.isBitSet(UPPER_LIMIT_BIT))
		{
			upperLimit = new JausEventLimit(data, dataIndex, limitDataType.getValue());
			dataIndex += upperLimit.size();
		}
	
		if(presenceVector.isBitSet(STATE_LIMIT_BIT))
		{
			stateLimit = new JausEventLimit(data, dataIndex, limitDataType.getValue());
			dataIndex += stateLimit.size();
		}
	
		if(presenceVector.isBitSet(REQUESTED_MINIMUM_RATE_BIT))
		{
			requestedMinimumRate = new JausUnsignedShort(data, dataIndex);
			dataIndex += requestedMinimumRate.size();
		}
	
		if(presenceVector.isBitSet(REQUESTED_UPDATE_RATE_BIT))
		{
			requestedUpdateRate = new JausUnsignedShort(data, dataIndex);
			dataIndex += requestedUpdateRate.size();
		}
		
		queryMessage = new JausMessage(data, dataIndex);
		dataIndex += queryMessage.size();
	
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

    public void setMessageCode(int commandCode)
    {
    	messageCode.setValue(commandCode);
    }

    public int getMessageCode()
    {
    	return messageCode.getValue();
    }    
    
    public void setEventType(int eventType)
    {
    	this.eventType.setValue(eventType);
    }

    public int getEventType()
    {
    	return eventType.getValue();
    }
    
    public void setQueryMessage(JausMessage message)
    {
    	queryMessage = message;
    }
    
    public JausMessage getQueryMessage()
    {
    	return queryMessage;
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
			
			eventType = new JausByte(data, dataIndex);
			dataIndex += eventType.size();
			
			if(presenceVector.isBitSet(EVENT_BOUNDARY_BIT))
			{
				eventBoundary = new JausByte(data, dataIndex);
				dataIndex += eventBoundary.size();
			}

			if(presenceVector.isBitSet(LIMIT_DATA_TYPE_BIT))
			{
				limitDataType = new JausByte(data, dataIndex);
				dataIndex += limitDataType.size();
			}
		
			if(presenceVector.isBitSet(LIMIT_DATA_FIELD_BIT))
			{
				limitDataField = new JausByte(data, dataIndex);
				dataIndex += limitDataField.size();
			}

			if(presenceVector.isBitSet(LOWER_LIMIT_BIT))
			{
				lowerLimit = new JausEventLimit(data, dataIndex, limitDataType.getValue());
				dataIndex += lowerLimit.size();
			}
		
			if(presenceVector.isBitSet(UPPER_LIMIT_BIT))
			{
				upperLimit = new JausEventLimit(data, dataIndex, limitDataType.getValue());
				dataIndex += upperLimit.size();
			}
		
			if(presenceVector.isBitSet(STATE_LIMIT_BIT))
			{
				stateLimit = new JausEventLimit(data, dataIndex, limitDataType.getValue());
				dataIndex += stateLimit.size();
			}
		
			if(presenceVector.isBitSet(REQUESTED_MINIMUM_RATE_BIT))
			{
				requestedMinimumRate = new JausUnsignedShort(data, dataIndex);
				dataIndex += requestedMinimumRate.size();
			}
		
			if(presenceVector.isBitSet(REQUESTED_UPDATE_RATE_BIT))
			{
				requestedUpdateRate = new JausUnsignedShort(data, dataIndex);
				dataIndex += requestedUpdateRate.size();
			}
			
			queryMessage = new JausMessage(data, dataIndex);
			dataIndex += queryMessage.size();
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
		int originalIndex = index;
		
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

			if(eventType.toJausBuffer(buffer, index))
			{
				index += eventType.size();
			}
			else
			{
				return false;
			}

			if(presenceVector.isBitSet(EVENT_BOUNDARY_BIT))
			{
				if(eventBoundary.toJausBuffer(buffer, index))
				{
					index += eventBoundary.size();
				}
				else
				{
					return false;
				}
			}			

			if(presenceVector.isBitSet(LIMIT_DATA_TYPE_BIT))
			{
				if(limitDataType.toJausBuffer(buffer, index))
				{
					index += limitDataType.size();
				}
				else
				{
					return false;
				}
			}			
		
			if(presenceVector.isBitSet(LIMIT_DATA_FIELD_BIT))
			{
				if(limitDataField.toJausBuffer(buffer, index))
				{
					index += limitDataField.size();
				}
				else
				{
					return false;
				}
			}			

			if(presenceVector.isBitSet(LOWER_LIMIT_BIT))
			{
				if(lowerLimit.toJausBuffer(buffer, index))
				{
					index += lowerLimit.size();
				}
				else
				{
					return false;
				}
			}			

			if(presenceVector.isBitSet(UPPER_LIMIT_BIT))
			{
				if(upperLimit.toJausBuffer(buffer, index))
				{
					index += upperLimit.size();
				}
				else
				{
					return false;
				}
			}			
		
			if(presenceVector.isBitSet(STATE_LIMIT_BIT))
			{
				if(stateLimit.toJausBuffer(buffer, index))
				{
					index += stateLimit.size();
				}
				else
				{
					return false;
				}
			}			

			if(presenceVector.isBitSet(REQUESTED_MINIMUM_RATE_BIT))
			{
				if(requestedMinimumRate.toJausBuffer(buffer, index))
				{
					index += requestedMinimumRate.size();
				}
				else
				{
					return false;
				}
			}			
		
			if(presenceVector.isBitSet(REQUESTED_UPDATE_RATE_BIT))
			{
				if(requestedUpdateRate.toJausBuffer(buffer, index))
				{
					index += requestedUpdateRate.size();
				}
				else
				{
					return false;
				}
			}			

			if(queryMessage.toJausBuffer(buffer, index))
			{
				index += queryMessage.size();
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

			if(eventType.toJausBuffer(buffer, index))
			{
				index += eventType.size();
			}
			else
			{
				return false;
			}

			if(presenceVector.isBitSet(EVENT_BOUNDARY_BIT))
			{
				if(eventBoundary.toJausBuffer(buffer, index))
				{
					index += eventBoundary.size();
				}
				else
				{
					return false;
				}
			}			

			if(presenceVector.isBitSet(LIMIT_DATA_TYPE_BIT))
			{
				if(limitDataType.toJausBuffer(buffer, index))
				{
					index += limitDataType.size();
				}
				else
				{
					return false;
				}
			}			
		
			if(presenceVector.isBitSet(LIMIT_DATA_FIELD_BIT))
			{
				if(limitDataField.toJausBuffer(buffer, index))
				{
					index += limitDataField.size();
				}
				else
				{
					return false;
				}
			}			

			if(presenceVector.isBitSet(LOWER_LIMIT_BIT))
			{
				if(lowerLimit.toJausBuffer(buffer, index))
				{
					index += lowerLimit.size();
				}
				else
				{
					return false;
				}
			}			

			if(presenceVector.isBitSet(UPPER_LIMIT_BIT))
			{
				if(upperLimit.toJausBuffer(buffer, index))
				{
					index += upperLimit.size();
				}
				else
				{
					return false;
				}
			}			
		
			if(presenceVector.isBitSet(STATE_LIMIT_BIT))
			{
				if(stateLimit.toJausBuffer(buffer, index))
				{
					index += stateLimit.size();
				}
				else
				{
					return false;
				}
			}			

			if(presenceVector.isBitSet(REQUESTED_MINIMUM_RATE_BIT))
			{
				if(requestedMinimumRate.toJausBuffer(buffer, index))
				{
					index += requestedMinimumRate.size();
				}
				else
				{
					return false;
				}
			}			
		
			if(presenceVector.isBitSet(REQUESTED_UPDATE_RATE_BIT))
			{
				if(requestedUpdateRate.toJausBuffer(buffer, index))
				{
					index += requestedUpdateRate.size();
				}
				else
				{
					return false;
				}
			}			

			if(queryMessage.toJausBuffer(buffer, index))
			{
				index += queryMessage.size();
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