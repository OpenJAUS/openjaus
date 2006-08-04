// File Name: jausType.c
//
// Written By: Danny Kent (jaus AT dannykent DOT com), Tom Galluzzo (galluzzo AT gmail DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines all the basic JausTypes and allows the user to use the JausType structure as a place-holder
// for any one type. This allows functions to operate on all JausTypes based on the individual type flags.

#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "cimar/jaus.h"

int isHostBigEndian(void)
{
    short a = 0x0100;
    return ( (int)*((unsigned char*) (&a)) );
}
