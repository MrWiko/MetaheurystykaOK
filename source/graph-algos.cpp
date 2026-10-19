#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <set>
#include <cmath>
#include "graph-algos.h"
#include "graph.h"
#define _USE_MATH_DEFINES
#include "represenation-struct.h"
#include <math.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace GraphAlgos {

    void printRepresentation(Graph& graphHandle, Representation representation){
        std::vector<std::vector<int>> result; 
        int size = graphHandle.sizeOfGraph; 

        if (representation == matrix){
            for (int i = 0; i < size; i++)
                result.push_back(std::vector<int>(size, 0));

            for (int i = 0; i < size; i++){
                for (auto v : graphHandle.getVertexChildren(i)){
                    result[i][v] = 1; 
                    result[v][i] = 1; //if there is an out edge from a node 
                }
            }

            std::cout << "  | ";
            for (int j = 1; j <= size; j++) 
                std::cout << j << " ";
            std::cout << "\n";

            std::cout << "--+";
            for (int j = 0; j < size * 2; j++) 
                std::cout << "-";
            std::cout << "\n";

            for (int i = 0; i < size; i++) {
                std::cout << i + 1 << " | ";
                for (int j = 0; j < size; j++) {
                    std::cout << result[i][j] << " ";
                }
                std::cout << "\n";
            }
        }

        else if (representation == list){
            for (int i = 0; i < graphHandle.sizeOfGraph; i++){
                std::cout << i+1 << ": "; 
                for (auto v : graphHandle.getVertexChildren(i))
                    std::cout << v+1 << " "; 
                std::cout << std::endl;
            }
        }

        else if (representation == table){
            for (int i = 0; i < graphHandle.sizeOfGraph; i++){
                for (auto v : graphHandle.getVertexChildren(i))
                    std::cout << "(" << i+1 << ", " << v+1 << ") "; 
                std::cout << std::endl;
            }
        }
    }

    void findEdge(Graph& graphHandle, int fromV, int toV){
        bool ifExists = false; 

        if(graphHandle.graphRepresentation == matrix){
            if(graphHandle.representationStructure[fromV][toV] == 1)
                ifExists = true; 
        }

        else if(graphHandle.graphRepresentation == list){
            for (auto v : graphHandle.getVertexChildren(fromV))
                if(v == toV)
                    ifExists = true; 
        }

        else if(graphHandle.graphRepresentation == table){
            for (auto edge : graphHandle.representationStructure)
                if (edge[1] == toV)
                    ifExists = true;
        }

        if (ifExists == true) 
            std::cout << "True: edge (" << fromV+1 << ',' << toV+1 << ") DOES exist in the Graph!\n";
        else
            std::cout << "False: edge (" << fromV+1 << "," << toV+1 << ") DOES NOT exist in the Graph!\n";
    }

    void printDFS(Graph& graphHandle, int source, std::vector<bool>& ifVisited){
        ifVisited[source] = true; 
        std::cout << source+1 << " "; 

        for (auto v : graphHandle.getVertexChildrenRep(source))
            if (!ifVisited[v])
                printDFS(graphHandle, v, ifVisited);
    }

    void printDFSIni(Graph& graphHandle){
        std::vector<bool> ifVisited(graphHandle.sizeOfGraph, false);
        std::cout << "DFS Order: ";

        for(int vNumber = 0; vNumber < graphHandle.sizeOfGraph; vNumber++){ // Initialize a vector to see if a node has been visited
            if(!ifVisited[vNumber])
                printDFS(graphHandle, vNumber, ifVisited);
        }

        std::cout << std::endl;
    }

    bool printBFS(Graph& graphHandle){
        int size = graphHandle.sizeOfGraph;
        std::vector<bool> ifVisited(size, false);
        std::vector<int> result; 

        std::queue<int> q;

        for(int vNumber = 0; vNumber < size; vNumber++){
            if(!ifVisited[vNumber]){
                ifVisited[vNumber] = true; 
                q.push(vNumber);

                while(!q.empty()){
                    int current = q.front();
                    q.pop();
                    result.push_back(current);

                    for (auto v : graphHandle.getVertexChildrenRep(current)){
                        if (!ifVisited[v]){
                            q.push(v);
                            ifVisited[v] = true;
                        }
                    }
                }
            }
        }

        std::cout << "BFS Order: ";
        for (auto x : result)
            std::cout << x+1 << " ";
        std::cout << std::endl;

        if (result.size() == graphHandle.sizeOfGraph)
            return true;
        return false; 
    }

    void printTopSortKahn(Graph& graphHandle, std::vector<int>& inDegree){
        int V = graphHandle.sizeOfGraph;
        std::queue<int> q;

        for (int i = 0; i < V; i++) { // Only start from nodes that dont have any incoming edges
            if (inDegree[i] == 0) {
                q.push(i);
            }
        }

        while (!q.empty()) {
            int current = q.front();
            q.pop();

            std::cout << current+1 << " ";

            for (auto it : graphHandle.getVertexChildrenRep(current)) { // Traverse the graph while "deleting" edges
                inDegree[it]--;

                if (inDegree[it] == 0) {
                    q.push(it);
                }
            }
        }
    }

    void printTopSortKahnIni(Graph& graphHandle){
        int V = graphHandle.sizeOfGraph;
        std::vector<int> inDegree(V, 0);

        for (int i = 0; i < V; i++) { // Calculate the inDegree for each node
            for (auto v : graphHandle.getVertexChildrenRep(i)) {
                inDegree[v]++;
            }
        }

        std::cout << "Kahn sorted order: ";
        printTopSortKahn(graphHandle, inDegree);
        std::cout << std::endl;
    }

    void printTopSortTarjan(Graph& graphHandle, std::vector<int>& mark, std::vector<int>& tempRes){ // 0 - unmarked, 1 - temporarly marked/been tracversed in this path, 2 - perm/already been traversed
        for(int i = 0; i < graphHandle.sizeOfGraph; i++)
            if(mark[i] != 2)
                visitTarjan(graphHandle, i, mark, tempRes);
    }

    void visitTarjan(Graph& graphHandle, int nodeNumber, std::vector<int>& mark, std::vector<int>& tempRes){ // Traverse the graph using DFS style traversing and change "colors"
        if (mark[nodeNumber] == 2)
            return;

        mark[nodeNumber] = 1;

        for (auto v : graphHandle.getVertexChildrenRep(nodeNumber))
            visitTarjan(graphHandle, v, mark, tempRes);

        mark[nodeNumber] = 2; 
        tempRes.push_back(nodeNumber+1);
    }
    
    void printTopSortTarjanIni(Graph& graphHandle){
        std::vector<int> mark(graphHandle.sizeOfGraph, 0);
        std::vector<int> tempRes;

        std::cout << "Tarjan sorted order: ";
        printTopSortTarjan(graphHandle, mark, tempRes);

        for(int i = tempRes.size()-1; i > -1; i--) // Print in reversed order to imitate a stack
            std::cout << tempRes[i] << " ";

        std::cout << std::endl;
    }

