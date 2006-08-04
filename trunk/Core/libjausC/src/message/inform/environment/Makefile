# ./src/message/inform/environment

INC		=	include
SRC		=	
BUILD	=	Build/
CC		=	gcc
CCFLAGS	=	-Wall -O2 -fPIC -g -c 

OBJECTS =	\
			$(DIRPATH)$(BUILD)reportVideoFrameMessage.o \

all: $(OBJECTS)

$(DIRPATH)$(BUILD)reportVideoFrameMessage.o : $(SRC)reportVideoFrameMessage.c
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)reportVideoFrameMessage.o ./reportVideoFrameMessage.c	