#ifndef ERROR_EVENT_H
#define ERROR_EVENT_H

#include <string>
#include "NodeManagerEvent.h"

class ErrorEvent : public NodeManagerEvent
{
public:
	ErrorEvent(unsigned int subType);
	ErrorEvent(unsigned int subType, const char *function, long line, std::string userString);
	~ErrorEvent();

	std::string toString();
	std::string getUserString();
	
	enum {Routing, Memory, NullPointer, Configuration, Message, Warning};

private:
	unsigned int subType;
	std::string userString;
	std::string file;
	std::string function;
	long line;
};

#endif

