// Youssef Elshabasy
// A class to represent a graph

#ifndef STUDENT_GRAPH
#define STUDENT_GRAPH

#include <iostream>
#include <unordered_map>
#include <limits>
#include "binary_heap.h"

#define INFINITY std::numeric_limits<double>::infinity()

class Graph
{
private:
    /// @brief The number of vertices in the graph.
    std::size_t numOfVertices;

    /// @brief The graph represented as an adjacency list.
    std::unordered_map<int, std::unordered_map<int, double>> graph;

public:
    /// @brief Constructs a graph with the given number of vertices.
    /// @param numOfVertices The number of vertices in the graph.
    explicit Graph(size_t numOfVertices)
        : numOfVertices(numOfVertices)
    {
        graph.reserve(numOfVertices);
    }

    /// @brief Adds an edge to the graph.
    /// @param source The source vertex.
    /// @param destination The destination vertex to connect to.
    /// @param weight The weight of the edge.
    void AddEdge(int source, int destination, double weight)
    {
        graph[source][destination] = weight;
    }

    /// @brief Checks if the graph has an edge between the source and destination vertices.
    /// @param source The source vertex.
    /// @param destination The destination vertex to check the edge to.
    /// @return True if the graph has an edge from the source to the destination vertex, false otherwise.
    bool HasEdge(int source, int destination)
    {
        return graph[source].find(destination) != graph[source].end();
    }

    /// @brief Gets the weight of the edge between the source and destination vertices.
    /// @param source The source vertex.
    /// @param destination The destination vertex to check the wieght of the edge to.
    /// @return The weight of the edge between the source and destination vertices, INFINITY if the edge does not exist.
    double EdgeWeight(int source, int destination)
    {
        if (!HasEdge(source, destination))
            return INFINITY;

        return graph[source][destination];
    }

    /// @brief Displays the shortest paths from the given start vertex to all other vertices in the graph using Dijkstra's algorithm.
    /// @param start The start vertex to find the shortest paths from.
    void DisplayShortestPaths(int start)
    {
        std::vector<std::vector<int>> minimumPaths(numOfVertices + 1, std::vector<int> { start });

        std::vector<double> minimumCosts(numOfVertices + 1, INFINITY);
        minimumCosts[start] = 0.0;

        BinaryHeap<std::pair<int, double>> priorityQueue;
        priorityQueue.insert(std::make_pair(start, 0.0));

        while (!priorityQueue.isEmpty())
        {
            int currentVertex = priorityQueue.findMin().first;
            double currentCost = priorityQueue.findMin().second;
            priorityQueue.deleteMin();

            for (const auto& connectedVertex : graph[currentVertex])
                if (currentCost + connectedVertex.second < minimumCosts[connectedVertex.first])
                {
                    minimumCosts[connectedVertex.first] = currentCost + connectedVertex.second;
                    priorityQueue.insert({ connectedVertex.first, minimumCosts[connectedVertex.first] });

                    minimumPaths[connectedVertex.first] = minimumPaths[currentVertex];
                    minimumPaths[connectedVertex.first].push_back(connectedVertex.first);
                }
        }

        for (size_t vertex = 1; vertex < minimumCosts.size(); ++vertex)
        {
            if (minimumCosts[vertex] == INFINITY)
                std::cout << vertex << ": not_possible" << std::endl;
            else
            {
                std::cout << vertex << ": ";
                for (const auto& connectedVertex : minimumPaths[vertex])
                    std::cout << connectedVertex << " ";
                std::cout << "cost: " << minimumCosts[vertex] << std::endl;
            }
        }
    }
};

#endif