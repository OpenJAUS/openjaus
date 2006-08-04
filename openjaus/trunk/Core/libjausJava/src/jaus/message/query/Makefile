# /src/jaus/message/query

BINDIR	=	./bin/
SRC		=	./
BUILD	=	./Build/
DIRPATH = 	./
INCLUDE = 	-I$(DIRPATH)
CC		=	gcj
CCFLAGS	=	-Wall -c $(INCLUDE) -I$(DIRPATH)
JARFLAGS = 	-Wall -C $(INCLUDE) -I$(DIRPATH)

all:
	$(CC) $(CCFLAGS) -o $(DIRPATH)$(BUILD)object/Jaus.Message.Query.o *.java
	$(CC) $(JARFLAGS) -d $(DIRPATH)$(BUILD)class/ *.java

	