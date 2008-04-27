/*****************************************************************************
 *  Copyright (c) 2008, OpenJAUS.com
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
// File Name: ErrorEvent.cpp
//
// Written By: Danny Kent (jaus AT dannykent DOT com) 
//
// Version: 3.3 BETA
//
// Date: 04/15/08
//
// Description: This file defines the interface of an ErrorEvent, 
// 				which is derived from a the NodeManagerEvent class

#include "nodeManager/events/ErrorEvent.h"

ErrorEvent::ErrorEvent(unsigned int subType)
{
	this->type = NodeManagerEvent::ErrorEvent;
	this->subType = subType;
	this->userString = "";
	this->file = "";
	this->line = -1;
	this->function = "";
}

ErrorEvent::ErrorEvent(unsigned int subType, const char *function, long line, std::string userString)
{
	this->type = NodeManagerEvent::ErrorEvent;
	this->subType = subType;
	this->userString = userString;
	this->function = function;
	this->line = line;
}

ErrorEvent::~ErrorEvent(){}

ErrorEvent *ErrorEvent::cloneEvent()
{
	return new ErrorEvent(this->subType, this->function.c_str(), this->line, this->userString);
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
		sprintf(buf, "ERROR (%s:%ld): %s\n", function.c_str(), line, this->userString.c_str());
	}
	else
	{
		sprintf(buf, "WARN (%s:%ld): %s\n", function.c_str(), line, this->userString.c_str());
	}

	return buf;
}
