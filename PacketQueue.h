#include <exception>
#include <iostream>
#include "Packet.h"

#ifndef PAKCET_QUEUE_HEADER
#define PACKET_QUEUE_HEADER
using namespace std;
class PacketItem {
	public:
		Packet item;
		PacketItem * next;
		PacketItem * prev;
};

class PacketQueue { 
	public:
		PacketQueue ( );
		~PacketQueue ( );

		void push ( Packet );
		void pop ( Packet& );

		void incrementSize ( );
		void decrementSize ( );
	 	int size  ( );

	private:
		PacketItem * HEAD;
		PacketItem * TAIL;
		int currentSize;
};

#endif