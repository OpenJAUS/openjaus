//File Name: JausByte.java
//
// Written By: Danny Kent (jaus@dannykent.com)
//
// Version: 3.2  
//
// Date: 07/04/06
//
// This file contains the JausMessageException class and its associated methods  
// JausMessageException is a superclass of various errors and exceptions that may occur during the parsing of message objects


package jaus.message;

public class JausMessageException extends Exception
{
	public JausMessageException()
	{
		super();
	}
	
	public JausMessageException(String s)
	{
		super(s);
	}
}