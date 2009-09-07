/*****************************************************************************
 *  Copyright (c) 2008, University of Florida
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
// File Name: ojnmService.cpp
//
// Written By: Danny Kent (jaus AT dannykent DOT com)
//
// Version: 3.3.0b
//
// Date: 09/08/09
//
// Description: This file creates a version of the OpenJAUS node manager which
//              can be used as a service daemon in linux.
//				This file is based on a skeleton found online at:
//				http://www.netzmafia.de/skripten/unix/linux-daemon-howto.html

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>

#include <openJaus.h>

// We need an eventHandler object for the NodeManager
class MyHandler : public EventHandler
{
private:
	FILE *outputFile;

public:
	MyHandler(FILE *file)
	{
		this->outputFile = file;
	}
	~MyHandler()
	{
	}

	void handleEvent(NodeManagerEvent *e)
	{
		SystemTreeEvent *treeEvent;
		ErrorEvent *errorEvent;
		JausMessageEvent *messageEvent;
		DebugEvent *debugEvent;
		ConfigurationEvent *configEvent;

		switch(e->getType())
		{
			case NodeManagerEvent::SystemTreeEvent:
				treeEvent = (SystemTreeEvent *)e;
				fprintf(outputFile, "%s\n", treeEvent->toString().c_str());
				fflush(outputFile);
				delete e;
				break;

			case NodeManagerEvent::ErrorEvent:
				errorEvent = (ErrorEvent *)e;
				fprintf(outputFile, "%s\n", errorEvent->toString().c_str());
				fflush(outputFile);
				delete e;
				break;

			case NodeManagerEvent::JausMessageEvent:
				messageEvent = (JausMessageEvent *)e;
				// If you turn this on, the system gets spam-y this is very useful for debug purposes
				if(messageEvent->getJausMessage()->commandCode != JAUS_REPORT_HEARTBEAT_PULSE)
				{
					//printf("%s\n", messageEvent->toString().c_str());
					//fflush(outputFile);
				}
				else
				{
					//printf("%s\n", messageEvent->toString().c_str());
					//fflush(outputFile);
				}
				delete e;
				break;

			case NodeManagerEvent::DebugEvent:
				debugEvent = (DebugEvent *)e;
				//printf("%s\n", debugEvent->toString().c_str());
				//fflush(outputFile);
				delete e;
				break;

			case NodeManagerEvent::ConfigurationEvent:
				configEvent = (ConfigurationEvent *)e;
				fprintf(outputFile, "%s\n", configEvent->toString().c_str());
				fflush(outputFile);
				delete e;
				break;

			default:
				fprintf(outputFile, "Unknown Node Manager Event: %s\n", e->toString().c_str());
				fflush(outputFile);
				delete e;
				break;
		}
	}
};

int main(void)
{
	/* Our process ID and Session ID */
	pid_t pid, sid;

	/* Fork off the parent process */
	pid = fork();
	if (pid < 0)
	{
		exit(EXIT_FAILURE);
	}

	/* If we got a good PID, then we can exit the parent process. */
	if (pid > 0)
	{
		exit(EXIT_SUCCESS);
	}

	/* Change the file mode mask */
	umask(0);

	/* Open any logs here */
	FILE *logFile;
	logFile = fopen("/var/log/ojNodeManager.log", "w+");
	if(logFile == NULL)
	{
		// Log error
		exit(EXIT_FAILURE);
	}

	/* Create a new SID for the child process */
	/* this is a unique session ID */
	sid = setsid();
	if (sid < 0)
	{
		/* Log the failure */
		fprintf(logFile, "Did not get a valid SID value\n");
		exit(EXIT_FAILURE);
	}

	/* Change the current working directory */
	if ((chdir("/")) < 0)
	{
		/* Log the failure */
		fprintf(logFile, "Could not change working directory to '/'\n");
		exit(EXIT_FAILURE);
	}

	/* Close out the standard file descriptors */
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);

	/* Daemon-specific initialization goes here */
	MyHandler *handler = new MyHandler(logFile);
	FileLoader *configData = new FileLoader();

	// Tests that the config file is valid
	if(!configData->load_cfg("/etc/ojNodeManager.conf"))
	{
		// "/etc/ojNodeManager.conf" not opened correctly
		// For backwards compatibility, we'll try to open "/etc/nodeManager.conf"
		if(!configData->load_cfg("/etc/nodeManager.conf"))
		{
			// Neither file loaded properly!
			// Log failure
			fprintf(logFile, "Could not open OpenJAUS Node Manager configuration file. Check that it exists? \"/etc/ojNodeManager.conf\"\n");
			exit(EXIT_FAILURE);
		}
	}

	printf("Starting OpenJAUS Node Manager Service Version %s (JULY 9, 2008)\n", OJ_NODE_MANAGER_VERSION);
	fflush(logFile);

	// Our Node Manager object
	NodeManager *nm;

	// Create our NodeManager object
	try
	{
		nm = new NodeManager(configData, handler);
	}
	catch(char *exceptionString)
	{
		// Log exception to the log file
		fprintf(logFile, "ojNodeManager Exception: %s\n", exceptionString);
		fprintf(logFile, "Terminating Program...\n");
		exit(EXIT_FAILURE);
	}
	catch(...)
	{
		fprintf(logFile, "Node Manager Construction Failed. Terminating Program...\n");
		exit(EXIT_FAILURE);
	}

	/* The Big Loop */
	while(true)
	{
	   /* Do some task here ... */

	   sleep(1); /* wait 30 seconds */
	}

	exit(EXIT_SUCCESS);
}
