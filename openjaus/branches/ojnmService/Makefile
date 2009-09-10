TARGET	= 	./bin/ojnmService
CCFLAGS	=	-Wall -fno-strict-aliasing -O2 -c -g -I ./include/ -I ../libjaus/include/ -I ../libopenJaus/include/
LFLAGS	=	-L ../libjaus/lib/ -L ../libopenJaus/lib/
LIBS	=	-lopenJaus -ljaus -lcurses -lpthread

SOURCES = ./src/ojnmService.cpp

OBJECTS = ./Build/ojnmService.o

default : all

all : $(TARGET)
	chmod +x ./ojnmd
	chmod +x $(TARGET)

clean : 
	rm -f ./Build/*.o
	rm -f $(TARGET)

$(TARGET) : $(OBJECTS)
	g++ $(LFLAGS) -o $(TARGET) $(OBJECTS) $(LIBS)

./Build/ojnmService.o : ./src/ojnmService.cpp
	g++ $(CCFLAGS) -o ./Build/ojnmService.o ./src/ojnmService.cpp
