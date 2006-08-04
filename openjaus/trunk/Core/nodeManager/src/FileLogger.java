// File Name: FileLogger.java
//
// Written By: Tom Galluzzo (galluzzo AT gmail DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This class manages writting all logged information to a log file.

import java.io.*;
import java.lang.reflect.Array;

public class FileLogger extends Thread
{
	DataRepository dataRepository;
	String loggingList[] = {
//							"MessageRouter Message Block",
//							"MessageRouter Message Count", 
							"Messages Received Count",
							"Messages Sent Count",
							"Node Send Queue Average Size",
							"Node Send Queue Max Size",
							"Node Receive Queue Average Size",
							"Node Receive Queue Max Size",
							"Component Receive Queue Average Size",
							"Component Receive Queue Max Size"};
	
	FileOutputStream output;
	FileWriter fileWriter;
	
	public FileLogger(DataRepository dataRepository, String fileString) throws IOException
	{
		this.dataRepository = dataRepository;
		fileWriter = new FileWriter(fileString);
		
		String buffer = new String();
		
		buffer =  loggingList[0];
		for(int i = 1; i < Array.getLength(loggingList); i++)
		{
			buffer += "," + loggingList[i];
		}
		buffer += "\n";
		fileWriter.write(buffer);
		fileWriter.flush();
	}
	
	public void logData(DataRepository repository) throws IOException
	{
		fileWriter.write(getDataString(repository));
		fileWriter.flush();
	}
	
	public String getDataString(DataRepository repository)
	{
		String buffer = new String();
	
		buffer =  repository.get(loggingList[0]).toString();
		for(int i = 1; i < Array.getLength(loggingList); i++)
		{
			buffer += "," + repository.get(loggingList[i]).toString();
		}
		buffer += "\n";

		return buffer;
	}

	public void run()
	{
		while(NodeManager.isRunning())
		{
			try
			{
				sleep(1000);
				logData(dataRepository);
			}
			catch(Exception e)
			{
				System.out.println("FileLogger Exception: " + e);
			}
			
		}
	    System.out.println("FileLogger: Shutting down");			
	}
	
}


