#pragma once

#include <vector>
#include <stack>
#include "Node.hpp"

/**
 * 
 */
class Graph
{
private:
    std::vector<Node> nodes;

public:
    Graph(uint32_t nodeCount);
    void addEdge(uint32_t n1, uint32_t n2);
    bool isBipartite();
};