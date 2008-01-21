#include <cimar.h>
#include <cimar/jaus.h>
#include <ncurses.h>
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

#include "simulator.h"
#include "pd.h"
#include "gpos.h"
#include "vss.h"
#include "vehicleSim.h"
#include "wd.h"

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
	char string[256] = {0};
	PointLla vehiclePosLla;
	static int lastChoice = '1';
	
	if(!keyboardLock && keyPress != -1 && keyPress != 27 && keyPress != 12) //Magic Numbers: 27 = ESC, 12 = Ctrl+l
	{
		switch(keyPress)
		{
			case ' ':
				wdToggleRequestControl();
				break;
			
			case 'S':
				wdSetSpeed();
				break;
			
			case 'W':
				wdCreateWaypoint();
				break;
			
			default:
				lastChoice = keyPress;			
		}
	}

	clear();

	mvprintw(row,35,"Keyboard Lock:	%s", keyboardLock?"ON, Press ctrl+L to unlock":"OFF, Press ctrl+L to lock");
	
	mvprintw(row++,0,"+---------------------------+");
	mvprintw(row++,0,"|     Component Menu        |");
	mvprintw(row++,0,"|                           |");
	mvprintw(row++,0,"| 1. Vehicle Sim            |");
	mvprintw(row++,0,"| 2. Primitive Driver       |");
	mvprintw(row++,0,"| 3. GPOS / VSS             |");
	mvprintw(row++,0,"| 4. Waypoint Driver        |");
	mvprintw(row++,0,"|                           |");		
	mvprintw(row++,0,"| ESC to Exit               |");		
	mvprintw(row++,0,"+---------------------------+");

	row = 2;
	col = 40;
	switch(lastChoice)
	{
		case '1':
			mvprintw(row++,col,"Vehicle Simulator");	
			mvprintw(row++,col,"VS Update Rate:	%7.2f", vehicleSimGetUpdateRate());	
			mvprintw(row++,col,"VS Run/Pause:	%s", vehicleSimGetRunPause() == VEHICLE_SIM_PAUSE ? "Pause" : "Run");	
			row++;
			mvprintw(row++,col,"VS Vehicle X:\t%9.2f", vehicleSimGetX());	
			mvprintw(row++,col,"VS Vehicle Y:\t%9.2f", vehicleSimGetY());	
			mvprintw(row++,col,"VS Vehicle H:\t%9.2f", vehicleSimGetH());	
			mvprintw(row++,col,"VS Vehicle Speed: %7.2f", vehicleSimGetSpeed());	
		
			row++;
			mvprintw(row++,col,"VS Throttle:\t%9.2f", vehicleSimGetLinearEffortX());	
			mvprintw(row++,col,"VS Brake:\t%9.2f", vehicleSimGetResistiveEffortX());	
			mvprintw(row++,col,"VS Steering:\t%9.2f", vehicleSimGetRotationalEffort());	
		
			row++;	
			vehiclePosLla = vehicleSimGetPositionLla();
			mvprintw(row++,col,"VS Vehicle Latitude:  %+10.7f", vehiclePosLla? vehiclePosLla->latitudeRadians*DEG_PER_RAD : 0.0);
			mvprintw(row++,col,"VS Vehicle Longitude: %+10.7f", vehiclePosLla? vehiclePosLla->longitudeRadians*DEG_PER_RAD : 0.0);
			break;
	
		case '2':		
			mvprintw(row++,col,"Primitive Driver");	
			mvprintw(row++,col,"PD Update Rate:	%5.2f", pdGetUpdateRate());	
			jausAddressToString(pdGetAddress(), string );	
			mvprintw(row++,col,"PD Address:\t%s", string);	
			mvprintw(row++,col,"PD State:\t%s", jausStateGetString(pdGetState()));	
			
			row++;
			if(pdGetControllerStatus())
			{
				jausAddressToString(pdGetControllerAddress(), string);	
				mvprintw(row++,col,"PD Controller:	%s", string);	
			}
			else
			{
				mvprintw(row++,col,"PD Controller:	None");	
			}
			mvprintw(row++,col,"PD Controller SC:	%s", pdGetControllerScStatus()?"Active":"Inactive");	
			mvprintw(row++,col,"PD Controller State:	%s", jausStateGetString(pdGetControllerState()));	
			
			row++;
			mvprintw(row++,col,"PD Prop Effort X: %0.0lf", pdGetWrenchEffort()? pdGetWrenchEffort()->propulsiveLinearEffortXPercent:-1.0);	
			mvprintw(row++,col,"PD Rstv Effort X: %0.0lf", pdGetWrenchEffort()? pdGetWrenchEffort()->resistiveLinearEffortXPercent:-1.0);	
			mvprintw(row++,col,"PD Rtat Effort Z: %0.0lf", pdGetWrenchEffort()? pdGetWrenchEffort()->propulsiveRotationalEffortZPercent:-1.0);	
			break;
		
		case '3':
			mvprintw(row++,col,"Global Pose Sensor");	
			mvprintw(row++,col,"GPOS Update Rate: %7.2f", gposGetUpdateRate());	
			jausAddressToString(gposGetAddress(), string );	
			mvprintw(row++,col,"GPOS Address:\t    %s", string);	
			mvprintw(row++,col,"GPOS State:\t    %s", jausStateGetString(gposGetState()));	
			mvprintw(row++,col,"GPOS SC State:\t    %s", gposGetScActive()? "Active" : "Inactive");	
			
			row++;
			mvprintw(row++,col,"Velocity State Sensor");	
			mvprintw(row++,col,"VSS Update Rate:  %7.2f", vssGetUpdateRate());	
			jausAddressToString(vssGetAddress(), string );	
			mvprintw(row++,col,"VSS Address:\t    %s", string);	
			mvprintw(row++,col,"VSS State:\t    %s", jausStateGetString(vssGetState()));	
			mvprintw(row++,col,"VSS SC State:\t    %s", vssGetScActive()? "Active" : "Inactive");	
			break;
		
		case '4':
			mvprintw(row++,col,"Waypoint Driver");	
			mvprintw(row++,col,"WD Update Rate: %7.2f", wdGetUpdateRate());	

			jausAddressToString(wdGetAddress(), string);	
			mvprintw(row++,col,"WD Address:\t  %s", string);	
			mvprintw(row++,col,"WD State:\t  %s", jausStateGetString(wdGetState()));
			
			if(wdGetControllerAddress())
			{
				jausAddressToString(wdGetControllerAddress(), string);	
				mvprintw(row++,col,"WD Controller:\t  %s", string);	
			}
			else
			{
				mvprintw(row++,col,"WD Controller:\t  None");	
			}

			row = 11;
			col = 2;
			mvprintw(row++,col,"GPOS SC:\t    %s", wdGetGposScStatus()? "Active" : "Inactive");
			mvprintw(row++,col,"VSS SC:\t    %s", wdGetVssScStatus()? "Active" : "Inactive");
			mvprintw(row++,col,"PD Wrench SC:\t    %s", wdGetPdWrenchScStatus()? "Active" : "Inactive");
			mvprintw(row++,col,"PD State SC:\t    %s", wdGetPdStatusScStatus()? "Active" : "Inactive");
			row++;
			mvprintw(row++,col,"WD Request Control:\t%s", wdGetRequestControl()? "True" : "False");
			mvprintw(row++,col,"(Space to Toggle)");
			mvprintw(row++,col,"WD Control:\t\t%s", wdGetInControlStatus()? "True" : "False");
			mvprintw(row++,col,"PD State:\t\t%s", jausStateGetString(wdGetPdState()));
			
			row = 11;
			col = 40;
			if(wdGetGlobalWaypoint())
			{
				mvprintw(row++,col,"Global Waypoint: (%9.7lf,%9.7lf)", wdGetGlobalWaypoint()->latitudeDegrees, wdGetGlobalWaypoint()->longitudeDegrees);
			}
			else
			{
				mvprintw(row++,col,"Global Waypoint: None");
			}
					
			if(wdGetTravelSpeed())
			{
				mvprintw(row++,col,"Travel Speed: %7.2f", wdGetTravelSpeed()->speedMps);
			}
			else
			{
				mvprintw(row++,col,"Travel Speed: None");				
			}

			mvprintw(row++,col,"dSpeedMps: %7.2f", wdGetDesiredVehicleState()? wdGetDesiredVehicleState()->desiredSpeedMps : 0.0);
			mvprintw(row++,col,"dPhi:      %7.2f", wdGetDesiredVehicleState()? wdGetDesiredVehicleState()->desiredPhiEffort : 0.0);
			
			break;

		default:
			mvprintw(row++,col,"NONE.");	
			break;
	}
	
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
		
	cDebug(1, "main: Starting Up %s Node Software\n", simulatorGetName());
	if(simulatorStartup())
	{
		cError("main: %s Node Startup failed\n", simulatorGetName());
		cDebug(1, "main: Exiting %s Node Software\n", simulatorGetName());
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
				
		usleep(100000);
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
	
	cDebug(1, "main: Shutting Down %s Node Software\n", simulatorGetName());
	simulatorShutdown();
	
	if(logFile != NULL)
	{
		fclose(logFile);
	}
	
	return 0;
}
