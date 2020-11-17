#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include "Graph.h"

#ifndef GRAPH_IO_HEADER
#define GRAPH_IO_HEADER
using namespace std;

class GraphIO : public Graph {
     public:
          GraphIO ( );
          ~GraphIO ( );
          
          int read ( string );
          int write ( string );

     private:
          long getNumber ( ifstream& );
};

#endif
