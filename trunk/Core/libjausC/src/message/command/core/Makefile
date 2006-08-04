# ./src/message/command/core

INC		=	include
SRC		=	
BUILD	=	Build/
CC		=	gcc
CCFLAGS	=	-Wall -O2 -fPIC -g -c 

OBJECTS =	\
			$(DIRPATH)$(BUILD)setComponentAuthorityMessage.o \
			$(DIRPATH)$(BUILD)shutdownMessage.o \
			$(DIRPATH)$(BUILD)standbyMessage.o \
			$(DIRPATH)$(BUILD)resumeMessage.o \
			$(DIRPATH)$(BUILD)resetMessage.o \
			$(DIRPATH)$(BUILD)setEmergencyMessage.o \
			$(DIRPATH)$(BUILD)clearEmergencyMessage.o \
			$(DIRPATH)$(BUILD)createServiceConnectionMessage.o \
			$(DIRPATH)$(BUILD)confirmServiceConnectionMessage.o \
			$(DIRPATH)$(BUILD)activateServiceConnectionMessage.o \
			$(DIRPATH)$(BUILD)suspendServiceConnectionMessage.o \
			$(DIRPATH)$(BUILD)terminateServiceConnectionMessage.o \
			$(DIRPATH)$(BUILD)requestComponentControlMessage.o \
			$(DIRPATH)$(BUILD)releaseComponentControlMessage.o \
			$(DIRPATH)$(BUILD)confirmComponentControlMessage.o \
			$(DIRPATH)$(BUILD)rejectComponentControlMessage.o \
			$(DIRPATH)$(BUILD)setTimeMessage.o \

all: $(OBJECTS)

$(DIRPATH)$(BUILD)setComponentAuthorityMessage.o : $(SRC)setComponentAuthorityMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)setComponentAuthorityMessage.o ./setComponentAuthorityMessage.c

$(DIRPATH)$(BUILD)shutdownMessage.o : $(SRC)shutdownMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)shutdownMessage.o ./shutdownMessage.c

$(DIRPATH)$(BUILD)standbyMessage.o : $(SRC)standbyMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)standbyMessage.o ./standbyMessage.c

$(DIRPATH)$(BUILD)resumeMessage.o : $(SRC)resumeMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)resumeMessage.o ./resumeMessage.c

$(DIRPATH)$(BUILD)resetMessage.o : $(SRC)resetMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)resetMessage.o ./resetMessage.c

$(DIRPATH)$(BUILD)setEmergencyMessage.o : $(SRC)setEmergencyMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)setEmergencyMessage.o ./setEmergencyMessage.c

$(DIRPATH)$(BUILD)clearEmergencyMessage.o : $(SRC)clearEmergencyMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)clearEmergencyMessage.o ./clearEmergencyMessage.c

$(DIRPATH)$(BUILD)createServiceConnectionMessage.o : $(SRC)createServiceConnectionMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)createServiceConnectionMessage.o ./createServiceConnectionMessage.c

$(DIRPATH)$(BUILD)confirmServiceConnectionMessage.o : $(SRC)confirmServiceConnectionMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)confirmServiceConnectionMessage.o ./confirmServiceConnectionMessage.c

$(DIRPATH)$(BUILD)activateServiceConnectionMessage.o : $(SRC)activateServiceConnectionMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)activateServiceConnectionMessage.o ./activateServiceConnectionMessage.c

$(DIRPATH)$(BUILD)suspendServiceConnectionMessage.o : $(SRC)suspendServiceConnectionMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)suspendServiceConnectionMessage.o ./suspendServiceConnectionMessage.c

$(DIRPATH)$(BUILD)terminateServiceConnectionMessage.o : $(SRC)terminateServiceConnectionMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)terminateServiceConnectionMessage.o ./terminateServiceConnectionMessage.c

$(DIRPATH)$(BUILD)requestComponentControlMessage.o : $(SRC)requestComponentControlMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)requestComponentControlMessage.o ./requestComponentControlMessage.c

$(DIRPATH)$(BUILD)releaseComponentControlMessage.o : $(SRC)releaseComponentControlMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)releaseComponentControlMessage.o ./releaseComponentControlMessage.c

$(DIRPATH)$(BUILD)confirmComponentControlMessage.o : $(SRC)confirmComponentControlMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)confirmComponentControlMessage.o ./confirmComponentControlMessage.c

$(DIRPATH)$(BUILD)rejectComponentControlMessage.o : $(SRC)rejectComponentControlMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)rejectComponentControlMessage.o ./rejectComponentControlMessage.c

$(DIRPATH)$(BUILD)setTimeMessage.o : $(SRC)setTimeMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)setTimeMessage.o ./setTimeMessage.c
	