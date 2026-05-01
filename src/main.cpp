#include <iostream>
#include <fstream>
#include <chrono>

#include "../include/Graph.hpp"

#define PATH "../test/BipartiteGraph4.txt"

int main()
{
    std::ifstream f(PATH);
    
    if (!f.is_open()) 
    {
        std::cout << "Soubor nebylo mozne nalezt nebo jej otevrit." << std::endl;
        return 1;
    }

    std::string line;
    uint32_t matrixSize;
    
    std::getline(f, line);
    matrixSize = stoi(line);
    
    Graph graph(matrixSize);

    for (uint32_t row = 0; row < matrixSize; row++)
    {
        std::getline(f, line);
        for (uint32_t col = row; col < matrixSize; col++)
        {  
            if (line[col] == '1')
            {
                graph.addEdge(row, col);
            }
        }
    }

    f.close();

    if (graph.isBipartite())
    {
        std::cout << "Graf je bipartitni." << std::endl;
    } else
    {
        std::cout << "Graf neni bipartitni." << std::endl;
    }

    return 0;
}