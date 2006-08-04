/* **************************************************************** */
/* utmLib.c															*/
/*																	*/
/* A library of functions to convert from Latitude and Longitude	*/
/* to X and Y within a UTM Zone using the WGS84 Spheroid.			*/
/*																	*/
/* This Library is based on the GPTC Projection Algorithms			*/
/* avalible from USGS at:											*/
/* ftp://edcftp.cr.usgs.gov/pub/software/gctpc/gctpc20.tar.Z		*/
/*																	*/
/* Adapted by:	Daniel A. Kent (jaus AT dannykent DOT com)			*/
/*				2004												*/
/*																	*/
/* Functions:	utmConversionInit() - Initialize Converstions		*/
/*				pointLlaToPointUtm() - (Lat,Lon) to (X,Y)			*/
/*				pointUtmToPointLla() - (X,Y) to (Lat,Lon)			*/
/*																	*/
/* Library Files:	cproj.c											*/
/*					utmfor.c										*/
/*					utminv.c										*/
/*					utmLib.c										*/
/*					cproj.h											*/
/*					proj.h											*/
/*					utmLib.h										*/
/*																	*/
/* **************************************************************** */

#include <malloc.h>
#include <stdio.h>
#include "cimar.h"

static unsigned char utmLibInitFlag = FALSE;	// Place holder to test if the library has been initialized
static long utmLibZone = 0;						// Place holder to remember the last zone the library was initialized to

/* **************************************************************** */
/* Function: utmInitCheck()											*/	
/* Inputs:	none													*/
/* Outputs: TRUE if the Library has been initialized				*/
/* Description: Used to check the status of the UTM Engine			*/
/* **************************************************************** */
unsigned char utmInitCheck(void)
{
	return utmLibInitFlag;
}

/* **************************************************************** */
/* Function: utmZoneCheck()											*/	
/* Inputs:	PointLLA												*/
/* Outputs: TRUE if zones are equal									*/
/* Description: Function takes a value for Longitude,				*/
/*				calculates the UTM Zone and checks whether the		*/
/* 				utmLib has been setup for that zone.				*/
/*				Use this to detect changes in zone during operation	*/
/* Units:	LAT and LON in RADIANS									*/
/* **************************************************************** */
unsigned char utmZoneCheck(PointLla point)
{
	long zone = 0;
	
	if(point->longitudeRadians > PI || point->longitudeRadians < -PI)
	{
		p_error("Invalid Test Point for UTM Zone Check. Check Radians??","");
		return FALSE;
	}
	
	zone = calc_utm_zone(point->longitudeRadians * DEG_PER_RAD);
	
	if(zone == utmLibZone)
		return TRUE;
	else
		return FALSE;
}

/* **************************************************************** */
/* Function: utmConversionInit()									*/	
/* Inputs:	PointLLA												*/
/* Outputs: 0 if sucessful											*/
/* Description: Function takes a seed value for Longitude,			*/
/*				calculates the UTM Zone and intializes the			*/
/*				utmForward and utmInverse functions.				*/
/*				Constructs the conversion for the WGS84 Spheroid	*/
/* Units:	LAT and LON in RADIANS									*/
/* **************************************************************** */
long utmConversionInit(PointLla point)
{
	long zone = 0;
	double r_maj = 6378137;			// Magic Number: These are the values
	double r_min = 6356752.3142;	// needed for the UTM ellipsoid
	double scale_fact = .9996;
//	long val;
	
	if(point->longitudeRadians > PI || point->longitudeRadians < -PI)
	{
		p_error("Invalid Seed Point for UTM Init. Check Radians??","");
		return(-1);
	}

	zone = calc_utm_zone(point->longitudeRadians*R2D);

	// Check if the zone is different than what was done before
	if(zone != utmLibZone)
	{		
		if(utmforint(r_maj, r_min, scale_fact, zone) != OK) return -1;
		if(utminvint(r_maj, r_min, scale_fact, zone) != OK) return -1;
		
		utmLibInitFlag = 1;
		utmLibZone = zone;
		return OK;
	}
	else
	{
		// Zone is the same, no need to re-init
		return OK;
	}
}

/* **************************************************************** */
/* Function: UTM2LLA()												*/	
/* Inputs:	PointXYZ												*/
/* Outputs: PointLLA												*/
/* Description: Converts the point given in X and Y to Lat			*/
/*				and Lon using the UTM projection for the			*/
/*				WGS84 Spheroid and the seeded UTM zone.				*/
/* Units:	LAT and LON in RADIANS									*/
/*			X and Y in METERS										*/
/* **************************************************************** */
PointLla pointUtmToPointLla(PointUtm pointUtm)
{
	PointLla pointLla = pointLlaCreate();
	
	utminv(pointUtm->xMeters, pointUtm->yMeters, &pointLla->longitudeRadians, &pointLla->latitudeRadians);
	
	return pointLla;
}

/* **************************************************************** */
/* Function: LLA2UTM()												*/	
/* Inputs:	PointXYZ												*/
/* Outputs: PointLLA												*/
/* Description: Converts the point given in Lat and Lon to 			*/
/*				Lat and Lon using the UTM projection for 			*/
/*				the WGS84 Spheroid and the seeded UTM Zone.			*/
/* Units:	LAT and LON in RADIANS									*/
/*			X and Y in METERS										*/
/* **************************************************************** */
PointUtm pointLlaToPointUtm(PointLla pointLla)
{
	PointUtm pointUtm = pointUtmCreate();
	
	utmfor(pointLla->longitudeRadians, pointLla->latitudeRadians, &pointUtm->xMeters, &pointUtm->yMeters);
	
	return pointUtm;
}

/* **************************************************************** */
/* Function: p_error()												*/	
/* Inputs:	char what												*/
/* Outputs: void													*/
/* Description: Provides p_error functions used in GCTP functions	*/
/* **************************************************************** */
void p_error(char *what, char *where)
{
	printf(what); printf("\n");
}
