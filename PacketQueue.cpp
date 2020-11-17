#include "PacketQueue.h"

PacketQueue::PacketQueue ( ) {
	HEAD = NULL;
	TAIL = NULL;
	currentSize = 0;
}

PacketQueue::~PacketQueue ( ) {
	//Packet p;
	//hile ( pop ( p ) ) { /* ITERATE AND DELETE */ }
}

void PacketQueue::push ( Packet p ) {
	try {
		PacketItem * ptr = new PacketItem ( );
		ptr->item = p;
		if ( currentSize == 0 ) {
			HEAD=TAIL=ptr;
		}else {
			TAIL->next = ptr;
			TAIL = ptr;
		}
		ptr = NULL;
		incrementSize ( );
	} catch ( exception & e ) {
		cout << e.what ( ) << endl;
	}
}

void PacketQueue::pop ( Packet &p ) {
	try {
		p.reset ( );
		if ( currentSize == 0 ) return;
		PacketItem * ptr = HEAD;
		p = HEAD->item;
		HEAD = HEAD->next;
		delete ptr;
		decrementSize ( );
	} catch ( exception & e ) {
		cout << e.what ( ) << endl;
	}
}

void PacketQueue::incrementSize ( ) {
	currentSize ++;
}

void PacketQueue::decrementSize ( ) {
	currentSize --;
}

int PacketQueue::size ( ) {
	return currentSize;
}