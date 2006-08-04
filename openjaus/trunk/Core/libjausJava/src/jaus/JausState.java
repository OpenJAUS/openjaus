package jaus;

public class JausState
{
	public static final int UNDEFINED	=	-1;
	public static final int UNKNOWN 	=	-1;
	public static final int INVALID 	= 	-1;

	public static final int INITIALIZE 	=	0;
	public static final int READY 		=	1;
	public static final int STANDBY 	=	2;
	public static final int SHUTDOWN 	=	3;
	public static final int FAILURE 	=	4;
	public static final int EMERGENCY 	=	5;
	
	int value;
	
	public JausState()
	{
		value = UNKNOWN;
	}

	public int getValue()
	{
		return value;
	}
	
	public void setValue(int value)
	{
		if(value > UNDEFINED && value <= EMERGENCY)
			this.value = value;
	}
	
	public String toString()
	{
		switch(value)
		{
			case INITIALIZE:
				return "Initialize";
				
			case READY:
				return "Ready";

			case STANDBY:
				return "Standby";

			case SHUTDOWN:
				return "Shutdown";

			case FAILURE:
				return "Failure";
			
			case EMERGENCY:
				return "Emergency";

			case UNDEFINED:
				return "Undefined/Unknown/Invalid";
				
			default:
				return "Undefined/Unknown/Invalid";
		}
	}
	
	public int hashCode()
	{
		return value;
	}
	
	public boolean equals(Object comparisionValue)
	{
		return value == ((JausState)comparisionValue).getValue();
	}
}
