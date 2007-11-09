#ifndef ERROR_EVENT_H
#define ERROR_EVENT_H

#include <string>
#include "NodeManagerEvent.h"

class ErrorEvent : public NodeManagerEvent
{
public:
	ErrorEvent(unsigned int subType);
	ErrorEvent::ErrorEvent(unsigned int subType, const char *file, const char *function, int line, std::string userString);
	~ErrorEvent();

	std::string toString();
	std::string getUserString();
	
	enum {Routing, Memory, NullPointer, Configuration};

private:
	unsigned int subType;
	std::string userString;
	std::string file;
	std::string function;
	long line;
};

#endif