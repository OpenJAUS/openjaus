// File Name: greatCircle.c
//
// Written By: Tom Galluzzo (galluzzo AT gmail DOT com) and Danny Kent (jaus AT dannykent DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file describes the functions that comprise great circle calculations. These provide 
// a converstion method from Latitude and Longitude to Meters based on the approximation that the circumference 
// of the earth is a great circle.

#ifndef	GREAT_CIRCLE_H
#define	GREAT_CIRCLE_H

#define GREAT_CIRCLE_EARTH_RADIUS_M 6378137.0

double greatCircleDistance(double lat1, double lon1, double lat2, double lon2);
double greatCircleCourse(double lat1, double lon1, double lat2, double lon2);
double greatCircleLat(double lat1, double d, double tc);
double greatCircleLon(double lat1, double lon1, double d, double tc);

#endif // GREAT_CIRCLE_H