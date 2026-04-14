#include "../include/Graph.hpp"
#include <iostream>
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
    std::stack<uint32_t> st;
    
    for (Node& n : nodes)
    {
        if (n.type != NONE) continue;

        n.type = EVEN;
        st.push(n.getIdx());

        while (!st.empty())
        {
            uint32_t current = st.top();
            st.pop();

            Type currentType = nodes[current].type;
            Type nextType = (currentType == EVEN) ? ODD : EVEN;

            for (uint32_t adjacent : nodes[current].getNeighbors())
            {
                Type adjacentType = nodes[adjacent].type;

                if (adjacentType == currentType) return false;
                if (adjacentType != NONE) continue;
                
                nodes[adjacent].type = nextType;             
                st.push(adjacent);
            }
        }
    }

    return true;
}