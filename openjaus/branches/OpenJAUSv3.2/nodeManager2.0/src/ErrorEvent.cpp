#include "ErrorEvent.h"


ErrorEvent::ErrorEvent(unsigned int subType)
{
	this->type = NodeManagerEvent::ErrorEvent;
	this->subType = subType;
	this->userString = "";
	this->file = "";
	this->line = -1;
	this->function = "";
}

ErrorEvent::ErrorEvent(unsigned int subType, char *function, int line, std::string userString)
{
	this->type = NodeManagerEvent::ErrorEvent;
	this->subType = subType;
	this->userString = userString;
	this->function = function;
	this->line = line;
}

ErrorEvent::~ErrorEvent()
{

}

std::string ErrorEvent::getUserString()
{
	return this->userString;
}

std::string ErrorEvent::toString()
{
	char buf[256] = {0};

	if(subType != ErrorEvent::Warning)
	{
		sprintf(buf, "ERROR (%s:%d): %s\n", function.c_str(), line, this->userString.c_str());
	}
	else
	{
		sprintf(buf, "WARN (%s:%d): %s\n", function.c_str(), line, this->userString.c_str());
	}

	return buf;
}