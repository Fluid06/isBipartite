#include "../include/Graph.hpp"
#include <iostream>

Graph::Graph(uint32_t vertexCount)
{
    vertices.reserve(vertexCount);

    for (uint32_t i = 0; i < vertexCount; i++)
    {
        vertices.emplace_back(i); // Vertex vertex(i); vertices.push_back(vertex);
    }
}

void Graph::addEdge(uint32_t n1, uint32_t n2)
{   
    vertices.at(n1).addNeighbor(n2);
    vertices.at(n2).addNeighbor(n1);
}

bool Graph::isBipartite()
{
    std::stack<uint32_t> stack;
    
    for (Vertex& vertex : vertices)
    {
        if (vertex.getColor() != NONE) continue;

        vertex.setColor(GREEN);
        stack.push(vertex.getIdx());

        do
        {
            uint32_t current = stack.top();
            stack.pop();

            Color currentColor = vertices.at(current).getColor();
            Color nextColor = (currentColor == GREEN) ? RED : GREEN;

            for (uint32_t neighbor : vertices.at(current).getNeighbors())
            {
                Color neighborColor = vertices.at(neighbor).getColor();

                if (neighborColor == currentColor) return false;
                if (neighborColor != NONE) continue;
                
                vertices.at(neighbor).setColor(nextColor);
                stack.push(neighbor);
            }
        } while (!stack.empty());
    }

    return true;
}