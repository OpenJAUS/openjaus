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
// File Name: portLib.h
//
// Written By: David Novick, Jeff Wit, Tom Galluzzo (galluzzo AT gmail DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: Serial port hardware abstraction header file

#include "config.h"
#ifdef HAVE_SGTTY_H
#include <sgtty.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#ifdef HAVE_LINUX_SERIAL_H
#include <linux/serial.h>
#endif

#include "cimar.h"

int portClose(SerialPort port)
{
	return( close(port) );
}

int portCtl(SerialPort port, int request, char *argp)
{
	if(request == FLUSH_IN_BUF) 
	{
    	return tcflush(port, TCIFLUSH);
	}
	else if(request == FLUSH_OUT_BUF) 
	{
    	return tcflush(port, TCOFLUSH);
	}
	else if(request == FLUSH_BOTH_BUF) 
	{
    	return tcflush(port, TCIOFLUSH);
	}
	else return -1;
}

SerialPort portOpen(int whichPort, int baud, char *control)
{
	SerialPort port;
	int bit, stop;
	char par;
	tcflag_t bitFlag[]={CS5, CS6, CS7, CS8}, PAR_CTRL=IGNPAR, BITS, PARITY=0x00, STOP_BIT=0x00, SPEED=B19200;
	struct termios t;
	char device[32];
#ifdef HAVE_LINUX_SERIAL_H
	struct serial_struct serialInfo;
#endif

	sprintf(device,"/dev/ttyS%d",whichPort-1);

	if( (port = open(device, O_RDWR )) == -1 )
	{
		pError("portLib: portOpen");
		return -1;
	} 

	// Strip the control parameters from the control string 
	sscanf( control, "%1d%1c%1d", &bit, &par, &stop );

	// Read in the current port attributes  
	if( tcgetattr(port, &t) == -1 )
	{
		pError("portLib: tcgetattr failed");
		return -1;
	}

#ifdef HAVE_SGTTY_H
	//Get the structure of the serial port
	if (ioctl(port, TIOCGSERIAL, &serialInfo) != 0)
	{
		perror("TIOCGSERIAL ioctl() failed\n");
		return -1;
	}
#endif
	
	// Set the # bits, parity and stop bits 
	if( (bit < 5) || (bit > 8) )
	{
		fprintf(stderr, "portLib: Invalid character bit size:%d [5-8]\n",bit ) ;
		return -1 ;
	}
    
	BITS = bitFlag[bit-5];

	if( par == 'E' || par == 'e' )
	{
		PARITY   = PARENB;  // Even parity 
		PAR_CTRL = INPCK;   // Enable parity check 
	}
	else if( par == 'O' || par == 'o' )
	{
		PARITY   = PARENB | PARODD;    // Odd parity 
		PAR_CTRL = INPCK;              // Enable parity check 
	}

	if( stop == 2 )
		STOP_BIT = CSTOPB;  // Two stop bits 

	// Set the baud rate 
	if( baud == 1200 )
		SPEED = B1200;
	else if( baud == 2400 ) 
		SPEED = B2400;
	else if( baud == 4800 )
		SPEED = B4800;
	else if( baud == 9600 )
		SPEED = B9600;
	else if( baud == 19200 )
		SPEED = B19200;
	else if( baud == 38400 )
		SPEED = B38400;
	else if( baud == 57600 )
	  SPEED = B57600 ;
	else if( baud == 115200)
	  SPEED = B115200;
	else if(baud == 500000)
	{
#ifdef HAVE_LINUX_SERIAL_H
		serialInfo.flags = ASYNC_SPD_CUST;
		serialInfo.custom_divisor = serialInfo.baud_base / 500000 ;
#endif
		SPEED = B38400;
	}
	
#ifdef HAVE_SGTTY_H
	if (ioctl(port, TIOCSSERIAL, &serialInfo) != 0)
	{
		perror("TIOCGSERIAL ioctl() failed\n");
		return -1;
	}
#endif

	// Input Modes
	t.c_iflag &= ~(	BRKINT	|	// Ignore break 
					ISTRIP	|	// Don't mask 
					INLCR	|	// Leave NL 
					ICRNL	|	// Leave CR 
					IGNCR	|	// "      " 
					IXON	|	// No flow control 
					IXOFF 		// No flow control  
					);    

	t.c_iflag |=(	IGNBRK	|	// Ignore break 
					PAR_CTRL 	// Parity control
					);

	// Output Modes
	t.c_oflag &= ~( OPOST );      // No output flags 

	// Control Modes
	t.c_cflag &= ~( CSIZE	|	// bits-per-byte 
					CSTOPB	|	// Two stop bits 
					HUPCL	|	// Hang up 
					PARENB		// Parity  
					);

	t.c_cflag |= (  CLOCAL	|	// Ignore modem status lines 
					CREAD	|	// Enable receiver 
					STOP_BIT|	// # stop bits 
					BITS	|	// bits-per-byte 
					PARITY		// Parity check  
					);

	// Local Modes
	t.c_lflag &= ~( ECHO	|	// No echo of any kind 
					ECHOE	|
					ECHOK	|
					ECHONL	|
					ICANON	|	// No canonical input 
					ISIG	|	// No signal generation 
					NOFLSH	|	// Enable flushing 
					TOSTOP		// No job control 
					);     

	// Control Characters 
	// When VMIN and VTIME are zero the read() function will
	// return as much data as possible without waiting
	
	t.c_cc[VMIN]  = 1; 
	t.c_cc[VTIME] = 0;

	// Set the baud rate 
	if( cfsetispeed( &t, SPEED ) == -1 )
	{
		pError("portLib: cfsetispeed") ;
		return -1;
	}
	if( cfsetospeed( &t, SPEED ) == -1 )
	{
		pError("portLib: cfsetospeed");
		return -1;
	}

	if( tcsetattr(port, TCSANOW, &t) == -1 )
	{
		pError("portLib: tcsetattr");
		return -1;
	}
	return port ;

}

int portSetVMin(SerialPort port, int vmin)
{
	struct termios t;

	// Read in the current port attributes  
	if( tcgetattr(port, &t) == -1 )
	{
		pError("portLib: tcgetattr");
		return -1;
	}

	t.c_cc[VMIN]  = vmin; 

	if( tcsetattr(port, TCSANOW, &t) == -1 )
	{
		pError("portLib: tcsetattr");
		return -1;
	}

	return 0;	
}

int portSetVtime(SerialPort port, int vtime)
{
	struct termios t;

	// Read in the current port attributes  
	if( tcgetattr(port, &t) == -1 )
	{
		pError("portLib: tcgetattr");
		return -1;
	}

	t.c_cc[VTIME]  = vtime; 

	if( tcsetattr(port, TCSANOW, &t) == -1 )
	{
		pError("portLib: tcsetattr");
		return -1;
	}

	return 0;	
}


int portRecv(SerialPort port, char *buf, int len)
{
	return( read(port, buf, len) ) ;
}

int portSend(SerialPort port, char *buf, int len)
{
	return( write(port, buf, len) ) ;
}


