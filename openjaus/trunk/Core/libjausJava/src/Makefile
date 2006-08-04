# src DIR
SRC = jaus/
BUILD = ../Build/
LIB = ../lib/

all: 
	@cd $(SRC); make "DIRPATH=../" "BUILD=$(BUILD)" "BINDIR=$(BINDIR)";

clean:
	rm -rf $(LIB)*
	rm -rf $(BUILD)class/*
	rm -rf $(BUILD)object/*