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
