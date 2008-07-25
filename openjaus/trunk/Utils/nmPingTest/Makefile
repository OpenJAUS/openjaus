TARGET	= 	./bin/ojCmptTest
CCFLAGS	=	-Wall -fno-strict-aliasing -O2 -c -g -I ./include/ -I ../OpenJAUSv3.3/libjaus/include/ -I ../OpenJAUSv3.3/libopenJaus/include/
LFLAGS	=	-L ../OpenJAUSv3.3/libjaus/lib/ -L ../OpenJAUSv3.3/libopenJaus/lib/
LIBS	=	-lopenJaus -ljaus -lcurses -lpthread

SOURCES =	./main.c

OBJECTS =	./Build/main.o

default : all

all : $(TARGET)

clean :
	rm -f ./Build/*.o
	rm -f $(TARGET)

$(TARGET) : $(OBJECTS)
	g++ $(LFLAGS) -o $(TARGET) $(OBJECTS) $(LIBS)

./Build/main.o : ./main.c
	g++ $(CCFLAGS) -o ./Build/main.o ./main.c
