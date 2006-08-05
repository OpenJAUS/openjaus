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
# ./src/message/command/platform

INC		=	include
SRC		=	
BUILD	=	Build/
CC		=	gcc
CCFLAGS	=	-Wall -O2 -fPIC -g -c

OBJECTS =	\
			$(DIRPATH)$(BUILD)setWrenchEffortMessage.o \
			$(DIRPATH)$(BUILD)setDiscreteDevicesMessage.o \
			$(DIRPATH)$(BUILD)setGlobalVectorMessage.o \
			$(DIRPATH)$(BUILD)setTravelSpeedMessage.o \
			$(DIRPATH)$(BUILD)setVelocityStateMessage.o \
			$(DIRPATH)$(BUILD)setGlobalWaypointMessage.o \

all: $(OBJECTS)

$(DIRPATH)$(BUILD)setWrenchEffortMessage.o : $(SRC)setWrenchEffortMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)setWrenchEffortMessage.o ./setWrenchEffortMessage.c	

$(DIRPATH)$(BUILD)setDiscreteDevicesMessage.o : $(SRC)setDiscreteDevicesMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)setDiscreteDevicesMessage.o ./setDiscreteDevicesMessage.c	
	
$(DIRPATH)$(BUILD)setGlobalVectorMessage.o : $(SRC)setGlobalVectorMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)setGlobalVectorMessage.o ./setGlobalVectorMessage.c	

$(DIRPATH)$(BUILD)setTravelSpeedMessage.o : $(SRC)setTravelSpeedMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)setTravelSpeedMessage.o ./setTravelSpeedMessage.c	

$(DIRPATH)$(BUILD)setGlobalWaypointMessage.o : $(SRC)setGlobalWaypointMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)setGlobalWaypointMessage.o ./setGlobalWaypointMessage.c	

$(DIRPATH)$(BUILD)setVelocityStateMessage.o : $(SRC)setVelocityStateMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)setVelocityStateMessage.o ./setVelocityStateMessage.c	
