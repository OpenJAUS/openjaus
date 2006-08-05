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
# ./src/message/experimental/worldModel

INC		=	include
SRC		=	
BUILD	=	Build/
CC		=	gcc
CCFLAGS	=	-Wall -O2 -fPIC -g -c 

OBJECTS =	\
			$(DIRPATH)$(BUILD)createVksObjectsMessage.o \
			$(DIRPATH)$(BUILD)deleteVksObjectsMessage.o \
			$(DIRPATH)$(BUILD)queryVksObjectsMessage.o \
			$(DIRPATH)$(BUILD)queryVksFeatureClassMetadataMessage.o \
			$(DIRPATH)$(BUILD)queryVksBoundsMessage.o \
			$(DIRPATH)$(BUILD)reportVksObjectsCreationMessage.o \
			$(DIRPATH)$(BUILD)reportVksFeatureClassMetadataMessage.o \
			$(DIRPATH)$(BUILD)reportVksBoundsMessage.o \
			$(DIRPATH)$(BUILD)reportVksObjectsMessage.o \
						

all: $(OBJECTS)

$(DIRPATH)$(BUILD)vectorObject.o : $(SRC)vectorObject.c
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)vectorObject.o $(SRC)vectorObject.c

$(DIRPATH)$(BUILD)createVksObjectsMessage.o : $(SRC)createVksObjectsMessage.c
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)createVksObjectsMessage.o $(SRC)createVksObjectsMessage.c

$(DIRPATH)$(BUILD)deleteVksObjectsMessage.o : $(SRC)deleteVksObjectsMessage.c
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)deleteVksObjectsMessage.o $(SRC)deleteVksObjectsMessage.c

$(DIRPATH)$(BUILD)queryVksObjectsMessage.o : $(SRC)queryVksObjectsMessage.c
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)queryVksObjectsMessage.o $(SRC)queryVksObjectsMessage.c

$(DIRPATH)$(BUILD)queryVksFeatureClassMetadataMessage.o : $(SRC)queryVksFeatureClassMetadataMessage.c
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)queryVksFeatureClassMetadataMessage.o $(SRC)queryVksFeatureClassMetadataMessage.c

$(DIRPATH)$(BUILD)queryVksBoundsMessage.o : $(SRC)queryVksBoundsMessage.c
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)queryVksBoundsMessage.o $(SRC)queryVksBoundsMessage.c

$(DIRPATH)$(BUILD)reportVksObjectsCreationMessage.o : $(SRC)reportVksObjectsCreationMessage.c
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)reportVksObjectsCreationMessage.o $(SRC)reportVksObjectsCreationMessage.c

$(DIRPATH)$(BUILD)reportVksFeatureClassMetadataMessage.o : $(SRC)reportVksFeatureClassMetadataMessage.c
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)reportVksFeatureClassMetadataMessage.o $(SRC)reportVksFeatureClassMetadataMessage.c

$(DIRPATH)$(BUILD)reportVksBoundsMessage.o : $(SRC)reportVksBoundsMessage.c
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)reportVksBoundsMessage.o $(SRC)reportVksBoundsMessage.c

$(DIRPATH)$(BUILD)reportVksObjectsMessage.o : $(SRC)reportVksObjectsMessage.c
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)reportVksObjectsMessage.o $(SRC)reportVksObjectsMessage.c
