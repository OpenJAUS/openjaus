// File Name: vector.h
//
// Written By: Tom Galluzzo (galluzzo AT gmail DOT com) and Danny Kent (jaus AT dannykent DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines the attributes of a Vector object

#ifndef VECTOR_H
#define VECTOR_H

typedef struct
{
	void **elementData;
	int elementCount;
	int capacity;
	int capacityIncrement;
}VectorStruct;

typedef VectorStruct * Vector;

Vector vectorCreate(void);
void vectorDestroy(Vector, void (*)(void *));
void vectorAdd(Vector, void *);
int vectorContains(Vector, void *, int (*)(void *, void *));
void *vectorRemove(Vector, void *, int (*)(void *, void *));
void *vectorRemoveAt(Vector, int);
void vectorRemoveAll(Vector vector, void (*elementDestroy)(void *));

#endif // VECTOR_H
