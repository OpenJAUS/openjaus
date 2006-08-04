// File Name: utmLib.h
//
// Written By: Danny Kent (jaus AT dannykent DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description:	This file provides an interface to the cproj library for use as a UTM conversion engine

#ifndef UTM_WRAPPER_H
#define UTM_WRAPPER_H

#include "cimar.h"
#include "cproj.h"

#ifndef RAD_PER_DEG
#define RAD_PER_DEG D2R
#endif

#ifndef DEG_PER_RAD
#define DEG_PER_RAD R2D
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

unsigned char utmInitCheck(void);
unsigned char utmZoneCheck(PointLla);
long utmConversionInit(PointLla);

PointLla pointUtmToPointLla(PointUtm);
PointUtm pointLlaToPointUtm(PointLla);

#endif
