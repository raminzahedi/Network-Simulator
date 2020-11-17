#include <sstream>

#ifndef PACKET_HEADER
#define PACKET_HEADER
using namespace std;
class Packet {
	public:
		Packet ( );
		~Packet ( );

		void setPath ( int, int );
		void setSize ( int );
		void setDelay ( int );
		void setTime ( int );

		int getSource ( );
		int getDestination ( );
		int getSize ( );
		int getDelay ( );
		int getTime ( );

		string toString ( );

		void reset ( );

	private:
		int source, destination, size, delay, timeOffset;
};

#endif