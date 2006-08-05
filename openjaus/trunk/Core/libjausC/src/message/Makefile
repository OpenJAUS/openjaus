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
# ./src/message

INC		=	include/cimar/jaus/
SRC		=	
BUILD	=	Build/
CC		=	gcc
CCFLAGS	=	-Wall -O2 -fPIC -g -c -I$(INC)

OBJECTS =	\
			$(DIRPATH)$(BUILD)jausMessage.o \
			$(DIRPATH)$(BUILD)jausBytePresenceVector.o \
			$(DIRPATH)$(BUILD)jausShortPresenceVector.o \
			$(DIRPATH)$(BUILD)jausIntegerPresenceVector.o \
#			$(DIRPATH)$(BUILD)skeletonMessage.o \

all: $(OBJECTS)
	@cd ./command; make "DIRPATH=../$(DIRPATH)" "BUILD=$(BUILD)" "BINDIR=$(BINDIR)" "INC=$(INC)";
	@cd ./inform; make "DIRPATH=../$(DIRPATH)" "BUILD=$(BUILD)" "BINDIR=$(BINDIR)" "INC=$(INC)";
	@cd ./query; make "DIRPATH=../$(DIRPATH)" "BUILD=$(BUILD)" "BINDIR=$(BINDIR)" "INC=$(INC)";
	@cd ./experimental; make "DIRPATH=../$(DIRPATH)" "BUILD=$(BUILD)" "BINDIR=$(BINDIR)" "INC=$(INC)";

$(DIRPATH)$(BUILD)jausMessage.o : $(SRC)jausMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)jausMessage.o ./jausMessage.c	

$(DIRPATH)$(BUILD)jausBytePresenceVector.o : $(SRC)jausBytePresenceVector.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)jausBytePresenceVector.o ./jausBytePresenceVector.c	

$(DIRPATH)$(BUILD)jausIntegerPresenceVector.o : $(SRC)jausIntegerPresenceVector.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)jausIntegerPresenceVector.o ./jausIntegerPresenceVector.c		

$(DIRPATH)$(BUILD)jausShortPresenceVector.o : $(SRC)jausShortPresenceVector.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)jausShortPresenceVector.o ./jausShortPresenceVector.c		

$(DIRPATH)$(BUILD)skeletonMessage.o : $(SRC)skeletonMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)skeletonMessage.o ./skeletonMessage.c		
	