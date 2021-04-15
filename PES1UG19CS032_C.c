/*
 * Takes graph input from STDIO
 * Runs Dijkstra on the input
 * */

#include <stdlib.h>
#include <limits.h>
#include <stdio.h>

#include "PES1UG19CS032_H.h"

int main() {
    int numVertices;
    
    scanf("%d", &numVertices);
    Graph_t* input_graph = Graph_Init(numVertices);
    
    int source, destination, weight; 
    
    for(int i = 0; i < numVertices; i++) {

        scanf("%d", &source);
        char c;
        while((c = getchar()) != '\n' && c != '\r' && c != EOF) {
            
            scanf("%d %d", &destination, &weight);
            
            /* 
             * Note that the destination and source are reversed
             * This is to invert the input_graph
             */
            Graph_Append(input_graph, destination, source, weight);
        }        
    }
    
    Dijkstra(*input_graph, numVertices);
    
    Graph_Destroy(input_graph);
    
    return 0;
}
