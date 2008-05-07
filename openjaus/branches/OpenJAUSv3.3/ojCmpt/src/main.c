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
// 
// Version:		3.3
//
// Written by:	Tom Galluzzo (galluzzo AT gmail DOT com) and Danny Kent (jaus AT dannykent DOT com)
//
// Date:		04/30/08
//
// Description:	This file contains the main code for implementing a CIMAR JAUS component

#include <ctype.h>
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

#include <jaus.h>
#include <openJaus.h>

#if defined(WIN32)
	#undef MOUSE_MOVED	// conflict between PDCURSES and WIN32
	#include <curses.h>
	#include <windows.h>
	#define SLEEP_MS(x) Sleep(x)
	#define CLEAR "cls"
#elif defined(__linux) || defined(linux) || defined(__linux__) || defined(__APPLE__)
	#include <ncurses.h>
	#include <termios.h>
	#include <unistd.h>
	#define CLEAR "clear"
	#define SLEEP_MS(x) usleep(x*1000)
#endif

#include "cmpt.h"

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

#define DEFAULT_STRING_LENGTH 128
#define KEYBOARD_LOCK_TIMEOUT_SEC	60.0

static int mainRunning = FALSE;
static int verbose = FALSE;
static int keyboardLock = FALSE;
static FILE *logFile = NULL;
static char timeString[DEFAULT_STRING_LENGTH] = "";
char logFileStr[DEFAULT_STRING_LENGTH] = "";

// Operating specific console handles
#if defined(WIN32)
	static HANDLE handleStdin;
#elif defined(__linux) || defined(linux) || defined(__linux__) || defined(__APPLE__)
	static struct termios newTermio;
	static struct termios storedTermio;
#endif

// Refresh screen in curses mode
void updateScreen(int keyboardLock, int keyPress)
{
	int row = 0;
	int col = 0;
	char string[128] = {0};
	
	clear();

	mvprintw(row++,col,"Keyboard Lock:	%s", keyboardLock?"ON, Press ctrl+L to unlock":"OFF, Press ctrl+L to lock"); row++;
	row++;
	
	jausAddressToString(cmptGetAddress(), string);
	mvprintw(row++,col,"CMPT Address:		%s", string);
	mvprintw(row++,col,"CMPT State:		%s", jausStateGetString( cmptGetState() ) );
	mvprintw(row++,col,"CMPT Update Rate:	%5.2f", cmptGetUpdateRate());	

	move(24,0);
	refresh();
}

