
/*
 * Helper Function Declarations
 * */


// Graph_ 

// The structure of a vertex in the graph
typedef struct vertex{
    int id;
    int weight;           
    struct vertex *next;
}Vertex;

// The structure of the root node of the adjacency list 
typedef struct adjacencyList{
    Vertex *head;
}AdjacencyList;

// A wrapper structure that holds the graph
typedef struct graph{
    int numVertices;     // Number of vertices in the graph
    AdjacencyList *list; // Adjacency list
}Graph_t;

// Graph_ Routines
Graph_t* Graph_Init(int n); // Initialises the graph 
void Graph_Append(Graph_t*g, int source, int destination, int weight); // Adds an edge to the graph
void Graph_Destroy(Graph_t*g); // Destroys the graph (frees up allocated memory)

Graph_t* Graph_Invert(Graph_t*g); // Unused

// Priority Queue using Min Heap_

// The structure of a node in the heap
typedef struct heapnode{
    int id;
    int distance;
    int predecessor;
}Heap_Node;

// The structure of the min heap
typedef struct minheap{
    int currentSize;
    int capacity;
    int *positionArray; // This array holds the position of the various vertices in the heap
    Heap_Node *heap;
}MinHeap_t;

// Heap_ Routines
MinHeap_t* Heap_Init(int n); // Initialises the heap
void Heap_Insert(MinHeap_t* h, int id, int distance, int predecessor); // Inserts a node into the heap
int Heap_Delete(MinHeap_t* h); // Deletes the minimum node from the heap
int Heap_Search(MinHeap_t* h, int id); // Returns the index of a vertex in the heap (using the position array)
void Heap_Update(MinHeap_t* h, int id, int newDistance, int newPredecessor); // Updates the priority of an element in the heap
int Heap_Size(MinHeap_t* h); // Returns the current size of the heap
int Heap_GetDistance(MinHeap_t* h, int id); // Returns the current distance of a node in the heap


// Utility functions
void printPath(MinHeap_t* h, int destination);

// Dijkstra
void Dijkstra(Graph_t g, int vertex);
