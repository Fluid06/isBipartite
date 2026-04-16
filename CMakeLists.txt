cmake_minimum_required(VERSION 3.10)

project(BipartiteGraph)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(isBipartite
    src/main.cpp
    src/Vertex.cpp
    src/Graph.cpp
)

target_compile_options(isBipartite PRIVATE -Wall -Wextra -fsanitize=address)
target_link_options(isBipartite PRIVATE -fsanitize=address)
target_include_directories(isBipartite PRIVATE include)