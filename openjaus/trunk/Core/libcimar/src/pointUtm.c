// File Name: pointUtm.c
//
// Written By: Danny Kent (jaus AT dannykent DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines the functions of a PointUtm object

#include <malloc.h>
#include "cimar.h"

PointUtm pointUtmCreate(void)
{
	PointUtm pointUtm;
	
	pointUtm = (PointUtm)malloc(sizeof(PointUtmStruct));
	if(pointUtm)
	{
		pointUtm->xMeters = 0.0;
		pointUtm->yMeters = 0.0;
		pointUtm->zMeters = 0.0;
		
		return pointUtm;
	}
	else
		return NULL;
}


void pointUtmDestroy(PointUtm pointUtm)
{
	free(pointUtm);
}

