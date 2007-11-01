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

#include <vector>
#include <queue>
//#include "JausTransportPacket.h"
#include "JausQueueMonitor.h"
#include "jaus.h"

class JausTransportQueue
{
public:
	JausTransportQueue(void);
	~JausTransportQueue(void);

	bool registerMonitor(JausQueueMonitor *monitor);
	void push(JausMessage inc);
	JausMessage pop(void);
	bool isEmpty(void);
	unsigned long size(void);

private:
	std::vector <JausQueueMonitor *> monitors;
	std::queue <JausMessage> list;
};

#endif
