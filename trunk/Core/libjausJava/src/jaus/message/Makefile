# /src/jaus/message

BINDIR	=	./bin/
SRC		=	./
BUILD	=	./Build/
DIRPATH = 	./
INCLUDE = 	-I$(DIRPATH)
CC		=	gcj
CCFLAGS	=	-Wall -c $(INCLUDE) -I$(DIRPATH)
JARFLAGS = 	-Wall -C $(INCLUDE) -I$(DIRPATH)

all:
	$(CC) $(CCFLAGS) -o $(DIRPATH)$(BUILD)object/Jaus.Message.o *.java
	$(CC) $(JARFLAGS) -d $(DIRPATH)$(BUILD)class/ *.java
	@cd ./command; make "INCLUDE += -I$(DIRPATH)" "DIRPATH = ../$(DIRPATH)";
	@cd ./experimental; make "INCLUDE += -I$(DIRPATH)" "DIRPATH = ../$(DIRPATH)";
	@cd ./inform; make "INCLUDE += -I$(DIRPATH)" "DIRPATH = ../$(DIRPATH)";
	@cd ./query; make "INCLUDE += -I$(DIRPATH)" "DIRPATH = ../$(DIRPATH)";	