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


