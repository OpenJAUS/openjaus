// File Name: greatCircle.h
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

#include <math.h>
#include "cimar.h"

double greatCircleDistance(double lat1, double lon1, double lat2, double lon2)
{
  static double d;

  lon1 = -lon1;
  lon2 = -lon2;
  d = 2*asin( sqrt( pow( sin((lat1-lat2)/2), 2.0 ) + cos(lat1)*cos(lat2)*pow(sin((lon1-lon2)/2),2.0)));
  return GREAT_CIRCLE_EARTH_RADIUS_M*d;
}

double greatCircleCourse(double lat1, double lon1, double lat2, double lon2)
{
  lon1 = -lon1;
  lon2 = -lon2;
  return fmod(atan2(sin(lon1-lon2)*cos(lat2),cos(lat1)*sin(lat2)-sin(lat1)*cos(lat2)*cos(lon1-lon2)), 2*M_PI);
}

double greatCircleLat(double lat1, double d, double tc)
{
  d /= GREAT_CIRCLE_EARTH_RADIUS_M;
  return asin(sin(lat1)*cos(d)+cos(lat1)*sin(d)*cos(tc));
}

double greatCircleLon(double lat1, double lon1, double d, double tc)
{
  lon1 = -lon1;
  d /= GREAT_CIRCLE_EARTH_RADIUS_M;
  return -(fmod(lon1-asin(sin(tc)*sin(d)/cos(lat1))+M_PI,2*M_PI)-M_PI);
}
