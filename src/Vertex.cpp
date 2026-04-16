#include "../include/Vertex.hpp"

Vertex::Vertex(uint32_t idx) : idx(idx)
{}

uint32_t Vertex::getIdx() const { return idx; }

Color Vertex::getColor() const { return color; }

void Vertex::setColor(Color color)
{
    this->color = color;
}

const std::vector<uint32_t>& Vertex::getNeighbors() const { return neighbors; }

void Vertex::addNeighbor(uint32_t idx)
{
    neighbors.push_back(idx);
}