void exportTickZ(Graph& graphHandle){
    const int n = graphHandle.sizeOfGraph;
    const double radius = 4.0;

    std::cout << "\\begin{tikzpicture}[>=stealth, every node/.style={circle, draw}]\n";

    // ---- Place vertices ----
    for (int i = 0; i < n; ++i)
    {
        double angle = 2.0 * M_PI * i / n;

        double x = radius * cos(angle);
        double y = radius * sin(angle);

        std::cout << "\\node (v" << i << ") at ("
                  << x << "," << y << ") {" << (i+1) << "};\n";
    }

    std::cout << "\n";

    // ---- Draw edges ----
    std::set<std::pair<int,int>> drawn;

    for (int from = 0; from < n; ++from)
    {
        const auto& children = graphHandle.getVertexChildren(from);

        for (int to : children)
        {
            // Skip duplicate edges for undirected graphs
            if (!graphHandle.getDirectionality())
            {
                if (drawn.count({to, from}))
                    continue;

                drawn.insert({from, to});
            }

            if (graphHandle.getDirectionality())
            {
                std::cout << "\\draw[->] (v"
                          << from << ") -- (v"
                          << to << ");\n";
            }
            else
            {
                std::cout << "\\draw (v"
                          << from << ") -- (v"
                          << to << ");\n";
            }
        }
    }

    std::cout << "\\end{tikzpicture}\n";
}
};
