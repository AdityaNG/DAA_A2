/*
 * Helper Function Definitions
 * */
#include "PES1UG19CS032_H.h"
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>

/*
 * Initialises adjacency list with n nodes 
 * */
Graph_t* Graph_Init(int n){
    Graph_t*graph = (Graph_t*)malloc(sizeof(Graph_t));
    graph->list = (AdjacencyList*)malloc(sizeof(AdjacencyList) * n);
    
    graph->numVertices = n;

    for(int i = 0; i < n; i++)
        graph->list[i].head = NULL;
    
    return graph;
}

/*
 * Appends a directional connection with a particular
 * DOES NOT HEAPIFY
 * */
void Graph_Append(Graph_t* g, int source, int destination, int weight){
    Vertex *new = (Vertex*)malloc(sizeof(Vertex));
    new->weight = weight;
    new->id = destination - 1;
    new->next = g->list[source - 1].head;
    g->list[source - 1].head = new;
}

/*
 * Frees all memory associated with the graph
 * Including the adj list
 * */
void Graph_Destroy(Graph_t* g){
    if(g){
        for(int i = 0; i < g->numVertices; i++){ // Freeing the edges of the graph
            Vertex *del;
            while((del = g->list[i].head) != NULL){
                g->list[i].head = del->next;
                free(del);
            }
        }
        free(g->list); // Freeing the adjacency list array (all the vertices of the graph)
        free(g); // Freeing the graph itself
    }
    return; 
}

Graph_t* Graph_Invert(Graph_t* g){ // Broken
    Graph_t*inverted = Graph_Init(g->numVertices);
    for(int i = 0; i < g->numVertices; i++){
        Vertex *temp = g->list[i].head;
        while(temp){
            Graph_Append(inverted, temp->id, i, temp->weight);
            temp = temp->next;
        }
    }
    
    inverted->numVertices = g->numVertices;
    return inverted;
}

/*
 * Initialises heap with n slots
 * Including the position array
 * */
MinHeap_t* Heap_Init(int n){
    MinHeap_t* h = (MinHeap_t*)malloc(sizeof(MinHeap_t));
    h->heap = (Heap_Node*)malloc(sizeof(Heap_Node) * n);
    h->positionArray = (int*)malloc(sizeof(int) * n);
    h->currentSize = 0;
    h->capacity = n;
    return h;
}

/*
 * Frees heap
 * Including the position array
 * */
void Heap_Destroy(MinHeap_t* h){
    free(h->positionArray);
    free(h->heap);
    free(h);
}

/*
 * Frees heap
 * Including the position array
 * */
void Heap_Insert(MinHeap_t* h, int id, int distance, int predecessor){
    if(h->currentSize == h->capacity) return; // Overflow
    h->heap[h->currentSize].id = id;
    h->heap[h->currentSize].distance = distance;
    h->heap[h->currentSize].predecessor = predecessor;
    h->currentSize++; 

    // Readjust bottom up
    int childPos = h->currentSize - 1;
    int parentPos = (childPos-1)/2;
    Heap_Node child = h->heap[childPos];
    h->heap[childPos] = child;
    h->positionArray[id] = childPos;
}

/*
 * Deletes 0th (smallest) element fromt heap
 * HEAPIFIES TOP DOWN
 * */
int Heap_Delete(MinHeap_t* h){
    int retVal = h->heap[0].id;
    Heap_Node temp = h->heap[h->currentSize - 1];
    h->heap[h->currentSize - 1] = h->heap[0]; // Moving the smallest element in the heap to the end
    h->positionArray[h->heap[0].id] = h->currentSize - 1;
    h->currentSize--; // Decrementing the heap size

    // Readjust top down
    int parentPos = 0;
    int childPos = 2*parentPos + 1;
    Heap_Node parent = temp; // The last element in the heap will become the root when the minimum element from the heap is removed
    while(childPos < h->currentSize){
        Heap_Node child = h->heap[childPos];
	// should look at both children and 
        if((childPos + 1 < h->currentSize) && child.distance > h->heap[childPos + 1].distance) // To get the smallest child
	{
            child = h->heap[childPos + 1]; //  Smaller of the 2 children
	    childPos++;
	}
        if(child.distance < parent.distance){
            h->heap[parentPos] = child;
            h->positionArray[child.id] = parentPos;
            parentPos = childPos;
            childPos = 2*parentPos + 1;
        }
        else break;
    }
    h->heap[parentPos] = parent;
    h->positionArray[parent.id] = parentPos;
    return retVal;
}

