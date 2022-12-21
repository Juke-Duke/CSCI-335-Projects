# Graph

In this assignment, we implement an adjacency list, as well as implement Dijkstra's algorithm to find the shortest path between a starting vertex to all other vertices in the graph.

## Getting Started

### Importing the header file:
```c++
#include "graph.h"
```

### Compiling the program using a Makefile:
```bash
$ make clean
$ make all
```

### Creating a Graph and testing queries:
```bash
$ ./CreateGraphAndTest { graph_file } { query_file }
```

### Finding the shortest paths:
```bash
$ ./FindPaths { graph_file } { source_vertex }
```

## Constructors

### `explicit Graph(std::size_t)`
Initializes a new instance of the Graph class that contains a specified number of vertices, and no edges.
```c++
Graph graph(5); // Creates a graph with 5 vertices, and no edges
```

## Methods

### `void AddEdge(int, int, double)`
Adds an edge to the graph given the source vertex, destination vertex, and weight of the edge.
```c++
Graph graph(2);

graph.AddEdge(2, 1, 2.8); // Adds an edge from vertex 2 to vertex 1 with weight 2.8.
```

### `bool HasEdge(int, int)`
Checks if an edge exists from the source vertex to the destination vertex.
```c++
Graph graph(2);

graph.AddEdge(2, 1, 2.8);

graph.HasEdge(2, 1); // Returns true

graph.HasEdge(1, 2); // Returns false
```

### `double EdgeWeight(int, int)`
Returns the weight of the edge from the source vertex to the destination vertex.
```c++
Graph graph(2);

graph.AddEdge(2, 1, 2.8);

graph.EdgeWeight(2, 1); // Returns 2.8

graph.EdgeWeight(1, 2); // Returns INFINITY
```

### `void DisplayShortestPaths(int)`
Utilizing Dijkstra's algorithm, finds the shortest path from the source vertex to all other vertices in the graph, then displays the path and its weight.
```c++
Graph graph(5);

graph.AddEdge(1, 2, 0.2);
graph.AddEdge(1, 4, 10.1);
graph.AddEdge(1, 5, 0.5);
graph.AddEdge(2, 1, 1.5);
graph.AddEdge(3, 2, 100.0);
graph.AddEdge(3, 4, 50.2);
graph.AddEdge(5, 2, 10.5);
graph.AddEdge(5, 3, 13.9);

graph.DisplayShortestPaths(2);

// Output:
// 1: 2 1 cost: 1.5
// 2: 2 cost: 0
// 3: 2 1 5 3 cost: 15.9
// 4: 2 1 4 cost: 11.6
// 5: 2 1 5 cost: 2
```

Youssef Elshabasy - 2022
