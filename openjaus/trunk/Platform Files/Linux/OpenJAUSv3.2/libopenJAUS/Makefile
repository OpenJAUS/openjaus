EXE		= 	./bin/nodeManager
TARGET	= 	./lib/libopenJAUS.so
CCFLAGS	=	-Wall -fno-strict-aliasing -O2 -c -g -I ./include/ -I /home/mechatronics/OpenJAUSv3.2/libjaus/include/
LFLAGS	=	-L /home/mechatronics/OpenJAUSv3.2/libjaus/lib/
LIBS		=	-ljaus -lrt
SOURCES =	./src/utils/multicastSocket.c \
		./src/utils/queue.c \
		./src/utils/inetAddress.c \
		./src/utils/timeLib.c \
		./src/utils/datagramPacket.c \
		./src/utils/datagramSocket.c \
		./src/nodeManagerInterface/scManager.c \
		./src/nodeManagerInterface/nodeManagerInterface.c \
		./src/nodeManagerInterface/lmHandler.c \
		./src/nodeManagerInterface/defaultJausMessageProcessor.c \
		./src/utils/FileLoader.cpp \
		./src/events/NodeManagerEvent.cpp \
		./src/events/SystemTreeEvent.cpp \
		./src/events/ErrorEvent.cpp \
		./src/JausTransportInterface.cpp \
		./src/JausSubsystemCommunicationManager.cpp \
		./src/NodeManagerComponent.cpp \
		./src/SystemTree.cpp \
		./src/OjApiComponentInterface.cpp \
		./src/JausComponentCommunicationManager.cpp \
		./src/LocalComponent.cpp \
		./src/NodeManager.cpp \
		./src/JausCommunicationManager.cpp \
		./src/CommunicatorComponent.cpp \
		./src/JausTransportQueue.cpp \
		./src/main.cpp \
		./src/OjUdpComponentInterface.cpp \
		./src/MessageRouter.cpp \
		./src/JausNodeCommunicationManager.cpp \
		./src/JausUdpInterface.cpp

OBJECTS =	./Build/multicastSocket.o \
		./Build/queue.o \
		./Build/inetAddress.o \
		./Build/timeLib.o \
		./Build/datagramPacket.o \
		./Build/datagramSocket.o \
		./Build/scManager.o \
		./Build/nodeManagerInterface.o \
		./Build/lmHandler.o \
		./Build/defaultJausMessageProcessor.o \
		./Build/FileLoader.o \
		./Build/NodeManagerEvent.o \
		./Build/SystemTreeEvent.o \
		./Build/ErrorEvent.o \
		./Build/JausTransportInterface.o \
		./Build/JausSubsystemCommunicationManager.o \
		./Build/NodeManagerComponent.o \
		./Build/SystemTree.o \
		./Build/OjApiComponentInterface.o \
		./Build/JausComponentCommunicationManager.o \
		./Build/LocalComponent.o \
		./Build/NodeManager.o \
		./Build/JausCommunicationManager.o \
		./Build/CommunicatorComponent.o \
		./Build/JausTransportQueue.o \
		./Build/OjUdpComponentInterface.o \
		./Build/MessageRouter.o \
		./Build/JausNodeCommunicationManager.o \
		./Build/JausUdpInterface.o

default : all

all : $(EXE)

