TARGET	= 	./bin/ojCmpt
CCFLAGS	=	-Wall -fno-strict-aliasing -O2 -c -g -I ./include/ -I ../libjaus/include/ -I ../libopenJaus/include/
LFLAGS	=	-L ../libjaus/lib/ -L ../libopenJaus/lib/
LIBS		=	-lopenJaus -ljaus -lcurses -lpthread
SOURCES =	./src/main.c \
		./src/cmpt.c \
		./src/properties.c \
		./src/getLine.c

OBJECTS =	./Build/main.o \
		./Build/cmpt.o \
		./Build/properties.o \
		./Build/getLine.o

default : all

all : $(TARGET)

clean :
	rm -f ./Build/*.o
	rm -f $(TARGET)

$(TARGET) : $(OBJECTS)
	g++ $(LFLAGS) -o $(TARGET) $(OBJECTS) $(LIBS)

./Build/main.o : ./src/main.c
	gcc $(CCFLAGS) -o ./Build/main.o ./src/main.c

./Build/cmpt.o : ./src/cmpt.c
	gcc $(CCFLAGS) -o ./Build/cmpt.o ./src/cmpt.c

./Build/properties.o : ./src/properties.c
	gcc $(CCFLAGS) -o ./Build/properties.o ./src/properties.c

./Build/getLine.o : ./src/getLine.c
	gcc $(CCFLAGS) -o ./Build/getLine.o ./src/getLine.c
