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
