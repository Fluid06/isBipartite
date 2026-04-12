#pragma once

#include <vector>
#include <cstdint>

enum Type
{
    NONE, ODD, EVEN
};

class Node
{
private:
    uint32_t idx;
    std::vector<uint32_t> neighbors;
    
public:
    Type type = NONE;
    Node(uint32_t idx);
    uint32_t getIdx() const;
    const std::vector<uint32_t>& getNeighbors() const;
    void addNeighbor(uint32_t n);
};