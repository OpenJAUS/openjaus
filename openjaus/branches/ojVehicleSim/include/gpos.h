// File:		gpos.h
// Version:		0.4 alpha
// Written by:	Tom Galluzzo (galluzzt@ufl.edu)
// Date:		07/01/2005
// Description:	This file contains the skeleton C header file code for implementing the gpos.c file

#ifndef GPOS_H
#define GPOS_H

#include <jaus.h>
#include <math.h>

#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE 1
#endif


OjCmpt gposCreate(void);
void gposDestroy(OjCmpt gpos);

JausState gposGetState(OjCmpt gpos);
JausAddress gposGetAddress(OjCmpt gpos);
double gposGetUpdateRate(OjCmpt gpos);
// USER: Insert prototypes for added public function here
double gposGetLatitude(OjCmpt gpos);
double gposGetLongitude(OjCmpt gpos);
double gposGetYaw(OjCmpt gpos);
int gposGetScActive(OjCmpt gpos);

#endif // GPOS_H
