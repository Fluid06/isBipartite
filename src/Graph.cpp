#include "../include/Graph.hpp"

Graph::Graph(uint32_t nodeCount)
{
    nodes.reserve(nodeCount);

    for (uint32_t i = 0; i < nodeCount; i++)
    {
        nodes.emplace_back(i); // Node n(i); nodes.push_back(n);
    }
}

void Graph::addEdge(uint32_t n1, uint32_t n2)
{   
    nodes[n1].addNeighbor(n2);
    nodes[n2].addNeighbor(n1);
}

bool Graph::isBipartite()
{
    for (const Node& node : nodes)
    {
        if (node.type != NONE) continue;
        if (!isBipartite(node.getIdx(), EVEN)) return false;
    }

    return true;
}

bool Graph::isBipartite(uint32_t current, Type prev)
{
    Node& currentNode = nodes[current];
    
    if (currentNode.type == prev) return false;
    if (currentNode.type != NONE) return true;

    currentNode.type = (prev == EVEN) ? ODD : EVEN;

    // checks bipartity of all neighbors by Depth-First search
    for (uint32_t neighbor : currentNode.getNeighbors())
    {
        if (!isBipartite(neighbor, currentNode.type)) return false;
    }

    return true;
}