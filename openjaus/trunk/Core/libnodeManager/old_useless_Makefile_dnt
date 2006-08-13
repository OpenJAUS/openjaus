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
