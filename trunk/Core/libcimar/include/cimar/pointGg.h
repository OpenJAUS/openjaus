// File Name: pointGg.h
//
// Written By: Danny Kent (jaus AT dannykent DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines the functions of a global grid point

#ifndef POINTGG_H
#define POINTGG_H

#include "cimar.h"

// PointGg
// This is a data structure to hold the row and column of the global grid center
typedef struct
{
	unsigned int row;
	unsigned int column;
}PointGgStruct;

typedef PointGgStruct *PointGg;

// Common Functions
PointGg pointGgCreate(void);
void pointGgDestroy(PointGg);

// Converstion Functions
PointUtm globalGridToUtm(PointGg pointGg, double gridResolution);
PointLla globalGridToLla(PointGg pointGg, double gridResolution);
PointGg llaToGlobalGrid(PointLla pointLla, double gridResolution);
PointGg utmToGlobalGrid(PointUtm pointUtm, double gridResolution);

#endif

