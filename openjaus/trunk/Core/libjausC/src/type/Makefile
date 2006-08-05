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
# ./src/type

INC		=	include/cimar/jaus/
SRC		=	
BUILD	=	Build/
CC		=	gcc
CCFLAGS	=	-Wall -O2 -fPIC -g -c -I$(INC)

OBJECTS =	\
			$(DIRPATH)$(BUILD)jausByte.o \
			$(DIRPATH)$(BUILD)jausDouble.o \
			$(DIRPATH)$(BUILD)jausFloat.o \
			$(DIRPATH)$(BUILD)jausInteger.o \
			$(DIRPATH)$(BUILD)jausLong.o \
			$(DIRPATH)$(BUILD)jausShort.o \
			$(DIRPATH)$(BUILD)jausType.o \
			$(DIRPATH)$(BUILD)jausUnsignedInteger.o \
			$(DIRPATH)$(BUILD)jausUnsignedLong.o \
			$(DIRPATH)$(BUILD)jausUnsignedShort.o \
			$(DIRPATH)$(BUILD)jausEventLimit.o \
			$(DIRPATH)$(BUILD)jausWorldModelFeatureClass.o \
			$(DIRPATH)$(BUILD)jausWorldModelVectorObject.o \
			$(DIRPATH)$(BUILD)jausTime.o \
			
all: $(OBJECTS)

$(DIRPATH)$(BUILD)jausByte.o : $(SRC)jausByte.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)jausByte.o ./jausByte.c

$(DIRPATH)$(BUILD)jausDouble.o : $(SRC)jausDouble.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)jausDouble.o ./jausDouble.c

$(DIRPATH)$(BUILD)jausFloat.o : $(SRC)jausFloat.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)jausFloat.o ./jausFloat.c

$(DIRPATH)$(BUILD)jausInteger.o : $(SRC)jausInteger.c
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)jausInteger.o ./jausInteger.c
	
$(DIRPATH)$(BUILD)jausLong.o : $(SRC)jausLong.c
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)jausLong.o ./jausLong.c

$(DIRPATH)$(BUILD)jausShort.o : $(SRC)jausShort.c
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)jausShort.o ./jausShort.c

$(DIRPATH)$(BUILD)jausUnsignedInteger.o : $(SRC)jausUnsignedInteger.c
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)jausUnsignedInteger.o ./jausUnsignedInteger.c

$(DIRPATH)$(BUILD)jausUnsignedLong.o : $(SRC)jausUnsignedLong.c
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)jausUnsignedLong.o ./jausUnsignedLong.c

$(DIRPATH)$(BUILD)jausUnsignedShort.o : $(SRC)jausUnsignedShort.c
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)jausUnsignedShort.o ./jausUnsignedShort.c

$(DIRPATH)$(BUILD)jausType.o : $(SRC)jausType.c
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)jausType.o ./jausType.c

$(DIRPATH)$(BUILD)jausEventLimit.o : $(SRC)jausEventLimit.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)jausEventLimit.o ./jausEventLimit.c

$(DIRPATH)$(BUILD)jausWorldModelVectorObject.o : $(SRC)jausWorldModelVectorObject.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)jausWorldModelVectorObject.o ./jausWorldModelVectorObject.c

$(DIRPATH)$(BUILD)jausWorldModelFeatureClass.o : $(SRC)jausWorldModelFeatureClass.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)jausWorldModelFeatureClass.o ./jausWorldModelFeatureClass.c

$(DIRPATH)$(BUILD)jausTime.o : $(SRC)jausTime.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)jausTime.o ./jausTime.c
