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
// File Name: cimar.h
//
// Written By: Danny Kent (jaus AT dannykent DOT com), 
//             Tom Galluzzo (galluzzo AT gmail DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file is used to include all the associated header files 
//              for the libcimar.so library

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
#include "cimar/queue.h"
#include "cimar/vector.h"
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

#ifdef __cplusplus
}
#endif

#endif
