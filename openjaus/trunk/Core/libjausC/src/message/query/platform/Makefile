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
# ./src/message/query/environment

INC		=	include
SRC		=	
BUILD	=	Build/
CC		=	gcc
CCFLAGS	=	-Wall -O2 -fPIC -g -c 

OBJECTS =	\
			$(DIRPATH)$(BUILD)queryPlatformSpecificationsMessage.o \
			$(DIRPATH)$(BUILD)queryPlatformOperationalDataMessage.o \
			$(DIRPATH)$(BUILD)queryGlobalPoseMessage.o \
			$(DIRPATH)$(BUILD)queryVelocityStateMessage.o \
			$(DIRPATH)$(BUILD)queryWrenchEffortMessage.o \
			$(DIRPATH)$(BUILD)queryDiscreteDevicesMessage.o \
			$(DIRPATH)$(BUILD)queryGlobalVectorMessage.o \
			$(DIRPATH)$(BUILD)queryTravelSpeedMessage.o \
			$(DIRPATH)$(BUILD)queryWaypointCountMessage.o \
			$(DIRPATH)$(BUILD)queryGlobalWaypointMessage.o \

all: $(OBJECTS)

$(DIRPATH)$(BUILD)queryPlatformSpecificationsMessage.o : $(SRC)queryPlatformSpecificationsMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)queryPlatformSpecificationsMessage.o ./queryPlatformSpecificationsMessage.c	
	
$(DIRPATH)$(BUILD)queryPlatformOperationalDataMessage.o : $(SRC)queryPlatformOperationalDataMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)queryPlatformOperationalDataMessage.o ./queryPlatformOperationalDataMessage.c

$(DIRPATH)$(BUILD)queryGlobalPoseMessage.o : $(SRC)queryGlobalPoseMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)queryGlobalPoseMessage.o ./queryGlobalPoseMessage.c	

$(DIRPATH)$(BUILD)queryVelocityStateMessage.o : $(SRC)queryVelocityStateMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)queryVelocityStateMessage.o ./queryVelocityStateMessage.c	

$(DIRPATH)$(BUILD)queryWrenchEffortMessage.o : $(SRC)queryWrenchEffortMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)queryWrenchEffortMessage.o ./queryWrenchEffortMessage.c	

$(DIRPATH)$(BUILD)queryWaypointCountMessage.o : $(SRC)queryWaypointCountMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)queryWaypointCountMessage.o ./queryWaypointCountMessage.c	

$(DIRPATH)$(BUILD)queryTravelSpeedMessage.o : $(SRC)queryTravelSpeedMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)queryTravelSpeedMessage.o ./queryTravelSpeedMessage.c	

$(DIRPATH)$(BUILD)queryGlobalVectorMessage.o : $(SRC)queryGlobalVectorMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)queryGlobalVectorMessage.o ./queryGlobalVectorMessage.c	

$(DIRPATH)$(BUILD)queryDiscreteDevicesMessage.o : $(SRC)queryDiscreteDevicesMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)queryDiscreteDevicesMessage.o ./queryDiscreteDevicesMessage.c	

$(DIRPATH)$(BUILD)queryGlobalWaypointMessage.o : $(SRC)queryGlobalWaypointMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)queryGlobalWaypointMessage.o ./queryGlobalWaypointMessage.c	


$(DIRPATH)$(BUILD)jausMessage.o : $(SRC)jausMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)jausMessage.o ./jausMessage.c	
