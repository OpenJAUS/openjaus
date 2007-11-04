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
#include "JausTransportInterface.h"
#include "JausCommunicationManager.h"

JausTransportQueue::JausTransportQueue(void){}

JausTransportQueue::~JausTransportQueue(void)
{
	list.~queue();
}

void JausTransportQueue::push(JausMessage inc)
{
	list.push(inc);
}

JausMessage JausTransportQueue::pop(void)
{
	JausMessage out = list.front();
	list.pop();
	return out;
}

bool JausTransportQueue::isEmpty(void)
{
	return list.empty();
}

unsigned long JausTransportQueue::size()
{
	return (unsigned long)list.size();
}

