# ./src/message/experimental

INC		=	include
SRC		=	
BUILD	=	Build/
CC		=	gcc
CCFLAGS	=	-Wall -O2 -fPIC -g -c 

OBJECTS =	\
			$(DIRPATH)$(BUILD)queryIdentificationMessage.o \
			$(DIRPATH)$(BUILD)reportIdentificationMessage.o \
			$(DIRPATH)$(BUILD)queryConfigurationMessage.o \
			$(DIRPATH)$(BUILD)reportConfigurationMessage.o \
			$(DIRPATH)$(BUILD)configurationChangedEventSetupMessage.o \
			$(DIRPATH)$(BUILD)configurationChangedEventNotificationMessage.o \
			$(DIRPATH)$(BUILD)queryServicesMessage.o \
			$(DIRPATH)$(BUILD)reportServicesMessage.o \
			$(DIRPATH)$(BUILD)queryPayloadDataElementMessage.o \
			$(DIRPATH)$(BUILD)queryPayloadInterfaceMessage.o \
			$(DIRPATH)$(BUILD)reportPayloadDataElementMessage.o \
			$(DIRPATH)$(BUILD)reportPayloadInterfaceMessage.o \
			$(DIRPATH)$(BUILD)setPayloadDataElementMessage.o \


all: $(OBJECTS)
	@cd ./events; make "DIRPATH=../$(DIRPATH)" "BUILD=$(BUILD)" "BINDIR=$(BINDIR)" "INC=$(INC)";
	@cd ./worldModel; make "DIRPATH=../$(DIRPATH)" "BUILD=$(BUILD)" "BINDIR=$(BINDIR)" "INC=$(INC)";
	
$(DIRPATH)$(BUILD)queryIdentificationMessage.o : $(SRC)queryIdentificationMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)queryIdentificationMessage.o ./queryIdentificationMessage.c	

$(DIRPATH)$(BUILD)reportIdentificationMessage.o : $(SRC)reportIdentificationMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)reportIdentificationMessage.o ./reportIdentificationMessage.c	

$(DIRPATH)$(BUILD)queryConfigurationMessage.o : $(SRC)queryConfigurationMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)queryConfigurationMessage.o ./queryConfigurationMessage.c	

$(DIRPATH)$(BUILD)reportConfigurationMessage.o : $(SRC)reportConfigurationMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)reportConfigurationMessage.o ./reportConfigurationMessage.c	

$(DIRPATH)$(BUILD)configurationChangedEventSetupMessage.o : $(SRC)configurationChangedEventSetupMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)configurationChangedEventSetupMessage.o ./configurationChangedEventSetupMessage.c	

$(DIRPATH)$(BUILD)configurationChangedEventNotificationMessage.o : $(SRC)configurationChangedEventNotificationMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)configurationChangedEventNotificationMessage.o ./configurationChangedEventNotificationMessage.c	

$(DIRPATH)$(BUILD)queryServicesMessage.o : $(SRC)queryServicesMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)queryServicesMessage.o ./queryServicesMessage.c	

$(DIRPATH)$(BUILD)reportServicesMessage.o : $(SRC)reportServicesMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)reportServicesMessage.o ./reportServicesMessage.c	

$(DIRPATH)$(BUILD)queryPayloadDataElementMessage.o : $(SRC)queryPayloadDataElementMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)queryPayloadDataElementMessage.o ./queryPayloadDataElementMessage.c	

$(DIRPATH)$(BUILD)queryPayloadInterfaceMessage.o : $(SRC)queryPayloadInterfaceMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)queryPayloadInterfaceMessage.o ./queryPayloadInterfaceMessage.c	

$(DIRPATH)$(BUILD)reportPayloadDataElementMessage.o : $(SRC)reportPayloadDataElementMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)reportPayloadDataElementMessage.o ./reportPayloadDataElementMessage.c	

$(DIRPATH)$(BUILD)reportPayloadInterfaceMessage.o : $(SRC)reportPayloadInterfaceMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)reportPayloadInterfaceMessage.o ./reportPayloadInterfaceMessage.c	

$(DIRPATH)$(BUILD)setPayloadDataElementMessage.o : $(SRC)setPayloadDataElementMessage.c 
	$(CC) $(CCFLAGS) -I $(DIRPATH)$(INC) -o $(DIRPATH)$(BUILD)setPayloadDataElementMessage.o ./setPayloadDataElementMessage.c	
