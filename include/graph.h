#pragma once
#include <vector>
#include <stdexcept>
#include "represenation-struct.h"
#include "algorithm"

class Graph {
protected:
    bool hasCycles = false;      // Due to the project's requirements we can take those for granted.
    bool isDirectional = true;

    bool isCoherent = true;
    float connectivity = 0.0f;
    float calculateConnectivity();
    //CreateHamiltonGraph(Graph&int vertexCount, float connectivity);
    void CreateHamiltonGraph(int vertexCount, float connectivity);

public:
    Representation graphRepresentation;
    std::vector<std::vector<int>> representationStructure; // Contains a matrix or a table of edges 
    size_t sizeOfGraph; // = adjacencyList.size()

    Graph(int vertexCount, float connectivity, bool dag=true, bool hamiltionian=false);
    void addVertices(int amount); // Very not recomended
    void addEdge(std::pair<int,int> startEndPair);
    const std::vector<int>& getVertexChildren(int vertex);
    std::vector<int> getVertexChildrenRep(int vertex); // Returns a list of neighbours of a node based on representation
    void createRepStructure(); // Converts input (adjList) into the chosen representation
    std::vector<std::vector<int>> adjacencyList; 
    float getConnectivityNumber();
    bool getCoherence();
    bool getCyclicality();
    bool getDirectionality();
};