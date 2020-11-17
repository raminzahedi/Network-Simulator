CC=g++
CFLAGS=-c
 
all: netsim

netsim: main.o Graph.o GraphIO.o GraphRouter.o Router.o Packet.o PacketQueue.o
	$(CC) -g main.o Graph.o GraphIO.o GraphRouter.o Router.o Packet.o PacketQueue.o -o netsim

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

Graph.o: Graph.h Graph.cpp
	$(CC) $(CFLAGS) Graph.h Graph.cpp

GraphIO.o: GraphIO.h GraphIO.cpp
	$(CC) $(CFLAGS) GraphIO.h GraphIO.cpp

GraphRouter.o: GraphRouter.h GraphRouter.cpp
	$(CC) $(CFLAGS) GraphRouter.h GraphRouter.cpp

Router.o: Router.h Router.cpp
	$(CC) $(CFLAGS) Router.h Router.cpp

Packet.o: Packet.h Packet.cpp
	$(CC) $(CFLAGS) Packet.h Packet.cpp

PacketQueue.o: PacketQueue.h PacketQueue.cpp
	$(CC) $(CFLAGS) PacketQueue.h PacketQueue.cpp

clean: 
	rm *.gch *.o netsim* 
