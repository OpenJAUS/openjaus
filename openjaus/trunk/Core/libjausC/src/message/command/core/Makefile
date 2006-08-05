##############################################################################
#   Copyright (c) 2006, University of Florida.
#   All rights reserved.
#   
#   This file is part of OpenJAUS.  OpenJAUS is distributed under the BSD 
#   license.  See the LICENSE file for details.
#  
#   Redistribution and use in source and binary forms, with or without 
#   modification, are permitted provided that the following conditions 
#   are met:
# 
#      * Redistributions of source code must retain the above copyright
#        notice, this list of conditions and the following disclaimer.
#      * Redistributions in binary form must reproduce the above
#        copyright notice, this list of conditions and the following
#        disclaimer in the documentation and/or other materials provided
#        with the distribution.
#      * Neither the name of the University of Florida nor the names of its 
#        contributors may be used to endorse or promote products derived from 
#        this software without specific prior written permission.
# 
#    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
#    "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
#    LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR 
#    A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
#    OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
#    SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
#    LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, 
#    DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY 
#    THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
#    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
#    OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
##############################################################################
# ./src/message/command/core

INC		=	include
SRC		=	
BUILD	=	Build/
CC		=	gcc
CCFLAGS	=	-Wall -O2 -fPIC -g -c 

OBJECTS =	\
			$(DIRPATH)$(BUILD)setComponentAuthorityMessage.o \
			$(DIRPATH)$(BUILD)shutdownMessage.o \
			$(DIRPATH)$(BUILD)standbyMessage.o \
			$(DIRPATH)$(BUILD)resumeMessage.o \
			$(DIRPATH)$(BUILD)resetMessage.o \
			$(DIRPATH)$(BUILD)setEmergencyMessage.o \
			$(DIRPATH)$(BUILD)clearEmergencyMessage.o \
			$(DIRPATH)$(BUILD)createServiceConnectionMessage.o \
			$(DIRPATH)$(BUILD)confirmServiceConnectionMessage.o \
			$(DIRPATH)$(BUILD)activateServiceConnectionMessage.o \
			$(DIRPATH)$(BUILD)suspendServiceConnectionMessage.o \
			$(DIRPATH)$(BUILD)terminateServiceConnectionMessage.o \
			$(DIRPATH)$(BUILD)requestComponentControlMessage.o \
			$(DIRPATH)$(BUILD)releaseComponentControlMessage.o \
			$(DIRPATH)$(BUILD)confirmComponentControlMessage.o \
			$(DIRPATH)$(BUILD)rejectComponentControlMessage.o \
			$(DIRPATH)$(BUILD)setTimeMessage.o \

all: $(OBJECTS)

$(DIRPATH)$(BUILD)setComponentAuthorityMessage.o : $(SRC)setComponentAuthorityMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)setComponentAuthorityMessage.o ./setComponentAuthorityMessage.c

$(DIRPATH)$(BUILD)shutdownMessage.o : $(SRC)shutdownMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)shutdownMessage.o ./shutdownMessage.c

$(DIRPATH)$(BUILD)standbyMessage.o : $(SRC)standbyMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)standbyMessage.o ./standbyMessage.c

$(DIRPATH)$(BUILD)resumeMessage.o : $(SRC)resumeMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)resumeMessage.o ./resumeMessage.c

$(DIRPATH)$(BUILD)resetMessage.o : $(SRC)resetMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)resetMessage.o ./resetMessage.c

$(DIRPATH)$(BUILD)setEmergencyMessage.o : $(SRC)setEmergencyMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)setEmergencyMessage.o ./setEmergencyMessage.c

$(DIRPATH)$(BUILD)clearEmergencyMessage.o : $(SRC)clearEmergencyMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)clearEmergencyMessage.o ./clearEmergencyMessage.c

$(DIRPATH)$(BUILD)createServiceConnectionMessage.o : $(SRC)createServiceConnectionMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)createServiceConnectionMessage.o ./createServiceConnectionMessage.c

$(DIRPATH)$(BUILD)confirmServiceConnectionMessage.o : $(SRC)confirmServiceConnectionMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)confirmServiceConnectionMessage.o ./confirmServiceConnectionMessage.c

$(DIRPATH)$(BUILD)activateServiceConnectionMessage.o : $(SRC)activateServiceConnectionMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)activateServiceConnectionMessage.o ./activateServiceConnectionMessage.c

$(DIRPATH)$(BUILD)suspendServiceConnectionMessage.o : $(SRC)suspendServiceConnectionMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)suspendServiceConnectionMessage.o ./suspendServiceConnectionMessage.c

$(DIRPATH)$(BUILD)terminateServiceConnectionMessage.o : $(SRC)terminateServiceConnectionMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)terminateServiceConnectionMessage.o ./terminateServiceConnectionMessage.c

$(DIRPATH)$(BUILD)requestComponentControlMessage.o : $(SRC)requestComponentControlMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)requestComponentControlMessage.o ./requestComponentControlMessage.c

$(DIRPATH)$(BUILD)releaseComponentControlMessage.o : $(SRC)releaseComponentControlMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)releaseComponentControlMessage.o ./releaseComponentControlMessage.c

$(DIRPATH)$(BUILD)confirmComponentControlMessage.o : $(SRC)confirmComponentControlMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)confirmComponentControlMessage.o ./confirmComponentControlMessage.c

$(DIRPATH)$(BUILD)rejectComponentControlMessage.o : $(SRC)rejectComponentControlMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)rejectComponentControlMessage.o ./rejectComponentControlMessage.c

$(DIRPATH)$(BUILD)setTimeMessage.o : $(SRC)setTimeMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)setTimeMessage.o ./setTimeMessage.c
	