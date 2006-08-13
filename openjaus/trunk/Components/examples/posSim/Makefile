##############################################################################
#   Copyright (c) 2006, University of Florida.
#   All rights reserved.
#   
#   This file is part of OpenJAUS.  OpenJAUS is distributed under the BSD 
#   license.  See the LICENSE file for details.
#  
#   Redistribution and use in source and binary forms, with or without 
#   modification, are permitted provided that the following conditions 
#   are met:
# 
#      * Redistributions of source code must retain the above copyright
#        notice, this list of conditions and the following disclaimer.
#      * Redistributions in binary form must reproduce the above
#        copyright notice, this list of conditions and the following
#        disclaimer in the documentation and/or other materials provided
#        with the distribution.
#      * Neither the name of the University of Florida nor the names of its 
#        contributors may be used to endorse or promote products derived from 
#        this software without specific prior written permission.
# 
#    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
#    "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
#    LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR 
#    A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
#    OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
#    SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
#    LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, 
#    DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY 
#    THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
#    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
#    OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
##############################################################################
EXE		=	posSim
BINDIR	=	./bin/
INC		=	./include/ 
SRC		=	./src/
BUILD	=	./Build/
LIBS	=	-lm -lpthread -lcurses -lnodeManager -ljausC -lcimar
CC		=	gcc
CCFLAGS	=	-Wall -O2 -c -g -I$(INC)
LFLAGS	=	-I$(INC)

OBJECTS =	\
			$(BUILD)gpos.o \
			$(BUILD)vss.o \
			$(BUILD)rddf.o \
			$(BUILD)main.o \
			$(BUILD)node.o \


default: $(BINDIR)$(EXE)

all: $(OBJECTS) $(BINDIR)$(EXE)

$(BINDIR)$(EXE) : $(OBJECTS)
	$(CC) $(LFLAGS) -o $(BINDIR)$(EXE) $(OBJECTS) $(LIBS) 

$(BUILD)vss.o : $(SRC)vss.c
	$(CC) $(CCFLAGS) -o $(BUILD)vss.o $(SRC)vss.c

$(BUILD)gpos.o : $(SRC)gpos.c
	$(CC) $(CCFLAGS) -o $(BUILD)gpos.o $(SRC)gpos.c

$(BUILD)main.o : $(SRC)main.c
	$(CC) $(CCFLAGS) -o $(BUILD)main.o $(SRC)main.c

$(BUILD)node.o : $(SRC)node.c
	$(CC) $(CCFLAGS) -o $(BUILD)node.o $(SRC)node.c

$(BUILD)rddf.o : $(SRC)rddf.c
	$(CC) $(CCFLAGS) -o $(BUILD)rddf.o $(SRC)rddf.c
	
clean:
	rm -f $(BUILD)*.o
	rm -f $(BINDIR)$(EXE)