void parseUserInput(char input)
{
	switch(input)
	{
		case 12: // 12 == 'ctrl + L'
			keyboardLock = !keyboardLock;
			break;
		
		case 27: // 27 
			if(!keyboardLock)
			{
				mainRunning = FALSE;
			}
			break;
		
		default:
			break;
	}
	return;
}
void parseCommandLine(int argCount, char **argString)
{
	int i = 0;
	int debugLevel = 0;
	char debugLogicString[DEFAULT_STRING_LENGTH] = "";
	
	for(i=1; i<argCount; i++)
	{
		if(argString[i][0] == '-')
		{
			switch(argString[i][1])
			{
				case 'v':
					verbose = TRUE;
					//setLogVerbose(TRUE);
					break;
					
				case 'd':
					if(argString[i][2] == '+') 
					{
						//setDebugLogic(DEBUG_GREATER_THAN);
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
						//setDebugLogic(DEBUG_LESS_THAN);
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
						//setDebugLogic(DEBUG_EQUAL_TO);
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
					//setDebugLevel(debugLevel);
					break;
					
				case 'l':
					if(argCount > i+1 && argString[i+1][0] != '-')
					{
						logFile = fopen(argString[i+1], "w");
						if(logFile != NULL)
						{
							fprintf(logFile, "CIMAR %s Log -- %s\n", argString[0], timeString);
							//setLogFile(logFile);
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
}

void setupTerminal()
{
	if(verbose)
	{
#if defined(__linux) || defined(linux) || defined(__linux__) || defined(__APPLE__)
		tcgetattr(0,&storedTermio);
		memcpy(&newTermio,&storedTermio,sizeof(struct termios));
		
		// Disable canonical mode, and set buffer size to 0 byte(s)
		newTermio.c_lflag &= (~ICANON);
		newTermio.c_lflag &= (~ECHO);
		newTermio.c_cc[VTIME] = 0;
		newTermio.c_cc[VMIN] = 0;
		tcsetattr(0,TCSANOW,&newTermio);
#elif defined(WIN32)
		// Setup the console window's input handle
		handleStdin = GetStdHandle(STD_INPUT_HANDLE); 
#endif
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
}

void cleanupConsole()
{
	if(verbose)
	{
#if defined(__linux) || defined(linux) || defined(__linux__) || defined(__APPLE__)
		tcsetattr(0,TCSANOW,&storedTermio);
#endif
	}
	else
	{
		// Stop Curses
		clear();
		endwin();
	}
}

char getUserInput()
{
	char retVal = FALSE;
	int choice;
	int i = 0;

	if(verbose)
	{
#if defined(WIN32)
    INPUT_RECORD inputEvents[128];
	DWORD eventCount;

		// See how many events are waiting for us, this prevents blocking if none
		GetNumberOfConsoleInputEvents(handleStdin, &eventCount);
		
		if(eventCount > 0)
		{
			// Check for user input here
			ReadConsoleInput( 
					handleStdin,		// input buffer handle 
					inputEvents,		// buffer to read into 
					128,				// size of read buffer 
					&eventCount);		// number of records read 
		}
 
	    // Parse console input events 
        for (i = 0; i < (int) eventCount; i++) 
        {
            switch(inputEvents[i].EventType) 
            { 
				case KEY_EVENT: // keyboard input 
					parseUserInput(inputEvents[i].Event.KeyEvent.uChar.AsciiChar);
					retVal = TRUE;
					break;
				
				default:
					break;
			}
		}
#elif defined(__linux) || defined(linux) || defined(__linux__) || defined(__APPLE__)
		choice = getc(stdin);
		if(choice > -1)
		{
			parseUserInput(choice);
			retVal = TRUE;
		}
#endif
	}
	else
	{
		choice = getch(); // Get the key that the user has selected
		updateScreen(keyboardLock, choice);
		if(choice > -1)
		{
			parseUserInput(choice);
			retVal = TRUE;
		}
	}

	return retVal;
}


int main(int argCount, char **argString)
{
	int i = 0;
	char keyPressed = FALSE;
	int keyboardLock = FALSE;
	double keyboardLockTime = getTimeSeconds() + KEYBOARD_LOCK_TIMEOUT_SEC;
	time_t timeStamp;
	char logFileStr[128] = {0};
	
	//Get and Format Time String
	time(&timeStamp);
	strftime(timeString, DEFAULT_STRING_LENGTH-1, "%m-%d-%Y %X", localtime(&timeStamp));

	parseCommandLine(argCount, argString);
	system(CLEAR);

	printf("main: CIMAR Core Executable: %s\n", timeString);

	if(logFile == NULL)
	{
		i = (int) strlen(argString[0]) - 1;
		while(i > 0 && argString[0][i-1] != '/') i--;
				
		sprintf(logFileStr, "%s.log", &argString[0][i]);
		printf("main: Creating log: %s\n", logFileStr);
		logFile = fopen(logFileStr, "w");
		if(logFile != NULL)
		{
			fprintf(logFile, "CIMAR %s Log -- %s\n", argString[0], timeString);
		}
		else 
		{
			printf("main: ERROR: Could not create log file\n");
			// BUG: Else pError here
		}
	}

	printf("main: Starting OpenJAUS CMPT: %s\n", timeString);
	if(cmptStartup())
	{
		printf("main: CMPT Startup failed\n");
		printf("main: Exiting CMPT\n");
#if defined(WIN32)
		system("pause");
#else
		printf("Press ENTER to exit\n");
		getch();
#endif
		return 0;
	}

	setupTerminal();

	mainRunning = TRUE;
	
	while(mainRunning)
	{
		keyPressed = getUserInput();

		if(keyPressed)
		{
			keyboardLockTime = getTimeSeconds() + KEYBOARD_LOCK_TIMEOUT_SEC;		
		}
		else if(getTimeSeconds() > keyboardLockTime)
		{
				keyboardLock = TRUE;
		}

		//if(verbose)
		//{
		//	choice = getc(stdin);
		//}
		//else // Not in verbose mode
		//{
		//	choice = getch(); // Get the key that the user has selected
		//	updateScreen(keyboardLock, choice);		
		//}
						
		SLEEP_MS(1000);
	}

	cleanupConsole();
	
	//cDebug(1, "main: Shutting Down %s Node Software\n", simulatorGetName());
	cmptShutdown();
	
	if(logFile != NULL)
	{
		fclose(logFile);
	}
	
	return 0;
}
