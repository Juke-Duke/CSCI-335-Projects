// Youssef Elshabasy
// Tests the graph class by querying the graph for adjacency

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "graph.h"

/// @brief Creates a graph from a file and tests the graph for adjacency.
/// @param argc The number of arguments.
/// @param argv The arguments.
/// @return 0 if the program runs successfully, 1 otherwise.
int graphTestDriver(int argc, char** argv)
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

  std::ifstream queryFile(argv[2]);

  while (queryFile >> source >> destination)
  {
    if (graph.HasEdge(source, destination))
      std::cout << source << " " << destination << ": connected " << graph.EdgeWeight(source, destination) << std::endl;
    else
      std::cout << source << " " << destination << ": not_connected" << std::endl;
  }

  return 0;
}

int main(int argc, char** argv)
{
  if (argc != 3)
  {
    std::cout << "Usage: " << argv[0] << " <GRAPH_File>" << "<ADJACENCY_QUERYFILE>" << std::endl;
    return 0;
  }

  graphTestDriver(argc, argv);

  return 0;
}
