EXE		=	node
BINDIR	=	./bin/
INC		=	./include/ 
SRC		=	./src/
BUILD	=	./Build/
LIBS	=	-lm -lpthread -lcurses  -lcimar -ljausC -lnodeManager
CC		=	gcc
CCFLAGS	=	-Wall -O2 -c -g -I$(INC)
LFLAGS	=	-I$(INC)

OBJECTS =	\
			$(BUILD)cmpt.o \
			$(BUILD)main.o \
			$(BUILD)node.o \

default: $(BINDIR)$(EXE)

all: $(OBJECTS) $(BINDIR)$(EXE)

$(BINDIR)$(EXE) : $(OBJECTS)
	$(CC) $(LFLAGS) -o $(BINDIR)$(EXE) $(OBJECTS) $(LIBS) 

$(BUILD)cmpt.o : $(SRC)cmpt.c
	$(CC) $(CCFLAGS) -o $(BUILD)cmpt.o $(SRC)cmpt.c

$(BUILD)main.o : $(SRC)main.c
	$(CC) $(CCFLAGS) -o $(BUILD)main.o $(SRC)main.c

$(BUILD)node.o : $(SRC)node.c
	$(CC) $(CCFLAGS) -o $(BUILD)node.o $(SRC)node.c

clean:
	rm -fv $(BUILD)*.o
	rm -fv $(BINDIR)$(EXE)
