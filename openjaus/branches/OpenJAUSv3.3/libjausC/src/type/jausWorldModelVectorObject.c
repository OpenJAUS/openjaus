/*****************************************************************************
 *  Copyright (c) 2006, University of Florida.
 *  All rights reserved.
 *  
 *  This file is part of OpenJAUS.  OpenJAUS is distributed under the BSD 
 *  license.  See the LICENSE file for details.
 * 
 *  Redistribution and use in source and binary forms, with or without 
 *  modification, are permitted provided that the following conditions 
 *  are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer in the documentation and/or other materials provided
 *       with the distribution.
 *     * Neither the name of the University of Florida nor the names of its 
 *       contributors may be used to endorse or promote products derived from 
 *       this software without specific prior written permission.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
 *   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
 *   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR 
 *   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
 *   OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, 
 *   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY 
 *   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 ****************************************************************************/
// File Name: jausWorldModelVectorObject.c
//
// Written By: Danny Kent (jaus AT dannykent DOT com), Tom Galluzzo (galluzzo AT gmail DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description:

#include <string.h>
#include <malloc.h>

#include <cimar.h>
#include "cimar/jaus.h"

// JausWorldModelVectorObject Constructor
JausWorldModelVectorObject vectorObjectCreate(void)
{
	JausWorldModelVectorObject object;
	
	object = (JausWorldModelVectorObject) malloc(sizeof(JausWorldModelVectorObjectStruct));
	if(object)
	{
		object->id = newJausUnsignedShort(0);
		object->type = newJausByte(JAUS_WM_UNKNOWN_TYPE);	// Object Type
		object->bufferMeters = newJausFloat(0.0);		// Buffer Size in meters
		object->featureClasses = vectorCreate();		// Dynamic Array of JausWorldModelFeatureClass data
		object->dataPoints = vectorCreate();			// Dynamic Array of PointLla data
		return object;
	}
	else
	{
		return NULL;
	}
}

// JausWorldModelVectorObject Constructor (from Buffer)
JausWorldModelVectorObject vectorObjectFromBuffer(unsigned char *buffer, unsigned int bufferSizeBytes, JausBoolean objectBuffered)
{
	unsigned int index = 0;
	int i = 0;
	JausByte featureClassCount;
	JausUnsignedShort dataPointCount;
	JausInteger tempInt;
	JausWorldModelVectorObject object = NULL;
	JausWorldModelFeatureClass class = NULL;
	PointLla point = NULL;
	
	object = (JausWorldModelVectorObject) malloc(sizeof(JausWorldModelVectorObjectStruct));
	if(object)
	{	
		// Object Id will always be 0, this is because it is not always included in the buffer to be unpacked
		// The specific message will have to populate this if provided
		object->id = newJausUnsignedShort(0);
	
		// Read Object Type		
		if(!jausByteFromBuffer(&object->type, buffer+index, bufferSizeBytes-index))
		{
			free(object);
			return NULL;
		}
		index += JAUS_BYTE_SIZE_BYTES;

		// Buffer is optional
		if(objectBuffered)
		{
			// Read Buffer Value
			if(!jausFloatFromBuffer(&object->bufferMeters, buffer+index, bufferSizeBytes-index))
			{
				free(object);
				return NULL;
			}
			index += JAUS_FLOAT_SIZE_BYTES;
		}
		else
		{
			// Setup Buffer if not specified
			object->bufferMeters = newJausFloat(0.0);
		}

		// Create FC Vector
		object->featureClasses = vectorCreate();
		if(!object->featureClasses)
		{
			free(object);
			return NULL;
		}
		
		// Read Number of Feature Classes
		if(!jausByteFromBuffer(&featureClassCount, buffer+index, bufferSizeBytes-index))
		{
			vectorDestroy(object->featureClasses, (void *)featureClassDestroy);
			free(object);
			return NULL;
		}
		index += JAUS_BYTE_SIZE_BYTES;
		
		for(i = 0; i < featureClassCount; i++)
		{
			// Create FC object from buffer
			class = featureClassFromBuffer(buffer+index, bufferSizeBytes-index);
			if(!class)
			{
				vectorDestroy(object->featureClasses, (void *)featureClassDestroy);
				free(object);
				return NULL;
			}
			index += featureClassSizeBytes(class);

			vectorAdd(object->featureClasses, class);
		}

		// Create DataPoints Vector
		object->dataPoints = vectorCreate();
		if(!object->dataPoints)
		{
			vectorDestroy(object->featureClasses, (void *)featureClassDestroy);
			free(object);
			return NULL;
		}
		
		// Read Number of data Points
		if(!jausUnsignedShortFromBuffer(&dataPointCount, buffer+index, bufferSizeBytes-index))
		{
			vectorDestroy(object->dataPoints, (void *)pointLlaDestroy);
			vectorDestroy(object->featureClasses, (void *)featureClassDestroy);
			free(object);
			return NULL;
		}
		index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;

		for(i = 0; i < dataPointCount; i++)
		{
			point = pointLlaCreate();
			if(!point)
			{
				vectorDestroy(object->dataPoints, (void *)pointLlaDestroy);
				vectorDestroy(object->featureClasses, (void *)featureClassDestroy);
				free(object);
				return NULL;
			}
			
			// unpack Latitude
			if(!jausIntegerFromBuffer(&tempInt, buffer+index, bufferSizeBytes-index))
			{
				vectorDestroy(object->dataPoints, (void *)pointLlaDestroy);
				vectorDestroy(object->featureClasses, (void *)featureClassDestroy);
				free(object);
				return NULL;
			}
			index += JAUS_INTEGER_SIZE_BYTES;
			
			// Scaled Int (-90, 90)			
			point->latitudeRadians = jausIntegerToDouble(tempInt, -90, 90) * RAD_PER_DEG;
			
			// unpack Latitude
			if(!jausIntegerFromBuffer(&tempInt, buffer+index, bufferSizeBytes-index))
			{
				vectorDestroy(object->dataPoints, (void *)pointLlaDestroy);
				vectorDestroy(object->featureClasses, (void *)featureClassDestroy);
				free(object);
				return NULL;
			}
			index += JAUS_INTEGER_SIZE_BYTES;
			
			// Scaled Int (-180, 180)
			point->longitudeRadians = jausIntegerToDouble(tempInt, -180, 180) * RAD_PER_DEG;

			vectorAdd(object->dataPoints, point);
		}

		return object;
	}
	else
	{
		return NULL;
	}
}

