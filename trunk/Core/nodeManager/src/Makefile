# /src

EXE		=	nodeManager
BINDIR	=	./bin/
SRC		=	./
BUILD	=	./Build/
DIRPATH = 	./
INCLUDE = 	-I$(DIRPATH)
CC		=	gcj
CCFLAGS	=	-Wall -c $(INCLUDE) -I$(DIRPATH) -I/usr/include/cimar/cimarJaus.jar
LIBS	=	-lcimarJausJava
LFLAGS	=	--main=NodeManager

all:
	$(CC) $(CCFLAGS) -o $(DIRPATH)$(BUILD)NodeManager.o *.java
	$(CC) $(LFLAGS) -o $(DIRPATH)$(BINDIR)$(EXE) $(DIRPATH)$(BUILD)*.o $(LIBS)

clean:
	rm -rf $(DIRPATH)$(BUILD)*
	rm -f $(DIRPATH)$(BINDIR)$(EXE)
