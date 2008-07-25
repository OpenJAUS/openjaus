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
// File:		node.c 
// Version:		0.4 alpha
// Written by:	Tom Galluzzo (galluzzt@ufl.edu)
// Date:		07/01/2005
// Description:	This file contains the main code for implementing a CIMAR JAUS component

#include <cimar.h>
#include <cimar/jaus.h>
#include <curses.h>
#include <ctype.h>
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

#include "node.h"
#include "exCmpt.h"

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

#define DEFAULT_STRING_LENGTH 128

#define KEYBOARD_LOCK_TIMEOUT_SEC	60.0

static int mainRunning = FALSE;

// Refresh screen in curses mode
void updateScreen(int keyboardLock, int keyPress)
{
	int row = 0;
	int col = 0;
	char string[128] = {0};
	
	clear();

	mvprintw(row++,col,"Keyboard Lock:	%s", keyboardLock?"ON, Press ctrl+L to unlock":"OFF, Press ctrl+L to lock"); row++;
	row++;
	
	jausAddressToString(exCmptGetAddress(), string);
	mvprintw(row++,col,"CMPT Address:		%s", string);
	mvprintw(row++,col,"CMPT State:		%s", jausStateGetString( exCmptGetState() ) );
	mvprintw(row++,col,"CMPT Update Rate:	%5.2f", exCmptGetUpdateRate());	
	row++;
	mvprintw(row++,col,"VSS Service Connection:\t%s", exCmptGetVssScStatus()? "Active" : "Inactive");
	mvprintw(row++,col,"VSS Velocity X (Mps):\t%0.2f", exCmptGetVss()? exCmptGetVss()->velocityXMps : 0.0);

	move(24,0);
	refresh();
}

