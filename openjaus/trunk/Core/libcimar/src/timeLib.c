// File Name: timeLib.c
//
// Written by: Tom Galluzzo (galluzzo AT gmail DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description:	CIMAR timing library header file

#ifdef __APPLE__

	#include <sys/time.h>
	#include "cimar.h"
	
	double getTimeSeconds(void)
	{
		static struct timeval time;
	
		gettimeofday(&time, NULL);
		
		return (double)time.tv_sec + (double)time.tv_usec/1.0e6;  
	}
	
#else

	#include <time.h>
	#include "cimar.h"
	
	double getTimeSeconds(void)
	{
		static struct timespec time;
		
		clock_gettime(CLOCK_REALTIME, &time);
		
		return (double)time.tv_sec + (double)time.tv_nsec/1.0e9;  
	}

#endif
