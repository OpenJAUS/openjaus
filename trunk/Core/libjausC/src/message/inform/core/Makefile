# ./src/message/inform/core

INC		=	include
SRC		=	
BUILD	=	Build/
CC		=	gcc
CCFLAGS	=	-Wall -O2 -fPIC -g -c 

OBJECTS =	\
			$(DIRPATH)$(BUILD)reportComponentAuthorityMessage.o \
			$(DIRPATH)$(BUILD)reportComponentStatusMessage.o \
			$(DIRPATH)$(BUILD)reportTimeMessage.o \


all: $(OBJECTS)

$(DIRPATH)$(BUILD)reportComponentStatusMessage.o : $(SRC)reportComponentStatusMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)reportComponentStatusMessage.o ./reportComponentStatusMessage.c

$(DIRPATH)$(BUILD)reportComponentAuthorityMessage.o : $(SRC)reportComponentAuthorityMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)reportComponentAuthorityMessage.o ./reportComponentAuthorityMessage.c

$(DIRPATH)$(BUILD)reportTimeMessage.o : $(SRC)reportTimeMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)reportTimeMessage.o ./reportTimeMessage.c