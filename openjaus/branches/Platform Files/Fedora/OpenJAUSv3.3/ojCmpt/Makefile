TARGET	= 	./bin/ojCmpt
CCFLAGS	=	-Wall -fno-strict-aliasing -O2 -c -g -I ./include/ -I ../libjaus/include/ -I ../libopenJaus/include/
LFLAGS	=	-L ../libjaus/lib/ -L ../libopenJaus/lib/
LIBS		=	-lopenJaus -ljaus -lrt -lcurses
SOURCES =	./src/properties.c \
		./src/cmpt.c \
		./src/main.c

OBJECTS =	./Build/properties.o \
		./Build/cmpt.o \
		./Build/main.o

default : all

all : $(TARGET)

clean :
	rm -f ./Build/*.o
	rm -f $(TARGET)

$(TARGET) : $(OBJECTS)
	g++ $(LFLAGS) -o $(TARGET) $(OBJECTS) $(LIBS)

./Build/properties.o : ./src/properties.c
	gcc $(CCFLAGS) -o ./Build/properties.o ./src/properties.c

./Build/cmpt.o : ./src/cmpt.c
	gcc $(CCFLAGS) -o ./Build/cmpt.o ./src/cmpt.c

./Build/main.o : ./src/main.c
	gcc $(CCFLAGS) -o ./Build/main.o ./src/main.c
