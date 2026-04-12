#pragma once

#include <vector>
#include "Node.hpp"

class Graph
{
private:
    std::vector<Node> nodes;

public:
    Graph(uint32_t nodeCount);
    void addEdge(uint32_t n1, uint32_t n2);
    bool isBipartite();
    bool isBipartite(uint32_t current, Type prev);
};