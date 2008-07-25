/*****************************************************************************
 *  Copyright (c) 2006, University of Florida.
 *  All rights reserved.
 *  
 *  This file is part of OpenJAUS.  OpenJAUS is distributed under the BSD 
 *  license.  See the LICENSE file for details.
 * 
 *  Redistribution and use in source and binary forms, with or without 
 *  modification, are permitted provided that the following conditions 
 *  are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer in the documentation and/or other materials provided
 *       with the distribution.
 *     * Neither the name of the University of Florida nor the names of its 
 *       contributors may be used to endorse or promote products derived from 
 *       this software without specific prior written permission.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
 *   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
 *   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR 
 *   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
 *   OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, 
 *   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY 
 *   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 ****************************************************************************/
package openjaus.libjaus;

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