clean :
	rm -f ./Build/*.o
	rm -f $(TARGET)
	rm -f $(EXE)

$(TARGET) : $(OBJECTS)
	g++ -shared $(LFLAGS) -o $(TARGET) $(OBJECTS) $(LIBS)

$(EXE) : $(TARGET) ./Build/main.o
	g++ $(LFLAGS) -o $(EXE) ./Build/main.o $(LIBS) $(TARGET)

./Build/multicastSocket.o : ./src/utils/multicastSocket.c
	gcc $(CCFLAGS) -o ./Build/multicastSocket.o ./src/utils/multicastSocket.c

./Build/queue.o : ./src/utils/queue.c
	gcc $(CCFLAGS) -o ./Build/queue.o ./src/utils/queue.c

./Build/inetAddress.o : ./src/utils/inetAddress.c
	gcc $(CCFLAGS) -o ./Build/inetAddress.o ./src/utils/inetAddress.c

./Build/timeLib.o : ./src/utils/timeLib.c
	gcc $(CCFLAGS) -o ./Build/timeLib.o ./src/utils/timeLib.c

./Build/datagramPacket.o : ./src/utils/datagramPacket.c
	gcc $(CCFLAGS) -o ./Build/datagramPacket.o ./src/utils/datagramPacket.c

./Build/datagramSocket.o : ./src/utils/datagramSocket.c
	gcc $(CCFLAGS) -o ./Build/datagramSocket.o ./src/utils/datagramSocket.c

./Build/scManager.o : ./src/nodeManagerInterface/scManager.c
	gcc $(CCFLAGS) -o ./Build/scManager.o ./src/nodeManagerInterface/scManager.c

./Build/nodeManagerInterface.o : ./src/nodeManagerInterface/nodeManagerInterface.c
	gcc $(CCFLAGS) -o ./Build/nodeManagerInterface.o ./src/nodeManagerInterface/nodeManagerInterface.c

./Build/lmHandler.o : ./src/nodeManagerInterface/lmHandler.c
	gcc $(CCFLAGS) -o ./Build/lmHandler.o ./src/nodeManagerInterface/lmHandler.c

./Build/defaultJausMessageProcessor.o : ./src/nodeManagerInterface/defaultJausMessageProcessor.c
	gcc $(CCFLAGS) -o ./Build/defaultJausMessageProcessor.o ./src/nodeManagerInterface/defaultJausMessageProcessor.c

./Build/FileLoader.o : ./src/utils/FileLoader.cpp
	g++ $(CCFLAGS) -o ./Build/FileLoader.o ./src/utils/FileLoader.cpp

./Build/NodeManagerEvent.o : ./src/events/NodeManagerEvent.cpp
	g++ $(CCFLAGS) -o ./Build/NodeManagerEvent.o ./src/events/NodeManagerEvent.cpp

./Build/SystemTreeEvent.o : ./src/events/SystemTreeEvent.cpp
	g++ $(CCFLAGS) -o ./Build/SystemTreeEvent.o ./src/events/SystemTreeEvent.cpp

./Build/ErrorEvent.o : ./src/events/ErrorEvent.cpp
	g++ $(CCFLAGS) -o ./Build/ErrorEvent.o ./src/events/ErrorEvent.cpp

./Build/JausTransportInterface.o : ./src/JausTransportInterface.cpp
	g++ $(CCFLAGS) -o ./Build/JausTransportInterface.o ./src/JausTransportInterface.cpp

./Build/JausSubsystemCommunicationManager.o : ./src/JausSubsystemCommunicationManager.cpp
	g++ $(CCFLAGS) -o ./Build/JausSubsystemCommunicationManager.o ./src/JausSubsystemCommunicationManager.cpp

./Build/NodeManagerComponent.o : ./src/NodeManagerComponent.cpp
	g++ $(CCFLAGS) -o ./Build/NodeManagerComponent.o ./src/NodeManagerComponent.cpp

./Build/SystemTree.o : ./src/SystemTree.cpp
	g++ $(CCFLAGS) -o ./Build/SystemTree.o ./src/SystemTree.cpp

./Build/OjApiComponentInterface.o : ./src/OjApiComponentInterface.cpp
	g++ $(CCFLAGS) -o ./Build/OjApiComponentInterface.o ./src/OjApiComponentInterface.cpp

./Build/JausComponentCommunicationManager.o : ./src/JausComponentCommunicationManager.cpp
	g++ $(CCFLAGS) -o ./Build/JausComponentCommunicationManager.o ./src/JausComponentCommunicationManager.cpp

./Build/LocalComponent.o : ./src/LocalComponent.cpp
	g++ $(CCFLAGS) -o ./Build/LocalComponent.o ./src/LocalComponent.cpp

./Build/NodeManager.o : ./src/NodeManager.cpp
	g++ $(CCFLAGS) -o ./Build/NodeManager.o ./src/NodeManager.cpp

./Build/JausCommunicationManager.o : ./src/JausCommunicationManager.cpp
	g++ $(CCFLAGS) -o ./Build/JausCommunicationManager.o ./src/JausCommunicationManager.cpp

./Build/CommunicatorComponent.o : ./src/CommunicatorComponent.cpp
	g++ $(CCFLAGS) -o ./Build/CommunicatorComponent.o ./src/CommunicatorComponent.cpp

./Build/JausTransportQueue.o : ./src/JausTransportQueue.cpp
	g++ $(CCFLAGS) -o ./Build/JausTransportQueue.o ./src/JausTransportQueue.cpp

./Build/main.o : ./src/main.cpp
	g++ $(CCFLAGS) -o ./Build/main.o ./src/main.cpp

./Build/OjUdpComponentInterface.o : ./src/OjUdpComponentInterface.cpp
	g++ $(CCFLAGS) -o ./Build/OjUdpComponentInterface.o ./src/OjUdpComponentInterface.cpp

./Build/MessageRouter.o : ./src/MessageRouter.cpp
	g++ $(CCFLAGS) -o ./Build/MessageRouter.o ./src/MessageRouter.cpp

./Build/JausNodeCommunicationManager.o : ./src/JausNodeCommunicationManager.cpp
	g++ $(CCFLAGS) -o ./Build/JausNodeCommunicationManager.o ./src/JausNodeCommunicationManager.cpp

./Build/JausUdpInterface.o : ./src/JausUdpInterface.cpp
	g++ $(CCFLAGS) -o ./Build/JausUdpInterface.o ./src/JausUdpInterface.cpp
