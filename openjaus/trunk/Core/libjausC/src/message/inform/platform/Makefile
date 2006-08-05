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
# ./src/message/inform/platform

INC		=	include
SRC		=	
BUILD	=	Build/
CC		=	gcc
CCFLAGS	=	-Wall -O2 -fPIC -g -c 

OBJECTS =	\
			$(DIRPATH)$(BUILD)reportPlatformSpecificationsMessage.o \
			$(DIRPATH)$(BUILD)reportPlatformOperationalDataMessage.o \
			$(DIRPATH)$(BUILD)reportGlobalPoseMessage.o \
			$(DIRPATH)$(BUILD)reportVelocityStateMessage.o \
			$(DIRPATH)$(BUILD)reportWrenchEffortMessage.o \
			$(DIRPATH)$(BUILD)reportDiscreteDevicesMessage.o \
			$(DIRPATH)$(BUILD)reportGlobalVectorMessage.o \
			$(DIRPATH)$(BUILD)reportTravelSpeedMessage.o \
			$(DIRPATH)$(BUILD)reportWaypointCountMessage.o \
			$(DIRPATH)$(BUILD)reportGlobalWaypointMessage.o \

all: $(OBJECTS)

$(DIRPATH)$(BUILD)reportPlatformSpecificationsMessage.o : $(SRC)reportPlatformSpecificationsMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)reportPlatformSpecificationsMessage.o ./reportPlatformSpecificationsMessage.c	

$(DIRPATH)$(BUILD)reportPlatformOperationalDataMessage.o : $(SRC)reportPlatformOperationalDataMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)reportPlatformOperationalDataMessage.o ./reportPlatformOperationalDataMessage.c	

$(DIRPATH)$(BUILD)reportGlobalPoseMessage.o : $(SRC)reportGlobalPoseMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)reportGlobalPoseMessage.o ./reportGlobalPoseMessage.c	

$(DIRPATH)$(BUILD)reportVelocityStateMessage.o : $(SRC)reportVelocityStateMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)reportVelocityStateMessage.o ./reportVelocityStateMessage.c	

$(DIRPATH)$(BUILD)reportWrenchEffortMessage.o : $(SRC)reportWrenchEffortMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)reportWrenchEffortMessage.o ./reportWrenchEffortMessage.c	

$(DIRPATH)$(BUILD)reportDiscreteDevicesMessage.o : $(SRC)reportDiscreteDevicesMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)reportDiscreteDevicesMessage.o ./reportDiscreteDevicesMessage.c	

$(DIRPATH)$(BUILD)reportGlobalVectorMessage.o : $(SRC)reportGlobalVectorMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)reportGlobalVectorMessage.o ./reportGlobalVectorMessage.c	

$(DIRPATH)$(BUILD)reportTravelSpeedMessage.o : $(SRC)reportTravelSpeedMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)reportTravelSpeedMessage.o ./reportTravelSpeedMessage.c	

$(DIRPATH)$(BUILD)reportWaypointCountMessage.o : $(SRC)reportWaypointCountMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)reportWaypointCountMessage.o ./reportWaypointCountMessage.c	

$(DIRPATH)$(BUILD)reportGlobalWaypointMessage.o : $(SRC)reportGlobalWaypointMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)reportGlobalWaypointMessage.o ./reportGlobalWaypointMessage.c	



$(DIRPATH)$(BUILD)jausMessage.o : $(SRC)jausMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)jausMessage.o ./jausMessage.c	