#include "Router.h"

Router::Router ( ) {
	bandwidth = 0;
	maxQueueSize = 0;

	//Keep track of all packet switching and packets lost because queue was too big.
	totalTransmitted = 0;
	totalLost = 0;
}

Router::~Router ( ) {

}

/*
	Set max queue size for the routers incoming and outgoing queues.
*/
void Router::setQueueSize ( int size ) {
	maxQueueSize = size;
}

/*
	Get max queue size for the routers incoming and outgoing queues.
*/
int Router::getQueueSize ( ) {
	return maxQueueSize;
}

/*
	Add Packet to incoming packets
*/
void Router::enqueueIncoming ( Packet p ) {
	if ( sizeIn ( ) < maxQueueSize ) {
		incoming.push ( p );
	} else {
		totalLost ++;
	}
}

/*
	Add Packet to outgoing packets
*/
void Router::enqueueOutgoing ( Packet p ) {
	if ( sizeOut ( ) < maxQueueSize ) {
		outgoing.push ( p );
	} else {
		totalLost ++;
	}
}

/*
	Add Packet to wire queue
	The wire queue holds packets that are suppose be in STATE = transmission.
	This give us the simulation that the packet hasn't arrived to the next router yet.
	##This queue has no limit of size.
*/
void Router::enqueueWire ( Packet p ) {
	wire.push ( p );
}

/*
	Remove packet from incoming packets
*/
Packet Router::dequeueIncoming ( ) {
	Packet p;
	if ( sizeIn() > 0 ) {
		incoming.pop ( p );
	}
	return p;
}

/*
	Remove packet from Output Queue and return it.
*/
Packet Router::dequeueOutgoing ( ) {
	Packet p;
	outgoing.pop ( p );
	totalTransmitted ++;
	return p;
}

/*
	Search wire queue to see if any packets have simulated wait time and return those as a list
*/
void Router::dequeueWire( PacketQueue &list ) {
	/*
		Do calculation to fill this list with packets that have finished delay.
	*/
	Packet p;
	PacketQueue tmpList;	
	while ( wire.size ( ) > 0 ) {
		p.reset ( );
		wire.pop ( p );
		if ( ( p.getDelay ( ) - 1 ) == 0 ) {
			p.setDelay ( 0 );
			list.push ( p );
		} else {
			p.setDelay ( p.getDelay ( ) );
			tmpList.push ( p );
		}
	}

	while ( tmpList.size ( ) > 0 ) {
		p.reset ( );
		tmpList.pop ( p );
		wire.push ( p );
	}
}

/*
	Return size of outbound packets.
*/
int Router::sizeOut ( ) {
	return outgoing.size ( );
}

/*
	Return size of inbound packets.
*/

int Router::sizeIn ( ) {
	return incoming.size ( );
}

void Router::setBandwidth ( int b ) {
	bandwidth = b;
}

int Router::getBandwidth ( ) {
	return bandwidth;
}

float Router::getAvgLost ( ) {
	return totalLost/totalTransmitted;
}

int Router::getPacketsLost ( ) {
	return totalLost;
}