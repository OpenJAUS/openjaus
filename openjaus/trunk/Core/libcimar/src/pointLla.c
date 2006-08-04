// File Name: pointLla.c
//
// Written By: Danny Kent (jaus AT dannykent DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines the functions of a PointLla Object

#include <malloc.h>
#include "cimar.h"

PointLla pointLlaCreate(void)
{
	PointLla pointLla;
	
	pointLla = (PointLla)malloc(sizeof(PointLlaStruct));
	
	if(pointLla)
	{
		pointLla->latitudeRadians = 10.0;
		pointLla->longitudeRadians = 10.0;
		pointLla->altitudeMeters = 0.0;
	
		return pointLla;
	}
	else
		return NULL;
}

void pointLlaDestroy(PointLla pointLla)
{
	free(pointLla);
}
