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
