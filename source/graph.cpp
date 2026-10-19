#include "graph.h"

float Graph::calculateConnectivity()
{
    float connectivity;
    unsigned int vCount = adjacencyList.size();
    if (vCount <= 1) {
        return 0.0f;
    }

    unsigned int eCount = 0;
    for (const auto& children : adjacencyList) {
        eCount += children.size();
    }

    connectivity = static_cast<float>(eCount) / (vCount * (vCount - 1));
    return connectivity;
}

void Graph::CreateHamiltonGraph(int vertexCount, float connectivity){
     // Creating the cycle
            bool visited[vertexCount]{};
            int nodeA = rand()%vertexCount;
            int startNode = nodeA;
            visited[nodeA] = true;
            int nodeB;
            for (size_t i = 0; i < vertexCount-1; i++)
            {
                do {nodeB = rand()%vertexCount; }
                while (visited[nodeB]);
                visited[nodeB] = true;
                adjacencyList[nodeA].push_back(nodeB);
                adjacencyList[nodeB].push_back(nodeA);
                nodeA = nodeB;
            }
            adjacencyList[nodeB].push_back(startNode);
            adjacencyList[startNode].push_back(nodeB);

            while (calculateConnectivity()<connectivity){
                // Populating the graph with edges until connectivity goal is set
                int node1 = rand()%vertexCount;
                int node2 = rand()%vertexCount;
                while (node2==node1) node2 = rand()%vertexCount;
                int node3 = rand()%vertexCount;
                while (node3==node1) node3 = rand()%vertexCount;
                while (node3==node2) node3 = rand()%vertexCount;
                // Make sure that we can add all the edges.
                if (std::find(adjacencyList[node1].begin(), adjacencyList[node1].end(), node2) != adjacencyList[node1].end()) {
                    continue;
                }
                if (std::find(adjacencyList[node1].begin(), adjacencyList[node1].end(), node3) != adjacencyList[node1].end()) {
                    continue;
                }
                if (std::find(adjacencyList[node2].begin(), adjacencyList[node2].end(), node3) != adjacencyList[node2].end()) {
                    continue;
                }
                adjacencyList[node1].push_back(node2);
                adjacencyList[node2].push_back(node1);
                adjacencyList[node1].push_back(node3);
                adjacencyList[node3].push_back(node1);
                adjacencyList[node2].push_back(node3);
                adjacencyList[node3].push_back(node2);
            }
}

Graph::Graph(int vertexCount, float connectivity, bool dag, bool hamiltonian)
{
    adjacencyList.resize(vertexCount);
    this->sizeOfGraph = vertexCount;
    this->connectivity = connectivity;
    if (dag){

        for (int i = 0; i < vertexCount; ++i) {
            for (int j = i+1; j < vertexCount; ++j) {
                if (static_cast<float>(rand()) / RAND_MAX < connectivity) {
                    adjacencyList[i].push_back(j);
                }
            }
        }
        isDirectional = true;
    }
    if (!dag){
        if (hamiltonian){
            CreateHamiltonGraph(vertexCount, connectivity);
        }
        else {
            CreateHamiltonGraph(vertexCount-1, connectivity); // It leaves out one vertex which will be isolated warranting nonhamiltonity.
        }
        isDirectional = false;
    }
    this->connectivity = calculateConnectivity();
}

void Graph::addVertices(int amount)
{    
    if (amount <= 0) return;
    adjacencyList.resize(adjacencyList.size()+amount);
    this->sizeOfGraph += amount;
    isCoherent = false;
    connectivity = calculateConnectivity();
}

void Graph::addEdge(std::pair<int, int> startEndPair)
{
    
    if (startEndPair.second >= (int)adjacencyList.size() || startEndPair.second < 0) {
        throw std::out_of_range("Target vertex out of range");
    }
    adjacencyList.at(startEndPair.first).push_back(startEndPair.second);
    connectivity = calculateConnectivity();
}

void Graph::createRepStructure(){
    if(graphRepresentation == matrix){
        for(int i = 0; i < sizeOfGraph; i++)
            representationStructure.push_back(std::vector<int>(sizeOfGraph, 0));
        
        for (int i = 0; i < sizeOfGraph; i++){
            for (auto v : this->getVertexChildren(i)){
                representationStructure[i][v] = 1; 
                //representationStructure[v][i] = -1; 
            }
        }
    }

    else if(graphRepresentation == table){
        for (int i = 0; i < sizeOfGraph; i++){
            for (auto v : this->getVertexChildren(i))
                representationStructure.push_back({i, v});
        }
    }

    else
        return;
}

const std::vector<int> &Graph::getVertexChildren(int vertex)
{
    return adjacencyList.at(vertex);
}

std::vector<int> Graph::getVertexChildrenRep(int vertex)
{
    std::vector<int> vertexChildren; 

    if(graphRepresentation == matrix){
        for (int i = 0; i < sizeOfGraph; i++)
            if(representationStructure[vertex][i] == 1)
                vertexChildren.push_back(i);
    }

    else if(graphRepresentation == list){
        vertexChildren = adjacencyList.at(vertex);
    }   

    else if(graphRepresentation == table){
        for(auto edge : representationStructure){
            if (edge[0] == vertex)
                vertexChildren.push_back(edge[1]);
        }
    }

    return vertexChildren;
}

float Graph::getConnectivityNumber()
{
    return connectivity;
}

bool Graph::getCoherence()
{
    return isCoherent;
}

bool Graph::getCyclicality()
{
    return hasCycles;
}

bool Graph::getDirectionality()
{
    return isDirectional;
}
