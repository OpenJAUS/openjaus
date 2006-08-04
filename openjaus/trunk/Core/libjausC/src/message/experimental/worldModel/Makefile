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
