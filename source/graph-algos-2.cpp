#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <stack>
#include <cmath>
#include "graph-algos.h"
#include "graph.h"
#include "represenation-struct.h"
#include <math.h>
#include "graph-algos-2.h"

namespace GraphAlgos {

    bool ifGraphHasEulerCycle(Graph &graphHandle)
    {
        int n = graphHandle.sizeOfGraph;
        bool isDirected = graphHandle.getDirectionality();

        // Copies adjList, to avoid conflict while deleteing the edges
        std::vector<std::vector<int>> adjListTemp(n);
        for (int i = 0; i < n; i++) {
            adjListTemp[i] = graphHandle.getVertexChildren(i);
        }

        // If Euler cycle can even exist
        if (!isDirected) {
            // Undirected graph: degree must be even
            for (int i = 0; i < n; i++) {
                if (adjListTemp[i].size() % 2 != 0) {
                    std::cout << "No Euler cycle found - vertex " << i
                              << " has odd degree (" << adjListTemp[i].size() << ")!" << std::endl;
                    return false;
                }
            }
        } else {
            // Directed graph: inDegree == outDegree
            std::vector<int> inDegree(n, 0);
            for (int i = 0; i < n; i++) {
                for (int v : adjListTemp[i]) {
                    inDegree[v]++;
                }
            }
            for (int i = 0; i < n; i++) {
                if ((int)adjListTemp[i].size() != inDegree[i]) {
                    std::cout << "No Euler cycle found - vertex " << i
                              << " has out-degree=" << adjListTemp[i].size()
                              << " but in-degree=" << inDegree[i] << "!" << std::endl;
                    return false;
                }
            }
        }

        // Find a connected node
        int startVertex = -1;
        for (int i = 0; i < n; i++) {
            if (!adjListTemp[i].empty()) {
                startVertex = i;
                break;
            }
        }
        if (startVertex == -1) {
            std::cout << "Graph has no edges!" << std::endl;
            return false;
        }

        // Hierholzer's algorithm – O(E)
        std::stack<int> stk;
        std::vector<int> cycle;
        stk.push(startVertex);

        while (!stk.empty()) {
            int v = stk.top();
            if (adjListTemp[v].empty()) {
                // No edges - add a node to cycle
                cycle.push_back(v);
                stk.pop();
            } else {
                // Go to another edge
                int u = adjListTemp[v].back();
                adjListTemp[v].pop_back();
                // For undirected delete the second edge in list
                if (!isDirected) {
                    auto it = std::find(adjListTemp[u].begin(), adjListTemp[u].end(), v);
                    if (it != adjListTemp[u].end()) {
                        adjListTemp[u].erase(it);
                    }
                }
                stk.push(u);
            }
        }

        // Check cohesion, if there are any edges, the FULL graph wasnt traversed
        for (int i = 0; i < n; i++) {
            if (!adjListTemp[i].empty()) {
                std::cout << "No Euler cycle found - graph is not connected!" << std::endl;
                return false;
            }
        }

        // Reverse to print correctly
        std::reverse(cycle.begin(), cycle.end());

        std::cout << "Euler cycle found: ";
        for (size_t i = 0; i < cycle.size(); i++) {
            std::cout << cycle[i];
            if (i + 1 < cycle.size()) std::cout << " -> ";
        }
        std::cout << std::endl;

        return true;
    }

    bool BacktrackingAlgorithm(Graph& graphHandle, int node, int startNode, int n, bool visited[]){
        
        #ifdef DEBUG
            std::cout<<"Program wita z początku backtracku"<<std::endl;
        #endif
        visited[node] = true;
        const auto& neighbours = graphHandle.adjacencyList.at(node);

        if (n == graphHandle.sizeOfGraph)
        { 
            if (std::find(neighbours.begin(), neighbours.end(), startNode) != neighbours.end()) return true;
            else {
                visited[node] = false;
                return false;
            }
        }

        for (auto x : neighbours){
            if (visited[x]) continue;
            if (BacktrackingAlgorithm(graphHandle, x, startNode, n+1, visited)) return true;
        }    //ifList
        visited[node] = false;
        return false;
    }

    bool ifGraphHasHamiltonCycle(Graph &graphHandle)
    {
        bool visited[graphHandle.sizeOfGraph]{};
        #ifdef DEBUG
            std::cout<<"Program wita z początku algorytmu"<<graphHandle.sizeOfGraph<<std::endl;
        #endif
        size_t i = 0;
        try {
            while (i < graphHandle.adjacencyList.size())
            {
                if (graphHandle.adjacencyList[i].size()>0) break;
                i++;
            }
            if (i == graphHandle.sizeOfGraph) throw std::runtime_error("Graph is empty");;
            bool final =  true;
            // Big optimization would falsify the results
           // for (int i = 0; i < graphHandle.sizeOfGraph; i++) {
            //    if (graphHandle.adjacencyList[i].size() < 2) final = false; 
           // }
            if (final)
                final = BacktrackingAlgorithm(graphHandle, i, i, 1, visited);
            if (final) std::cout<<"Graph has a hamiltonian cycle."<<std::endl;
            else std::cout<<"Graph has no hamiltonian cycle!"<<std::endl;
            return final;
        }
        catch (std::runtime_error e){
            std::cout<<"Program has failed"<<std::endl;
            return false;
        }
        
    }
};