// JausWorldModelVectorObject To Buffer
JausBoolean vectorObjectToBuffer(JausWorldModelVectorObject object, unsigned char *buffer, unsigned int bufferSizeBytes, JausBoolean objectBuffered)
{
	unsigned int index = 0;
	int i = 0;
	JausInteger tempInt;
	JausWorldModelFeatureClass class = NULL;
	PointLla point = NULL;
	
	if(object)
	{
		// Type
		if(!jausByteToBuffer(object->type, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
		index += JAUS_BYTE_SIZE_BYTES;
		
		// Buffer is Optional
		if(objectBuffered)
		{
			if(!jausFloatToBuffer(object->bufferMeters, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_FLOAT_SIZE_BYTES;
		}
		
		// FC Count
		if(!jausByteToBuffer((JausByte)object->featureClasses->elementCount, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
		index += JAUS_BYTE_SIZE_BYTES;
		
		for(i = 0; i < object->featureClasses->elementCount; i++)
		{
			class = (JausWorldModelFeatureClass)object->featureClasses->elementData[i];

			if(!featureClassToBuffer(class, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += featureClassSizeBytes(class);
		}
		
		if(!jausUnsignedShortToBuffer((JausUnsignedShort)object->dataPoints->elementCount, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
		index += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
		
		for(i = 0; i < object->dataPoints->elementCount; i++)
		{
			point = (PointLla) object->dataPoints->elementData[i];

			// Scaled Int (-90, 90)
			tempInt = jausIntegerFromDouble((point->latitudeRadians * DEG_PER_RAD), -90, 90);

			//pack Latitude
			if(!jausIntegerToBuffer(tempInt, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_INTEGER_SIZE_BYTES;

			// Scaled Int (-180, 180)
			tempInt = jausIntegerFromDouble((point->longitudeRadians * DEG_PER_RAD), -180, 180);

			//pack Longitude
			if(!jausIntegerToBuffer(tempInt, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
			index += JAUS_INTEGER_SIZE_BYTES;
		}

		return JAUS_TRUE;
	}
	
	return JAUS_FALSE;		
}

// JausWorldModelVectorObject Destructor
void vectorObjectDestroy(JausWorldModelVectorObject object)
{
	if(object)
	{
		vectorDestroy(object->featureClasses, (void *)featureClassDestroy);
		vectorDestroy(object->dataPoints, (void *)pointLlaDestroy);

		free(object);
		object = NULL;
	}
}

// JausWorldModelVectorObject Buffer Size
unsigned int vectorObjectSizeBytes(JausWorldModelVectorObject object, JausBoolean objectBuffered)
{
	int i = 0;
	unsigned int size = 0;
	JausWorldModelFeatureClass class = NULL;
	
	if(object)
	{
		size += JAUS_BYTE_SIZE_BYTES;		// Type
	
		if(objectBuffered)
		{
			size += JAUS_FLOAT_SIZE_BYTES; 	// Buffer
		}
		
		size += JAUS_BYTE_SIZE_BYTES;		// Feature Class Count
		
		for(i = 0; i < object->featureClasses->elementCount; i++)
		{
			class = (JausWorldModelFeatureClass) object->featureClasses->elementData[i];
			size += featureClassSizeBytes(class);	// size of each featureClass
		}
		
		size += JAUS_UNSIGNED_SHORT_SIZE_BYTES;	// Point Count
		
		for(i = 0; i < object->dataPoints->elementCount; i++)
		{
			size += JAUS_INTEGER_SIZE_BYTES;	// Latitude
			size += JAUS_INTEGER_SIZE_BYTES;	// Longitude
		}
	}
	return size;
}

// JausWorldModelVectorObject Type To String
int vectorObjectTypeToString(JausWorldModelVectorObject object, char *string)
{
	switch(object->type)
	{
		case JAUS_WM_POINT_TYPE:
			return sprintf(string, "Point");					
		case JAUS_WM_LINE_TYPE:
			return sprintf(string, "Line");
		case JAUS_WM_POLYGON_TYPE:
			return sprintf(string, "Polygon");
		default:
			return sprintf(string, "Unknown");
	}
}

JausWorldModelVectorObject vectorObjectCopy(JausWorldModelVectorObject input)
{
	JausWorldModelVectorObject objectCopy;
	JausWorldModelFeatureClass fc;
	PointLla pointInput, pointCopy;
	int i;
	
	objectCopy = (JausWorldModelVectorObject) malloc(sizeof(JausWorldModelVectorObjectStruct));
	if(objectCopy)
	{
		objectCopy->id = input->id;
		objectCopy->type = input->type;
		objectCopy->bufferMeters = input->bufferMeters;
		objectCopy->featureClasses = vectorCreate();
		if(!objectCopy->featureClasses)
		{
			cError("JausWorldModelVectorObject:%d: Failed to create objectCopy->featureClasses\n", __LINE__);
			free(objectCopy);
			return NULL;
		}

		for(i = 0; i < input->featureClasses->elementCount; i++)
		{
			fc = featureClassCopy((JausWorldModelFeatureClass)input->featureClasses->elementData[i]);
			if(!fc)
			{
				cError("JausWorldModelVectorObject:%d: Failed to clone FeatureClass\n", __LINE__);
				vectorDestroy(objectCopy->featureClasses, (void *)featureClassDestroy);
				free(objectCopy);
				return NULL;
			}
			vectorAdd(objectCopy->featureClasses, fc);
		}
		

		objectCopy->dataPoints = vectorCreate();
		if(!objectCopy->dataPoints)
		{
			cError("JausWorldModelVectorObject:%d: Failed to create objectCopy->dataPoints\n", __LINE__);
			vectorDestroy(objectCopy->featureClasses, (void *)featureClassDestroy);
			free(objectCopy);
			return NULL;
		}

		for(i = 0; i < input->dataPoints->elementCount; i++)
		{
			pointInput = (PointLla) input->dataPoints->elementData[i];
			pointCopy = pointLlaCreate();
			if(!pointCopy)
			{
				cError("JausWorldModelVectorObject:%d: Failed to clone DataPoint\n", __LINE__);
				vectorDestroy(objectCopy->featureClasses, (void *)featureClassDestroy);
				vectorDestroy(objectCopy->dataPoints, (void *)pointLlaDestroy);
				free(objectCopy);
				return NULL;
			}
			
			pointCopy->latitudeRadians = pointInput->latitudeRadians;
			pointCopy->longitudeRadians = pointInput->longitudeRadians;
			
			vectorAdd(objectCopy->dataPoints, pointCopy);
		}
		return objectCopy;
	}
	else
	{
		cError("JausWorldModelVectorObject:%d: Failed to create objectCopy\n", __LINE__);
		return NULL;
	}

	cError("JausWorldModelVectorObject:%d: This shouldn't happen.\n", __LINE__);	
	return NULL;
}
