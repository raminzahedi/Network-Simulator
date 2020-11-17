#include "Packet.h"

Packet::Packet ( ) {
	source = -1;
	destination = -1;
	delay = 0;
	timeOffset = 0;
}

Packet::~Packet ( ) {

}
/*
	Set source and destination indexes for packet.
	Kinda acts like a header.
*/
void Packet::setPath ( int s , int d ) {
	source = s;
	destination = d;
}

void Packet::setSize ( int s ) {
	size = s;
}

void Packet::setDelay ( int d ) {
	delay = d;
}

void Packet::setTime ( int t ) {
	timeOffset = t;
}

int Packet::getSource ( ) {
	return source;
}

int Packet::getDestination ( ) {
	return destination;
}

int Packet::getSize ( ) {
	return size;
}

int Packet::getDelay ( ) {
	return delay;
}

int Packet::getTime ( ) {
	return timeOffset;
}

string Packet::toString ( ) {
	stringstream info;
	info << "Source: " << source << endl;
	info << "Destination: " << destination << endl;
	info << "Size: " << size << endl;
	return info.str(); 
}

void Packet::reset ( ) {
	source = -1;
	destination = -1;
	size = -1;
	delay = 0;
}