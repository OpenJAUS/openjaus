TARGET	= 	./bin/ojVehicleSim
CCFLAGS	=	-Wall -fno-strict-aliasing -O2 -c -g -I ./include/ -I ../libjaus/include/ -I ../libopenJaus/include/
LFLAGS	=	-L ../libjaus/lib/ -L ../libopenJaus/lib/
LIBS		=	-lopenJaus -ljaus -lrt -lcurses
SOURCES =	./src/utm/pointUtm.c \
		./src/utm/pointLla.c \
		./src/utm/utminv.c \
		./src/utm/greatCircle.c \
		./src/utm/utmLib.c \
		./src/utm/utmfor.c \
		./src/utm/cproj.c \
		./src/simulator.c \
		./src/vehicle.c \
		./src/pd.c \
		./src/main.c \
		./src/getLine.c \
		./src/gpos.c \
		./src/vehicleSim.c \
		./src/wd.c \
		./src/vss.c \
		./src/properties.c

OBJECTS =	./Build/pointUtm.o \
		./Build/pointLla.o \
		./Build/utminv.o \
		./Build/greatCircle.o \
		./Build/utmLib.o \
		./Build/utmfor.o \
		./Build/cproj.o \
		./Build/simulator.o \
		./Build/vehicle.o \
		./Build/pd.o \
		./Build/main.o \
		./Build/getLine.o \
		./Build/gpos.o \
		./Build/vehicleSim.o \
		./Build/wd.o \
		./Build/vss.o \
		./Build/properties.o

default : all

all : $(TARGET)

clean :
	rm -f ./Build/*.o
	rm -f $(TARGET)

$(TARGET) : $(OBJECTS)
	g++ $(LFLAGS) -o $(TARGET) $(OBJECTS) $(LIBS)

./Build/pointUtm.o : ./src/utm/pointUtm.c
	gcc $(CCFLAGS) -o ./Build/pointUtm.o ./src/utm/pointUtm.c

./Build/pointLla.o : ./src/utm/pointLla.c
	gcc $(CCFLAGS) -o ./Build/pointLla.o ./src/utm/pointLla.c

./Build/utminv.o : ./src/utm/utminv.c
	gcc $(CCFLAGS) -o ./Build/utminv.o ./src/utm/utminv.c

./Build/greatCircle.o : ./src/utm/greatCircle.c
	gcc $(CCFLAGS) -o ./Build/greatCircle.o ./src/utm/greatCircle.c

./Build/utmLib.o : ./src/utm/utmLib.c
	gcc $(CCFLAGS) -o ./Build/utmLib.o ./src/utm/utmLib.c

./Build/utmfor.o : ./src/utm/utmfor.c
	gcc $(CCFLAGS) -o ./Build/utmfor.o ./src/utm/utmfor.c

./Build/cproj.o : ./src/utm/cproj.c
	gcc $(CCFLAGS) -o ./Build/cproj.o ./src/utm/cproj.c

./Build/simulator.o : ./src/simulator.c
	gcc $(CCFLAGS) -o ./Build/simulator.o ./src/simulator.c

./Build/vehicle.o : ./src/vehicle.c
	gcc $(CCFLAGS) -o ./Build/vehicle.o ./src/vehicle.c

./Build/pd.o : ./src/pd.c
	gcc $(CCFLAGS) -o ./Build/pd.o ./src/pd.c

./Build/main.o : ./src/main.c
	gcc $(CCFLAGS) -o ./Build/main.o ./src/main.c

./Build/getLine.o : ./src/getLine.c
	gcc $(CCFLAGS) -o ./Build/getLine.o ./src/getLine.c

./Build/gpos.o : ./src/gpos.c
	gcc $(CCFLAGS) -o ./Build/gpos.o ./src/gpos.c

./Build/vehicleSim.o : ./src/vehicleSim.c
	gcc $(CCFLAGS) -o ./Build/vehicleSim.o ./src/vehicleSim.c

./Build/wd.o : ./src/wd.c
	gcc $(CCFLAGS) -o ./Build/wd.o ./src/wd.c

./Build/vss.o : ./src/vss.c
	gcc $(CCFLAGS) -o ./Build/vss.o ./src/vss.c

./Build/properties.o : ./src/properties.c
	gcc $(CCFLAGS) -o ./Build/properties.o ./src/properties.c
