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
# ./src/message/experimental

INC		=	include
SRC		=	
BUILD	=	Build/
CC		=	gcc
CCFLAGS	=	-Wall -O2 -fPIC -g -c 

OBJECTS =	\
			$(DIRPATH)$(BUILD)queryIdentificationMessage.o \
			$(DIRPATH)$(BUILD)reportIdentificationMessage.o \
			$(DIRPATH)$(BUILD)queryConfigurationMessage.o \
			$(DIRPATH)$(BUILD)reportConfigurationMessage.o \
			$(DIRPATH)$(BUILD)configurationChangedEventSetupMessage.o \
			$(DIRPATH)$(BUILD)configurationChangedEventNotificationMessage.o \
			$(DIRPATH)$(BUILD)queryServicesMessage.o \
			$(DIRPATH)$(BUILD)reportServicesMessage.o \
			$(DIRPATH)$(BUILD)queryPayloadDataElementMessage.o \
			$(DIRPATH)$(BUILD)queryPayloadInterfaceMessage.o \
			$(DIRPATH)$(BUILD)reportPayloadDataElementMessage.o \
			$(DIRPATH)$(BUILD)reportPayloadInterfaceMessage.o \
			$(DIRPATH)$(BUILD)setPayloadDataElementMessage.o \


all: $(OBJECTS)
	@cd ./events; make "DIRPATH=../$(DIRPATH)" "BUILD=$(BUILD)" "BINDIR=$(BINDIR)" "INC=$(INC)";
	@cd ./worldModel; make "DIRPATH=../$(DIRPATH)" "BUILD=$(BUILD)" "BINDIR=$(BINDIR)" "INC=$(INC)";
	
$(DIRPATH)$(BUILD)queryIdentificationMessage.o : $(SRC)queryIdentificationMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)queryIdentificationMessage.o ./queryIdentificationMessage.c	

$(DIRPATH)$(BUILD)reportIdentificationMessage.o : $(SRC)reportIdentificationMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)reportIdentificationMessage.o ./reportIdentificationMessage.c	

$(DIRPATH)$(BUILD)queryConfigurationMessage.o : $(SRC)queryConfigurationMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)queryConfigurationMessage.o ./queryConfigurationMessage.c	

$(DIRPATH)$(BUILD)reportConfigurationMessage.o : $(SRC)reportConfigurationMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)reportConfigurationMessage.o ./reportConfigurationMessage.c	

$(DIRPATH)$(BUILD)configurationChangedEventSetupMessage.o : $(SRC)configurationChangedEventSetupMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)configurationChangedEventSetupMessage.o ./configurationChangedEventSetupMessage.c	

$(DIRPATH)$(BUILD)configurationChangedEventNotificationMessage.o : $(SRC)configurationChangedEventNotificationMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)configurationChangedEventNotificationMessage.o ./configurationChangedEventNotificationMessage.c	

$(DIRPATH)$(BUILD)queryServicesMessage.o : $(SRC)queryServicesMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)queryServicesMessage.o ./queryServicesMessage.c	

$(DIRPATH)$(BUILD)reportServicesMessage.o : $(SRC)reportServicesMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)reportServicesMessage.o ./reportServicesMessage.c	

$(DIRPATH)$(BUILD)queryPayloadDataElementMessage.o : $(SRC)queryPayloadDataElementMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)queryPayloadDataElementMessage.o ./queryPayloadDataElementMessage.c	

$(DIRPATH)$(BUILD)queryPayloadInterfaceMessage.o : $(SRC)queryPayloadInterfaceMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)queryPayloadInterfaceMessage.o ./queryPayloadInterfaceMessage.c	

$(DIRPATH)$(BUILD)reportPayloadDataElementMessage.o : $(SRC)reportPayloadDataElementMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)reportPayloadDataElementMessage.o ./reportPayloadDataElementMessage.c	

$(DIRPATH)$(BUILD)reportPayloadInterfaceMessage.o : $(SRC)reportPayloadInterfaceMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)reportPayloadInterfaceMessage.o ./reportPayloadInterfaceMessage.c	

$(DIRPATH)$(BUILD)setPayloadDataElementMessage.o : $(SRC)setPayloadDataElementMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)setPayloadDataElementMessage.o ./setPayloadDataElementMessage.c	
