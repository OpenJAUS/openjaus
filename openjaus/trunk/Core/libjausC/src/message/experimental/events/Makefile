# ./src/message/experimental/events

INC		=	include
SRC		=	
BUILD	=	Build/
CC		=	gcc
CCFLAGS	=	-Wall -O2 -fPIC -g -c 

OBJECTS =	\
			$(DIRPATH)$(BUILD)createEventMessage.o \
			$(DIRPATH)$(BUILD)confirmEventMessage.o \
			$(DIRPATH)$(BUILD)cancelEventMessage.o \

all: $(OBJECTS)

$(DIRPATH)$(BUILD)createEventMessage.o : $(SRC)createEventMessage.c
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)createEventMessage.o $(SRC)createEventMessage.c

$(DIRPATH)$(BUILD)cancelEventMessage.o : $(SRC)cancelEventMessage.c
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)cancelEventMessage.o $(SRC)cancelEventMessage.c

$(DIRPATH)$(BUILD)confirmEventMessage.o : $(SRC)confirmEventMessage.c
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)confirmEventMessage.o $(SRC)confirmEventMessage.c
	