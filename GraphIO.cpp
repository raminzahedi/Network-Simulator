#include "GraphIO.h"
using namespace std;

GraphIO::GraphIO ( ) {

}

GraphIO::~GraphIO ( ) {

}

/*
     Read in ascii version of a graph.
*/
int GraphIO::read ( string filename ) {
     try {

          ifstream graphFile ( filename.c_str() );
          
          if(graphFile.is_open()){
               int i = 0, b = 0, nodes, edges;
               nodes = getNumber ( graphFile );
               edges = getNumber ( graphFile ); //Grab edge amount
               
               create ( nodes ); //create graphTable based on node amount
               
               //run through and add edges to graphTable
               while( !graphFile.eof ( ) ){
                    if ( (i = getNumber(graphFile)) == -1 ) {
                         break;
                    }
                    if ( !(b = getNumber(graphFile)) == -1 ) {
                         break;
                    }
                    setEdge ( i , b );
               }
               
               graphFile.close();
               return 1;
          } else {
               cout<<"File could not be found.\n";
          }
          return 1;
     } catch ( ... ) {
          return 0;
     }
}

/*
     Print out ascii version of graph
*/
int GraphIO::write ( string filename ) {
     try {
          
          ofstream graphFile ( filename.c_str() );
          
          if(graphFile.is_open()){
               graphFile << size ( ) << " " << edges ( ) << endl; 
               /*
                    Loop through graph and set each link possible
               */
               for ( int i = 0; i < size ( ); i++ ) {
                    for ( int b = i; b < size ( ); b++ ) {
                         if ( getEdge ( i , b ) == 1) {
                              graphFile << i << " " << b << endl;
                         }
                    }
               }
               graphFile.close ();
          }
          return 1;
     } catch ( ... ) {
          return 0;
     }
}

long GraphIO::getNumber ( ifstream &file ) {
       string number = "";
       char c = file.get();
       if ( !file.good() ) {
          return -1;
       }
       while ( c != ' ' && c != '\n' && c!='\r' ) {
          number += c;
          c = file.get();
       }

       return atoi ( number.c_str () );
}
