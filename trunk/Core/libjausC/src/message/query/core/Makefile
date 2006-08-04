# ./src/message/query/core

INC		=	include
SRC		=	
BUILD	=	Build/
CC		=	gcc
CCFLAGS	=	-Wall -O2 -fPIC -g -c 

OBJECTS =	\
			$(DIRPATH)$(BUILD)queryComponentAuthorityMessage.o \
			$(DIRPATH)$(BUILD)queryComponentStatusMessage.o \
			$(DIRPATH)$(BUILD)queryTimeMessage.o \

all: $(OBJECTS)

$(DIRPATH)$(BUILD)queryComponentAuthorityMessage.o : $(SRC)queryComponentAuthorityMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)queryComponentAuthorityMessage.o ./queryComponentAuthorityMessage.c

$(DIRPATH)$(BUILD)queryComponentStatusMessage.o : $(SRC)queryComponentStatusMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)queryComponentStatusMessage.o ./queryComponentStatusMessage.c

$(DIRPATH)$(BUILD)queryTimeMessage.o : $(SRC)queryTimeMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)queryTimeMessage.o ./queryTimeMessage.c

	