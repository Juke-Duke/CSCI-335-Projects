// Youssef Elshabasy
// Finds the shortest paths from a given vertex to all other vertices in a graph

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "graph.h"

/// @brief The driver for the finding the shortest paths from a given vertex to all other vertices in a graph.
/// @param argc Amount of arguments.
/// @param argv The arguments.
/// @return 0 if successful, 1 if not.
int pathfindDriver(int argc, char** argv)
{
  std::ifstream graphFile(argv[1]);

  std::string line;
  int source, destination;

  graphFile >> line;
  Graph graph(std::stoi(line));

  while (std::getline(graphFile, line))
  {
    std::istringstream stream(line);

    double weight;

    stream >> source;

    while (stream >> destination >> weight)
    {
      graph.AddEdge(source, destination, weight);
    }
  }

  graphFile.close();

  graph.DisplayShortestPaths(atoi(argv[2]));

  return 0;
}

int main(int argc, char** argv)
{
  if (argc != 3)
  {
    cout << "Usage: " << argv[0] << " <GRAPH_FILE>" << "<STARTING_VERTEX>" << endl;
    return 0;
  }

  pathfindDriver(argc, argv);

  return 0;
}
