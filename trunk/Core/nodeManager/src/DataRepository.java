// File Name: DataRepository.java
//
// Written By: Tom Galluzzo (galluzzo AT gmail DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: Central HashMap location for any NodeManager logged issues

import java.util.*;

public class DataRepository extends HashMap
{
	public DataRepository()
	{
		super();
	}
	
	public Object put(Object key, Object value)
	{
		// TODO: Generate event if necessary
		return super.put(key, value);
	}
}