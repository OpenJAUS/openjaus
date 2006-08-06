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

EXE		=	test
BIN		=	./bin/
BUILD	=	./Build/
INC		=	./include/
UTM		=	./include/cimar/utm/
LIB		=	./lib/
SRC		=	./src/
LIBS	=	-lrt -lm
CC		=	gcc
CCFLAGS	=	-Wall -fPIC -g -c -I$(INC) -I$(UTM)
LFLAGS	=	-I$(INC) -I$(UTM)

OBJECTS =	\
			$(BUILD)bres.o \
			$(BUILD)datagramPacket.o \
			$(BUILD)datagramSocket.o \
			$(BUILD)inetAddress.o \
			$(BUILD)logLib.o \
			$(BUILD)multicastSocket.o \
			$(BUILD)networkInterface.o \
			$(BUILD)portLib.o \
			$(BUILD)properties.o \
			$(BUILD)queue.o \
			$(BUILD)timeLib.o \
			$(BUILD)vector.o \
			$(BUILD)greatCircle.o \
			$(BUILD)torusBuffer.o \
			$(BUILD)pointGg.o \
			$(BUILD)pointLla.o \
			$(BUILD)pointUtm.o \
			$(BUILD)cproj.o \
			$(BUILD)utmfor.o \
			$(BUILD)utminv.o \
			$(BUILD)utmLib.o \

LIBRARY = libcimar.so

default: $(LIBRARY)

test: $(BIN)$(EXE)

all: $(LIBRARY)

$(LIBRARY) : $(OBJECTS)
	gcc -shared -o $(LIB)$(LIBRARY) $(BUILD)*.o $(LIBS)
	
$(BUILD)bres.o : $(SRC)bres.c
	$(CC) $(CCFLAGS) -o $(BUILD)bres.o $(SRC)bres.c

$(BUILD)datagramPacket.o : $(SRC)datagramPacket.c
	$(CC) $(CCFLAGS) -o $(BUILD)datagramPacket.o $(SRC)datagramPacket.c

$(BUILD)datagramSocket.o : $(SRC)datagramSocket.c
	$(CC) $(CCFLAGS) -o $(BUILD)datagramSocket.o $(SRC)datagramSocket.c

$(BUILD)inetAddress.o : $(SRC)inetAddress.c
	$(CC) $(CCFLAGS) -o $(BUILD)inetAddress.o $(SRC)inetAddress.c

$(BUILD)logLib.o : $(SRC)logLib.c
	$(CC) $(CCFLAGS) -o $(BUILD)logLib.o $(SRC)logLib.c

$(BUILD)multicastSocket.o : $(SRC)multicastSocket.c
	$(CC) $(CCFLAGS) -o $(BUILD)multicastSocket.o $(SRC)multicastSocket.c

$(BUILD)networkInterface.o : $(SRC)networkInterface.c
	$(CC) $(CCFLAGS) -o $(BUILD)networkInterface.o $(SRC)networkInterface.c

$(BUILD)portLib.o : $(SRC)portLib.c
	$(CC) $(CCFLAGS) -o $(BUILD)portLib.o $(SRC)portLib.c

$(BUILD)properties.o : $(SRC)properties.c
	$(CC) $(CCFLAGS) -o $(BUILD)properties.o $(SRC)properties.c

$(BUILD)queue.o : $(SRC)queue.c
	$(CC) $(CCFLAGS) -o $(BUILD)queue.o $(SRC)queue.c

$(BUILD)timeLib.o : $(SRC)timeLib.c
	$(CC) $(CCFLAGS) -o $(BUILD)timeLib.o $(SRC)timeLib.c

$(BUILD)vector.o : $(SRC)vector.c
	$(CC) $(CCFLAGS) -o $(BUILD)vector.o $(SRC)vector.c

$(BUILD)greatCircle.o : $(SRC)greatCircle.c
	$(CC) $(CCFLAGS) -o $(BUILD)greatCircle.o $(SRC)greatCircle.c

$(BUILD)torusBuffer.o : $(SRC)torusBuffer.c
	$(CC) $(CCFLAGS) -o $(BUILD)torusBuffer.o $(SRC)torusBuffer.c

$(BUILD)pointGg.o : $(SRC)pointGg.c
	$(CC) $(CCFLAGS) -o $(BUILD)pointGg.o $(SRC)pointGg.c

$(BUILD)pointUtm.o : $(SRC)pointUtm.c
	$(CC) $(CCFLAGS) -o $(BUILD)pointUtm.o $(SRC)pointUtm.c

$(BUILD)pointLla.o : $(SRC)pointLla.c
	$(CC) $(CCFLAGS) -o $(BUILD)pointLla.o $(SRC)pointLla.c

$(BUILD)cproj.o : $(SRC)utm/cproj.c
	$(CC) $(CCFLAGS) -o $(BUILD)cproj.o $(SRC)utm/cproj.c

$(BUILD)utmfor.o : $(SRC)utm/utmfor.c
	$(CC) $(CCFLAGS) -o $(BUILD)utmfor.o $(SRC)utm/utmfor.c

$(BUILD)utminv.o : $(SRC)utm/utminv.c
	$(CC) $(CCFLAGS) -o $(BUILD)utminv.o $(SRC)utm/utminv.c

$(BUILD)utmLib.o : $(SRC)utm/utmLib.c
	$(CC) $(CCFLAGS) -o $(BUILD)utmLib.o $(SRC)utm/utmLib.c

clean:
	rm -fv $(LIB)*
	rm -fv $(BUILD)*
	rm -fv $(BIN)$(EXE)

install:
	./Install
	
uninstall:
	./Uninstall
	
