# ./src/message/query/environment

INC		=	include
SRC		=	
BUILD	=	Build/
CC		=	gcc
CCFLAGS	=	-Wall -O2 -fPIC -g -c 

OBJECTS =	\
			$(DIRPATH)$(BUILD)queryVideoFrameMessage.o \

all: $(OBJECTS)

$(DIRPATH)$(BUILD)queryVideoFrameMessage.o : $(SRC)queryVideoFrameMessage.c
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)queryVideoFrameMessage.o ./queryVideoFrameMessage.c	