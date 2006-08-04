// File Name: jaus.h
//
// Written By: Danny Kent (jaus AT dannykent DOT com), Tom Galluzzo (galluzzo AT gmail DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file is a wrapper for all other headers in jaus and will provide the user with access 
// to the complete jaus library

#ifndef JAUS_H
#define JAUS_H

#ifdef __cplusplus
extern "C" 
{
#endif

typedef enum
{
	JAUS_FALSE,
	JAUS_TRUE
}JausBoolean;

#define JAUS_IDENTIFICATION_LENGTH_BYTES	80
				
#define JAUS_PI			3.14159265358979323846
#define JAUS_HALF_PI	1.570796326794897

// Define Target System Endianess Here
#ifdef __i386__
	#define JAUS_LITTLE_ENDIAN 1
#elif __ppc__
	#define JAUS_BIG_ENDIAN 1
#else
	#error "Please define system endianess in jaus.h. #define either JAUS_LITTLE_ENDIAN or JAUS_BIG_ENDIAN"
#endif

#include "cimar/jaus/type/jausType.h"

#include "cimar/jaus/jausAddress.h"
#include "cimar/jaus/jausState.h"
#include "cimar/jaus/jausSubsystem.h"
#include "cimar/jaus/jausNode.h"
#include "cimar/jaus/jausComponent.h"
#include "cimar/jaus/jausService.h"
#include "cimar/jaus/jausPayloadInterface.h"

#include "cimar/jaus/message/jausMessageHeaders.h"

#ifdef __cplusplus
}
#endif

#endif // JAUS_H
