# ./src/message

INC		=	include/cimar/jaus/
SRC		=	
BUILD	=	Build/
CC		=	gcc
CCFLAGS	=	-Wall -O2 -fPIC -g -c -I$(INC)

OBJECTS =	\
			$(DIRPATH)$(BUILD)jausMessage.o \
			$(DIRPATH)$(BUILD)jausBytePresenceVector.o \
			$(DIRPATH)$(BUILD)jausShortPresenceVector.o \
			$(DIRPATH)$(BUILD)jausIntegerPresenceVector.o \
#			$(DIRPATH)$(BUILD)skeletonMessage.o \

all: $(OBJECTS)
	@cd ./command; make "DIRPATH=../$(DIRPATH)" "BUILD=$(BUILD)" "BINDIR=$(BINDIR)" "INC=$(INC)";
	@cd ./inform; make "DIRPATH=../$(DIRPATH)" "BUILD=$(BUILD)" "BINDIR=$(BINDIR)" "INC=$(INC)";
	@cd ./query; make "DIRPATH=../$(DIRPATH)" "BUILD=$(BUILD)" "BINDIR=$(BINDIR)" "INC=$(INC)";
	@cd ./experimental; make "DIRPATH=../$(DIRPATH)" "BUILD=$(BUILD)" "BINDIR=$(BINDIR)" "INC=$(INC)";

$(DIRPATH)$(BUILD)jausMessage.o : $(SRC)jausMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)jausMessage.o ./jausMessage.c	

$(DIRPATH)$(BUILD)jausBytePresenceVector.o : $(SRC)jausBytePresenceVector.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)jausBytePresenceVector.o ./jausBytePresenceVector.c	

$(DIRPATH)$(BUILD)jausIntegerPresenceVector.o : $(SRC)jausIntegerPresenceVector.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)jausIntegerPresenceVector.o ./jausIntegerPresenceVector.c		

$(DIRPATH)$(BUILD)jausShortPresenceVector.o : $(SRC)jausShortPresenceVector.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)jausShortPresenceVector.o ./jausShortPresenceVector.c		

$(DIRPATH)$(BUILD)skeletonMessage.o : $(SRC)skeletonMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)skeletonMessage.o ./skeletonMessage.c		
	