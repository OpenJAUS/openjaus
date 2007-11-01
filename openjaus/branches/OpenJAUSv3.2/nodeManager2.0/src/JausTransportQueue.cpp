/*  
 * Name: JausTransportQueue
 *
 * (c) 2007 OpenJAUS.com
 * By: Danny Kent (jaus AT dannykent.com)
 * 
 * Version: 1.0
 *
 * Description: Provides a FIFO queue for JausTransportPackets. Supports monitoring.
 *
 */

#include "JausTransportQueue.h"
#include "JausTransportPacket.h"
#include "JausTransportInterface.h"
#include "JausCommunicationManager.h"

JausTransportQueue::JausTransportQueue(void){}

JausTransportQueue::~JausTransportQueue(void)
{
	list.~queue();
	monitors.~vector();
}

void JausTransportQueue::push(JausMessage inc)
{
	list.push(inc);

	for(unsigned int i = 0; i < monitors.size(); i++)
	{
		monitors.at(i)->queueNewItem();
	}

}

JausMessage JausTransportQueue::pop(void)
{
	JausMessage out = list.front();
	list.pop();

	if(list.empty())
	{
		for(unsigned int i = 0; i < monitors.size(); i++)
		{
			monitors.at(i)->queueEmpty();
		}
	}

	return out;
}

bool JausTransportQueue::registerMonitor(JausQueueMonitor *monitor)
{
	// TODO: Check that this monitor is not already on the list (need a way to do that)

	monitors.push_back(monitor);
	return true;
}

bool JausTransportQueue::isEmpty(void)
{
	return list.empty();
}

unsigned long JausTransportQueue::size()
{
	return (unsigned long)list.size();
}

