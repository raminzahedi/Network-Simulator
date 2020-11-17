#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <climits>
#ifndef GRAPH_HEADER
#define GRAPH_HEADER

using namespace std;

class Graph {
     public:
          Graph ( );
          ~Graph ( );
     
          int create ( int );
          int generateEdges ( ); //nodes
          void setEdge ( int, int );
          void setEdge ( int, int, int );
          void removeEdge ( int, int );
          int getEdge ( int, int );
          int nextPath ( int, int );
          int clear ( );
          int size ( );
          int edges ( );
          
          int checkConnectivity ( );
          int findShortestPaths ( );
          string toString ( );
     private:
          int ** graphTable, ** minPathTable;
          int graphNodes, graphEdges;

          void checkLocation ( int , int*& );
};

#endif