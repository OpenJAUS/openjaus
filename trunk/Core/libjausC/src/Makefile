# ./src/
BINDIR	=	../bin/
INC		=	../include/
SRC		=	./
BUILD	=	../Build/
LIBS	=	
CC		=	gcc
CCFLAGS	=	-Wall -O2 -fPIC -g -c -I$(INC)

OBJECTS =	\
			$(BUILD)jausAddress.o \
			$(BUILD)jausComponent.o \
			$(BUILD)jausNode.o \
			$(BUILD)jausSubsystem.o \
			$(BUILD)jausState.o \
			$(BUILD)jausService.o \
			$(BUILD)jausPayloadInterface.o \

all: $(OBJECTS)
	@cd ./type; make "DIRPATH=../$(DIRPATH)" "BUILD=$(BUILD)" "BINDIR=$(BINDIR)" "INC=$(INC)";
	@cd ./message; make "DIRPATH=../$(DIRPATH)" "BUILD=$(BUILD)" "BINDIR=$(BINDIR)" "INC=$(INC)";
	
$(BUILD)jausAddress.o : $(SRC)jausAddress.c
	$(CC) $(CCFLAGS) -o $(BUILD)jausAddress.o $(SRC)jausAddress.c

$(BUILD)jausComponent.o : $(SRC)jausComponent.c
	$(CC) $(CCFLAGS) -o $(BUILD)jausComponent.o $(SRC)jausComponent.c

$(BUILD)jausNode.o : $(SRC)jausNode.c
	$(CC) $(CCFLAGS) -o $(BUILD)jausNode.o $(SRC)jausNode.c

$(BUILD)jausSubsystem.o : $(SRC)jausSubsystem.c
	$(CC) $(CCFLAGS) -o $(BUILD)jausSubsystem.o $(SRC)jausSubsystem.c

$(BUILD)jausState.o : $(SRC)jausState.c
	$(CC) $(CCFLAGS) -o $(BUILD)jausState.o $(SRC)jausState.c

$(BUILD)jausService.o : $(SRC)jausService.c
	$(CC) $(CCFLAGS) -o $(BUILD)jausService.o $(SRC)jausService.c

$(BUILD)jausPayloadInterface.o : $(SRC)jausPayloadInterface.c
	$(CC) $(CCFLAGS) -o $(BUILD)jausPayloadInterface.o $(SRC)jausPayloadInterface.c
