#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <vector>
#include <algorithm>

#include "Graph.hpp"

const std::string PATH = "../TestData";

int main()
{
    std::vector<std::filesystem::path> testFiles;

    for (const auto& file : std::filesystem::directory_iterator(PATH))
    {
        if (file.path().filename() != "results.txt")
        {
            testFiles.push_back(file);
        }
    }

    sort(testFiles.begin(), testFiles.end());

    for (const auto& filepath : testFiles)
    {
        std::ifstream f(filepath.string());
        
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
            std::cout << "Graph in " << filepath.filename().string() << " is bipartite" << std::endl;
        } else
        {
            std::cout << "Graph in " << filepath.filename().string() << " is not bipartite" << std::endl;
        }
    }


    return 0;
}