TARGET	= 	./messageTest
CCFLAGS	=	-Wall -fPIC -fno-strict-aliasing -O2 -c -g -I ./include/ -I ../OpenJAUSv3.3/libjaus/include/
LFLAGS	=	-L ../OpenJAUSv3.3/libjaus/lib/
LIBS		=	-ljaus -lrt
SOURCES =	./messageTest.c

OBJECTS =	./Build/messageTest.o

default : all

all : $(TARGET)

clean :
	rm -f ./Build/*.o
	rm -f $(TARGET)

$(TARGET) : $(OBJECTS)
	gcc $(LFLAGS) -o $(TARGET) $(OBJECTS) $(LIBS)

./Build/messageTest.o : ./messageTest.c
	gcc $(CCFLAGS) -o ./Build/messageTest.o ./messageTest.c

./messageTest.c : ./testGen
	./testGen

./testGen : ./testGen.c	
	gcc -o ./testGen ./testGen.c