int main(int argCount, char **argString)
{
	int i = 0;
	int choice=0;
	int verbose = FALSE;
	int keyboardLock = FALSE;
	int debugLevel = 0;
	double keyboardLockTime = getTimeSeconds() + KEYBOARD_LOCK_TIMEOUT_SEC;
	struct termios newTermio;
	struct termios storedTermio;
	FILE *logFile = NULL;
	char logFileStr[DEFAULT_STRING_LENGTH] = "";
	char timeString[DEFAULT_STRING_LENGTH] = "";
	char debugLogicString[DEFAULT_STRING_LENGTH] = "";
	time_t timeStamp;
	
	//Get and Format Time String
	time(&timeStamp);
	strftime(timeString, DEFAULT_STRING_LENGTH-1, "%m-%d-%Y %X", localtime(&timeStamp));

	system("clear");

	printf("main: CIMAR Core Executable: %s\n", timeString);

	// Make directory and set permisions on CIMAR Directory to fully read, write, execute
	if(mkdir("/var/log/CIMAR/", 0777) < 0) 
	{
		if(errno != EEXIST)
		{
			perror("main: Error");
			return -1;
		}
	}

	for(i=1; i<argCount; i++)
	{
		if(argString[i][0] == '-')
		{
			switch(argString[i][1])
			{
				case 'v':
					verbose = TRUE;
					setLogVerbose(TRUE);
					break;
					
				case 'd':
					if(argString[i][2] == '+') 
					{
						setDebugLogic(DEBUG_GREATER_THAN);
						sprintf(debugLogicString, "Greater than or equal to: ");
						if(argString[i][3] >= '0' && argString[i][3] <= '9')
						{
							debugLevel = atoi(&argString[i][3]);
						}
						else
						{
							printf("main: Incorrect use of arguments\n");
							break;
						}
					}
					else if(argString[i][2] == '-')
					{
						setDebugLogic(DEBUG_LESS_THAN);
						sprintf(debugLogicString, "Less than or equal to: ");
						if(argString[i][3] >= '0' && argString[i][3] <= '9')
						{
							debugLevel = atoi(&argString[i][3]);
						}
						else
						{
							printf("main: Incorrect use of arguments\n");
							break;
						}
					}
					else if(argString[i][2] == '=')
					{
						setDebugLogic(DEBUG_EQUAL_TO);
						if(argString[i][3] >= '0' && argString[i][3] <= '9')
						{
							debugLevel = atoi(&argString[i][3]);
						}
						else
						{
							printf("main: Incorrect use of arguments\n");
							break;
						}
					}
					else if(argString[i][2] >= '0' && argString[i][2] <= '9')
					{
						debugLevel = atoi(&argString[i][2]);
					}
					else
					{
						printf("main: Incorrect use of arguments\n");
						break;
					}
					printf("main: Switching to debug level: %s%d\n", debugLogicString, debugLevel);
					setDebugLevel(debugLevel);
					break;
					
				case 'l':
					if(argCount > i+1 && argString[i+1][0] != '-')
					{
						logFile = fopen(argString[i+1], "w");
						if(logFile != NULL)
						{
							fprintf(logFile, "CIMAR %s Log -- %s\n", argString[0], timeString);
							setLogFile(logFile);
						}
						else printf("main: Error creating log file, switching to default\n");
					}
					else
					{
						printf("main: Incorrect use of arguments\n");
					}
					break;

				default:
					printf("main: Incorrect use of arguments\n");
					break;
			}
		}
	}

	if(logFile == NULL)
	{
		i = strlen(argString[0]) - 1;
		while(i>0 && argString[0][i-1] != '/') i--;
				
		sprintf(logFileStr, "/var/log/CIMAR/%s.log", &argString[0][i]);
		printf("main: Creating log: %s\n", logFileStr);
		logFile = fopen(logFileStr, "w");
		if(logFile != NULL)
		{
			fprintf(logFile, "CIMAR %s Log -- %s\n", argString[0], timeString);
			setLogFile(logFile);
		}
		else printf("main: ERROR: Could not create log file\n");
		// BUG: Else pError here
	}
		
	cDebug(1, "main: Starting Up %s Node Software\n", nodeGetName());
	if(nodeStartup())
	{
		cError("main: %s Node Startup failed\n", nodeGetName());
		cDebug(1, "main: Exiting %s Node Software\n", nodeGetName());
		return 0;
	}

	if(verbose)
	{
		tcgetattr(0,&storedTermio);
		memcpy(&newTermio,&storedTermio,sizeof(struct termios));
		
		// Disable canonical mode, and set buffer size to 0 byte(s)
		newTermio.c_lflag &= (~ICANON);
		newTermio.c_lflag &= (~ECHO);
		newTermio.c_cc[VTIME] = 0;
		newTermio.c_cc[VMIN] = 0;
		tcsetattr(0,TCSANOW,&newTermio);
	}
	else
	{	
		// Start up Curses window
		initscr();
		cbreak();
		noecho();
		nodelay(stdscr, 1);	// Don't wait at the getch() function if the user hasn't hit a key
		keypad(stdscr, 1); // Allow Function key input and arrow key input
	}
	
	mainRunning = TRUE;
	
	while(mainRunning)
	{
		if(verbose)
		{
			choice = getc(stdin);
		}
		else // Not in verbose mode
		{
			choice = getch(); // Get the key that the user has selected
			updateScreen(keyboardLock, choice);		
		}

		if(choice > -1)
		{
			keyboardLockTime = getTimeSeconds() + KEYBOARD_LOCK_TIMEOUT_SEC;
			if(choice == 12) // 12 == 'ctrl + L'
			{
				keyboardLock = !keyboardLock;
			}
		}
		else
		{
			if(getTimeSeconds() > keyboardLockTime)
			{
				keyboardLock = TRUE;
			}
		}
		
		
		if(!keyboardLock)
		{
			switch(choice)
			{
				// USER: Add key press event options here

				case 27: // Escape Key Pressed
					mainRunning = FALSE;
					break;
					
				default:
					break;
			}
		}
				
		usleep(50000);
	}
	
	if(verbose)
	{
		tcsetattr(0,TCSANOW,&storedTermio);
	}
	else
	{
		// Stop Curses
		clear();
		endwin();
	}
	
	cDebug(1, "main: Shutting Down %s Node Software\n", nodeGetName());
	nodeShutdown();
	
	if(logFile != NULL)
	{
		fclose(logFile);
	}
	
	return 0;
}
