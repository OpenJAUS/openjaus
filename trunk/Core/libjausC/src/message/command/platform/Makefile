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
