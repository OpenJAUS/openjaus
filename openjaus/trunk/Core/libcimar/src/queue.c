// File Name: queue.c
//
// Written By: Tom Galluzzo (galluzzo AT gmail DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description:	This file describes the functionality associated with a generic void pointer Queue object.

#include <stdlib.h>
#include "cimar.h"

Queue queueCreate(Monitor monitor)
{
	Queue queue = NULL;
	
	queue = (Queue)malloc( sizeof(QueueStruct) );
	if(queue == NULL)
	{
		return NULL;
	}
	
	queue->monitor = monitor;
	queue->firstObject = NULL;
	queue->lastObject = NULL;
	queue->size = 0;
	
	return queue;
}

void queueDestroy(Queue queue, void (*objectDestroy)(void *))
{
	QueueObject *queueObject;
	QueueObject *deadQueueObject;

	if(queue == NULL)
	{
		return;
	}
	
	queueObject = queue->firstObject;
	while(queueObject)
	{
		deadQueueObject = queueObject;
		queueObject = queueObject->nextObject;

		if(deadQueueObject->object)
		{
			if(objectDestroy)
			{
				objectDestroy(deadQueueObject->object);
			}
		}
		free(deadQueueObject);
	}
	
	free(queue);
}

void *queuePop(Queue queue)
{
	QueueObject *queueObject = queue->firstObject;
	void *object;

	if(queueObject)
	{
		queue->firstObject = queueObject->nextObject;
		if(queue->firstObject == NULL)
		{
			queue->lastObject = NULL;
		}
		queue->size--;
	
		object = queueObject->object;
		
		free(queueObject);
		
		return object;	
	}
	else
	{
		return NULL;
	}
}

void queuePush(Queue queue, void *object)
{
	QueueObject *queueObject;

	queueObject = (QueueObject*)malloc( sizeof(QueueObject) );
	queueObject->object = object;
	queueObject->nextObject = NULL;

	if(queue->firstObject == NULL)
	{
		queue->firstObject = queueObject;
	}

	if(queue->lastObject)
	{
		queue->lastObject->nextObject = queueObject;
	}

	queue->lastObject = queueObject;

	queue->size++;
	
	if(queue->monitor)
	{
		monitorSignal(queue->monitor);
	}
}
