TARGET	= 	./bin/ojNodeManager
CCFLAGS	=	-Wall -fno-strict-aliasing -O2 -c -g -I ./include/ -I /home/mechatronics/workspace/OpenJAUSv3.3/libjaus/include/ -I /home/mechatronics/workspace/OpenJAUSv3.3/libopenJaus/include/
LFLAGS	=	-L /home/mechatronics/workspace/OpenJAUSv3.3/libjaus/lib/ -L /home/mechatronics/workspace/OpenJAUSv3.3/libopenJaus/lib/
LIBS	=	-lopenJaus -ljaus -lrt -lcurses

SOURCES =	./src/main.cpp

OBJECTS =	./Build/main.o

default : all

all : $(TARGET)

clean :
	rm -f ./Build/*.o
	rm -f $(TARGET)

$(TARGET) : $(OBJECTS)
	g++ $(LFLAGS) -o $(TARGET) $(OBJECTS) $(LIBS)

./Build/main.o : ./src/main.cpp
	g++ $(CCFLAGS) -o ./Build/main.o ./src/main.cpp
