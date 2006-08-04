// File Name: cimar.h
//
// Written By: Danny Kent (jaus AT dannykent DOT com), Tom Galluzzo (galluzzo AT gmail DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file is used to include all the associated header files for the libcimar.so library

#ifndef CIMAR_H
#define CIMAR_H

#ifdef __cplusplus
extern "C" 
{
#endif

#ifndef CIMAR_DEFINES
#define CIMAR_DEFINES
#define CIMAR_PI		3.14159265358979323846
#define CIMAR_HALF_PI	1.570796326794897
#define CIMAR_TRUE	1
#define CIMAR_FALSE 0
#endif

// Network Classes
#include "cimar/inetAddress.h"
#include "cimar/datagramPacket.h"
#include "cimar/datagramSocket.h"
#include "cimar/networkInterface.h"
#include "cimar/multicastSocket.h"

// Storage Containers
#include "cimar/monitor.h"
#include "cimar/queue.h"
#include "cimar/vector.h"
#include "cimar/ringBuffer.h"
#include "cimar/torusBuffer.h"
#include "cimar/properties.h"

// UTM Library
#include "cimar/pointUtm.h"
#include "cimar/pointLla.h"
#include "cimar/pointGg.h"
#include "cimar/utm/utmLib.h"

// Great Circle Calculations
#include "cimar/greatCircle.h"

// Misc Library Functions
#include "cimar/bres.h"
#include "cimar/logLib.h"
#include "cimar/portLib.h"
#include "cimar/timeLib.h"
#include "cimar/gridMapLib.h"

#ifdef __cplusplus
}
#endif

#endif

