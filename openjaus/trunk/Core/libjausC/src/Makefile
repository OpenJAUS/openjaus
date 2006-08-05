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
# ./src/
BINDIR	=	../bin/
INC		=	../include/
SRC		=	./
BUILD	=	../Build/
LIBS	=	
CC		=	gcc
CCFLAGS	=	-Wall -O2 -fPIC -g -c -I$(INC)

OBJECTS =	\
			$(BUILD)jausAddress.o \
			$(BUILD)jausComponent.o \
			$(BUILD)jausNode.o \
			$(BUILD)jausSubsystem.o \
			$(BUILD)jausState.o \
			$(BUILD)jausService.o \
			$(BUILD)jausPayloadInterface.o \

all: $(OBJECTS)
	@cd ./type; make "DIRPATH=../$(DIRPATH)" "BUILD=$(BUILD)" "BINDIR=$(BINDIR)" "INC=$(INC)";
	@cd ./message; make "DIRPATH=../$(DIRPATH)" "BUILD=$(BUILD)" "BINDIR=$(BINDIR)" "INC=$(INC)";
	
$(BUILD)jausAddress.o : $(SRC)jausAddress.c
	$(CC) $(CCFLAGS) -o $(BUILD)jausAddress.o $(SRC)jausAddress.c

$(BUILD)jausComponent.o : $(SRC)jausComponent.c
	$(CC) $(CCFLAGS) -o $(BUILD)jausComponent.o $(SRC)jausComponent.c

$(BUILD)jausNode.o : $(SRC)jausNode.c
	$(CC) $(CCFLAGS) -o $(BUILD)jausNode.o $(SRC)jausNode.c

$(BUILD)jausSubsystem.o : $(SRC)jausSubsystem.c
	$(CC) $(CCFLAGS) -o $(BUILD)jausSubsystem.o $(SRC)jausSubsystem.c

$(BUILD)jausState.o : $(SRC)jausState.c
	$(CC) $(CCFLAGS) -o $(BUILD)jausState.o $(SRC)jausState.c

$(BUILD)jausService.o : $(SRC)jausService.c
	$(CC) $(CCFLAGS) -o $(BUILD)jausService.o $(SRC)jausService.c

$(BUILD)jausPayloadInterface.o : $(SRC)jausPayloadInterface.c
	$(CC) $(CCFLAGS) -o $(BUILD)jausPayloadInterface.o $(SRC)jausPayloadInterface.c
