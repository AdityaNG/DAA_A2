/*
 * Takes graph input from STDIO
 * Runs Dijkstra on the input
 * */

#include <stdlib.h>
#include <limits.h>
#include <stdio.h>

#include "PES1UG19CS032_H.h"

int main(){
    int numVertices;
    
    scanf("%d", &numVertices);
    Graph_t* input_graph = Graph_Init(numVertices);
    
    int source, destination, weight, temp1, temp2;
    
    for(int i = 0; i < numVertices; i++){
        scanf("%d", &source);            
        char c;
        while((c = getchar()) != '\n' && c != '\r'){
            scanf("%d %d", &temp1, &temp2);
            if(temp1 != destination){
                destination = temp1;
                weight = temp2;
                /* 
                Note that the destination and source are reversed
                This is to invert the input_graph
                */
                Graph_Append(input_graph, destination, source, weight);
            }
            else break;
        }        
    }
    
    Dijkstra(*input_graph, numVertices);
    
    Graph_Destroy(input_graph);
    
    return 0;
}
