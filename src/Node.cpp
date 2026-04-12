#include "../include/Node.hpp"

Node::Node(uint32_t idx) : idx(idx)
{}

uint32_t Node::getIdx() const
{
    return idx;
}

const std::vector<uint32_t>& Node::getNeighbors() const
{
    return neighbors;
}

void Node::addNeighbor(uint32_t n)
{
    neighbors.push_back(n);
}