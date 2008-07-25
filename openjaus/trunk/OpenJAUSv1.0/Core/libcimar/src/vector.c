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
// File Name: vector.c
//
// Written By: Tom Galluzzo (galluzzo AT gmail DOT com) and Danny Kent (jaus AT dannykent DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines the attributes of a Vector object

#include <stdio.h>
#include <stdlib.h>
#include "cimar.h"

int vectorIncrement(Vector);

Vector vectorCreate(void)
{
	Vector vector;
	
	vector = (Vector)malloc( sizeof(VectorStruct) );
	if(vector == NULL)
	{
		return NULL;
	}
	
	vector->capacity = 8;
	vector->capacityIncrement = 8;
	
	vector->elementCount = 0;
	vector->elementData = (void **)malloc( sizeof(void *) * vector->capacity);
	if(vector->elementData == NULL)
	{
		free(vector);
		return NULL;
	}
	
	return vector;
}

void vectorDestroy(Vector vector, void (*elementDestroy)(void *))
{
	int i;
	
	if(vector == NULL)
	{
		return;
	}
	
	if(elementDestroy != NULL)
	{
		i = vector->elementCount;
		while(i--)
		{
			elementDestroy(vector->elementData[i]);
		}
	}

	free(vector->elementData);
	free(vector);
}

void vectorAdd(Vector vector, void *element)
{
	vector->elementCount++;
	if(vector->elementCount > vector->capacity)
	{
		vectorIncrement(vector);
	}
	
	vector->elementData[vector->elementCount - 1] = element;
}

int vectorIncrement(Vector vector)
{
	int newCapacity = vector->capacity + vector->capacityIncrement;
	void ** newElementData;

	newElementData = (void **)realloc((void *)vector->elementData,  sizeof(void *) * newCapacity);
	
	if(newElementData == NULL)
	{
		return -1;
	}
	else
	{
		vector->elementData = newElementData;
		vector->capacity = newCapacity;
		return 0;
	}
}

int vectorContains(Vector vector, void *testElement, int (*equals)(void *, void *))
{
	int i;

	for(i = 0; i < vector->elementCount; i++)
	{
		if(equals(vector->elementData[i], testElement))
		{
			return i;
		}
	}
	
	return -1;
}

// Returns the element removed
void *vectorRemoveAt(Vector vector, int index)
{
	int i;
//	int newCapacity = vector->capacity - vector->capacityIncrement;
	void *retValue;
	
	if(vector->elementCount < index)
	{
		return NULL;
	}
	
	retValue = vector->elementData[index];
	for(i = index; i < vector->elementCount; i++)
	{
		vector->elementData[i] = vector->elementData[i+1];
	}
	
	// TODO: Check to see if we should shrink capacity
	// vector->elementData = (void **)realloc((void *)vector->elementData,  sizeof(void *) * newCapacity);
	vector->elementCount--;
	// vector->capacity = newCapacity;

	return retValue;
}

// returns the element removed
void *vectorRemove(Vector vector, void *testElement, int (*equals)(void *, void *))
{
	int i;
	
	for(i = 0; i < vector->elementCount; i++)
	{
		if(equals(vector->elementData[i], testElement))
		{
			return vectorRemoveAt(vector, i);
		}
	}
	
	return NULL;
}

void vectorRemoveAll(Vector vector, void (*elementDestroy)(void *))
{
	int i;

	if(elementDestroy != NULL)
	{
		i = vector->elementCount;
		while(i--)
		{
			elementDestroy(vector->elementData[i]);
		}
		vector->elementCount = 0;
	}
}
