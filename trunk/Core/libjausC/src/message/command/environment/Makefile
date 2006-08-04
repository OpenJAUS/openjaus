# ./src/message/command/environment

INC		=	include
SRC		=	
BUILD	=	Build/
CC		=	gcc
CCFLAGS	=	-Wall -O2 -fPIC -g -c 

OBJECTS =	\
			$(DIRPATH)$(BUILD)selectCameraMessage.o \

all: $(OBJECTS)

$(DIRPATH)$(BUILD)selectCameraMessage.o : $(SRC)selectCameraMessage.c
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)selectCameraMessage.o ./selectCameraMessage.c	