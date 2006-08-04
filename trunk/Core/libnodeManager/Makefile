BUILD	=	./Build/
INC	=	./include/
LIB	=	./lib/
SRC	=	./src/
LIBS	=	-lpthread -lcimar -ljausC
CC	=	gcc
CCFLAGS	=	-Wall -fPIC -g -c -I$(INC)
LFLAGS	=	-I$(INC)

OBJECTS =	\
			$(BUILD)libNodeManager.o \
			$(BUILD)lmHandler.o \
			$(BUILD)scManager.o \
			$(BUILD)defaultJausMessageProcessor.o \

HEADER = nodeManager.h

LIBRARY = libnodeManager.so

default: $(LIBRARY)

all: $(LIBRARY)

$(LIBRARY) : $(OBJECTS)
	gcc -shared -o $(LIB)$(LIBRARY) $(OBJECTS) $(LIBS)

$(BUILD)lmHandler.o : $(SRC)lmHandler.c
	$(CC) $(CCFLAGS) -o $(BUILD)lmHandler.o $(SRC)lmHandler.c

$(BUILD)libNodeManager.o : $(SRC)libNodeManager.c
	$(CC) $(CCFLAGS) -o $(BUILD)libNodeManager.o $(SRC)libNodeManager.c

$(BUILD)scManager.o : $(SRC)scManager.c
	$(CC) $(CCFLAGS) -o $(BUILD)scManager.o $(SRC)scManager.c

$(BUILD)defaultJausMessageProcessor.o : $(SRC)defaultJausMessageProcessor.c
	$(CC) $(CCFLAGS) -o $(BUILD)defaultJausMessageProcessor.o $(SRC)defaultJausMessageProcessor.c

clean:
	rm -fv $(LIB)*
	rm -fv $(BUILD)*

install:
	./Install

uninstall:
	./Uninstall
