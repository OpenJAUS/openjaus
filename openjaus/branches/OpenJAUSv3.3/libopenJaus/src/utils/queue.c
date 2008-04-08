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
#include <pthread.h>
#include "utils/queue.h"

Queue queueCreate(void)
{
	Queue queue = NULL;
	
	queue = (Queue)malloc( sizeof(QueueStruct) );
	if(queue == NULL)
	{
		return NULL;
	}
	
	queue->firstObject = NULL;
	queue->lastObject = NULL;
	queue->size = 0;
	pthread_mutex_init(&queue->mutex, NULL);

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

	pthread_mutex_destroy(&queue->mutex);
	
	free(queue);
}

void *queuePop(Queue queue)
{
	QueueObject *queueObject = queue->firstObject;
	void *object;

	if(queueObject)
	{
		pthread_mutex_lock(&queue->mutex);
		
		queue->firstObject = queueObject->nextObject;
		if(queue->firstObject == NULL)
		{
			queue->lastObject = NULL;
		}
		queue->size--;
	
		object = queueObject->object;
		
		free(queueObject);

		pthread_mutex_unlock(&queue->mutex);
		
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

	pthread_mutex_lock(&queue->mutex);
	
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

	pthread_mutex_unlock(&queue->mutex);

}
