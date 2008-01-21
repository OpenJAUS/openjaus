EXE		=	vehicleSim
BINDIR	=	./bin/
INC		=	./include/ 
SRC		=	./src/
BUILD	=	./Build/
LIBS	=	-lm -lpthread -lcurses -lnodeManager -ljausC -lcimar
CC		=	gcc
CCFLAGS	=	-Wall -O2 -g -c -I$(INC)
LFLAGS	=	-I$(INC)

OBJECTS =	\
			$(BUILD)gpos.o \
			$(BUILD)pd.o \
			$(BUILD)main.o \
			$(BUILD)simulator.o \
			$(BUILD)vehicle.o \
			$(BUILD)wd.o \
			$(BUILD)vehicleSim.o \
			$(BUILD)vss.o \

default: $(BINDIR)$(EXE)

all: $(OBJECTS) $(BINDIR)$(EXE)

$(BINDIR)$(EXE) : $(OBJECTS)
	$(CC) $(LFLAGS) -o $(BINDIR)$(EXE) $(OBJECTS) $(LIBS) 

$(BUILD)gpos.o : $(SRC)gpos.c
	$(CC) $(CCFLAGS) -o $(BUILD)gpos.o $(SRC)gpos.c

$(BUILD)pd.o : $(SRC)pd.c
	$(CC) $(CCFLAGS) -o $(BUILD)pd.o $(SRC)pd.c

$(BUILD)main.o : $(SRC)main.c
	$(CC) $(CCFLAGS) -o $(BUILD)main.o $(SRC)main.c

$(BUILD)simulator.o : $(SRC)simulator.c
	$(CC) $(CCFLAGS) -o $(BUILD)simulator.o $(SRC)simulator.c

$(BUILD)vehicleSim.o : $(SRC)vehicleSim.c
	$(CC) $(CCFLAGS) -o $(BUILD)vehicleSim.o $(SRC)vehicleSim.c

$(BUILD)vss.o : $(SRC)vss.c
	$(CC) $(CCFLAGS) -o $(BUILD)vss.o $(SRC)vss.c

$(BUILD)wd.o : $(SRC)wd.c
	$(CC) $(CCFLAGS) -o $(BUILD)wd.o $(SRC)wd.c

$(BUILD)vehicle.o : $(SRC)vehicle.c
	$(CC) $(CCFLAGS) -o $(BUILD)vehicle.o $(SRC)vehicle.c

clean:
	rm -f $(BUILD)*.o
	rm -f $(BINDIR)$(EXE)
