/*  
 * Name: JausTransportQueue
 *
 * (c) 2007 OpenJAUS.com
 * By: Danny Kent (jaus AT dannykent.com)
 * 
 * Version: 1.0
 *
 * Description: Provides an interface for monitoring JausQueues
 *
 */
#ifndef JAUS_TRANSPORT_QUEUE_H
#define JAUS_TRANSPORT_QUEUE_H

#include <queue>
#include "jaus.h"

class JausTransportQueue
{
public:
	JausTransportQueue(void);
	~JausTransportQueue(void);

	void push(JausMessage inc);
	JausMessage pop(void);
	bool isEmpty(void);
	unsigned long size(void);

private:
	std::queue <JausMessage> list;
};

#endif
