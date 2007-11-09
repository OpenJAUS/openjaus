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

ErrorEvent::ErrorEvent(unsigned int subType, const char *file, const char *function, int line, std::string userString)
{
	this->type = NodeManagerEvent::ErrorEvent;
	this->subType = subType;
	this->userString = userString;
	this->file = file;
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

	sprintf(buf, "ERROR (%s:%s:%d): %s\n", file, function, line, this->userString.c_str());

	return buf;
}