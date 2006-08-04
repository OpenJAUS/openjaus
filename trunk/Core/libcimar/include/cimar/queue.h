// File Name: queue.h
//
// Written By: Tom Galluzzo (galluzzo AT gmail DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description:	This file describes the functionality associated with a generic void pointer Queue object.

#ifndef QUEUE_H
#define QUEUE_H

typedef struct queueObject
{
	void *object;
	struct queueObject *nextObject;
}QueueObject;

typedef struct
{
	Monitor monitor;
	QueueObject *firstObject;
	QueueObject *lastObject;
	int size;
}QueueStruct;

typedef QueueStruct *Queue;

Queue queueCreate(Monitor);
void queueDestroy(Queue, void (*)(void *));
void*  queuePop(Queue);
void queuePush(Queue, void *);

#endif // QUEUE_H