/*
 * Deletes 0th (smallest) element fromt heap
 * HEAPIFIES BOTTOM UP
 * */
void Heap_Update(MinHeap_t* h, int index, int newDistance, int newPredecessor){
    h->heap[index].predecessor = newPredecessor;
    h->heap[index].distance = newDistance;

    // Readjust bottom up
    int childPos = index;
    int parentPos = (childPos-1)/2;
    Heap_Node child = h->heap[childPos];
    while(parentPos >= 0 && childPos != parentPos){
        Heap_Node parent = h->heap[parentPos];
        if(parent.distance > child.distance){
            h->heap[childPos] = parent; // A vertex slides down if its distance is greater
            h->positionArray[parent.id] = childPos;
            childPos = parentPos;
            parentPos = (childPos - 1)/2;
        }
        else break; // Already a heap
    }
    h->heap[childPos] = child;
    h->positionArray[child.id] = childPos;
}

/*
 * Returns the position of a particular id
 * */
int Heap_Search(MinHeap_t* h, int id){
    return h->positionArray[id];
}

/*
 * Returns the current size of the heap after deletions
 * */
int Heap_Size(MinHeap_t* h){
    return h->currentSize;
}

/*
 * Returns the distance of a particular id from the destination
 * */
int Heap_GetDistance(MinHeap_t* h, int index){
    return h->heap[index].distance;
}


/*
 * Prints all the shortest paths from all nodes to the destination
 * Each node has a 'predecessor' which points in the shortest direction to the destination
 *
 * If we start from a node and look at its predecessor and then look at its predecessor,
 * eventually we reach the destination.
 * 
 * We print out this path for all nodes (except the destination itself)
 * */
void printPath(MinHeap_t* h, int destination){
    int *parent = (int*)malloc(sizeof(int) * h->capacity);
    int *distance = (int*)malloc(sizeof(int) * h->capacity);
    for(int i = 0; i < h->capacity; i++){
        int j = h->heap[i].id;
        parent[j] = h->heap[i].predecessor;
        distance[j] = h->heap[i].distance;
    }
    for(int i = 0; i < h->capacity; i++){
        if(i == destination - 1) continue;
        printf("%d ", i+1);
        if(distance[i] == INT_MAX) printf("NO PATH\n");
        else{
            printf("%d ", i+1);
            int next = i;
            while((next = parent[next]) != destination - 1) printf("%d ", next + 1);
            printf("%d %d\n", destination, distance[i]);
        }
    }
    free(parent);
    free(distance);
}

/*
 * Implementation of Dijkstra's Algorithm
 * */
void Dijkstra(Graph_t g, int vertex) {
    MinHeap_t *queue = Heap_Init(g.numVertices);
    for(int i = 0; i < g.numVertices; i++) Heap_Insert(queue, i, INT_MAX, vertex-1);
    Heap_Update(queue, Heap_Search(queue, vertex-1), 0, vertex-1);

    while(Heap_Size(queue) != 0){ // While priority queue is not empty
        int nearestNode = Heap_Delete(queue);
        int prevIndex = Heap_Search(queue, nearestNode);
        int distance = Heap_GetDistance(queue, prevIndex);
        Vertex *temp = g.list[nearestNode].head;
        while(temp != NULL){
            int index = Heap_Search(queue, temp->id); // Finding the position of this vertex in the MinHeap_ array
            if(index < Heap_Size(queue)){ // Vertex is a part of the heap
                int newDistance = distance + temp->weight;
                int oldDistance = Heap_GetDistance(queue, index);
                if(newDistance < oldDistance) Heap_Update(queue, index, newDistance, nearestNode);
            }
            temp = temp->next;
        }
    }
    printPath(queue, vertex);
    Heap_Destroy(queue);
}
