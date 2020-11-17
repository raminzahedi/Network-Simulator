#include "Graph.h"


Graph::Graph ( ) {
     graphTable = NULL;
     minPathTable = NULL;
     graphNodes = 0;
     graphEdges = 0;
}

Graph::~Graph ( ) {
     clear ( );
}

/*
     Create a graph based on the amount of verteces given.
*/
int Graph::create ( int nodes ) {
     try {
          /*
               We need to clear out any previous created graphTables
          */
          
          clear ( );
          
          /*
               Set graphNodes to nodes and reset graphEdges.
               Allocate memory for new graph table.
          */
          graphNodes = nodes;
          
          graphTable = new int*[graphNodes];
          minPathTable = new int*[graphNodes];
          for ( int i = 0; i < graphNodes; i++ ) {
               graphTable[i] = new int[graphNodes];
               minPathTable[i] = new int[graphNodes];    
               for ( int b = 0; b < graphNodes; b++ ) {
                    graphTable[i][b] = INT_MAX;
                    minPathTable[i][b] = INT_MAX;
               }
          }
          
          return 1;
     } catch ( ... ) {
          return 0;
     }
}

/*
     Will set an edge in the graphTable;
*/
void Graph::setEdge ( int from , int to ) {
     if ( !graphTable[from][to] ) {
          graphEdges++;
     }
     graphTable[from][to] = 1;
     graphTable[to][from] = 1;

}

/*
     Will set an edge with a weight
*/
void Graph::setEdge ( int from, int to, int weight ) {
     if ( !graphTable[from][to] ) {
          graphEdges++;
     }
     graphTable[from][to] = weight;
     graphTable[to][from] = weight;    
}

/*
     Remove an edge between from and to
*/
void Graph::removeEdge ( int from , int to ) {
     if ( graphTable[from][to] ) {
         graphEdges--;
     }
     graphTable[from][to] = 0;
     graphTable[to][from] = 0;
}
/*
     Check if there is an edge between FROM->TO
*/
int Graph::getEdge ( int from , int to ) {
     return graphTable[from][to];
}

/*
     Generate graph of nodes*nodes
     This will create a multi-dimensioanl array of [nodes][nodes] size.   
*/
int Graph::generateEdges ( ) {
     try {
          for ( int i = 0; i < graphNodes; i++ ) {
               for ( int b = i; b < graphNodes; b++ ) {
                    /*
                         Run random to figure out if we set an edge at this location and then flip indexes to set it for both nodes 
                    */
                    if ( i != b ) {
                         if ( rand () % 2 == 1 ) {
                              setEdge ( i , b );
                         } else {
                              removeEdge ( i , b );
                         }
                    }
               }
          }
          return 1;
     } catch ( ... ) {
          return 0;
     }
}

/*
     Clear out graph_table
*/
int Graph::clear ( ) {
     try {
          if ( !graphTable ) {
               return 1;
          }

          for ( int i = 0; i < graphNodes; i++ ) {
               if ( graphTable[i] ) {
                    delete [] graphTable[i];
                    delete [] minPathTable[i];
                    graphTable[i] = NULL;
                    minPathTable[i] = NULL;
               }
          }
          if ( graphTable ) {
               delete graphTable;
               delete minPathTable;
               graphTable = NULL;
               minPathTable = NULL;
          }
          graphNodes = 0;
          graphEdges = 0;
          
          return 1;
     } catch ( ... ) {
          return 0;
     }
}
/*
     Get Graph Edge count
*/
int Graph::edges ( ) {
     return graphEdges;
}
/*
     Get Graph Size
*/
int Graph::size ( ) {
     return graphNodes;
}

/*
     Get Next Path from Source to Destination based on minPathTable
*/

int Graph::nextPath ( int a, int b ) {
     if ( minPathTable[a][b] != INT_MAX ) {
          return b;
     }
     int nextPath = -1;
     int minPath = -1;
     for ( int i = 0; i < size ( ); i ++ ) {
          if ( minPathTable[a][i] != INT_MAX && i != a && minPath < minPathTable[a][i]) {
               minPath = minPathTable[a][i];
               nextPath = i;
          }
     }
     return nextPath;
}

/*
     Run Shortest path algorithm on entire graph
*/
int Graph::findShortestPaths ( ) {
     try {
          int i,j,k,n = size ( );

          for(k = 0;k<n;k++) {
               for(i = 0;i<n;i++) {
                    for(j = 0;j<n;j++) {
                         if(graphTable[i][k]!=INT_MAX && graphTable[k][j] != INT_MAX)
                              
                              if ( minPathTable[i][j] > graphTable[i][k] + graphTable[k][j] ) {
                                   minPathTable[i][j] = graphTable[i][k] + graphTable[k][j];
                              } else {
                                   minPathTable[i][j] = graphTable[i][j];
                              }

                              
                         else
                              minPathTable[i][j] = graphTable[i][j];
                    }
               }
               /*
               //Uncomment this block to see shortestPath algorithm at work
               //Look at the last iteration for the routing table
               cout<<"in the "<<k<<"th iteration, the result is:"<<endl;
               for(i = 0;i<n;i++) {
                    cout << i << " | ";
                    for(j = 0;j<n;j++) {
                         cout<<(minPathTable[i][j]==1?j:0)<<" ";
                    }
                    cout<<endl;
               }
               */
          }
          return 1;
     } catch ( ... ) {
          return 0;
     }
}

/*
     Runs a check on every possible vertex to make sure it can reach everyother vertex.
*/
int Graph::checkConnectivity ( ) {
     try {
          int * graphCheck = new int[graphNodes];
          for ( int i = 0; i < graphNodes; i ++ ) {
               graphCheck[i] = INT_MAX;
          }
          for ( int i = 0; i < graphNodes; i ++ ) {
               checkLocation ( i , graphCheck );
               if ( graphCheck[i] == 0 ) {
                    return 0;
               }
          }
          delete [] graphCheck;
          return 1;
     } catch ( ... ) {
          return 0;
     }
}

/*
     DFS check to make sure we can attain every vertex in the possible graph.
*/
void Graph::checkLocation ( int from , int *&graphCheck ) {
     int edge = INT_MAX;
     graphCheck[from] = 0;

     for ( int v =  0; v < graphNodes; v++ ) {
          if ( v == from ) continue;
          if ( getEdge ( from , v ) == 1 && graphCheck[v] == INT_MAX ) {
               edge = 1;
               checkLocation ( v , graphCheck );
          } else
          if ( graphCheck[v] ==  1 ) {
               edge = 1;
          }
     }
     graphCheck[from] = edge;
}

/*
     Print out of all of the edges in the graph.
     Looks like the graph print out that GraphIO can provide.
*/
string Graph::toString ( ) {
     stringstream outputParser;
     for ( int i = 0; i < graphNodes; i++ ) {
          for ( int b = i; b < graphNodes; b++ ) {
               if ( b != i && getEdge ( i , b ) >= 0 ) {
                    outputParser << i << " " << b << " -> " << getEdge ( i , b ) << endl;
               }
          }
     }
     return outputParser.str();
}