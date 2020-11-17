#include <iostream>
#include "Graph.h"
#include "Router.h"
#include "Packet.h"

#ifndef GRAPH_ROUTER_HEADER
#define GRAPH_ROUTER_HEADER
using namespace std;
class GraphRouter : public Graph {
	public:
		GraphRouter ( int );
		~GraphRouter ( );
		
		void send ( int , int );

		int getTotalGeneratedPackets ( );
		int getTotalSuccessfulPackets ( );

		int getMaxLostPackets ( );
		int getMinLostPackets ( );
		int getAvgLostPackets ( );

		float getAvgTransmissionTime ( );
		float getMaxTransmissionTime ( );
		float getMinTransmissionTime ( );

		float getAveragePacketTransmission ( );

		void run ( ); //Run each queue waiting in each NetworkNode
	private:
		int maxQueueSize;
		int totalGeneratedPackets;
		int totalSuccessfulPackets;
		int totalTransmissionTime, totalTime, maxTransmission, minTransmission;
		Router * routers; //Holds all nodes and their queue's that transmit data.

		void createRouters ( );
		void clearRouters ( );
};


#endif