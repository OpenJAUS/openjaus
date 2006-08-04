# ./src/message/query/communications

INC		=	include
SRC		=	
BUILD	=	Build/
CC		=	gcc
CCFLAGS	=	-Wall -O2 -fPIC -g -c 

OBJECTS =	\
			$(DIRPATH)$(BUILD)queryHeartbeatPulseMessage.o \

all: $(OBJECTS)

$(DIRPATH)$(BUILD)queryHeartbeatPulseMessage.o : $(SRC)queryHeartbeatPulseMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)queryHeartbeatPulseMessage.o ./queryHeartbeatPulseMessage.c	