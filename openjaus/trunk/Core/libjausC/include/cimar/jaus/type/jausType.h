// File Name: jausType.h
//
// Written By: Danny Kent (jaus AT dannykent DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines all the basic JausTypes and allows the user to use the JausType structure 
// as a place-holder for any one type. This allows functions to operate on all JausTypes based on the 
// individual type flags.

#ifndef JAUS_TYPE_H
#define JAUS_TYPE_H

//Individual Jaus Types
#include "jausByte.h"
#include "jausShort.h"
#include "jausInteger.h"
#include "jausLong.h"
#include "jausUnsignedShort.h"
#include "jausUnsignedInteger.h"
#include "jausUnsignedLong.h"
#include "jausFloat.h"
#include "jausDouble.h"
#include "jausBytePresenceVector.h"
#include "jausShortPresenceVector.h"
#include "jausIntegerPresenceVector.h"
#include "jausEventLimit.h"
#include "jausWorldModelVectorObject.h"
#include "jausWorldModelFeatureClass.h"
#include "jausTime.h"

int isHostBigEndian(void);

#endif

