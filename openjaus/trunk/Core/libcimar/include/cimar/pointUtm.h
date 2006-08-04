// File Name: pointUtm.h
//
// Written By: Danny Kent (jaus AT dannykent DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines the functions of a PointUtm object

#ifndef POINTUTM_H
#define POINTUTM_H

typedef struct{
	double xMeters;
	double yMeters;
	double zMeters;
} PointUtmStruct;

typedef PointUtmStruct *PointUtm;

PointUtm pointUtmCreate(void);
void pointUtmDestroy(PointUtm);

#endif
