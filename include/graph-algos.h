#pragma once
#include "graph.h"
#include "represenation-struct.h"

namespace GraphAlgos {
    /*
    type method_name(const Graph& graph, ...)
    */

    void printRepresentation(Graph& graphHandle, Representation representation);

    void findEdge(Graph& graphHandle, int fromV, int toV);

    void printDFS(Graph& graphHandle, int source, std::vector<bool>& ifVisited);
    void printDFSIni(Graph& graphHandle);
    bool printBFS(Graph& graphHandle); // Bool because its used also to check cohesion

    void printTopSortKahn(Graph& graphHandle, std::vector<int>& inDegree);
    void printTopSortKahnIni(Graph& graphHandle);

    void printTopSortTarjan(Graph& graphHandle, std::vector<int>& mark, std::vector<int>& tempRes);
    void visitTarjan(Graph& graphHandle, int nodeNumber, std::vector<int>& mark, std::vector<int>& tempRes);
    void printTopSortTarjanIni(Graph& graphHandle);
    
    void exportTickZ(Graph& graphHandle);
};