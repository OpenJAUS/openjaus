# ./src/message/inform/comminications

INC		=	include
SRC		=	
BUILD	=	Build/
CC		=	gcc
CCFLAGS	=	-Wall -O2 -fPIC -g -c 

OBJECTS =	\
			$(DIRPATH)$(BUILD)reportHeartbeatPulseMessage.o \

all: $(OBJECTS)

$(DIRPATH)$(BUILD)reportHeartbeatPulseMessage.o : $(SRC)reportHeartbeatPulseMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)reportHeartbeatPulseMessage.o ./reportHeartbeatPulseMessage.c	