/*  
 * Name: JausQueueMonitor
 *
 * (c) 2007 OpenJAUS.com
 * By: Danny Kent (jaus AT dannykent.com)
 * 
 * Version: 1.0
 *
 * Description: Provides an interface for monitoring JausQueues
 *
 */

#ifndef JAUS_QUEUE_MONITOR
#define JAUS_QUEUE_MONITOR

class JausQueueMonitor
{
public:
	JausQueueMonitor();
	virtual ~JausQueueMonitor();

	virtual void queueEmpty();
	virtual void queueFull();
	virtual void queueNewItem();

};

#endif
