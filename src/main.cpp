#include <iostream>
#include <fstream>

#include "../include/Graph.hpp"

int main()
{
    std::ifstream f("../test/CyclicGraph.txt");
    
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

    for (unsigned int row = 0; row < matrixSize; row++)
    {
        std::getline(f, line);
        for (unsigned int col = row; col < matrixSize; col++)
        {  
            if (line[col] == '1')
            {
                graph.addEdge(row, col);
            }
        }
    }
    std::cout << "Graphs bipartity: " << graph.isBipartite() << std::endl;

    return 0;
}