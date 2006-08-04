// File Name: pointLla.h
//
// Written By: Danny Kent (jaus AT dannykent DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines the functions of a PointLla Object

#ifndef POINTLLA_H
#define POINTLLA_H

typedef struct{
	double latitudeRadians;
	double longitudeRadians;
	double altitudeMeters;
} PointLlaStruct;

typedef PointLlaStruct *PointLla;

PointLla pointLlaCreate(void);
void pointLlaDestroy(PointLla);

#endif
