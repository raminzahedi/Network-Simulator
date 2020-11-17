#include <iostream>
#include "Graph.h"
#include "GraphIO.h"
#include "GraphRouter.h"

using namespace std;

int main ( int argc, char ** argv ) {
     if ( argc != 3 ) {
          cout << "To run this you need arguments: <seed> <graph_filename>" << endl;
          exit ( 0 );
     } 
     string seedNumber = argv[1];
     string fileName = argv[2];

     srand ( atoi( seedNumber.c_str() ) );

     //GraphRouter ( maxQueueSize for routers , )
     GraphRouter graphRouter ( 30 ); //We just want to reuse the graph so we will create a router based off its information once it's loaded in.
     GraphIO * graphIO = (GraphIO*)&graphRouter; //Use graphRouter Graph by typecasting it into GraphIO so we can use it to load in the file.
         
     
     //if graph file doesn't exist, create a graph file
     ifstream f(fileName.c_str());
     if(!f.good()){
          graphRouter.create ( 150 ); 
          cout << "Created graph" << endl;

          graphRouter.generateEdges ( );
          cout << "Generated edges" << endl;

          graphIO->write ( fileName );
          cout << "Graph is saved to " << fileName << endl;
     }


     if ( !graphIO->read ( fileName ) ) {
          cout << "Unable to read graph from " << fileName << endl;
          exit ( 0 );
     }
     cout << "Graph was read from " << fileName <<endl;
    
     if ( !graphIO->checkConnectivity ( ) ) {
          cout << "Graph wasn't completely connected " << fileName << "." <<endl;
          exit ( 0 );
     }
      cout << "Graph is completely connected." <<endl;

     if ( !graphIO->findShortestPaths ( ) ) {
          cout << "Unable to find shortest paths" << endl;
          exit ( 0 );
     }
     cout << "Shortest Paths found." << endl;


     for ( int i = 0 ; i < 1000 ; i++ ) {// Run for 1000 seconds

          for( int j = 0; j < 20; j++){// Randomly Select 20 source destination pairs

               graphRouter.send ( rand() % 150 , rand() % 150 );
          }
          graphRouter.run ( );
     }

     //Print out all gathered statistics
     cout << "Routing Statistics: " << endl;
     cout << "Total number of packets generated: " << graphRouter.getTotalGeneratedPackets ( ) << endl;
     cout << "Total number of packets that reached destination: " << graphRouter.getTotalSuccessfulPackets ( ) << endl;
     
    
     //Print out completion time and dropped packet statistics.
     cout << "Time for completion for the transmissions: " << endl
          << "Max: " << graphRouter.getMaxTransmissionTime ( ) << " seconds" << endl
          << "Min: " << graphRouter.getMinTransmissionTime ( ) << " seconds" << endl
          << "Avg: " << graphRouter.getAvgTransmissionTime ( ) << " seconds" << endl;

     cout << "Number for packets dropped at a router: " << endl
          << "Max: " << graphRouter.getAvgLostPackets ( ) << endl
          << "Min: " << graphRouter.getMinLostPackets ( ) << endl
          << "Avg: " << graphRouter.getMaxLostPackets ( ) << endl;
     

     graphIO = NULL;

     exit ( 0 );
     return 0;
}
